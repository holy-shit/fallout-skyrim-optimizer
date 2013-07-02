fallout-skyrim-optimizer
========================
by MonochromeWench (the.wench@wenchy.net)
modified by olegchir (olegchiruhin@gmail.com)

Performance tweaker for Fallout New Vegas and TES V: Skyrim 
(formerly Fallout New Vegas 4GB or FNV4Gb)

fallout-skyrim-optimizer is a tool to load Fallout New Vegas 
and Skyrim with the Large Address Aware executable flag set so the 
entire 4GB Virtual Memory Address Space can be used
by the game. This is useful when using lots of mods.

fallout-skyrim-optimizer is licensed under the terms of 
the GNU Lesser General Public License version 2.1. 
Read the included lgpl-2.1.txt for the terms. Source code is 
included with the package. Original binaries compiled using Microsoft Visual 
Studio 2012 on Windows 8 x64 with Win32 target.


Running the game
================

Running with Steam
-------
First, make sure Steam is running. Then run FNV4GB.exe to launch the game! 
You don't even need it in the games directory, just make sure FNV4gb.exe and
fnv4gb_helper.dll are together.

If your version of Fallout New Vegas is not the standard version with the
SteamAppID of 22380 you need to run fnv4gb.exe and specify the actual 
SteamAppID on the command line. Example: fnv4gb.exe -SteamAppID 22380


Running without Steam
-------
It is required for heavily patched mods that provides steam-free mode
and require modified exe files and inconsistent cache.
Put fnv4gb.exe and fnv4gb_helper.dll for Fallout New Vegas
(or skyrim4gb.exe and skyrim4gb_helper.dll for Skyrim)
into the game directory and run our exefile.

Warning! This patch created only for legal use of the game.
Please don't use it with SKIDROW cracks (or anything like that)
because it is prohibited by law of most countries including Russia :-)


Command Line Reference
======================

```
FNV4GB.exe    [-exe string] [-laaexe string] [-SteamAppID number] [-nolaa]
              [-noskse] [-extradll string [-extradll string [...]]]
			  [-- game parameters]
```

Details

-exe        The games original executable. If not an absolute path FNV4GB
            will look for the executable in the Fallout New Vegas directory 
			using paths that should be in the registry. 
			Default is FalloutNV.exe.

-laaexe     The executable created by the loader that has the LAA flag set. 
            This must not be the same file as the original executable. 
			* If this is an absolute path the file will be created using that 
			  exact path.
			* If the path starts with .\ the exe will be created relative to 
			  the directory containg FNV4GB.
			* Otherwise it will be created relative to the original executable.
			Default is use the original's name and create it in a directory 
			called 'exes' in the directory containing FNV4GB.exe.

-SteamAppID The SteamAppID id to use. Default is 22380 for Fallout New Vegas
            and 72850 for Skyrim.

-nolaa      Don't set the LAA flag or unset it if it was already set in the 
            original executable. 

-nonvse     Disable attempting to load NVSE (New Vegas Script Extender) when
            playing Fallout New Vegas

-noskse     Disable attempting to load SKSE (Skyrim Script Extender) when
            playing Skyrim

-extradll   An extra dll to load into the laaexe process after its been 
            created. This can be specified multiple times to load more than one
			dll.

--          Anything after this will be passed as is to the game when the 
            loader creates the process.

Examples

FNV4GB.exe -laaexe .\FalloutNV.exe
    Create a LAA Exe called FalloutNV.exe in the directory containing FNV4GB. 
	This is probably what you'd want to do if you need some other application
	to detect FalloutNV.exe loading, not FalloutNV.exe.4gb


Technical Details
========================

FNV4GB performs the following actions

1) Gets the Install Path for the game from the registry value:
   HKEY_LOCAL_MACHINE\SOFTWARE\Bethesda Softworks\FalloutNV\Installed Path
2) Changes to the games Directory
3) Copies FalloutNV.exe to FalloutNV.4GB if needed
4) Sets the LARGEADDRESSAWARE bit on FalloutNV.4GB if needed
5) Sets the environment variable SteamAPPId to 22380 (or whatever value was 
   specified on the command line) which tells Steam to run the game (not 
   restart and load the launcher)
6) Creates a new process for FalloutNV.4GB with the main thread suspended
7) Injects fnv4gb_helper.dll into the FalloutNV.4GB process
8) fnv4gb_helper unsets the LARGEADDRESSAWARE bit in the loaded headers so 
   when steam verifies the loaded executable in memory it passes
9) fnv4gb_helper hooks the GetTickCount function to attempt to reduce 
   stuttering
10) fnv4gb_helper hooks the CreateFileA function so when steam attempts to 
   verify the disk executable file against the loaded memory it loads the 
   untouched FalloutNV.exe instead of the modified FalloutNV.4gb
11) The FNV4GB loader verifies that Large Addresses are enabeles in the 
    FalloutNV.4gb
12) FNV4GB loader unsuspends the main thread so the game can run
