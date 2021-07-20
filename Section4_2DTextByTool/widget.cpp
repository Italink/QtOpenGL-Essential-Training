#include "widget.h"
#include <QPainter>
#include <QTime>
#include "GLTool.h"
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
    GLTool::drawText(text,font,QColor(50,100,200));                               //绘制纹理，填充整个视口（viewport）
}

void Widget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
}


