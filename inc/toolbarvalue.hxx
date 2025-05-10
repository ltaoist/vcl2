/* comment */
#ifndef INCLUDED_VCL_INC_TOOLBARVALUE_HXX
#define INCLUDED_VCL_INC_TOOLBARVALUE_HXX

#include <tools/gen.hxx>
#include <vcl/salnativewidgets.hxx>

/*  Toolbarvalue:
 *
 *  Value container for toolbars detailing the grip position
 */
class ToolbarValue final : public ImplControlValue
{
public:
    ToolbarValue()
        : ImplControlValue(ControlType::Toolbar, 0)
    {
        mbIsTopDockingArea = false;
    }
    virtual ~ToolbarValue() override;
    virtual ToolbarValue* clone() const override;
    ToolbarValue(ToolbarValue const&) = default;
    ToolbarValue(ToolbarValue&&) = default;
    ToolbarValue& operator=(ToolbarValue const&) = delete; // due to ImplControlValue
    ToolbarValue& operator=(ToolbarValue&&) = delete; // due to ImplControlValue
    tools::Rectangle maGripRect;
    // indicates that this is the top aligned dockingarea
    // adjacent to the menubar, only used on Windows
    bool mbIsTopDockingArea;
};

#endif // INCLUDED_VCL_INC_TOOLBARVALUE_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
