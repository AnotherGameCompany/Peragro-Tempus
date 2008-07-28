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
static char const metainfo_terrained[] =
"<?xml version=\"1.0\"?>"
"<!-- terrained.csplugin -->"
"<plugin>"
"  <scf>"
"    <classes>"
"      <class>"
"        <name>peragro.terrained</name>"
"        <implementation>TerrainEd</implementation>"
"        <description>TerrainEd</description>"
"      </class>"
"    </classes>"
"  </scf>"
"</plugin>"
;
  #ifndef TerrainEd_FACTORY_REGISTER_DEFINED 
  #define TerrainEd_FACTORY_REGISTER_DEFINED 
    SCF_DEFINE_FACTORY_FUNC_REGISTRATION(TerrainEd) 
  #endif

class terrained
{
SCF_REGISTER_STATIC_LIBRARY(terrained,metainfo_terrained)
  #ifndef TerrainEd_FACTORY_REGISTERED 
  #define TerrainEd_FACTORY_REGISTERED 
    TerrainEd_StaticInit TerrainEd_static_init__; 
  #endif
public:
 terrained();
};
terrained::terrained() {}

}
