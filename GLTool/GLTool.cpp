#include "GLTool.h"
#include <QPainter>
#include <QtOpenGLExtensions/QOpenGLExtensions>
#include <QtOpenGLExtensions/QtOpenGLExtensions>
namespace GLTool {
    TextureTool* textureTool=nullptr;
}
GLFilter *GLTool::createFilter(const QByteArray &code)
{
    return new GLFilter(code);
}

void GLTool::drawTexture(GLuint textureId, QRectF geomtry, float rotation)
{
    if(textureTool==nullptr)
        textureTool=new TextureTool();
    textureTool->drawTexture(textureId,geomtry,rotation);
}

void GLTool::drawImage(QImage image, QRectF geomtry, float rotation)
{
    if(textureTool==nullptr)
        textureTool=new TextureTool();
    textureTool->drawImage(image,geomtry,rotation);
}

QImage GLTool::createTextImgae(QString text, QFont font, QColor fontColor)
{
    QFontMetrics fontMetrics(font);                     //Qt中用来测量字体尺寸的
    QRect bounding=fontMetrics.boundingRect(text);      //获取到字符串的外包矩形
    QImage image(bounding.size(),QImage::Format_ARGB32);
    image.fill(Qt::transparent);                        //使用透明色填充Image
    QPainter painter(&image);
    painter.setRenderHint(QPainter::TextAntialiasing);  //开启抗锯齿
    painter.setFont(font);
    painter.setPen(fontColor);
    painter.drawText(QRect(0,0,image.width(),image.height()),Qt::AlignCenter,text);
    painter.end();
    return image;
}

void GLTool::drawText(QString text, QFont font, QColor fontColor, QRectF geomtry, float rotation)
{
    if(textureTool==nullptr)
        textureTool=new TextureTool();
    textureTool->drawImage(createTextImgae(text,font,fontColor),geomtry,rotation);
}
