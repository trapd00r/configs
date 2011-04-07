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
   set statusline=
   set statusline=%1*%t%*
   set statusline+=%7*[%2*%n%7*]%*
   set statusline+=\ %3*│%*
   set statusline+=\ %4*%c%3*c%*,
   set statusline+=\ %*%1*%l%3*/%7*%L%3*
   set statusline+=\ %3*│%*
   set statusline+=\ %9*%03.3b%*
   set statusline+=\ %7*\-\ %*
   set statusline+=0x%8*%02.2B%*
   "set statusline+=\ %3*│%*
   set statusline+=%r\ %=
   set statusline+=%3*
   set statusline+=%{FileSize()}
   set statusline+=%7*
   set statusline+=\ %m
   "set statusline+=%{StatuslineLongLineWarning()}
   set statusline+=%{fugitive#statusline()}

   hi StatusLine   ctermfg=239 ctermbg=234 cterm=bold
   hi StatusLineNC ctermfg=239 ctermbg=234
else
  set statusline=%<[%02n]\ %F%(\ %m%h%w%y%r%)\ %a%=\ %8l,%c%V/%L\ (%P)\ [%08O:%02B]
endif
