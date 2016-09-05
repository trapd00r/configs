###< vim: set ft=zsh:fdm=marker:fmr=#<,#>:fdl=0:fen:et:sw=2:fcl=all:
###
#      ${HOME}/etc/zsh/05-appearance.zsh
#   ‗‗‗‗‗‗‗‗‗‗‗‗ ‗‗‗‗‗‗ ‗‗‗‗‗‗‗‗ ‗‗‗‗‗‗‗‗‗‗‗
#         owner  Magnus Woldrich <magnus.woldrich@gmail.com>
#         btime  2009-04-24
#         mtime  2016-09-05 14:56:04
#   permissions  You are free to use things you may find useful here.
#                Would my tweaks happen to give you a raise or fetch you a
#                girlfriend, it goes without saying I'm counting on you
#                to share with me as I've shared with you.
#           git  http://github.com/trapd00r/configs/zsh  (up-to-date)
#           url  http://devel.japh.se/configs/zsh        (sync 1/24h)
#           irc  japh@freenode #zsh #vim #perl
#   ‗‗‗‗‗‗‗‗‗‗‗‗ ‗‗‗‗‗‗‗‗‗‗‗‗‗ ‗‗‗‗ ‗‗‗‗ ‗‗‗‗
###
###>
# ls colors
#autoload colors; colors;
#
#setopt multios
#setopt cdablevarS
#
#if [[ x$WINDOW != x ]]
#then
#    SCREEN_NO="%B$WINDOW%b "
#else
#    SCREEN_NO=""
#fi
#
## Apply theming defaults
#PS1="%n@%m:%~%# "
#
## git theming default: Variables for theming the git info prompt
##export ZSH_THEME_GIT_PROMPT_PREFIX="git->["         # Prefix at the very beginning of the prompt, before the branch name
##export ZSH_THEME_GIT_PROMPT_SUFFIX="]"             # At the very end of the prompt
##export ZSH_THEME_GIT_PROMPT_DIRTY="Œ"              # Text to display if the branch is dirty
##export ZSH_THEME_GIT_PROMPT_CLEAN="afaf"               # Text to display if the branch is clean
#
## Setup the prompt with pretty colors
#setopt prompt_subst
