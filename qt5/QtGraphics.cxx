/* comment */
#include <QtGraphics.hxx>

#include <QtData.hxx>
#include <QtFont.hxx>
#include <QtFrame.hxx>
#include <QtGraphics_Controls.hxx>
#include <QtPainter.hxx>

#include <QtGui/QImage>
#include <QtGui/QPainter>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QtGraphics::QtGraphics( QtFrame *pFrame, QImage *pQImage )
    : m_pFrame( pFrame )
    , m_pTextStyle{ nullptr, }
    , m_aTextColor( 0x00, 0x00, 0x00 )
{
    m_pBackend = std::make_unique<QtGraphicsBackend>(m_pFrame, pQImage);

    if (!initWidgetDrawBackends(false))
    {
        if (!QtData::noNativeControls())
            m_pWidgetDraw.reset(new QtGraphics_Controls(*this));
    }
    if (m_pFrame)
        setDevicePixelRatioF(m_pFrame->devicePixelRatioF());
}

QtGraphics::~QtGraphics() { ReleaseFonts(); }

void QtGraphics::ChangeQImage(QImage* pQImage)
{
    m_pBackend->setQImage(pQImage);
    m_pBackend->ResetClipRegion();
}

SalGraphicsImpl* QtGraphics::GetImpl() const { return m_pBackend.get(); }

SystemGraphicsData QtGraphics::GetGraphicsData() const { return SystemGraphicsData(); }

#if ENABLE_CAIRO_CANVAS

bool QtGraphics::SupportsCairo() const { return false; }

cairo::SurfaceSharedPtr
QtGraphics::CreateSurface(const cairo::CairoSurfaceSharedPtr& /*rSurface*/) const
{
    return nullptr;
}

cairo::SurfaceSharedPtr QtGraphics::CreateSurface(const OutputDevice& /*rRefDevice*/, int /*x*/,
                                                  int /*y*/, int /*width*/, int /*height*/) const
{
    return nullptr;
}

cairo::SurfaceSharedPtr QtGraphics::CreateBitmapSurface(const OutputDevice& /*rRefDevice*/,
                                                        const BitmapSystemData& /*rData*/,
                                                        const Size& /*rSize*/) const
{
    return nullptr;
}

css::uno::Any QtGraphics::GetNativeSurfaceHandle(cairo::SurfaceSharedPtr& /*rSurface*/,
                                                 const basegfx::B2ISize& /*rSize*/) const
{
    return css::uno::Any();
}

#endif

void QtGraphics::handleDamage(const tools::Rectangle& rDamagedRegion)
{
    assert(m_pWidgetDraw);
    assert(dynamic_cast<QtGraphics_Controls*>(m_pWidgetDraw.get()));
    assert(!rDamagedRegion.IsEmpty());

    QImage* pImage = static_cast<QtGraphics_Controls*>(m_pWidgetDraw.get())->getImage();
    QImage blit(*pImage);
    blit.setDevicePixelRatio(1);
    QtPainter aPainter(*m_pBackend);
    aPainter.drawImage(QPoint(rDamagedRegion.Left(), rDamagedRegion.Top()), blit);
    aPainter.update(toQRect(rDamagedRegion));
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
