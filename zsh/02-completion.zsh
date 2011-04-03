#!/usr/bin/zsh

zstyle ':completion:*'                    list-colors ${(s.:.)LS_COLORS}
zstyle ':completion:*:default'            list-colors ${(s.:.)LS_COLORS}
zstyle ':completion:*'                    menu select=10
zstyle ':completion:*'                    muttrc='$HOME/configs/.muttrc'
zstyle ':completion:*'                    use-perl=1
zstyle ':completion:*'                    my-accounts='m@japh.se'

zstyle ':completion:*'                    squeeze-slashes true
zstyle ':completion:*:cd:*'               ignore-parents parent pwd

zstyle ':completion:*:(all-|)files'       ignored-patterns '*.un~'
zstyle ':completion:*:*:kill:*:processes' list-colors '=(#b) #([0-9]#)*=0=01;31'

zstyle ':completion::complete:*'          use-cache on
zstyle ':completion::complete:*'          cache-path ~/.zsh/cache/$HOST
zstyle ':completion:*:processes'          command 'ps -axw'
zstyle ':completion:*:processes-names'    command 'ps -awxho command'
zstyle ':completion:*'                    matcher-list 'm:{a-z}={A-Z}'
zstyle ':completion:*:functions'          ignored-patterns '_*'
zstyle ':completion:*:scp:*'              tag-order \
zstyle ':completion:*:scp:*'              group-order \
zstyle ':completion:*:ssh:*'              tag-order \
zstyle ':completion:*:ssh:*'              group-order \

zstyle ':completion:*:(ssh|scp):*:my-accounts' users-hosts \
  'scp1@192.168.1.100' 'scp1@brutus.ethup.se' 'trapd00r@90.225.22.81'

go_prefixes=(5 6 8)
for p in $prefixes; do
  compctl -g "*.${p}" ${p}l
  compctl -g "*.go"   ${p}g
done
compctl -g "*.go" gofmt
compctl -g "*.go" gccgo


#zstyle ':completion:*:*:kill:*' menu yes select
#zstyle ':completion:*:kill:*'   force-list always
#zstyle ':completion:*' menu select=10 interactive list-dirs-first


# vim: set ts=2 expandtab sw=2:

