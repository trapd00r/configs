#!/usr/bin/zsh

#No flow control please.
stty -ixon

unsetopt bgnice
unsetopt autoparamslash
unsetopt auto_remove_slash
unsetopt list_types

setopt all_export
setopt auto_param_keys
setopt auto_param_slash
setopt autocd
setopt autolist
setopt autopushd
setopt autoresume
setopt cdablevars
setopt complete_aliases
setopt complete_in_word
setopt extended_history
setopt extendedglob
setopt globdots
setopt histignorealldups
setopt interactive_comments
setopt kshglob
setopt longlistjobs
setopt mailwarning
setopt nobareglobqual
setopt notify
setopt nullglob
setopt numeric_glob_sort
setopt octal_zeroes
setopt prompt_subst
setopt pushdminus
setopt pushdsilent
setopt pushdtohome
setopt rc_quotes
setopt rcquotes
setopt recexact
setopt share_history

autoload -U age
autoload -U compinit
compinit

# url-quote-magic                                                            {{{
autoload -U url-quote-magic

function _url-quote-magic() {
  url-quote-magic;
  _zsh_highlight-zle-buffer
}
zle -N self-insert _url-quote-magic
zle -C most-accessed-file menu-complete _generic

autoload -U url-quote-magic
zle -N self-insert url-quote-magic
#}}}
# vim: set et sw=2:
