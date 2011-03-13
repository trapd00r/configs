" cpan.vim
" vim:fdm=marker:et:sw=2:
" Vim plugin for perl hackers {{{
"
"
" &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& {{{
"
" This file is free software; you can redistribute it and/or modify it under
" the terms of the GNU General Public License as published by the Free
" Software Foundation; either version 2, or (at your option) any later
" version.
" 
" This file is distributed in the hope that it will be useful, but WITHOUT ANY
" WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
" FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
" details.
" 
" You should have received a copy of the GNU General Public License along with
" GNU Emacs; see the file COPYING.  If not, write to the Free Software
" Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,
" USA.
"
" &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& }}}
" Author: Cornelius <cornelius.howl@DELETE-ME.gmail.com>
" Version: 2.21
" Site: http://oulixe.us/
" Date: Sun Sep 19 10:47:15 2009
" Screencast:  http://www.youtube.com/watch?v=erF0NWUIbr4  <cpan.vim>
"
" Common Functions {{{

fun! s:get_perllib_path()
  if &filetype && &filetype == 'perl'
    let l:path = &path
    if strlen(l:path) > 1 
      return split( l:path , ',')
    endif
  else
    return split( system('perl -e ''print join "\n",@INC''') , "\n" ) 
  endif
endf

fun! s:defopt(opt,value)
  if !exists( '{a:opt}' )
    let {a:opt} = a:value
  endif
endf

fun! s:echo(msg)
  redraw
  echo a:msg
endf

" expiry by min
fu! s:is_expired(file,expiry)
  let lt = localtime( )
  let ft = getftime( expand( a:file ) )
  let dist = lt - ft
  return dist > a:expiry * 60 
endf

"  }}}
" Internal Configs {{{
let g:pkg_token_pattern = '\w[a-zA-Z0-9:_]\+'
let g:cpan_mod_cachef = expand('~/.vim-cpan-module-cache')
let g:cpan_ins_mod_cachef = expand('~/.vim-cpan-installed-module-cache')
let g:cpan_cache_expiry = 60 * 24 * 20
" }}}
" Module Functions {{{

fun! s:getModulePath(mod)
  let paths = s:get_perllib_path()
  let fname = s:translate_module_name( a:mod )
  call insert(paths,'lib/')
  for p in paths
    let fullpath = p . '/' . fname
    if filereadable( fullpath ) 
      return fullpath
    endif
  endfor
  return 
endf


" fetch source list from remote
fun! CPANSourceLists()
  let paths = [ 
        \expand('~/.cpanplus/02packages.details.txt.gz'),
        \expand('~/.cpan/sources/modules/02packages.details.txt.gz')
        \]
  if exists('g:cpan_user_defined_sources')
    call extend( paths , g:cpan_user_defined_sources )
  endif

  for f in paths 
    if filereadable( f ) 
      return f
    endif
  endfor

  " not found
  cal s:echo("CPAN source list not found.")
  let f = expand('~/.cpan/sources/modules/02packages.details.txt.gz')
  " XXX: refactor me !!
  if ! isdirectory( expand('~/.cpan') )
    cal mkdir( expand('~/.cpan') )
  endif

  if ! isdirectory( expand('~/.cpan/sources') )
    cal mkdir( expand('~/.cpan/sources') )
  endif

  if ! isdirectory( expand('~/.cpan/sources/modules') )
    cal mkdir( expand('~/.cpan/sources/modules') )
  endif

  cal s:echo("Downloading CPAN source list.")
  if executable('curl')
    exec '!curl http://cpan.nctu.edu.tw/modules/02packages.details.txt.gz -o ' . f
    return f
  elseif executable('wget')
    exec '!wget http://cpan.nctu.edu.tw/modules/02packages.details.txt.gz -O ' . f
    return f
  endif
  echoerr "You don't have curl or wget to download the package list."
  return
endf


fun! s:tab_open_module_file_in_paths(mod)
  let paths = s:get_perllib_path()
  let fname = s:translate_module_name( a:mod )
  let path = s:getModulePath( a:mod )
  if filereadable( path ) 
    exec 'tabe ' . path
  endif
endf


