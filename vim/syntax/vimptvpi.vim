" Vim syntax file
" Language:     Vimpoint .vpi intermission files
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


highlight   VPIBackground     ctermfg=white      ctermbg=white 

highlight   VPITitle          ctermfg=black      ctermbg=white   cterm=bold
highlight   VPITitleCode      ctermfg=darkblue       ctermbg=white   cterm=bold
highlight   VPITitleEmph      ctermfg=black      ctermbg=white   cterm=bold,underline
highlight   VPITitleCodeEmph  ctermfg=magenta    ctermbg=white   cterm=bold


highlight   VPIName           ctermfg=black      ctermbg=white   
highlight   VPINameCode       ctermfg=darkblue       ctermbg=white   
highlight   VPINameEmph       ctermfg=black      ctermbg=white   cterm=underline
highlight   VPINameCodeEmph   ctermfg=magenta    ctermbg=white   cterm=bold

highlight   VPILine           ctermfg=darkblue   ctermbg=white   cterm=underline

highlight link  VPITitleCodeOne        VPITitleCode 
highlight link  VPITitleEmphOne        VPITitleEmph    
highlight link  VPITitleCodeEmphOne    VPITitleCodeEmph
highlight link  VPINameCodeOne         VPINameCode 
highlight link  VPINameEmphOne         VPINameEmph    
highlight link  VPINameCodeEmphOne     VPINameCodeEmph

syn match   VPIBackground    /./

let sep_row = g:Vimpoint_INTERMISSION_TITLE_ROW + 1

execute 'syn match  VPILine   /\%' . sep_row
      \                     .  'l\(\%2c\s*\ze\s\s\|\(\s\s\)\@<=\s*\ze\s$\)/ '

execute 'syn match  VPITitle  /\%<' . (sep_row+1) .  'l./ '
    \   'contains=VPITitleCode,VPITitleBold,VPITitleCodeBold,VPITitleCodeOne,VPITitleBoldOne,VPITitleCodeBoldOne,VPILine'

execute 'syn match  VPIName   /\%>' . sep_row .  'l./ '
    \   'contains=VPINameCode,VPINameBold,VPINameCodeBold,VPINameCodeOne,VPINameBoldOne,VPINameCodeBoldOne'


let b:current_syntax = "vpi"
