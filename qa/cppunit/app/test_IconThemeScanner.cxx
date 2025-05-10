/* comment */

#include <stdexcept>

#include <rtl/ustring.hxx>
#include <IconThemeScanner.hxx>
#include <vcl/IconThemeInfo.hxx>

#include <cppunit/TestAssert.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class IconThemeScannerTest : public CppUnit::TestFixture
{
    void
    AddedThemeIsFoundById();

    void
    AddedThemeInfoIsReturned();

    void
    ExceptionIsThrownIfInvalidInfoIsRequested();

    // Adds code needed to register the test suite
    CPPUNIT_TEST_SUITE(IconThemeScannerTest);
    CPPUNIT_TEST(AddedThemeIsFoundById);
    CPPUNIT_TEST(AddedThemeInfoIsReturned);
    CPPUNIT_TEST(ExceptionIsThrownIfInvalidInfoIsRequested);

    // End of test suite definition
    CPPUNIT_TEST_SUITE_END();
};

void
IconThemeScannerTest::AddedThemeIsFoundById()
{
    vcl::IconThemeScanner scanner;
    scanner.AddIconThemeByPath("file:://images_katze.zip");
    OUString id = vcl::IconThemeInfo::FileNameToThemeId(u"images_katze.zip");
    bool found = scanner.IconThemeIsInstalled(id);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("icon theme could be added by url", true, found);
}

void
IconThemeScannerTest::AddedThemeInfoIsReturned()
{
    vcl::IconThemeScanner scanner;
    OUString theme("file:://images_katze.zip");
    scanner.AddIconThemeByPath(theme);
    OUString id = vcl::IconThemeInfo::FileNameToThemeId(u"images_katze.zip");
    const vcl::IconThemeInfo& info = scanner.GetIconThemeInfo(id);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("'katze' icon theme is found from id", theme, info.GetUrlToFile());
}

void
IconThemeScannerTest::ExceptionIsThrownIfInvalidInfoIsRequested()
{
    vcl::IconThemeScanner scanner;
    scanner.AddIconThemeByPath("file:://images_katze.zip");
    bool thrown = false;
    try
    {
        scanner.GetIconThemeInfo("hund");
    }
    catch (const std::runtime_error&)
    {
        thrown = true;
    }
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Exception is thrown if invalid theme info is requested", true, thrown);
}

// Put the test suite in the registry
CPPUNIT_TEST_SUITE_REGISTRATION(IconThemeScannerTest);

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
