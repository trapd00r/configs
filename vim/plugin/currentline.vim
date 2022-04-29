" Vim global plugin for highlighting the current line
" Maintainer: Magnus Woldrich
"       Date: 2022-04-29

" Highlights the current line.

" Subsequent calls will toggle the highlight:
" - Remove the highlighting if called when the cursor is on an already
"   highlighted line
" - Add new highlighting if called when the cursor is on a
"   non-highlighted line

if exists("current_line")
    finish
endif
let loaded_current_line = 1

" Configure these to your liking
" nnoremap <silent> <leader>hl :call HighlightCurrentLine('♥')<cr>

highlight CurrentLine
  \ term=bolditalic
  \ ctermbg=184 ctermfg=bg cterm=bolditalic
  \ guibg=#1d7d70 guifg=bg gui=bold


function! HighlightCurrentLine(opt)
  if a:opt == 'clear'
    call clearmatches()
    return
  endif

  let current_line = line('.')

  " Check if we have matched previously
  try
    let matches =  getmatches()[0]['pos1']
    catch /E684\|E716/
  endtry

  if exists("matches")
    " Is the match on the current line?
    if matches[0] == current_line
    " Then act as a toggle and clear the match
      call clearmatches()
      return
    else
      " The match is on another line number;
      " clear previous match and add a new one.
      call clearmatches()
      let match = matchaddpos("CurrentLine", [current_line], 1)
    endif
  else
    let match = matchaddpos("CurrentLine", [current_line], 1)
    return
  endif
endfunction
