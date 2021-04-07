#include "widget.h"
#include <QPainter>
#include <QTime>


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

    VAO.create();
    QOpenGLVertexArrayObject::Binder bind(&VAO);
    VBO.create();
    VBO.bind();
    float vertex[]={
        //顶点            //纹理坐标
        -1.0f,-1.0f,    0.0f,0.0f,    //左下
        -1.0f, 1.0f,    0.0f,1.0f,    //左上
         1.0f,-1.0f,    1.0f,0.0f,    //右下
         1.0f, 1.0f,    1.0f,1.0f     //右上
    };

    VBO.allocate(vertex,sizeof (vertex));
    shaderProgram.create();
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,":/text.vert");
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,":/text.frag");
    shaderProgram.link();
    shaderProgram.enableAttributeArray(0);
    shaderProgram.enableAttributeArray(1);
    shaderProgram.setAttributeBuffer(0,GL_FLOAT,0,               2,4*sizeof (float));
    shaderProgram.setAttributeBuffer(1,GL_FLOAT,2*sizeof (float),2,4*sizeof (float));
    VBO.release();
}

void Widget::paintGL()
{
    shaderProgram.bind();
    flushTexture();
    texture.bind(0);
    shaderProgram.setUniformValue("texture",0);
    QOpenGLVertexArrayObject::Binder bind(&VAO);
    glDrawArrays(GL_TRIANGLE_STRIP,0,4);
    shaderProgram.release();
}

void Widget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
}

void Widget::flushTexture()
{
    QString text=QTime::currentTime().toString();
    QFont font("微软雅黑",50);
    QFontMetrics fontMetrics(font);                 //Qt中用来测量字体尺寸的
    QRect bounding=fontMetrics.boundingRect(text);  //获取到字符串的外包矩形
    QImage image(bounding.size(),QImage::Format_ARGB32);
    image.fill(Qt::transparent);        //使用透明色填充Image
    QPainter painter(&image);
    painter.setFont(font);
    painter.setPen(QColor(0,90,200));
    painter.drawText(QRect(0,0,image.width(),image.height()),Qt::AlignCenter,text);
    painter.end();
    if(texture.isCreated())
        texture.destroy();          //销毁纹理，重新分配存储
    texture.create();               //通过这种方法来实现动态纹理适应于纹理尺寸会动态变化的情况，内存分配会占用一定性能，但在这里影响微乎其微（如果是绘制视频帧，那么就需要提前分配存储，之后动态上传像素数据）
    texture.setData(image.mirrored());
}

