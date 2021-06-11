#ifndef TEXTURETOOL_H
#define TEXTURETOOL_H

#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>

class TextureTool
{
public:
    TextureTool();
    void drawTexture(GLuint textureId, QRectF geomtry=QRectF(-1,-1,2,2), float rotation=0);
    void drawImage(QImage image, QRectF geomtry=QRectF(-1,-1,2,2), float rotation=0);
private:
    QOpenGLVertexArrayObject VAO;
    QOpenGLBuffer VBO;
    QOpenGLShaderProgram program;
};

#endif // TEXTURETOOL_H
