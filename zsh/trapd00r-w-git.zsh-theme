# Theme with full path names and hostname
# Handy if you work on different servers all the time;
PROMPT='%{$fg[red]%}%n%{$reset_color%}@%{$fg[grey]%}%M:%{$fg[blue]%}%/%{$reset_color%} |$(git_prompt_info)
%{$fg[grey]%}%(!.#.»)%{$reset_color%} '

ZSH_THEME_GIT_PROMPT_PREFIX=" %{$fg[yellow]%}git:("
ZSH_THEME_GIT_PROMPT_SUFFIX=")%{$reset_color%}"
