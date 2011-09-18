" Vim syntax file
" Language:     Vimpoint .vps presentation files
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
syntax sync fromstart
set nowrap


highlight   VPSBackground    ctermfg=white      ctermbg=white
highlight   VPSBulletPoint   ctermfg=black      ctermbg=white

highlight   VPSTitle         ctermfg=black      ctermbg=white   cterm=bold
highlight   VPSTitleCode     ctermfg=darkblue       ctermbg=white   cterm=bold
highlight   VPSTitleEmph     ctermfg=black      ctermbg=white   cterm=bold
highlight   VPSTitleCodeEmph ctermfg=darkblue       ctermbg=white   cterm=bold

highlight   VPSLine          ctermfg=white      ctermbg=white   cterm=underline
highlight   VPSBlock         ctermfg=darkblue   ctermbg=darkblue

highlight   VPSTimerDisplay  ctermfg=darkred   ctermbg=black  cterm=underline
highlight   VPSTimerDisplayEnd ctermfg=darkblue ctermbg=black  cterm=underline

highlight link  VPSTitleOne             VPSTitle        
highlight link  VPSTitleCodeOne         VPSTitleCode    
highlight link  VPSTitleEmphOne         VPSTitleEmph    
highlight link  VPSTitleCodeEmphOne     VPSTitleCodeEmph

syn match  VPSBackground  
    \ /./

syn region  VPSLine
    \ matchgroup=VPSBackground
    \      start=/^\s/ 
    \        end=/\s$/
    \  nextgroup=VPSBlock

syn match VPSBlock /./ nextgroup=VPSBlock

syn match  VPSTitle  
    \ /\%^.*\n\_.\{-}\ze\_^\s*\n/
    \ contains=VPSTitleCode,VPSTitleEmph,VPSTitleCodeEmph,VPSTitleCodeOne,VPSTitleEmphOne,VPSTitleCodeEmphOne
    \ nextgroup=VPSLine


let b:current_syntax = "vps"
