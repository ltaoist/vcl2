/* comment */
#pragma once

#include <vcl/gdimtf.hxx>

namespace tools { class PolyPolygon; }

namespace ImplVectorizer
{
    bool     ImplVectorize( const Bitmap& rColorBmp, GDIMetaFile& rMtf,
                            sal_uInt8 cReduce, const Link<tools::Long,void>* pProgress );
};

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
