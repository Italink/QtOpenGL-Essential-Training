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
    glClearColor(0.0f,0.5f,0.9f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    shaderProgram.create();
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,":/gl.vert");
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,":/gl.frag");
    shaderProgram.link();
    shaderProgram.enableAttributeArray("pos");
}

void Widget::paintGL()
{
    shaderProgram.bind();
    GLfloat vertices[]={
         0.5f,  0.5f, 0.0f,   // 右上角
         0.5f, -0.5f, 0.0f,   // 右下角
        -0.5f,  0.5f, 0.0f,   // 左上角
        -0.5f, -0.5f, 0.0f,  // 左下角
    };
    shaderProgram.setAttributeArray("pos",vertices,3);
    glDrawArrays(GL_TRIANGLE_STRIP,0,4);

}

void Widget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
}

