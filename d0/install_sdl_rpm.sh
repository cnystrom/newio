#/bin/sh

wget http://www.libsdl.org/release/SDL-1.2.8-1.i386.rpm
wget http://www.libsdl.org/projects/SDL_image/release/SDL_image-1.2.4-1.i386.rpm
wget http://www.libsdl.org/projects/SDL_mixer/release/SDL_mixer-1.2.6-1.i386.rpm
wget http://www.libsdl.org/projects/SDL_ttf/release/SDL_ttf-2.0.7-1.i386.rpm

rpm -ivh SDL-1.2.8-1.i386.rpm
rpm -ivh SDL_image-1.2.4-1.i386.rpm
rpm -ivh SDL_mixer-1.2.6-1.i386.rpm
rpm -ivh SDL_ttf-2.0.7-1.i386.rpm


