#ifndef TEXTTOOL_H
#define TEXTTOOL_H


#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>

class TextTool
{
private:
    TextTool();
public:
    static void setup(QOpenGLWidget* widget);
    static void draw(QString text, QFont font=QFont(), QColor fontColor=Qt::red, QRectF geomtry=QRectF(-1,-1,2,2), float rotation=0);
private:
};

#endif // TEXTTOOL_H
