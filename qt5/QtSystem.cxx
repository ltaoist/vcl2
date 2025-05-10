/* comment */

#include <QtGui/QGuiApplication>
#include <QtGui/QScreen>

#include <tools/gen.hxx>
#include <QtSystem.hxx>
#include <QtTools.hxx>

unsigned int QtSystem::GetDisplayScreenCount() { return QGuiApplication::screens().size(); }

tools::Rectangle QtSystem::GetDisplayScreenPosSizePixel(unsigned int nScreen)
{
    QRect qRect = QGuiApplication::screens().at(nScreen)->geometry();
    return toRectangle(scaledQRect(qRect, qApp->devicePixelRatio()));
}

int QtSystem::ShowNativeDialog(const OUString&, const OUString&, const std::vector<OUString>&)
{
    return 0;
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
