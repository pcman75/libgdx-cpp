#include "stdafx.h"
#include "Renderer.h"
#include "ModelLoaderOld.h"

Renderer::Renderer(Application* app) 
	: m_invaderAngle(0), m_lastScore(0), m_lastLives(0), m_lastWave(0)
{
	m_spriteBatch = new SpriteBatch();


	FileHandleStream* in = Gdx.files->internalHandle("data/ship.obj").getStream(Read, Binary);
	m_shipMesh = ModelLoaderOld::loadObj(in);
	delete in;

	in = Gdx.files->internalHandle("data/invader.obj").getStream(Read, Binary);
	m_invaderMesh = ModelLoaderOld::loadObj(in);
	delete in;

	//FileHandleStream* in;
	in = Gdx.files->internalHandle("data/block.obj").getStream(Read, Binary);
	m_blockMesh = ModelLoaderOld::loadObj(in);
	delete in;

	in = Gdx.files->internalHandle("data/shot.obj").getStream(Read, Binary);
	m_shotMesh = ModelLoaderOld::loadObj(in);
	delete in;

	m_shipTexture = new Texture(Gdx.files->internalHandle("data/ship.png"), Pixmap::Format::RGB565, true);
	m_shipTexture->setFilter(Texture::TextureFilter::MipMap, Texture::TextureFilter::Linear);
	m_invaderTexture = new Texture(Gdx.files->internalHandle("data/invader.png"), Pixmap::Format::RGB565, true);
	m_invaderTexture->setFilter(Texture::TextureFilter::MipMap, Texture::TextureFilter::Linear);
	m_backgroundTexture = new Texture(Gdx.files->internalHandle("data/planet.jpg"), Pixmap::Format::RGB565, true);
	m_backgroundTexture->setFilter(Texture::TextureFilter::MipMap, Texture::TextureFilter::Linear);
	m_explosionTexture = new Texture(Gdx.files->internalHandle("data/explode.png"), Pixmap::Format::RGBA4444, true);
	m_explosionTexture->setFilter(Texture::TextureFilter::MipMap, Texture::TextureFilter::Linear);

	VertexAttribute attributes[] = {VertexAttribute(VertexAttributes::Position, 3, "a_position"), VertexAttribute(
		VertexAttributes::TextureCoordinates, 2, "a_texCoord")};
	m_explosionMesh = new Mesh(true, attributes, 2);

	float vertices[4 * 16 * (3 + 2)];
	int idx = 0;
	for (int row = 0; row < 4; row++) 
	{
		for (int column = 0; column < 4; column++) 
		{
			vertices[idx++] = 1;
			vertices[idx++] = 1;
			vertices[idx++] = 0;
			vertices[idx++] = 0.25f + column * 0.25f;
			vertices[idx++] = 0 + row * 0.25f;

			vertices[idx++] = -1;
			vertices[idx++] = 1;
			vertices[idx++] = 0;
			vertices[idx++] = 0 + column * 0.25f;
			vertices[idx++] = 0 + row * 0.25f;

			vertices[idx++] = -1;
			vertices[idx++] = -1;
			vertices[idx++] = 0;
			vertices[idx++] = 0.f + column * 0.25f;
			vertices[idx++] = 0.25f + row * 0.25f;

			vertices[idx++] = 1;
			vertices[idx++] = -1;
			vertices[idx++] = 0;
			vertices[idx++] = 0.25f + column * 0.25f;
			vertices[idx++] = 0.25f + row * 0.25f;
		}
	}

	m_explosionMesh->setVertices(vertices, sizeof(vertices)/sizeof(vertices[0]));
	m_font = new BitmapFont(Gdx.files->internalHandle("data/font10.fnt"), Gdx.files->internalHandle("data/font10.png"), false);

	m_camera = new PerspectiveCamera(67, Gdx.graphics->getWidth(), Gdx.graphics->getHeight());
}

void Renderer::render(Application* app, Simulation* simulation) 
{
	GL10* gl = app->getGraphics()->getGL10();
	gl->glClear(GL10::GDX_GL_COLOR_BUFFER_BIT | GL10::GDX_GL_DEPTH_BUFFER_BIT);
	gl->glViewport(0, 0, app->getGraphics()->getWidth(), app->getGraphics()->getHeight());

	renderBackground(gl);

	gl->glDisable(GL10::GDX_GL_DITHER);
	gl->glEnable(GL10::GDX_GL_DEPTH_TEST);
	gl->glEnable(GL10::GDX_GL_CULL_FACE);

	setProjectionAndCamera(app->getGraphics(), simulation->ship, app);
	setLighting(gl);

	gl->glEnable(GL10::GDX_GL_TEXTURE_2D);

	renderShip(gl, simulation->ship, app);
	renderInvaders(gl, simulation->invaders);

	gl->glDisable(GL10::GDX_GL_TEXTURE_2D);
	renderBlocks(gl, simulation->blocks);

	gl->glDisable(GL10::GDX_GL_LIGHTING);
	renderShots(gl, simulation->shots);
	if(simulation->shipShot)
		renderShot(gl, *simulation->shipShot);

	gl->glEnable(GL10::GDX_GL_TEXTURE_2D);
	renderExplosions(gl, simulation->explosions);

	gl->glDisable(GL10::GDX_GL_CULL_FACE);
	gl->glDisable(GL10::GDX_GL_DEPTH_TEST);

	m_spriteBatch->setProjectionMatrix(m_viewMatrix);
	m_spriteBatch->setTransformMatrix(m_transformMatrix);
	m_spriteBatch->begin();
	if (simulation->ship.lives != m_lastLives || simulation->score != m_lastScore || simulation->wave != m_lastWave) 
	{
		std::stringstream statusMessage;
		statusMessage << "lives: " << simulation->ship.lives << " wave: " << simulation->wave << " score: " << simulation->score;

		m_status = statusMessage.str();
		m_lastLives = simulation->ship.lives;
		m_lastScore = simulation->score;
		m_lastWave = simulation->wave;
	}
	m_spriteBatch->enableBlending();
	m_spriteBatch->setBlendFunction(GL10::GDX_GL_ONE, GL10::GDX_GL_ONE_MINUS_SRC_ALPHA);
	m_font->draw(m_spriteBatch, m_status, 0, 320);
	m_spriteBatch->end();

	m_invaderAngle += app->getGraphics()->getDeltaTime() * 90;
	if (m_invaderAngle > 360) 
		m_invaderAngle -= 360;
}

void Renderer::renderBackground(GL10* gl) 
{
	m_viewMatrix.setToOrtho2D(0, 0, 400, 320);
	m_spriteBatch->setProjectionMatrix(m_viewMatrix);
	m_spriteBatch->setTransformMatrix(m_transformMatrix);
	m_spriteBatch->begin();
	m_spriteBatch->disableBlending();
	m_spriteBatch->setColor(Color::WHITE);
	m_spriteBatch->draw(m_backgroundTexture, 0, 0, 480, 320, 0, 0, 512, 512, false, false);
	m_spriteBatch->end();
}



void Renderer::setProjectionAndCamera(Graphics* graphics, const Ship& ship, Application* app) 
{
	m_camera->position.set(ship.position.x, 6, 2);
	m_camera->direction.set(ship.position.x, 0, -4).sub(m_camera->position).nor();
	m_camera->update();
	m_camera->apply(Gdx.gl10);
}



void Renderer::setLighting (GL10* gl) 
{
	static float direction[] = {1, 0.5f, 0, 0};
	gl->glEnable(GL10::GDX_GL_LIGHTING);
	gl->glEnable(GL10::GDX_GL_LIGHT0);
	gl->glLightfv(GL10::GDX_GL_LIGHT0, GL10::GDX_GL_POSITION, direction, 0);
	gl->glEnable(GL10::GDX_GL_COLOR_MATERIAL);
}

