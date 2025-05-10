/* comment */

#include <unotest/filters-test.hxx>
#include <test/bootstrapfixture.hxx>
#include <vcl/FilterConfigItem.hxx>
#include <tools/stream.hxx>
#include <vcl/graph.hxx>
#include <vcl/graphicfilter.hxx>
#include <filter/PsdReader.hxx>

using namespace css;

/* Implementation of Filters test */

class PsdFilterTest
    : public test::FiltersTest
    , public test::BootstrapFixture
{
public:
    PsdFilterTest() : BootstrapFixture(true, false) {}

    virtual bool load(const OUString &,
        const OUString &rURL, const OUString &,
        SfxFilterFlags, SotClipboardFormatId, unsigned int) override;

    OUString getUrl() const
    {
        return m_directories.getURLFromSrc(u"/vcl/qa/cppunit/graphicfilter/data/psd/");
    }

    /**
     * Ensure CVEs remain unbroken
     */
    void testCVEs();
    void testTdf142629();

    CPPUNIT_TEST_SUITE(PsdFilterTest);
    CPPUNIT_TEST(testCVEs);
    CPPUNIT_TEST(testTdf142629);
    CPPUNIT_TEST_SUITE_END();
};

bool PsdFilterTest::load(const OUString &,
    const OUString &rURL, const OUString &,
    SfxFilterFlags, SotClipboardFormatId, unsigned int)
{
    SvFileStream aFileStream(rURL, StreamMode::READ);
    Graphic aGraphic;
    return ImportPsdGraphic(aFileStream, aGraphic);
}

void PsdFilterTest::testCVEs()
{
#ifndef DISABLE_CVE_TESTS
    testDir(OUString(), getUrl());
#endif
}

void PsdFilterTest::testTdf142629()
{
    OUString aURL = getUrl() + "tdf142629.psd";
    SvFileStream aFileStream(aURL, StreamMode::READ);
    Graphic aGraphic;
    GraphicFilter& rFilter = GraphicFilter::GetGraphicFilter();

    ErrCode bResult = rFilter.ImportGraphic(aGraphic, aURL, aFileStream);

    // Without the fix in place, the following asserts would have failed
    CPPUNIT_ASSERT_EQUAL(ERRCODE_NONE, bResult);

    CPPUNIT_ASSERT(aGraphic.IsAlpha());
    CPPUNIT_ASSERT(aGraphic.IsTransparent());
}

CPPUNIT_TEST_SUITE_REGISTRATION(PsdFilterTest);

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
