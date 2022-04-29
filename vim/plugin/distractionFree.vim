if ! exists('s:distractionSettings')
  let s:distractionSettings = {}
endif

if ! exists('g:distraction_free#toggle_options')
  let g:distraction_free#toggle_options = [
    \ 'cursorline',
    \ 'colorcolumn',
    \ 'cursorcolumn',
    \ 'number',
    \ 'relativenumber',
    \ 'list',
    \ 'ruler',
    \ 'showtabline',
    \ 'laststatus',
    \]
endif

function! s:DoAllWindows(command) abort
  let currwin=winnr()
  let currBuff=bufnr("%")
  let currTab=tabpagenr()
  let curaltwin=winnr('#')
  execute 'bufdo ' . a:command
  execute 'buffer ' . currBuff
  execute 'windo ' . a:command
  execute curaltwin . 'wincmd w'
  execute currwin . 'wincmd w'
  execute 'tabdo ' . a:command
  execute 'tabn ' . currTab
endfunction

function! s:DistractionsOff() abort
  let s:distractionFree = 1
  let s:distractionSettings['gitgutter']  = get(g:, 'gitgutter_enabled', 0)
  let s:distractionSettings['signify']    = exists('b:sy') && b:sy.active
  let s:distractionSettings['limelight']  = exists(':Limelight') && get(g:, 'distraction_free#toggle_limelight', 0)
  let s:distractionSettings['tmux']       = exists('$TMUX') && get(g:, 'distraction_free#toggle_tmux', 0)
  let s:distractionSettings['fullscreen'] = has('fullscreen') && &fullscreen
  let [k, v, z] = [[], [], []]
  for setting in g:distraction_free#toggle_options
    let k = add(k, printf('&%s', setting))
    let v = add(v, printf('s:distractionSettings[%s]', string(setting)))
    let z = add(z, 0)
  endfor
  execute 'let ['.join(v, ', ').'] = ['. join(k, ', ') .']'
  call s:DoAllWindows('let ['. join(k, ', ') .'] = ['. join(z, ', ') .']')
  unlet k v z
  if s:distractionSettings['gitgutter']
    call s:DoAllWindows('GitGutterDisable')
  endif
  if s:distractionSettings['signify']
    call s:DoAllWindows('SignifyToggle')
  endif
  if s:distractionSettings['limelight']
    silent! Limelight
  endif
  if s:distractionSettings['tmux']
    silent! !tmux set -q status off
  endif
  if has('gui_running')
    let s:distractionSettings['guioptions'] = &guioptions
    set guioptions-=T
    set guioptions-=r
    set guioptions-=L
    if has('fullscreen')
      set fullscreen
    endif
  endif
  augroup Distractions
    autocmd!
    autocmd VimLeavePre * | if s:distractionSettings['tmux'] | silent! !tmux set -q status on | endif
  augroup END
  if exists('#User#DistractionsOff')
    doautocmd User DistractionsOff
  endif
endfunction

function! s:DistractionsOn() abort
  let s:distractionFree = 0
  let [k, v] = [[], []]
  for setting in g:distraction_free#toggle_options
    let k = add(k, printf('&%s', setting))
    let v = add(v, printf('s:distractionSettings[%s]', string(setting)))
  endfor
  call s:DoAllWindows('let ['.join(k, ', ').'] = ['. join(v, ', ') .']')
  unlet k v
  if s:distractionSettings['gitgutter']
    call s:DoAllWindows('GitGutterEnable')
  endif
  if s:distractionSettings['signify']
    call s:DoAllWindows('SignifyToggle')
  endif
  if s:distractionSettings['limelight']
    silent! Limelight!
  endif
  if s:distractionSettings['tmux']
    silent! !tmux set -q status on
  endif
  if has('gui_running')
    let &guioptions = s:distractionSettings['guioptions']
    if s:distractionSettings['fullscreen']
      let &fullscreen = s:distractionSettings['fullscreen']
    endif
  endif
  if exists(':AirLineRefresh')
    silent! AirlineRefresh
  elseif exists('#Powerline')
    silent! PowerlineReloadColorscheme
    silent! doautocmd Powerline ColorScheme
  elseif exists('#LightLine')
    silent! call lightline#enable()
  endif
  augroup Distractions
    autocmd!
  augroup END
  if exists('#User#DistractionsOff')
    doautocmd User DistractionsOff
  endif
endfunction

function! s:ToggleDistractions() abort
  if ! exists('s:distractionFree') || !s:distractionFree
    call s:DistractionsOff()
  else
    call s:DistractionsOn()
  endif
  silent! redraw!
endfunction

command! -bar -nargs=0 DistractionsToggle call <SID>ToggleDistractions()
command! -bar -nargs=0 DistractionsOn call <SID>DistractionsOn()
command! -bar -nargs=0 DistractionsOff call <SID>DistractionsOff()