fun! s:open_module_in_paths(mod)
  let paths = s:get_perllib_path()
  let fname = s:translate_module_name( a:mod )
  call insert(paths, 'lib/' )
  for p in paths 
    let fullpath = p . '/' . fname
    if filereadable( fullpath ) 
      exec 'tabe ' . fullpath
      return
    endif
  endfor
  echomsg "No such module: " . a:mod
endf

fun! s:get_cursor_module_name()
  return matchstr( expand("<cWORD>") , g:pkg_token_pattern )
endf

fun! s:open_module()
  if g:cpan_win_type == 'v'
    vertical resize 98
  else
    resize 60
  endif
  call s:open_module_in_paths( getline('.') )
endf

fun! s:translate_module_name(n)
  return substitute( a:n , '::' , '/' , 'g' ) . '.pm'
endf

fun! CurrentLibModules(force)
  return s:get_path_module_list(getcwd().'/lib',a:force)
endf


fun! CPANParseSourceList(file)
  if executable('zcat')
    let cmd = 'zcat ' . a:file . " | grep -v '^[0-9a-zA-Z-]*: '  | cut -d' ' -f1 > " . g:cpan_mod_cachef
  else
    let cmd = 'cat ' . a:file . " | gunzip | grep -v '^[0-9a-zA-Z-]*: '  | cut -d' ' -f1 > " . g:cpan_mod_cachef
  endif
  echo system( cmd )
  if v:shell_error 
    echoerr v:shell_error
  endif
  let g:cpan_mod_cache = readfile( g:cpan_mod_cachef )
  return g:cpan_mod_cache
endf

fun! CPANModules(force)
  " check runtime cache
  if a:force == 0 && exists('g:cpan_mod_cache')
    retu g:cpan_mod_cache
  endif

  " check file cache if we define a cache filename
  if exists('g:cpan_mod_cachef')
        \ && a:force == 0 
        \ && filereadable(g:cpan_mod_cachef) 
        \ && ! s:is_expired( g:cpan_mod_cachef , g:cpan_cache_expiry )  

      let g:cpan_mod_cache = readfile( g:cpan_mod_cachef )
      return g:cpan_mod_cache
  endif

  let path =  CPANSourceLists()
  if filereadable( path ) 
    return CPANParseSourceList( path )
  else
    echoerr "CPAN sources list not found!"
    return [ ]
  endif
endf

fun! CPANInstalledModules(force)
  " check runtime cache
  if a:force == 0 && exists('g:cpan_ins_mod_cache')
    echomsg 'runtime cache'
    return g:cpan_ins_mod_cache
  endif

  if exists('g:cpan_ins_mod_cachef')
        \ && a:force == 0 
        \ && filereadable( g:cpan_ins_mod_cachef ) 
        \ && ! s:is_expired( g:cpan_ins_mod_cachef , g:cpan_cache_expiry )
    let g:cpan_ins_mod_cache = readfile( g:cpan_ins_mod_cachef )
    return g:cpan_ins_mod_cache
  elseif a:force == 0
    return [ "Please Press Ctrl-R to find installed modules." ]
  endif

  " update cache
  let paths = 'lib ' . join( s:get_perllib_path(),' ')

  cal s:echo("finding packages from @INC... This might take a while. Press Ctrl-C to stop.")
  let out = system( 'find ' . paths . ' -type f -iname "*.pm" ' 
        \ . " | xargs -I{} head {} | egrep -o 'package [_a-zA-Z0-9:]+;' "
        \ . " | perl -pe 's/^package (.*?);/\$1/' "
        \ . " | sort | uniq > " . g:cpan_ins_mod_cachef )
  if v:shell_error 
    echoerr v:shell_error
  endif
  cal s:echo("ready")

  let g:cpan_ins_mod_cache = readfile( g:cpan_ins_mod_cachef )
  return g:cpan_ins_mod_cache
endf



