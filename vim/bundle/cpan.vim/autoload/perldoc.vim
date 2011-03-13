" &&&& Perldoc Window &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&"
"=VERSION 1.1.
"
let s:perldoc_window = { 'width':50 , 'height': 82 }
let s:perldoc_window.version = 1.1


fun! s:perldoc_window.gen_text(name,param)
  " XXX: use system instead..
  exec 'r !perldoc -tT ' . a:param . ' ' . a:name
endf

fun! s:perldoc_window.buffer_init()
  setlocal modifiable noswapfile nobuflisted
  setlocal buftype=nofile bufhidden=hide fdc=0
  setlocal nowrap cursorline nonumber
  setfiletype perldoc
endf

fun! s:perldoc_window.buffer_name(name)
  exec 'silent file Perldoc-' . a:name
endf

fun! s:perldoc_window.syntax_init()
  syn match HEADER +^\w.*$+
  syn match STRING +".\{-}"+
  syn match STRING2 +'.\{-}'+
  hi link HEADER Identifier
  hi link STRING Comment
  hi link STRING2 Comment
endf

fun! s:perldoc_window.open_tab(name,param,stay)

  tabnew
  let bname = 'Perldoc-' . a:name
  let b = bufnr( bname )
  if b != -1 
    exec b . 'buf'
    call cursor(1,1)
    return
  endif

  cal self.buffer_init()
  cal self.buffer_name(a:name)
  cal self.gen_text(a:name,a:param)
  cal self.syntax_init()
  setlocal nomodifiable
  call cursor(1,1)
  autocmd BufWinLeave <buffer> call g:perldoc.close_tab()
  nmap <buffer> <ESC> <C-W>q

  if a:stay
    exec 'tabnext ' .  (tabpagenr() - 1)
  endif
endf

fun! s:perldoc_window.open(name,param)
  " XXX: save size for each window
  " save window size
  let self.previous_height = winheight('%')
  let self.previous_width  = winwidth('%')

  vnew
  let bname = 'Perldoc-' . a:name
  let b = bufnr( bname )
  if b != -1 
    exec b . 'buf'
    call cursor(1,1)
    return
  endif


  cal self.buffer_init()
  cal self.buffer_name(a:name)
  cal self.gen_text(a:name,a:param)
  cal self.syntax_init()

  setlocal nomodifiable
  call cursor(1,1)
  exec 'resize ' . self.width
  exec 'vertical resize ' . self.height
  autocmd BufWinLeave <buffer> call g:perldoc.close()
  nmap <buffer> <ESC> <C-W>q
endf

fun! s:perldoc_window.close_tab()
  redraw
  bw
endf

fun! s:perldoc_window.close()
  bw
  exec 'vertical resize ' . self.previous_width
  exec 'resize ' . self.previous_height
  redraw
endf

fun! perldoc#load()
  if ! exists('g:perldoc')
    let g:perldoc = copy(s:perldoc_window)
  endif
endf