void Renderer::renderShip(GL10* gl, const Ship& ship, Application* app) 
{
	if (ship.isExploding) 
		return;

	m_shipTexture->bind();
	gl->glPushMatrix();
	gl->glTranslatef(ship.position.x, ship.position.y, ship.position.z);
	gl->glRotatef(45 * (-app->getInput()->getAccelerometerY() / 5), 0, 0, 1);
	gl->glRotatef(180, 0, 1, 0);
	m_shipMesh->render(GL10::GDX_GL_TRIANGLES);
	gl->glPopMatrix();
}

void Renderer::renderInvaders(GL10* gl, const Simulation::Invaders& invaders) 
{
	m_invaderTexture->bind();
	for(Simulation::Invaders::const_iterator invader = invaders.begin(); invader != invaders.end(); invader++)
	{
		gl->glPushMatrix();
		gl->glTranslatef(invader->position.x, invader->position.y, invader->position.z);
		gl->glRotatef(m_invaderAngle, 0, 1, 0);
		m_invaderMesh->render(GL10::GDX_GL_TRIANGLES);
		gl->glPopMatrix();
	}
}

void Renderer::renderBlocks(GL10* gl, const Simulation::Blocks& blocks) 
{
	gl->glEnable(GL10::GDX_GL_BLEND);
	gl->glBlendFunc(GL10::GDX_GL_SRC_ALPHA, GL10::GDX_GL_ONE_MINUS_SRC_ALPHA);
	gl->glColor4f(0.2f, 0.2f, 1, 0.7f);
	for(Simulation::Blocks::const_iterator block = blocks.begin(); block != blocks.end(); block++)
	{
		gl->glPushMatrix();
		gl->glTranslatef(block->position.x, block->position.y, block->position.z);
		m_blockMesh->render(GL10::GDX_GL_TRIANGLES);
		gl->glPopMatrix();
	}
	gl->glColor4f(1, 1, 1, 1);
	gl->glDisable(GL10::GDX_GL_BLEND);
}

void Renderer::renderShots(GL10* gl, const Simulation::Shots& shots) 
{
	gl->glColor4f(1, 1, 0, 1);
	for(Simulation::Shots::const_iterator shot = shots.begin(); shot != shots.end(); shot++)
	{
		renderShot(gl, *shot);
	}
	gl->glColor4f(1, 1, 1, 1);
}

void Renderer::renderShot(GL10* gl, const Shot& shot) 
{
	gl->glPushMatrix();
	gl->glTranslatef(shot.position.x, shot.position.y, shot.position.z);
	m_shotMesh->render(GL10::GDX_GL_TRIANGLES);
	gl->glPopMatrix();
}

void Renderer::renderExplosions(GL10* gl, const Simulation::Explosions& explosions) 
{
	gl->glEnable(GL10::GDX_GL_BLEND);
	gl->glBlendFunc(GL10::GDX_GL_SRC_ALPHA, GL10::GDX_GL_ONE_MINUS_SRC_ALPHA);
	m_explosionTexture->bind();
	for(Simulation::Explosions::const_iterator explosion = explosions.begin(); explosion != explosions.end(); explosion++)
	{
		gl->glPushMatrix();
		gl->glTranslatef(explosion->position.x, explosion->position.y, explosion->position.z);
		m_explosionMesh->render(GL10::GDX_GL_TRIANGLE_FAN, (int)((explosion->aliveTime / Explosion::EXPLOSION_LIVE_TIME) * 15) * 4, 4);
		gl->glPopMatrix();
	}
	gl->glDisable(GL10::GDX_GL_BLEND);
}

void Renderer::dispose () 
{
	m_spriteBatch->dispose();
	m_shipTexture->dispose();
	m_invaderTexture->dispose();
	m_backgroundTexture->dispose();
	m_explosionTexture->dispose();
	m_font->dispose();
	m_explosionMesh->dispose();
	m_shipMesh->dispose();
	m_invaderMesh->dispose();
	m_shotMesh->dispose();
	m_blockMesh->dispose();
}

