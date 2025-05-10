/* comment */
#ifndef INCLUDED_VCL_SOURCE_GRAPHIC_GRAPHIC_HXX
#define INCLUDED_VCL_SOURCE_GRAPHIC_GRAPHIC_HXX

#include <com/sun/star/graphic/XGraphic.hpp>
#include <com/sun/star/lang/XUnoTunnel.hpp>
#include <com/sun/star/awt/XBitmap.hpp>
#include <com/sun/star/graphic/XGraphicTransformer.hpp>

#include <graphic/UnoGraphicDescriptor.hxx>

#include <vcl/graph.hxx>

namespace unographic {

class Graphic final : public css::graphic::XGraphic,
                public css::awt::XBitmap,
                public css::lang::XUnoTunnel,
                public css::graphic::XGraphicTransformer,
                public ::unographic::GraphicDescriptor
{
public:
    Graphic();
    virtual ~Graphic() noexcept override;

    using ::unographic::GraphicDescriptor::init;
    void init(const ::Graphic& rGraphic);

    // XInterface
    virtual css::uno::Any SAL_CALL queryAggregation( const css::uno::Type & rType ) override;
    virtual css::uno::Any SAL_CALL queryInterface( const css::uno::Type & rType ) override;
    virtual void SAL_CALL acquire() noexcept override;
    virtual void SAL_CALL release() noexcept override;
private:
    // XServiceInfo
    virtual OUString SAL_CALL getImplementationName() override;
    virtual sal_Bool SAL_CALL supportsService( const OUString& ServiceName ) override;
    virtual css::uno::Sequence< OUString > SAL_CALL getSupportedServiceNames() override;

    // XTypeProvider
    virtual css::uno::Sequence< css::uno::Type > SAL_CALL getTypes(  ) override;
    virtual css::uno::Sequence< sal_Int8 > SAL_CALL getImplementationId(  ) override;

    // XGraphic
    virtual ::sal_Int8 SAL_CALL getType(  ) override;

    // XBitmap
    virtual css::awt::Size SAL_CALL getSize(  ) override;
    virtual css::uno::Sequence< ::sal_Int8 > SAL_CALL getDIB(  ) override;
    virtual css::uno::Sequence< ::sal_Int8 > SAL_CALL getMaskDIB(  ) override;

    // XUnoTunnel
    virtual sal_Int64 SAL_CALL getSomething( const css::uno::Sequence< sal_Int8 >& rId ) override;

    // XGraphicTransformer
    virtual css::uno::Reference< css::graphic::XGraphic > SAL_CALL colorChange(
        const css::uno::Reference< css::graphic::XGraphic >& rGraphic,
        sal_Int32 nColorFrom, sal_Int8 nTolerance, sal_Int32 nColorTo, sal_Int8 nAlphaTo ) override;

    virtual css::uno::Reference< css::graphic::XGraphic > SAL_CALL applyDuotone(
        const css::uno::Reference< css::graphic::XGraphic >& rGraphic,
        sal_Int32 nColorOne, sal_Int32 nColorTwo ) override;

    virtual css::uno::Reference< css::graphic::XGraphic > SAL_CALL applyBrightnessContrast(
        const css::uno::Reference< css::graphic::XGraphic >& rxGraphic,
        sal_Int32 nBrightness, sal_Int32 nContrast, sal_Bool mso ) override;

    ::Graphic maGraphic;
};

}

#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
