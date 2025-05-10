/* comment */#ifndef INCLUDED_FILTER_SOURCE_GRAPHICFILTER_IPICT_SHAPE_HXX
#define INCLUDED_FILTER_SOURCE_GRAPHICFILTER_IPICT_SHAPE_HXX

#include <vcl/virdev.hxx>

namespace PictReaderShape {
  /** draws a line from orig to dest knowing penSize

  Attention: in order to draw horizontal/vertical/small lines, this function can instead draw a rectangle or
        a polygon. In this case, we retrieve the line information from VirtualDev ( GetLineColor )
        and we use them as fill information ( SetFillColor ). We restore after the VirtualDev state.

        This implies also that this function must be modified if we use real pattern to draw these primitives.
   */
  void drawLine(VirtualDevice *dev, Point const &orig, Point const &dest, Size const &pSize);

  /** draws a rectangle knowing penSize */
  void drawRectangle(VirtualDevice *dev, bool drawFrame, tools::Rectangle const &rect, Size const &pSize);

  /** draws a polygon knowing penSize */
void drawPolygon(VirtualDevice *dev, bool drawFrame, tools::Polygon const &rect, Size const &pSize);

  /** draws an ellipse knowing penSize */
  void drawEllipse(VirtualDevice *dev, bool drawFrame, tools::Rectangle const &orig, Size const &pSize);

  /** draws a rounded rectangle knowing penSize
      \note ovalSize is two time the size of the corner
  */
  void drawRoundRectangle(VirtualDevice *dev, bool drawFrame, tools::Rectangle const &orig, Size const &ovalS, Size const &pSize);

  /** draws an arc in a b2dpolygon knowing penSize
      \note  - it supposes that angl1 < angl2
  */
  void drawArc(VirtualDevice *dev, bool drawFrame, tools::Rectangle const &orig, const double& angle1, const double& angle2, Size const &pSize);
}

#endif // INCLUDED_FILTER_SOURCE_GRAPHICFILTER_IPICT_SHAPE_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
