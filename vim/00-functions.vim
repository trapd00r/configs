"    File: $HOME/etc/functions.vim
"  Author: Magnus Woldrich <m@japh.se>
" Updated: 2012-01-23 09:11:36

func! Vidir_Sanitize(content)
  mark z
  " get rid of annoying swedish characters                                     {{{
  silent! %s/\v[åä]/a/g
  silent! %s/\v[ö]/o/g
  silent! %s/\v[ÅÄ]/A/g
  silent! %s/\v[Ö]/O/g
  "}}}

  silent! %s/\v[ ]/_/g
  silent! %s/,/./g
  silent! %s/\v[;<>*|'&!#)([\]{}]//g
  silent! %s/\v./\L&/g
  silent! %s/\v_+\ze[.]|\zs[.]\ze_+//g
  silent! %s/[$]/S/g
  silent! %s/\v-{2,}/-/g
  silent! %s/\v_-_/-/g
  silent! %s/\v[_]{2,}/_/g
  silent! %s/\v[/_-]@<\=[a-z]/\U&/g
  silent! %s/\v_(Feat|The|It|Of|At)_/\L&/ig
  silent! %s/\v_(Och|N[åa]n)_/\L&/g

  if (a:content == 'music') || (a:content == 'mvid')
    :silent! %s/\v[&]/feat/g
    :silent! %s/\v(_[el]p[_]?)/\U\1/ig
  else
    :silent! %s/\v[&]/and/g
  endif

  'z
  delmark z
endfunc

func! Vidir_SmartUC()
  :s/\<\@<![A-Z]/_&/g
  ":s/\w\@<=\ze\u/_/g
endfunc

func! Markdown_Preview()
  :silent exe '!markdown_preview ' . expand('%:p')
endfunc

func! LS()
  :source /home/scp1/dev/vim-lscolors/plugin/lscolors.vim
endfunc

" :cabbrev that apply only at start of line                                  {{{
" makes Cabbrev('W', 'w') only abbreviate if W is the first char on the line
func! Single_quote(str)
  return "'" . substitute(copy(a:str), "'", "''", 'g') . "'"
endfunc

func! Cabbrev(key, value)
  exe printf('cabbrev <expr> %s (getcmdtype() == ":" && getcmdpos() <= %d) ? %s : %s',
    \ a:key, 1+len(a:key), Single_quote(a:value), Single_quote(a:key))
endfunc
"}}}

func! AddFoldMarkers()
  setlocal virtualedit=all

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

  setlocal formatoptions=
  normal ^77li{{{
  " to close the unexpected fold :) }}}
  normal o
  normal o
  normal o

  put = comment_char . fold_marker_end
  normal kkk
endfunc

func! SortLen()
  %s/\v^/\=len(getline('.')) . '↑'/
  sort n
  %s/\v^\d+↑//
  normal G
endfunc

func! OddEvenHL()
  syn match oddEven /^.*$\n/ nextgroup=oddOdd
  syn match oddOdd  /^.*$\n/ nextgroup=oddEven

  hi oddEven ctermbg=233
  hi oddOdd  ctermbg=234
endfunc

func! InsertDataDumper()
  if (&ft != 'perl') || (&ft != 'pod')
    let ok = confirm("Not a Perl file, proceed anyway?", "&Yes\n&No\n", 2)
    if (ok == 0) || (ok == 2)
      return ''
    endif
  endif

  let l:dd_include   = "use Data::Dumper;\n\n{\n"
  let l:dd_package   = "package Data::Dumper;\n"
  let l:dd_no_strict = "no strict 'vars';\n"
  let l:dd_options_1 = "$Terse = $Indent = $Useqq = $Deparse = $Sortkeys = 1;\n"
  let l:dd_options_2 = "$Quotekeys = 0;\n}\n\n"

  return dd_include . dd_package . dd_no_strict . dd_options_1 . dd_options_2
endfunc

" Show syntax highlighting groups for word under cursor
nmap <C-e> :call SynStack()<CR>
func! SynStack()
  if !exists("*synstack")
    return
  endif
  echo map(synstack(line('.'), col('.')), 'synIDattr(v:val, "name")')
endfunc

func! TitleCaseCenter()
  let word = expand('<cword>')
  s/\w\+/\u&/g
  center
  echo "Word under cursor was " . word
endfunc

func! RemoveTrailingCrap()
  if search('\s\+$', 'n')
    :%s/\s\+$//
  endif
  if search( nr2char(182) . '$' )
    :execute ":%s/" . nr2char(182) . "//"
  endif
endfunc


func! CurDir()
  let curdir = substitute(getcwd(), '/home/scp1/', "~/", "g")
  return curdir
endfunc

func! GotPaste()
  return &paste ? '-[PASTE]-' : ''
endfunc


autocmd BufReadPost * call SetCursorPosition()
func! SetCursorPosition()
  if &filetype !~ 'svn\|commit\c'
    if line("'\"") > 0 && line("'\"") <= line("$")
      exe "normal! g`\""
      normal! zz
    endif
  end
endfunc


func! FileSize()
  let bytes = getfsize(expand("%:p"))
  if bytes <= 0
    return "0"
  endif
  if bytes < 1024
    return bytes
  else
    return (bytes / 1024) . "K"
  endif
endfunc


func! ToggleRelativeAbsoluteNumber()
  exe 'set ' . (&number ? 'relativenumber' : 'number')
endfunc


func! ToggleSpell()
  exe 'set ' . (&spell ? 'nospell' : 'spell')
endfunc
