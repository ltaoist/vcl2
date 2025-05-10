/* comment */
#ifndef INCLUDED_VCL_INC_VCLEVENTLISTENERS_HXX
#define INCLUDED_VCL_INC_VCLEVENTLISTENERS_HXX

#include <vector>

class VclEventListeners
{
public:
    void Call(VclSimpleEvent& rEvent) const;
    void addListener(const Link<VclSimpleEvent&, void>& rListener);
    void removeListener(const Link<VclSimpleEvent&, void>& rListener);

private:
    std::vector<Link<VclSimpleEvent&, void>> m_aListeners;
    mutable bool m_updated = false;
};

#endif // INCLUDED_VCL_INC_VCLEVENTLISTENERS_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
