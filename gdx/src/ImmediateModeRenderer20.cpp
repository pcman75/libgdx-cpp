#include "stdafx.h"
#include "ImmediateModeRenderer20.h"
#include "Color.h"

ImmediateModeRenderer20::ImmediateModeRenderer20(bool hasNormals, bool hasColors, int numTexCoords)
{
	init(5000, hasNormals, hasColors, m_numTexCoords);
}

ImmediateModeRenderer20::ImmediateModeRenderer20(int maxVertices, bool hasNormals, bool hasColors, int numTexCoords)
{
	init(maxVertices, hasNormals, hasColors, numTexCoords);
}


void ImmediateModeRenderer20::begin(const Matrix4& projModelView, int primitiveType)
{
	m_customShader = NULL;
	m_projModelView.set(projModelView);
	m_primitiveType = primitiveType;
}

void ImmediateModeRenderer20::begin(ShaderProgram* shader, int primitiveType)
{
	m_customShader = shader;
	m_primitiveType = primitiveType;
}

void ImmediateModeRenderer20::color(float r, float g, float b, float a)
{
	m_vertices[m_vertexIdx + m_colorOffset] = Color::toFloatBits(r, g, b, a);
}

void ImmediateModeRenderer20::texCoord(float u, float v)
{
	int idx = m_vertexIdx + m_texCoordOffset;
	m_vertices[idx] = u;
	m_vertices[idx + 1] = v;
	m_numSetTexCoords += 2;
}

void ImmediateModeRenderer20::normal(float x, float y, float z)
{
	int idx = m_vertexIdx + m_normalOffset;
	m_vertices[idx] = x;
	m_vertices[idx + 1] = y;
	m_vertices[idx + 2] = z;
}

void ImmediateModeRenderer20::vertex(float x, float y, float z)
{
	int idx = m_vertexIdx;
	m_vertices[idx] = x;
	m_vertices[idx + 1] = y;
	m_vertices[idx + 2] = z;

	m_numSetTexCoords = 0;
	m_vertexIdx += m_vertexSize;
	m_numVertices++;
}

void ImmediateModeRenderer20::end()
{
	if(m_customShader)
	{
		m_customShader->begin();
		m_mesh->setVertices(m_vertices, m_vertexIdx);
		m_mesh->render(m_customShader, m_primitiveType);
		m_customShader->end();
	}
	else
	{
		m_defaultShader->begin();
		m_defaultShader->setUniformMatrix("u_projModelView", m_projModelView);
		for(int i = 0; i < m_numTexCoords; i++)
		{
			std::stringstream name;
			name << "u_sampler" << i;
			m_defaultShader->setUniformi(name.str(), i);
		}
		m_mesh->setVertices(m_vertices, m_vertexIdx);
		m_mesh->render(m_defaultShader, m_primitiveType);
		m_defaultShader->end();
	}

	m_numSetTexCoords = 0;
	m_vertexIdx = 0;
	m_numVertices = 0;
}

int ImmediateModeRenderer20::getNumVertices()
{
	return m_numVertices;
}

int ImmediateModeRenderer20::getMaxVertices()
{
	return m_maxVertices;
}

ImmediateModeRenderer20::~ImmediateModeRenderer20()
{
	if(m_defaultShader) 
	{
		m_defaultShader->dispose();
		delete m_defaultShader;
	}
	m_mesh->dispose();
	delete m_mesh; 
}

void ImmediateModeRenderer20::init(int maxVertices, bool hasNormals, bool hasColors, int numTexCoords)
{
	m_maxVertices = maxVertices;

	std::vector<VertexAttribute> attribs;
	buildVertexAttributes(hasNormals, hasColors, numTexCoords, attribs);
	
	m_mesh = new Mesh(false, &attribs[0], attribs.size());
	std::string vertexShader;
	createVertexShader(hasNormals, hasColors, numTexCoords, vertexShader);
	std::string fragmentShader;
	createFragmentShader(hasNormals, hasColors, numTexCoords, fragmentShader);

	m_defaultShader = new ShaderProgram(vertexShader, fragmentShader);
	if(!m_defaultShader->isCompiled())
		throw new GdxRuntimeException("Couldn't compile immediate mode default shader!\n" + m_defaultShader->getLog());

	m_numTexCoords = numTexCoords;
	m_vertices = new float[maxVertices * (m_mesh->getVertexAttributes().vertexSize() / 4)];
	m_vertexSize = m_mesh->getVertexAttributes().vertexSize() / 4;

	VertexAttribute attrib;
	
	if(m_mesh->getVertexAttribute(VertexAttributes::Normal, attrib))
	{
		m_normalOffset = attrib.offset / 4;
	}
	else
	{
		m_normalOffset = 0;
	}
	
	if(m_mesh->getVertexAttribute(VertexAttributes::ColorPacked, attrib))
	{
		m_colorOffset = attrib.offset / 4;
	}
	else
	{
		m_colorOffset = 0;
	}

	if(m_mesh->getVertexAttribute(VertexAttributes::TextureCoordinates, attrib))
	{
		m_texCoordOffset = attrib.offset / 4;
	}
	else
	{
		m_texCoordOffset = 0;
	}
}

