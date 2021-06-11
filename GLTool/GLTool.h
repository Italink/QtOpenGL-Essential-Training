#ifndef GLTOOL_H
#define GLTOOL_H

#include "TextureTool.h"
#include "GLFilter.h"
#include <QColor>
#include <QFont>
#include <QOpenGLTexture>

/**
 *  所有的工具函数接口将置于此命名空间中
 */

namespace GLTool {
    extern TextureTool* textureTool;

    /**
     * @brief drawTexture 该函数用于在指定区域绘制纹理图形
     * @param texture 纹理对象
     * @param geomtry 图像将绘制在该标准化坐标区域
     * @param rotation 按纹理中心进行旋转的旋转角度
     */
    void drawTexture(const QOpenGLTexture& texture, QRectF geomtry=QRectF(-1,-1,2,2), float rotation=0);

    /**
     * @brief drawTexture 该函数用于在指定区域绘制纹理图形
     * @param textureId 纹理对象的id
     * @param geomtry 图像将绘制在该标准化坐标区域
     * @param rotation 按纹理中心进行旋转的旋转角度
     */
    void drawTexture(GLuint textureId, QRectF geomtry=QRectF(-1,-1,2,2), float rotation=0);

    /**
     * @brief drawImage 该函数用于在指定区域绘制QImage
     * @param image QImage对象
     * @param geomtry 图像将绘制在该标准化坐标区域
     * @param rotation 按纹理中心进行旋转的旋转角度
     */
    void drawImage(QImage image, QRectF geomtry=QRectF(-1,-1,2,2), float rotation=0);

    /**
     * @brief drawText 该函数用于在指定区域绘制文字
     * @param text 文字内容
     * @param font 字体属性（包含字体类型，字体大小，加粗，斜体等数据）
     * @param fontColor 字体颜色
     * @param geomtry 图像将绘制在该标准化坐标区域
     * @param rotation 按纹理中心进行旋转的旋转角度
     */
    void drawText(QString text, QFont font=QFont(), QColor fontColor=Qt::red, QRectF geomtry=QRectF(-1,-1,2,2), float rotation=0);

    /**
     * @brief createTextImgae 该函数用于创建文字的QImage图像，使用该Image能实现3D文字的显示
     * @param text 文字内容
     * @param font 字体属性（包含字体类型，字体大小，加粗，斜体等数据）
     * @param fontColor 字体颜色
     * @return 返回文字的QImage
     */
    QImage createTextImgae(QString text, QFont font=QFont(), QColor fontColor=Qt::red);
    GLFilter* createFilter(const QByteArray& code);
}

#endif // GLTOOL_H
