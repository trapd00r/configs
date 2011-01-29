syn match Parens display '()'
syn match Braces display '[\{}]'
syn match Brackets display '[][]'
"syn region cParen matchgroup=Delimiter start='(' end=')' contains=ALL
"hi cParen ctermfg=196
"au VimEnter * au Syntax * syn match Braces display '[]{}()[]' 
"syn match openParen "(\_[^)]*\%$"

hi Parens ctermfg=220 cterm=bold
hi Braces  cterm=bold
hi Brackets  cterm=bold
"hi Brackets ctermfg=202 cterm=bold
"perlNiceOperator  Operator

