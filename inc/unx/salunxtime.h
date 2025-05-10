/* comment */
#ifndef INCLUDED_VCL_INC_UNX_SALUNXTIME_H
#define INCLUDED_VCL_INC_UNX_SALUNXTIME_H

#if defined LINUX || defined FREEBSD || \
    defined NETBSD || defined OPENBSD || defined DRAGONFLY
#include <sys/time.h>
#elif defined AIX
#include <time.h>
#include <sys/time.h>
#include <strings.h>
#endif
#include <sal/types.h>

inline bool operator >= ( const timeval &t1, const timeval &t2 )
{
    if( t1.tv_sec == t2.tv_sec )
        return t1.tv_usec >= t2.tv_usec;
    return t1.tv_sec > t2.tv_sec;
}

inline bool operator > ( const timeval &t1, const timeval &t2 )
{
    if( t1.tv_sec == t2.tv_sec )
        return t1.tv_usec > t2.tv_usec;
    return t1.tv_sec > t2.tv_sec;
}

inline timeval &operator -= ( timeval &t1, const timeval &t2 )
{
    if( t1.tv_usec < t2.tv_usec )
    {
        t1.tv_sec--;
        t1.tv_usec += 1000000;
    }
    t1.tv_sec  -= t2.tv_sec;
    t1.tv_usec -= t2.tv_usec;
    return t1;
}

inline timeval &operator += ( timeval &t1, sal_uIntPtr t2 )
{
    t1.tv_sec  += t2 / 1000;
    t1.tv_usec += (t2 % 1000) * 1000;
    if( t1.tv_usec > 1000000 )
    {
        t1.tv_sec++;
        t1.tv_usec -= 1000000;
    }
    return t1;
}

inline timeval operator - ( const timeval &t1, const timeval &t2 )
{
    timeval t0 = t1;
    t0 -= t2;
    return t0;
}

#endif // INCLUDED_VCL_INC_UNX_SALUNXTIME_H

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
