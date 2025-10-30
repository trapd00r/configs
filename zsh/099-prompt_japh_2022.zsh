## Load version control information
#autoload -Uz vcs_info
#precmd() { vcs_info }
#
### Format the vcs_info_msg_0_ variable
###zstyle ':vcs_info:git:*' formats 'branch %b'
## 
#zstyle ':vcs_info:git*' formats "%{$fg[grey]%}%s %{$reset_color%}%r/%S%{$fg[grey]%} %{$fg[blue]%}%b%{$reset_color%}%m%u%c%{$reset_color%} "
zstyle ':vcs_info:git*' actionformats "%s  %r/%S %b %m%u%c "

##
### Set up the prompt (with git branch name)
setopt PROMPT_SUBST
#PROMPT='%n in ${PWD/#$HOME/~} ${vcs_info_msg_0_} > '

#source ~/etc/zsh/git.zsh


askas_butik_prompt_update() {
    # Use case statement instead of multiple if-elif for better performance
    case "$HOST" in
      fantomen) ASKAS_BUTIK_PROMPT="%F{107}[%F{108}${ASKAS_BUTIK}%F{107}]%f%k" ;;
      endie)    ASKAS_BUTIK_PROMPT="%F{107}[%F{109}${ASKAS_BUTIK}%F{107}]%f%k" ;;
      debbie)   ASKAS_BUTIK_PROMPT="%F{107}[%F{110}${ASKAS_BUTIK}%F{107}]%f%k" ;;
      dockie)   ASKAS_BUTIK_PROMPT="%F{107}[%F{111}${ASKAS_BUTIK}%F{107}]%f%k" ;;
      x1)       ASKAS_BUTIK_PROMPT="%F{107}[%F{208}${ASKAS_BUTIK}%F{107}]%f%k" ;;
      *)        ASKAS_BUTIK_PROMPT="%F{107}[%F{196}${ASKAS_BUTIK}%F{107}]%f%k" ;;
    esac
#  PROMPT=$'%F{240}┌[${ASKAS_BUTIK_PROMPT}%F{220}${vcs_info_msg_0_}%F{240}]%f
#%F{240}└[%F{30}%}%~%F{208}>%F{255} '
  PROMPT=$'%F{240}╔[%F{30}%}%~%F{220}${vcs_info_msg_0_}%F{240}]%f
%F{240}╚${ASKAS_BUTIK_PROMPT}%F{208}>%F{255} '
}
#

#PS2=$' %F{196}%}|>%{$reset_color%} '
