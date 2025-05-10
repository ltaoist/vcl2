/* comment */
#include <QtTools.hxx>

#include <cairo.h>

#include <tools/stream.hxx>
#include <vcl/event.hxx>
#include <vcl/image.hxx>
#include <vcl/filter/PngImageWriter.hxx>

#include <QtGui/QImage>

void CairoDeleter::operator()(cairo_surface_t* pSurface) const { cairo_surface_destroy(pSurface); }

sal_uInt16 GetKeyModCode(Qt::KeyboardModifiers eKeyModifiers)
{
    sal_uInt16 nCode = 0;
    if (eKeyModifiers & Qt::ShiftModifier)
        nCode |= KEY_SHIFT;
    if (eKeyModifiers & Qt::ControlModifier)
        nCode |= KEY_MOD1;
    if (eKeyModifiers & Qt::AltModifier)
        nCode |= KEY_MOD2;
    if (eKeyModifiers & Qt::MetaModifier)
        nCode |= KEY_MOD3;
    return nCode;
}

sal_uInt16 GetMouseModCode(Qt::MouseButtons eButtons)
{
    sal_uInt16 nCode = 0;
    if (eButtons & Qt::LeftButton)
        nCode |= MOUSE_LEFT;
    if (eButtons & Qt::MiddleButton)
        nCode |= MOUSE_MIDDLE;
    if (eButtons & Qt::RightButton)
        nCode |= MOUSE_RIGHT;
    return nCode;
}

Qt::DropActions toQtDropActions(sal_Int8 dragOperation)
{
    Qt::DropActions eRet = Qt::IgnoreAction;
    if (dragOperation & css::datatransfer::dnd::DNDConstants::ACTION_COPY)
        eRet |= Qt::CopyAction;
    if (dragOperation & css::datatransfer::dnd::DNDConstants::ACTION_MOVE)
        eRet |= Qt::MoveAction;
    if (dragOperation & css::datatransfer::dnd::DNDConstants::ACTION_LINK)
        eRet |= Qt::LinkAction;
    return eRet;
}

sal_Int8 toVclDropActions(Qt::DropActions dragOperation)
{
    sal_Int8 nRet(0);
    if (dragOperation & Qt::CopyAction)
        nRet |= css::datatransfer::dnd::DNDConstants::ACTION_COPY;
    if (dragOperation & Qt::MoveAction)
        nRet |= css::datatransfer::dnd::DNDConstants::ACTION_MOVE;
    if (dragOperation & Qt::LinkAction)
        nRet |= css::datatransfer::dnd::DNDConstants::ACTION_LINK;
    return nRet;
}

sal_Int8 toVclDropAction(Qt::DropAction dragOperation)
{
    sal_Int8 nRet(0);
    if (dragOperation == Qt::CopyAction)
        nRet = css::datatransfer::dnd::DNDConstants::ACTION_COPY;
    else if (dragOperation == Qt::MoveAction)
        nRet = css::datatransfer::dnd::DNDConstants::ACTION_MOVE;
    else if (dragOperation == Qt::LinkAction)
        nRet = css::datatransfer::dnd::DNDConstants::ACTION_LINK;
    return nRet;
}

Qt::DropAction getPreferredDropAction(sal_Int8 dragOperation)
{
    Qt::DropAction eAct = Qt::IgnoreAction;
    if (dragOperation & css::datatransfer::dnd::DNDConstants::ACTION_MOVE)
        eAct = Qt::MoveAction;
    else if (dragOperation & css::datatransfer::dnd::DNDConstants::ACTION_COPY)
        eAct = Qt::CopyAction;
    else if (dragOperation & css::datatransfer::dnd::DNDConstants::ACTION_LINK)
        eAct = Qt::LinkAction;
    return eAct;
}

QImage toQImage(const Image& rImage)
{
    QImage aImage;

    if (!!rImage)
    {
        SvMemoryStream aMemStm;
        auto rBitmapEx = rImage.GetBitmapEx();
        vcl::PngImageWriter aWriter(aMemStm);
        aWriter.write(rBitmapEx);
        aImage.loadFromData(static_cast<const uchar*>(aMemStm.GetData()), aMemStm.TellEnd());
    }

    return aImage;
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
