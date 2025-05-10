/* comment */

#pragma once

#include <map>
#include <vector>

#include <rtl/strbuf.hxx>
#include <rtl/string.hxx>
#include <sal/types.h>
#include <vcl/dllapi.h>

class SvMemoryStream;

namespace vcl
{
class PDFObjectContainer;
namespace filter
{
class PDFObjectElement;
class PDFElement;
}

/// Copies objects from one PDF file into another one.
class PDFObjectCopier
{
    PDFObjectContainer& m_rContainer;

    void copyRecursively(OStringBuffer& rLine, filter::PDFElement& rInputElement,
                         SvMemoryStream& rDocBuffer,
                         std::map<sal_Int32, sal_Int32>& rCopiedResources);

public:
    PDFObjectCopier(PDFObjectContainer& rContainer);

    /// Copies resources of a given kind from an external page to the output,
    /// returning what has to be included in the new resource dictionary.
    OString copyExternalResources(filter::PDFObjectElement& rPage, const OString& rKind,
                                  std::map<sal_Int32, sal_Int32>& rCopiedResources);

    /// Copies a single resource from an external document, returns the new
    /// object ID in our document.
    sal_Int32 copyExternalResource(SvMemoryStream& rDocBuffer, filter::PDFObjectElement& rObject,
                                   std::map<sal_Int32, sal_Int32>& rCopiedResources);

    /// Copies resources of pPage into rLine.
    void copyPageResources(filter::PDFObjectElement* pPage, OStringBuffer& rLine);

    void copyPageResources(filter::PDFObjectElement* pPage, OStringBuffer& rLine,
                           std::map<sal_Int32, sal_Int32>& rCopiedResources);

    /// Copies page one or more page streams from rContentStreams into rStream.
    static sal_Int32 copyPageStreams(std::vector<filter::PDFObjectElement*>& rContentStreams,
                                     SvMemoryStream& rStream, bool& rCompressed);
};
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
