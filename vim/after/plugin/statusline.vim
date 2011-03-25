if exists('g:loaded_fugitive')
   set statusline=%f\ %m\ (%L\ lines)\ %r\ %=%{fugitive#statusline()}\ (%l,%c)\ %y
   hi StatusLine ctermfg=085 ctermbg=234 cterm=bold
   hi StatusLineNC cterm=bold
else
  set statusline=%<[%02n]\ %F%(\ %m%h%w%y%r%)\ %a%=\ %8l,%c%V/%L\ (%P)\ [%08O:%02B]
endif
