#include "GLTool.h"
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
    texture.create();
    texture.setData(QImage(":image.png").mirrored());

    filter=GLTool::createFilter(            //创建一个取反色的滤镜
                "#version 450 core\n"
                "in vec2 texCoord;\n"
                "uniform sampler2D pre;\n"
                "out vec4 FragColor;\n"
                "void main(){\n"
                "   FragColor=vec4(1)-vec4(texture(pre,texCoord).xyz,0);\n"
                "}");
}

void Widget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
}

void Widget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    GLTool::drawTexture(texture.textureId(),QRectF(-1,-1,1,1),90);
    GLTool::drawImage(QImage(":image.png"),QRectF(0,0,1,1),0);
    GLTool::drawText("hello",QFont(),QColor(10,100,200),QRectF(0,-1,1,1));
    filter->runFilter(rect());      //这里的区域是窗口大小而非标准化坐标
}
