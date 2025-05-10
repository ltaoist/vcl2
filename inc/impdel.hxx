/* comment */
#ifndef INCLUDED_VCL_IMPDEL_HXX
#define INCLUDED_VCL_IMPDEL_HXX

#include <algorithm>
#include <vector>

namespace vcl
{

class DeletionListener;

class DeletionNotifier
{
    std::vector< DeletionListener* > m_aListeners;
    protected:
    DeletionNotifier() {}

    ~DeletionNotifier()
    { notifyDelete(); }

    inline void notifyDelete();

    public:
    void addDel( DeletionListener* pListener )
    { m_aListeners.push_back( pListener ); }

    void removeDel( DeletionListener* pListener )
    { m_aListeners.erase(std::remove(m_aListeners.begin(), m_aListeners.end(), pListener), m_aListeners.end()); }
};

class DeletionListener
{
    DeletionNotifier*  m_pNotifier;
    public:
    DeletionListener( DeletionNotifier* pNotifier )
    :  m_pNotifier( pNotifier )
       {
           if( m_pNotifier )
               m_pNotifier->addDel( this );
       }
   ~DeletionListener()
   {
       if( m_pNotifier )
           m_pNotifier->removeDel( this );
   }
   void deleted() { m_pNotifier = nullptr; }
   bool isDeleted() const { return (m_pNotifier == nullptr); }
};

inline void DeletionNotifier::notifyDelete()
{
    for( auto& rListener : m_aListeners )
       rListener->deleted();

    m_aListeners.clear();
}

} // namespace vcl

#endif // INCLUDED_VCL_IMPDEL_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
