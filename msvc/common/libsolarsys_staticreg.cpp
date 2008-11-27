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
static char const metainfo_solarsys[] =
"<?xml version=\"1.0\"?>"
"<plugin>"
"  <scf>"
"    <classes>"
"      <class>"
"        <name>recon69.solarsysfactory</name>"
"        <implementation>SolarsysFactory</implementation>"
"        <description>A plugin for creating a solar system back drop.</description>"
"	<requires>peragro.environment.starboxfactory</requires>"
"	<requires>recon69.mybodyfactory</requires>"
"	<requires>peragro.environment.starboxfactory</requires>"
"      </class>     "
"    </classes>"
"  </scf>"
"</plugin>"
;
  #ifndef SolarsysFactory_FACTORY_REGISTER_DEFINED 
  #define SolarsysFactory_FACTORY_REGISTER_DEFINED 
    SCF_DEFINE_FACTORY_FUNC_REGISTRATION(SolarsysFactory) 
  #endif

class solarsys
{
SCF_REGISTER_STATIC_LIBRARY(solarsys,metainfo_solarsys)
  #ifndef SolarsysFactory_FACTORY_REGISTERED 
  #define SolarsysFactory_FACTORY_REGISTERED 
    SolarsysFactory_StaticInit SolarsysFactory_static_init__; 
  #endif
public:
 solarsys();
};
solarsys::solarsys() {}

}
