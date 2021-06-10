#ifndef TEXTURETOOL_H
#define TEXTURETOOL_H

#include<QOpenGLWidget>
#include<QOpenGLExtraFunctions>
#include<QOpenGLVertexArrayObject>
#include<QOpenGLShaderProgram>
#include <QOpenGLBuffer>

class TextureTool : protected QOpenGLExtraFunctions
{
private:
    TextureTool();
    static TextureTool* getTool();
    void init(QOpenGLWidget* glWidget);
    void drawTexture(GLuint textureId, QRectF geomtry=QRectF(-1,-1,2,2), float rotation=0);
public:
    static void setup(QOpenGLWidget* widget);
    static void draw(GLuint textureId, QRectF geomtry=QRectF(-1,-1,2,2), float rotation=0);
    static void draw(QImage image, QRectF geomtry=QRectF(-1,-1,2,2), float rotation=0);
private:
    QOpenGLWidget* glWidget;
    QOpenGLVertexArrayObject VAO;
    QOpenGLBuffer VBO;
    QOpenGLShaderProgram program;
};

#endif // TEXTURETOOL_H
