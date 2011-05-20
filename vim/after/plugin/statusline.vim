" Vim statusline file - after/plugin/statusline.vim
" Author: Magnus Woldrich <magnus@trapd00r.se>


hi User1 ctermfg=064 ctermbg=234 cterm=bold
hi User2 ctermfg=085 ctermbg=234 cterm=bold
hi User3 ctermfg=238 ctermbg=234 cterm=bold
hi User4 ctermfg=032 ctermbg=234 cterm=bold
hi User5 ctermfg=044 ctermbg=234 cterm=bold
hi User6 ctermfg=058 ctermbg=234 cterm=bold
hi User7 ctermfg=240 ctermbg=234 cterm=bold
hi User8 ctermfg=130 ctermbg=234 cterm=bold
hi User9 ctermfg=065 ctermbg=234 cterm=bold


if exists('g:loaded_fugitive')
  let &statusline='%1*%t%*
    \%7*[%2*%n%7*]%*
    \ %3*│%*
    \ %4*%c%3*c%*
    \ %*%1*%l%3*/%7*%L%3*
    \ %3*│%*
    \ %9*%03.3b%*
    \ %7*-%*
    \ 0x%8*%02.2B%*
    \ %3*│%*
    \ %r %=
    \ %3*
    \ %{FileSize()}
    \ %7*
    \ %m
    \ %{fugitive#statusline()}'


  let g:NCstatusline='%9*%t%*
    \%7*[%3*%n%7*]%*
    \ %3*│%*
    \ %7*%c%3*c%*
    \ %*%7*%l%3*/%7*%L%3*
    \ %3*│%*
    \ %7*%03.3b%*
    \ %7*-%*
    \ 0x%7*%02.2B%*
    \ %3*│%*
    \ %r %=
    \ %3*
    \ %{FileSize()}
    \ %7*
    \ %m
    \ %{fugitive#statusline()}'
else
  " XXX
  let &statusline='%<[%02n] %F%( %m%h%w%y%r%) %a%= %8l,%c%V/%L (%P) [%08O:%02B]'
  let g:NCstatusline='no git, not active'
endif

hi StatusLine   ctermfg=239 ctermbg=234 cterm=bold
hi StatusLineNC ctermfg=239 ctermbg=234 cterm=NONE

let g:Active_statusline = &g:statusline

au WinEnter * let &l:statusline = g:Active_statusline
au WinLeave * let &l:statusline = g:NCstatusline 
