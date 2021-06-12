#include "TextureTool.h"
#include <QOpenGLTexture>
#include <QOpenGLWidget>

TextureTool::TextureTool()
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
                                    "uniform mat4 model;\n"
                                    "void main(){\n"
                                    "   gl_Position=model*vec4(pos,0,1);\n"
                                    "   texCoord=(pos+1)/2;"
                                    "}\n");

    program.addShaderFromSourceCode(QOpenGLShader::Fragment,
                                    "#version 450 core\n"
                                    "in vec2 texCoord;\n"
                                    "uniform sampler2D tex;\n"
                                    "out vec4 FragColor;\n"
                                    "void main(){\n"
                                    "   FragColor=texture(tex,texCoord);\n"
                                    "}\n");
    program.link();
    program.enableAttributeArray(0);
    program.setAttributeBuffer(0,GL_FLOAT,0,2);
    VAO.release();
    VBO.release();
}

void TextureTool::drawTexture(GLuint textureId, QRectF geomtry, float rotation)
{
    QOpenGLFunctions *func =QOpenGLContext::currentContext()->functions();
    QOpenGLVertexArrayObject::Binder bind(&VAO);
    program.bind();
    QMatrix4x4 model;
    model.translate(geomtry.center().x(),geomtry.center().y());
    model.rotate(rotation,QVector3D(0,0,1));
    model.scale(geomtry.width()/2,geomtry.height()/2);
    program.setUniformValue("model",model);
    func->glActiveTexture(GL_TEXTURE0);
    func->glBindTexture(GL_TEXTURE_2D,textureId);
    func->glDrawArrays(GL_TRIANGLE_STRIP,0,4);
    program.release();
}

void TextureTool::drawImage(QImage image, QRectF geomtry, float rotation)
{
    QOpenGLTexture texture(QOpenGLTexture::Target2D);
    texture.create();
    texture.setMinMagFilters(QOpenGLTexture::Linear,QOpenGLTexture::Linear);
    texture.setData(image.mirrored());
    drawTexture(texture.textureId(),geomtry,rotation);
}
