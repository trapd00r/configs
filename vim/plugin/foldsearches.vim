" Vim global plugin for folding text around search results
" Last change:  Wed Aug 10 10:06:31 BST 2011
" Maintainer:	Damian Conway
" License:	This file is placed in the public domain.
"
" japh 2022-04-24
" Modifications:
" - added setlocal hlsearch because I want to still see the matches highlighted even after folding
" - adjusted foldtext
" - fixed bug where foldmarkers were deleted after a zz + zz

" If already loaded, we're done...
if exists("loaded_foldsearch")
    finish
endif
let loaded_foldsearch = 1

" Preserve external compatibility options, then enable full vim compatibility...
let s:save_cpo = &cpo
set cpo&vim

" Remember default behaviours...
let s:DEFFOLDMETHOD = &foldmethod
let s:DEFFOLDEXPR   = &foldexpr
let s:DEFFOLDTEXT   = &foldtext
let s:DEFFOLDMARKER = &foldmarker
let s:DEFFOLDLEVEL  = 1000

" This is what the options are changed to...
let s:FOLDEXPR = 'FS_FoldSearchLevel()'
let s:FOLDTEXT = {
\   'visible'   : "'___/ line ' . (v:foldend+1) . ' \\' . repeat('_',80) ",
\   'invisible' : "repeat(' ',80)",
\}

" folding around searches
" nmap <silent> <expr>  AA  FS_ToggleFoldAroundSearch({'context':1})

" folding around use statements
"nmap <silent> <expr>  zu  FS_FoldAroundTarget('^\s*use\s\+\S.*;','context':1)


" Turn the mechanism on and off...
function! FS_ToggleFoldAroundSearch (opts)
    for k in keys(a:)
      echo k
    endfor
    " How much context to show...
    let b:FOLDCONTEXT = get(a:opts, 'context', 1)
    let &foldminlines = b:FOLDCONTEXT

    " Show folds???
    let folds_visible = get(a:opts, 'folds', 'visible')

    " Make sure we can remember the previous setup...
    if !exists('b:foldsearch')
        let b:foldsearch = { 'active' : 0 }
    endif

    " Turn off, if it's on...
    if b:foldsearch.active
        let &foldmethod = get(b:foldsearch, 'prevfoldmethod', s:DEFFOLDMETHOD)
        let &foldtext   = get(b:foldsearch, 'prevfoldtext',   s:DEFFOLDTEXT)
        let &foldlevel  = get(b:foldsearch, 'prevfoldlevel',  s:DEFFOLDLEVEL)
        let &foldexpr   = get(b:foldsearch, 'prevfoldexpr',   s:DEFFOLDEXPR)
        let &foldmarker = get(b:foldsearch, 'prevfoldexpr',   s:DEFFOLDMARKER)

        " Remove autocommands for refolding for each new search...
        augroup FoldSearch
            autocmd!
        augroup END

        " Remember that it's off...
        let b:foldsearch.active = 0

        " Disable special <CR> behaviour...
        nunmap <buffer> <CR>

        " this deletes the foldmarkers, Damian!
"        return 'zE'

    " Turn on, if it's off...
    else

        " Save old settings...
        let b:foldsearch.prevfoldmethod = &foldmethod
        let b:foldsearch.prevfoldexpr   = &foldexpr
        let b:foldsearch.prevfoldtext   = &foldtext
        let b:foldsearch.prevfoldlevel  = &foldlevel
        let b:foldsearch.prevfoldmarker = &foldmarker

        " Set up new behaviour...
        let &foldtext   = s:FOLDTEXT[folds_visible]
        let &foldexpr   = s:FOLDEXPR
        let &foldmethod = 'expr'
        let &foldlevel  = 0


        " Recalculate folding for each new search...
        augroup FoldSearch
            autocmd!
            autocmd CursorMoved  *  let b:inopenfold = foldlevel('.') && foldclosed('.') == -1
            autocmd CursorMoved  *  let &foldexpr  = &foldexpr
            autocmd CursorMoved  *  let &foldlevel = 0
            autocmd CursorMoved  *  call ReopenFold()
            function! ReopenFold ()
                if b:inopenfold
                    normal zo
                endif
            endfunction
        augroup END

        " Enable special <CR> behaviour...
        nnoremap <buffer> <expr> <CR> foldlevel('.') ? 'zA' : ''

        " Remember that it's on...
        let b:foldsearch.active = 1

        " a redraw also clears the hlsearch 
        " and I want to keep them
        return "\<C-L>:setlocal hlsearch\<CR>"
    endif
endfunction

" Search for a particular target and turn search folding on (if not already on)...
function! FS_FoldAroundTarget (target, opts)
    let context       = get(a:opts, 'context', 1        )
    let folds_visible = get(a:opts, 'folds',   'visible')

    " If already in a foldsearch...
    if exists('b:foldsearch')
        if b:foldsearch.active
            " If already folding this pattern...
            if @/ == a:target
                " Toggle off...
"                return ":exec 'normal ' . FS_ToggleFoldAroundSearch({'context':1})\<CR>"
                let ret = ":exec 'normal ' . FS_ToggleFoldAroundSearch({'context':1})\<CR>"
                setlocal hlsearch
                return ret

            " Otherwise stay in foldsearch and switch to target...
            else
                let b:FOLDCONTEXT = get(a:opts, 'context', 1)
                let &foldtext     = s:FOLDTEXT[folds_visible]
                let &foldminlines = 1
                setlocal hlsearch
                return '/' . a:target . "\<CR>"
            endif
        endif
    endif

    " If not already in a foldsearch, search for target then toggle on...
    return '/' . a:target . "\<CR>:exec 'normal ' . FS_ToggleFoldAroundSearch(".string(a:opts).")\<CR>"
endfunction

" Utility function implements folding expression...
function! FS_FoldSearchLevel ()
    " Allow one line of context before and after...
    let startline = v:lnum > 1         ? v:lnum - b:FOLDCONTEXT : v:lnum
    let endline   = v:lnum < line('$') ? v:lnum + b:FOLDCONTEXT : v:lnum
    let context = getline(startline, endline)

    " Simulate smartcase matching...
    let matchpattern = @/
    if &smartcase && matchpattern =~ '\u'
        let matchpattern = '\C'.matchpattern
    endif

    " Line is folded if surrounding context doesn't match last search pattern...
    return match(context, matchpattern) == -1

endfunction

" Restore previous external compatibility options
let &cpo = s:save_cpo
