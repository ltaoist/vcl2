/* comment */
#ifndef INCLUDED_VCL_INC_PRINT_H
#define INCLUDED_VCL_INC_PRINT_H

#include <rtl/ustring.hxx>
#include <vcl/dllapi.h>
#include <vcl/print.hxx>
#include "salprn.hxx"

#include <vector>
#include <unordered_map>

class JobSetup;

namespace vcl
{ class PrinterListener; }

struct ImplPrnQueueData
{
    std::unique_ptr<QueueInfo>           mpQueueInfo;
    std::unique_ptr<SalPrinterQueueInfo> mpSalQueueInfo;

// unlike other similar places, we need to ifdef this to keep old GCC baseline happy
#ifdef _MSC_VER
    ImplPrnQueueData() {}
    ImplPrnQueueData(ImplPrnQueueData&&) = default;
  
    ImplPrnQueueData& operator=( ImplPrnQueueData const & ) = delete; // MSVC2017 workaround
    ImplPrnQueueData( ImplPrnQueueData const & ) = delete; // MSVC2017 workaround
#endif
};

class VCL_PLUGIN_PUBLIC ImplPrnQueueList
{
public:
    std::unordered_map< OUString, sal_Int32 > m_aNameToIndex;
    std::vector< ImplPrnQueueData >     m_aQueueInfos;
    std::vector< OUString >             m_aPrinterList;

    ImplPrnQueueList() {}
    ~ImplPrnQueueList();

    ImplPrnQueueList& operator=( ImplPrnQueueList const & ) = delete; // MSVC2017 workaround
    ImplPrnQueueList( ImplPrnQueueList const & ) = delete; // MSVC2017 workaround

void                    Add( std::unique_ptr<SalPrinterQueueInfo> pData );
    ImplPrnQueueData*       Get( const OUString& rPrinter );
};

void ImplDeletePrnQueueList();
void ImplUpdateJobSetupPaper( JobSetup& rJobSetup );

#endif // INCLUDED_VCL_INC_PRINT_H

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
