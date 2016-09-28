" Vim syntax file
" Language:     Vimpoint .vpf first-slide files
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


highlight   VPFBackground     ctermfg=white      ctermbg=white 

highlight   VPFTitle          ctermfg=black      ctermbg=white   cterm=bold
highlight   VPFTitleCode      ctermfg=darkblue       ctermbg=white   cterm=bold
highlight   VPFTitleEmph      ctermfg=black      ctermbg=white   cterm=bold,underline
highlight   VPFTitleCodeEmph  ctermfg=magenta    ctermbg=white   cterm=bold


highlight   VPFName           ctermfg=black      ctermbg=white   cterm=bold
highlight   VPFNameCode       ctermfg=darkblue       ctermbg=white   cterm=bold
highlight   VPFNameEmph       ctermfg=black      ctermbg=white   cterm=bold,underline
highlight   VPFNameCodeEmph   ctermfg=magenta    ctermbg=white   cterm=bold

highlight   VPFInfo           ctermfg=black      ctermbg=white
highlight   VPFInfoCode       ctermfg=darkblue       ctermbg=white
highlight   VPFInfoEmph       ctermfg=black      ctermbg=white   cterm=bold
highlight   VPFInfoCodeEmph   ctermfg=magenta    ctermbg=white   cterm=bold

highlight   VPFLine           ctermfg=darkblue   ctermbg=white   cterm=underline

highlight link  VPFTitleCodeOne        VPFTitleCode 
highlight link  VPFTitleEmphOne        VPFTitleEmph    
highlight link  VPFTitleCodeEmphOne    VPFTitleCodeEmph
highlight link  VPFNameCodeOne         VPFNameCode 
highlight link  VPFNameEmphOne         VPFNameEmph    
highlight link  VPFNameCodeEmphOne     VPFNameCodeEmph
highlight link  VPFInfoCodeOne         VPFInfoCode 
highlight link  VPFInfoEmphOne         VPFInfoEmph    
highlight link  VPFInfoCodeEmphOne     VPFInfoCodeEmph

syn match   VPFBackground    /./

syn region  VPFLine
    \ matchgroup=VPFBackground 
    \      start=/º/ 
    \        end=/º/
    \    oneline

syn region  VPFTitle   
    \ matchgroup=VPFBackground 
    \      start=/¹/ 
    \        end=/¹/
    \   contains=VPFTitleCode,VPFTitleBold,VPFTitleCodeBold,VPFTitleCodeOne,VPFTitleBoldOne,VPFTitleCodeBoldOne

syn region  VPFName   
    \ matchgroup=VPFBackground 
    \      start=/²/ 
    \        end=/²/
    \   contains=VPFNameCode,VPFNameBold,VPFNameCodeBold,VPFNameCodeOne,VPFNameBoldOne,VPFNameCodeBoldOne

syn region  VPFInfo   
    \ matchgroup=VPFBackground 
    \      start=/³/ 
    \        end=/³/
    \   contains=VPFInfoCode,VPFInfoBold,VPFInfoCodeBold,VPFInfoCodeOne,VPFInfoBoldOne,VPFInfoCodeBoldOne


let b:current_syntax = "vpf"
