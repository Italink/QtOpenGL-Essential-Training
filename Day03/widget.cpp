#include "widget.h"

Widget::Widget(QWidget *parent)
    : QOpenGLWidget(parent)
    , VBO(QOpenGLBuffer::VertexBuffer)
    , EBO(QOpenGLBuffer::IndexBuffer)
    , texture(QOpenGLTexture::Target2D)
{

}

Widget::~Widget()
{
    makeCurrent();
}

void Widget::initializeGL()
{
    initializeOpenGLFunctions();            //初始化QOpenGLFunctions，其本质是将QOpenGLFunctions与当前OpenGL上下文进行绑定
    glClearColor(0.0f,0.5f,0.9f,1.0f);      //设置清屏颜色
    glClear(GL_COLOR_BUFFER_BIT);           //清空颜色缓存区
    VAO.create();
    VAO.bind();
    VBO.create();
    VBO.bind();
    EBO.create();
    EBO.bind();

    uint elements[]={0,1,2,3};
    EBO.allocate(elements,sizeof(elements));//向GPU申请分配EBO内存，并把索引数组写入到EBO中

    float vertices[]={
         0.5f,  0.5f, 0.0f, 1.0f, 1.0f,  // 右上角
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f,  // 右下角
        -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,  // 左上角
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  // 左下角
    };

    VBO.allocate(vertices,sizeof (vertices));

    texture.create();                       //向GPU申请创建纹理对象
    texture.setData(QImage(":/OpenGL.jpg").mirrored());     //从QImage导入像素数据（内部会自动设置格式和分配存储）

    shaderProgram.create();
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,":/gl.vert");
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,":/gl.frag");
    shaderProgram.link();

    shaderProgram.enableAttributeArray(0);
    shaderProgram.setAttributeBuffer(0,GL_FLOAT,0,3,5*sizeof (float));       //将VBO和EBO的id，以及解析格式存储到当前VAO中

    shaderProgram.enableAttributeArray(1);
    shaderProgram.setAttributeBuffer(1,GL_FLOAT,3*sizeof (float),2,5*sizeof (float));

    VAO.release();
    VBO.release();      //作用同 QOpenGLBuffer::release(QOpenGLBuffer::VertexBuffer)
    EBO.release();      //作用同 QOpenGLBuffer::release(QOpenGLBuffer::IndexBuffer)
}

void Widget::paintGL()
{
    shaderProgram.bind();
    texture.bind(0);                                    //将纹理对象绑定到0号纹理单元
    shaderProgram.setUniformValue("texture",0);         //设置采样器[sample texture]从0号纹理单元获取数据
    QOpenGLVertexArrayObject::Binder bind(&VAO);        //构造时调用VAO.bind()，析构时调用VAO.release()

    glDrawElements(GL_TRIANGLE_STRIP,4,GL_UNSIGNED_INT,nullptr);
}

void Widget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
}

