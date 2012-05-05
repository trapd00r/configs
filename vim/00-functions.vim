"    File: $HOME/etc/functions.vim
"  Author: Magnus Woldrich <m@japh.se>
" Updated: 2012-01-23 09:11:36

". do stuff with lines matching pattern
" :g/\v^#\w+/let @" .= getline('.')."\n"|d _



" Vidir - sanitize filenames                                                 {{{
fu! Vidir_Sanitize(content)
  mark z

  "silent! %s/\(\_^[ ]*\)\@<![ ]\+/_/g
  "%s/\(\_^\s*\|\_^\s\+\d\+\)\@<!\s/_/g

  silent! %s/\v[åä]/a/g
  silent! %s/\v[ö]/o/g
  silent! %s/\v[ÅÄ]/A/g
  silent! %s/\v[Ö]/O/g
  silent! %s/,/./g
  silent! %s/\v[;<>*|'&!#)([\]{}]//g
  silent! %s/\v_+\ze[.]|\zs[.]\ze_+//g
  silent! %s/[$]/S/g
  silent! %s/\v-{2,}/-/g
  silent! %s/\v_-_/-/g
  silent! %s/\v[_]{2,}/_/g
  silent! %s/\v[/_-]@<\=[a-z]/\U&/g
  silent! %s/\v_(Feat|The|It|Of|At)_/\L&/ig
  silent! %s/\v_(Och|N[åa]n)_/\L&/g

  if (a:content == 'music') || (a:content == 'mvid')
    silent! %s/\v./\L&/g
    silent! %s/\v^\s*[0-9]+\s+\zs\s+/_/g
    silent! %s/\(\_^[ ]*\)\@<![ ]\+/_/g
    :silent! %s/\v[&]/feat/g
    :silent! %s/\v(_[el]p[_]?)/\U\1/ig
    :silent! %s/\v([_-]?cd[sm][_-]?|flac|[_-]demo|vinyl|[_-](web|pcb|osv))/\U\1/ig
  elseif (a:content == 'tv')
    :silent! %s/\v^\s*[0-9]+\s+\zs\s+/./g
    silent! %s/\(\_^[ ]*\)\@<![ ]\+/./g
    silent! %s/\v[.]-[.]/./g
  else
    :silent! %s/\v[&]/and/g
  endif

  'z
  delmark z
endfu
"}}}
" Vidir - sort-of-TitleCase helper                                           {{{
fu! Vidir_SmartUC()
  :s/\<\@<![A-Z]/_&/g
  ":s/\w\@<=\ze\u/_/g
endfu
"}}}
" highlights - hl match under cursor differently from Search                 {{{
"fu! HL_Search_Cword()
"  let s:old_cpo = &cpo
"  set cpo&vim
"
"  if exists('b:search_cword_item')
"    try
"      call matchdelete(b:search_cword_item)
"    catch /^Vim\%((\a\+\)\=:E/ " ignore E802,E803
"    endtry
"  endif
"
"  " :silent !printf '\e]12;\#242424\a'
"  hi Search       ctermfg=233 ctermfg=106 cterm=bold
"  "hi Search       ctermfg=106 ctermbg=233 cterm=bold
"  hi search_cword ctermfg=085 ctermbg=234 cterm=bold
"
"  let b:search_cword_item = matchadd('search_cword', (&ic ? '\c' : '') . '\%#' . @/, 1)
"
"  let &cpo = s:old_cpo
"endfu
"}}}
" highlights - hl every even/odd line                                        {{{
fu! OddEvenHL()
  syn match oddEven /^.*$\n/ nextgroup=oddOdd
  syn match oddOdd  /^.*$\n/ nextgroup=oddEven

  hi oddEven ctermbg=233
  hi oddOdd  ctermbg=234
endfu
"}}}
" cabs - less stupidity                                                      {{{
fu! Single_quote(str)
  return "'" . substitute(copy(a:str), "'", "''", 'g') . "'"
endfu
fu! Cabbrev(key, value)
  exe printf('cabbrev <expr> %s (getcmdtype() == ":" && getcmdpos() <= %d) ? %s : %s',
    \ a:key, 1+len(a:key), Single_quote(a:value), Single_quote(a:key))
endfu
"}}}
" sub - TitleCase word                                                       {{{
fu! TitleCaseCenter()
  let word = expand('<cword>')
  s/\w\+/\u&/g
  center
  echo "Word under cursor was " . word
endfu
"}}}
" sub - trailing trash                                                       {{{
fu! RemoveTrailingCrap()
  if search('\s\+$', 'n')
    :%s/\s\+$//
  endif
  if search( nr2char(182) . '$' )
    :execute ":%s/" . nr2char(182) . "//"
  endif
endfu
"}}}
" toggle number/relativenumber                                               {{{
fu! ToggleRelativeAbsoluteNumber()
  exe 'set ' . (&number ? 'relativenumber' : 'number')
endfu
"}}}
" toggle spell                                                               {{{
fu! ToggleSpell()
  exe 'set ' . (&spell ? 'nospell' : 'spell')
endfu
"}}}
" toggle paste                                                               {{{
fun! TogglePaste()
  exe 'set ' . (&paste ? 'nopaste' : 'paste')
endfun
"}}}
" preview markdown                                                           {{{
fu! Markdown_Preview()
  :silent exe '!markdown_preview ' . expand('%:p')
endfu
"}}}
" ls(1) colors                                                               {{{
fu! LS()
  :source /home/scp1/dev/vim-lscolors/plugin/lscolors.vim
endfu
"}}}
" shorten cwd                                                                {{{
fu! CurDir()
  let curdir = substitute(getcwd(), '/home/scp1/', '~/', '')
  return curdir
endfu
"}}}
" syn group for item under cursor                                            {{{
nmap <C-e> :call SynStack()<CR>
fu! SynStack()
  if !exists("*synstack")
    return
  endif
  echo map(synstack(line('.'), col('.')), 'synIDattr(v:val, "name")')
endfu
"}}}
" folding - add markers                                                      {{{
fu! AddFoldMarkers()
  setl virtualedit=all

  let comment_char = '#'
  if(&ft == 'vim')
    let comment_char = '"'
  elseif(&ft == 'xdefaults')
    let comment_char = '!'
  elseif(&ft == 'lisp')
    let comment_char = ';;'
  endif

  let fold_marker_start = '{{{'
  let fold_marker_end   = '}}}'

  setl formatoptions=
  normal ^77li{{{
  " to close the unexpected fold :) }}}
  normal o
  normal o
  normal o

  put = comment_char . fold_marker_end
  normal kkk
endfu
"}}}
" sort - by line length                                                      {{{
fu! SortLen()
  mark z
  %s/\v^/\=len(getline('.')) . '↑'/
  sort n
  %s/\v^\d+↑//
  normal G
  'z
  delmark z
endfu
"}}}
" viminfo - save cursor position                                             {{{
autocmd BufReadPost * call SetCursorPosition()
fu! SetCursorPosition()
  if &filetype !~ 'svn\|commit\c'
    if line("'\"") > 0 && line("'\"") <= line("$")
      exe "normal! g`\""
      normal! zz
    endif
  end
endfu
"}}}
" % filesize                                                                 {{{
fu! FileSize()
  let bytes = getfsize(expand("%:p"))
  if bytes <= 0
    return "0"
  endif
  if bytes < 1024
    return bytes
  else
    return (bytes / 1024) . "K"
  endif
endfu
"}}}

" vim: set sw=2 et fdm=marker:
