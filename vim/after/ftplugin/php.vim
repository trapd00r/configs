" setlocal omnifunc=phpactor#Complete
setlocal commentstring=//\ %s
setlocal keywordprg=:terminal++close\ pman
setlocal grepprg=rg\ --vimgrep\ --type\ php
setlocal suffixesadd+=.php

let g:ale_php_phpmd_ruleset='phpmd.xml'
let b:ale_linters = ['phpcs']
let b:ale_fixers = ['phpcbf', 'php_cs_fixer']
let g:PHPProjectBin = getcwd() . '/vendor/bin'
let g:PHPPhanBin = g:PHPProjectBin . '/phan'
let g:PHPPhanClient = g:PHPProjectBin . '/phan_client'


if executable(g:PHPPhanBin)
    " start phan daemon
    let job = job_start(g:PHPPhanBin . ' --daemonize-tcp-port 4846 --quick')
    let &makeprg = g:PHPPhanClient

    if has('nvim')
        setlocal errorformat=%m\ in\ %f\ on\ line\ %l
    else
        setlocal errorformat=%m\ in\ %f\ on\ line\ %l,%-GErrors\ parsing\ %f,%-G
    endif

    function! PHPsynCHK()
        let winnum = winnr()
        silent make --disable-usage-on-error -l %

        " open the error window if it contains an error. Don't limit the number of lines.
        cw

        " return to the window with cursor set on the line of the first error (if any)
        execute winnum . 'wincmd w'
        redraw!
    endfunction
endif



augroup php_setup
    autocmd!
    " update tags in background whenever you write a php file
    autocmd BufWritePost *.php silent! !eval '[ -f ".git/hooks/ctags"  ] && .git/hooks/ctags' &
    if executable(g:PHPPhanBin)
        autocmd BufWritePost *.php call PHPsynCHK()
    endif
augroup END

" Include use statement
nmap <buffer> <Leader>u :PhpactorImportClass<cr>

" Invoke the context menu
nmap <buffer> <F5> :PhpactorContextMenu<cr>

" Goto definition of class or class member under the cursor
" nnoremap <buffer> gd :PhpactorGotoDefinition<cr>
" nnoremap <buffer> gr :PhpactorFindReferences<cr>
" nnoremap <buffer> gi :PhpactorGotoImplementations<cr>
" nnoremap <buffer> K :PhpactorHover<CR>

" Transform the classes in the current file
nmap <buffer> <Leader>tt :PhpactorTransform<CR>

" Extract method from selection
vmap <silent><buffer><Leader>em :<C-U>PhpactorExtractMethod<CR>


