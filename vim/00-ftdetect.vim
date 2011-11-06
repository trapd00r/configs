"    File: $HOME/etc/ftdetect.vim
"  Author: Magnus Woldrich <m@japh.se>
" Updated: 2011-11-06 02:33:56

filetype plugin indent on

set formatprg=perl\ -MText::Autoformat\ -e'autoformat'
set formatoptions=qro

"au BufNewFile         *            silent! 0r ~/etc/vim/templates/template.%:e | :19

if &term != 'linux'
  au InsertEnter * :silent !printf '\e]12;\#ffff00\a'
  au InsertLeave * :silent !printf '\e]12;\#ff0000\a'
  au VimLeave    * :silent !printf '\e]12;\#69ff00\a'
endif

au BufNewFile *.pl silent! 0r ~/etc/vim/templates/template.pl   |
  \ call search('APP')  | normal di':startinsert

au BufNewFile *.PL silent! 0r ~/etc/vim/templates/template.PL   |
  \ call search('__PACKAGE__') | exe 'normal dt} ' | startinsert

au BufNewFile *.pm silent! 0r ~/etc/vim/templates/template.pm   |
  \ call cursor(0, 9) | exe 'normal d$A ' | startinsert

au BufNewFile *.t  silent! 0r ~/etc/vim/templates/template.t    |
  \ :6 | exe 'normal o' | startinsert

au BufNewFile *.vim silent! 0r ~/etc/vim/templates/template.vim |

au BufNewFile *.c  silent! 0r ~/etc/vim/templates/template.c    |
  \ :5 | exe 'normal o ' | startinsert 

au BufNewFile *.md,*.markdown silent! 0r ~/etc/vim/templates/template.markdown |
  \ :0 | exe 'normal d$A' | startinsert

au BufNewFile *.bash silent! 0r ~/etc/vim/templates/template.bash

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
au BufRead,BufNewFile *.overtime   set ft=overtime
au BufWritePost       *.{sh,pl}    silent exe
au FileType           perl         set makeprg=perl\ -c\ %\ $*
au FileType           perl         setlocal errorformat=%f:%l:%m
au FileType           perl         setlocal keywordprg=perldoc\ -f
au FileType           pl,pm,t      set ft=perl
au Filetype           git,*commit* call ToggleSpell()
au Filetype           help         call Filetype_Help()

au BufRead,BufNewFile README.{md,markdown,pod} let $BROWSER='firefox'
au BufRead,BufNewFile ~/etc/zsh/01-colors.zsh  set syntax=

let g:VimrexFileDir                = expand("~/") . 'var/vim/'
let g:extradite_width              = 40
let g:indent_guides_auto           = 0
let g:space_no_jump                = 1
let g:xf86conf_xfree86_versio      = 2

" mpd                                                                        {{{
let g:mpd_host                     = '192.168.1.128'
let g:mpd_port                     = 6600
let g:mpc_lyrics_use_cache         = 1
"}}}
" xclipboard.vim                                                             {{{
let g:xclipboard_pipe_path         = '/home/scp1/etc/vim/xclipboard.fifo'
"}}}

" C                                                                          {{{
let c_comment_strings              = 1
let c_gnu                          = 1
let c_space_errors                 = 1
let c_syntax_for_h                 = 1
"}}}
" dircolors                                                                  {{{
let dircolors_is_slackware         = 1
"}}}
" sed                                                                        {{{
let g:highlight_sedtabs            = 1
"}}}
" (ba)?sh                                                                    {{{
let g:readline_has_bash            = 1
let g:sh_fold_enabled              = 4
let g:sh_is_posix                  = 1
let g:sh_maxlines                  = 200
let g:sh_minlines                  = 100
"}}}
" netrw                                                                      {{{
let g:netrw_http_cmd               = 'w3m'
let g:netrw_http_xcmd              = '-dump >'
"}}}
" perl                                                                       {{{
let g:perl_compiler_force_warnings = 0
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
"}}}
" (la)?tex                                                                   {{{
let g:tex_conceal                  = 1
"}}}
" viml                                                                       {{{
let g:vim_indent_cont              = 2
let g:vimsyn_embed                 = 'p'
let g:vimsyn_folding               = 'afp'
"}}}
" lua                                                                        {{{
let lua_version                    = 5
let lua_subversion                 = 0
"}}}

let g:vt_author                    = 'Magnus Woldrich'
let g:vt_email                     = 'm@japh.se'
let g:vt_template_dir_path         = '~/.vim/templates/'
