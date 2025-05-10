/* comment */
#pragma once

#include <rtl/ustring.hxx>
#include <vcl/textdata.hxx>
#include <vcl/txtattr.hxx>
#include <vector>
#include <memory>

class TextCharAttribList
{
private:
    TextCharAttribList(const TextCharAttribList&) = delete;
    TextCharAttribList& operator=(const TextCharAttribList&) = delete;

    std::vector<std::unique_ptr<TextCharAttrib> > maAttribs;
    bool            mbHasEmptyAttribs;

public:
                    TextCharAttribList();
                    ~TextCharAttribList();

    void            Clear();
    sal_uInt16          Count() const               { return maAttribs.size(); }

    const TextCharAttrib& GetAttrib( sal_uInt16 n ) const { return *maAttribs[n]; }
    TextCharAttrib& GetAttrib( sal_uInt16 n )       { return *maAttribs[n]; }
    std::unique_ptr<TextCharAttrib>  RemoveAttrib( sal_uInt16 n )
    {
        std::unique_ptr<TextCharAttrib> pReleased = std::move(maAttribs[n]);
        maAttribs.erase( maAttribs.begin() + n );
        return pReleased;
    }

    void            InsertAttrib( std::unique_ptr<TextCharAttrib> pAttrib );

    void            DeleteEmptyAttribs();
    void            ResortAttribs();

    bool&           HasEmptyAttribs()       { return mbHasEmptyAttribs; }

    TextCharAttrib* FindAttrib( sal_uInt16 nWhich, sal_Int32 nPos );
    TextCharAttrib* FindEmptyAttrib( sal_uInt16 nWhich, sal_Int32 nPos );
    bool            HasBoundingAttrib( sal_Int32 nBound );
};

class TextNode
{
    OUString            maText;
    TextCharAttribList  maCharAttribs;

    void                ExpandAttribs( sal_Int32 nIndex, sal_Int32 nNewChars );
    void                CollapseAttribs( sal_Int32 nIndex, sal_Int32 nDelChars );

public:
                        TextNode( OUString aText );

    TextNode( const TextNode& ) = delete;
    void operator=( const TextNode& ) = delete;

    const OUString&     GetText() const         { return maText; }

    const TextCharAttrib&   GetCharAttrib(sal_uInt16 nPos) const  { return maCharAttribs.GetAttrib(nPos); }
    const TextCharAttribList&   GetCharAttribs() const  { return maCharAttribs; }
    TextCharAttribList&         GetCharAttribs()        { return maCharAttribs; }

    void                InsertText( sal_Int32 nPos, std::u16string_view rText );
    void                InsertText( sal_Int32 nPos, sal_Unicode c );
    void                RemoveText( sal_Int32 nPos, sal_Int32 nChars );

    std::unique_ptr<TextNode> Split( sal_Int32 nPos );
    void                Append( const TextNode& rNode );
};

class TextDoc
{
    std::vector<std::unique_ptr<TextNode>>  maTextNodes;
    sal_uInt16              mnLeftMargin;

    void                DestroyTextNodes();

public:
                        TextDoc();
                        ~TextDoc();

    void                Clear();

    std::vector<std::unique_ptr<TextNode>>&       GetNodes()              { return maTextNodes; }
    const std::vector<std::unique_ptr<TextNode>>& GetNodes() const        { return maTextNodes; }

    void                RemoveChars( const TextPaM& rPaM, sal_Int32 nChars );
    TextPaM             InsertText( const TextPaM& rPaM, sal_Unicode c );
    TextPaM             InsertText( const TextPaM& rPaM, std::u16string_view rStr );

    TextPaM             InsertParaBreak( const TextPaM& rPaM );
    TextPaM             ConnectParagraphs( TextNode* pLeft, const TextNode* pRight );

    sal_Int32           GetTextLen( const sal_Unicode* pSep, const TextSelection* pSel = nullptr ) const;
    OUString            GetText( const sal_Unicode* pSep ) const;
    OUString            GetText( sal_uInt32 nPara ) const;

    void                SetLeftMargin( sal_uInt16 n )   { mnLeftMargin = n; }
    sal_uInt16          GetLeftMargin() const       { return mnLeftMargin; }

    bool            IsValidPaM( const TextPaM& rPaM );
};

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
