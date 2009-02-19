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
static char const metainfo_cmdemotes[] =
"<?xml version=\"1.0\"?>"
"<!-- cmdemotes.csplugin -->"
"<plugin>"
"  <scf>"
"    <classes>"
"      <class>"
"        <name>peragro.commands.emotes</name>"
"        <implementation>cmdEmote</implementation>"
"        <description>Emote Commands</description>"
"      </class>"
"    </classes>"
"  </scf>"
"</plugin>"
;
  #ifndef cmdEmote_FACTORY_REGISTER_DEFINED 
  #define cmdEmote_FACTORY_REGISTER_DEFINED 
    SCF_DEFINE_FACTORY_FUNC_REGISTRATION(cmdEmote) 
  #endif

class cmdemotes
{
SCF_REGISTER_STATIC_LIBRARY(cmdemotes,metainfo_cmdemotes)
  #ifndef cmdEmote_FACTORY_REGISTERED 
  #define cmdEmote_FACTORY_REGISTERED 
    cmdEmote_StaticInit cmdEmote_static_init__; 
  #endif
public:
 cmdemotes();
};
cmdemotes::cmdemotes() {}

}