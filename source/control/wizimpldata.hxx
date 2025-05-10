/* comment */
#ifndef INCLUDED_VCL_SOURCE_CONTROL_WIZIMPLDATA_HXX
#define INCLUDED_VCL_SOURCE_CONTROL_WIZIMPLDATA_HXX

#include <stack>

struct WizPageData
{
    WizPageData*    mpNext;
    std::unique_ptr<BuilderPage> mxPage;
};

struct ImplWizButtonData
{
    ImplWizButtonData*  mpNext;
    VclPtr<Button>      mpButton;
    tools::Long                mnOffset;
};

namespace vcl
{
    struct WizardMachineImplData
    {
        OUString                        sTitleBase;         // the base for the title
        std::stack<WizardTypes::WizardState> aStateHistory;      // the history of all states (used for implementing "Back")

        WizardTypes::WizardState nFirstUnknownPage;
            // the WizardDialog does not allow non-linear transitions (e.g. it's
            // not possible to add pages in a non-linear order), so we need some own maintenance data

        bool                            m_bAutoNextButtonState;

        bool                            m_bTravelingSuspended;

        WizardMachineImplData()
            :nFirstUnknownPage( 0 )
            ,m_bAutoNextButtonState( false )
            ,m_bTravelingSuspended( false )
        {
        }
    };
}   // namespace svt

#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
