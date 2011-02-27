" Vim syntax file
" Language: Perldoc file
" Maintainer: Petar Shangov (pshangov@yahoo.com)
" Last Change:  2006 Apr 06

if version < 600
  syntax clear
elseif exists("b:current_syntax")
  finish
endif

:syntax region perldocHead matchgroup=perldocIgnore start="^" end=" \~$" oneline
:syntax match perldocBullet "\t*  \* "
:syntax match perldocItem "^\t.*"
:syntax region perldocCode matchgroup=perldocIgnore start=/^>$/ end=/^<$/

:highlight default link perldocHead String
:highlight default link perldocCode Identifier 
:highlight default link perldocIgnore Ignore 
:highlight default link perldocItem Statement 
:highlight default link perldocBullet Statement

let b:current_syntax = "perldoc2"
syntax sync fromstart

" vim: ts=8 sw=2

