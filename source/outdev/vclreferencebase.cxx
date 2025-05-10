/* comment */
#include <vcl/vclreferencebase.hxx>

VclReferenceBase::VclReferenceBase() :
    mnRefCnt(1), // cf. VclPtrInstance and README.lifecycle
    mbDisposed(false)
{
}

VclReferenceBase::~VclReferenceBase()
{
    disposeOnce();
}

void VclReferenceBase::disposeOnce()
{
    if ( mbDisposed )
        return;
    mbDisposed = true;
    dispose();
}

void VclReferenceBase::dispose()
{
}

