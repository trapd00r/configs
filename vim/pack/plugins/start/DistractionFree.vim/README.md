# DistractionFree.vim

Distraction-free editing in vim

![screenshot](https://raw.githubusercontent.com/DanielFGray/DistractionFree.vim/master/screencast.gif)

The idea behind this plugin is to disable some of the fancier plugins or settings that might be running in Vim. Maybe you're writing a README file or a blog post and your Vim feels too busy for prose writing. This plugin will save the values of a list of settings and then disable them until you turn them back on.

Drawing inspiration from [Goyo.vim](https://github.com/junegunn/goyo.vim) and [litedfm](https://github.com/bilalq/lite-dfm), I decided to try my hand at making my own but with a user definable list of settings to toggle, and without any of the margins or padding around buffers.

# Installation

Installation is done as usual, with your plugin manager of choice.

If you don't have one already, I suggest [vim-plug](https://github.com/junegunn/vim-plug).

# Customization

This plugin exposes a couple of commands to switch between modes: `:DistractionsOn`, `:DistractionsOff`, and `:DistractionsToggle`. There aren't any mappings defined, you must add your own. I use the following:

``` vim
nnoremap <Leader>df <Esc>:DistractionsToggle<CR>
```

You can define the list of settings you want toggled (shown is the default):

``` vim
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
```

You can enable toggling of Limelight (show in screencast above):

``` vim
let g:distraction_free#toggle_limelight = 1
```

You can also toggle the tmux status bar:

``` vim
let g:distraction_free#toggle_tmux = 1
```

You can also define autocmds to be fired when entering or leaving DistractionFree mode, for example if you wanted to enable `showmode` and `showcmd`:

``` vim
function! s:distractions_off()
  set showmode showcmd
endfunction
function! s:distractions_on()
  set noshowmode noshowcmd
endfunction
autocmd! User DistractionsOn nested call <SID>distractions_on()
autocmd! User DistractionsOff nested call <SID>distractions_off()
```
