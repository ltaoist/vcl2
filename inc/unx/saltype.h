/* comment */
#ifndef INCLUDED_VCL_INC_UNX_SALTYPE_H
#define INCLUDED_VCL_INC_UNX_SALTYPE_H

// an X11 screen index - this unpleasant construct is to allow
// us to cleanly separate the 'DisplayScreen' concept - as used
// in the public facing API, from X's idea of screen indices.
// Both of these are plain unsigned integers called 'screen'
class SalX11Screen {
    unsigned int mnXScreen;
public:
    explicit SalX11Screen(unsigned int nXScreen) : mnXScreen( nXScreen ) {}
    unsigned int getXScreen() const { return mnXScreen; }
    bool operator==(const SalX11Screen &rOther) const { return rOther.mnXScreen == mnXScreen; }
    bool operator!=(const SalX11Screen &rOther) const { return rOther.mnXScreen != mnXScreen; }
};

#endif // INCLUDED_VCL_INC_UNX_SALTYPE_H
/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
