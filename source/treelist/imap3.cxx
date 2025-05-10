/* comment */
#include <vcl/imap.hxx>

#include <tools/debug.hxx>

/******************************************************************************
|*
|* Ctor
|*
\******************************************************************************/

IMapCompat::IMapCompat(SvStream& rStm, const StreamMode nStreamMode)
    : pRWStm(&rStm)
    , nCompatPos(0)
    , nTotalSize(0)
    , nStmMode(nStreamMode)
{
    DBG_ASSERT(nStreamMode == StreamMode::READ || nStreamMode == StreamMode::WRITE, "Wrong Mode!");

    if (pRWStm->GetError())
        return;

    if (nStmMode == StreamMode::WRITE)
    {
        nCompatPos = pRWStm->Tell();
        pRWStm->SeekRel(4);
        nTotalSize = nCompatPos + 4;
    }
    else
    {
        sal_uInt32 nTotalSizeTmp;
        pRWStm->ReadUInt32(nTotalSizeTmp);
        nTotalSize = nTotalSizeTmp;
        nCompatPos = pRWStm->Tell();
    }
}

/******************************************************************************
|*
|* Dtor
|*
\******************************************************************************/

IMapCompat::~IMapCompat()
{
    if (pRWStm->GetError())
        return;

    if (nStmMode == StreamMode::WRITE)
    {
        const sal_uInt64 nEndPos = pRWStm->Tell();

        pRWStm->Seek(nCompatPos);
        pRWStm->WriteUInt32(nEndPos - nTotalSize);
        pRWStm->Seek(nEndPos);
    }
    else
    {
        const sal_uInt64 nReadSize = pRWStm->Tell() - nCompatPos;

        if (nTotalSize > nReadSize)
            pRWStm->SeekRel(nTotalSize - nReadSize);
    }
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
