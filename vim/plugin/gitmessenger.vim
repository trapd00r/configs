if exists('g:loaded_git_messenger')
    finish
endif
let g:loaded_git_messenger = 1

let g:git_messenger_close_on_cursor_moved = get(g:, 'git_messenger_close_on_cursor_moved', v:true)
let g:git_messenger_git_command = get(g:, 'git_messenger_git_command', 'git')
let g:git_messenger_no_default_mappings = get(g:, 'git_messenger_no_default_mappings', v:false)
let g:git_messenger_into_popup_after_show = get(g:, 'git_messenger_into_popup_after_show', v:true)
let g:git_messenger_always_into_popup = get(g:, 'git_messenger_always_into_popup', v:false)
let g:git_messenger_preview_mods = get(g:, 'git_messenger_preview_mods', '')

command! -nargs=0 -bar GitMessenger call gitmessenger#new(expand('%:p'), line('.'), bufnr('%'), {'close_on_cursor_moved' : g:git_messenger_close_on_cursor_moved})
command! -nargs=0 -bar GitMessengerClose call gitmessenger#close_popup(bufnr('%'))

nnoremap <silent><Plug>(git-messenger) :<C-u>GitMessenger<CR>
nnoremap <silent><Plug>(git-messenger-close) :<C-u>call gitmessenger#close_popup(bufnr('%'))<CR>
nnoremap <silent><Plug>(git-messenger-into-popup) :<C-u>call gitmessenger#into_popup(bufnr('%'))<CR>
nnoremap <silent><Plug>(git-messenger-scroll-down-1) :<C-u>call gitmessenger#scroll(bufnr('%'), 'C-e')<CR>
nnoremap <silent><Plug>(git-messenger-scroll-up-1) :<C-u>call gitmessenger#scroll(bufnr('%'), 'C-y')<CR>
nnoremap <silent><Plug>(git-messenger-scroll-down-page) :<C-u>call gitmessenger#scroll(bufnr('%'), 'C-f')<CR>
nnoremap <silent><Plug>(git-messenger-scroll-up-page) :<C-u>call gitmessenger#scroll(bufnr('%'), 'C-b')<CR>
nnoremap <silent><Plug>(git-messenger-scroll-down-half) :<C-u>call gitmessenger#scroll(bufnr('%'), 'C-d')<CR>
nnoremap <silent><Plug>(git-messenger-scroll-up-half) :<C-u>call gitmessenger#scroll(bufnr('%'), 'C-u')<CR>

if !g:git_messenger_no_default_mappings
    nmap <Leader>gm <Plug>(git-messenger)
endif
