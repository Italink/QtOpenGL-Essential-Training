#ifndef WIDGET_H
#define WIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>
#include <QOpenGLFramebufferObject>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>

class Widget : public QOpenGLWidget ,protected QOpenGLExtraFunctions
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
protected:
    virtual void initializeGL() override;
    virtual void paintGL() override;
    virtual void resizeGL(int w,int h) override;
    virtual void mousePressEvent(QMouseEvent*) override;

private:
    void runMousePoints();
private:
    QOpenGLFramebufferObject* FBO;
    QOpenGLVertexArrayObject VAO;
    QOpenGLBuffer VBO;
    QOpenGLTexture background;
    QOpenGLShaderProgram waveProgram;
    QOpenGLShaderProgram renderProgram;
    QVector<QVector3D> mouse;
    float frequency = 0.1;    //频率
    float amplitude = 0.1;    //最大振幅
    float wave_width = 100;   //波纹的宽度
    float depth = 1;        //水平面距离背景图片的深度
    float speed = 1000;        //水纹的移动速度
    float lifetime = 1000;
    float lastTime;
};
#endif // WIDGET_H
