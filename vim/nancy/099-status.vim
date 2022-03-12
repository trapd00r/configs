"    File: $HOME/etc/vim/nancy/099-status.vim
"  Author: Magnus Woldrich <m@japh.se>
" Updated: 2022-02-13 15:17:49


hi StatusLine   ctermfg=233 ctermbg=234  cterm=none
hi StatusLineNC ctermfg=233 ctermbg=234 cterm=none

hi link User1 ModeMsg
hi User2 ctermfg=106 ctermbg=234 cterm=none
hi User3 ctermfg=250 ctermbg=234 cterm=none
" User4 is set to the calculated LS_COLORS for the current file below
hi User4 ctermfg=032 ctermbg=234 cterm=none
hi User5 ctermfg=245 ctermbg=234 cterm=none
hi User6 ctermfg=220 ctermbg=234 cterm=none
hi User7 ctermfg=240 ctermbg=234 cterm=none
hi User8 ctermfg=234 ctermbg=fg  cterm=none
hi User9 ctermfg=197 ctermbg=234 cterm=none

" Now, these regexes are obviously bad, but this function will only be used for
" this only purpose so it doesn't matter.
" Here's an aid for generating this:
" curl -s https://raw.githubusercontent.com/trapd00r/LS_COLORS/master/LS_COLORS | grep -Pv '^(?:[#*]|TERM)|^$' | perl -pe 's{^\.?(\S+)\s+(?:[34]8;5;(\d+))}{elsif(a:filename =~ "\v.+\.$1")\n  hi User4 ctermfg=$2 ctermbg=234 cterm=none};s{;\d+$}{}' | perl -pe "s/\"/'/g"

function! LsColorForStatusLine(filename)
  if(a:filename =~ '\v.+\.sh')
    hi User4 ctermfg=172 ctermbg=234 cterm=none

  elseif(a:filename =~ '\v.+\.vim')
    hi User4 ctermfg=106 ctermbg=234 cterm=none

  elseif(a:filename =~ '\v.+\.txt')
    hi User4 ctermfg=188 ctermbg=234 cterm=none

  elseif(a:filename =~ '\v.+\.(css|sass)')
    hi User4 ctermfg=125 ctermbg=234 cterm=none

  elseif(a:filename =~ '\v.+\.csv')
    hi User4 ctermfg=078 ctermbg=234 cterm=none

  elseif(a:filename =~ '\v.+\.js[mp]?')
    hi User4 ctermfg=074 ctermbg=234 cterm=none

  elseif(a:filename =~ '\v.+\.json')
    hi User4 ctermfg=178 ctermbg=234 cterm=none

  elseif(a:filename =~ '\v.+\.log')
    hi User4 ctermfg=190 ctermbg=234 cterm=none

  elseif(a:filename =~ '\v.+\.(markdown|md)')
    hi User4 ctermfg=190 ctermbg=234 cterm=bold

  elseif(a:filename =~ '\vREADME|CHANGES')
    hi User4 ctermfg=190 ctermbg=234 cterm=bold

  elseif(a:filename =~ '\v.+\.php')
    hi User4 ctermfg=081 ctermbg=234 cterm=none

  elseif(a:filename =~ '\vMakefile([.]PL)?')
    hi User4 ctermfg=196 ctermbg=234 cterm=none

  elseif(a:filename =~ '\v.+\.pl')
    hi User4 ctermfg=208 ctermbg=234 cterm=none

  elseif(a:filename =~ '\v.+\.pm')
    hi User4 ctermfg=203 ctermbg=234 cterm=none


  elseif(a:filename =~ '\v.+\.(sql|sqlite)')
    hi User4 ctermfg=222 ctermbg=234 cterm=none
    
  elseif(a:filename =~ '\v.+\.t$')
    hi User4 ctermfg=114 ctermbg=234 cterm=none

  elseif(a:filename =~ '\v.+\.tt$')
    hi User4 ctermfg=173 ctermbg=234 cterm=none

  elseif(a:filename =~ '\v.+\.html?$')
    hi User4 ctermfg=132 ctermbg=234 cterm=none

  else
    hi User4 ctermfg=137 ctermbg=234 cterm=none
  endif
endfun

fun! SetStatusLineAskasButik()
  return expand("$ASKAS_BUTIK")
endfun


au BufRead,BufNewFile,BufEnter * call LsColorForStatusLine(expand('%:p'))
set statusline=
"set statusline +=%1*\ %n\ %*                         " buffer number
set statusline +=\ %5*%{&ff}%*\                       " file format
set statusline +=%3*%y%*\                             " file type
set statusline +=\%7*¦%9*\                            " askås butik
set statusline +=%{SetStatusLineAskasButik()}         " askås butik
set statusline +=\ \%7*¦%4*\ %<%F%*                   " full path
set statusline +=%2*%m%*                              " modified flag
set statusline +=\%7*\ ¦\ \%6*%{fugitive#head()}      " git branch
set statusline +=\%7*\ ¦\ \%1*%{ContextInStatusbar()} " current function or block
"set statusline +=%1*%=%5l%*                          " current line
"set statusline +=%1*/%L%*                            " total lines
"set statusline +=%1*%4v\ %*                          " virtual column number
"set statusline +=%1*0x%04B\ %*                       " character under cursor

