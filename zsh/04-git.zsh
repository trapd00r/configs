###< vim: set ft=zsh:fdm=marker:fmr=#<,#>:fdl=0:fen:et:sw=2:fcl=all:
###
#      ${HOME}/etc/zsh/04-git.zsh
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

# get the name of the branch we are on
#zstyle ':vcs_info:*' disable bzr cdv mtn svk tla
#function git_prompt_info() {
#  ref=$(git symbolic-ref HEAD 2> /dev/null) || return
#  echo "$ZSH_THEME_GIT_PROMPT_PREFIX${ref#refs/heads/}$(parse_git_dirty)$ZSH_THEME_GIT_PROMPT_SUFFIX"
#}
#
#parse_git_dirty () {
#  if [[ $((git status 2> /dev/null) | tail -n1) != "nothing to commit (working directory clean)" ]]; then
#    echo "$ZSH_THEME_GIT_PROMPT_DIRTY"
#  else
#    echo "$ZSH_THEME_GIT_PROMPT_CLEAN"
#  fi
#}
#
##
## Will return the current branch name
## Usage example: git pull origin $(current_branch)
##
#function current_branch() {
#  ref=$(git symbolic-ref HEAD 2> /dev/null) || return
#  echo ${ref#refs/heads/}
#}
