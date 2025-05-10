/* comment */
#pragma once

#include <unx/genprn.h>

class SalFrame;

class QtPrinter final : public PspSalPrinter
{
public:
    QtPrinter(SalInfoPrinter* pInfoPrinter);
};

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
