#ifndef WIDGET_H
#define WIDGET_H

#include <QOpenGLWidget>
#include <QWidget>
#include <QVector3D>
#include <QVector4D>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLExtraFunctions>
#include <QTime>

class Widget : public QOpenGLWidget, public QOpenGLExtraFunctions
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    int numOfPerFrame = 100;
    float lifetime = 1;
    double defaultSize=5;
    // QOpenGLWidget interface
protected:
    virtual void initializeGL() override;
    virtual void resizeGL(int w, int h) override;
    virtual void paintGL() override;

protected:
    void createParticles();
    void updateParticles();
    void renderParticles();

private:
    struct Particle{
        QVector3D position;
        QVector3D velocity;
        float size;
        float life;
        QVector4D color;
    };

    QOpenGLShaderProgram updateProgram;
    QOpenGLShaderProgram renderProgram;
    QOpenGLVertexArrayObject VAO;

    QOpenGLBuffer VBO;
    QOpenGLBuffer VBOBuffer;

    GLuint particleQuery;
    GLuint currentNumOfParticles = 0;
    QTime timeOfLastFrame;
};

#endif // WIDGET_H
