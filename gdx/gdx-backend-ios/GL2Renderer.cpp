//
//  GL2Renderer.cpp
//  gdx
//
//  Created by Tamas Jano on 02/04/2012.
//  Copyright (c) 2012 Home. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include "Renderer.h"

// Neat trick to include the shader files as a string instead of loading them
// at runtime. 
// NOT to be used in production as the compiler will report weird line numbers
#define STRINGIFY(A) #A
#include "./shaders/Simple.vert"
#include "./shaders/Simple.frag"


    
class GL2Renderer : public Renderer
{
public:
    GL2Renderer();
    void initialize(int width, int height);
    void render() const;
private:
    GLuint buildShader(const char* source, GLenum shaderType) const;
    GLuint buildProgram(const char* vShader, const char* fShader) const;
    void applyOrtho(float maxX, float maxY) const;
    void applyRotation(float degrees) const;
    GLuint m_simpleProgram;
    GLuint m_framebuffer;
    GLuint m_renderbuffer;
    float m_currentAngle;
};

// This is for demo purposes
struct Vertex {
    float Position[2];
    float Color[4];
};

// Define the positions and colors of triangles
const Vertex Vertices[] = {
    {{-0.5, -0.886},    {1, 1, 0.5f, 1}},
    {{0.5, -0.866},     {1, 1, 0.5f, 1}},
    {{0, 1},            {1, 1, 0.5f, 1}},
    {{-0.5, -0.866},    {0.5f, 0.5f, 0.5f, 0.5f}},
    {{0.5, -0.866},     {0.5f, 0.5f, 0.5f, 0.5f}},
    {{0, -0.4f},        {0.5f, 0.5f, 0.5f, 0.5f}},
};


Renderer* createGL2Renderer()
{
    Renderer* renderer = new GL2Renderer();
    renderer->initialize(320, 480);
    return renderer;
};

GL2Renderer::GL2Renderer()
{
    glGenRenderbuffers(1, &m_renderbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, m_renderbuffer);
};

void GL2Renderer::initialize(int width, int height)
{
    // create the framebuffer object and attach the color buffer
    glGenFramebuffers(1, &m_framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, m_renderbuffer);
    
    glViewport(0, 0, width, height);
    
    // The strings are included with that trick - remember?
    m_simpleProgram = buildProgram(SimpleVertexShader, SimpleFragmentShader);
    
    glUseProgram(m_simpleProgram);
    
    // Initialise the projection matrix
    const float maxX = 2;
    const float maxY = 3;
    applyOrtho(maxX, maxY);
};

void GL2Renderer::render() const
{
    glClearColor(0.5f, 0.5f, 0.0f, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    
    applyRotation(m_currentAngle);
    GLuint positionSlot = glGetAttribLocation(m_simpleProgram, "Position");
    GLuint colorSlot = glGetAttribLocation(m_simpleProgram, "SourceColor");
    
    glEnableVertexAttribArray(positionSlot);
    glEnableVertexAttribArray(colorSlot);
    
    GLsizei stride = sizeof(Vertex);
    const GLvoid* pCoords = &Vertices[0].Position[0];
    const GLvoid* pColors = &Vertices[0].Color[0];
    
    glVertexAttribPointer(positionSlot, 2, GL_FLOAT, GL_FALSE, stride, pCoords);
    glVertexAttribPointer(colorSlot, 4, GL_FLOAT, GL_FALSE, stride, pColors);
    
    GLsizei vertexCount = sizeof(Vertices) / sizeof(Vertex);
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    
    glDisableVertexAttribArray(positionSlot);
    glDisableVertexAttribArray(colorSlot);
}

GLuint GL2Renderer::buildProgram(const char *vShaderSource, const char *fShaderSource) const
{
    GLuint vertexShader = buildShader(vShaderSource, GL_VERTEX_SHADER);
    GLuint fragmentShader = buildShader(fShaderSource, GL_FRAGMENT_SHADER);
    
    GLuint programHandle = glCreateProgram();
    glAttachShader(programHandle, vertexShader);
    glAttachShader(programHandle, fragmentShader);
    glLinkProgram(programHandle);
    
    GLint linkSuccess;
    glGetProgramiv(programHandle, GL_LINK_STATUS, &linkSuccess);
    if (linkSuccess == GL_FALSE) {
        std::cout << "buildProgram\n";
        GLchar messages[256];
        glGetProgramInfoLog(programHandle, sizeof(messages), 0, &messages[0]);
        std::cout << messages;
        exit(1);
    }
    
    return programHandle;
}

GLuint GL2Renderer::buildShader(const char *source, GLenum shaderType) const
{
    GLuint shaderHandle = glCreateShader(shaderType);
    glShaderSource(shaderHandle, 1, &source, 0);
    glCompileShader(shaderHandle);
    
    GLint compileSuccess;
    glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &compileSuccess);
    
    if (compileSuccess == GL_FALSE) {
        std::cout << "buildShader\n";
        GLchar messages[256];
        glGetShaderInfoLog(shaderHandle, sizeof(messages), 0, &messages[0]);
        std::cout << messages;
        exit(1);
    }
    
    return shaderHandle;
}

/** 
 *  Because OpenGL ES 2.0 doesn't have glOrtho and glRotate
 *  the methods need to be implemented
 **/
void GL2Renderer::applyOrtho(float maxX, float maxY) const
{
    float a = 1.0f / maxX;
    float b = 1.0f / maxY;
    float ortho[16] = {
        a, 0,   0, 0,
        0, b,   0, 0,
        0, 0,   -1, 0,
        0, 0,   0, 1
    };
    
    GLint projectionUniform = glGetUniformLocation(m_simpleProgram, "Projection");
    glUniformMatrix4fv(projectionUniform, 1, 0, &ortho[0]);
}

void GL2Renderer::applyRotation(float degrees) const
{
    float radians = degrees * 3.14159f / 180.0f;
    float s = std::sin(radians);
    float c = std::cos(radians);
    float zRotation[16] = {
        c, s, 0, 0,
        -s, c, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };
    
    GLint modelviewUniform = glGetUniformLocation(m_simpleProgram, "Modelview");
    glUniformMatrix4fv(modelviewUniform, 1, 0, &zRotation[0]);
}
    