fun! s:get_path_module_list(path,force)
  let cache_name = a:path
  let cache_name =  tolower( substitute( cache_name , '/' , '.' , 'g') )

  let cache_dir = expand('~/.vim/cache/')
  if ! isdirectory( cache_dir )
    cal mkdir( cache_dir )
  endif

  let cpan_path_cachef = cache_dir . cache_name

  " cache for differnet path
  if a:force == 0 && exists('g:cpan_path_cache') && exists('g:cpan_path_cache[ a:path ]') 
    return g:cpan_path_cache[ a:path ]
  endif

  if ! exists('g:cpan_path_cache') 
    let g:cpan_path_cache = { }
  endif

  if a:force == 0 && filereadable( cpan_path_cachef ) && ! s:is_expired( cpan_path_cachef , g:cpan_cache_expiry )
    let g:cpan_path_cache[ a:path ] = readfile( cpan_path_cachef )
    return g:cpan_path_cache[ a:path ]
  endif

  cal s:echo( "finding packages... from " . a:path )

  if exists('use_pcre_grep') 
    call system( 'find '.a:path.' -type f -iname "*.pm" ' 
        \ . " | xargs -I{} grep -Po '(?<=package) [_a-zA-Z0-9:]+' {} "
        \ . " | sort | uniq > " . cpan_path_cachef )
  else
    call system( 'find '.a:path.' -type f -iname "*.pm" ' 
        \ . " | xargs -I{} egrep -o 'package [_a-zA-Z0-9:]+;' {} "
        \ . " | perl -pe 's/^package (.*?);/\$1/' "
        \ . " | sort | uniq > " . cpan_path_cachef )
  endif
  cal s:echo('cached')

  let g:cpan_path_cache[ a:path ] = readfile( cpan_path_cachef )
  return g:cpan_path_cache[ a:path ]
endf





" }}}
" Help Function {{{
fun! s:ShowHelp()
  redraw
  echo ":: CPAN Helper Plugin ::"
  echo "   @       - Query this module on search.cpan.org in browser"
  echo "   p       - Open perldoc in tab"
  echo "   P       - Open perldoc in tab (Background)"
  echo "   I       - Install this module"
  echo "   f       - Install this module by cpanf (CPAN Fresh)"
  echo "   t       - Open this module source file in new tab"
  echo "   R       - To reload installed modules"
  echo "   <ENTER> - Open this module source file in split window"
endf
" }}}

if exists('g:loaded_cpan') || v:version < 701
  "finish
endif

