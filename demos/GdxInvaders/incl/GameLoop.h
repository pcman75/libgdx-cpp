/*
 * Copyright 2010 Mario Zechner (contact@badlogicgames.com), Nathan Sweet (admin@esotericsoftware.com)
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the
 * License. You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS"
 * BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language
 * governing permissions and limitations under the License.
 */

package com.badlogic.gdxinvaders.screens;

import com.badlogic.gdx.Application;
import com.badlogic.gdx.Files.FileType;
import com.badlogic.gdx.Input;
import com.badlogic.gdx.Input.Keys;
import com.badlogic.gdx.audio.Sound;
import com.badlogic.gdx.graphics.GL10;
import com.badlogic.gdxinvaders.Renderer;
import com.badlogic.gdxinvaders.simulation.Simulation;
import com.badlogic.gdxinvaders.simulation.SimulationListener;

public class GameLoop implements Screen, SimulationListener
{
	/** the simulation **/
	private final Simulation simulation;
	/** the renderer **/
	private final Renderer renderer;
	/** explosion sound **/
	private final Sound explosion;
	/** shot sound **/
	private final Sound shot;

	public GameLoop (Application app)
	{
		simulation = new Simulation();
		simulation.listener = this;
		renderer = new Renderer(app);
		explosion = app.getAudio().newSound(app.getFiles().getFileHandle("data/explosion.ogg", FileType.Internal));
		shot = app.getAudio().newSound(app.getFiles().getFileHandle("data/shot.ogg", FileType.Internal));
	}

	@Override
	public void dispose ()
	{
		renderer.dispose();
		shot.dispose();
		explosion.dispose();
	}

	@Override
	public boolean isDone ()
	{
		return simulation.ship.lives == 0;
	}

	@Override
	public void render (Application app)
	{
		app.getGraphics().getGL10().glClear(GL10.GL_COLOR_BUFFER_BIT | GL10.GL_DEPTH_BUFFER_BIT);
		renderer.render(app, simulation);
	}

	@Override
	public void update (Application app)
	{
		simulation.update(app.getGraphics().getDeltaTime());

		Input input = app.getInput();
		if (input.getAccelerometerY() < 0)
			simulation.moveShipLeft(app.getGraphics().getDeltaTime(), Math.abs(input.getAccelerometerY()) / 10);
		else
			simulation.moveShipRight(app.getGraphics().getDeltaTime(), Math.abs(input.getAccelerometerY()) / 10);

		if (input.isKeyPressed(Keys.DPAD_LEFT)) simulation.moveShipLeft(app.getGraphics().getDeltaTime(), 0.5f);
		if (input.isKeyPressed(Keys.DPAD_RIGHT)) simulation.moveShipRight(app.getGraphics().getDeltaTime(), 0.5f);

		if (input.isTouched() || input.isKeyPressed(Keys.SPACE)) simulation.shot();
	}

	@Override
	public void explosion ()
	{
		explosion.play();
	}

	@Override
	public void shot ()
	{
		shot.play();
	}
}
