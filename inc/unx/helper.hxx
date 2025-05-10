/* comment */
#ifndef INCLUDED_VCL_INC_UNX_HELPER_HXX
#define INCLUDED_VCL_INC_UNX_HELPER_HXX

#include <vector>

#include <rtl/ustring.hxx>


// forwards
namespace osl { class File; }

namespace psp
{

void getPrinterPathList( std::vector< OUString >& rPathList, const char* pSubDir );

OUString const & getFontPath();

// normalized path (equivalent to realpath)
void normPath( OString& rPath );

// splits rOrgPath into dirname and basename
// rOrgPath will be subject to normPath
void splitPath( OString& rOrgPath, OString& rDir, OString& rBase );

enum class whichOfficePath { InstallationRootPath, UserPath, ConfigPath };

OUString getOfficePath( whichOfficePath ePath );

} // namespace


#endif // INCLUDED_VCL_INC_UNX_HELPER_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
