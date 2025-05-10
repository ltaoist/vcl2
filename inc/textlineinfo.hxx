/* comment */
#ifndef INCLUDED_VCL_INC_TEXTLINEINFO_HXX
#define INCLUDED_VCL_INC_TEXTLINEINFO_HXX

#include <memory>
#include <vector>

class ImplTextLineInfo
{
private:
    tools::Long        mnWidth;
    sal_Int32   mnIndex;
    sal_Int32   mnLen;

public:
   ImplTextLineInfo( tools::Long nWidth, sal_Int32 nIndex, sal_Int32 nLen )
   {
       mnWidth = nWidth;
       mnIndex = nIndex;
       mnLen   = nLen;
   }

    tools::Long       GetWidth() const { return mnWidth; }
    sal_Int32  GetIndex() const { return mnIndex; }
    sal_Int32  GetLen() const { return mnLen; }
};

#define MULTITEXTLINEINFO_RESIZE    16

class ImplMultiTextLineInfo
{
public:
                ImplMultiTextLineInfo();
                ~ImplMultiTextLineInfo();

    void        AddLine( const ImplTextLineInfo& );
    void        Clear();

    const ImplTextLineInfo& GetLine( sal_Int32 nLine ) const
                            { return mvLines[nLine]; }
    ImplTextLineInfo& GetLine( sal_Int32 nLine )
                            { return mvLines[nLine]; }
    sal_Int32   Count() const { return mvLines.size(); }

private:
    ImplMultiTextLineInfo( const ImplMultiTextLineInfo& ) = delete;
    ImplMultiTextLineInfo& operator=( const ImplMultiTextLineInfo& ) = delete;

    std::vector<ImplTextLineInfo>  mvLines;

};

#endif // INCLUDED_VCL_INC_TEXTLINEINFO_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
