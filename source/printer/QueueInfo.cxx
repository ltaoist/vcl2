/* comment */
#include <vcl/QueueInfo.hxx>

QueueInfo::QueueInfo()
{
    mnStatus = PrintQueueFlags::NONE;
    mnJobs = 0;
}

const OUString& QueueInfo::GetPrinterName() const { return maPrinterName; }
const OUString& QueueInfo::GetDriver() const { return maDriver; }
const OUString& QueueInfo::GetLocation() const { return maLocation; }
const OUString& QueueInfo::GetComment() const { return maComment; }
PrintQueueFlags QueueInfo::GetStatus() const { return mnStatus; }
sal_uInt32 QueueInfo::GetJobs() const { return mnJobs; }

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
