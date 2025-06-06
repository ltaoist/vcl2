/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file incorporates work covered by the following license notice:
 *
 *   Licensed to the Apache Software Foundation (ASF) under one or more
 *   contributor license agreements. See the NOTICE file distributed
 *   with this work for additional information regarding copyright
 *   ownership. The ASF licenses this file to you under the Apache
 *   License, Version 2.0 (the "License"); you may not use this file
 *   except in compliance with the License. You may obtain a copy of
 *   the License at http://www.apache.org/licenses/LICENSE-2.0 .
 */

#include <tools/stream.hxx>
#include <tools/vcompat.hxx>
#include <tools/gen.hxx>
#include <unotools/configmgr.hxx>
#include <unotools/fontcfg.hxx>
#include <unotools/fontdefs.hxx>
#include <o3tl/hash_combine.hxx>
#include <i18nlangtag/mslangid.hxx>

#include <vcl/font.hxx>
#include <vcl/svapp.hxx>
#include <vcl/outdev.hxx>
#include <vcl/virdev.hxx>

#include <impfont.hxx>
#include <fontattributes.hxx>
#include <fontsubset.hxx>
#include <sft.hxx>

#include <algorithm>
#include <string_view>

#include <vcl/TypeSerializer.hxx>

#ifdef _WIN32
#include <vcl/metric.hxx>
#endif

using namespace vcl;

namespace
{
    Font::ImplType& GetGlobalDefault()
    {
        static Font::ImplType gDefault;
        return gDefault;
    }
}

Font::Font() : mpImplFont(GetGlobalDefault())
{
}

Font::Font( const vcl::Font& rFont ) : mpImplFont( rFont.mpImplFont )
{
}

Font::Font( vcl::Font&& rFont ) noexcept : mpImplFont( std::move(rFont.mpImplFont) )
{
}

Font::Font( const OUString& rFamilyName, const Size& rSize )
{
    if (const_cast<const ImplType&>(mpImplFont)->maFamilyName != rFamilyName
        || const_cast<const ImplType&>(mpImplFont)->maAverageFontSize != rSize)
    {
        mpImplFont->SetFamilyName( rFamilyName );
        mpImplFont->SetFontSize( rSize );
    }
}

Font::Font( const OUString& rFamilyName, const OUString& rStyleName, const Size& rSize )
{
    if (const_cast<const ImplType&>(mpImplFont)->maFamilyName != rFamilyName
        || const_cast<const ImplType&>(mpImplFont)->maStyleName != rStyleName
        || const_cast<const ImplType&>(mpImplFont)->maAverageFontSize != rSize)
    {
        mpImplFont->SetFamilyName( rFamilyName );
        mpImplFont->SetStyleName( rStyleName );
        mpImplFont->SetFontSize( rSize );
    }
}

Font::Font( FontFamily eFamily, const Size& rSize )
{
    if (const_cast<const ImplType&>(mpImplFont)->meFamily != eFamily
        || const_cast<const ImplType&>(mpImplFont)->maAverageFontSize != rSize)
    {
        mpImplFont->SetFamilyType( eFamily );
        mpImplFont->SetFontSize( rSize );
    }
}

Font::~Font()
{
}

void Font::SetColor( const Color& rColor )
{
    if (const_cast<const ImplType&>(mpImplFont)->maColor != rColor)
    {
        mpImplFont->maColor = rColor;
    }
}

void Font::SetFillColor( const Color& rColor )
{
    if (const_cast<const ImplType&>(mpImplFont)->maFillColor != rColor)
    {
        mpImplFont->maFillColor = rColor;
        if ( rColor.IsTransparent() )
            mpImplFont->mbTransparent = true;
    }
}

void Font::SetTransparent( bool bTransparent )
{
    if (const_cast<const ImplType&>(mpImplFont)->mbTransparent != bTransparent)
        mpImplFont->mbTransparent = bTransparent;
}

void Font::SetAlignment( TextAlign eAlign )
{
    if (const_cast<const ImplType&>(mpImplFont)->meAlign != eAlign)
        mpImplFont->SetAlignment(eAlign);
}

void Font::SetFamilyName( const OUString& rFamilyName )
{
    if (const_cast<const ImplType&>(mpImplFont)->maFamilyName != rFamilyName)
        mpImplFont->SetFamilyName( rFamilyName );
}

void Font::SetStyleName( const OUString& rStyleName )
{
    if (const_cast<const ImplType&>(mpImplFont)->maStyleName != rStyleName)
        mpImplFont->maStyleName = rStyleName;
}

void Font::SetFontSize( const Size& rSize )
{
    if (const_cast<const ImplType&>(mpImplFont)->GetFontSize() != rSize)
        mpImplFont->SetFontSize( rSize );
}

void Font::SetFamily( FontFamily eFamily )
{
    if (const_cast<const ImplType&>(mpImplFont)->GetFamilyTypeNoAsk() != eFamily)
        mpImplFont->SetFamilyType( eFamily );
}

void Font::SetCharSet( rtl_TextEncoding eCharSet )
{
    if (const_cast<const ImplType&>(mpImplFont)->GetCharSet() != eCharSet)
    {
        mpImplFont->SetCharSet( eCharSet );

        if ( eCharSet == RTL_TEXTENCODING_SYMBOL )
            mpImplFont->SetSymbolFlag( true );
        else
            mpImplFont->SetSymbolFlag( false );
    }
}

bool Font::IsSymbolFont() const
{
    return mpImplFont->IsSymbolFont();
}

void Font::SetSymbolFlag( bool bSymbol )
{
    if (const_cast<const ImplType&>(mpImplFont)->mbSymbolFlag != bSymbol)
    {
        mpImplFont->SetSymbolFlag( bSymbol );

        if ( IsSymbolFont() )
        {
            mpImplFont->SetCharSet( RTL_TEXTENCODING_SYMBOL );
        }
        else
        {
            if ( std::as_const(mpImplFont)->GetCharSet() == RTL_TEXTENCODING_SYMBOL )
                mpImplFont->SetCharSet( RTL_TEXTENCODING_DONTKNOW );
        }
    }
}

void Font::SetLanguageTag( const LanguageTag& rLanguageTag )
{
    if (const_cast<const ImplType&>(mpImplFont)->maLanguageTag != rLanguageTag)
        mpImplFont->maLanguageTag = rLanguageTag;
}

void Font::SetCJKContextLanguageTag( const LanguageTag& rLanguageTag )
{
    if (const_cast<const ImplType&>(mpImplFont)->maCJKLanguageTag != rLanguageTag)
        mpImplFont->maCJKLanguageTag = rLanguageTag;
}

void Font::SetLanguage( LanguageType eLanguage )
{
    if (const_cast<const ImplType&>(mpImplFont)->maLanguageTag.getLanguageType(false) != eLanguage)
        mpImplFont->maLanguageTag.reset( eLanguage);
}

void Font::SetCJKContextLanguage( LanguageType eLanguage )
{
    if (const_cast<const ImplType&>(mpImplFont)->maCJKLanguageTag.getLanguageType(false) != eLanguage)
        mpImplFont->maCJKLanguageTag.reset( eLanguage);
}

void Font::SetPitch( FontPitch ePitch )
{
    if (const_cast<const ImplType&>(mpImplFont)->GetPitchNoAsk() != ePitch)
        mpImplFont->SetPitch( ePitch );
}

void Font::SetOrientation( Degree10 nOrientation )
{
    if (const_cast<const ImplType&>(mpImplFont)->mnOrientation != nOrientation)
        mpImplFont->mnOrientation = nOrientation;
}

void Font::SetVertical( bool bVertical )
{
    if (const_cast<const ImplType&>(mpImplFont)->mbVertical != bVertical)
        mpImplFont->mbVertical = bVertical;
}

void Font::SetKerning( FontKerning eKerning )
{
    if (const_cast<const ImplType&>(mpImplFont)->meKerning != eKerning)
        mpImplFont->meKerning = eKerning;
}

bool Font::IsKerning() const
{
    return mpImplFont->meKerning != FontKerning::NONE;
}

void Font::SetFixKerning( short nSpacing )
{
    if (const_cast<const ImplType&>(mpImplFont)->mnSpacing != nSpacing)
        mpImplFont->mnSpacing = nSpacing;
}

short Font::GetFixKerning() const
{
    return mpImplFont->mnSpacing;
}

bool Font::IsFixKerning() const
{
    return mpImplFont->mnSpacing != 0;
}

void Font::SetWeight( FontWeight eWeight )
{
    if (const_cast<const ImplType&>(mpImplFont)->GetWeightNoAsk() != eWeight)
        mpImplFont->SetWeight( eWeight );
}

void Font::SetWidthType( FontWidth eWidth )
{
    if (const_cast<const ImplType&>(mpImplFont)->GetWidthTypeNoAsk() != eWidth)
        mpImplFont->SetWidthType( eWidth );
}

void Font::SetItalic( FontItalic eItalic )
{
    if (const_cast<const ImplType&>(mpImplFont)->GetItalicNoAsk() != eItalic)
        mpImplFont->SetItalic( eItalic );
}

void Font::SetOutline( bool bOutline )
{
    if (const_cast<const ImplType&>(mpImplFont)->mbOutline != bOutline)
        mpImplFont->mbOutline = bOutline;
}

void Font::SetShadow( bool bShadow )
{
    if (const_cast<const ImplType&>(mpImplFont)->mbShadow != bShadow)
        mpImplFont->mbShadow = bShadow;
}

void Font::SetUnderline( FontLineStyle eUnderline )
{
    if (const_cast<const ImplType&>(mpImplFont)->meUnderline != eUnderline)
        mpImplFont->meUnderline = eUnderline;
}

void Font::SetOverline( FontLineStyle eOverline )
{
    if (const_cast<const ImplType&>(mpImplFont)->meOverline != eOverline)
        mpImplFont->meOverline = eOverline;
}

void Font::SetStrikeout( FontStrikeout eStrikeout )
{
    if (const_cast<const ImplType&>(mpImplFont)->meStrikeout != eStrikeout)
        mpImplFont->meStrikeout = eStrikeout;
}

void Font::SetRelief( FontRelief eRelief )
{
    if (const_cast<const ImplType&>(mpImplFont)->meRelief != eRelief)
        mpImplFont->meRelief = eRelief;
}

void Font::SetEmphasisMark( FontEmphasisMark eEmphasisMark )
{
    if (const_cast<const ImplType&>(mpImplFont)->meEmphasisMark != eEmphasisMark )
        mpImplFont->meEmphasisMark = eEmphasisMark;
}

void Font::SetWordLineMode( bool bWordLine )
{
    if (const_cast<const ImplType&>(mpImplFont)->mbWordLine != bWordLine)
        mpImplFont->mbWordLine = bWordLine;
}

Font& Font::operator=( const vcl::Font& rFont )
{
    mpImplFont = rFont.mpImplFont;
    return *this;
}

Font& Font::operator=( vcl::Font&& rFont ) noexcept
{
    mpImplFont = std::move(rFont.mpImplFont);
    return *this;
}

FontEmphasisMark Font::GetEmphasisMarkStyle() const
{
    FontEmphasisMark nEmphasisMark = GetEmphasisMark();

    // If no Position is set, then calculate the default position, which
    // depends on the language
    if (!(nEmphasisMark & (FontEmphasisMark::PosAbove | FontEmphasisMark::PosBelow)))
    {
        LanguageType eLang = GetLanguage();
        // In Chinese Simplified the EmphasisMarks are below/left
        if (MsLangId::isSimplifiedChinese(eLang))
        {
            nEmphasisMark |= FontEmphasisMark::PosBelow;
        }
        else
        {
            eLang = GetCJKContextLanguage();

            // In Chinese Simplified the EmphasisMarks are below/left
            if (MsLangId::isSimplifiedChinese(eLang))
                nEmphasisMark |= FontEmphasisMark::PosBelow;
            else
                nEmphasisMark |= FontEmphasisMark::PosAbove;
        }
    }

    return nEmphasisMark;
}

bool Font::operator==( const vcl::Font& rFont ) const
{
    return mpImplFont == rFont.mpImplFont;
}

bool Font::EqualIgnoreColor( const vcl::Font& rFont ) const
{
    return mpImplFont->EqualIgnoreColor( *rFont.mpImplFont );
}

size_t Font::GetHashValueIgnoreColor() const
{
    return mpImplFont->GetHashValueIgnoreColor();
}

