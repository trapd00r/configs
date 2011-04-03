#!/usr/bin/zsh


setopt ALL_EXPORT
#setopt print_exit_value
unsetopt bgnice autoparamslash
setopt extended_history
setopt share_history
setopt notify globdots pushdtohome cdablevars autolist
setopt autocd recexact longlistjobs
setopt autoresume pushdsilent
setopt autopushd pushdminus extendedglob rcquotes mailwarning
setopt AUTO_PARAM_SLASH
setopt AUTO_PARAM_KEYS
setopt COMPLETE_IN_WORD
setopt NUMERIC_GLOB_SORT
setopt RC_QUOTES # allow ' inside ''
setopt INTERACTIVE_COMMENTS
setopt PROMPT_SUBST
setopt OCTAL_ZEROES
#setopt NO_CLOBBER

autoload -U age

autoload -U compinit
compinit


autoload -U url-quote-magic
zle -N self-insert url-quote-magic

unsetopt AUTO_REMOVE_SLASH
unsetopt COMPLETE_ALIASES


# vim: set ts=2 expandtab sw=2:

