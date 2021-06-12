#include "GLTool.h"
#include <QPainter>
#include <QtOpenGLExtensions/QOpenGLExtensions>
#include <QtOpenGLExtensions/QtOpenGLExtensions>
namespace GLTool {
TextureTool* textureTool=nullptr;

void drawTexture(const QOpenGLTexture &texture, QRectF geomtry, float rotation)
{
    drawTexture(texture.textureId(),geomtry, rotation);
}

GLFilter *createFilter(const QByteArray &code)
{
    return new GLFilter(code);
}

void drawTexture(GLuint textureId, QRectF geomtry, float rotation)
{
    if(textureTool==nullptr)
        textureTool=new TextureTool();
    textureTool->drawTexture(textureId,geomtry,rotation);
}

void drawImage(QImage image, QRectF geomtry, float rotation)
{
    if(textureTool==nullptr)
        textureTool=new TextureTool();
    textureTool->drawImage(image,geomtry,rotation);
}

QImage createTextImgae(QString text, QFont font, QColor fontColor)
{
    QFontMetrics fontMetrics(font);                     //Qt中用来测量字体尺寸的
    QRect bounding=fontMetrics.boundingRect(text);      //获取到字符串的外包矩形
    QImage image(bounding.size(),QImage::Format_ARGB32);
    image.fill(Qt::transparent);                        //使用透明色填充Image
    QPainter painter(&image);
    painter.setRenderHints(QPainter::TextAntialiasing|QPainter::Antialiasing);  //开启抗锯齿
    painter.setFont(font);
    painter.setPen(fontColor);
    painter.drawText(QRect(0,0,image.width(),image.height()),Qt::AlignCenter,text);
    painter.end();
    return image;
}

void drawText(QString text, QFont font, QColor fontColor, QRectF geomtry, float rotation)
{
    if(textureTool==nullptr)
        textureTool=new TextureTool();
    textureTool->drawImage(createTextImgae(text,font,fontColor),geomtry,rotation);
}



}
