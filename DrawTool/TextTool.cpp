#include "TextTool.h"
#include "TextureTool.h"

#include <QPainter>
TextTool::TextTool()
{

}


void TextTool::setup(QOpenGLWidget *widget)
{
    TextureTool::setup(widget);
}

void TextTool::draw(QString text, QFont font, QColor fontColor, QRectF geomtry, float rotation)
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
    TextureTool::draw(image,geomtry,rotation);
}
