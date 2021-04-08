#include "widget.h"
#include <QTimer>
#include <QTime>

Widget::Widget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    QTimer *timer=new QTimer;
    connect(timer,&QTimer::timeout,this,static_cast<void (QWidget::*)()>(&QWidget::repaint));
    timer->setInterval(17);
    timer->start();
}

Widget::~Widget()
{
}

void Widget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0,0,0,0);
    shaderProgram.create();

    shaderProgram.addShaderFromSourceCode(QOpenGLShader::Vertex,"#version 450 core\n"
                                                                "layout(location = 0) in vec2 aPos;\n"
                                                                "void main(){\n"
                                                                "  gl_Position = vec4(aPos,0,1); \n"
                                                             "}");

    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,":/GLSLSandbox.frag");
    shaderProgram.link();
    shaderProgram.enableAttributeArray(0);  //开启0号顶点数据
}

void Widget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    shaderProgram.bind();

    float time=QTime::currentTime().msecsSinceStartOfDay()/1000.0f;
    shaderProgram.setUniformValue("time",time);             //输入时间

    QVector2D resolution(this->width(),this->height());     //输入窗口分辨率
    shaderProgram.setUniformValue("resolution",resolution);

    QVector2D vertices[4]={
        {-1,-1},
        {-1, 1},
        { 1,-1},
        { 1, 1}};

    shaderProgram.setAttributeArray(0,vertices);            //从客户端传递顶点数据

    glDrawArrays(GL_TRIANGLE_STRIP,0,4);                    //需要保证没有绑定VAO和VBO

    shaderProgram.release();
}

void Widget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
}

