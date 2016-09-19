###< vim: set ft=zsh:fdm=marker:fmr=#<,#>:fdl=0:fen:et:sw=2:fcl=all:
###
#      ${HOME}/etc/zsh/03-functions.zsh
#   ‗‗‗‗‗‗‗‗‗‗‗‗ ‗‗‗‗‗‗ ‗‗‗‗‗‗‗‗ ‗‗‗‗‗‗‗‗‗‗‗
#         owner  Magnus Woldrich <magnus.woldrich@gmail.com>
#         btime  2009-04-24
#         mtime  2016-09-05 16:31:24
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

#< basics
cd()        { builtin cd "$@" && ls }
l()         { vdir  -h --format=across --color -w 100 --sort=time "$@" }
df()        { /bin/df -h --total "$@" }
apvlv()     { /usr/bin/apvlv -c $XDG_CONFIG_HOME/apvlvrc "$@" }
neverball() { /usr/bin/neverball --data $XDG_CONFIG_HOME/neverball/ }
scrot()     { cd $HOME/img/_scrots && /usr/bin/scrot -q 100 "$@" }
tcx()       { /usr/bin/tmux attach || /usr/bin/tmux -f $XDG_CONFIG_HOME/etc/tmux.conf }
mutt()      { TERM=xterm-256color muttneo -F $XDG_CONFIG_HOME/muttneorc "$@" }
tig()       { TERM=xterm-256color /usr/bin/tig "$@"}
goto()      { [ -d "$1" ] && cd "$1" || cd "$(dirname "$1")"; }
du1()       { du -h --max-depth=1 "$@" | sort -k 1,1hr -k 2,2f; }
scx()       { TERM=xterm-256color screen -x }
zman()      { PAGER="less -g -s '+/^       "$1"'" man zshall }
#>
#< shell
which() {
  IFS="$(printf '\n\t')"
  printf '\e[?7t'
  builtin which "$@" \
    && builtin type "$@" \
    && whereis "$@" \
    && file $(builtin type "$@" | awk '{print $3}') 2> /dev/null
  printf '\e[?7t'
}
commands() {
  echo -n $PATH | xargs -d : -I {} find {} -maxdepth 1 \
       -executable -type f -printf '%P\n' | sort -u
}
#>

f() {
  =feh -D2.1 -rZxd -B black -g 1080x1920 -r \
       --action "cp -v '%f' /home/scp1/img/_; cp -v '%f'" \
       --action2 "rm -v '%f'"  "$@"
}
vimhelp() {
  /usr/bin/vim -X -c \
    " for k in range(0, 127) | \
        if (k != 104 && k < 106 && k != 58) || k > 109 | \
          silent! exe 'nnoremap ' . nr2char(k) . ' :qa!<CR>' | \
        endif | \
      endfor  | :h $@ | :only \
    "
}
#< mplayer
m() {
  /usr/bin/mplayer -include ${HOME}/etc/mplayer/config -profile sid "$@"
}
ms() {
  /usr/bin/mplayer -shuffle -include ${HOME}/etc/mplayer/config -profile sid "$@"
}
#mplayer() {
#  /usr/bin/mplayer -include ${HOME}/etc/mplayer/config -profile sid "$@"
#}
mplayer() {
  /usr/bin/mplayer \
    -identify \
    -include $XDG_CONFIG_HOME/mplayer/config \
    -profile sid $@
#    -profile sid $(absname "$@") | tee $XDG_CONFIG_HOME/mplayer/log.txt
#    printf "\n\e[38;5;220;1;3m ⚡ \e[m\e[38;5;160;1;4mdeleted\e[m\n\n"
#  /bin/cat $XDG_CONFIG_HOME/mplayer/log.txt
#  echo;echo
#  /bin/rm -v $XDG_CONFIG_HOME/mplayer/log.txt
}
mplayer_pipe() {
  /usr/bin/mplayer \
    -quiet -msglevel all=0 -identify -include $XDG_CONFIG_HOME/mplayer/config \
    -profile $HOST > $XDG_CONFIG_HOME/mplayer/log.txt
  rm -v $XDG_CONFIG_HOME/mplayer/log.txt
}
mplayer_headphones() {
  /usr/bin/mplayer \
    -msgmodule 1 -msgcolor -include $XDG_CONFIG_HOME/mplayer/config \
    -channels 6 -af resample=48000,hrtf "$@"
}
mplayer_6ch_headphones() {
  /usr/bin/mplayer \
    -channels 6 -af resample=48000,hrtf \
    -include $XDG_CONFIG_HOME/mplayer/config "$@"
}
#>
