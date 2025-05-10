/* comment */
#include <sal/log.hxx>

#include <vcl/metaact.hxx>
#include <vcl/print.hxx>
#include <vcl/printer/Options.hxx>

#include <utility>
#include <vector>

void Printer::DrawGradientEx( OutputDevice* pOut, const tools::Rectangle& rRect, const Gradient& rGradient )
{
    const vcl::printer::Options& rPrinterOptions = GetPrinterOptions();

    if( rPrinterOptions.IsReduceGradients() )
    {
        if( vcl::printer::GradientMode::Stripes == rPrinterOptions.GetReducedGradientMode() )
        {
            if( !rGradient.GetSteps() || ( rGradient.GetSteps() > rPrinterOptions.GetReducedGradientStepCount() ) )
            {
                Gradient aNewGradient( rGradient );

                aNewGradient.SetSteps( rPrinterOptions.GetReducedGradientStepCount() );
                pOut->DrawGradient( rRect, aNewGradient );
            }
            else
                pOut->DrawGradient( rRect, rGradient );
        }
        else
        {
            const Color&    rStartColor = rGradient.GetStartColor();
            const Color&    rEndColor = rGradient.GetEndColor();
            const tools::Long      nR = ( ( static_cast<tools::Long>(rStartColor.GetRed()) * rGradient.GetStartIntensity() ) / 100 +
                                   ( static_cast<tools::Long>(rEndColor.GetRed()) * rGradient.GetEndIntensity() ) / 100 ) >> 1;
            const tools::Long      nG = ( ( static_cast<tools::Long>(rStartColor.GetGreen()) * rGradient.GetStartIntensity() ) / 100 +
                                   ( static_cast<tools::Long>(rEndColor.GetGreen()) * rGradient.GetEndIntensity() ) / 100 ) >> 1;
            const tools::Long      nB = ( ( static_cast<tools::Long>(rStartColor.GetBlue()) * rGradient.GetStartIntensity() ) / 100 +
                                   ( static_cast<tools::Long>(rEndColor.GetBlue()) * rGradient.GetEndIntensity() ) / 100 ) >> 1;
            const Color     aColor( static_cast<sal_uInt8>(nR), static_cast<sal_uInt8>(nG), static_cast<sal_uInt8>(nB) );

            pOut->Push( vcl::PushFlags::LINECOLOR | vcl::PushFlags::FILLCOLOR );
            pOut->SetLineColor( aColor );
            pOut->SetFillColor( aColor );
            pOut->DrawRect( rRect );
            pOut->Pop();
        }
    }
    else
        pOut->DrawGradient( rRect, rGradient );
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
