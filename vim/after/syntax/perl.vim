" vim-perl-extra
" Magnus Woldrich, 2011

syn match Parens      display '()'
"syn match Braces      display  '{\|}'
syn match Brackets    display '[][]'
syn match Dumper      display '.*Dumper'
syn match fat_comma   display '=>'
syn match comma       display ','

hi Parens    ctermfg=208 cterm=bold
hi Braces                cterm=bold
hi Brackets              cterm=bold
hi Dumper    ctermfg=196 cterm=bold
hi fat_comma ctermfg=136 cterm=bold
hi comma     ctermfg=246
hi dt        ctermfg=2   cterm=bold
