/* comment */
#ifndef INCLUDED_VCL_INC_QUARTZ_SALGDICOMMON_HXX
#define INCLUDED_VCL_INC_QUARTZ_SALGDICOMMON_HXX

#include <iostream>

#include <premac.h>
#ifdef IOS
#include <CoreGraphics/CoreGraphics.h>
#else
#include <ApplicationServices/ApplicationServices.h>
#endif
#include <postmac.h>

#include <tools/color.hxx>
#include <vcl/salgtype.hxx>

// abstracting quartz color instead of having to use a CGFloat[] array
class RGBAColor
{
public:
    RGBAColor( ::Color );
    RGBAColor( float fRed, float fGreen, float fBlue, float fAlpha ); //NOTUSEDYET
    const CGFloat* AsArray() const { return m_fRGBA; }
    bool IsVisible() const { return m_fRGBA[3] > 0; }
    void SetAlpha( float fAlpha ) { m_fRGBA[3] = fAlpha; }

    CGFloat GetRed() const   { return m_fRGBA[0]; }
    CGFloat GetGreen() const { return m_fRGBA[1]; }
    CGFloat GetBlue() const  { return m_fRGBA[2]; }
    CGFloat GetAlpha() const { return m_fRGBA[3]; }
private:
    CGFloat m_fRGBA[4]; // red, green, blue, alpha
};

inline RGBAColor::RGBAColor( ::Color nColor )
{
    m_fRGBA[0] = nColor.GetRed() * (1.0/255);
    m_fRGBA[1] = nColor.GetGreen() * (1.0/255);
    m_fRGBA[2] = nColor.GetBlue() * (1.0/255);
    m_fRGBA[3] = 1.0; // opaque
}

inline RGBAColor::RGBAColor( float fRed, float fGreen, float fBlue, float fAlpha )
{
    m_fRGBA[0] = fRed;
    m_fRGBA[1] = fGreen;
    m_fRGBA[2] = fBlue;
    m_fRGBA[3] = fAlpha;
}

inline std::ostream &operator <<(std::ostream& s, const RGBAColor &aColor)
{
#ifndef SAL_LOG_INFO
    (void) aColor;
#else
    s << "{" << aColor.GetRed() << "," << aColor.GetGreen() << "," << aColor.GetBlue() << "," << aColor.GetAlpha() << "}";
#endif
    return s;
}

// XOR emulation suckage.
// See http://www.openoffice.org/marketing/ooocon2008/programme/wednesday_1401.pdf
// and https://bugs.freedesktop.org/show_bug.cgi?id=38844 .

class XorEmulation
{
public:
    XorEmulation();
    ~XorEmulation();

    void SetTarget( int nWidth, int nHeight, int nBitmapDepth, CGContextRef, CGLayerRef );
    bool UpdateTarget();
    void Enable() { m_bIsEnabled = true; }
    void Disable() { m_bIsEnabled = false; }
    bool IsEnabled() const { return m_bIsEnabled; }
    CGContextRef GetTargetContext() const { return m_xTargetContext; }
    CGContextRef GetMaskContext() const { return (m_bIsEnabled ? m_xMaskContext : nullptr); }

private:
    CGLayerRef m_xTargetLayer;
    CGContextRef m_xTargetContext;
    CGContextRef m_xMaskContext;
    CGContextRef m_xTempContext;
    sal_uLong* m_pMaskBuffer;
    sal_uLong* m_pTempBuffer;
    int m_nBufferLongs;
    bool m_bIsEnabled;
};

#endif // INCLUDED_VCL_INC_QUARTZ_SALGDICOMMON_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
