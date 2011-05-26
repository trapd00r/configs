func! Filetype_txt()
  if (&modifiable == 1)
    normal ggVGgqgg0
    set ft=_txt
  endif
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

func! Filetype_help()
  set colorcolumn=0
  set listchars=tab:\ \ 
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
  if &number
    set relativenumber
  else
    set number
  endif
endfunc


func! ToggleSpell()
  if &spell
    set nospell
  else
    set spell
    "hi SpellBad ctermfg=196 ctermbg=234 cterm=bold
    "hi SpellCap ctermfg=160 ctermbg=234 cterm=bold
    "hi SpellRare ctermfg=196 ctermbg=233 cterm=bold
    "hi SpellLocal ctermfg=160 ctermbg=235 cterm=bold
  endif
endfunc
