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

ASKAS_BUTIK_PROMPT=${ASKAS_BUTIK}

askas_butik_prompt_update() {
	if [[ $ASKAS_BUTIK = 'magnusw1' ]]; then
	  ASKAS_BUTIK_PROMPT="%F{240}[%F{107}${ASKAS_BUTIK}%F{240}]%f%k"
	else
	  ASKAS_BUTIK_PROMPT="%F{160}[%F{196}${ASKAS_BUTIK}%F{160}]%f%k"
	fi
#  PROMPT=$'%F{240}┌[${ASKAS_BUTIK_PROMPT}%F{220}${vcs_info_msg_0_}%F{240}]%f
#%F{240}└[%F{30}%}%~%F{208}>%F{255} '
  PROMPT=$'%F{240}┌[%F{30}%}%~%F{220}${vcs_info_msg_0_}%F{240}]%f
%F{240}└${ASKAS_BUTIK_PROMPT}%F{208}>%F{255} '
}
#

#PS2=$' %F{196}%}|>%{$reset_color%} '
