/* comment */
#include <vcl/txtattr.hxx>
#include <vcl/font.hxx>

TextAttrib::~TextAttrib()
{
}

bool TextAttrib::operator==( const TextAttrib& rAttr ) const
{
    return mnWhich == rAttr.mnWhich;
}

TextAttribFontColor::TextAttribFontColor( const Color& rColor )
    : TextAttrib( TEXTATTR_FONTCOLOR ), maColor( rColor )
{
}

void TextAttribFontColor::SetFont( vcl::Font& rFont ) const
{
    rFont.SetColor( maColor );
}

std::unique_ptr<TextAttrib> TextAttribFontColor::Clone() const
{
    return std::unique_ptr<TextAttrib>(new TextAttribFontColor( *this ));
}

bool TextAttribFontColor::operator==( const TextAttrib& rAttr ) const
{
    return ( ( TextAttrib::operator==(rAttr ) ) &&
                ( maColor == static_cast<const TextAttribFontColor&>(rAttr).maColor ) );
}

TextAttribFontWeight::TextAttribFontWeight( FontWeight eWeight )
    : TextAttrib( TEXTATTR_FONTWEIGHT ), meWeight( eWeight )
{
}

void TextAttribFontWeight::SetFont( vcl::Font& rFont ) const
{
    rFont.SetWeight( meWeight );
}

std::unique_ptr<TextAttrib> TextAttribFontWeight::Clone() const
{
    return std::unique_ptr<TextAttrib>(new TextAttribFontWeight( *this ));
}

bool TextAttribFontWeight::operator==( const TextAttrib& rAttr ) const
{
    return ( ( TextAttrib::operator==(rAttr ) ) &&
                ( meWeight == static_cast<const TextAttribFontWeight&>(rAttr).meWeight ) );
}

TextAttribProtect::TextAttribProtect() :
    TextAttrib( TEXTATTR_PROTECTED )
{
}

void TextAttribProtect::SetFont( vcl::Font& ) const
{
}

std::unique_ptr<TextAttrib> TextAttribProtect::Clone() const
{
    return std::unique_ptr<TextAttrib>(new TextAttribProtect());
}

bool TextAttribProtect::operator==( const TextAttrib& rAttr ) const
{
    return TextAttrib::operator==(rAttr );
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
