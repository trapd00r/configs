" vim:ft=vim:
"    File: $VIMRUNTIME/03-commands.vim
"  Author: Magnus Woldrich <m@japh.se>
" Updated: 2016-09-14 13:47:06

" you'll need my vim fork: http://github.com/trapd00r/wim
if v:progname == 'wim'
  comclear
  try
    " this one is especially annoying
    command! tohtml  TOhtml
    command! vresize vert resize 80
    command! hresize resize 60
    command! Write   write
    command! Command command
  catch /^Vim\%((\a\+)\)\=:E183/
  endtry
endif
