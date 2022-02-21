" Copyright (c) 2020 Jongwook Choi
"
" MIT License


let s:cpo_save = &cpo
set cpo&vim

" -------------------
" Configs
" -------------------

" keybindings (default)
let s:fzf_ripgrep_keybindings = {}
let s:fzf_ripgrep_keybindings['toggle-preview'] = 'CTRL-/'

let g:fzf_ripgrep_keybindings = extend(
      \ copy(s:fzf_ripgrep_keybindings),
      \ get(g:, 'fzf_ripgrep_keybindings', {})
      \)


" -------------------
" Common & Utilities
" -------------------

" Utility functions brought from @junegunn/fzf.vim {{{
" https://github.com/junegunn/fzf.vim
" Copyright (c) Junegunn Choi, under MIT License
function! s:get_color(attr, ...)
  let gui = has('termguicolors') && &termguicolors
  let fam = gui ? 'gui' : 'cterm'
  let pat = gui ? '^#[a-f0-9]\+' : '^[0-9]\+$'
  for group in a:000
    let code = synIDattr(synIDtrans(hlID(group)), a:attr, fam)
    if code =~? pat
      return code
    endif
  endfor
  return ''
endfunction

let s:ansi = {'black': 30, 'red': 31, 'green': 32, 'yellow': 33, 'blue': 34, 'magenta': 35, 'cyan': 36}

function! s:csi(color, fg)
  let prefix = a:fg ? '38;' : '48;'
  if a:color[0] == '#'
    return prefix.'2;'.join(map([a:color[1:2], a:color[3:4], a:color[5:6]], 'str2nr(v:val, 16)'), ';')
  endif
  return prefix.'5;'.a:color
endfunction

function! s:ansi(str, group, default, ...)
  let fg = s:get_color('fg', a:group)
  let bg = s:get_color('bg', a:group)
  let color = (empty(fg) ? s:ansi[a:default] : s:csi(fg, 1)) .
        \ (empty(bg) ? '' : ';'.s:csi(bg, 0))
  return printf("\x1b[%s%sm%s\x1b[m", color, a:0 ? ';1' : '', a:str)
endfunction

for s:color_name in keys(s:ansi)
  execute "function! s:".s:color_name."(str, ...)\n"
        \ "  return s:ansi(a:str, get(a:, 1, ''), '".s:color_name."')\n"
        \ "endfunction"
endfor
" }}}

function! fzf#vim#ripgrep#warn(msg) abort
  echohl WarningMsg
  echom a:msg
  echohl NONE
endfunction

function! fzf#vim#ripgrep#is_buffer_explorer()
  " returns True if the current buffer is an explorer-type buffer
  " (e.g. NERDTree, coc-explorer) to avoid opening files in the same window.
  if &filetype == 'nerdtree' && bufname('%') == get(t:, 'NERDTreeBufName', '')
    return 1
  elseif &filetype == 'coc-explorer'
    return 1
  endif
  return 0
endfunction
" -------------------
" Core Implementation
" -------------------

" :Rg (non-fuzzy)
" fzf 0.19+ "reload' magic: https://github.com/junegunn/fzf/issues/1750
function! fzf#vim#ripgrep#rg(initial_query, ...) abort
  let l:opts = get(a:, 1, {})
  let l:fullscreen = get(l:opts, 'fullscreen', 0)
  let l:prompt_name = get(l:opts, 'prompt_name', 'Rg')
  let l:path = get(l:opts, 'path', '')

  " Set search path automatically, if nerdtree tree/explorer is shown
  if empty(l:path)
    let l:path = (&filetype == 'nerdtree' ? b:NERDTree.root.path._str() : '')
  endif

  let command_fmt = 'rg --column --line-number --no-heading --color=always --smart-case %s %s || true'
  let l:rg_path_args = !empty(l:path) ? shellescape(l:path) : ''
  let initial_command = printf(command_fmt, shellescape(a:initial_query), l:rg_path_args)
  let reload_command = printf(command_fmt, '{q}', l:rg_path_args)
  let fzf_opts_header = ['--ansi', '--header',
        \ ':: Press '.s:magenta(g:fzf_ripgrep_keybindings['toggle-preview'], 'Special').' to toggle preview, '
        \ . (!empty(a:initial_query) ? s:magenta('CTRL-Q', 'Special').' to switch to quickfix' : '')
        \ .nr2char(10). '   To use fuzy-filtering mode rather than refreshing rg, try '.s:magenta(':RgFzf', 'Special').' instead.'
        \ ]
  let fzf_opts = [
        \ '--phony', '--query', a:initial_query, '--bind', 'change:reload:'.reload_command,
        \ '--prompt', l:prompt_name.'> '] + fzf_opts_header

  if fzf#vim#ripgrep#is_buffer_explorer()
    wincmd w   " we need to move the focus out of the pinned nerdtree buffer or coc-explorer
  endif

  call fzf#vim#grep(initial_command, 1,
        \ l:fullscreen ? fzf#vim#with_preview({'options': fzf_opts}, 'up:60%', g:fzf_ripgrep_keybindings['toggle-preview'])
        \              : fzf#vim#with_preview({'options': fzf_opts}, 'right:50%', g:fzf_ripgrep_keybindings['toggle-preview']),
        \ l:fullscreen)

  " TODO: Need to access user's query (if it has changed) inside the fzf process
  call s:fzfrg_bind_keymappings(a:initial_query, l:path, '')
