Static Client NSIS Script:

This NSIS script builds an installer for the static client.


Instructions:
=====================================================

Copy the following files into the PT directory:

client_static.exe
config.cs
vfs.cfg

cg.dll
cgGL.dll
dbghelp.dll

data.zip
cally.zip
shader.zip

Compile the NSIS script. 

Distribute PTInstall.exe


Issues:
=====================================================

- Any Local modifications to the client will be deleted on uninstall.

- Start Menu shortcuts lack icons.