#include "widget.h"
#include <QOpenGLFramebufferObject>
#include <QPainter>
#include <QTime>
#include "../GLTool/GLTool.h"
Widget::Widget(QWidget *parent)
    : QOpenGLWidget(parent)
    , texture(QOpenGLTexture::Target2D)
{
    timer.setInterval(20);        //设置定时器刷新间隔
                                  //定时调用重绘函数repaint(也可以调用update，只不过update不是直接响应)
    connect(&timer,&QTimer::timeout,this,static_cast<void (QWidget::*)()>(&QWidget::repaint));
    timer.start();
}

Widget::~Widget()
{
}

void Widget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);
    fbo=new QOpenGLFramebufferObject(size());       //创建与窗口同等尺寸的帧缓存对象
}

void Widget::paintGL()
{
    QString text=QTime::currentTime().toString();
    QFont font("微软雅黑",40);
    QFontMetrics fontMetrics(font);                                               //Qt中用来测量字体尺寸的
    QRect bounding=fontMetrics.boundingRect(text);
    QRect viewport(0,0,bounding.width(),bounding.height());                       //将OpenGL的视口调整为文字区域，且在屏幕中心
    viewport.moveCenter(rect().center());
    glViewport(viewport.x(),viewport.y(),viewport.width(),viewport.height());
    fbo->bind();
    glClear(GL_COLOR_BUFFER_BIT);
    GLTool::drawText(text,font,QColor(50,100,200));
    fbo->release();                                 //解绑fbo，绑定默认帧缓存对象
    glViewport(0,0,width(),height());               //重置视口为窗口大小
    GLTool::drawTexture(fbo->texture());
}

void Widget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
    delete fbo;
    fbo=new QOpenGLFramebufferObject(w,h);       //重新帧缓存对象
}


