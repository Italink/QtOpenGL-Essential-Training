#ifndef WIDGET_H
#define WIDGET_H

#include "GLFilter.h"

#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>
#include <QOpenGLTexture>

class Widget : public QOpenGLWidget, protected QOpenGLExtraFunctions
{
    Q_OBJECT
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    // QOpenGLWidget interface
protected:
    virtual void initializeGL() override;
    virtual void resizeGL(int w, int h) override;
    virtual void paintGL() override;
private:
    QOpenGLTexture texture;
    GLFilter* filter;
};
#endif // WIDGET_H