endfunction


" :RgFzf (rg fuzzy)
function! fzf#vim#ripgrep#rg_fzf(search_pattern, ...) abort
  " search_pattern: query to ripgrep. star(*) must have already been resolved
  let l:opts = get(a:, 1, {})
  let l:fullscreen = get(l:opts, 'fullscreen', 0)
  let l:prompt_name = get(l:opts, 'prompt_name', 'RgFzf')
  let l:prompt_query = get(l:opts, 'prompt_query', a:search_pattern)
  let l:path = get(l:opts, 'path', '')
  let l:rg_additional_arg = get(l:opts, 'rg_additional_arg', '')

  let fzf_opts_prompt = ['--prompt', printf(l:prompt_name.'%s> ', empty(l:prompt_query) ? '' : (' ('.l:prompt_query.')'))]
  let fzf_opts_header = ['--ansi', '--header',
        \ ':: Press '.s:magenta(g:fzf_ripgrep_keybindings['toggle-preview'], 'Special').' to toggle preview, '
        \ . (!empty(a:search_pattern) ? s:magenta('CTRL-Q', 'Special').' to switch to quickfix' : '')
        \ .nr2char(10). '   To refresh ripgrep results rather than fuzzy-filtering, try '.s:magenta(':Rg', 'Special').' instead.'
        \ ]
  let fzf_opts_contentsonly = ['--delimiter', ':', '--nth', '4..']   " fzf.vim#346
  let fzf_opts = fzf_opts_prompt + fzf_opts_header + fzf_opts_contentsonly

  " Set search path automatically, if nerdtree tree/explorer is shown
  if empty(l:path)
    let l:path = (&filetype == 'nerdtree' ? b:NERDTree.root.path._str() : '')
  endif
  let l:rg_path_args = !empty(l:path) ? shellescape(l:path) : ''

  if fzf#vim#ripgrep#is_buffer_explorer()
    wincmd w   " we need to move the focus out of the pinned nerdtree buffer or coc-explorer
  endif

  " Invoke ripgrep through fzf
  " TODO: pipe post-processor
  let rg_command = 'rg --column --line-number --no-heading --color=always --smart-case '.l:rg_additional_arg.' '.shellescape(a:search_pattern).' '.l:rg_path_args
  call fzf#vim#grep(rg_command, 1,
        \ l:fullscreen ? fzf#vim#with_preview({'options': fzf_opts}, 'up:60%', g:fzf_ripgrep_keybindings['toggle-preview'])
        \              : fzf#vim#with_preview({'options': fzf_opts}, 'right:50%', g:fzf_ripgrep_keybindings['toggle-preview']),
        \ l:fullscreen)
  call s:fzfrg_bind_keymappings(a:search_pattern, l:path, l:rg_additional_arg)
endfunction


function! s:fzfrg_bind_keymappings(query, path, rg_options) abort
  " additional keymappings on the fzf window (e.g. move to quickfix)
  " Assumes: the current buffer is a FZF window (need to store argument into b: vars for tmap)
  " Args:
  " - query: the rg pattern string (will be escaped inside)
  " - path: the path (directory) to search (will be escaped inside)
  " - rg_options: additional flags passed to rg (passed to shell as-is)
  let b:FzfRg_last_query = a:query
  let b:FzfRg_last_path = a:path
  let b:FzfRg_last_options = a:rg_options
  if !empty(b:FzfRg_last_query)
    " CTRL-Q (unless query is empty) -> call rg again into the quickfix
    tnoremap <silent> <buffer> <C-q>    <C-\><C-n>:call timer_start(0,
          \ fzf#vim#ripgrep#_bind_agcall(b:FzfRg_last_query, b:FzfRg_last_path, b:FzfRg_last_options))<CR>:q<CR>
  endif
endfunction

function! fzf#vim#ripgrep#_bind_agcall(query, path, rg_options) abort
  " Make a lambda function callable by timer_start, binding `query` and `options`.
  let l:rg_path_args = !empty(a:path) ? shellescape(a:path) : ''
  return { -> ag#Ag('grep!', "--smart-case " . a:rg_options . " " . shellescape(a:query) . " " . l:rg_path_args) }
endfunction


" :RgDefFzf
function! fzf#vim#ripgrep#rgdef_fzf(query, ...) abort
  let l:opts = get(a:, '1', {})
  let l:fullscreen = get(l:opts, 'fullscreen', 0)
  let l:path = get(l:opts, 'path', '')  " TODO can we just pass through opts dict?
  " TODO: currently, only python is supported.
  let rgdef_type = '--type "py"'
  let rgdef_prefix = '^\s*(def|class)'
  let rgdef_pattern = rgdef_prefix.' \w*'.a:query.'\w*'

  " if the query itself starts with prefix patterns, let itself be the regex pattern
  if a:query =~ ('\v'.rgdef_prefix.'($|\s+)')
    let rgdef_pattern = '^\s*'.a:query
  endif

  return fzf#vim#ripgrep#rg_fzf(rgdef_pattern, {
        \ 'fullscreen': l:fullscreen,
        \ 'prompt_name': 'RgDefFzf', 'prompt_query': a:query,
        \ 'path': l:path,
        \ 'rg_additional_arg': rgdef_type })
endfunction


" ------------------------------------------------------------------
let &cpo = s:cpo_save
unlet s:cpo_save
