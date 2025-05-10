/* comment */
#pragma once

#include <sal/config.h>

#include <font/LogicalFontInstance.hxx>

#include <QtGui/QFont>

#include "QtFontFace.hxx"

class QtFont final : public QFont, public LogicalFontInstance
{
    friend rtl::Reference<LogicalFontInstance>
    QtFontFace::CreateFontInstance(const vcl::font::FontSelectPattern&) const;

    bool GetGlyphOutline(sal_GlyphId, basegfx::B2DPolyPolygon&, bool) const override;
    bool ImplGetGlyphBoundRect(sal_GlyphId, tools::Rectangle&, bool) const override;

    explicit QtFont(const vcl::font::PhysicalFontFace&, const vcl::font::FontSelectPattern&);
};

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
