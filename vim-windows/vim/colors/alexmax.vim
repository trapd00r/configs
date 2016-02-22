" alexmax.vim by AlexMax
"
" A theme designed for a 16 color terminal.  Looks best with Python, other
" languages are supported piecemeal as I find the time and/or care.
"
" Syntax colors are based loosely on the Sunburst theme for Textmate,
" translated into the 16 standard ANSI terminal colors.  Interface colors
" tend to adhere to a white-on-blue asthetic, reminiscent of irssi.
"
" If you're going to hack support for your favorite language into this
" colorscheme, be aware that due to the inconsistent way that some of the vim
" syntax files are put together it's not always possible to make a language
" highlight similarly to Python.  For example, many syntax files consider
" parentheses an operator, or do not count quotes as being part of a string.
"
" Since the theme is loosely based on Sunburst, GUI users can use:
"     let alexmax_sunburst = 1 
" to turn the syntax highlighting colors into something more closely
" resembling the actual Sunburst theme.  Please note that this only swaps out
" color definitions, it does not attempt to make the actual syntax
" highlighting resemble Textmate any more or less than the default colors do.

set background=dark
highlight clear
if exists("syntax_on")
	syntax reset
endif
let g:colors_name = "alexmax"

" GUI color equivalents.
let s:Black='#000000'
let s:DarkBlue='#0000bb'
let s:DarkGreen='#00bb00'
let s:DarkGray='#555555'
let s:DarkCyan='#00bbbb'
let s:DarkRed='#bb0000'
let s:DarkMagenta='#bb00bb'
let s:DarkYellow='#bbbb00'
let s:Gray='#bbbbbb'
let s:Blue='#5555ff'
let s:Green='#55ff55'
let s:Cyan='#55ffff'
let s:Red='#ff5555'
let s:Magenta='#ff55ff'
let s:Yellow='#ffff55'
let s:White='#ffffff'

if has("gui_macvim")
	if exists("alexmax_sunburst") && alexmax_sunburst != 0
		" GUI-style text and cursor
		exe 'hi Normal guifg='.s:White.' guibg='.s:Black
		exe 'hi Cursor guibg='.s:White
	else
		" Terminal-style text and cursor
		exe 'hi Normal guifg='.s:Gray.' guibg='.s:Black
		exe 'hi Cursor guibg='.s:Green
	endif
endif

" Base vim color scheme
exe 'hi Cursor guibg='.s:Green 
exe 'hi Directory ctermfg=White guifg='.s:White
exe 'hi Folded ctermfg=White guifg='.s:White
exe 'hi FoldColumn ctermfg=Yellow guifg='.s:Yellow
exe 'hi HelpExample ctermfg=White guifg='.s:White
exe 'hi LineNr ctermfg=White guifg='.s:White
exe 'hi MatchParen cterm=Reverse ctermfg=Gray ctermbg=None guibg='.s:Gray
exe 'hi NonText ctermfg=DarkGray guifg='.s:DarkGray
exe 'hi Pmenu ctermfg=Gray ctermbg=DarkBlue guifg='.s:Gray.' guibg='.s:DarkBlue
exe 'hi PmenuSel ctermfg=White ctermbg=DarkBlue guifg='.s:White.' guibg='.s:DarkBlue
exe 'hi SignColumn ctermfg=Yellow guifg='.s:Yellow
exe 'hi SpecialKey ctermfg=DarkGray guifg='.s:DarkGray
exe 'hi StatusLine cterm=None ctermfg=White ctermbg=DarkBlue gui=None guifg='.s:White.' guibg='.s:DarkBlue
exe 'hi StatusLineNC cterm=None ctermfg=Gray ctermbg=DarkBlue gui=None guifg='.s:Gray.' guibg='.s:DarkBlue
exe 'hi VertSplit cterm=None ctermfg=DarkBlue ctermbg=None guifg='.s:Black.' guibg='.s:DarkBlue
exe 'hi WildMenu ctermfg=Yellow ctermbg=DarkBlue guifg='.s:Yellow.' guibg='.s:DarkBlue

" Redefine syntax colors to look more like Textmate's Sunburst in the GUI.
if exists("alexmax_sunburst") && alexmax_sunburst != 0
	let s:DarkGreen='#65b042'
	let s:Gray='#aeaeae'
	let s:Blue='#3e87e3'
	let s:Green='#99cf50'
	let s:Cyan='#89bdff'
	let s:Red='#e28964'
	let s:Yellow='#dad085'
endif

" Base vim syntax highlighting.
exe 'hi Comment ctermfg=DarkGray gui=Italic guifg='.s:DarkGray
exe 'hi Constant ctermfg=Blue guifg='.s:Blue
exe 'hi Delimiter ctermfg=Gray guifg='.s:White
exe 'hi Entity ctermfg=Cyan guifg='.s:Cyan
exe 'hi Identifier cterm=NONE ctermfg=Blue guifg='.s:Blue
exe 'hi PreProc ctermfg=Cyan guifg='.s:Cyan
exe 'hi String ctermfg=DarkGreen guifg='.s:DarkGreen
exe 'hi Special ctermfg=Yellow guifg='.s:Yellow
exe 'hi Statement ctermfg=Red guifg='.s:Red
exe 'hi Type ctermfg=Green guifg='.s:Green

" HTML highlighting.
exe 'hi htmlArg ctermfg=Cyan guifg='.s:Cyan
exe 'hi htmlTag ctermfg=Cyan guifg='.s:Cyan
exe 'hi htmlTagN ctermfg=Cyan guifg='.s:Cyan
exe 'hi htmlTagName ctermfg=Cyan guifg='.s:Cyan
exe 'hi htmlEndTag ctermfg=Cyan guifg='.s:Cyan

" PHP highlighting.
" * Assumes usage of Paul Garvin's php.vim syntax file.
exe 'hi phpConstants ctermfg=Red guifg='.s:Red
exe 'hi phpFunctions ctermfg=Yellow guifg='.s:Yellow
exe 'hi phpInclude ctermfg=Red guifg='.s:Red
exe 'hi phpMemberSelector ctermfg=Red guifg='.s:Red
exe 'hi phpParent ctermfg=Gray guifg='.s:Gray
exe 'hi phpSpecial ctermfg=Green guifg='.s:Green
exe 'hi phpVarSelector ctermfg=Blue guifg='.s:Blue

" Python highlighting.
" * Assumes usage of Ian McCracken's python.vim syntax file.
exe 'hi pythonBuiltinFunc ctermfg=Yellow guifg='.s:Yellow
exe 'hi pythonClassDef ctermfg=Green guifg='.s:Green
exe 'hi pythonFuncDef ctermfg=Green guifg='.s:Green
exe 'hi pythonParamName ctermfg=Blue guifg='.s:Blue

" Shell highlighting.
exe 'hi shDerefSimple ctermfg=Blue guifg='.s:Blue
exe 'hi shRange ctermfg=Gray guifg='.s:Gray
exe 'hi shSnglCase ctermfg=Gray guifg='.s:Gray

" XML highlighting.
exe 'hi xmlAttrib ctermfg=Cyan guifg='.s:Cyan
exe 'hi xmlEntityPunct ctermfg=Blue guifg='.s:Blue
exe 'hi xmlEntityPunct ctermfg=Blue guifg='.s:Blue
exe 'hi xmlEqual ctermfg=Cyan guifg='.s:Cyan
exe 'hi xmlProcessingDelim ctermfg=Cyan guifg='.s:Cyan
exe 'hi xmlTagName ctermfg=Cyan guifg='.s:Cyan
