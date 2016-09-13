" Vim color file - neverlandgui.vim
" Eyes are sober, this is the plan
" I'm still sitting in a car heading Neverland
" Author: Magnus Woldrich <magnus.woldrich@gmail.com>
" 2016-02-22


" Set background first
set background=dark
hi clear

if version > 580
    " no guarantees for version 5.8 and below, but this makes it stop
    " complaining
    if exists("syntax_on")
        syntax reset
    endif
endif
let g:colors_name="neverlandgui"

" Setting normal before any other highlight group is a good idea
hi Normal          guifg=#ffffff guibg=#121212

" background might have changed to 'light', so fix it
set background=dark

hi Boolean         guifg=#af5fff guibg=bg      gui=none
hi Character       guifg=#afaf5f guibg=bg      gui=none
hi ColorColumn     guifg=fg      guibg=#262626 gui=none
hi Comment         guifg=#808080 guibg=bg      gui=none
hi Conditional     guifg=#ff0000 guibg=bg      gui=bold
hi Constant        guifg=#87af00 guibg=bg      gui=bold
hi Cursor          guifg=#000000 guibg=#e88b00 gui=none
hi CursorColumn    guifg=fg      guibg=#121212 gui=none
hi CursorLine      guifg=fg      guibg=#1c1c1c gui=none
hi CursorLineNr    guifg=#000000 guibg=#d70000 gui=boldreverse
hi Debug           guifg=#ffd7ff guibg=bg      gui=bold
hi Define          guifg=#5fd7ff guibg=bg      gui=none  
hi Delimiter       guifg=#808080 guibg=bg      gui=none  
hi DiffAdd         guifg=fg      guibg=#005f87 gui=none
hi DiffChange      guifg=#d7afaf guibg=#4e4e4e gui=none
hi DiffDelete      guifg=#d70087 guibg=#5f005f gui=none
hi DiffText        guifg=fg      guibg=#878787 gui=bold
hi Directory       guifg=#87ff00 guibg=bg      gui=bold
hi Error           guifg=#ffafff guibg=#87005f gui=none
hi ErrorMsg        guifg=#ff00af guibg=#000000 gui=bold
hi Exception       guifg=#87ff00 guibg=bg      gui=bold
hi Float           guifg=#af5fff guibg=bg      gui=none
hi FoldColumn      guifg=#5f87af guibg=#121212 gui=none
hi Folded          guifg=#585858 guibg=#262626 gui=bold
hi Function        guifg=#87ff00 guibg=bg      gui=none
hi Identifier      guifg=#afd75f guibg=bg      gui=none
hi Ignore          guifg=#808080 guibg=#080808 gui=none
hi IncSearch       guifg=#121212 guibg=#121212 gui=none
hi Keyword         guifg=#87afff guibg=bg      gui=bold
hi Label           guifg=#ffffaf guibg=bg      gui=none
hi LineNr          guifg=#808080 guibg=#121212 gui=none
hi Macro           guifg=#d7ffaf guibg=bg      gui=none
hi MatchParen      guifg=#ff0000 guibg=#1c1c1c gui=bold
hi ModeMsg         guifg=#ffaf5f guibg=bg      gui=none
hi MoreMsg         guifg=#888888 guibg=bg      gui=italic
hi NonText         guifg=#121212 guibg=#121212 gui=none
hi Number          guifg=#0087ff guibg=bg      gui=none
hi Operator        guifg=#afd700 guibg=bg      gui=none
hi Pmenu           guifg=#af875f guibg=#000000 gui=none
hi PmenuSbar       guifg=#000000 guibg=#121212 gui=none
hi PmenuSel        guifg=#ff0000 guibg=#262626 gui=bold
hi PmenuThumb      guifg=#af875f guibg=#000000 gui=none
hi PreCondit       guifg=#87ff00 guibg=bg      gui=bold
hi PreProc         guifg=#ffafd7 guibg=bg      gui=none
hi Question        guifg=#5fd7ff guibg=bg      gui=none
hi Repeat          guifg=#d7005f guibg=bg      gui=bold
hi Search          guifg=#121212 guibg=#ff0000 gui=bold
hi SignColumn      guifg=#87ff00 guibg=#262626 gui=none
hi Special         guifg=#5fd7ff guibg=#080808 gui=none
hi SpecialChar     guifg=#d7005f guibg=bg      gui=bold
hi SpecialComment  guifg=#8a8a8a guibg=bg      gui=bold
hi SpecialKey      guifg=#5fd7ff guibg=bg      gui=none
hi SpellBad        guifg=#ff0000 guibg=#121212 gui=bold
hi SpellCap        guifg=#875f00 guibg=#121212 gui=bold
hi SpellLocal      guifg=#af0000 guibg=#121212 gui=bold
hi SpellRare       guifg=#875f87 guibg=#121212 gui=bold
hi Statement       guifg=#d78700 guibg=bg      gui=bold
hi StatusLine      guifg=#121212 guibg=#b87649 gui=reverse
hi StatusLineNC    guifg=#666666 guibg=#121212 gui=none
hi StorageClass    guifg=#ff8700 guibg=bg      gui=none
hi String          guifg=#d7af5f guibg=bg      gui=none
hi Structure       guifg=#5fd7ff guibg=bg      gui=none
hi TabLine         guifg=#484848 guibg=#121212 gui=underline
hi TabLineFill     guifg=#484848 guibg=#121212 gui=underline
hi TabLineSel      guifg=#000000 guibg=#f77722 gui=bold
hi Tag             guifg=#d7005f guibg=bg      gui=none
hi Title           guifg=#5faf5f guibg=bg      gui=none
hi Todo            guifg=#d70000 guibg=#121212 gui=bold
hi Type            guifg=#d75f00 guibg=bg      gui=none
hi Typedef         guifg=#5fd7ff guibg=bg      gui=none
hi Underlined      guifg=#121212 guibg=#121212 gui=reverseboldunderlineitalic
hi VertSplit       guifg=#808080 guibg=#080808 gui=bold
hi Visual          guifg=#ff0000 guibg=#000000 gui=bold
hi VisualNOS       guifg=fg      guibg=#444444 gui=none
hi WarningMsg      guifg=#0000ff guibg=#444444 gui=bold
hi WildMenu        guifg=#5fd7ff guibg=#000000 gui=none
