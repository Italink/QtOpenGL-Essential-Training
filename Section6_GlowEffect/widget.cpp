#include "widget.h"
#include <QPainter>
#include <QTime>
#include "../Tool/TextureTool/TextureTool.h"
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
    TextureTool::setup(this);
}

void Widget::paintGL()
{
    flushTexture();
    TextureTool::draw(texture.textureId());             //绘制纹理，填充整个视口（viewport）
}

void Widget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
}

void Widget::flushTexture()
{
    QString text=QTime::currentTime().toString();
    QFont font("微软雅黑",40);
    QFontMetrics fontMetrics(font);                     //Qt中用来测量字体尺寸的
    QRect bounding=fontMetrics.boundingRect(text);      //获取到字符串的外包矩形
    QImage image(bounding.size(),QImage::Format_ARGB32);
    image.fill(Qt::transparent);                        //使用透明色填充Image
    QPainter painter(&image);
    painter.setRenderHint(QPainter::TextAntialiasing);  //开启抗锯齿
    painter.setFont(font);
    painter.setPen(QColor(0,90,200));
    painter.drawText(QRect(0,0,image.width(),image.height()),Qt::AlignCenter,text);
    painter.end();
    if(texture.isCreated())
        texture.destroy();                              //销毁纹理，重新分配存储
    texture.create();                                   //通过这种方法来实现动态纹理适应于纹理尺寸会动态变化的情况，内存分配会占用一定性能，但在这里影响微乎其微（如果是绘制视频帧，那么就需要提前分配存储，之后动态上传像素数据）
    texture.setData(image.mirrored());
    QRect viewport(image.rect());                       //将OpenGL的视口调整为文字区域，且在屏幕中心
    viewport.moveCenter(rect().center());
    glViewport(viewport.x(),viewport.y(),viewport.width(),viewport.height());
}

