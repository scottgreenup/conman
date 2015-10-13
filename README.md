# ConMan

This is a CONfiguration MANager that will manage your config files. The main use
case is for people who want to more readily backup their dotfiles, etc configs,
and extra bits. It also allows you to easily deploy your configuration to a new
computer, or share one.

ConMan uses git to store the files and keep versions of them. You will have a
conman directory that tracks your files with git, and knows where to
symbolically link them.
