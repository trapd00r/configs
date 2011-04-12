#!/bin/zsh

for r in $HOME/.zsh/*.zsh; do
  if [[ $DEBUG > 0 ]]; then
    echo "zsh: sourcing $r"
  fi
  source $r
done

source $HOME/.zsh/$ZSH_THEME.theme
source $HOME/.zsh/02-abbrevations.zsh

eval `keychain -q --eval id_dsa`
export TZ='Europe/Stockholm'

compdef _files mkdir
