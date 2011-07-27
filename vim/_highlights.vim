"    File: $HOME/etc/highlights.vim
"  Author: Magnus Woldrich <m@japh.se>
" Updated: 2011-07-27 12:06:12

syn match wsEOL display '\v[ ]+$' conceal cchar=O

hi SpellBad   ctermfg=196 ctermbg=233  cterm=bold
hi SpellCap   ctermfg=196 ctermbg=233  cterm=bold
hi SpellRare  ctermfg=196 ctermbg=233  cterm=bold
hi SpellLocal ctermfg=160 ctermbg=235  cterm=bold

hi wsEOL      ctermfg=196 ctermbg=none cterm=bold

hi LineNr     ctermfg=241 ctermbg=none cterm=italic