void Font::Merge( const vcl::Font& rFont )
{
    if ( !rFont.GetFamilyName().isEmpty() )
    {
        SetFamilyName( rFont.GetFamilyName() );
        SetStyleName( rFont.GetStyleName() );
        SetCharSet( GetCharSet() );
        SetLanguageTag( rFont.GetLanguageTag() );
        SetCJKContextLanguageTag( rFont.GetCJKContextLanguageTag() );
        // don't use access methods here, might lead to AskConfig(), if DONTKNOW
        SetFamily( rFont.mpImplFont->GetFamilyTypeNoAsk() );
        SetPitch( rFont.mpImplFont->GetPitchNoAsk() );
    }

    // don't use access methods here, might lead to AskConfig(), if DONTKNOW
    if ( rFont.mpImplFont->GetWeightNoAsk() != WEIGHT_DONTKNOW )
        SetWeight( rFont.GetWeight() );
    if ( rFont.mpImplFont->GetItalicNoAsk() != ITALIC_DONTKNOW )
        SetItalic( rFont.GetItalic() );
    if ( rFont.mpImplFont->GetWidthTypeNoAsk() != WIDTH_DONTKNOW )
        SetWidthType( rFont.GetWidthType() );

    if ( rFont.GetFontSize().Height() )
        SetFontSize( rFont.GetFontSize() );
    if ( rFont.GetUnderline() != LINESTYLE_DONTKNOW )
    {
        SetUnderline( rFont.GetUnderline() );
        SetWordLineMode( rFont.IsWordLineMode() );
    }
    if ( rFont.GetOverline() != LINESTYLE_DONTKNOW )
    {
        SetOverline( rFont.GetOverline() );
        SetWordLineMode( rFont.IsWordLineMode() );
    }
    if ( rFont.GetStrikeout() != STRIKEOUT_DONTKNOW )
    {
        SetStrikeout( rFont.GetStrikeout() );
        SetWordLineMode( rFont.IsWordLineMode() );
    }

    // Defaults?
    SetOrientation( rFont.GetOrientation() );
    SetVertical( rFont.IsVertical() );
    SetEmphasisMark( rFont.GetEmphasisMark() );
    SetKerning( rFont.IsKerning() ? FontKerning::FontSpecific : FontKerning::NONE );
    SetOutline( rFont.IsOutline() );
    SetShadow( rFont.IsShadow() );
    SetRelief( rFont.GetRelief() );
}

void Font::GetFontAttributes( FontAttributes& rAttrs ) const
{
    rAttrs.SetFamilyName( mpImplFont->GetFamilyName() );
    rAttrs.SetStyleName( mpImplFont->maStyleName );
    rAttrs.SetFamilyType( mpImplFont->GetFamilyTypeNoAsk() );
    rAttrs.SetPitch( mpImplFont->GetPitchNoAsk() );
    rAttrs.SetItalic( mpImplFont->GetItalicNoAsk() );
    rAttrs.SetWeight( mpImplFont->GetWeightNoAsk() );
    rAttrs.SetWidthType( WIDTH_DONTKNOW );
    rAttrs.SetSymbolFlag( mpImplFont->GetCharSet() == RTL_TEXTENCODING_SYMBOL );
}

// tdf#127471 for corrections on EMF/WMF we need the AvgFontWidth in Windows-specific notation
tools::Long Font::GetOrCalculateAverageFontWidth() const
{
    if(0 == mpImplFont->GetCalculatedAverageFontWidth())
    {
        // VirtualDevice is not thread safe
        SolarMutexGuard aGuard;

        // create unscaled copy of font (this), a VirtualDevice and set it there
        vcl::Font aUnscaledFont(*this);
        ScopedVclPtr<VirtualDevice> pTempVirtualDevice(VclPtr<VirtualDevice>::Create());
        aUnscaledFont.SetAverageFontWidth(0);
        pTempVirtualDevice->SetFont(aUnscaledFont);

#ifdef _WIN32
        // on Windows systems use FontMetric to get/create AverageFontWidth from system
        const FontMetric aMetric(pTempVirtualDevice->GetFontMetric());
        const_cast<Font*>(this)->mpImplFont->SetCalculatedAverageFontWidth(aMetric.GetAverageFontWidth());
#else
        // On non-Windows systems we need to calculate AvgFontWidth
        // as close as possible (discussion see documentation in task),
        // so calculate it. For discussion of method used, see task
        // buffer measure string creation, will always use the same
        static constexpr OUStringLiteral aMeasureString
            = u"\u0020\u0021\u0022\u0023\u0024\u0025\u0026\u0027"
               "\u0028\u0029\u002A\u002B\u002C\u002D\u002E\u002F"
               "\u0030\u0031\u0032\u0033\u0034\u0035\u0036\u0037"
               "\u0038\u0039\u003A\u003B\u003C\u003D\u003E\u003F"
               "\u0040\u0041\u0042\u0043\u0044\u0045\u0046\u0047"
               "\u0048\u0049\u004A\u004B\u004C\u004D\u004E\u004F"
               "\u0050\u0051\u0052\u0053\u0054\u0055\u0056\u0057"
               "\u0058\u0059\u005A\u005B\u005C\u005D\u005E\u005F"
               "\u0060\u0061\u0062\u0063\u0064\u0065\u0066\u0067"
               "\u0068\u0069\u006A\u006B\u006C\u006D\u006E\u006F"
               "\u0070\u0071\u0072\u0073\u0074\u0075\u0076\u0077"
               "\u0078\u0079\u007A\u007B\u007C\u007D\u007E";

        const double fAverageFontWidth(
            pTempVirtualDevice->GetTextWidth(aMeasureString) /
            static_cast<double>(aMeasureString.getLength()));
        const_cast<Font*>(this)->mpImplFont->SetCalculatedAverageFontWidth(basegfx::fround(fAverageFontWidth));
#endif
    }

    return mpImplFont->GetCalculatedAverageFontWidth();
}

