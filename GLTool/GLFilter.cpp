#include "GLFilter.h"



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



