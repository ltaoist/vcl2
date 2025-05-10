/* comment */
#pragma once

#include <vcl/bitmap.hxx>
#include <vcl/BitmapReadAccess.hxx>
#include <vcl/graph.hxx>

#include <com/sun/star/uno/Sequence.h>
#include <com/sun/star/beans/PropertyValue.hpp>
#include <com/sun/star/task/XStatusIndicator.hpp>

class JPEGWriter final
{
    SvStream&           mrStream;
    Bitmap::ScopedReadAccess mpReadAccess;
    sal_uInt8*          mpBuffer;
    bool                mbNative;
    bool                mbGreys;
    sal_Int32           mnQuality;
    sal_Int32           maChromaSubsampling;

    bool*               mpExpWasGrey;

    css::uno::Reference< css::task::XStatusIndicator > mxStatusIndicator;

public:
    JPEGWriter( SvStream& rStream,
                const css::uno::Sequence< css::beans::PropertyValue >* pFilterData,
                bool* pExportWasGrey );

    void*       GetScanline( tools::Long nY );
    bool    Write( const Graphic& rGraphic );

};

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