SvStream& ReadImplFont( SvStream& rIStm, ImplFont& rImplFont, tools::Long& rnNormedFontScaling )
{
    VersionCompatRead aCompat( rIStm );
    sal_uInt16      nTmp16(0);
    sal_Int16       nTmps16(0);
    bool            bTmp(false);
    sal_uInt8       nTmp8(0);

    rImplFont.SetFamilyName( rIStm.ReadUniOrByteString(rIStm.GetStreamCharSet()) );
    rImplFont.maStyleName = rIStm.ReadUniOrByteString(rIStm.GetStreamCharSet());
    TypeSerializer aSerializer(rIStm);
    aSerializer.readSize(rImplFont.maAverageFontSize);

    static const bool bFuzzing = utl::ConfigManager::IsFuzzing();
    if (bFuzzing)
    {
        if (rImplFont.maAverageFontSize.Width() > 8192)
        {
            SAL_WARN("vcl.gdi", "suspicious average width of: " << rImplFont.maAverageFontSize.Width());
            rImplFont.maAverageFontSize.setWidth(8192);
        }
    }

    rIStm.ReadUInt16( nTmp16 ); rImplFont.SetCharSet( static_cast<rtl_TextEncoding>(nTmp16) );
    rIStm.ReadUInt16( nTmp16 ); rImplFont.SetFamilyType( static_cast<FontFamily>(nTmp16) );
    rIStm.ReadUInt16( nTmp16 ); rImplFont.SetPitch( static_cast<FontPitch>(nTmp16) );
    rIStm.ReadUInt16( nTmp16 ); rImplFont.SetWeight( static_cast<FontWeight>(nTmp16) );
    rIStm.ReadUInt16( nTmp16 ); rImplFont.meUnderline = static_cast<FontLineStyle>(nTmp16);
    rIStm.ReadUInt16( nTmp16 ); rImplFont.meStrikeout = static_cast<FontStrikeout>(nTmp16);
    rIStm.ReadUInt16( nTmp16 ); rImplFont.SetItalic( static_cast<FontItalic>(nTmp16) );
    rIStm.ReadUInt16( nTmp16 ); rImplFont.maLanguageTag.reset( LanguageType(nTmp16) );
    rIStm.ReadUInt16( nTmp16 ); rImplFont.meWidthType = static_cast<FontWidth>(nTmp16);

    rIStm.ReadInt16( nTmps16 ); rImplFont.mnOrientation = Degree10(nTmps16);

    rIStm.ReadCharAsBool( bTmp ); rImplFont.mbWordLine = bTmp;
    rIStm.ReadCharAsBool( bTmp ); rImplFont.mbOutline = bTmp;
    rIStm.ReadCharAsBool( bTmp ); rImplFont.mbShadow = bTmp;
    rIStm.ReadUChar( nTmp8 ); rImplFont.meKerning = static_cast<FontKerning>(nTmp8);

    if( aCompat.GetVersion() >= 2 )
    {
        rIStm.ReadUChar( nTmp8 );     rImplFont.meRelief = static_cast<FontRelief>(nTmp8);
        rIStm.ReadUInt16( nTmp16 );   rImplFont.maCJKLanguageTag.reset( LanguageType(nTmp16) );
        rIStm.ReadCharAsBool( bTmp ); rImplFont.mbVertical = bTmp;
        rIStm.ReadUInt16( nTmp16 );   rImplFont.meEmphasisMark = static_cast<FontEmphasisMark>(nTmp16);
    }

    if( aCompat.GetVersion() >= 3 )
    {
        rIStm.ReadUInt16( nTmp16 ); rImplFont.meOverline = static_cast<FontLineStyle>(nTmp16);
    }

    // tdf#127471 read NormedFontScaling
    if( aCompat.GetVersion() >= 4 )
    {
        sal_Int32 nNormedFontScaling(0);
        rIStm.ReadInt32(nNormedFontScaling);
        rnNormedFontScaling = nNormedFontScaling;
    }

    if( aCompat.GetVersion() >= 5 )
    {
        rIStm.ReadInt16( nTmps16 );
        rImplFont.mnSpacing = nTmps16;
    }

    // Relief
    // CJKContextLanguage

    return rIStm;
}

SvStream& WriteImplFont( SvStream& rOStm, const ImplFont& rImplFont, tools::Long nNormedFontScaling )
{
    // tdf#127471 increase to version 4
    // tdf#66819 increase to version 5
    VersionCompatWrite aCompat( rOStm, 5 );

    TypeSerializer aSerializer(rOStm);
    rOStm.WriteUniOrByteString( rImplFont.GetFamilyName(), rOStm.GetStreamCharSet() );
    rOStm.WriteUniOrByteString( rImplFont.GetStyleName(), rOStm.GetStreamCharSet() );
    aSerializer.writeSize(rImplFont.maAverageFontSize);

    rOStm.WriteUInt16( GetStoreCharSet( rImplFont.GetCharSet() ) );
    rOStm.WriteUInt16( rImplFont.GetFamilyTypeNoAsk() );
    rOStm.WriteUInt16( rImplFont.GetPitchNoAsk() );
    rOStm.WriteUInt16( rImplFont.GetWeightNoAsk() );
    rOStm.WriteUInt16( rImplFont.meUnderline );
    rOStm.WriteUInt16( rImplFont.meStrikeout );
    rOStm.WriteUInt16( rImplFont.GetItalicNoAsk() );
    rOStm.WriteUInt16( static_cast<sal_uInt16>(rImplFont.maLanguageTag.getLanguageType( false)) );
    rOStm.WriteUInt16( rImplFont.GetWidthTypeNoAsk() );

    rOStm.WriteInt16( rImplFont.mnOrientation.get() );

    rOStm.WriteBool( rImplFont.mbWordLine );
    rOStm.WriteBool( rImplFont.mbOutline );
    rOStm.WriteBool( rImplFont.mbShadow );
    rOStm.WriteUChar( static_cast<sal_uInt8>(rImplFont.meKerning) );

    // new in version 2
    rOStm.WriteUChar( static_cast<unsigned char>(rImplFont.meRelief) );
    rOStm.WriteUInt16( static_cast<sal_uInt16>(rImplFont.maCJKLanguageTag.getLanguageType( false)) );
    rOStm.WriteBool( rImplFont.mbVertical );
    rOStm.WriteUInt16( static_cast<sal_uInt16>(rImplFont.meEmphasisMark) );

    // new in version 3
    rOStm.WriteUInt16( rImplFont.meOverline );

    // new in version 4, NormedFontScaling
    rOStm.WriteInt32(nNormedFontScaling);

    // new in version 5
    rOStm.WriteInt16( rImplFont.mnSpacing );
    return rOStm;
}

