/* comment */
#ifndef INCLUDED_VCL_INC_SALGEOM_HXX
#define INCLUDED_VCL_INC_SALGEOM_HXX

#include <iostream>

#include <vcl/dllapi.h>
#include <vcl/WindowPosSize.hxx>
#include <tools/long.hxx>

// There are some unused functions, which I would keep to ease understanding.
class SalFrameGeometry : public vcl::WindowPosSize
{
    // non-drawable area / margins / frame / decorations around the client area
    sal_uInt32 m_nLeftDecoration, m_nTopDecoration, m_nRightDecoration, m_nBottomDecoration;
    unsigned int m_nDisplayScreenNumber;

public:
    SalFrameGeometry()
        : m_nLeftDecoration(0)
        , m_nTopDecoration(0)
        , m_nRightDecoration(0)
        , m_nBottomDecoration(0)
        , m_nDisplayScreenNumber(0)
    {
    }

    constexpr sal_uInt32 leftDecoration() const { return m_nLeftDecoration; }
    void setLeftDecoration(sal_uInt32 nLeftDecoration) { m_nLeftDecoration = nLeftDecoration; }
    constexpr sal_uInt32 topDecoration() const { return m_nTopDecoration; }
    void setTopDecoration(sal_uInt32 nTopDecoration) { m_nTopDecoration = nTopDecoration; }
    constexpr sal_uInt32 rightDecoration() const { return m_nRightDecoration; }
    void setRightDecoration(sal_uInt32 nRightDecoration) { m_nRightDecoration = nRightDecoration; }
    constexpr sal_uInt32 bottomDecoration() const { return m_nBottomDecoration; }
    void setBottomDecoration(sal_uInt32 nBottomDecoration)
    {
        m_nBottomDecoration = nBottomDecoration;
    }
    void setDecorations(sal_uInt32 nLeft, sal_uInt32 nTop, sal_uInt32 nRight, sal_uInt32 nBottom)
    {
        m_nLeftDecoration = nLeft;
        m_nTopDecoration = nTop;
        m_nRightDecoration = nRight;
        m_nBottomDecoration = nBottom;
    }

    unsigned int screen() const { return m_nDisplayScreenNumber; }
    void setScreen(unsigned int nScreen) { m_nDisplayScreenNumber = nScreen; }
};

inline std::ostream& operator<<(std::ostream& s, const SalFrameGeometry& rGeom)
{
    s << *static_cast<const vcl::WindowPosSize*>(&rGeom) << ":{" << rGeom.leftDecoration() << ","
      << rGeom.topDecoration() << "," << rGeom.rightDecoration() << "," << rGeom.bottomDecoration()
      << "}s" << rGeom.screen();
    return s;
}

/// Interface used to share logic on sizing between
/// SalVirtualDevices and SalFrames
class VCL_PLUGIN_PUBLIC SalGeometryProvider
{
public:
    virtual ~SalGeometryProvider() {}
    virtual tools::Long GetWidth() const = 0;
    virtual tools::Long GetHeight() const = 0;
    virtual bool IsOffScreen() const = 0;
};

#endif // INCLUDED_VCL_INC_SALGEOM_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
