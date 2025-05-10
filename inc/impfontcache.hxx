/* comment */
#pragma once

#include <sal/config.h>

#include <rtl/ref.hxx>
#include <o3tl/lru_map.hxx>
#include <o3tl/hash_combine.hxx>
#include <tools/gen.hxx>

#include "font/FontSelectPattern.hxx"
#include "glyphid.hxx"

class Size;
namespace vcl { class Font; }
namespace vcl::font { class PhysicalFontCollection; }

// TODO: closely couple with PhysicalFontCollection

struct GlyphBoundRectCacheKey
{
    const LogicalFontInstance* m_pFont;
    const sal_GlyphId m_nId;

    GlyphBoundRectCacheKey(const LogicalFontInstance* pFont, sal_GlyphId nID)
        : m_pFont(pFont), m_nId(nID)
    {}

    bool operator==(GlyphBoundRectCacheKey const& aOther) const
    { return m_pFont == aOther.m_pFont && m_nId == aOther.m_nId; }
};

struct GlyphBoundRectCacheHash
{
    std::size_t operator()(GlyphBoundRectCacheKey const& aCache) const
    {
        std::size_t seed = 0;
        o3tl::hash_combine(seed, aCache.m_pFont);
        o3tl::hash_combine(seed, aCache.m_nId);
        return seed;
    }
};

typedef o3tl::lru_map<GlyphBoundRectCacheKey, tools::Rectangle,
                      GlyphBoundRectCacheHash> GlyphBoundRectCache;

class ImplFontCache
{
private:
    // cache of recently used font instances
    struct IFSD_Equal { bool operator()( const vcl::font::FontSelectPattern&, const vcl::font::FontSelectPattern& ) const; };
    struct IFSD_Hash { size_t operator()( const vcl::font::FontSelectPattern& ) const; };
    typedef o3tl::lru_map<vcl::font::FontSelectPattern, rtl::Reference<LogicalFontInstance>, IFSD_Hash, IFSD_Equal> FontInstanceList;

    LogicalFontInstance* mpLastHitCacheEntry; ///< keeps the last hit cache entry
    FontInstanceList maFontInstanceList;
    GlyphBoundRectCache m_aBoundRectCache;

    rtl::Reference<LogicalFontInstance> GetFontInstance(vcl::font::PhysicalFontCollection const*, vcl::font::FontSelectPattern&);

public:
    ImplFontCache();
    ~ImplFontCache();

    rtl::Reference<LogicalFontInstance> GetFontInstance(vcl::font::PhysicalFontCollection const *,
                             const vcl::Font&, const Size& rPixelSize, float fExactHeight, bool bNonAntialias = false);
    rtl::Reference<LogicalFontInstance> GetGlyphFallbackFont( vcl::font::PhysicalFontCollection const *, vcl::font::FontSelectPattern&,
                            LogicalFontInstance* pLogicalFont,
                            int nFallbackLevel, OUString& rMissingCodes );

    bool GetCachedGlyphBoundRect(const LogicalFontInstance *, sal_GlyphId, tools::Rectangle &);
    void CacheGlyphBoundRect(const LogicalFontInstance *, sal_GlyphId, tools::Rectangle &);

    void                Invalidate();
};

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
