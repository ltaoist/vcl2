/* comment */#ifndef INCLUDED_VCL_HYPERLABEL_HXX
#define INCLUDED_VCL_HYPERLABEL_HXX

#include <memory>

#include <vcl/toolkit/fixed.hxx>

namespace vcl
{
    class HyperLabel final : public FixedText
    {
        Link<HyperLabel*,void>  maClickHdl;

        virtual void        MouseMove( const MouseEvent& rMEvt ) override;
        virtual void        MouseButtonDown( const MouseEvent& rMEvt ) override;
        virtual void        GetFocus() override;
        virtual void        LoseFocus() override;

        void                implInit();

        using FixedText::CalcMinimumSize;

    public:
        HyperLabel( vcl::Window* _pParent, WinBits _nWinStyle );
        virtual ~HyperLabel( ) override;

        virtual void    DataChanged( const DataChangedEvent& rDCEvt ) override;
        virtual void    ApplySettings(vcl::RenderContext& rRenderContext) override;

        void                SetID( sal_Int16 ID );
        sal_Int16           GetID() const;

        void                SetIndex( sal_Int32 Index );
        sal_Int32           GetIndex() const;

        void                SetLabel( const OUString& _rText );

        void                ToggleBackgroundColor( const Color& _rGBColor );
        void                SetInteractive( bool _bInteractive );

        void                SetClickHdl( const Link<HyperLabel*,void>& rLink ) { maClickHdl = rLink; }

        Size const &        CalcMinimumSize( tools::Long nMaxWidth );
    private:
        sal_Int16           ID;
        sal_Int32           Index;
        bool                bInteractive;
        Size                m_aMinSize;
        bool                m_bHyperMode;
    };
}

#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
