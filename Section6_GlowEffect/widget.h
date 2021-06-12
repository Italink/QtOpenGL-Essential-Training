#ifndef WIDGET_H
#define WIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QTimer>
#include <GLFilter.h>

class Widget : public QOpenGLWidget , protected QOpenGLExtraFunctions
{
    Q_OBJECT
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void setBlurRadius(int radius);
protected:
    virtual void initializeGL() override;
    virtual void paintGL() override;
    virtual void resizeGL(int w, int h) override;
private:
    QOpenGLTexture texture;
    QTimer timer;
    QOpenGLFramebufferObject* xBlur;
    QOpenGLFramebufferObject* yBlur;
    GLFilter* xFilter;
    GLFilter* yFilter;
    GLFilter* glowFilter;

    QVector<float> guassWeight;
};

#endif // WIDGET_H
