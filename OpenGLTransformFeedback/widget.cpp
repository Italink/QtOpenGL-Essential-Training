#include "widget.h"

Widget::Widget(QWidget *parent)
    : QOpenGLWidget(parent)
    , VBO(QOpenGLBuffer::VertexBuffer)
    , VBOBuffer(QOpenGLBuffer::IndexBuffer)
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
    glClear(GL_COLOR_BUFFER_BIT);
    float vertices[]={
         0.5f,  0.5f, 0.0f,  // 右上角
         0.5f, -0.5f, 0.0f,  // 右下角
        -0.5f,  0.5f, 0.0f,  // 左上角
        -0.5f, -0.5f, 0.0f, // 左下角
    };
    VAO.create();
    VAO.bind();
    VBO.create();
    VBO.bind();
    VBO.allocate(vertices,sizeof (vertices));

    shaderProgram.create();
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,":/feedback.vert");

    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Geometry,":/feedback.geom");

    const char* var[]={"outValue"};

    glTransformFeedbackVaryings(shaderProgram.programId(),1,var,GL_INTERLEAVED_ATTRIBS);
    shaderProgram.link();
    shaderProgram.enableAttributeArray(0);
    shaderProgram.setAttributeBuffer(0,GL_FLOAT,0,1);       //将VBO和EBO的id，以及解析格式存储到VAO中
    VBOBuffer.create();
    VBOBuffer.bind();
    VBOBuffer.allocate(sizeof (vertices));
    VAO.release();
    VBO.release();
    VBOBuffer.release();
}

void Widget::paintGL()
{
    shaderProgram.bind();  
    QOpenGLVertexArrayObject::Binder bind(&VAO);
    glEnable(GL_RASTERIZER_DISCARD);
    glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER,0,VBOBuffer.bufferId());
    glBeginTransformFeedback(GL_POINTS);
    glDrawArrays(GL_POINTS,0,3);
    glEndTransformFeedback();
    glDisable(GL_RASTERIZER_DISCARD);
    VBOBuffer.bind();
    float s[12]={0};
    VBOBuffer.read(0,s,48);
    for(int i=0;i<12;i++)
        qDebug()<<s[i];
    qDebug()<<"-";
}

void Widget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
}

