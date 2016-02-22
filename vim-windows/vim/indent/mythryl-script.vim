" Vim indent file
" Language:	Mythryl for scripting
" Maintainer:	Jeffrey Lau <vim@NOSPAMjlau.tk>
" Last Change:	2010 Feb 25 (<- most likely out-dated)
" Remark:	includes the Mythryl indent file
"
" URL:		http://github.com/zoonfafer/vim-mythryl
"

" Only load this indent file when no other was loaded.
if exists("b:did_indent")
	finish
endif


"==============================================================
" Vim Indent Includes
"--------------------------------------------------------------

" syn include @Mythryl <sfile>:p:h/mythryl.vim
" runtime! <sfile>:p:h/mythryl.vim """ <-- doesn't work.

if version < 600
	source <sfile>:p:h/mythryl.vim
else
	runtime! indent/mythryl.vim
	" unlet b:did_indent
	" Umm:  Do we really need that?
endif

let b:did_indent = 1

" vim:sw=8
