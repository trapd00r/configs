" mY oWn Chaos taking.
" Author: Yue Wu <ywupub@gmail.com>
" License: BSD

if exists("b:current_syntax")
  finish
endif

" Yup, it's html!
runtime syntax/html.vim

syntax match ywchaosTag '\s\zs@[^@[:blank:]]*' contains=ywchaosTagPre
syntax match ywchaosTag '^\zs@[^@[:blank:]]*' contains=ywchaosTagPre
highlight def link ywchaosTag Tag

syntax match ywchaosTagPre '@' contained
highlight def link ywchaosTagPre Ignore

syntax match ywchaosDateEntry '^\d\{,2}/\d\{,2}/\d\{,4}'
highlight def link ywchaosDateEntry Title
syntax match ywchaosTimeEntry '^\d\{,2}:\d\{,2}[[:digit:]:-]*'
highlight def link ywchaosTimeEntry Number

highlight def link ywchaoskwd Statement

" syntax region ywchaosTagsLine matchgroup=Comment start='^<TAGS>$' end='^<\/TAGS>$' contains=ALL
