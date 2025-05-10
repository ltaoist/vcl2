/* comment */

#include <stdexcept>

#include <rtl/ustring.hxx>
#include <vcl/IconThemeInfo.hxx>

#include <cppunit/TestAssert.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace vcl;

class IconThemeInfoTest : public CppUnit::TestFixture
{
    void
    UpperCaseDisplayNameIsReturnedForNonDefaultId();

    void
    ImagesZipIsNotValid();

    void
    ImagesColibreZipIsValid();

    void
    ThemeIdIsDetectedFromFileNameWithUnderscore();

    void
    ExceptionIsThrownWhenIdCannotBeDetermined1();

    void
    ExceptionIsThrownWhenIdCannotBeDetermined2();

    // Adds code needed to register the test suite
    CPPUNIT_TEST_SUITE(IconThemeInfoTest);
    CPPUNIT_TEST(UpperCaseDisplayNameIsReturnedForNonDefaultId);
    CPPUNIT_TEST(ThemeIdIsDetectedFromFileNameWithUnderscore);
    CPPUNIT_TEST(ImagesZipIsNotValid);
    CPPUNIT_TEST(ImagesColibreZipIsValid);
    CPPUNIT_TEST(ExceptionIsThrownWhenIdCannotBeDetermined1);
    CPPUNIT_TEST(ExceptionIsThrownWhenIdCannotBeDetermined2);

    // End of test suite definition
    CPPUNIT_TEST_SUITE_END();
};

void
IconThemeInfoTest::UpperCaseDisplayNameIsReturnedForNonDefaultId()
{
    OUString displayName = vcl::IconThemeInfo::ThemeIdToDisplayName("katze");
    CPPUNIT_ASSERT_EQUAL_MESSAGE("theme id is properly uppercased", OUString("Katze"), displayName);
}

void
IconThemeInfoTest::ImagesZipIsNotValid()
{
    bool valid = vcl::IconThemeInfo::UrlCanBeParsed(u"file://images.zip");
    CPPUNIT_ASSERT_EQUAL_MESSAGE("images.zip is not a valid theme name", false, valid);
}

void
IconThemeInfoTest::ImagesColibreZipIsValid()
{
    bool valid = vcl::IconThemeInfo::UrlCanBeParsed(u"file://images_colibre.zip");
    CPPUNIT_ASSERT_EQUAL_MESSAGE("images_colibre.zip is a valid theme name", true, valid);
}

void
IconThemeInfoTest::ThemeIdIsDetectedFromFileNameWithUnderscore()
{
    OUString sname = vcl::IconThemeInfo::FileNameToThemeId(u"images_colibre.zip");
    CPPUNIT_ASSERT_EQUAL_MESSAGE("'colibre' theme id is returned for 'images_colibre.zip'", OUString("colibre"), sname);
}

void
IconThemeInfoTest::ExceptionIsThrownWhenIdCannotBeDetermined1()
{
    bool thrown = false;
    try {
        vcl::IconThemeInfo::FileNameToThemeId(u"images_colibre");
    }
    catch (std::runtime_error&) {
        thrown = true;
    }
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Exception was thrown",true, thrown);
}

void
IconThemeInfoTest::ExceptionIsThrownWhenIdCannotBeDetermined2()
{
    bool thrown = false;
    try {
        vcl::IconThemeInfo::FileNameToThemeId(u"image_colibre.zip");
    }
    catch (std::runtime_error&) {
        thrown = true;
    }
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Exception was thrown", true, thrown);
}

// Put the test suite in the registry
CPPUNIT_TEST_SUITE_REGISTRATION(IconThemeInfoTest);

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
