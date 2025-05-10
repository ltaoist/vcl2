/* comment */
#include <sal/config.h>

#include <vcl/NotebookbarContextControl.hxx>
#include <vcl/layout.hxx>

/*
 * ContextVBox is a VclVBox which shows own children depending on current context.
 * This control can be used in the notebookbar .ui files
 */

class ContextVBox final : public VclVBox, public NotebookbarContextControl
{
public:
    explicit ContextVBox(vcl::Window* pParent);
    virtual ~ContextVBox() override;
    void SetContext(vcl::EnumContext::Context eContext) override;
};

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