void ImmediateModeRenderer20::buildVertexAttributes(bool hasNormals, bool hasColor, int numTexCoords, std::vector<VertexAttribute>& attribs)
{
	attribs.push_back(VertexAttribute(VertexAttributes::Position, 3, ShaderProgram::POSITION_ATTRIBUTE));
	if(hasNormals) 
		attribs.push_back(VertexAttribute(VertexAttributes::Normal, 3, ShaderProgram::NORMAL_ATTRIBUTE));
	if(hasColor) 
		attribs.push_back(VertexAttribute(VertexAttributes::ColorPacked, 4, ShaderProgram::COLOR_ATTRIBUTE));
	for(int i = 0; i < numTexCoords; i++)
	{
		attribs.push_back(VertexAttribute(VertexAttributes::TextureCoordinates, 2, ShaderProgram::TEXCOORD_ATTRIBUTE + i));
	}

}

void ImmediateModeRenderer20::createVertexShader(bool hasNormals, bool hasColors, int numTexCoords, std::string& shader)
{
	std::stringstream shaderBuilder;
	shaderBuilder << "attribute vec4 " << ShaderProgram::POSITION_ATTRIBUTE << ";\n";
	if(hasNormals)
		shaderBuilder << "attribute vec3 " << ShaderProgram::NORMAL_ATTRIBUTE << ";\n";
	if(hasColors)
		shaderBuilder << "attribute vec4 " << ShaderProgram::COLOR_ATTRIBUTE << ";\n";

	for(int i = 0; i < numTexCoords; i++)
	{
		shaderBuilder << "attribute vec2 " << ShaderProgram::TEXCOORD_ATTRIBUTE << i << ";\n";
	}

	shaderBuilder << "uniform mat4 u_projModelView;\n";
	if(hasColors)
		shaderBuilder << "varying vec4 v_col;\n";

	for(int i = 0; i < numTexCoords; i++)
	{
		shaderBuilder << "varying vec2 v_tex" << i << ";\n";
	}

	shaderBuilder << "void main() {\n" << "   gl_Position = u_projModelView * " << ShaderProgram::POSITION_ATTRIBUTE << ";\n";
	if(hasColors)
		shaderBuilder << "   v_col = " << ShaderProgram::COLOR_ATTRIBUTE << ";\n";

	for(int i = 0; i < numTexCoords; i++)
	{
		shaderBuilder << "   v_tex" << i << " = " << ShaderProgram::TEXCOORD_ATTRIBUTE << i << ";\n";
	}

	shaderBuilder << "}\n";

	shader = shaderBuilder.str();
}

void ImmediateModeRenderer20::createFragmentShader(bool hasNormals, bool hasColors, int numTexCoords, std::string& shader)
{
	std::stringstream shaderBuilder;
	shaderBuilder << "#ifdef GL_ES\n" << "precision highp float;\n" << "#endif\n";

	if(hasColors) 
		shaderBuilder << "varying vec4 v_col;\n";
	for(int i = 0; i < numTexCoords; i++)
	{
		shaderBuilder << "varying vec2 v_tex" << i << ";\n";
		shaderBuilder << "uniform sampler2D u_sampler" << i << ";\n";
	}

	shaderBuilder << "void main() {\n" << "   gl_FragColor = ";
	if(hasColors)
		shaderBuilder << "v_col";
	else
		shaderBuilder << "vec4(1, 1, 1, 1)";

	if(numTexCoords > 0) 
		shaderBuilder << " * ";

	for(int i = 0; i < numTexCoords; i++)
	{
		if(i == numTexCoords - 1)
		{
			shaderBuilder << " texture2D(u_sampler" << i << ",  v_tex" << i << ")";
		}
		else
		{
			shaderBuilder << " texture2D(u_sampler" << i << ",  v_tex" << i << ") *";
		}
	}

	shaderBuilder << ";\n}";

	shader = shaderBuilder.str();
}

