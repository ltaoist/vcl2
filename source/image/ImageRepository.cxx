/* comment */
#include <vcl/bitmapex.hxx>
#include <imagerepository.hxx>
#include <vcl/ImageTree.hxx>
#include <vcl/settings.hxx>
#include <vcl/svapp.hxx>

namespace vcl
{
    bool ImageRepository::loadImage( const OUString& _rName, BitmapEx& _out_rImage )
    {
        OUString sIconTheme = Application::GetSettings().GetStyleSettings().DetermineIconTheme();

        return ImageTree::get().loadImage( _rName, sIconTheme, _out_rImage, false/*_bSearchLanguageDependent*/ );
    }

} // namespace vcl

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
