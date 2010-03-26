" Vim compiler file
" Compiler:     Perl syntax checks (perl -Wc) v1.1
" Maintainer:   Lukas Zapletal <Lukas.Zapletal@seznam.cz>
" Last Change:  2001 Sep 10

" Changelog:
"
" 1.1: fixed ' near "..." '
" 1.0: initial version
" 

" Todo:
" Include ' near "..." ' in the error message

if exists("current_compiler")
  finish
endif
let current_compiler = "perl"

" there is no pipes under windows, vi use temp file
" and as perl outputs to stderr this have to be handled corectly
if has("win32")
	setlocal shellpipe=1>&2\ 2>
endif

setlocal makeprg=perl\ -Wc\ %

" Sample errors:
" Type of arg 1 to push must be array (not hash element) at NFrame.pm line 129, near ");"
" Useless use of a constanst at test.pl line 5.
setlocal errorformat=%m\ at\ %f\ line\ %l%.%#,
                    \%-G%.%# " ignore any lines that didn't match one of the patterns above
