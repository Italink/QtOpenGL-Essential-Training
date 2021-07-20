#ifndef GLFILTER_H
#define GLFILTER_H

#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLFramebufferObject>
#include <QOpenGLFunctions>

class GLFilter
{
public:
    GLFilter(const QByteArray &filterCode);
    template<typename  ShaderProgramFunction=std::function<void(QOpenGLShaderProgram&)>>
    void runFilter(QOpenGLFramebufferObject * readFBO, QRect readGeomtry, QOpenGLFramebufferObject * writeFBO, QRect drawGeomtry,ShaderProgramFunction function=[](QOpenGLShaderProgram&){})
    {
        QOpenGLFunctions* func=QOpenGLContext::currentContext()->functions();
        if(fbo!=nullptr&&fbo->size()!=readGeomtry.size())
            delete fbo;
        if(fbo==nullptr)
            fbo=new QOpenGLFramebufferObject(readGeomtry.width(),readGeomtry.height());
        QOpenGLFramebufferObject::blitFramebuffer(fbo,QRect(0,0,fbo->width(),fbo->height()),readFBO,readGeomtry);
        if(writeFBO!=nullptr)
            writeFBO->bind();

        program.bind();
        func->glActiveTexture(GL_TEXTURE0);
        func->glBindTexture(GL_TEXTURE_2D,fbo->texture());
        function(program);
        QOpenGLVertexArrayObject::Binder binder(&VAO);
        func->glDrawArrays(GL_TRIANGLE_STRIP,0,4);
        if(writeFBO!=nullptr)
            writeFBO->release();
        program.release();
    }

    template<typename  ShaderProgramFunction=std::function<void(QOpenGLShaderProgram&)>>
    void runFilter(QRect geomtry,ShaderProgramFunction function=[](QOpenGLShaderProgram&){})
    {
        QOpenGLFunctions* func=QOpenGLContext::currentContext()->functions();
        if(fbo!=nullptr&&fbo->size()!=geomtry.size())
            delete fbo;

        GLuint prevFbo = 0;                                                     //获取当前绑定的FBO
        func->glGetIntegerv(GL_FRAMEBUFFER_BINDING, (GLint *) &prevFbo);
        if(fbo==nullptr)
            fbo=new QOpenGLFramebufferObject(geomtry.width(),geomtry.height());     //由于Qt创建FBO的同时会进行绑定
        QOpenGLFramebufferObject::blitFramebuffer(fbo,QRect(0,0,fbo->width(),fbo->height()),nullptr,geomtry);

        func->glBindFramebuffer(GL_FRAMEBUFFER,prevFbo);                        //所以要在这里进行复原

        GLint preViewport[4] = {0};
        func->glGetIntegerv(GL_VIEWPORT, preViewport);                          //获取当前的viewport数据

        func->glViewport(geomtry.x(),geomtry.y(),geomtry.width(),geomtry.height());

        func->glScissor(geomtry.x(),geomtry.y(),geomtry.width(),geomtry.height());        //清除指定区域
        func->glEnable(GL_SCISSOR_TEST);
        func->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        func->glDisable(GL_SCISSOR_TEST);
        program.bind();

        func->glActiveTexture(GL_TEXTURE0);
        func->glBindTexture(GL_TEXTURE_2D,fbo->texture());

        function(program);

        QOpenGLVertexArrayObject::Binder binder(&VAO);

        func->glDrawArrays(GL_TRIANGLE_STRIP,0,4);
        program.release();
        func->glViewport(preViewport[0],preViewport[1],preViewport[2],preViewport[3]);
    }
private:
    QOpenGLVertexArrayObject VAO;
    QOpenGLBuffer VBO;
    QOpenGLShaderProgram program;
    QOpenGLFramebufferObject* fbo=nullptr;
};

#endif // GLFILTER_H
