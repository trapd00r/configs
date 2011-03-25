filetype plugin indent on
set formatprg=perl\ -MText::Autoformat\ -e'autoformat'
set formatoptions=qro

au BufWritePost *.{sh,pl} silent exe

au BufRead,BufNewFile *.markdown set ft=md
au BufRead,BufNewFile *.md set ft=md
au BufRead,BufNewFile *.go set ft=go
au BufRead,BufNewFile *.txt set ft=_txt


au      FileType pl,pm,t set filetype=perl
au      FileType perl :noremap K :!perldoc <cword> <bar><bar> perldoc -f <cword><cr>
au!     FileType perl :noremap <leader>c
    \ :!time perl -Mwarnings::unused -MVi::QuickFix -c %<cr>

autocmd FileType perl set makeprg=perl\ -c\ %\ $*
autocmd FileType perl setlocal errorformat=%f:%l:%m
autocmd FileType perl setlocal keywordprg=perldoc\ -f
autocmd! BufNewFile * silent! 0r ~/configs/vim/templates/template.%:e

"autocmd BufNewFile,BufRead *.p? compiler perl
"au BufWritePost *.pl,*.pm !perl -c %

let g:tex_conceal                = 1

let g:perl_compiler_force_warnings = 0

let perl_moose_stuff             = 1
let perl_no_scope_in_variables   = 1
let perl_no_sync_on_sub          = 1
let perl_no_sync_on_global_var   = 1
let perl_extended_vars           = 1
let perl_include_pod             = 1
let perl_string_as_statement     = 1
let perl_nofold_packages         = 1
let perl_sync_dist               = 1000
let perl_want_scope_in_variables = 1
let perl_pod_formatting          = 1
let perl_pod_spellcheck_headings = 1
let perlhelp_prog                = '/usr/bin/perldoc'

let extradite_width              = 40




"let g:indent_guides_auto = 0
"autocmd VimEnter,Colorscheme * :hi IndentGuidesOdd  ctermbg=233
"autocmd VimEnter,Colorscheme * :hi IndentGuidesEven ctermbg=234
