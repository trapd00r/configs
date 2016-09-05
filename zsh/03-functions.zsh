m() {
  /usr/bin/mplayer -include ${HOME}/etc/mplayer/config -profile sid "$@"
}
ms() {
  /usr/bin/mplayer -shuffle -include ${HOME}/etc/mplayer/config -profile sid "$@"
}
l()         {  vdir  -h --format=across --color -w 100 --sort=time "$@" }
#rmdir()     { find "$@" -type d -empty -print0 | xargs -0 /bin/rm -rv }
df()        { /bin/df -h --total "$@" }
apvlv()     { /usr/bin/apvlv -c $XDG_CONFIG_HOME/apvlvrc "$@" }
neverball() { /usr/bin/neverball --data $XDG_CONFIG_HOME/neverball/ }
scrot()     { /usr/bin/scrot -q 89 "$@" }
tcx()       { /usr/bin/tmux attach || /usr/bin/tmux -f $HOME/etc/tmux.conf }
mutt()      { TERM=xterm-256color /usr/bin/mutt -F /home/scp1/etc/muttrc "$@" }
tig()       { TERM=xterm-256color /usr/bin/tig }
goto()      { [ -d "$1" ] && cd "$1" || cd "$(dirname "$1")"; }
cd()        { builtin cd "$@" && ls }
du1()       { du -h --max-depth=1 "$@" | sort -k 1,1hr -k 2,2f; }
horny()     { feh -FZrD3 /mnt/erotica/{.00-pics,pix}; printf "Done!\n" }
scx()       { TERM=xterm-256color screen -x }
f() {
# --force-aliasing \
  =feh -D2.1 -rZxd -B black -g 1080x1920 -r \
       --action "cp -v '%f' /home/scp1/_; cp -v '%f' /mnt/porn5/_/" \
       --action2 "rm -v '%f'"  "$@"
}
zman() { PAGER="less -g -s '+/^       "$1"'" man zshall }

which() {
  IFS="$(printf '\n\t')"
  printf '\e[?7t'
  builtin which "$@" \
    && builtin type "$@" \
    && whereis "$@" \
    && file $(builtin type "$@" | awk '{print $3}') 2> /dev/null
  printf '\e[?7t'
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

mplayer() {
  /usr/bin/mplayer -include ${HOME}/etc/mplayer/config -profile sid "$@"
}

mplayer_redir() {
  /usr/bin/mplayer \
    -identify \
    -include $XDG_CONFIG_HOME/mplayer/config \
    -profile sid $(absname "$@") | tee $XDG_CONFIG_HOME/mplayer/log.txt
    printf "\n\e[38;5;220;1;3m ⚡ \e[m\e[38;5;160;1;4mdeleted\e[m\n\n"
  /bin/cat $XDG_CONFIG_HOME/mplayer/log.txt
  echo;echo
  /bin/rm -v $XDG_CONFIG_HOME/mplayer/log.txt
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
commands() {
  echo -n $PATH | xargs -d : -I {} find {} -maxdepth 1 \
       -executable -type f -printf '%P\n' | sort -u
}
# vim: ft=sh:
