function! ToggleRelativeAbsoluteNumber()
  if &number
    set relativenumber
  else
    set number
  endif
endfunction

function! ToggleSpell()
  if &spell
    set nospell
  else
    set spell
    hi SpellBad ctermfg=196 ctermbg=234 cterm=bold
    hi SpellCap ctermfg=160 ctermbg=234 cterm=bold
    hi SpellRare ctermfg=196 ctermbg=233 cterm=bold
    hi SpellLocal ctermfg=160 ctermbg=235 cterm=bold
  endif
endfunction
