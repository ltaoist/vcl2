/* comment */

#include <svl/lockfilecommon.hxx>
#include "commonfuzzer.hxx"

#include <config_features.h>
#include <com/sun/star/io/WrongFormatException.hpp>
#include <osl/detail/component-mapping.h>

const lib_to_factory_mapping* lo_get_factory_map(void)
{
    static lib_to_factory_mapping map[] = { { 0, 0 } };

    return map;
}

const lib_to_constructor_mapping* lo_get_constructor_map(void)
{
    static lib_to_constructor_mapping map[] = { { 0, 0 } };

    return map;
}

extern "C" void* lo_get_custom_widget_func(const char*) { return nullptr; }

extern "C" int LLVMFuzzerInitialize(int* argc, char*** argv)
{
    TypicalFuzzerInitialize(argc, argv);
    return 0;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size)
{
    sal_Int32 nCurPos(0);
    css::uno::Sequence<sal_Int8> aBuffer(reinterpret_cast<const sal_Int8*>(data), size);
    try
    {
        svt::LockFileCommon::ParseEntry(aBuffer, nCurPos);
    }
    catch (const css::io::WrongFormatException&)
    {
    }
    return 0;
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
