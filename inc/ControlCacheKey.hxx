/* comment */
#ifndef INCLUDED_VCL_INC_CONTROLCACHEKEY_HXX
#define INCLUDED_VCL_INC_CONTROLCACHEKEY_HXX

#include <tools/gen.hxx>
#include <vcl/salnativewidgets.hxx>
#include <o3tl/hash_combine.hxx>

class ControlCacheKey
{
public:
    ControlType mnType;
    ControlPart mnPart;
    ControlState mnState;
    Size maSize;

    ControlCacheKey(ControlType nType, ControlPart nPart, ControlState nState, const Size& rSize)
        : mnType(nType)
        , mnPart(nPart)
        , mnState(nState)
        , maSize(rSize)
    {
    }

    bool operator==(ControlCacheKey const& aOther) const
    {
        return mnType == aOther.mnType && mnPart == aOther.mnPart && mnState == aOther.mnState
               && maSize.Width() == aOther.maSize.Width()
               && maSize.Height() == aOther.maSize.Height();
    }

    bool canCacheControl() const
    {
        switch (mnType)
        {
            case ControlType::Checkbox:
            case ControlType::Radiobutton:
            case ControlType::ListNode:
            case ControlType::Slider:
            case ControlType::Progress:
            // FIXME: these guys have complex state hidden in ImplControlValue
            // structs which affects rendering, needs to be a and needs to be
            // part of the key to our cache.
            case ControlType::Spinbox:
            case ControlType::SpinButtons:
            case ControlType::TabItem:
                return false;

            case ControlType::Menubar:
                if (mnPart == ControlPart::Entire)
                    return false;
                break;

            default:
                break;
        }
        return true;
    }
};

struct ControlCacheHashFunction
{
    std::size_t operator()(ControlCacheKey const& aCache) const
    {
        std::size_t seed = 0;
        o3tl::hash_combine(seed, aCache.mnType);
        o3tl::hash_combine(seed, aCache.mnPart);
        o3tl::hash_combine(seed, aCache.mnState);
        o3tl::hash_combine(seed, aCache.maSize.Width());
        o3tl::hash_combine(seed, aCache.maSize.Height());
        return seed;
    }
};

#endif // INCLUDED_VCL_INC_CONTROLCACHEKEY_HXX
