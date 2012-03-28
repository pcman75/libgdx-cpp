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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, app->getGraphics()->getWidth(), app->getGraphics()->getHeight());

	renderBackground();

	glDisable(GL_DITHER);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	setProjectionAndCamera(app->getGraphics(), simulation->ship, app);
	setLighting();

	glEnable(GL_TEXTURE_2D);

	renderShip(simulation->ship, app);
	renderInvaders(simulation->invaders);

	glDisable(GL_TEXTURE_2D);
	renderBlocks(simulation->blocks);

	glDisable(GL_LIGHTING);
	renderShots(simulation->shots);
	if(simulation->shipShot)
		renderShot(*simulation->shipShot);

	glEnable(GL_TEXTURE_2D);
	renderExplosions(simulation->explosions);

	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);

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
	m_spriteBatch->setBlendFunction(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	m_font->draw(m_spriteBatch, m_status, 0, 320);
	m_spriteBatch->end();

	m_invaderAngle += app->getGraphics()->getDeltaTime() * 90;
	if (m_invaderAngle > 360) 
		m_invaderAngle -= 360;
}

void Renderer::renderBackground() 
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
	m_camera->apply();
}



void Renderer::setLighting() 
{
	static float direction[] = {1, 0.5f, 0, 0};
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, direction);
	glEnable(GL_COLOR_MATERIAL);
}

void Renderer::renderShip(const Ship& ship, Application* app) 
{
	if (ship.isExploding) 
		return;

	m_shipTexture->bind();
	glPushMatrix();
	glTranslatef(ship.position.x, ship.position.y, ship.position.z);
	glRotatef(45 * (-app->getInput()->getAccelerometerY() / 5), 0, 0, 1);
	glRotatef(180, 0, 1, 0);
	m_shipMesh->render(GL_TRIANGLES);
	glPopMatrix();
}

void Renderer::renderInvaders(const Simulation::Invaders& invaders) 
{
	m_invaderTexture->bind();
	for(Simulation::Invaders::const_iterator invader = invaders.begin(); invader != invaders.end(); invader++)
	{
		glPushMatrix();
		glTranslatef(invader->position.x, invader->position.y, invader->position.z);
		glRotatef(m_invaderAngle, 0, 1, 0);
		m_invaderMesh->render(GL_TRIANGLES);
		glPopMatrix();
	}
}

void Renderer::renderBlocks(const Simulation::Blocks& blocks) 
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(0.2f, 0.2f, 1, 0.7f);
	for(Simulation::Blocks::const_iterator block = blocks.begin(); block != blocks.end(); block++)
	{
		glPushMatrix();
		glTranslatef(block->position.x, block->position.y, block->position.z);
		m_blockMesh->render(GL_TRIANGLES);
		glPopMatrix();
	}
	glColor4f(1, 1, 1, 1);
	glDisable(GL_BLEND);
}

void Renderer::renderShots(const Simulation::Shots& shots) 
{
	glColor4f(1, 1, 0, 1);
	for(Simulation::Shots::const_iterator shot = shots.begin(); shot != shots.end(); shot++)
	{
		renderShot(*shot);
	}
	glColor4f(1, 1, 1, 1);
}

void Renderer::renderShot(const Shot& shot) 
{
	glPushMatrix();
	glTranslatef(shot.position.x, shot.position.y, shot.position.z);
	m_shotMesh->render(GL_TRIANGLES);
	glPopMatrix();
}

void Renderer::renderExplosions(const Simulation::Explosions& explosions) 
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	m_explosionTexture->bind();
	for(Simulation::Explosions::const_iterator explosion = explosions.begin(); explosion != explosions.end(); explosion++)
	{
		glPushMatrix();
		glTranslatef(explosion->position.x, explosion->position.y, explosion->position.z);
		m_explosionMesh->render(GL_TRIANGLE_FAN, (int)((explosion->aliveTime / Explosion::EXPLOSION_LIVE_TIME) * 15) * 4, 4);
		glPopMatrix();
	}
	glDisable(GL_BLEND);
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

