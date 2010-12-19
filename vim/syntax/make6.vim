" Vim syntax file
" Language:	Mythryl's make6
" Maintainer:	Jeffrey Lau <vim@NOSPAMjlau.tk>
" Last Change:	2010 Feb 16 (<- most likely out-dated)
" Remark:	(!) probably being phased out in 2--3 years
"
" Filenames:	*.make6, *.standard
" URL:		http://github.com/zoonfafer/vim-mythryl
" Creation:	2009 Dec 26


" For version 5.x: Clear all syntax items
" For version 6.x: Quit when a syntax file was already loaded
if version < 600
	syntax clear
elseif exists("b:current_syntax")
	finish
endif

" Mythryl make6 is case-sensitive
syn case match


"==============================================================
" Vim Syntax Clusters
"--------------------------------------------------------------

syn cluster make6ApiNameErrors
	\ contains=make6VariableError,
	\          make6ApiNameError

syn cluster make6PkgNameErrors
	\ contains=make6VariableError,
	\          make6PkgNameError

syn cluster make6NotTop
	\ contains=@make6ApiNameErrors,
	\          @make6PkgNameErrors,
	\          make6ApiName,
	\          make6PkgName

syn cluster make6Comment
	\ contains=make6OnelineComment,
	\          make6MultilineComment

syn cluster make6PreProcCondition
	\ contains=make6PreProcKeyword,
	\          make6PreProcFunction


"==============================================================
" special section headers
"--------------------------------------------------------------

syn keyword make6SectionHeader
	\ LIBRARY_GROUP_EXPORTS LIBRARY_GROUP_COMPONENTS
	\ LIBRARY_EXPORTS LIBRARY_COMPONENTS


"==============================================================
" some sort of keywords...
"--------------------------------------------------------------

syn match make6Keyword	"^make\>"
syn match make6Keyword	"group\>"
syn match make6Keyword	"library\>"


"==============================================================
" parentheses
"--------------------------------------------------------------

syn region make6Paren
	\ contains=ALLBUT,@make6NotTop,make6Special
	\ matchgroup=make6Keyword
	\ start="\%(^\s*\)\@<!(" end=")" skip="\\\\\|\\)"


"==============================================================
" Mythryl Identifiers
" Note: should really share with the main Mythryl syntax file
"--------------------------------------------------------------
syn match make6ApiName
	\ contained
	\ containedin=make6Api 
	\ contains=@make6Comments
	\ "[A-Z]\%(\%(_[A-Z'_0-9]\|[A-Z'0-9]\)[A-Za-z'_0-9]*\)\?[a-z][A-Za-z'_0-9]*"

syn match make6PkgName
	\ contained
	\ containedin=make6Pkg 
	\ contains=@make6Comments
	\ nextgroup=make6PackageColonColon 
	\ "[a-z][_'a-z0-9]*"

syn match make6PkgColonColon
	\ nextgroup=make6PackageName
	\ "\%([a-z][_'a-z0-9]*\)\@<=::"	

syn region make6Api
	\ contains=@make6ApiNameErrors,make6ApiName,@make6Comments
	\ matchgroup=make6Define
	\ start="\%(\s\+\%(-\s*\)\?\|(\s*\)\@<=api\>"
	\ matchgroup=make6ApiName
	\ end="\%($\|)\)\@="

syn region make6Pkg
	\ contains=@make6PkgNameErrors,make6PkgName,@make6Comments
	\ matchgroup=make6Define
	\ start="\%(\s\+\%(-\s*\)\?\|(\s*\)\@<=\%(pkg\|generic\|package\)\>"
	\ matchgroup=make6PkgName
	\ end="\%($\|)\|api\)\@="

syn match make6VariableError
	\ contained
	\ contains=NONE
	\ "[a-z]\S*[^a-z':_0-9)[:space:]][^[:space:]]*"

syn match make6VariableError
	\ contained
	\ contains=NONE
	\ "[A-Z]\S*[^A-Za-z':_0-9)[:space:]][^[:space:]]*"

syn match make6VariableError
	\ contained
	\ contains=NONE
	\  "_[a-z]\S*"

syn match make6ApiNameError
	\ contained
	\ containedin=make6Api
	\ contains=make6VariableError
	\ "\<[^A-Z]\S*" 

syn match make6PkgNameError
	\ contained
	\ containedin=make6Pkg
	\ contains=make6VariableError
	\ "\<[^a-z]\S*" 


"==============================================================
" Make6 Variable Identifiers
"--------------------------------------------------------------

syn region make6Ident
	\ contains=make6Statement,make6Ident,make6SString,make6DString
	\ start="\$(" skip="\\)\|\\\\" end=")"

syn region make6Ident
	\ contains=make6Statement,make6Ident,make6SString,make6DString
	\ start="\${" skip="\\}\|\\\\" end="}"

syn match make6Ident "\$\w*"


"==============================================================
" Comment
"--------------------------------------------------------------

syn match make6OnelineComment
	\ contains=@Spell,make6Todo
	\ "#\%(#\|\s\+\).*\|#$" 

syn region make6MultilineComment fold
	\ contains=make6Todo,make6MultilineComment
	\ start="/\*" end="\*/"

syn keyword make6Todo contained
	\ TODO FIXME XXX


"==============================================================
" Preproc... Conditionals... etc.
"--------------------------------------------------------------

syn match make6PreProc "\%(^\s*\)\@<=#\%(else\|endif\)"
syn match make6PreProc
	\ contains=@make6PreProcCondition,make6Api,make6Pkg
	\ "\%(^\s*\)\@<=#\%(if\|elif\).*$"

syn region make6PreProc
	\ matchgroup=make6PreProc
	\ start="\%(^\s*\)\@<=#error\>"
	\ matchgroup=make6PreProcErrorString
	\ end=".\+"

syn keyword make6PreProcFunction
	\ defined not or and

syn keyword make6PreProcKeyword
	\ ARCH_X86 ARCH_SPARC ARCH_PPC
	\ OPSYS_UNIX OPSYS_WIN32 OS_MACOS
	\ LITTLE_ENDIAN BIG_ENDIAN


"==============================================================
" Highlighting commands
"--------------------------------------------------------------
" Define the default highlighting.
" For version 5.7 and earlier: only when not done already
" For version 5.8 and later: only when an item doesn't have highlighting yet
if version >= 508 || !exists("did_make6_syn_inits")
	if version < 508
		let did_make6_syn_inits = 1
		command -nargs=+ HL hi link <args>
	else
		command -nargs=+ HL hi def link <args>
	endif

	HL make6Ident		Identifier
	HL make6OnelineComment	Comment
	HL make6MultilineComment	Comment
	HL make6Todo		Todo
	HL make6Define		Define
	HL make6Keyword		Keyword
	HL make6PreProcKeyword	Keyword
	HL make6PreProcFunction	Function
	HL make6SectionHeader	Keyword
	HL make6ApiName		Type
	HL make6PkgName		Identifier
	HL make6PreProc		Preproc
	HL make6PreProcConditional	Statement
	HL make6PreProcErrorString	String
	HL make6Special		Special
	HL make6VariableError	Error
	HL make6ApiNameError	Error
	HL make6PkgNameError	Error

	delcommand HL
endif

let b:current_syntax = "make6"

" vim: ts=8
