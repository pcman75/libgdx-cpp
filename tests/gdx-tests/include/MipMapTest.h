/*******************************************************************************
 * Copyright 2011 See AUTHORS file.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ******************************************************************************/
#pragma once

class MipMapTest :
	public GdxTest
{
public:
	
	PerspectiveCamera camera;
	PerspectiveCamController controller;
	Mesh mesh;
	Texture textureHW;
	Texture textureSW;
	Texture currTexture;
	ShaderProgram shader;
	Stage ui;
	InputMultiplexer multiplexer;
	SelectBox minFilter;
	SelectBox magFilter;
	CheckBox hwMipMap;

	bool needsGL20()
	{
		return true;
	}
	void create()
	{
		camera = new PerspectiveCamera(67, Gdx.graphics.getWidth(), Gdx.graphics.getHeight());
		camera.position.set(0, 1.5f, 1.5f);
		camera.lookAt(0, 0, 0);
		camera.update();
		controller = new PerspectiveCamController(camera);

		mesh = new Mesh(true, 4, 4, new VertexAttribute(Usage.Position, 3, ShaderProgram.POSITION_ATTRIBUTE), new VertexAttribute(
		                    Usage.TextureCoordinates, 2, ShaderProgram.TEXCOORD_ATTRIBUTE));
		mesh.setVertices(new float[] {-1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, -1, 1, 0, -1, 0, -1, 0, 0,});
		mesh.setIndices(new short[] {0, 1, 2, 3});

		shader = new ShaderProgram(Gdx.files.internal("data/shaders/flattex-vert.glsl").readString(), Gdx.files.internal(
		                               "data/shaders/flattex-frag.glsl").readString());
		if(!shader.isCompiled()) throw GdxRuntimeException("shader error: " + shader.getLog());

		textureHW = new Texture(Gdx.files.internal("data/badlogic.jpg"), Format.RGB565, true);
		MipMapGenerator.setUseHardwareMipMap(false);
		textureSW = new Texture(Gdx.files.internal("data/badlogic.jpg"), Format.RGB565, true);
		currTexture = textureHW;

		createUI();

		multiplexer = new InputMultiplexer();
		Gdx.input.setInputProcessor(multiplexer);
		multiplexer.addProcessor(ui);
		multiplexer.addProcessor(controller);
	}

	private void createUI()
	{
		Skin skin = new Skin(Gdx.files.internal("data/uiskin.json"), Gdx.files.internal("data/uiskin.png"));
		ui = new Stage(Gdx.graphics.getWidth(), Gdx.graphics.getHeight(), false);

		String[] filters = new String[TextureFilter.values().length];
		int idx = 0;
		for(TextureFilter filter : TextureFilter.values())
		{
			filters[idx++] = filter.toString();
		}
		hwMipMap = new CheckBox("Hardware Mips", skin.getStyle(CheckBoxStyle.class), "hardware");
		minFilter = new SelectBox(filters, skin.getStyle(SelectBoxStyle.class), "minfilter");
		magFilter = new SelectBox(new String[] {"Nearest", "Linear"}, skin.getStyle(SelectBoxStyle.class), "magfilter");

		Table table = new Table();
		table.width = ui.width();
		table.height = 30;
		table.y = ui.height() - 30;
		table.add(hwMipMap).spaceRight(5);
		table.add(new Label("Min Filter", skin.getStyle(LabelStyle.class))).spaceRight(5);
		table.add(minFilter).spaceRight(5);
		table.add(new Label("Mag Filter", skin.getStyle(LabelStyle.class))).spaceRight(5);
		table.add(magFilter);

		ui.addActor(table);
	}

	@Override
	public void render()
	{
		Gdx.gl.glClear(GL10.GL_COLOR_BUFFER_BIT);
		Gdx.gl.glEnable(GL10.GL_TEXTURE_2D);

		camera.update();

		currTexture = hwMipMap.isChecked() ? textureHW : textureSW;
		currTexture.bind();
		currTexture.setFilter(TextureFilter.valueOf(minFilter.getSelection()), TextureFilter.valueOf(magFilter.getSelection()));

		shader.begin();
		shader.setUniformMatrix("u_projTrans", camera.combined);
		shader.setUniformi("s_texture", 0);
		mesh.render(shader, GL10.GL_TRIANGLE_FAN);
		shader.end();

		ui.draw();
	}
}
