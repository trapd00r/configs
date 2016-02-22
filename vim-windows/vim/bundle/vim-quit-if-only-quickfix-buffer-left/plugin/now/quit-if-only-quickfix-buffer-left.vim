if exists("loaded_plugin_now_quit_if_only_quickfix_buffer_left")
  finish
endif
let loaded_plugin_now_quit_if_only_quickfix_buffer_left = 1

let s:cpo_save = &cpo
set cpo&vim

augroup plugin-now-quit-if-only-quickfix-buffer-left
  autocmd!
  autocmd WinEnter * if winnr('$') == 1 && &buftype == 'quickfix' | quit | endif
augroup end

let &cpo = s:cpo_save
unlet s:cpo_save