let g:loaded_cpan = 0200  "Version
" }}}
" Configurations "{{{
"}}}

" use Perldoc
cal perldoc#load()


" CPAN Window {{{
let g:CPAN = { }
let g:CPAN.Mode = { 'Installed': 1 , 'CurrentLib': 2 , 'All': 3  }

let s:CPANWindow = copy( swindow#class )
let s:CPANWindow.search_mode = g:CPAN.Mode.Installed

fun! s:CPANWindow.init_buffer()
  setfiletype cpanwindow
  autocmd CursorMovedI <buffer>       call s:CPANWindow.update()
  autocmd BufWinLeave  <buffer>       call s:CPANWindow.close()
  cal self.buffer_name()
endf

fun! s:CPANWindow.index()
  if self.search_mode == g:CPAN.Mode.Installed
    return CPANInstalledModules(0)
  elseif self.search_mode == g:CPAN.Mode.All
    return CPANModules(0)
  elseif self.search_mode == g:CPAN.Mode.CurrentLib
    return CurrentLibModules(0)
  else
    return [ ]
  endif
endf

fun! s:CPANWindow.buffer_reload_init()
  call self.buffer_name()
  startinsert
  call cursor( 1 , col('$')  )
endf

fun! s:CPANWindow.init_mapping()
  " Module action bindings
  imap <silent> <buffer>     <Tab>   <Esc>:SwitchCPANWindowMode<CR>
  nmap <silent> <buffer>     <Tab>   :SwitchCPANWindowMode<CR>
  inoremap <silent> <buffer> @   <ESC>:exec '!' .g:cpan_browser_command . ' http://search.cpan.org/search?query=' . getline('.') . '&mode=all'<CR>
  nnoremap <silent> <buffer> @   <ESC>:exec '!' .g:cpan_browser_command . ' http://search.cpan.org/dist/' . substitute( getline('.') , '::' , '-' , 'g' )<CR>

  nnoremap <silent> <buffer> p   :call  g:perldoc.open_tab(expand('<cWORD>'),'',0)<CR>
  nnoremap <silent> <buffer> P   :call  g:perldoc.open_tab(expand('<cWORD>'),'',1)<CR>
  nnoremap <silent> <buffer> $   :call  g:perldoc.open(expand('<cWORD>'),'')<CR>

  nnoremap <silent> <buffer> !   :exec '!perldoc ' . expand('<cWORD>')<CR>
  nnoremap <silent> <buffer> f   :exec '!sudo cpanf ' . expand('<cWORD>')<CR>

  nnoremap <silent><script><buffer> <Enter> :call <SID>open_module()<CR>
  nnoremap <silent><script><buffer> t       :call <SID>tab_open_module_file_in_paths( getline('.') )<CR>
  nnoremap <silent><script><buffer> I       :exec '!' . g:cpan_cmd . ' ' . getline('.')<CR>

  imap <buffer> <C-r> <ESC>:ReloadInstalledModuleCache<CR>
  nmap <buffer> <C-r> :ReloadInstalledModuleCache<CR>

  nmap <script><silent><buffer> ?    :cal <SID>ShowHelp()<CR>
endf

fun! s:CPANWindow.switch_mode()
  let self.search_mode = self.search_mode + 1
  if self.search_mode == 4
    let self.search_mode = 1
  endif
  call self.buffer_name()

  " update predefined result
  let self.predefined_index = self.index()
  cal self.update()
  cal cursor( 1, col('$') )
endf

fun! s:CPANWindow.buffer_name()
  if self.search_mode == g:CPAN.Mode.Installed 
    silent file CPAN\ (Installed)
  elseif self.search_mode == g:CPAN.Mode.All
    silent file CPAN\ (All)
  elseif self.search_mode == g:CPAN.Mode.CurrentLib
    silent file CPAN\ (CurrentLib)
  endif
endf
" }}}

" }}}
" Commands {{{
com! SwitchCPANWindowMode   :call s:CPANWindow.switch_mode()
com! OpenCPANWindowS        :call s:CPANWindow.open('topleft', 'split',g:cpan_win_height)
com! OpenCPANWindowSV       :call s:CPANWindow.open('topleft', 'vsplit',g:cpan_win_width)

com! ReloadModuleCache              :cal CPANModules(1)
com! ReloadInstalledModuleCache     :cal CPANInstalledModules(1)
com! ReloadCurrentLibModuleCache    :cal CurrentLibModules(1)

" }}}

" Default Option Init {{{
cal s:defopt('g:cpan_win_type','vsplit')
cal s:defopt('g:cpan_win_width',20)
cal s:defopt('g:cpan_win_height',10)
cal s:defopt('g:cpan_mod_cachef', expand('~/.vim-cpan-module-cache'))
cal s:defopt('g:cpan_ins_mod_cachef', expand('~/.vim-cpan-installed-module-cache'))
cal s:defopt('g:cpan_cache_expiry' , 60 * 24 * 20)
cal s:defopt('g:cpan_default_mapping',1)

if ! exists('g:cpan_browser_command')
  if system('uname') =~ 'Darwin' && executable('open')
    let g:cpan_browser_command  = 'open '
  elseif system('uname') =~ 'Linux'
    let g:cpan_browser_command  = 'firefox'
  else  " default
    let g:cpan_browser_command  = 'firefox'
  endif
endif

if ! exists('g:cpan_cmd')
  if executable( expand('~/bin/cpanm') )
    let g:cpan_cmd = 'sudo ' . expand('~/bin/cpanm')
  elseif executable('cpanm')
    let g:cpan_cmd = 'sudo cpanm '
  elseif executable('cpan')
    let g:cpan_cmd = 'sudo cpan'
  elseif executable('cpanp')
    let g:cpan_cmd = 'sudo cpanp i'
  endif
endif

if g:cpan_default_mapping 
  nnoremap <silent> <C-c><C-m>        :OpenCPANWindowS<CR>
  nnoremap <silent> <C-c><C-v>        :OpenCPANWindowSV<CR>
  "inoremap <C-x><C-m>                 <C-R>=CompleteCPANModuleList()<CR>
endif
" }}}
