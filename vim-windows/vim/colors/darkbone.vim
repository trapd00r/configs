" Name:		darkbone.vim
" Maintainer:	Kojo Sugita
" Last Change:	2008-11-22
" Revision:	1.1

set background=dark
hi clear
if exists("syntax_on")
  syntax reset
endif
let g:colors_name = 'darkbone'

"default colors
hi Normal	guifg=#ffffff guibg=#121212
hi NonText	guifg=#606080 guibg=#121212
hi SpecialKey	guifg=#404060
hi Cursor	guifg=#121212 guibg=#ff8000
hi CursorLine	guibg=#121212
hi CursorColumn	guibg=#121212
hi lCursor	guifg=#121212 guibg=#a0a0c0
hi CursorIM	guifg=#121212 guibg=#a0a0c0

" Directory
hi Directory	guifg=#e0e0ff guibg=#121212 gui=bold

" Diff
hi DiffAdd	guifg=#8090f0 guibg=#121212 gui=none
hi DiffChange	guifg=#8090f0 guibg=#121212 gui=none
hi DiffDelete	guifg=#8090f0 guibg=#121212 gui=none
hi DiffText	guifg=#8090f0 guibg=#121212 gui=bold

" Message
hi ModeMsg	guifg=#a0a0c0 guibg=#121212
hi MoreMsg	guifg=#a0a0c0 guibg=#121212
hi ErrorMsg	guifg=#ff0000 guibg=#121212
hi WarningMsg	guifg=#f10e0e guibg=#121212

hi VertSplit	guifg=#606080 guibg=#606080

" Folds
hi Folded	guifg=#a0a0c0 guibg=#121212
hi FoldColumn	guifg=#a0a0c0 guibg=#102010

" Search
hi Search	guifg=#121212 guibg=#ff5300 gui=bold
hi IncSearch	guifg=#121212 guibg=#df4800 gui=none

hi LineNr	guifg=#606080 guibg=#121212 gui=none
hi Question	guifg=#a0a0c0 guibg=#121212

"\n, \0, %d, %s, etc...
" hi Special	guifg=#d0e080 guibg=#121212 gui=none
hi Special	guifg=#808080 guibg=#121212 gui=none

" status line
hi StatusLine	guifg=#808080 guibg=#121212 gui=bold,underline
hi StatusLineNC	guifg=#606080 guibg=#121212 gui=bold,underline
hi WildMenu	guifg=#121212 guibg=#c0c0ff

hi Title	guifg=#c0c0ff guibg=#121212 gui=bold
hi Visual	guifg=#121212 guibg=#707090 gui=none
hi VisualNOS	guifg=#a0a0c0 guibg=#121212

hi Number	guifg=#1692dc guibg=#121212 gui=bold
hi Char		guifg=#d0e080 guibg=#121212
hi String	guifg=#bc742c guibg=#121212

hi Boolean	guifg=#ff0000 guibg=#121212
hi Comment	guifg=#808080
hi Constant 	guifg=#f0a0b0 guibg=#121212 gui=none
hi Identifier	guifg=#8090f0
hi Statement	guifg=#8090f0 gui=none

"Procedure name
hi Function	guifg=#f0b040

"Define, def
" hi PreProc	guifg=#f0a0b0 gui=none
hi PreProc	guifg=#e0e0ff gui=none

hi Type		guifg=#e0e0ff gui=none
hi Underlined	guifg=#a0a0c0 gui=underline
hi Error	guifg=#ee1111 guibg=#121212
hi Todo		guifg=#8090f0 guibg=#121212 gui=none
hi SignColumn   guibg=#121212

" Matches
hi MatchParen	guifg=#ff0000 guibg=#121212 gui=none

if version >= 700
  " Pmenu
  hi Pmenu	guibg=#202040
  hi PmenuSel	guibg=#404080 guifg=#a0a0c0
  hi PmenuSbar	guibg=#202040

  " Tab
  hi TabLine	  guifg=#888888 guibg=#121212 gui=underline
  hi TabLineFill  guifg=#ff0000 guibg=#121212 gui=none
  hi TabLineSel	  guifg=#e24705 guibg=#060606 gui=bold
endif

" vim:set ts=8 sts=2 sw=2 tw=0:
