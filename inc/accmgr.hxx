/* comment */
#ifndef INCLUDED_VCL_INC_ACCMGR_HXX
#define INCLUDED_VCL_INC_ACCMGR_HXX

#include <vector>
#include <optional>

#include <vcl/keycod.hxx>

class Accelerator;

class ImplAccelManager
{
private:
    std::optional<std::vector< Accelerator* >> mxAccelList;
    std::optional<std::vector< Accelerator* >> mxSequenceList;

public:
                        ImplAccelManager()
                        {
                        }
                        ~ImplAccelManager();

    bool                InsertAccel( Accelerator* pAccel );
    void                RemoveAccel( Accelerator const * pAccel );

    void                EndSequence();
    void                FlushAccel() { EndSequence(); }

    bool                IsAccelKey( const vcl::KeyCode& rKeyCode );
};

#endif // INCLUDED_VCL_INC_ACCMGR_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
