# Path to your oh-my-zsh configuration.
export ZSH=$HOME/.zsh/oh-my-zsh

# Set to the name theme to load.
# Look in ~/.oh-my-zsh/themes/
export ZSH_THEME="u@h_pipe_pwd_git"

# Set to this to use case-sensitive completion
# export CASE_SENSITIVE="true"

# Comment this out to disable weekly auto-update checks
# export DISABLE_AUTO_UPDATE="true"



source $HOME/.zsh/alias.zsh
source $HOME/.zsh/functions.zsh
source $HOME/.zsh/appearance.zsh
source $HOME/.zsh/colors.zsh
source $HOME/.zsh/git.zsh
source $HOME/.zsh/u@h_pipe_pwd_git.zsh-theme

export TERM='rxvt-256color'
export CDPATH='.:~:/mnt'
export PATH=~/bin:/bin:/usr/bin:/sbin:/usr/sbin:/usr/bin/perlbin/site:/usr/bin/perlbin/vendor:/usr/bin/perlbin/core
export MANPATH=$MANPATH:/usr/local/man:/opt/local/share/man
export EDITOR=vim
export PAGER=vimpager
setopt ALL_EXPORT

eval `keychain -q --eval id_dsa`
TZ='Europe/Stockholm'; export TZ
HISTFILE=$HOME/.zsh-history
HISTSIZE=5000
SAVEHIST=1000
setopt extended_history
#setopt share_history
function history_all { history -E 1 }

setopt notify globdots pushdtohome cdablevars autolist
setopt autocd recexact longlistjobs
setopt autoresume histignoredups pushdsilent
setopt autopushd pushdminus extendedglob rcquotes mailwarning
unsetopt bgnice autoparamslash
autoload -U compinit
compinit

# smart urls
autoload -U url-quote-magic
zle -N self-insert url-quote-magic


zstyle ':completion::complete:*' use-cache on
zstyle ':completion::complete:*' cache-path ~/.zsh/cache/$HOST
zstyle ':completion:*' list-colors ${(s.:.)LS_COLORS}
zstyle ':completion:*:processes' command 'ps -axw'
zstyle ':completion:*:processes-names' command 'ps -awxho command'
zstyle ':completion:*:*:kill:*:processes' list-colors '=(#b) #([0-9]#)*=0=01;31'
zstyle ':completion:*' hosts $(awk '/^[^#]/ {print $2 $3" "$4" "$5}' /etc/hosts | grep -v ip6- && grep "^#%" /etc/hosts | awk -F% '{print $2}') 
zstyle ':completion:*' matcher-list 'm:{a-z}={A-Z}'
zstyle ':completion:*:functions' ignored-patterns '_*'
zstyle ':completion:*:scp:*' tag-order \
zstyle ':completion:*:scp:*' group-order \
zstyle ':completion:*:ssh:*' tag-order \
zstyle ':completion:*:ssh:*' group-order \

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
