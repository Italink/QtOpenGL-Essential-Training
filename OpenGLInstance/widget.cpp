#include "widget.h"

Widget::Widget(QWidget *parent)
    : QOpenGLWidget(parent)
{
}

Widget::~Widget()
{
}

void Widget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0,0,0,1);

    float quadVertices[] = {
        // 位置          // 颜色
        -0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
         0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
        -0.05f, -0.05f,  0.0f, 0.0f, 1.0f,

        -0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
         0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
         0.05f,  0.05f,  0.0f, 1.0f, 1.0f
    };
    VAO.create();
    VAO.bind();
    VBO.create();
    VBO.bind();
    VBO.allocate(quadVertices,sizeof (quadVertices));

    shaderProgram.create();
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,":/gl.vert");
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,":/gl.frag");
    shaderProgram.link();
    shaderProgram.enableAttributeArray(0);
    shaderProgram.enableAttributeArray(1);
    shaderProgram.setAttributeBuffer(0,GL_FLOAT,0,2,5*sizeof (float));
    shaderProgram.setAttributeBuffer(1,GL_FLOAT,2*sizeof (float),3,5*sizeof (float));

    shaderProgram.enableAttributeArray(2);
    QVector2D translations[100];
    int index = 0;
    float offset = 0.1f;
    for(int y = -10; y < 10; y += 2)
    {
        for(int x = -10; x < 10; x += 2)
        {
            QVector2D translation;
            translation.setX( (float)x / 10.0f + offset);
            translation.setY( (float)y / 10.0f + offset);
            translations[index++] = translation;
        }
    }
    instanceVBO.create();
    instanceVBO.bind();
    instanceVBO.allocate(translations,100*sizeof (QVector2D));
    shaderProgram.setAttributeBuffer(2,GL_FLOAT,0,2,2*sizeof (float));
    instanceVBO.release();
    glVertexAttribDivisor(2,1);

}

void Widget::paintGL()
{
    VAO.bind();
    shaderProgram.bind();
    glDrawArraysInstanced(GL_TRIANGLES,0,6,100);
}

void Widget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
}

