"    File: $HOME/etc/ftdetect.vim
"  Author: Magnus Woldrich <m@japh.se>
" Updated: 2011-07-06 11:15:18

filetype plugin indent on

set formatprg=perl\ -MText::Autoformat\ -e'autoformat'
set formatoptions=qro


au BufNewFile         *            silent! 0r ~/etc/vim/templates/template.%:e
au BufRead            *            call SetCursorPosition()
au BufNewFile         *.txt        set ft=_txt
au BufRead,BufNewFile *.css        set sw=2
au BufRead,BufNewFile *.go         set ft=go
au BufRead,BufNewFile *.htm        set sw=1
au BufRead,BufNewFile *.html       set sw=1
au BufRead,BufNewFile *.markdown   set ft=md | normal gg
au BufRead,BufNewFile *.md         set ft=md | normal gg
au BufRead,BufNewFile *.mkd        set ft=md | normal gg
au BufRead,BufNewFile *.xml        set sw=1
au BufWritePost       *.{sh,pl}    silent exe
au FileType           perl         set makeprg=perl\ -c\ %\ $*
au FileType           perl         setlocal errorformat=%f:%l:%m
au FileType           perl         setlocal keywordprg=perldoc\ -f
au FileType           pl,pm,t      set ft=perl
au filetype           git,*commit* call ToggleSpell()
au filetype           help         call Filetype_help()

au BufRead,BufNewFile ~/etc/zsh/01-colors.zsh set syntax=

let g:extradite_width              = 40
let g:VimrexFileDir                = expand("~/") . 'var/vim/'
let g:netrw_http_cmd               = 'w3m'
let g:netrw_http_xcmd              = '-dump >'
let g:perl_compiler_force_warnings = 0
let g:tex_conceal                  = 1
let g:vimrc                        = "/home/scp1/etc/vimrc"
let g:vt_author                    = 'Magnus Woldrich'
let g:vt_email                     = 'm@japh.se'
let g:vt_template_dir_path         = '~/.vim/templates/'
let g:perl_extended_vars           = 1
let g:perl_include_pod             = 1
let g:perl_moose_stuff             = 1
let g:perl_no_scope_in_variables   = 1
let g:perl_no_sync_on_global_var   = 1
let g:perl_no_sync_on_sub          = 1
let g:perl_nofold_packages         = 1
let g:perl_pod_formatting          = 1
let g:perl_pod_spellcheck_headings = 1
let g:perl_string_as_statement     = 1
let g:perl_sync_dist               = 1000
let g:perl_want_scope_in_variables = 1
let g:perlhelp_prog                = '/usr/bin/perldoc'
let g:space_no_jump                = 1
let g:vim_indent_cont              = 2
let g:indent_guides_auto           = 0