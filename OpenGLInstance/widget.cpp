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



    float offset = 0.1f;
    QVector<QVector4D> vec;
    for(int y = -10; y < 10; y += 2)
    {
        for(int x = -10; x < 10; x += 2)
        {
            QMatrix4x4 mat;
            mat.translate(x/ 10.0f + offset,y / 10.0f + offset);
            mat.rotate((x+y)*10,QVector3D(0,0,1));
            vec.push_back(mat.column(0));
            vec.push_back(mat.column(1));
            vec.push_back(mat.column(2));
            vec.push_back(mat.column(3));
        }
    }

    instanceVBO.create();
    instanceVBO.bind();
    instanceVBO.allocate(vec.data(),vec.size()*sizeof (QVector4D));
    shaderProgram.enableAttributeArray(2);
    shaderProgram.setAttributeBuffer(2,GL_FLOAT,0,4,4*sizeof (QVector4D));
    glVertexAttribDivisor(2,1);

    shaderProgram.enableAttributeArray(3);
    shaderProgram.setAttributeBuffer(3,GL_FLOAT,1*sizeof (QVector4D),4,4*sizeof (QVector4D));
    glVertexAttribDivisor(3,1);

    shaderProgram.enableAttributeArray(4);
    shaderProgram.setAttributeBuffer(4,GL_FLOAT,2*sizeof (QVector4D),4,4*sizeof (QVector4D));
    glVertexAttribDivisor(4,1);

    shaderProgram.enableAttributeArray(5);
    shaderProgram.setAttributeBuffer(5,GL_FLOAT,3*sizeof (QVector4D),4,4*sizeof (QVector4D));
    glVertexAttribDivisor(5,1);

    instanceVBO.release();

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

