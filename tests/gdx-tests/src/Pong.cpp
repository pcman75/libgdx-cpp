#include "stdafx.h"
#include "Pong.h"

Pong::Pong()
{
	leftScore = 0;
	rightScore = 0;
	leftPaddleMulti = 1;
	ballSpeed = BALL_SPEED;
}

/** Here we setup all the resources. A MeshRenderer for the paddles which we use for both, a MeshRenderer for the ball and a
* Text for rendering the score. */
void Pong::create()
{
	setupGraphics();
	setupGame();
}

/** This method sets up all the graphics related stuff like the Meshes, the camera and the Font */
void Pong::setupGraphics()
{
	//
	// We first construct the paddle mesh which consists of
	// four 2D vertices forming a vertically elongated rectangle
	// constructed around the origin. We don't use colors, normals
	// texture coordinates or indices. Note that we use a fixed
	// point Mesh here. The paddle has dimensions (10, 60).
	//
	paddleMesh = new Mesh(true, VertexAttribute(VertexAttributes::Position, 2, "a_position"));
	float vertices[] = {-5, -30, 5, -30, 5, 30, -5, 30};
	paddleMesh->setVertices(vertices, 8);

	//
	// We do the same for the ball which has dimensions (10,10)
	//
	ballMesh = new Mesh(true, VertexAttribute(VertexAttributes::Position, 2, "a_position"));
	float ballVerts[] = {-5, -5, 5, -5, 5, 5, -5, 5};
	ballMesh->setVertices(ballVerts, 8);

	//
	// We construct a new font from a system font. We assume
	// Arial is installed on both the desktop and Android.
	//
	// font = Gdx.graphics.newFont("Arial", 30, FontStyle.Plain);
	score = "0 : 0";
	spriteBatch = new SpriteBatch();

	//
	// Finally we construct an {@link OrthographicCamera} which
	// will scale our scene to 480x320 pixels no matter what the
	// real screen dimensions. This will of course squish the scene
	// on devices like the Droid. The screen center will be at (0,0)
	// so that's the reference frame for our scene.
	//
	camera = new OrthographicCamera(480, 320);
}

/** This sets up the game data like the initial paddle positions and the ball position and direction. */
void Pong::setupGame()
{
	leftPaddle.set(-200, 20);
	rightPaddle.set(200, 0);
	ball.set(0, 0);
	ballDirection.set(-1, 0);
}


void Pong::render()
{
	// we update the game state so things move.
	updateGame();

	// First we clear the screen
	GL10* gl = Gdx.graphics->getGL10();
	gl->glViewport(0, 0, Gdx.graphics->getWidth(), Gdx.graphics->getHeight());
	gl->glClear(GL10::GDX_GL_COLOR_BUFFER_BIT);

	// Next we update the camera and set the camera matrix
	camera->update();
	camera->apply(Gdx.gl10);

	// Now we render the ball, we remember that we
	// Defined 4 vertices so we use a triangle fan
	// We also push and pop the matrix. This is not really
	// necessary as the model view matrix doesn't contain
	// anything at this point.
	gl->glPushMatrix();
	gl->glTranslatef(ball.x, ball.y, 0);
	ballMesh->render(GL10::GDX_GL_TRIANGLE_FAN);
	gl->glPopMatrix();

	// Rendering the two paddles works analogous
	gl->glPushMatrix();
	gl->glTranslatef(leftPaddle.x, leftPaddle.y, 0);
	paddleMesh->render(GL10::GDX_GL_TRIANGLE_FAN);
	gl->glPopMatrix();

	gl->glPushMatrix();
	gl->glTranslatef(rightPaddle.x, rightPaddle.y, 0);
	paddleMesh->render(GL10::GDX_GL_TRIANGLE_FAN);
	gl->glPopMatrix();

	// Finally we render the text centered at the top
	// of the screen. We use the text bounds for this.
	// For text to be transparent we have to enable blending and texturing.
	// We could setup blending once but i'm lazy :)
	spriteBatch->begin();
	// spriteBatch.drawText(font, score, Gdx.graphics.getWidth() / 2 - font.getStringWidth(score) / 2, Gdx.graphics.getHeight()
	// - font.getLineHeight(), Color.WHITE);
	spriteBatch->end();
}

