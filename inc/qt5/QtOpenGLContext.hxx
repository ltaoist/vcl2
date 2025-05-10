/* comment */
#pragma once

#include <vcl/opengl/OpenGLContext.hxx>

class QWindow;
class QOpenGLContext;

class QtOpenGLContext final : public OpenGLContext
{
public:
    virtual void initWindow() override;

private:
    virtual const GLWindow& getOpenGLWindow() const override { return m_aGLWin; }
    virtual GLWindow& getModifiableOpenGLWindow() override { return m_aGLWin; }
    virtual bool ImplInit() override;

    virtual void makeCurrent() override;
    virtual void destroyCurrentContext() override;
    virtual bool isCurrent() override;
    virtual bool isAnyCurrent() override;
    virtual void resetCurrent() override;
    virtual void swapBuffers() override;

    static bool g_bAnyCurrent;

    GLWindow m_aGLWin;

    QWindow* m_pWindow;
    QOpenGLContext* m_pContext;
};
