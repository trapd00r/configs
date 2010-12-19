if [ "$(whoami)" = "root" ]; then NCOLOR="red"; else NCOLOR="white"; fi

PROMPT='%{$fg[blue]%}%n%{$fg[white]%}@%{$fg[blue]%}%m%b%{$reset_color%} | %{$fg[yellow]%}%/%b%{$reset_color%} $(git_prompt_info)
%(!.#.») '

# git theming
ZSH_THEME_GIT_PROMPT_PREFIX="%{$fg_bold[blue]%}(%{$fg_no_bold[yellow]%}%B"
ZSH_THEME_GIT_PROMPT_SUFFIX="%b%{$fg_bold[blue]%})%{$reset_color%} "
ZSH_THEME_GIT_PROMPT_CLEAN=""
ZSH_THEME_GIT_PROMPT_DIRTY="%{$fg_bold[red]%}✗"

