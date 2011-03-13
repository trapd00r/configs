

" &&&& Perl Function Search window &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& {{{
"
" Feature
"   built-in function name search
"
let s:FunctionWindow = copy(swindow#class)
let s:FunctionWindow.Modes = { 'BUILTIN':0 , 'PERLINTERNAL':1 }
let s:FunctionWindow.resource = [ ]


fun! s:echo(msg)
  echomsg a:msg 
  redraw
endf

fun! s:FunctionWindow.init_mapping()
  nnoremap <silent> <buffer> <Enter> :cal OpenPerldocWindow( substitute( getline('.') , '^\(\w\+\).*$' , '\1' , '' ) ,'-f')<CR>
endf

fun! s:FunctionWindow.init_syntax()
  syn match PerlFunctionName "^\S\+"
  syn keyword PerlType LIST FILEHANDLE VARIABLE FILEHANDLE EXPR FILENAME DIRHANDLE SOCKET NAME BLOCK NUMBER HASH ARRAY
  hi link PerlFunctionName Identifier
  hi link PerlType Type
endf

fun! s:FunctionWindow.init_buffer()
  setfiletype perlfunctionwindow
  call s:echo( "Loading Function List...")
  let self.resource = readfile( expand('~/.vim/perl/perl-functions') )
  call s:echo( "Ready" )
  cal self.render_result( self.resource )
  autocmd CursorMovedI <buffer> call s:FunctionWindow.update_search()
  silent file Perl\ Builtin\ Functions
endf

fun! s:FunctionWindow.buffer_reload_init()
  call setline(1,'')
  call cursor(1,1)
  startinsert
endf

fun! s:FunctionWindow.update_search()
  let pattern = getline(1)
  let matches = filter( copy( self.resource )  , 'v:val =~ ''' . pattern . '''' )
  let old = getpos('.')
  silent 2,$delete _
  cal self.render_result( matches )
  cal setpos('.',old)
  startinsert
endf

fun! s:FunctionWindow.switch_mode()
  if self.mode == 1 | let self.mode = 0 | else | let self.mode = self.mode + 1 | endif
endf

com! SwitchFunctionWindowMode  :call s:FunctionWindow.switch_mode()
com! OpenFunctionWindow        :call s:FunctionWindow.open('topleft', 'split',10)
nnoremap <C-c><C-f>        :OpenFunctionWindow<CR>
" &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&"}}}
