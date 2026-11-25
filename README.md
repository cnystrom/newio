# NewIO

NewIO (also written New I/O or NIO) is Chris Nystrom's remote-display system from the mid-2000s. It has four parts:

- `nio_lib`: a library you link into programs.
- `niod`: the server, which runs as an SSH subsystem.
- `d0`: Dreadnought, the SDL client.
- `demos`: example programs.

Programs use a simple RPC protocol to drive an SDL client over SSH. It is "a poor man's X-Windows, although it is not a desktop system."

This is **version 0.12, build 067_RC05, dated January 30, 2011** (`newio-110130`).

- Project site: https://newio.org
- Chris Nystrom: https://nystrom.family/chris/

## Changelog (top level)

- 070814: fixed vazpac bug; cleaned up niod.c
- 070916: fixed nio_music_playing()
- 081121: minor cleanups to d0/src/main.c and d0/src/rpc.c
- 090122: updated for latest ffmpeg lib and fixed d0/text_box.c issues
- 110130: updated to latest sock_lib and cleaned up compiler errors and warnings

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

**What builds right now:** this tree was test-built on a modern Linux system (gcc 14). The following libraries build:

- `common/msg_lib`
- `common/file_io_lib`
- `common/sock_lib`
- `common/ssh2_lib`
- `common/nio_log`

Everything else does not build as it is. Third-party files were removed for publication (see below), and these parts depend on them:

- `str_lib` needs `strlcpy` and `strlcat`.
- `nio_lib` needs `keysym.h` and `colors.h`.
- `d0` needs its font and primitives helpers.
- Several demos have had their sources removed.

`niod` depends on `str_lib`. Fixing all of this means supplying replacements for those files.

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

  Makefiles and project files that name these files were left as they were.
