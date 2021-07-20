#include "widget.h"

#include <QMouseEvent>
#include <QTime>
#include <QTimer>

Widget::Widget(QWidget *parent)
    : QOpenGLWidget(parent)
    , background(QOpenGLTexture::Target2D)
{
    QTimer *timer = new QTimer();
    connect(timer,&QTimer::timeout,this,static_cast<void (QWidget::*)()>(&QWidget::repaint));
    timer->setInterval(17);
    timer->start();
}

Widget::~Widget()
{
    makeCurrent();
}

void Widget::initializeGL()
{
    initializeOpenGLFunctions ();
    VAO.create ();
    VBO.create ();
    FBO=new QOpenGLFramebufferObject(size(),QOpenGLFramebufferObject::NoAttachment,GL_TEXTURE_2D,GL_RED);
    waveProgram.create();
    renderProgram.create();
    waveProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,":/wave.vert");
    waveProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,":/wave.frag");
    waveProgram.link();

    renderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,":/render.vert");
    renderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,":/render.frag");
    renderProgram.link();

    background.create();
    background.setWrapMode(QOpenGLTexture::MirroredRepeat);
    background.setMinMagFilters(QOpenGLTexture::Linear,QOpenGLTexture::Linear);
    background.setData(QImage(":/background.jpg").mirrored());

    VAO.bind ();
    VBO.bind ();
    float vertices[]={
        -1,-1,
         1,-1,
        -1, 1,
         1, 1,
    };

    VBO.allocate (vertices,sizeof (vertices));
    waveProgram.setAttributeBuffer(0,GL_FLOAT,0,2,2*sizeof (float));
    waveProgram.enableAttributeArray(0);
    renderProgram.enableAttributeArray(0);;
    VBO.release();
    VAO.release();

    lastTime=QTime::currentTime().msecsSinceStartOfDay();

}

void Widget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    QOpenGLVertexArrayObject::Binder bind(&VAO);
    FBO->bind();
    waveProgram.bind();
    waveProgram.setUniformValueArray("mouse",mouse.data(),mouse.size());
    waveProgram.setUniformValue("size",mouse.size());
    waveProgram.setUniformValue("frequency",frequency);
    waveProgram.setUniformValue("amplitude",amplitude);
    waveProgram.setUniformValue("wave_width",wave_width);
    waveProgram.setUniformValue("speed",speed);
    glDrawArrays(GL_TRIANGLE_STRIP,0,4);
    FBO->release();

    renderProgram.bind();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,FBO->texture());
    background.bind(1);
    renderProgram.setUniformValue("wave",0);
    renderProgram.setUniformValue("background",1);
    renderProgram.setUniformValue("screen_width",QVector2D(width(),height()));
    renderProgram.setUniformValue("depth",depth);
    GL_RGBA
    glDrawArrays(GL_TRIANGLE_STRIP,0,4);
    runMousePoints();
}

void Widget::resizeGL(int w, int h)
{
    glViewport (0,0,w,h);
    delete FBO;
    FBO=new QOpenGLFramebufferObject(w,h,QOpenGLFramebufferObject::NoAttachment,GL_TEXTURE_2D,GL_RED);
}

void Widget::mousePressEvent(QMouseEvent *e)
{
    mouse.push_back(QVector3D(e->x(),height()-e->y(),0));
}

void Widget::runMousePoints()
{
    float currentTime=QTime::currentTime().msecsSinceStartOfDay();
    float dure=currentTime-lastTime;
    float run=dure/lifetime;
    QVector<QVector3D> temp;
    for(auto it:mouse){
        QVector3D m=it+QVector3D(0,0,run);
        if(m.z()<=1)
            temp.push_back(m);
    }
    mouse=temp;
    lastTime=currentTime;
}

