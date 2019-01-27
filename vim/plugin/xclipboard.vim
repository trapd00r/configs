" xclipboard.vim
" Author:         Magnus Woldrich <m@japh.se>
" Version:        0.02

if(exists("g:loaded_xclipboard"))
  finish
endif

let g:loaded_xclipboard = 1

if(filewritable(g:xclipboard_pipe_path) != 1) 
  let g:xclipboard_pipe_path = expand('~/.vim/xclipboard.fifo')
endif

if filewritable( xclipboard_pipe_path ) != 1
  echo xclipboard_pipe_path . ' is not writeable'
  echo 'set g:xclipboard_pipe_path or mkfifo ' . xclipboard_pipe_path
  finish
endif

" Write buffer to fifo
nnoremap <leader>W  :exec ':w>> '  . eval(string(  xclipboard_pipe_path ))<CR>
" Write the current line to fifo
nnoremap <leader>w  :exec ':.w>> ' . eval(string(  xclipboard_pipe_path ))<CR>

"vnoremap <leader>w  :exec ":'<,'>w>> " . eval(string(  xclipboard_pipe_path ))<CR>
