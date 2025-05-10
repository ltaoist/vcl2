/* comment */
#include <QtOpenGLContext.hxx>

#include <epoxy/gl.h>

#include <vcl/sysdata.hxx>
#include <opengl/zone.hxx>
#include <sal/log.hxx>

#include <window.h>

#include <QtObject.hxx>

#include <QtGui/QOpenGLContext>
#include <QtGui/QWindow>

bool QtOpenGLContext::g_bAnyCurrent = false;

void QtOpenGLContext::swapBuffers()
{
    OpenGLZone aZone;

    if (m_pContext && m_pWindow && m_pWindow->isExposed())
    {
        m_pContext->swapBuffers(m_pWindow);
    }

    BuffersSwapped();
}

void QtOpenGLContext::resetCurrent()
{
    clearCurrent();

    OpenGLZone aZone;

    if (m_pContext)
    {
        m_pContext->doneCurrent();
        g_bAnyCurrent = false;
    }
}

bool QtOpenGLContext::isCurrent()
{
    OpenGLZone aZone;
    return g_bAnyCurrent && (QOpenGLContext::currentContext() == m_pContext);
}

bool QtOpenGLContext::isAnyCurrent()
{
    OpenGLZone aZone;
    return g_bAnyCurrent && (QOpenGLContext::currentContext() != nullptr);
}

bool QtOpenGLContext::ImplInit()
{
    if (!m_pWindow)
    {
        SAL_WARN("vcl.opengl.qt", "failed to create window");
        return false;
    }

    m_pWindow->setSurfaceType(QSurface::OpenGLSurface);
    m_pWindow->create();

    m_pContext = new QOpenGLContext(m_pWindow);
    if (!m_pContext->create())
    {
        SAL_WARN("vcl.opengl.qt", "failed to create context");
        return false;
    }

    m_pContext->makeCurrent(m_pWindow);
    g_bAnyCurrent = true;

    bool bRet = InitGL();
    InitGLDebugging();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    registerAsCurrent();

    return bRet;
}

void QtOpenGLContext::makeCurrent()
{
    if (isCurrent())
        return;

    OpenGLZone aZone;

    clearCurrent();

    if (m_pContext && m_pWindow)
    {
        m_pContext->makeCurrent(m_pWindow);
        g_bAnyCurrent = true;
    }

    registerAsCurrent();
}

void QtOpenGLContext::destroyCurrentContext()
{
    OpenGLZone aZone;

    if (m_pContext)
    {
        m_pContext->doneCurrent();
        g_bAnyCurrent = false;
    }

    if (glGetError() != GL_NO_ERROR)
    {
        SAL_WARN("vcl.opengl.qt", "glError: " << glGetError());
    }
}

void QtOpenGLContext::initWindow()
{
    if (!m_pChildWindow)
    {
        SystemWindowData winData = generateWinData(mpWindow, mbRequestLegacyContext);
        m_pChildWindow = VclPtr<SystemChildWindow>::Create(mpWindow, 0, &winData, false);
    }

    if (m_pChildWindow)
    {
        InitChildWindow(m_pChildWindow.get());
    }

    m_pWindow
        = static_cast<QtObject*>(m_pChildWindow->ImplGetWindowImpl()->mpSysObj)->windowHandle();
}
