# ck3-iron-patcher

Patches CK3 Ironman saves to allow them to be hosted in multiplayer. Tested with game version 1.0.3

It does so by changing a byte in the savegame at a specific position, so that the savegame browser in CK3 thinks it isn't in Ironman mode, while it actually is.
This allows for Ironman games to be hosted in multiplayer.

## Download

You can download a Linux binary and a Windows mingw build (that doesn't seem to work on Win10 apparently, so you might have to compile yourself for windows) from [the repositories releases page.](https://github.com/timbuntu/ck3-iron-patcher/releases)

## Compiling

Compile with the c compiler of your choice. There aren't any dependencies other than the c standard library.

## Usage

You can find the location of the CK3 savegames for your system on the [CK3 Wiki](https://ck3.paradoxwikis.com/Modding#Save_game_editing).

1. Backup your save in case something goes wrong!
2. Execute the patcher from commandline with the path to your savegame as argument, or drag&drop the savegame onto the patcher executable.
3. Start CK3 and check if your savegame is listed as not being Ironman.
4. You need to reapply the patch eveytime you save and exit that savegame.
