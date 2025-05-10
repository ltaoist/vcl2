/* comment */
#pragma once

#include <vcl/dllapi.h>
#include <tools/urlobj.hxx>
#include <tools/stream.hxx>
#include <unotools/ucbhelper.hxx>
#include <unotools/ucbstreamhelper.hxx>
#include <utility>

namespace vcl
{
class VCL_DLLPUBLIC SwapFile
{
private:
    INetURLObject maSwapURL;

public:
    SwapFile(INetURLObject aSwapURL)
        : maSwapURL(std::move(aSwapURL))
    {
    }

    ~SwapFile() COVERITY_NOEXCEPT_FALSE
    {
        utl::UCBContentHelper::Kill(maSwapURL.GetMainURL(INetURLObject::DecodeMechanism::NONE));
    }

    const INetURLObject& getSwapURL() const { return maSwapURL; }

    OUString getSwapURLString() const
    {
        return maSwapURL.GetMainURL(INetURLObject::DecodeMechanism::NONE);
    }

    std::unique_ptr<SvStream> openOutputStream()
    {
        OUString sSwapURL = getSwapURLString();
        if (!sSwapURL.isEmpty())
        {
            try
            {
                return utl::UcbStreamHelper::CreateStream(
                    sSwapURL, StreamMode::READWRITE | StreamMode::SHARE_DENYWRITE);
            }
            catch (const css::uno::Exception&)
            {
            }
        }
        return std::unique_ptr<SvStream>();
    }
};
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
