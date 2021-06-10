#include "TextureTool.h"
#include "TestWidget.h"

Widget::Widget(QWidget *parent)
    : QOpenGLWidget(parent)
    , texture(QOpenGLTexture::Target2D)
{
}

Widget::~Widget()
{
}

void Widget::initializeGL()
{
    initializeOpenGLFunctions();
    TextureTool::setup(this);
    texture.create();
    texture.setData(QImage(":image.png").mirrored());
}

void Widget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
}

void Widget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    TextureTool::draw(texture.textureId(),QRectF(-1,-1,1,1),90);
    TextureTool::draw(QImage(":image.png"),QRectF(0,0,1,1),0);
}

