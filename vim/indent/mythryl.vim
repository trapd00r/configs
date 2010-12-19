" Vim indent file
" Language:	Mythryl
" Maintainer:	Jeffrey Lau <vim@NOSPAMjlau.tk>
" Last Change:	2010 Feb 18 (<- most likely out-dated)
" Remark:	included by the Mythryl-script indent file
"
" URL:		http://github.com/zoonfafer/vim-mythryl
"

" Only load this indent file when no other was loaded.
if exists("b:did_indent")
	finish
endif
let b:did_indent = 1

setlocal noexpandtab
setlocal indentexpr=GetMythrylIndent()
setlocal nolisp
setlocal smartindent
setlocal textwidth=80
setlocal shiftwidth=4
setlocal softtabstop=4

"==============================================================
" Url:	http://mythryl.org/my-Indentation.html
"  Indent four blanks per nested scope, with the following exceptions:
"   * Indent multi-line case statement bodies five blanks.
"   * Indent multi-line if statement conditions and bodies five blanks.
"   * Indent multi-line tuple and record contents two blanks, to distinguish them from code. 
"--------------------------------------------------------------


function! GetMythrylIndent()

	return 0

endfunction


" vim:sw=8
