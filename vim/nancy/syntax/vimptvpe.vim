" Vim syntax file
" Language:     Vimpoint .vpe example files
" Written By:   Damian Conway
" Last Change:  Tue Apr 22 08:32:54 EST 2008

" For version 5.x: Clear all syntax items
" For version 6.x: Quit when a syntax file was already loaded
if version < 600
  syntax clear
elseif exists("b:current_syntax")
  finish
endif

syntax case ignore

highlight   VPEText     ctermfg=white      ctermbg=black 

syn match  VPEText  /./


let b:current_syntax = "vpe"
