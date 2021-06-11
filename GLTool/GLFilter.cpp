#include "GLFilter.h"

#include <QOpenGLFunctions>

GLFilter::GLFilter(const QByteArray& filterCode)
{
    VAO.create();
    VBO.create();
    VAO.bind();
    GLfloat vertices[]={
        -1, 1,      //左上
        -1,-1,      //左下
         1, 1,      //右上
         1,-1       //右下
    };
    VBO.bind();
    VBO.allocate(vertices,sizeof (vertices));
    program.create();
    program.addShaderFromSourceCode(QOpenGLShader::Vertex,
                                    "#version 450 core\n"
                                    "in layout(location = 0 ) vec2 pos;\n"
                                    "out vec2 texCoord;\n"
                                    "void main(){\n"
                                    "   gl_Position=vec4(pos,0,1);\n"
                                    "   texCoord=(pos+1)/2;"
                                    "}\n");

    program.addShaderFromSourceCode(QOpenGLShader::Fragment,
                                    filterCode);
    program.link();
    program.enableAttributeArray(0);
    program.setAttributeBuffer(0,GL_FLOAT,0,2);
    VAO.release();
    VBO.release();
}

void GLFilter::runFilter(QOpenGLFramebufferObject *readFBO, QRect readGeomtry, QOpenGLFramebufferObject *writeFBO, QRect drawGeomtry)
{
    QOpenGLFunctions* func=QOpenGLContext::currentContext()->functions();
    if(fbo!=nullptr&&fbo->size()!=readGeomtry.size())
        delete fbo;

    fbo=new QOpenGLFramebufferObject(readGeomtry.width(),readGeomtry.height());
    QOpenGLFramebufferObject::blitFramebuffer(fbo,QRect(0,0,fbo->width(),fbo->height()),readFBO,readGeomtry);
    writeFBO->bind();
    func->glActiveTexture(GL_TEXTURE0);
    func->glBindTexture(GL_TEXTURE_2D,fbo->texture());
    program.bind();
    QOpenGLVertexArrayObject::Binder binder(&VAO);
    func->glDrawArrays(GL_TRIANGLE_STRIP,0,4);
    program.release();
    writeFBO->release();
}

void GLFilter::runFilter(QRect geomtry)
{
    QOpenGLFunctions* func=QOpenGLContext::currentContext()->functions();
    if(fbo!=nullptr&&fbo->size()!=geomtry.size())
        delete fbo;

    GLuint prevFbo = 0;                                                     //获取当前绑定的FBO
    func->glGetIntegerv(GL_FRAMEBUFFER_BINDING, (GLint *) &prevFbo);

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

    func->glActiveTexture(GL_TEXTURE0);
    func->glBindTexture(GL_TEXTURE_2D,fbo->texture());
    program.bind();
    QOpenGLVertexArrayObject::Binder binder(&VAO);
    func->glDrawArrays(GL_TRIANGLE_STRIP,0,4);
    program.release();
    func->glViewport(preViewport[0],preViewport[1],preViewport[2],preViewport[3]);
}

