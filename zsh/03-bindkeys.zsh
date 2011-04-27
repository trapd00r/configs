#!/usr/bin/zsh

bindkey -v
bindkey "^?" backward-delete-char
bindkey "^H" backward-delete-char
bindkey "^[[3~" delete-char
bindkey "^[[1~" beginning-of-line
bindkey "^[[4~" end-of-line
bindkey '^r' history-incremental-search-backward
bindkey "^[[5~" up-line-or-history
bindkey "^[[6~" down-line-or-history
bindkey "^A" beginning-of-line
bindkey "^E" end-of-line
bindkey "^W" backward-delete-word
bindkey "^b" backward-word
bindkey "^f" forward-word
bindkey "^d" delete-word
bindkey "^k" kill-line
bindkey ' ' magic-space
bindkey '^I' complete-word

bindkey -M isearch ' ' self-insert

bindkey -s '^x0' ' &> /dev/null '
bindkey -s '^x1' '  > /dev/null '
bindkey -s '^x2' ' 2> /dev/null '
bindkey -s '^x3' ' 2>&1 '

bindkey -s '^p' 'mpc playlist --format "%file%" | separate | ls_color\n'
bindkey -s '^t' '\\top\n'
bindkey -s '^n' '\\ncmpcpp\n'
bindkey -s '^v' 'vim\n'


# Bind custom defined completers
bindkey "^N"      most-accessed-file
bindkey "^X^A"    all-matches
bindkey "^_^A"    all-matches
bindkey "^X^P"    pids
bindkey "^_^P"    pids
