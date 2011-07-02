filetype plugin indent on
set formatprg=perl\ -MText::Autoformat\ -e'autoformat'
set formatoptions=qro

au filetype git,*commit* call ToggleSpell()
au filetype help call Filetype_help()

au BufWritePost *.{sh,pl} silent exe

au BufRead * call SetCursorPosition()

" Vim doesn't want to perform events on symlinks
let g:vimrc            = "/home/scp1/etc/vimrc"
let g:vimrc_statusline = "/home/scp1/etc/vim/after/plugin/statusline.vim"
let g:vimrc_functions  = "/home/scp1/etc/vim/functions.vim"

au BufRead,BufNewFile *.md,*.mkd,*.markdown  set ft=md | normal gg
au BufRead,BufNewFile *.go   set ft=go
au BufNewFile         *.txt  set ft=_txt


au BufRead,BufNewFile *.xml  set sw=1
au BufRead,BufNewFile *.html set sw=1
au BufRead,BufNewFile *.htm  set sw=1
au BufRead,BufNewFile *.css  set sw=2

au BufRead,BufNewFile ~/etc/zsh/01-colors.zsh set syntax=

au  FileType pl,pm,t set filetype=perl
au  FileType perl :noremap K :!perldoc <cword> <bar><bar> perldoc -f <cword><cr>

au FileType perl set makeprg=perl\ -c\ %\ $*
au FileType perl setlocal errorformat=%f:%l:%m
au FileType perl setlocal keywordprg=perldoc\ -f

au! BufNewFile * silent! 0r ~/etc/vim/templates/template.%:e 

let g:VimrexFileDir                = expand("~/") . 'var/vim/'
let g:netrw_http_cmd               = 'w3m'
let g:netrw_http_xcmd              = '-dump >'

let g:tex_conceal                  = 1

let vim_indent_cont                = 2
let g:vt_template_dir_path         = '~/.vim/templates/'
let g:vt_author                    = 'Magnus Woldrich'
let g:vt_email                     = 'm@japh.se'

let g:perl_compiler_force_warnings = 0

let perl_moose_stuff               = 1
let perl_no_scope_in_variables     = 1
let perl_no_sync_on_sub            = 1
let perl_no_sync_on_global_var     = 1
let perl_extended_vars             = 1
let perl_include_pod               = 1
let perl_string_as_statement       = 1
let perl_nofold_packages           = 1
let perl_sync_dist                 = 1000
let perl_want_scope_in_variables   = 1
let perl_pod_formatting            = 1
let perl_pod_spellcheck_headings   = 1
let perlhelp_prog                  = '/usr/bin/perldoc'

let extradite_width                = 40

let space_no_jump                  = 1

"let g:indent_guides_auto = 0
"au VimEnter,Colorscheme * :hi IndentGuidesOdd  ctermbg=233
"au VimEnter,Colorscheme * :hi IndentGuidesEven ctermbg=234
