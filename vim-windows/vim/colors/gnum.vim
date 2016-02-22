" local syntax file - set colors on a per-machine basis:
" vim: tw=0 ts=4 sw=4
" Vim color file
" Maintainer:	Heikki Mehtänen <heikki@mehtanen.fi>
" Last Change:	2009 Dec 01

set background=dark
hi clear
if exists("syntax_on")
  syntax reset
endif
let g:colors_name = "gnum"
hi Normal		guifg=green			guibg=black
hi Comment	term=bold		ctermfg=DarkGrey		guifg=#80a0ff
hi Constant	term=underline	ctermfg=Yellow			guifg=Magenta
hi Special	term=bold		ctermfg=Grey	guifg=Red
hi Identifier term=underline	cterm=bold			ctermfg=Green guifg=#40ffff
hi Statement term=bold		ctermfg=White gui=bold	guifg=#aa4444
hi PreProc	term=underline	ctermfg=LightBlue	guifg=#ff80ff
hi Type	term=underline		ctermfg=LightGreen	guifg=#60ff60 gui=bold
hi Function	term=bold		ctermfg=Yellow		guifg=Yellow
hi Repeat	term=underline	ctermfg=White		guifg=Blue
hi Operator				ctermfg=Red			guifg=Red
hi Ignore				ctermfg=black		guifg=bg
hi Error	term=reverse ctermbg=Red ctermfg=White guibg=Red guifg=White
hi Todo	term=standout ctermbg=Yellow ctermfg=Black guifg=Blue guibg=Yellow
hi LineNr	ctermfg=Grey guifg=Grey

" Common groups that link to default highlighting.
" You can specify other highlighting easily.
hi link String	Constant
hi link Character	Constant
hi link Number	Constant
hi link Boolean	Constant
hi link Float		Number
hi link Conditional	Repeat
hi link Label		Statement
hi link Keyword	Statement
hi link Exception	Statement
hi link Include	PreProc
hi link Define	PreProc
hi link Macro		PreProc
hi link PreCondit	PreProc
hi link StorageClass	Type
hi link Structure	Type
hi link Typedef	Type
hi link Tag		Constant
hi link SpecialChar	Special
hi link Delimiter	Special
hi link SpecialComment Special
hi link Debug		Special
