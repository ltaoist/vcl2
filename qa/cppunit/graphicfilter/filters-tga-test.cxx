/* comment */

#include <unotest/filters-test.hxx>
#include <test/bootstrapfixture.hxx>
#include <vcl/FilterConfigItem.hxx>
#include <tools/stream.hxx>
#include <vcl/graph.hxx>
#include <filter/TgaReader.hxx>

using namespace ::com::sun::star;

/* Implementation of Filters test */

class TgaFilterTest
    : public test::FiltersTest
    , public test::BootstrapFixture
{
public:
    TgaFilterTest() : BootstrapFixture(true, false) {}

    virtual bool load(const OUString &,
        const OUString &rURL, const OUString &,
        SfxFilterFlags, SotClipboardFormatId, unsigned int) override;

    /**
     * Ensure CVEs remain unbroken
     */
    void testCVEs();

    CPPUNIT_TEST_SUITE(TgaFilterTest);
    CPPUNIT_TEST(testCVEs);
    CPPUNIT_TEST_SUITE_END();
};

bool TgaFilterTest::load(const OUString &,
    const OUString &rURL, const OUString &,
    SfxFilterFlags, SotClipboardFormatId, unsigned int)
{
    SvFileStream aFileStream(rURL, StreamMode::READ);
    Graphic aGraphic;
    return ImportTgaGraphic(aFileStream, aGraphic);
}

void TgaFilterTest::testCVEs()
{
#ifndef DISABLE_CVE_TESTS
    testDir(OUString(), m_directories.getURLFromSrc(u"/vcl/qa/cppunit/graphicfilter/data/tga/"));
#endif
}

CPPUNIT_TEST_SUITE_REGISTRATION(TgaFilterTest);

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
