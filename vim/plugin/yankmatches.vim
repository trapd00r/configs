" Vim global plugin for yanking or deleting all lines with a match
" Maintainer:	Damian Conway
" License:	This file is placed in the public domain.
" Hacker: Magnus Woldrich
"
" MW modifications:
" - fixed so the yanked matches are available both for pasting with p
"   and in the system clipboard
" - added YankedMatches highlight group to visualize what's been yanked
"   use a binding like this to turn it off:
"
" nnoremap <silent> <C-l> :call HLNextOff() <BAR> :nohlsearch <BAR> :hi clear YankedMatches<CR>


if exists("loaded_delete_matches")
    finish
endif
let loaded_delete_matches = 1

" Preserve external compatibility options, then enable full vim compatibility...
let s:save_cpo = &cpo
set cpo&vim


" Originally just:
"       nmap <silent> dm  :g//delete<CR>
" But that doesn't retain all deletes in the nameless register
"
" Then:
"       nmap <silent> dm  :let @a = ""<CR>:g//delete A<CR>
" But that doesn't seem to work :-(
" So:


"====[ Interface ]====================================================
"
" Change these if you want different commands for the specified actions...
"
nmap <silent> <leader>dm  :     call ForAllMatches('delete', {})<CR>
nmap <silent> <leader>DM  :     call ForAllMatches('delete', {'inverse':1})<CR>
nmap <silent> <leader>ym  :     call ForAllMatches('yank',   {})<CR>
nmap <silent> <leader>YM  :     call ForAllMatches('yank',   {'inverse':1})<CR>

vmap <silent> <leader>dm  :<C-U>call ForAllMatches('delete', {'visual':1})<CR>
vmap <silent> <leader>DM  :<C-U>call ForAllMatches('delete', {'visual':1, 'inverse':1})<CR>
vmap <silent> <leader>ym  :<C-U>call ForAllMatches('yank',   {'visual':1})<CR>
vmap <silent> <leader>YM  :<C-U>call ForAllMatches('yank',   {'visual':1, 'inverse':1})<CR>

function! ForAllMatches (command, options)
    " Remember where we parked...
    let orig_pos = getpos('.')

    " Work out the implied range of lines to consider...
    let in_visual = get(a:options, 'visual', 0)
    let start_line = in_visual ? getpos("'<'")[1] : 1
    let end_line   = in_visual ? getpos("'>'")[1] : line('$')

    " Are we inverting the selection???
    let inverted = get(a:options, 'inverse', 0)

    " Are we modifying the buffer???
    let deleting = a:command == 'delete'

    " Honour smartcase (which :lvimgrep doesn't, by default)
    let sensitive = &ignorecase && &smartcase && @/ =~ '\u' ? '\C' : ''

    " Identify the lines to be operated on...
    exec 'silent lvimgrep /' . sensitive . @/ . '/j %'
    let matched_line_nums
    \ = reverse(filter(map(getloclist(0), 'v:val.lnum'), 'start_line <= v:val && v:val <= end_line'))

    " Invert the list of lines, if requested...
    if inverted
        let inverted_line_nums = range(start_line, end_line)
        for line_num in matched_line_nums
            call remove(inverted_line_nums, line_num-1)
        endfor
        let matched_line_nums = reverse(inverted_line_nums)
    endif

    highlight YankedMatches
      \ ctermfg=bg ctermbg=214 cterm=bolditalic
      \ guifg=bg guibg=#ffaf00 gui=none

    " Filter the original lines...
    let yanked = ""
    for line_num in matched_line_nums
        " Remember yanks or deletions...
        let yanked = getline(line_num) . "\n" . yanked


        " Delete buffer lines if necessary...
        if deleting
            exec line_num . 'delete'
        else
          " Highlight the line by number
          silent! call matchaddpos("YankedMatches", [line_num], 1);
        endif
    endfor

    " Make yanked lines available for putting...

    " struggled a lot with getting the yanked matches to the system clipboard
    " (XA_PRIMARY) as well...
    call setreg("*", yanked, 'l' )
    call setreg("+", yanked, 'l' )
    call setreg("",  yanked, 'l' )

    " Return to original position...
    call setpos('.', orig_pos)

    " Report results...
    redraw
    let match_count = len(matched_line_nums)
    if match_count == 0
        unsilent echo 'Nothing to ' . a:command . ' (no matches found)'
    elseif deleting
        unsilent echo match_count . (match_count > 1 ? ' fewer lines' : ' less line')
    else
        unsilent echo match_count . ' line' . (match_count > 1 ? 's' : '') . ' yanked'
    endif
endfunction


