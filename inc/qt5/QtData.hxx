/* comment */
#pragma once

#include <unx/gendata.hxx>

#include <o3tl/enumarray.hxx>
#include <vcl/ptrstyle.hxx>
#include <memory>
#include <vclpluginapi.h>

class QCursor;

class VCLPLUG_QT_PUBLIC QtData final : public GenericUnixSalData
{
    o3tl::enumarray<PointerStyle, std::unique_ptr<QCursor>> m_aCursors;

public:
    explicit QtData();
    virtual ~QtData() override;

    virtual void ErrorTrapPush() override;
    virtual bool ErrorTrapPop(bool bIgnoreError = true) override;

    QCursor& getCursor(PointerStyle ePointerStyle);

    static bool noNativeControls();
};

inline QtData* GetQtData() { return static_cast<QtData*>(GetSalData()); }

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