/** Updates the game state, moves the ball, checks for collisions or whether the ball has left the playfield. */
void Pong::updateGame()
{
	// the delta time so we can do frame independent time based movement
	float deltaTime = Gdx.graphics->getDeltaTime();

	// move the ball with a velocity of 50 pixels
	// per second. The ballDirection is a unit vector
	// we simply scale by the velocity.
	ball.add(ballSpeed * ballDirection.x * deltaTime, ballSpeed * ballDirection.y * deltaTime);

	// Next we check wheter the ball left the field to
	// the left or to the right and update the score
	if(ball.x < -240)
	{
		ball.set(0, 0); // reset to center
		ballSpeed = BALL_SPEED; // reset the ball speed
		ballDirection.set(MathUtils::randomFloat() + 0.1f, MathUtils::randomFloat()).nor(); // new ball direction, must be unit length
		rightScore++; // right paddle scored!
		score = leftScore + " : " + rightScore;
		// we set the left paddle multiplicator here which governs
		// how fast the left paddle can follow the ball.
		leftPaddleMulti = min(1, MathUtils::randomFloat() + 0.3f);
	}

	if(ball.x > 240)
	{
		ball.set(0, 0); // reset to center
		ballSpeed = BALL_SPEED; // reset the ball speed
		ballDirection.set(MathUtils::randomFloat() + 0.1f, MathUtils::randomFloat()).nor(); // new ball direction, must be unit length
		leftScore++; // left paddle scored!
		score = leftScore + " : " + rightScore;
		// we set the left paddle multiplicator here which governs
		// how fast the left paddle can follow the ball.
		leftPaddleMulti = min(1, MathUtils::randomFloat() + 0.3f);
	}

	// if the ball is hitting the bottom or top we
	// reverse its direction in y so that it bounces
	if(ball.y > 160)
	{
		ballDirection.y = -ballDirection.y;
		ball.y = 160;
	}

	if(ball.y < -160)
	{
		ballDirection.y = -ballDirection.y;
		ball.y = -160;
	}

	// if the ball is heading towards the right paddle and
	// has hit it we reflect it
	if(ballDirection.x > 0 && ball.x > rightPaddle.x - 5 && ball.x < rightPaddle.x + 5 && ball.y > rightPaddle.y - 30
		&& ball.y < rightPaddle.y + 30)
	{
		ball.x = rightPaddle.x - 6; // set the position of a little so we don't get to this code in the next frame
		ballDirection.x = -ballDirection.x;
		float sign = MathUtils::sign(ball.y - rightPaddle.y);
		ballDirection.y = sign * fabs(ball.y - rightPaddle.y) / 30; // reflect it depending on where the paddle was
		// hit
		ballDirection.nor();
		ballSpeed += 10; // and faster!
		if(ballSpeed > 300) ballSpeed = 300;
	}

	// and the same for the left paddle
	if(ballDirection.x < 0 && ball.x < leftPaddle.x + 5 && ball.x > leftPaddle.x - 5 && ball.y > leftPaddle.y - 30
		&& ball.y < leftPaddle.y + 30)
	{
		ball.x = leftPaddle.x + 6; // set the position of a little so we don't get to this code in the next frame
		ballDirection.x = -ballDirection.x;
		float sign = MathUtils::sign(ball.y - leftPaddle.y);
		ballDirection.y = sign * fabs(ball.y - leftPaddle.y) / 30; // reflect it depending on where the paddle was hit
		ballDirection.nor();
		ballSpeed += 10; // and faster!
		if(ballSpeed > 300) ballSpeed = 300;
		// we set the left paddle multiplicator here which governs
		// how fast the left paddle can follow the ball.
		leftPaddleMulti = min(1, MathUtils::randomFloat() + 0.3f);
	}

	
	// Has the user touched the screen? then position the paddle
	if(Gdx.input->isTouched())
	{
		// get the touch coordinates and translate them
		// to the game coordinate system.
		float touchX = 480 * (Gdx.input->getX() / (float)Gdx.graphics->getWidth() - 0.5f);
		float touchY = 320 * (0.5f - Gdx.input->getY() / (float)Gdx.graphics->getHeight());

		if(touchX > rightPaddle.x)
			rightPaddle.y = touchY;
	}
	
	// very very simple ai. moves when the ball is heading towards
	// the left paddle
	if(ballDirection.x < 0)
	{
		float dir = MathUtils::sign(ball.y - leftPaddle.y);
		leftPaddle.y += dir * deltaTime * (ballSpeed * leftPaddleMulti);
		if(dir > 0 && leftPaddle.y > ball.y) leftPaddle.y = ball.y;
		if(dir < 0 && leftPaddle.y < ball.y) leftPaddle.y = ball.y;
	}
}