SvStream& ReadFont( SvStream& rIStm, vcl::Font& rFont )
{
    // tdf#127471 try to read NormedFontScaling
    tools::Long nNormedFontScaling(0);
    SvStream& rRetval(ReadImplFont( rIStm, *rFont.mpImplFont, nNormedFontScaling ));

    if (nNormedFontScaling > 0)
    {
#ifdef _WIN32
        // we run on windows and a NormedFontScaling was written
        if(rFont.GetFontSize().getWidth() == nNormedFontScaling)
        {
            // the writing producer was running on a non-windows system, adapt to needed windows
            // system-specific pre-multiply
            const tools::Long nHeight(std::max<tools::Long>(rFont.GetFontSize().getHeight(), 0));
            sal_uInt32 nScaledWidth(0);

            if(nHeight > 0)
            {
                vcl::Font aUnscaledFont(rFont);
                aUnscaledFont.SetAverageFontWidth(0);
                const FontMetric aUnscaledFontMetric(Application::GetDefaultDevice()->GetFontMetric(aUnscaledFont));

                if (nHeight > 0)
                {
                    const double fScaleFactor(static_cast<double>(nNormedFontScaling) / static_cast<double>(nHeight));
                    nScaledWidth = basegfx::fround(static_cast<double>(aUnscaledFontMetric.GetAverageFontWidth()) * fScaleFactor);
                }
            }

            rFont.SetAverageFontWidth(nScaledWidth);
        }
        else
        {
            // the writing producer was on a windows system, correct pre-multiplied value
            // is already set, nothing to do. Ignore 2nd value. Here a check
            // could be done if adapting the 2nd, NormedFontScaling value would be similar to
            // the set value for plausibility reasons
        }
#else
        // we do not run on windows and a NormedFontScaling was written
        if(rFont.GetFontSize().getWidth() == nNormedFontScaling)
        {
            // the writing producer was not on a windows system, correct value
            // already set, nothing to do
        }
        else
        {
            // the writing producer was on a windows system, correct FontScaling.
            // The correct non-pre-multiplied value is the 2nd one, use it
            rFont.SetAverageFontWidth(nNormedFontScaling);
        }
#endif
    }

    return rRetval;
}

SvStream& WriteFont( SvStream& rOStm, const vcl::Font& rFont )
{
    // tdf#127471 prepare NormedFontScaling for additional export
    tools::Long nNormedFontScaling(rFont.GetFontSize().getWidth());

    // FontScaling usage at vcl-Font is detected by checking that FontWidth != 0
    if (nNormedFontScaling > 0)
    {
        const tools::Long nHeight(std::max<tools::Long>(rFont.GetFontSize().getHeight(), 0));

        // check for negative height
        if(0 == nHeight)
        {
            nNormedFontScaling = 0;
        }
        else
        {
#ifdef _WIN32
            // for WIN32 the value is pre-multiplied with AverageFontWidth
            // which makes it system-dependent. Turn that back to have the
            // normed non-windows form of it for export as 2nd value
            vcl::Font aUnscaledFont(rFont);
            aUnscaledFont.SetAverageFontWidth(0);
            const FontMetric aUnscaledFontMetric(
                Application::GetDefaultDevice()->GetFontMetric(aUnscaledFont));

            if (aUnscaledFontMetric.GetAverageFontWidth() > 0)
            {
                const double fScaleFactor(
                    static_cast<double>(nNormedFontScaling)
                    / static_cast<double>(aUnscaledFontMetric.GetAverageFontWidth()));
                nNormedFontScaling = static_cast<tools::Long>(fScaleFactor * nHeight);
            }
#endif
        }
    }

    return WriteImplFont( rOStm, *rFont.mpImplFont, nNormedFontScaling );
}

namespace
{
    bool identifyTrueTypeFont( const void* i_pBuffer, sal_uInt32 i_nSize, Font& o_rResult )
    {
        bool bResult = false;
        TrueTypeFont* pTTF = nullptr;
        if( OpenTTFontBuffer( i_pBuffer, i_nSize, 0, &pTTF ) == SFErrCodes::Ok )
        {
            TTGlobalFontInfo aInfo;
            GetTTGlobalFontInfo( pTTF, &aInfo );
            // most importantly: the family name
            if( !aInfo.ufamily.isEmpty() )
                o_rResult.SetFamilyName( aInfo.ufamily );
            else if( !aInfo.family.isEmpty() )
                o_rResult.SetFamilyName( OStringToOUString( aInfo.family, RTL_TEXTENCODING_ASCII_US ) );
            // set weight
            if( aInfo.weight )
            {
                if( aInfo.weight < FW_EXTRALIGHT )
                    o_rResult.SetWeight( WEIGHT_THIN );
                else if( aInfo.weight < FW_LIGHT )
                    o_rResult.SetWeight( WEIGHT_ULTRALIGHT );
                else if( aInfo.weight < FW_NORMAL )
                    o_rResult.SetWeight( WEIGHT_LIGHT );
                else if( aInfo.weight < FW_MEDIUM )
                    o_rResult.SetWeight( WEIGHT_NORMAL );
                else if( aInfo.weight < FW_SEMIBOLD )
                    o_rResult.SetWeight( WEIGHT_MEDIUM );
                else if( aInfo.weight < FW_BOLD )
                    o_rResult.SetWeight( WEIGHT_SEMIBOLD );
                else if( aInfo.weight < FW_EXTRABOLD )
                    o_rResult.SetWeight( WEIGHT_BOLD );
                else if( aInfo.weight < FW_BLACK )
                    o_rResult.SetWeight( WEIGHT_ULTRABOLD );
                else
                    o_rResult.SetWeight( WEIGHT_BLACK );
            }
            else
                o_rResult.SetWeight( (aInfo.macStyle & 1) ? WEIGHT_BOLD : WEIGHT_NORMAL );
            // set width
            if( aInfo.width )
            {
                if( aInfo.width == FWIDTH_ULTRA_CONDENSED )
                    o_rResult.SetAverageFontWidth( WIDTH_ULTRA_CONDENSED );
                else if( aInfo.width == FWIDTH_EXTRA_CONDENSED )
                    o_rResult.SetAverageFontWidth( WIDTH_EXTRA_CONDENSED );
                else if( aInfo.width == FWIDTH_CONDENSED )
                    o_rResult.SetAverageFontWidth( WIDTH_CONDENSED );
                else if( aInfo.width == FWIDTH_SEMI_CONDENSED )
                    o_rResult.SetAverageFontWidth( WIDTH_SEMI_CONDENSED );
                else if( aInfo.width == FWIDTH_NORMAL )
                    o_rResult.SetAverageFontWidth( WIDTH_NORMAL );
                else if( aInfo.width == FWIDTH_SEMI_EXPANDED )
                    o_rResult.SetAverageFontWidth( WIDTH_SEMI_EXPANDED );
                else if( aInfo.width == FWIDTH_EXPANDED )
                    o_rResult.SetAverageFontWidth( WIDTH_EXPANDED );
                else if( aInfo.width == FWIDTH_EXTRA_EXPANDED )
                    o_rResult.SetAverageFontWidth( WIDTH_EXTRA_EXPANDED );
                else if( aInfo.width >= FWIDTH_ULTRA_EXPANDED )
                    o_rResult.SetAverageFontWidth( WIDTH_ULTRA_EXPANDED );
            }
            // set italic
            o_rResult.SetItalic( (aInfo.italicAngle != 0) ? ITALIC_NORMAL : ITALIC_NONE );

            // set pitch
            o_rResult.SetPitch( (aInfo.pitch == 0) ? PITCH_VARIABLE : PITCH_FIXED );

            // set style name
            if( !aInfo.usubfamily.isEmpty() )
                o_rResult.SetStyleName( aInfo.usubfamily );
            else if( !aInfo.subfamily.isEmpty() )
                o_rResult.SetStyleName( OUString::createFromAscii( aInfo.subfamily ) );

            // cleanup
            CloseTTFont( pTTF );
            // success
            bResult = true;
        }
        return bResult;
    }

