/* comment */
#ifndef INCLUDED_VCL_JOBDATA_HXX
#define INCLUDED_VCL_JOBDATA_HXX

#include "ppdparser.hxx"

namespace psp {

enum class orientation {
    Portrait,
    Landscape
};

struct VCL_DLLPUBLIC JobData
{
    int                     m_nCopies;
    bool                    m_bCollate;
    int                     m_nLeftMarginAdjust;
    int                     m_nRightMarginAdjust;
    int                     m_nTopMarginAdjust;
    int                     m_nBottomMarginAdjust;
    // user overrides for PPD
    int                     m_nColorDepth;
    int                     m_nPSLevel;     // 0: no override, else languagelevel to use
    int                     m_nColorDevice; // 0: no override, -1 grey scale, +1 color
    int                     m_nPDFDevice;   // 0: no override, -1 PostScript, +1: Automatically PDF, +2: Explicitly PDF
    orientation             m_eOrientation;
    OUString                m_aPrinterName;
    bool                    m_bPapersizeFromSetup;
    const PPDParser*        m_pParser;
    PPDContext              m_aContext;

    JobData() :
            m_nCopies( 1 ),
            m_bCollate(false),
            m_nLeftMarginAdjust( 0 ),
            m_nRightMarginAdjust( 0 ),
            m_nTopMarginAdjust( 0 ),
            m_nBottomMarginAdjust( 0 ),
            m_nColorDepth( 24 ),
            m_nPSLevel( 0 ),
            m_nColorDevice( 0 ),
            m_nPDFDevice( 0 ),
            m_eOrientation( orientation::Portrait ),
            m_bPapersizeFromSetup( false ),
            m_pParser( nullptr ) {}

    JobData& operator=(const psp::JobData& rRight);

    JobData( const JobData& rData ) { *this = rData; }

    void setCollate( bool bCollate );
    void setPaper( int nWidth, int nHeight ); // dimensions in pt
    void setPaperBin( int nPaperBin );
    void resolveDefaultBackend();
    void setDefaultBackend(bool bUsePDF);

    // creates a new buffer using new
    // it is up to the user to delete it again
    bool getStreamBuffer( void*& pData, sal_uInt32& bytes );
    static bool constructFromStreamBuffer( const void* pData, sal_uInt32 bytes, JobData& rJobData );
};

} // namespace


#endif // PSPRINT_JOBDATA_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
