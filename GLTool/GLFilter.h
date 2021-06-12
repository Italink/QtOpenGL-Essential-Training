#ifndef GLFILTER_H
#define GLFILTER_H

#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLFramebufferObject>

class GLFilter
{
public:
    GLFilter(const QByteArray &filterCode);
    void runFilter(QOpenGLFramebufferObject * readFBO, QRect readGeomtry, QOpenGLFramebufferObject * writeFBO, QRect drawGeomtry,QVector<GLuint> extTextureIds={});
    void runFilter(QRect geomtry);
    QOpenGLShaderProgram &getProgram();

private:
    QOpenGLVertexArrayObject VAO;
    QOpenGLBuffer VBO;
    QOpenGLShaderProgram program;
    QOpenGLFramebufferObject* fbo=nullptr;
};

#endif // GLFILTER_H
