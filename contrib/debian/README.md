
Debian
====================
This directory contains files used to package harzcoind/harzcoin-qt
for Debian-based Linux systems. If you compile harzcoind/harzcoin-qt yourself, there are some useful files here.

## harzcoin: URI support ##


harzcoin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install harzcoin-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your harzcoin-qt binary to `/usr/bin`
and the `../../share/pixmaps/harzcoin128.png` to `/usr/share/pixmaps`

harzcoin-qt.protocol (KDE)

