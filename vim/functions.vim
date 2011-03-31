" I save all the time ...
"   Error detected while processing function DeleteTrailingWS:
"   line    1:
"   Pattern not found:

"func! DeleteTrailingWS()
"  :%s/\v\s+$//g
"endfunc


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
