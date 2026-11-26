#!/usr/bin/env python3
"""Fetch and build the Windows (x86_64) libraries d0.exe needs.

Added 2026 for the MinGW-w64 cross build (see build-windows.sh).

  python3 win32/get-deps.py [DEPS_DIR]      (default: win32/deps)

It downloads prebuilt MinGW-w64 packages from the MSYS2 repository
(libssh2, OpenSSL, FreeType, libpng, libjpeg, libvorbis and what they
need), the MSYS2 build of SDL 1.2.15, and the SDL_ttf 2.0.11,
SDL_image 1.2.12 and SDL_mixer 1.2.12 sources from libsdl.org, and
builds those three against SDL 1.2.15. Everything ends up under
DEPS_DIR/mingw64 (include, lib, bin).

Needs: python3, curl, tar with zstd, x86_64-w64-mingw32-gcc, pkg-config.
"""
import os, re, subprocess, sys

REPO = 'https://repo.msys2.org/mingw/mingw64/'
SDL_REL = 'https://www.libsdl.org/projects/'
WANT = ['libssh2', 'openssl', 'zlib', 'freetype', 'libpng', 'libjpeg-turbo',
        'libvorbis', 'libogg', 'libwinpthread', 'libstdc++', 'libgcc']
# not needed at run time, or replaced by SDL 1.2.15 below
SKIP = {'gcc-libs', 'cc-libs', 'python', 'python-packaging', 'gettext',
        'SDL', 'sdl12-compat', 'SDL2', 'cairo', 'pixman', 'fontconfig'}
CC = 'x86_64-w64-mingw32-gcc'

deps = os.path.abspath(sys.argv[1] if len(sys.argv) > 1 else
                       os.path.join(os.path.dirname(__file__), 'deps'))
pkgs = os.path.join(deps, 'pkgs')
src = os.path.join(deps, 'src')
pre = os.path.join(deps, 'mingw64')
for d in (pkgs, src):
    os.makedirs(d, exist_ok=True)

def run(cmd, **kw):
    print('+', cmd if isinstance(cmd, str) else ' '.join(cmd))
    subprocess.run(cmd, check=True, **kw)

def fetch(url, path):
    if not os.path.exists(path):
        run(['curl', '-sfL', '-o', path, url])

index = subprocess.run(['curl', '-sfL', REPO], check=True,
                       capture_output=True, text=True).stdout
files = re.findall(r'href="(mingw-w64-x86_64-[^"]+?-any\.pkg\.tar\.zst)"', index)

def latest(name):
    q = re.escape(name.replace('+', '%2B'))
    c = [f for f in files
         if re.match(r'mingw-w64-x86_64-%s-[0-9r][^-]*-[0-9.]+-any' % q, f)]
    if not c:
        return None
    out = subprocess.run(['sort', '-V'], input='\n'.join(c),
                         capture_output=True, text=True).stdout.split()
    return out[-1]

def install(name):
    f = latest(name)
    if f is None:
        print('not in repository:', name)
        return []
    local = os.path.join(pkgs, f.replace('%2B', '+'))
    fetch(REPO + f, local)
    run(['tar', '--zstd', '-xf', local, '-C', deps, 'mingw64'])
    info = subprocess.run(['tar', '--zstd', '-xOf', local, '.PKGINFO'],
                          check=True, capture_output=True, text=True).stdout
    return [re.split(r'[<>=]', d)[0].replace('mingw-w64-x86_64-', '')
            for d in re.findall(r'^depend = (\S+)', info, re.M)]

done, todo = set(), list(WANT)
while todo:
    n = todo.pop()
    if n in done or n in SKIP:
        continue
    done.add(n)
    todo += install(n)
install('SDL')      # SDL 1.2.15 (MSYS2 "SDL" package)

env = dict(os.environ, PKG_CONFIG_LIBDIR=os.path.join(pre, 'lib/pkgconfig'),
           PKG_CONFIG_SYSROOT_DIR=deps)
def pc(args):
    return subprocess.run(['pkg-config'] + args, env=env, check=True,
                          capture_output=True, text=True).stdout.split()

sdl = ['-I' + pre + '/include/SDL', '-I' + pre + '/include']
lib = ['-L' + pre + '/lib']
cflags = ['-O2', '-Wno-incompatible-pointer-types', '-shared']

def addon(tarname, dll, srcs, extra_c, extra_l, header):
    tgz = os.path.join(src, tarname + '.tar.gz')
    fetch(SDL_REL + tarname.split('-')[0] + '/release/' + tarname + '.tar.gz', tgz)
    run(['tar', '-xzf', tgz, '-C', src])
    d = os.path.join(src, tarname)
    run([CC] + cflags + ['-o', dll] + srcs + sdl + extra_c + lib + extra_l +
        ['-lSDL', '-Wl,--out-implib,lib%s.dll.a' % dll[:-4]], cwd=d)
    run(['cp', dll, pre + '/bin/'], cwd=d)
    run(['cp', 'lib%s.dll.a' % dll[:-4], pre + '/lib/'], cwd=d)
    run(['cp', header, pre + '/include/SDL/'], cwd=d)

addon('SDL_ttf-2.0.11', 'SDL_ttf.dll', ['SDL_ttf.c'],
      pc(['--cflags', 'freetype2']), ['-lfreetype'], 'SDL_ttf.h')
addon('SDL_image-1.2.12', 'SDL_image.dll',
      ['IMG.c', 'IMG_bmp.c', 'IMG_gif.c', 'IMG_jpg.c', 'IMG_lbm.c', 'IMG_pcx.c',
       'IMG_png.c', 'IMG_pnm.c', 'IMG_tga.c', 'IMG_tif.c', 'IMG_xcf.c',
       'IMG_xpm.c', 'IMG_xv.c', 'IMG_xxx.c', 'IMG_webp.c'],
      pc(['--cflags', 'libpng']) +
      ['-DLOAD_' + t for t in ('BMP', 'GIF', 'JPG', 'LBM', 'PCX', 'PNG', 'PNM',
                               'TGA', 'XCF', 'XPM', 'XV')],
      ['-lpng16', '-ljpeg', '-lz'], 'SDL_image.h')
addon('SDL_mixer-1.2.12', 'SDL_mixer.dll',
      ['mixer.c', 'music.c', 'effect_position.c', 'effect_stereoreverse.c',
       'effects_internal.c', 'load_aiff.c', 'load_voc.c', 'load_ogg.c',
       'wavestream.c', 'music_ogg.c', 'dynamic_ogg.c'],
      ['-DWAV_MUSIC', '-DOGG_MUSIC'],
      ['-lvorbisfile', '-lvorbis', '-logg', '-lwinmm'], 'SDL_mixer.h')
print('Windows libraries are in', pre)
