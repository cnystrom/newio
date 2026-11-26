#!/bin/sh
#
# Cross-build the d0 client for 64-bit Windows with MinGW-w64.
# Added 2026.
#
#   python3 win32/get-deps.py        (once: fetches/builds win32/deps)
#   ./build-windows.sh [DEPS_DIR]
#
# The result, d0.exe with the DLLs it needs, is put in win32/d0/.
# Copy the GNU FreeFont TTFs (FreeMono.ttf ...) into win32/d0/fonts/
# before you zip it up; d0 looks for them in fonts/ next to d0.exe.
#

set -e

TOP=$(cd "$(dirname "$0")" && pwd)
DEPS=$(cd "${1:-$TOP/win32/deps}" && pwd)
PREFIX=$DEPS/mingw64
CROSS=x86_64-w64-mingw32
OUT=$TOP/win32/d0

# The Makefiles call gcc, ar, ranlib and sdl-config by name; point
# those at the cross tools and the Windows libraries.
TOOLS=$(mktemp -d)
trap 'rm -rf "$TOOLS"' EXIT
cat > "$TOOLS/cc" <<EOT
#!/bin/sh
exec $CROSS-gcc -I$PREFIX/include "\$@" -L$PREFIX/lib
EOT
cat > "$TOOLS/sdl-config" <<EOT
#!/bin/sh
case "\$1" in
--cflags) echo "-I$PREFIX/include -I$PREFIX/include/SDL -Dmain=SDL_main" ;;
--libs) echo "-L$PREFIX/lib -lmingw32 -lSDLmain -lSDL -mwindows" ;;
esac
EOT
ln -s "$(command -v $CROSS-ar)" "$TOOLS/ar"
ln -s "$(command -v $CROSS-ranlib)" "$TOOLS/ranlib"
chmod +x "$TOOLS/cc" "$TOOLS/sdl-config"
PATH=$TOOLS:$PATH
export PATH

cd "$TOP/d0/src"
make -f Makefile.MinGW clean >/dev/null 2>&1 || true
make -f Makefile.MinGW CC=cc TARGET_OS=WIN32

# d0.exe plus every non-Windows DLL it loads, directly or not
rm -rf "$OUT"
mkdir -p "$OUT/fonts"
cp d0.exe "$OUT/"
todo="$OUT/d0.exe"
while [ -n "$todo" ]; do
	next=""
	for f in $todo; do
		for dll in $($CROSS-objdump -p "$f" | awk '/DLL Name:/ {print $3}'); do
			src=$(ls "$PREFIX/bin" | grep -ix "$dll" || true)
			if [ -n "$src" ] && [ ! -f "$OUT/$src" ]; then
				cp "$PREFIX/bin/$src" "$OUT/"
				next="$next $OUT/$src"
			fi
		done
	done
	todo=$next
done

# leave the source tree ready for a Linux build again
make -f Makefile.MinGW clean >/dev/null 2>&1 || true

echo "Built $OUT/d0.exe"
