/* comment */

#ifndef INCLUDED_VCL_IPRIORITABLE_HXX
#define INCLUDED_VCL_IPRIORITABLE_HXX

#include <vcl/dllapi.h>

#define VCL_PRIORITY_DEFAULT -1

namespace vcl
{

class VCL_DLLPUBLIC IPrioritable
{
protected:
    IPrioritable() : m_nPriority(VCL_PRIORITY_DEFAULT)
    {
    }

public:
    virtual ~IPrioritable()
    {
    }

    int GetPriority() const
    {
        return m_nPriority;
    }

    void SetPriority(int nPriority)
    {
        m_nPriority = nPriority;
    }

    virtual void HideContent() = 0;
    virtual void ShowContent() = 0;
    virtual bool IsHidden() = 0;

private:
    int m_nPriority;
};

} // namespace vcl

#endif // INCLUDED_VCL_IPRIORITABLE_HXX

/* comment */
