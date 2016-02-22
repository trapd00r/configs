" chris2's colorscheme
"
" mostly monochrome
"
" Maintainer:   Christian Neukirchen <chneukirchen@gmail.com>
" Last Change:  29sep2009

set background=dark
hi clear
if exists("syntax_on")
  syntax reset
endif
let g:colors_name = "chris2"

hi Normal       guifg=grey88 guibg=Grey14
hi clear Special
hi clear Comment
hi clear Constant
hi clear Identifier
hi clear Statement
hi clear PreProc
hi clear Type
hi Ignore       guifg=grey30 ctermfg=8
hi Error        gui=NONE guifg=NONE guibg=Firebrick3
hi Todo         term=bold cterm=bold gui=bold ctermfg=NONE ctermbg=NONE guifg=NONE guibg=NONE

hi SpecialKey   guifg=grey50 ctermfg=8

hi Directory    guifg=NONE gui=italic 
hi FoldColumn   guibg=black guifg=NONE
hi Folded       guibg=fg guifg=bg
hi ModeMsg      gui=bold
hi MoreMsg      gui=bold guifg=NONE
hi NonText      gui=bold guifg=Grey30 ctermfg=8
hi Question     gui=bold guifg=NONE
hi SignColumn   guibg=Grey guifg=DarkBlue

hi StatusLine   gui=bold guifg=black guibg=Gray70
hi StatusLineNC gui=NONE guifg=Gray76 guibg=Gray23
hi VertSplit    gui=NONE guifg=Gray76 guibg=Gray23
hi LineNr       guifg=Grey30 guibg=Grey5

hi TabLine      gui=underline guibg=LightGrey term=reverse cterm=reverse ctermfg=NONE ctermbg=NONE
hi TabLineFill  gui=reverse
hi TabLineSel   gui=bold

hi ErrorMsg     guibg=Firebrick2 guifg=White
hi WarningMsg   guifg=Firebrick2

hi Cursor       guibg=green guifg=bg
hi CursorColumn guibg=Gray20
hi CursorIM     guibg=green guifg=bg
hi CursorLine   guibg=Gray20
hi lCursor      guibg=yellow guifg=bg
hi Visual       gui=bold guifg=red guibg=NONE term=reverse cterm=bold ctermfg=1 ctermbg=NONE

hi MatchParen   guifg=green guibg=NONE ctermbg=NONE ctermfg=2
hi Search       guibg=NONE guifg=#1e90ff
hi IncSearch    guibg=NONE guifg=#1e90ff

hi Title        gui=bold guifg=DeepSkyBlue3 term=bold cterm=bold ctermfg=NONE ctermfg=NONE
hi Subtitle     gui=bold term=bold cterm=bold
hi link helpHeader Title
hi link helpHeadline Subtitle
