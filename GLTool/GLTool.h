#ifndef GLTOOL_H
#define GLTOOL_H

#include "TextureTool.h"
#include "GLFilter.h"
#include <QColor>
#include <QFont>

namespace GLTool {
    extern TextureTool* textureTool;
    void drawTexture(GLuint textureId, QRectF geomtry=QRectF(-1,-1,2,2), float rotation=0);
    void drawImage(QImage image, QRectF geomtry=QRectF(-1,-1,2,2), float rotation=0);
    void drawText(QString text, QFont font=QFont(), QColor fontColor=Qt::red, QRectF geomtry=QRectF(-1,-1,2,2), float rotation=0);
    QImage createTextImgae(QString text, QFont font=QFont(), QColor fontColor=Qt::red);
    GLFilter* createFilter(const QByteArray& code);
}

#endif // GLTOOL_H
