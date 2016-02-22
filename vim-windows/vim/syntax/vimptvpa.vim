" Vim syntax file
" Language:     Vimpoint .vpa presentation files
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


highlight   VPAInverse       ctermfg=white      ctermbg=black
highlight   VPABackground    ctermfg=white      ctermbg=white
highlight   VPABulletPoint   ctermfg=black      ctermbg=white

highlight   VPATitle         ctermfg=black      ctermbg=white   cterm=bold
highlight   VPATitleCode     ctermfg=darkblue       ctermbg=white   cterm=bold
highlight   VPATitleEmph     ctermfg=black      ctermbg=white   cterm=bold
highlight   VPATitleCodeEmph ctermfg=darkblue       ctermbg=white   cterm=bold

highlight   VPACode          ctermfg=darkblue       ctermbg=white
highlight   VPAEmph          ctermfg=black      ctermbg=white   cterm=underline
highlight   VPACodeEmph      ctermfg=darkred        ctermbg=white     cterm=bold

highlight   VPACodeBlock     ctermfg=darkblue       ctermbg=white
highlight   VPACodeBlockEmph ctermfg=darkred        ctermbg=white     cterm=bold

highlight   VPALine          ctermfg=darkblue   ctermbg=white   cterm=underline

highlight   VPATimerDisplay  ctermfg=darkred   ctermbg=black  cterm=underline
highlight   VPATimerDisplayEnd ctermfg=darkblue ctermbg=black  cterm=underline

highlight link  VPATitleOne             VPATitle
highlight link  VPATitleCodeOne         VPATitleCode
highlight link  VPATitleEmphOne         VPATitleEmph
highlight link  VPATitleCodeEmphOne     VPATitleCodeEmph
highlight link  VPACodeOne              VPACode
highlight link  VPAEmphOne              VPAEmph
highlight link  VPACodeEmphOne          VPACodeEmph
highlight link  VPACodeBlockOne         VPACodeBlock
highlight link  VPACodeBlockEmphOne     VPACodeBlockEmph

syn match  VPABackground
    \ /./

syn region  VPALine
    \ matchgroup=VPABackground
    \      start=/^\s/
    \        end=/\s$/

syn region  VPABulletPoint
    \    start=/^ \{3}[·»¤×]\s/
    \      end=/\_^\s*\_$/
    \ contains=VPACode,VPAEmph,VPACodeEmph,VPACodeOne,VPAEmphOne,VPACodeEmphOne

syn match   VPACodeBlock
    \ /^ \{4,}.*$/
    \ contains=VPACodeBlockEmph,VPACodeBlockEmphOne

syn match  VPATitle
    \ /\%^.*\n\_.\{-}\ze\_^\s*\n/
    \ contains=VPATitleCode,VPATitleEmph,VPATitleCodeEmph,VPATitleCodeOne,VPATitleEmphOne,VPATitleCodeEmphOne
    \ nextgroup=VPALine


let b:current_syntax = "vpa"
