/* comment */

#include <unotest/filters-test.hxx>
#include <test/bootstrapfixture.hxx>
#include <vcl/FilterConfigItem.hxx>
#include <tools/stream.hxx>
#include <vcl/graph.hxx>
#include <filter/RasReader.hxx>

using namespace css;

/* Implementation of Filters test */

class RasFilterTest
    : public test::FiltersTest
    , public test::BootstrapFixture
{
public:
    RasFilterTest() : BootstrapFixture(true, false) {}

    virtual bool load(const OUString &,
        const OUString &rURL, const OUString &,
        SfxFilterFlags, SotClipboardFormatId, unsigned int) override;

    /**
     * Ensure CVEs remain unbroken
     */
    void testCVEs();

    CPPUNIT_TEST_SUITE(RasFilterTest);
    CPPUNIT_TEST(testCVEs);
    CPPUNIT_TEST_SUITE_END();
};

bool RasFilterTest::load(const OUString &,
    const OUString &rURL, const OUString &,
    SfxFilterFlags, SotClipboardFormatId, unsigned int)
{
    SvFileStream aFileStream(rURL, StreamMode::READ);
    Graphic aGraphic;
    return ImportRasGraphic(aFileStream, aGraphic);
}

void RasFilterTest::testCVEs()
{
#ifndef DISABLE_CVE_TESTS
    testDir(OUString(),
        m_directories.getURLFromSrc(u"/vcl/qa/cppunit/graphicfilter/data/ras/"));
#endif
}

CPPUNIT_TEST_SUITE_REGISTRATION(RasFilterTest);

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
