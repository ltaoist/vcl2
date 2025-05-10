/* comment */
#pragma once

#include <sal/config.h>

#include <vclpluginapi.h>
#include <font/PhysicalFontFace.hxx>

#include <tools/ref.hxx>

#include <QtCore/QString>
#include <QtGui/QFont>

class FontAttributes;
namespace vcl::font
{
class FontSelectPattern;
}

class QtFontFace final : public vcl::font::PhysicalFontFace
{
public:
    static QtFontFace* fromQFont(const QFont& rFont);
    static QtFontFace* fromQFontDatabase(const QString& aFamily, const QString& aStyle);
    static void fillAttributesFromQFont(const QFont& rFont, FontAttributes& rFA);

    VCLPLUG_QT_PUBLIC static FontWeight toFontWeight(const int nWeight);
    VCLPLUG_QT_PUBLIC static FontWidth toFontWidth(const int nStretch);
    VCLPLUG_QT_PUBLIC static FontItalic toFontItalic(const QFont::Style eStyle);

    sal_IntPtr GetFontId() const override;

    QFont CreateFont() const;

    rtl::Reference<LogicalFontInstance>
    CreateFontInstance(const vcl::font::FontSelectPattern& rFSD) const override;

    hb_blob_t* GetHbTable(hb_tag_t nTag) const override;

private:
    typedef enum { Font, FontDB } FontIdType;

    QtFontFace(const QtFontFace&);
    QtFontFace(const FontAttributes&, QString rFontID, const FontIdType);

    const QString m_aFontId;
    const FontIdType m_eFontIdType;
};

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
