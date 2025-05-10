/* comment */
#pragma once

#include <vcl/dllapi.h>
#include <rtl/ustring.hxx>
#include <tools/gen.hxx>
#include <memory>

class GraphicReader
{
public:
    virtual ~GraphicReader();

    const OUString& GetUpperFilterName() const { return maUpperName; }

protected:
    OUString maUpperName;

    GraphicReader();
};

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
