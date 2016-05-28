#include "SyncTextureSprite.h"
#include "../Graphic/GraphicPrivate.h"
#include "../Utils.h"
#include <QQuickWindow>

static GLfloat tex[8], vtx[8];
static QOpenGLShaderProgram *program = nullptr;

namespace
{
    const char *vShaderCode =
        "attribute mediump vec4 VtxCoord;\n"
        "attribute mediump vec2 TexCoord;\n"
        "varying mediump vec2 TexCoordOut;\n"
        "void main(void)\n"
        "{\n"
        "    gl_Position = VtxCoord;\n"
        "    TexCoordOut = TexCoord;\n"
        "}\n";

    const char *fShaderCode =
        "varying mediump vec2 TexCoordOut;\n"
        "uniform sampler2D SamplerP;\n"
        "void main(void)\n"
        "{\n"
        "    lowp vec4 p;\n"
        "    p = texture2D(SamplerP, TexCoordOut);\n"
        "    if (p.a != 0.0) {\n"
        "        p.r /= p.a;\n"
        "        p.g /= p.a;\n"
        "        p.b /= p.a;\n"
        "        gl_FragColor = vec4(p.b, p.g, p.r, p.a);\n"
        "    } else {\n"
        "        gl_FragColor = vec4(0.0, 0.0, 0.0, 0.0);\n"
        "    }\n"
        "}";
}

static QOpenGLShaderProgram &shaderProgram()
{
    if (program) return *program;
    program = new QOpenGLShaderProgram;
    program->addShaderFromSourceCode(QOpenGLShader::Vertex, vShaderCode);
    program->addShaderFromSourceCode(QOpenGLShader::Fragment, fShaderCode);
    program->bindAttributeLocation("VtxCoord", 0);
    program->bindAttributeLocation("TexCoord", 1);
    program->bind();
    program->setUniformValue("SamplerP", 0);
    tex[0] = 0; tex[1] = 0;
    tex[2] = 1; tex[3] = 0;
    tex[4] = 0; tex[5] = 1;
    tex[6] = 1; tex[7] = 1;
    return *program;
}

static void loadTexture(QOpenGLFunctions *glFunctions, GLuint texture, int width, int height, quint8 *data, int alignment)
{
    glFunctions->glBindTexture(GL_TEXTURE_2D, texture);
    glFunctions->glPixelStorei(GL_UNPACK_ALIGNMENT, alignment);
    glFunctions->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glFunctions->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFunctions->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glFunctions->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glFunctions->glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
}

static void drawTexture(QOpenGLFunctions *glFunctions, GLuint *planes, QRectF dest, QRectF rect)
{
    QOpenGLShaderProgram &p = shaderProgram();
    p.bind();
    GLfloat h = 2 / rect.width(), v = 2 / rect.height();
    GLfloat l = dest.left()*h - 1, r = dest.right()*h - 1, t = 1 - dest.top()*v, b = 1 - dest.bottom()*v;
    vtx[0] = l; vtx[1] = t;
    vtx[2] = r; vtx[3] = t;
    vtx[4] = l; vtx[5] = b;
    vtx[6] = r; vtx[7] = b;
    p.setAttributeArray(0, vtx, 2);
    p.setAttributeArray(1, tex, 2);
    p.enableAttributeArray(0);
    p.enableAttributeArray(1);
    glFunctions->glActiveTexture(GL_TEXTURE0);
    glFunctions->glBindTexture(GL_TEXTURE_2D, planes[0]);
    glFunctions->glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

SyncTextureSprite::SyncTextureSprite(const Comment &comment, BLDanmaku *item) :
texture(0), item(item)
{
    glFunctions = item->window()->openglContext()->functions();
    QSize size = item->size();
	QFont font = GraphicPrivate::getFont(comment.font*GraphicPrivate::getScale(comment.mode, comment.date, size));
	QSize need = GraphicPrivate::getSize(comment.string, font);
	source = new QImage(GraphicPrivate::getCache(comment.string, comment.color, font, need, comment.isLocal()));
}

SyncTextureSprite::~SyncTextureSprite()
{
    qDebug() << "clear texture";
    if (texture)
        glFunctions->glDeleteTextures(1, &texture);
	delete source;
}

void SyncTextureSprite::draw(QPainter *painter, QRectF dest)
{
	if (!texture){
        glFunctions->glGenTextures(1, &texture);
        loadTexture(glFunctions, texture, source->width(), source->height(), source->bits(), 4);
		delete source;
		source = nullptr;
	}

	painter->beginNativePainting();
    QRect rect(QPoint(0, 0), item->size());
    glFunctions->glEnable(GL_BLEND);
    glFunctions->glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    drawTexture(glFunctions, &texture, dest, rect);
	painter->endNativePainting();
}

QSize SyncTextureSprite::getSize()
{
	return source ? source->size() : QSize();
}


