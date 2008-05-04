// This file is automatically generated.
#include "cssysdef.h"
#include "csutil/scf.h"

// Put static linking stuff into own section.
// The idea is that this allows the section to be swapped out but not
// swapped in again b/c something else in it was needed.
#if !defined(CS_DEBUG) && defined(CS_COMPILER_MSVC)
#pragma const_seg(".CSmetai")
#pragma comment(linker, "/section:.CSmetai,r")
#pragma code_seg(".CSmeta")
#pragma comment(linker, "/section:.CSmeta,er")
#pragma comment(linker, "/merge:.CSmetai=.CSmeta")
#endif

namespace csStaticPluginInit
{
static char const metainfo_loader_starbox[] =
"<?xml version=\"1.0\"?>"
"<!-- loader_starbox.csplugin -->"
"<plugin>"
"  <scf>"
"    <classes>"
"      <class>"
"        <name>recon69.loader.starbox</name>"
"        <implementation>myLoaderStarbox</implementation>"
"        <description>Loader plugin for starbox objects</description>"
"        <requires>recon69.starboxfactory</requires>"
"      </class>"
"    </classes>"
"  </scf>"
"</plugin>"
;
  #ifndef myLoaderStarbox_FACTORY_REGISTER_DEFINED 
  #define myLoaderStarbox_FACTORY_REGISTER_DEFINED 
    SCF_DEFINE_FACTORY_FUNC_REGISTRATION(myLoaderStarbox) 
  #endif

class loader_starbox
{
SCF_REGISTER_STATIC_LIBRARY(loader_starbox,metainfo_loader_starbox)
  #ifndef myLoaderStarbox_FACTORY_REGISTERED 
  #define myLoaderStarbox_FACTORY_REGISTERED 
    myLoaderStarbox_StaticInit myLoaderStarbox_static_init__; 
  #endif
public:
 loader_starbox();
};
loader_starbox::loader_starbox() {}

}