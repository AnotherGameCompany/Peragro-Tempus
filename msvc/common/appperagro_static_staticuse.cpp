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
struct _static_use { _static_use (); };
_static_use::_static_use () {}
SCF_USE_STATIC_PLUGIN(csclipboard)
SCF_USE_STATIC_PLUGIN(loader_starbox)
SCF_USE_STATIC_PLUGIN(mystarbox)
SCF_USE_STATIC_PLUGIN(component_playercontrols)
SCF_USE_STATIC_PLUGIN(component_viewcontrols)
SCF_USE_STATIC_PLUGIN(component_networkmove)
SCF_USE_STATIC_PLUGIN(component_viewbob)
SCF_USE_STATIC_PLUGIN(componentmesh)
SCF_USE_STATIC_PLUGIN(soundmanager)
SCF_USE_STATIC_PLUGIN(worldloader)
SCF_USE_STATIC_PLUGIN(cachemanager)
SCF_USE_STATIC_PLUGIN(effectsmanager)
SCF_USE_STATIC_PLUGIN(cmdmanager)
SCF_USE_STATIC_PLUGIN(cmdhelp)
SCF_USE_STATIC_PLUGIN(cmdlogout)
SCF_USE_STATIC_PLUGIN(cmdquit)
SCF_USE_STATIC_PLUGIN(cmdrelocate)

