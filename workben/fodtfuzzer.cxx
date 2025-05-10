/* comment */

#include <tools/stream.hxx>
#include <vcl/FilterConfigItem.hxx>
#include "commonfuzzer.hxx"

extern "C" void* SwCreateDialogFactory()
{
    return nullptr;
}

extern "C" bool TestImportFODT(SvStream &rStream);

extern "C" int LLVMFuzzerInitialize(int *argc, char ***argv)
{
    TypicalFuzzerInitialize(argc, argv);
    return 0;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size)
{
    SvMemoryStream aStream(const_cast<uint8_t*>(data), size, StreamMode::READ);
    (void)TestImportFODT(aStream);
    return 0;
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
