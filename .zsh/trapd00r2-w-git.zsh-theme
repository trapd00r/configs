autoload -U add-zsh-hook
autoload -Uz vcs_info

zstyle ':vcs_info:*' actionformats \
    '%F{5}(%f%s%F{5})%F{3}-%F{5}[%F{2}%b%F{3}|%F{1}%a%F{5}]%f '
zstyle ':vcs_info:*' formats \
    '%F{10}%s%F{7}:%F{10}(%F{12}%b%F{10})%f '
zstyle ':vcs_info:(sv[nk]|bzr):*' branchformat '%b%F{1}:%F{3}%r'
zstyle ':vcs_info:*' enable git

add-zsh-hook precmd prompt_jnrowe_precmd

prompt_jnrowe_precmd () {
    vcs_info

    if [ "${vcs_info_msg_0_}" = "" ]; then
        #dir_status="|%F{3}%n%F{7}@%F{3}%m%F{7}:%F{9}%l%f"
        dir_status="%F{1}%n%F{7}@%F{9}%m%F{7}:%F{12}%/"
        
        PROMPT='%{$fg_bold[green]%}%p%{$reset_color%}${vcs_info_msg_0_}${dir_status} ${ret_status}%{$reset_color%}
> '
    elif [[ $(git diff --cached --name-status 2>/dev/null ) != "" ]]; then
        dir_status="%F{1}%n%F{7}@%F{9}%m%F{7}:%F{12}%/ | %F{1}>%f"
    elif [[ $(git diff --name-status 2>/dev/null ) != "" ]]; then
        dir_status="%F{1}%n%F{7}@%F{9}%m%F{7}:%F{12}%/"
        PROMPT='%{$fg_bold[green]%}%p%{$reset_color%}${dir_status} ${ret_status}
${vcs_info_msg_0_}%{$reset_color%}
> '
    else
        dir_status="%F{2}▶%f"
    fi
}

local ret_status="%(?:%{$fg_bold[grey]%}OK:%{$fg_bold[green]%}:%s%?)"

#PROMPT='${ret_status}%{$fg_bold[green]%}%p %{$reset_color%} ${vcs_info_msg_0_}${dir_status}%{$reset_color%}
#> '

#  vim: set ft=zsh ts=4 sw=4 et:
