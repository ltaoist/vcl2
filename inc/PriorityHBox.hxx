/* comment */
#pragma once

#include <vcl/layout.hxx>
#include "IPrioritable.hxx"

#include <vector>

/*
 * PriorityHBox is a VclHBox which hides its own children if there is no sufficient space.
 * Hiding order can be modified using child's priorities. If a control have default
 * priority assigned (VCL_PRIORITY_DEFAULT), it is always shown.
 */

class PriorityHBox : public VclHBox
{
protected:
    bool m_bInitialized;

    std::vector<vcl::IPrioritable*> m_aSortedChildren;

    virtual int GetHiddenCount() const;

    virtual void GetChildrenWithPriorities();

public:
    explicit PriorityHBox(vcl::Window* pParent);

    virtual ~PriorityHBox() override;

    void Initialize();

    void SetSizeFromParent();

    virtual Size calculateRequisition() const override;

    virtual void Resize() override;

    virtual void Paint(vcl::RenderContext& rRenderContext, const tools::Rectangle& rRect) override;
};

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
