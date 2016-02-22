" Vim syntax file
" Language:     Mythryl for scripting
" Maintainer:   Jeffrey Lau <vim@NOSPAMjlau.tk>
" Last Change:	2010 Feb 18 (<- most likely out-dated)
" Remark:	includes the Mythryl syntax
" 
" Filenames:	N/A
" URL:          http://github.com/zoonfafer/vim-mythryl
" Creation:	2010 Feb 18

" For version 5.x: Clear all syntax items
" For version 6.x: Quit when a syntax file was already loaded
if version < 600
	syntax clear
elseif exists("b:current_syntax")
	finish
endif

" Mythryl is case-sensitive
syn case match


"==============================================================
" Vim Syntax Includes
"--------------------------------------------------------------

" syn include @Mythryl <sfile>:p:h/mythryl.vim
" runtime! <sfile>:p:h/mythryl.vim """ <-- doesn't work.

if version < 600
	source <sfile>:p:h/mythryl.vim
else
	runtime! syntax/mythryl.vim
	unlet b:current_syntax
endif


"==============================================================
" Mythryl Scripting Globals
" Note:	identifiers taken from "package scripting_globals" of:-
"	   src/lib/core/internal/make7.api
"	of Mythryl's source distribution.
"--------------------------------------------------------------

syn keyword myScriptingGlobal
	\ atod atoi back__ticks basename bash chdir chomp die dirname
	\ environ eval evali evalf evals evalli evallf evalls exit explode
	\ factors fields filter fscanf
	\ getcwd getenv getpid getuid geteuid getppid
	\ getgid getegid getgroups getlogin getpgrp
	\ mkdir
	\ setgid setpgid setsid setuid
	\ implode in iseven isodd isprime join' join
	\ lstat now product rename rmdir round
	\ shuffle' shuffle sleep sort sorted
	\ scanf sscanf
	\ stat strcat strlen strsort struniqsort
	\ sum system time tolower toupper
	\ tokens trim uniquesort unlink words
	\ dot__qquotes arg0 argv
	\ isfile isdir ispipe issymlink issocket ischardev isblockdev
	\ mayread maywrite mayexecute
	\ eval_kludge_ref_int eval_kludge_ref_float eval_kludge_ref_string
	\ eval_kludge_ref_list_int eval_kludge_ref_list_float eval_kludge_ref_list_string


"==============================================================
" Highlighting commands
"--------------------------------------------------------------
" Define the default highlighting.
" For version 5.7 and earlier: only when not done already
" For version 5.8 and later: only when an item doesn't have highlighting yet
if version >= 508 || !exists("did_mythryl_script_syntax_inits")
	if version < 508
		let did_mythryl_script_syntax_inits = 1
		command -nargs=+ HL hi link <args>
	else
		command -nargs=+ HL hi def link <args>
	endif

	""" Keywords
	HL myScriptingGlobal	Keyword

	delcommand HL
endif

let b:current_syntax = "mythryl-script"

" vim: ts=8
