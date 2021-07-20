#include "widget.h"
Widget::Widget(QWidget *parent)
    : QOpenGLWidget(parent)
    , VBO(QOpenGLBuffer::VertexBuffer)
    , EBO(QOpenGLBuffer::IndexBuffer)
{
}

Widget::~Widget()
{
    makeCurrent();
}

void Widget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.0f,0.5f,0.9f,1.0f);
    GL_TEXTURE_2D
    glClear(GL_COLOR_BUFFER_BIT);
    VAO.create();
    VAO.bind();
    VBO.create();
    VBO.bind();
    EBO.create();
    EBO.bind();
    uint elements[]={0,1,3};

    EBO.allocate(elements,sizeof(elements));
    float vertices[]={
         0.5f,  0.5f, 0.0f,  // 右上角
         0.5f, -0.5f, 0.0f,  // 右下角
        -0.5f,  0.5f, 0.0f,  // 左上角
        -0.5f, -0.5f, 0.0f, // 左下角
    };
    VBO.allocate(vertices,sizeof (vertices));

    shaderProgram.create();
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,":/gl.vert");
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,":/gl.frag");
    shaderProgram.link();
    shaderProgram.enableAttributeArray(0);
    shaderProgram.setAttributeBuffer(0,GL_FLOAT,0,3);       //将VBO和EBO的id，以及解析格式存储到VAO中
    VAO.release();
    VBO.release();
    EBO.release();
}

void Widget::paintGL()
{
    shaderProgram.bind();  
    QOpenGLVertexArrayObject::Binder bind(&VAO);
    glDrawElements(GL_TRIANGLES,3,GL_UNSIGNED_INT,nullptr);
}

void Widget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
}

