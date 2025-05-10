/* comment */
#include <sal/config.h>

#include <vcl/NotebookbarContextControl.hxx>
#include <ContextVBox.hxx>

ContextVBox::ContextVBox( vcl::Window *pParent )
    : VclVBox( pParent )
{
}

ContextVBox::~ContextVBox()
{
    disposeOnce();
}

void ContextVBox::SetContext( vcl::EnumContext::Context eContext )
{
    for (int nChild = 0; nChild < GetChildCount(); ++nChild)
    {
        if ( GetChild( nChild )->GetType() == WindowType::CONTAINER )
        {
            VclContainer* pChild = static_cast<VclContainer*>( GetChild( nChild ) );

            if ( pChild->HasContext( eContext ) || pChild->HasContext( vcl::EnumContext::Context::Any ) )
            {
                Size aSize( pChild->GetOptimalSize() );
                aSize.AdjustHeight(6 );
                pChild->Show();
                pChild->SetSizePixel( aSize );
            }
            else
            {
                pChild->Hide();
                pChild->SetSizePixel( Size( 0, 0 ) );
            }
        }
    }
    Size aSize( GetOptimalSize() );
    aSize.AdjustWidth(6 );
    SetSizePixel( aSize );
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
