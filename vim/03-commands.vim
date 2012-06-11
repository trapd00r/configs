"    File: $HOME/etc/vim/_commands.vim
"  Author: Magnus Woldrich <m@japh.se>
" Updated: 2011-08-21 14:09:05

command! Vresize :vert resize 80
command! Sortnum :sort n /TOIGNORE


if v:progname == 'wim'
  command! vresize :vert resize 80
  command! sortnum :sort n /TOIGNORE
  command! ls echo 42
endif
