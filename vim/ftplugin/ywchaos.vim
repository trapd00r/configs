" mY oWn Chaos taking.
" Author: Yue Wu <ywupub@gmail.com>
" License: BSD

" Make @ as keyword.
" setlocal iskeyword+=@-@
setlocal fdm=expr
setlocal foldexpr=Ywchaos_FoldExpr(v:lnum)
setlocal foldtext=getline(v:foldstart)
let b:ywchaos_fmd='normal'

setlocal completefunc=Ywchaos_CompleteFunc

silent! call Ywchaos_MakeTagsline()

nmap <silent> <buffer> <C-]> :call Ywchaos_VimgrepTag()<CR>
nmap <silent> <buffer> <Tab> :call Ywchaos_key_AutoTab('normal')<CR>
nmap <silent> <buffer> <Leader>n :call Ywchaos_NewItem()<CR>
nmap <silent> <buffer> <Leader><C-l> :call Ywchaos_MakeTagsline(1)<CR>
nmap <silent> <buffer> <Leader>i :call Ywchaos_Insert()<CR>

imap <silent> <expr> <buffer> <Tab> Ywchaos_key_AutoTab("i")
