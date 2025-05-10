/* comment */#pragma once

#include "textundo.hxx"
#include <vcl/textdata.hxx>

class TextUndoDelPara : public TextUndo
{
private:
    bool            mbDelObject;
    sal_uInt32      mnPara;
    TextNode*       mpNode; // points at the valid not-destroyed object

public:
                    TextUndoDelPara( TextEngine* pTextEngine, TextNode* pNode, sal_uInt32 nPara );
                    virtual ~TextUndoDelPara() override;

    virtual void    Undo() override;
    virtual void    Redo() override;

    virtual OUString GetComment () const override;
};

class TextUndoConnectParas : public TextUndo
{
private:
    sal_uInt32          mnPara;
    sal_Int32           mnSepPos;

public:
                    TextUndoConnectParas( TextEngine* pTextEngine, sal_uInt32 nPara, sal_Int32 nSepPos );
                    virtual ~TextUndoConnectParas() override;

    virtual void    Undo() override;
    virtual void    Redo() override;

    virtual OUString GetComment () const override;
};

class TextUndoSplitPara : public TextUndo
{
private:
    sal_uInt32          mnPara;
    sal_Int32           mnSepPos;

public:
                    TextUndoSplitPara( TextEngine* pTextEngine, sal_uInt32 nPara, sal_Int32 nSepPos );
                    virtual ~TextUndoSplitPara() override;

    virtual void    Undo() override;
    virtual void    Redo() override;

    virtual OUString GetComment () const override;
};

class TextUndoInsertChars : public TextUndo
{
private:
    TextPaM         maTextPaM;
    OUString        maText;

public:
                    TextUndoInsertChars( TextEngine* pTextEngine, const TextPaM& rTextPaM, OUString aStr );

    virtual void    Undo() override;
    virtual void    Redo() override;

    virtual bool    Merge( SfxUndoAction *pNextAction ) override;

    virtual OUString GetComment () const override;
};

class TextUndoRemoveChars : public TextUndo
{
private:
    TextPaM         maTextPaM;
    OUString        maText;

public:
                    TextUndoRemoveChars( TextEngine* pTextEngine, const TextPaM& rTextPaM, OUString aStr );

    virtual void    Undo() override;
    virtual void    Redo() override;

    virtual OUString GetComment () const override;
};

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
