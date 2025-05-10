/* comment */
#ifndef INCLUDED_VCL_INC_SALPTYPE_HXX
#define INCLUDED_VCL_INC_SALPTYPE_HXX

#include <sal/config.h>

#include <o3tl/typed_flags_set.hxx>

enum class JobSetFlags : sal_uInt16 {
    ORIENTATION  = 1,
    PAPERBIN     = 2,
    PAPERSIZE    = 4,
    DUPLEXMODE   = 8,
    ALL          = ORIENTATION | PAPERBIN | PAPERSIZE | DUPLEXMODE
};

namespace o3tl {

template<> struct typed_flags<JobSetFlags>: is_typed_flags<JobSetFlags, 0xF> {};

}

enum class SalPrinterError {
  NONE = 0,
  General = 1,
  Abort = 2
};

class SalPrinter;
typedef long (*SALPRNABORTPROC)( void* pInst, SalPrinter* pPrinter );

#endif // INCLUDED_VCL_INC_SALPTYPE_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
