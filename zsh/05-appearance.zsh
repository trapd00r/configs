# ls colors
autoload colors; colors;

setopt multios
setopt cdablevarS

if [[ x$WINDOW != x ]]
then
    SCREEN_NO="%B$WINDOW%b "
else
    SCREEN_NO=""
fi

# Apply theming defaults
PS1="%n@%m:%~%# "

# git theming default: Variables for theming the git info prompt
#export ZSH_THEME_GIT_PROMPT_PREFIX="git->["         # Prefix at the very beginning of the prompt, before the branch name
#export ZSH_THEME_GIT_PROMPT_SUFFIX="]"             # At the very end of the prompt
#export ZSH_THEME_GIT_PROMPT_DIRTY="Œ"              # Text to display if the branch is dirty
#export ZSH_THEME_GIT_PROMPT_CLEAN="afaf"               # Text to display if the branch is clean

# Setup the prompt with pretty colors
setopt prompt_subst