    struct WeightSearchEntry
    {
        const char* string;
        int         string_len;
        FontWeight  weight;

        bool operator<( const WeightSearchEntry& rRight ) const
        {
            return rtl_str_compareIgnoreAsciiCase_WithLength( string, string_len, rRight.string, rRight.string_len ) < 0;
        }
    }
    const weight_table[] =
    {
        { "black", 5, WEIGHT_BLACK },
        { "bold", 4, WEIGHT_BOLD },
        { "book", 4, WEIGHT_LIGHT },
        { "demi", 4, WEIGHT_SEMIBOLD },
        { "heavy", 5, WEIGHT_BLACK },
        { "light", 5, WEIGHT_LIGHT },
        { "medium", 6, WEIGHT_MEDIUM },
        { "regular", 7, WEIGHT_NORMAL },
        { "super", 5, WEIGHT_ULTRABOLD },
        { "thin", 4, WEIGHT_THIN }
    };

    bool identifyType1Font( const char* i_pBuffer, sal_uInt32 i_nSize, Font& o_rResult )
    {
        // might be a type1, find eexec
        const char* pStream = i_pBuffer;
        const char* const pExec = "eexec";
        const char* pExecPos = std::search( pStream, pStream+i_nSize, pExec, pExec+5 );
        if( pExecPos != pStream+i_nSize)
        {
            // find /FamilyName entry
            static const char* const pFam = "/FamilyName";
            const char* pFamPos = std::search( pStream, pExecPos, pFam, pFam+11 );
            if( pFamPos != pExecPos )
            {
                // extract the string value behind /FamilyName
                const char* pOpen = pFamPos+11;
                while( pOpen < pExecPos && *pOpen != '(' )
                    pOpen++;
                const char* pClose = pOpen;
                while( pClose < pExecPos && *pClose != ')' )
                    pClose++;
                if( pClose - pOpen > 1 )
                {
                    o_rResult.SetFamilyName( OStringToOUString( std::string_view( pOpen+1, pClose-pOpen-1 ), RTL_TEXTENCODING_ASCII_US ) );
                }
            }

            // parse /ItalicAngle
            static const char* const pItalic = "/ItalicAngle";
            const char* pItalicPos = std::search( pStream, pExecPos, pItalic, pItalic+12 );
            if( pItalicPos != pExecPos )
            {
                const char* pItalicEnd = pItalicPos + 12;
                auto nItalic = rtl_str_toInt64_WithLength(pItalicEnd, 10, pExecPos - pItalicEnd);
                o_rResult.SetItalic( (nItalic != 0) ? ITALIC_NORMAL : ITALIC_NONE );
            }

            // parse /Weight
            static const char* const pWeight = "/Weight";
            const char* pWeightPos = std::search( pStream, pExecPos, pWeight, pWeight+7 );
            if( pWeightPos != pExecPos )
            {
                // extract the string value behind /Weight
                const char* pOpen = pWeightPos+7;
                while( pOpen < pExecPos && *pOpen != '(' )
                    pOpen++;
                const char* pClose = pOpen;
                while( pClose < pExecPos && *pClose != ')' )
                    pClose++;
                if( pClose - pOpen > 1 )
                {
                    WeightSearchEntry aEnt;
                    aEnt.string = pOpen+1;
                    aEnt.string_len = (pClose-pOpen)-1;
                    aEnt.weight = WEIGHT_NORMAL;
                    WeightSearchEntry const * pFound = std::lower_bound( std::begin(weight_table), std::end(weight_table), aEnt );
                    if( pFound != std::end(weight_table) &&
                        rtl_str_compareIgnoreAsciiCase_WithLength( pFound->string, pFound->string_len, aEnt.string, aEnt.string_len) == 0 )
                        o_rResult.SetWeight( pFound->weight );
                }
            }

            // parse isFixedPitch
            static const char* const pFixed = "/isFixedPitch";
            const char* pFixedPos = std::search( pStream, pExecPos, pFixed, pFixed+13 );
            if( pFixedPos != pExecPos )
            {
                // skip whitespace
                while( pFixedPos < pExecPos-4 &&
                       ( *pFixedPos == ' '  ||
                         *pFixedPos == '\t' ||
                         *pFixedPos == '\r' ||
                         *pFixedPos == '\n' ) )
                {
                    pFixedPos++;
                }
                // find "true" value
                if( rtl_str_compareIgnoreAsciiCase_WithLength( pFixedPos, 4, "true", 4 ) == 0 )
                    o_rResult.SetPitch( PITCH_FIXED );
                else
                    o_rResult.SetPitch( PITCH_VARIABLE );
            }
        }
        return false;
    }
}

Font Font::identifyFont( const void* i_pBuffer, sal_uInt32 i_nSize )
{
    Font aResult;
    if( ! identifyTrueTypeFont( i_pBuffer, i_nSize, aResult ) )
    {
        const char* pStream = static_cast<const char*>(i_pBuffer);
        if( pStream && i_nSize > 100 &&
             *pStream == '%' && pStream[1] == '!' )
        {
            identifyType1Font( pStream, i_nSize, aResult );
        }
    }

    return aResult;
}

// The inlines from the font.hxx header are now instantiated for pImpl-ification
const Color& Font::GetColor() const { return mpImplFont->maColor; }
const Color& Font::GetFillColor() const { return mpImplFont->maFillColor; }
bool Font::IsTransparent() const { return mpImplFont->mbTransparent; }

TextAlign Font::GetAlignment() const { return mpImplFont->GetAlignment(); }

const OUString& Font::GetFamilyName() const { return mpImplFont->GetFamilyName(); }
const OUString& Font::GetStyleName() const { return mpImplFont->maStyleName; }

