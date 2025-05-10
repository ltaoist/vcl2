/* comment */#pragma once

#include <svl/undo.hxx>
#include <vcl/texteng.hxx>

class TextEngine;
class TextView;
class TextSelection;
class TextDoc;
class TEParaPortions;

class TextUndoManager : public SfxUndoManager
{
    TextEngine*     mpTextEngine;

protected:

    void            UndoRedoStart();
    void            UndoRedoEnd();

    TextView*       GetView() const { return mpTextEngine->GetActiveView(); }

public:
    explicit TextUndoManager( TextEngine* pTextEngine );
    virtual ~TextUndoManager() override;

    using SfxUndoManager::Undo;
    virtual bool Undo() override;
    using SfxUndoManager::Redo;
    virtual bool Redo() override;

};

class TextUndo : public SfxUndoAction
{
private:
    TextEngine*         mpTextEngine;

protected:

    TextView*           GetView() const { return mpTextEngine->GetActiveView(); }
    void                SetSelection( const TextSelection& rSel );

    TextDoc*            GetDoc() const { return mpTextEngine->mpDoc.get(); }
    TEParaPortions*     GetTEParaPortions() const { return mpTextEngine->mpTEParaPortions.get(); }

public:
    explicit            TextUndo( TextEngine* pTextEngine );
    virtual             ~TextUndo() override;

    TextEngine*         GetTextEngine() const   { return mpTextEngine; }

    virtual void        Undo() override      = 0;
    virtual void        Redo() override      = 0;

    virtual OUString GetComment() const override;
};

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
