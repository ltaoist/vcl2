/* comment */
#ifndef INCLUDED_VCL_RESAMPLEKERNEL_HXX
#define INCLUDED_VCL_RESAMPLEKERNEL_HXX

#include <boost/math/special_functions/sinc.hpp>

namespace vcl {

// Resample kernels

class Kernel
{
public:
             Kernel() {}
    virtual ~Kernel() {}

    virtual double  GetWidth() const = 0;
    virtual double  Calculate( double x ) const = 0;
};

class Lanczos3Kernel final : public Kernel
{
public:
    Lanczos3Kernel() : Kernel () {}

    virtual double  GetWidth() const override { return 3.0; }
    virtual double  Calculate (double x) const override
    {
        return (-3.0 <= x && x < 3.0) ? SincFilter(x) * SincFilter( x / 3.0 ) : 0.0;
    }

    static double SincFilter(double x)
    {
        if (x == 0.0)
        {
            return 1.0;
        }
        x = x * M_PI;
        return boost::math::sinc_pi(x, SincPolicy());
    }

private:
    typedef boost::math::policies::policy<
        boost::math::policies::promote_double<false> > SincPolicy;
};

class BicubicKernel final : public Kernel
{
public:
    BicubicKernel() : Kernel () {}

private:
    virtual double  GetWidth() const override { return 2.0; }
    virtual double  Calculate (double x) const override
    {
        if (x < 0.0)
        {
            x = -x;
        }

        if (x <= 1.0)
        {
            return (1.5 * x - 2.5) * x * x + 1.0;
        }
        else if (x < 2.0)
        {
            return ((-0.5 * x + 2.5) * x - 4) * x + 2;
        }
        return 0.0;
    }
};

class BilinearKernel final : public Kernel
{
public:
    BilinearKernel() : Kernel () {}

private:
    virtual double  GetWidth() const override { return 1.0; }
    virtual double  Calculate (double x) const override
    {
        if (x < 0.0)
        {
            x = -x;
        }
        if (x < 1.0)
        {
            return 1.0-x;
        }
        return 0.0;
    }
};

} // namespace vcl

#endif // INCLUDED_VCL_RESAMPLEKERNEL_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
