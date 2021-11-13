"    File: $HOME/etc/vim/after/plugin/statusline.vim
"  Author: Magnus Woldrich <m@japh.se>
" Updated: 2011-07-02 17:48:48


hi StatusLine   ctermfg=233 ctermbg=234  cterm=none
hi StatusLineNC ctermfg=233 ctermbg=234 cterm=none
set statusline=​
"set statusline&

hi User1 ctermfg=196 ctermbg=234 cterm=italic
hi User2 ctermfg=106 ctermbg=234 cterm=boldunderline
hi User3 ctermfg=238 ctermbg=234 cterm=italic
hi User4 ctermfg=032 ctermbg=234 cterm=italic
hi User5 ctermfg=044 ctermbg=234 cterm=italic
hi User6 ctermfg=058 ctermbg=234 cterm=italic
hi User7 ctermfg=240 ctermbg=234 cterm=italic
hi User8 ctermfg=234 ctermbg=fg  cterm=italicreversebold
hi User9 ctermfg=094 ctermbg=234 cterm=bolditalic

" active
"exe 'let &statusline="[%8*' . b:changedtick . '%1*%F%9*[%8*%02n%9*]"'
"exe 'let &statusline=" %1*♡%8* ' . b:changedtick . '%3* changes to %2*%F%3*[%4*%02n' . b:current_syntax . ',' . v:register 
let fakereg = '"'
let fakereg = substitute(v:register, '\v"', 'unnamed', 'g')
"let function_name = ShowFuncName()
exe 'let &statusline=" %8*' . b:changedtick . '%3* changes to %2*%F %3*[%7*%02n%3*,%7*' . fakereg . '%3*,%1*♡%3*]"'
"'af %8*%F%*%4⌈53⌋'
let g:NCstatusline='%9*%t'
let g:Active_statusline = &g:statusline

au WinEnter * let &l:statusline = g:Active_statusline
au WinLeave * let &l:statusline = g:NCstatusline
