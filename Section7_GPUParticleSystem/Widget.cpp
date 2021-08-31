#include "Widget.h"

#include <QTimer>

const int MAX_PARTICLES_SIZE = 1000000;

Widget::Widget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    setMinimumSize(800,600);
    QTimer *timer=new QTimer(this);
    timer->setInterval(18);        //设置定时器刷新间隔
                                   //定时调用重绘函数repaint(也可以调用update，只不过update不是直接响应)
    connect(timer,&QTimer::timeout,this,static_cast<void (QWidget::*)()>(&QWidget::repaint));
    timer->start();
}

Widget::~Widget()
{
}

void Widget::initializeGL()
{
    initializeOpenGLFunctions();

    VBO.create();
    VBO.bind();
    VBO.setUsagePattern(QOpenGLBuffer::DynamicDraw);
    VBO.allocate(sizeof (Particle)*MAX_PARTICLES_SIZE);

    VBOBuffer.create();
    VBOBuffer.bind();
    VBOBuffer.setUsagePattern(QOpenGLBuffer::DynamicDraw);
    VBOBuffer.allocate(sizeof (Particle)*MAX_PARTICLES_SIZE);

    glGenQueries(1,&particleQuery);

    VAO.create();
    VAO.bind();

    updateProgram.create();
    updateProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,":/ParticleRunner.vert");
    updateProgram.addShaderFromSourceFile(QOpenGLShader::Geometry,":/ParticleRunner.geom");

    const char* feedbackVar[5]={"position","velocity","size","life","color"};
    glTransformFeedbackVaryings(updateProgram.programId(),5,feedbackVar,GL_INTERLEAVED_ATTRIBS);
    updateProgram.link();

    VBO.bind();
    updateProgram.enableAttributeArray(0);
    updateProgram.enableAttributeArray(1);
    updateProgram.enableAttributeArray(2);
    updateProgram.enableAttributeArray(3);
    updateProgram.enableAttributeArray(4);

    renderProgram.create();
    renderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,":/ParticleRender.vert");
    renderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,":/ParticleRender.frag");
    renderProgram.link();

    timeOfLastFrame=QTime::currentTime();

    glEnable(GL_PROGRAM_POINT_SIZE);
}

void Widget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
}

void Widget::paintGL()
{
    createParticles();
    updateParticles();
    renderParticles();
}

void Widget::createParticles()
{
    VAO.bind();
    VBO.bind();
    QVector<Particle> createBuffer;
    for(int i=0;i<numOfPerFrame;i++){
        Particle particle;
        particle.position=QVector3D(0,0,0);
        particle.velocity=QVector3D((rand()%1000/1000.0-0.5)*0.1,0.1,(rand()%1000/1000.0-0.5)*0.1);
        particle.size=defaultSize;
        particle.life=0;
        particle.color=QVector4D(1,1,1,1);
        createBuffer<<particle;
    }
    VBO.write(currentNumOfParticles*sizeof (Particle),createBuffer.data(),createBuffer.size()*sizeof (Particle));
    currentNumOfParticles+=createBuffer.size();

    VAO.release();
    VBO.release();
}

void Widget::updateParticles()
{
    float durationSecond=timeOfLastFrame.msecsTo(QTime::currentTime())/1000.0;
    timeOfLastFrame=QTime::currentTime();
    VAO.bind();
    VBO.bind();

    updateProgram.bind();
    updateProgram.setUniformValue("lifetime",lifetime);
    updateProgram.setUniformValue("duration",durationSecond);

    updateProgram.setAttributeBuffer(0,GL_FLOAT,offsetof(Particle,position ),3,sizeof(Particle));
    updateProgram.setAttributeBuffer(1,GL_FLOAT,offsetof(Particle,velocity ),3,sizeof(Particle));
    updateProgram.setAttributeBuffer(2,GL_FLOAT,offsetof(Particle,size     ),1,sizeof(Particle));
    updateProgram.setAttributeBuffer(3,GL_FLOAT,offsetof(Particle,life     ),1,sizeof(Particle));
    updateProgram.setAttributeBuffer(4,GL_FLOAT,offsetof(Particle,color    ),4,sizeof(Particle));

    glEnable(GL_RASTERIZER_DISCARD);
    glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER,0,VBOBuffer.bufferId());
    glBeginQuery(GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN, particleQuery);
    glBeginTransformFeedback(GL_POINTS);
    glDrawArrays(GL_POINTS,0,currentNumOfParticles);
    glEndTransformFeedback();
    glEndQuery(GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN);
    glGetQueryObjectuiv(particleQuery, GL_QUERY_RESULT,&currentNumOfParticles);
    glDisable(GL_RASTERIZER_DISCARD);
    qSwap(VBO,VBOBuffer);
    updateProgram.release();
    VAO.release();
    VBO.release();

}

void Widget::renderParticles()
{
    renderProgram.bind();
    VAO.bind();
    VBO.bind();
    QMatrix4x4 VP;
    VP.perspective(45.0f,width()/(float)height(),0.1f,1000.0f);
    VP.lookAt(QVector3D(10,10,10),QVector3D(0,0,0),QVector3D(0,1,0));
    renderProgram.setUniformValue("VP",VP);
    glDrawArrays(GL_POINTS,0,currentNumOfParticles);
    VAO.release();
    VBO.release();
    renderProgram.release();
}

