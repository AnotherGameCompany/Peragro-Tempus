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
static char const metainfo_cmdquit[] =
"<?xml version=\"1.0\"?>"
"<!-- cmdquit.csplugin -->"
"<plugin>"
"  <scf>"
"    <classes>"
"      <class>"
"        <name>peragro.commands.quit</name>"
"        <implementation>cmdQuit</implementation>"
"        <description>Quit Command</description>"
"      </class>"
"    </classes>"
"  </scf>"
"</plugin>"
;
  #ifndef cmdQuit_FACTORY_REGISTER_DEFINED 
  #define cmdQuit_FACTORY_REGISTER_DEFINED 
    SCF_DEFINE_FACTORY_FUNC_REGISTRATION(cmdQuit) 
  #endif

class cmdquit
{
SCF_REGISTER_STATIC_LIBRARY(cmdquit,metainfo_cmdquit)
  #ifndef cmdQuit_FACTORY_REGISTERED 
  #define cmdQuit_FACTORY_REGISTERED 
    cmdQuit_StaticInit cmdQuit_static_init__; 
  #endif
public:
 cmdquit();
};
cmdquit::cmdquit() {}

}