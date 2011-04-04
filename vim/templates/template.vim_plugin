" vim:foldmethod=marker:fen:
scriptencoding utf-8

" Change Log: {{{
" }}}
" Document {{{
"
" Name: <% eval: expand('%:t:r') %>
" Version: 0.0.0
" Author:  tyru <tyru.exe@gmail.com>
" Last Change: .
" License: Distributable under the same terms as Vim itself (see :help license)
"
" Description:
"   NO DESCRIPTION YET
"
" Usage: {{{
"   Commands: {{{
"   }}}
"   Mappings: {{{
"   }}}
"   Global Variables: {{{
"   }}}
" }}}
" }}}

" Load Once {{{
if (exists('g:loaded_<%eval:substitute(expand("%:t:r"), "\\m\\W", "_", "g")%>') && g:loaded_<%eval:substitute(expand("%:t:r"), "\\m\\W", "_", "g")%>) || &cp
    finish
endif
let g:loaded_<%eval:substitute(expand("%:t:r"), "\\m\\W", "_", "g")%> = 1
" }}}
" Saving 'cpoptions' {{{
let s:save_cpo = &cpo
set cpo&vim
" }}}



" Restore 'cpoptions' {{{
let &cpo = s:save_cpo
" }}}
