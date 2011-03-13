" ==== Search Window Class =========================================== {{{
" Author:  Cornelius (林佑安)
" Version: 0.4

" Autocomplpop Conflict Guard
let g:acpguard_class = { }
let g:acpguard_class.warning_pres_t = '500m'

fun! g:acpguard_class.check()

  " check for autocomplpop.vim
  " we can not check loaded_autocomplpop variable , because we might load
  " window.vim before we load autocomplpop.
  if ( exists('g:AutoComplPop_Behavior') || exists('g:loaded_acp') ) 
      \ && exists("#CursorMovedI")
    " then we should disable it , because the autocmd CursorMoveI conflicts
    
    if ! exists( 'self.warning_show' )
      call s:echo("AutoComplPop Disabled: the cursor moved event of autocomplpop conflicts with me.")
      exec 'sleep ' . self.warning_pres_t
      let  self.warning_show = 1
    endif
    AutoComplPopDisable
    let self.reveal_autocomplpop = 1
  endif

endf

fun! g:acpguard_class.reveal()
  if exists('g:AutoComplPop_Behavior') && exists('reveal_autocomplpop')
    call s:echo("AutoComplPop Enabled.")
    AutoComplPopEnable
    unlet self.reveal_autocomplpop 
  endif
endf

fun! s:echo(msg)
  redraw
  echomsg a:msg
endf

" search window manager
let swindow#class = {
  \'buf_nr' : -1 ,
  \'mode' : 0 , 
  \'predefined_index': [] ,
  \'max_result': 100
  \}
let swindow#class.loaded = 1

let swindow#class.version = 0.4

fun! swindow#class.open(pos,type,size)
  call g:acpguard_class.check()
  call self.split(a:pos,a:type,a:size)
endf

fun! swindow#class.split(position,type,size)
  if ! bufexists( self.buf_nr )
    if a:type == 'split' | let act = 'new' 
    elseif a:type == 'vsplit' | let act = 'vnew'
    else | let act = 'new' | endif

    let self.win_type = a:type

    exec a:position . ' ' . a:size . act
    let self.buf_nr = bufnr('%')

    cal self._init_buffer()
    cal self.init_buffer()
    cal self.init_syntax()
    cal self.init_basic_mapping()
    cal self.init_mapping()

    let self.predefined_index = self.index()
    cal self.update_search()

    cal self.start()
  elseif bufwinnr(self.buf_nr) == -1 
    exec a:position . ' ' . a:size . a:type
    execute self.buf_nr . 'buffer'
    cal self.buffer_reload_init()
  elseif bufwinnr(self.buf_nr) != bufwinnr('%')
    execute bufwinnr(self.buf_nr) . 'wincmd w'
    cal self.buffer_reload_init()
  endif
endf

fun! swindow#class.index()
  return []
endf

fun! swindow#class.update()
  cal self.update_search()
  cal self.update_highlight()
  startinsert
endfunc

fun! swindow#class.update_search()
  let pattern = self.get_pattern()
  let lines = self.filter_result( pattern , self.predefined_index )
  if len(lines) > self.max_result 
    let lines = remove( lines , 0 , self.max_result )
  endif
  cal self.render( lines )
endf

fun! swindow#class.update_highlight()
  let pattern = self.get_pattern()
  if strlen( pattern ) > 0
    exec 'syn clear Search'
    exec 'syn match Search +'. pattern . '+'
  else
    exec 'syn clear Search'
  endif
endf

" start():
" after a buffer is initialized , start() function will be called to
" setup.
fun! swindow#class.start()
  call cursor( 1, 1 )
  startinsert
endf

" buffer_reload_init() 
" will be triggered after search window opened and the
" buffer is loaded back , which doesn't need to initiailize.
fun! swindow#class.buffer_reload_init()   
endf

" _init_buffer() 
" initialize newly created buffer for search window.
fun! swindow#class._init_buffer() 
  setlocal noswapfile  buftype=nofile bufhidden=hide
  setlocal nobuflisted nowrap cursorline nonumber fdc=0
endf

fun! swindow#class.init_buffer()
endf

" init_syntax() 
" setup the syntax for search window buffer
fun! swindow#class.init_syntax() 
endf

" init_mapping() 
" define your mappings for search window buffer
fun! swindow#class.init_mapping() 
endf

" init_base_mapping()
" this defines default set mappings
fun! swindow#class.init_basic_mapping()
  imap <buffer>     <Enter> <ESC>j<Enter>
  imap <buffer>     <C-a>   <Esc>0i
  imap <buffer>     <C-e>   <Esc>A
  imap <buffer>     <C-b>   <Esc>i
  imap <buffer>     <C-f>   <Esc>a
  inoremap <buffer> <C-n> <ESC>j
  nnoremap <buffer> <C-n> j
  nnoremap <buffer> <C-p> k
  nnoremap <buffer> <ESC> <C-W>q
  nnoremap <buffer> q <C-W>q
  nnoremap <buffer> i ggA
endf

fun! swindow#class.filter_render(lines)

endf

" clear current buffer except pattern line
" re-render the result ( lines )
fun! swindow#class.render(lines)

  cal self.filter_render( a:lines )

  let old = getpos('.')
  if line('$') > 2
    silent 2,$delete _
  endif
  let r=join( a:lines , "\n" )
  silent put=r
  cal setpos('.',old)
endf

" override this if your pattern is on different line
fun! swindow#class.get_pattern()
  return getline(1)
endf

" reder_result()
" put list into buffer
fun! swindow#class.filter_result(ptn,list)
  return filter( copy( a:list ) , 'v:val =~ "' . a:ptn . '"' )
endf

fun! swindow#class.close()
  " since we call buffer back , we dont need to remove buffername
  " silent 0f
  call g:acpguard_class.reveal()
  redraw
endf

" ==== Window Manager =========================================== }}}