const Size& Font::GetFontSize() const { return mpImplFont->GetFontSize(); }
void Font::SetFontHeight( tools::Long nHeight ) { SetFontSize( Size( std::as_const(mpImplFont)->GetFontSize().Width(), nHeight ) ); }
tools::Long Font::GetFontHeight() const { return mpImplFont->GetFontSize().Height(); }
void Font::SetAverageFontWidth( tools::Long nWidth ) { SetFontSize( Size( nWidth, std::as_const(mpImplFont)->GetFontSize().Height() ) ); }
tools::Long Font::GetAverageFontWidth() const { return mpImplFont->GetFontSize().Width(); }

rtl_TextEncoding Font::GetCharSet() const { return mpImplFont->GetCharSet(); }

const LanguageTag& Font::GetLanguageTag() const { return mpImplFont->maLanguageTag; }
const LanguageTag& Font::GetCJKContextLanguageTag() const { return mpImplFont->maCJKLanguageTag; }
LanguageType Font::GetLanguage() const { return mpImplFont->maLanguageTag.getLanguageType( false); }
LanguageType Font::GetCJKContextLanguage() const { return mpImplFont->maCJKLanguageTag.getLanguageType( false); }

Degree10 Font::GetOrientation() const { return mpImplFont->mnOrientation; }
bool Font::IsVertical() const { return mpImplFont->mbVertical; }
FontKerning Font::GetKerning() const { return mpImplFont->meKerning; }

FontPitch Font::GetPitch() { return mpImplFont->GetPitch(); }
FontWeight Font::GetWeight() { return mpImplFont->GetWeight(); }
FontWidth Font::GetWidthType() { return mpImplFont->GetWidthType(); }
FontItalic Font::GetItalic() { return mpImplFont->GetItalic(); }
FontFamily Font::GetFamilyType() { return mpImplFont->GetFamilyType(); }

FontPitch Font::GetPitch() const { return mpImplFont->GetPitchNoAsk(); }
FontWeight Font::GetWeight() const { return mpImplFont->GetWeightNoAsk(); }
FontWidth Font::GetWidthType() const { return mpImplFont->GetWidthTypeNoAsk(); }
FontItalic Font::GetItalic() const { return mpImplFont->GetItalicNoAsk(); }
FontFamily Font::GetFamilyType() const { return mpImplFont->GetFamilyTypeNoAsk(); }

int Font::GetQuality() const { return mpImplFont->GetQuality(); }
void Font::SetQuality( int nQuality ) { mpImplFont->SetQuality( nQuality ); }
void Font::IncreaseQualityBy( int nQualityAmount ) { mpImplFont->IncreaseQualityBy( nQualityAmount ); }
void Font::DecreaseQualityBy( int nQualityAmount ) { mpImplFont->DecreaseQualityBy( nQualityAmount ); }

bool Font::IsOutline() const { return mpImplFont->mbOutline; }
bool Font::IsShadow() const { return mpImplFont->mbShadow; }
FontRelief Font::GetRelief() const { return mpImplFont->meRelief; }
FontLineStyle Font::GetUnderline() const { return mpImplFont->meUnderline; }
FontLineStyle Font::GetOverline()  const { return mpImplFont->meOverline; }
FontStrikeout Font::GetStrikeout() const { return mpImplFont->meStrikeout; }
FontEmphasisMark Font::GetEmphasisMark() const { return mpImplFont->meEmphasisMark; }
bool Font::IsWordLineMode() const { return mpImplFont->mbWordLine; }
bool Font::IsSameInstance( const vcl::Font& rFont ) const { return (mpImplFont == rFont.mpImplFont); }


ImplFont::ImplFont() :
    meWeight( WEIGHT_DONTKNOW ),
    meFamily( FAMILY_DONTKNOW ),
    mePitch( PITCH_DONTKNOW ),
    meWidthType( WIDTH_DONTKNOW ),
    meItalic( ITALIC_NONE ),
    meAlign( ALIGN_TOP ),
    meUnderline( LINESTYLE_NONE ),
    meOverline( LINESTYLE_NONE ),
    meStrikeout( STRIKEOUT_NONE ),
    meRelief( FontRelief::NONE ),
    meEmphasisMark( FontEmphasisMark::NONE ),
    meKerning( FontKerning::FontSpecific ),
    mnSpacing( 0 ),
    meCharSet( RTL_TEXTENCODING_DONTKNOW ),
    maLanguageTag( LANGUAGE_DONTKNOW ),
    maCJKLanguageTag( LANGUAGE_DONTKNOW ),
    mbSymbolFlag( false ),
    mbOutline( false ),
    mbConfigLookup( false ),
    mbShadow( false ),
    mbVertical( false ),
    mbTransparent( true ),
    maColor( COL_TRANSPARENT ),
    maFillColor( COL_TRANSPARENT ),
    mbWordLine( false ),
    mnOrientation( 0 ),
    mnQuality( 0 ),
    mnCalculatedAverageFontWidth( 0 )
{}

ImplFont::ImplFont( const ImplFont& rImplFont ) :
    maFamilyName( rImplFont.maFamilyName ),
    maStyleName( rImplFont.maStyleName ),
    meWeight( rImplFont.meWeight ),
    meFamily( rImplFont.meFamily ),
    mePitch( rImplFont.mePitch ),
    meWidthType( rImplFont.meWidthType ),
    meItalic( rImplFont.meItalic ),
    meAlign( rImplFont.meAlign ),
    meUnderline( rImplFont.meUnderline ),
    meOverline( rImplFont.meOverline ),
    meStrikeout( rImplFont.meStrikeout ),
    meRelief( rImplFont.meRelief ),
    meEmphasisMark( rImplFont.meEmphasisMark ),
    meKerning( rImplFont.meKerning ),
    mnSpacing( rImplFont.mnSpacing ),
    maAverageFontSize( rImplFont.maAverageFontSize ),
    meCharSet( rImplFont.meCharSet ),
    maLanguageTag( rImplFont.maLanguageTag ),
    maCJKLanguageTag( rImplFont.maCJKLanguageTag ),
    mbSymbolFlag( rImplFont.mbSymbolFlag ),
    mbOutline( rImplFont.mbOutline ),
    mbConfigLookup( rImplFont.mbConfigLookup ),
    mbShadow( rImplFont.mbShadow ),
    mbVertical( rImplFont.mbVertical ),
    mbTransparent( rImplFont.mbTransparent ),
    maColor( rImplFont.maColor ),
    maFillColor( rImplFont.maFillColor ),
    mbWordLine( rImplFont.mbWordLine ),
    mnOrientation( rImplFont.mnOrientation ),
    mnQuality( rImplFont.mnQuality ),
    mnCalculatedAverageFontWidth( rImplFont.mnCalculatedAverageFontWidth )
{}

