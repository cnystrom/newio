# NewIO

NewIO (also written New I/O or NIO) is Chris Nystrom's remote-display system from the mid-2000s. It has four parts:

- `nio_lib`: a library you link into programs.
- `niod`: the server, which runs as an SSH subsystem.
- `d0`: Dreadnought, the SDL client.
- `demos`: example programs.

Programs use a simple RPC protocol to drive an SDL client over SSH. It is "a poor man's X-Windows, although it is not a desktop system."

This is **version 0.13** (November 2026). It updates version 0.12, build 067_RC05, dated January 30, 2011 (`newio-110130`), so that it builds on current systems and adds a Windows build of the client. See `Changelog` and the release notes.

- Project site: https://newio.org
- Chris Nystrom: https://nystrom.family/chris/

## Changelog (top level)

- 070814: fixed vazpac bug; cleaned up niod.c
- 070916: fixed nio_music_playing()
- 081121: minor cleanups to d0/src/main.c and d0/src/rpc.c
- 090122: updated for latest ffmpeg lib and fixed d0/text_box.c issues
- 110130: updated to latest sock_lib and cleaned up compiler errors and warnings
- 261126: 0.13: builds on modern Linux (gcc 14); Windows d0 client cross-built with MinGW-w64; new replacements for removed third-party files; niod build fix; removed the FFmpeg movie player and the d0 update.sh download

`d0/Changelog` has the client's build-by-build history.

## Authors

- **Chris Nystrom**: most of the code. Some later files are copyright Dreadnought Incorporated, Chris's company.
- **Jason Reynolds** (2007): the UI spec and widget code in `nio_lib/nio_ui_lib.*`, `d0/src/rpcui.*` and `d0/src/do_uidata_in.c`.
- **John Blitch and Jason Reynolds** (2007): `nio_lib/ui_spec.c` and `nio_lib/ui_spec_widgets.c`.
- Some routines in `common/file_io_lib/misc_io.c` (the Win32 home-directory lookup) are taken from, or inspired by, GLib. GLib is Copyright (C) 1995-1998 Peter Mattis, Spencer Kimball and Josh MacDonald and is LGPL-licensed. Their attribution is kept in the file.

## License

Each file's own header governs it:

- **Libraries** (`common/`, most of `nio_lib/`, and the `d0/src/*_lib` helpers): GNU LGPL version 2.1 or later. See [LICENSE](LICENSE).
- **Client, server, Reynolds/Blitch UI code and demos** (`d0/src`, `niod`, the `nio_lib` UI files, `demos/`): GNU GPL version 2 or later. See [COPYING](COPYING).
- **Files with no license header**: these are Chris's and are offered under the LGPL 2.1 or later, which is the same license as the GLib-derived routines.

The GPL-licensed UI files in `nio_lib/` are part of the library build. A `nio_lib.a` built with them is therefore covered by the GPL as a whole.

## Building

These are the original Linux notes. You need libssh2, SDL 1.2, SDL_ttf, SDL_mixer, SDL_image, ffmpeg, json-c, and their `-devel` packages.

- `compile.sh`: compile the whole package.
- `compile-server.sh`: compile just the server.
- `compile-d0.sh`: compile Dreadnought, the client.
- `install-server.sh`: install the server on a local Linux machine.
- `build.sh`, `clean.sh` and `archive.sh`: set the version, clean the tree, and pack a `newio-<date>.tar.gz`.

Visual Studio 2005 projects are in the `VisualC` folders. The Inno Setup script for the Windows client installer is `d0/src/Win32_Installer/DreadNought.iss`.

**What builds right now (2026):** on a modern Linux system (gcc 14, SDL 1.2 or sdl12-compat, libssh2, OpenSSL) the top-level `compile.sh` builds everything: `common`, `niod`, `nio_lib`, `d0` and the demos `demo1`, `demo_apps`, `edit`, `example3`, `jukebox`, `neko`, and `paint`. New, original replacements were written for the removed third-party files that the build needs: `strlcpy`/`strlcat`, `keysym.h`, `colors.c`/`colors.h` (colour names from the X.Org `rgb.txt`), the d0 font helpers (`d0/src/font_lib`), `SDL_prim` and `win32_lib.c`. The demos whose sources were removed (`bounce`, `clickomania`, `epicycle`, `grav`, `kaleidescope`, `pong`, `vazpac`) are no longer in the demo build scripts.

The FFmpeg movie player in `d0/src/movie_lib` (written for the 2009 FFmpeg API) was removed in 2026. d0 is built with stand-ins, so movie requests from a program do nothing.

**Windows client:** `d0.exe` cross-builds for 64-bit Windows with MinGW-w64:

1. `python3 win32/get-deps.py` fetches the Windows libraries (MSYS2 packages and SDL 1.2.15) and builds SDL_ttf, SDL_image and SDL_mixer against SDL 1.2.15 in `win32/deps`.
2. `./build-windows.sh` builds `d0.exe` and puts it, with the DLLs it needs, in `win32/d0`.
3. Copy the GNU FreeFont TTF files (`FreeMono.ttf` and the rest) into `win32/d0/fonts`.

The server side (`niod`, `nio_lib` and the demos) still builds for Linux only.

## Prepared for publication

The tree was changed as follows before publishing:

- **Street addresses**: removed from the original file headers. The email addresses and other contact lines were left alone.
- **Passwords**: the hardcoded passwords in the example programs (`common/msg_lib/examples/client2.c*`, `common/ssh2_lib/attic/example*.c`) were replaced with `CHANGEME`.
- **Binaries and build logs**: compiled objects, binaries, Visual Studio build logs and user files, `.DS_Store` files, bundled DLLs, fonts and media were removed.
- **Third-party code**: these files were removed because they were not written by NewIO's authors:
  - Todd C. Miller's `strlcat`/`strlcpy`
  - Ryan McGuigan's `SDL_prim`
  - Eric S. Raymond's `playlib` and David Olofson's `speaker`
  - Tcl/Tk `colors.c`/`colors.h`
  - Sam Lantinga's `keysym.h` and `SDL_win32_main.c`
  - Bob Pendleton's font helpers and the `bounce` demo
  - the Ron Tapia / Greg Boewring demos (`kaleidescope`, `grav`, `epicycle`)
  - the Daniel Stenberg curl helper
  - the Downhill Project `win32_lib.c`
  - a libssh2 sample
  - the demo ports of PhilVaz's VazPac, Aaron Cox's Pong and Marius Andra's Clickomania
  - the vendored Win32 include and library trees

  Makefiles and project files that name these files were left as they were, apart from the 2026 build fixes described under Building.