bool ImplFont::operator==( const ImplFont& rOther ) const
{
    if(!EqualIgnoreColor( rOther ))
        return false;

    if( (maColor        != rOther.maColor)
    ||  (maFillColor    != rOther.maFillColor) )
        return false;

    return true;
}

bool ImplFont::EqualIgnoreColor( const ImplFont& rOther ) const
{
    // equality tests split up for easier debugging
    if( (meWeight   != rOther.meWeight)
    ||  (meItalic   != rOther.meItalic)
    ||  (meFamily   != rOther.meFamily)
    ||  (mePitch    != rOther.mePitch) )
        return false;

    if( (meCharSet        != rOther.meCharSet)
    ||  (maLanguageTag    != rOther.maLanguageTag)
    ||  (maCJKLanguageTag != rOther.maCJKLanguageTag)
    ||  (meAlign          != rOther.meAlign) )
        return false;

    if( (maAverageFontSize       != rOther.maAverageFontSize)
    ||  (mnOrientation  != rOther.mnOrientation)
    ||  (mbVertical     != rOther.mbVertical) )
        return false;

    if( (maFamilyName   != rOther.maFamilyName)
    ||  (maStyleName    != rOther.maStyleName) )
        return false;

    if( (meUnderline    != rOther.meUnderline)
    ||  (meOverline     != rOther.meOverline)
    ||  (meStrikeout    != rOther.meStrikeout)
    ||  (meRelief       != rOther.meRelief)
    ||  (meEmphasisMark != rOther.meEmphasisMark)
    ||  (mbWordLine     != rOther.mbWordLine)
    ||  (mbOutline      != rOther.mbOutline)
    ||  (mbShadow       != rOther.mbShadow)
    ||  (meKerning      != rOther.meKerning)
    ||  (mnSpacing      != rOther.mnSpacing)
    ||  (mbTransparent  != rOther.mbTransparent) )
        return false;

    return true;
}

size_t ImplFont::GetHashValue() const
{
    size_t hash = GetHashValueIgnoreColor();
    o3tl::hash_combine( hash, static_cast<sal_uInt32>( maColor ));
    o3tl::hash_combine( hash, static_cast<sal_uInt32>( maFillColor ));
    return hash;
}

size_t ImplFont::GetHashValueIgnoreColor() const
{
    size_t hash = 0;

    o3tl::hash_combine( hash, meWeight );
    o3tl::hash_combine( hash, meItalic );
    o3tl::hash_combine( hash, meFamily );
    o3tl::hash_combine( hash, mePitch );

    o3tl::hash_combine( hash, meCharSet );
    o3tl::hash_combine( hash, maLanguageTag.getLanguageType( false ).get());
    o3tl::hash_combine( hash, maCJKLanguageTag.getLanguageType( false ).get());
    o3tl::hash_combine( hash, meAlign );

    o3tl::hash_combine( hash, maAverageFontSize.GetHashValue());
    o3tl::hash_combine( hash, mnOrientation.get());
    o3tl::hash_combine( hash, mbVertical );

    o3tl::hash_combine( hash, maFamilyName );
    o3tl::hash_combine( hash, maStyleName );

    o3tl::hash_combine( hash, meUnderline );
    o3tl::hash_combine( hash, meOverline );
    o3tl::hash_combine( hash, meStrikeout );
    o3tl::hash_combine( hash, meRelief );
    o3tl::hash_combine( hash, meEmphasisMark );
    o3tl::hash_combine( hash, mbWordLine );
    o3tl::hash_combine( hash, mbOutline );
    o3tl::hash_combine( hash, mbShadow );
    o3tl::hash_combine( hash, meKerning );
    o3tl::hash_combine( hash, mnSpacing );
    o3tl::hash_combine( hash, mbTransparent );

    return hash;
}

void ImplFont::AskConfig()
{
    if( mbConfigLookup )
        return;

    mbConfigLookup = true;

    // prepare the FontSubst configuration lookup
    const utl::FontSubstConfiguration& rFontSubst = utl::FontSubstConfiguration::get();

    OUString      aShortName;
    OUString      aFamilyName;
    ImplFontAttrs nType = ImplFontAttrs::None;
    FontWeight  eWeight = WEIGHT_DONTKNOW;
    FontWidth   eWidthType = WIDTH_DONTKNOW;
    OUString    aMapName = GetEnglishSearchFontName( maFamilyName );

    utl::FontSubstConfiguration::getMapName( aMapName,
        aShortName, aFamilyName, eWeight, eWidthType, nType );

    // lookup the font name in the configuration
    const utl::FontNameAttr* pFontAttr = rFontSubst.getSubstInfo( aMapName );

    // if the direct lookup failed try again with an alias name
    if ( !pFontAttr && (aShortName != aMapName) )
        pFontAttr = rFontSubst.getSubstInfo( aShortName );

    if( pFontAttr )
    {
        // the font was found in the configuration
        if( meFamily == FAMILY_DONTKNOW )
        {
            if ( pFontAttr->Type & ImplFontAttrs::Serif )
                meFamily = FAMILY_ROMAN;
            else if ( pFontAttr->Type & ImplFontAttrs::SansSerif )
                meFamily = FAMILY_SWISS;
            else if ( pFontAttr->Type & ImplFontAttrs::Typewriter )
                meFamily = FAMILY_MODERN;
            else if ( pFontAttr->Type & ImplFontAttrs::Italic )
                meFamily = FAMILY_SCRIPT;
            else if ( pFontAttr->Type & ImplFontAttrs::Decorative )
                meFamily = FAMILY_DECORATIVE;
        }

        if( mePitch == PITCH_DONTKNOW )
        {
            if ( pFontAttr->Type & ImplFontAttrs::Fixed )
                mePitch = PITCH_FIXED;
        }
    }

    // if some attributes are still unknown then use the FontSubst magic
    if( meFamily == FAMILY_DONTKNOW )
    {
        if( nType & ImplFontAttrs::Serif )
            meFamily = FAMILY_ROMAN;
        else if( nType & ImplFontAttrs::SansSerif )
            meFamily = FAMILY_SWISS;
        else if( nType & ImplFontAttrs::Typewriter )
            meFamily = FAMILY_MODERN;
        else if( nType & ImplFontAttrs::Italic )
            meFamily = FAMILY_SCRIPT;
        else if( nType & ImplFontAttrs::Decorative )
            meFamily = FAMILY_DECORATIVE;
    }

    if( GetWeight() == WEIGHT_DONTKNOW )
        SetWeight( eWeight );
    if( meWidthType == WIDTH_DONTKNOW )
        meWidthType = eWidthType;
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
