# vim: set ft=sh tw=0:
alias  cp='cp -v'
alias  ls='perl =_ls'
alias  mv='mv -v'
alias  rm=rmc
alias vim=wim

if [[ $UID != 0 ]]
then
  if [ -f "$HOME/.ssh/config" ]
  then
    for host in $(
      perl -ne 'print "$1\n" if /\A[Hh]ost\s+(.+)$/' $HOME/.ssh/config
      ); do
      alias $host="ssh $host '$@'"
    done
  fi
  alias cclive='cclive --config-file $XDG_CONFIG_HOME/ccliverc -f best'
  alias bigloo='rlwrap bigloo'
  alias clisp=' rlwrap clisp'
  alias irb='   rlwrap irb-1.8'
fi

alias    cpan='cpanm'

alias  albums='pimpd2 --albums'
alias    copy='pimpd2 --copy'
alias   copya='pimpd2 --copy-album'
alias    love='pimpd2 --love'
alias    play='ossmix mplayer 18 || pimpd2 --play'
alias   slove='pimpd2 --slove'
alias   songs='pimpd2 --songs'
alias    stop='ossmix mplayer 0  || pimpd2 --kill'
alias  unlove='pimpd2 --unlove'

alias     :q!='kill -9 $$'
alias      :q='exit'
alias     die='kill -9 $$'
alias   dmesg='$HOME/dev/Term-ExtendedColor/bin/colored_dmesg|grep -v TCP'
alias      gd='GIT_PAGER="" git diff'
alias     get='woof -u -U -i 0.0.0.0 -p 4040'
alias  github='PAGER=/bin/cat perl /home/scp1/bin/github'
alias      gt='git tag|sort --reverse'
alias prename='prename -v'
alias     put='woof -u -i 0.0.0.0 -p 4040'
alias     scd='screen -d'
alias     scx='screen -x'
alias   share='perl $HOME/dev/cpan-mirror-server-http/bin/cpanmirrorhttpd -root . -port 8080 --verbose'
alias   urxvt="=urxvt -name $HOST $@"
alias    wget='wget --no-check-certificate -U=Mozilla'

alias --  -='builtin cd -'
alias     b='builtin cd $HOME/bin'
alias     c='builtin cd $HOME/etc'
alias     d='builtin cd $HOME/dev'
alias     g='builtin cd $HOME/dev/_upstream'
alias     h='builtin cd $HOME/http/japh.se'
alias     q='builtin cd $HOME/dev/pickyfont'
alias     u='builtin cd $HOME/dev/utils'
alias     x='builtin cd $XDG_CONFIG_HOME'
alias     z='builtin cd $HOME/etc/zsh'
alias    aa='builtin cd $HOME/dev/App-Autotest'
alias    ap='builtin cd $HOME/dev/pimpd2'
alias    at='builtin cd $HOME/dev/ttycolor'
alias    dm='builtin cd $HOME/dev/Daemon-Mplayer'
alias    pp='builtin cd $HOME/dev/pimpd'
alias   RPD='builtin cd $HOME/dev/RPD'
alias   flc='builtin cd $HOME/dev/File-LsColor'
alias   mll='builtin cd $HOME/dev/Module-LocalLoad'
alias   mnp='builtin cd $HOME/dev/Mplayer-NowPlaying-CPAN'
alias   mp3='builtin cd $HOME/toburn'
alias   tec='builtin cd $HOME/dev/Term-ExtendedColor'
alias   tet='builtin cd $HOME/dev/Term-ExtendedColor-TTY'
alias   tex='builtin cd $HOME/dev/Term-ExtendedColor-Xresources'
alias xxlfd='builtin cd $HOME/dev/Xorg-XLFD'
alias     t='mkdr /tmp/scp1; builtin cd /tmp/scp1'

alias lso='=ls | pv -qL 10'
alias lsq='=ls --color=always --time-style=full-iso -AlQ'
alias lsl='=ls --color=auto   --group-directories-first -Ah'
alias lss='=ls --color=auto -1 | grep "(^\w*[^_-])"'
alias ls1='=ls -1'
alias lsa='=ls --color=auto --time-style=full-iso'
alias lsd='/bin/ls -FAv | grep /$ | column'
alias   R='rehash'
alias  qi='qemu -cdrom iso -boot d hd'
alias  ss='source $XDG_CONFIG_HOME/zsh/zshrc'

if [ -f '/etc/rc.d/oss' ]; then
  alias        v+='ossmix vmix0.pcm8   -- +2'
  alias       v++='ossmix vmix0.pcm9   -- +2'
  alias      v+++='ossmix vmix0.pcm10  -- +2'
  alias        v-='ossmix vmix0.pcm8   -- -2'
  alias       v--='ossmix vmix0.pcm9   -- -2'
  alias      v---='ossmix vmix0.pcm10 -- -2'
fi

#if [ $WANNA_PLAY_WITH_WIIMOTE ]
#then
#  alias      wmp='wminput -c mplayer&'
#  alias      win='wminput -c ir_ptr -w -c neverball&'
#  alias      wir='wminput -c ir_ptr -w -c ir_ptr&'
#  alias      wig='wminput -c gamepad&'
#  alias      wit='wminput -c buttons-term&'
#fi

# feh[theme][recursive?][slide-delay?]                                       {{{
# theme = [f]ullscreen | [i]ndex | [j]ust | [t]humbnail
# recursive: r for recursive, nothing otherwise
# slide-delay:
#     none   - no slideshow
#     x      - slideshow, seconds will be specified on commandline
#              (like "fehfrx 7 .")
alias feh='feh -FZ --quiet --verbose -G -d --draw-tinted --action "rm '\'%f\'\"
alias fehe='feh -Texif'
alias feher='feh -Texif --recursive'
alias fehf='feh -Tfs'
alias fehfr='feh -Tfs --recursive'
alias fehi='feh .fehindex.jpg'
alias fehj='feh -Trfs'
alias fehjr='feh -Trfs --recursive'
alias fehjx='feh -Trfs --slideshow-delay'
alias fehfx='feh -Tfs --slideshow-delay'
alias fehjrx='feh -Trfs --recursive --slideshow-delay'
alias fehfrx='feh -Tfs --recursive --slideshow-delay'
alias feht='feh -Tthumb_s'
alias fehtr='feh -Tthumb_s --recursive'
alias fehtb='feh -Tthumb_b'
alias fehtbr='feh -Tthumb_b --recursive'
alias fehtn='feh -Tthumb_s_nt'
alias fehtnr='feh -Tthumb_s_nt --recursive'
alias fehtnb='feh -Tthumb_b_nt'
alias fehtnbr='feh -Tthumb_b_nt --recursive'
#}}}

case $HOSTNAME in
  shiva)
    alias rec="ffmpeg -f x11grab -s 3360x1050 -r 25 -i :0.0+840,4 -sameq"
    ;;
  rambo)
    alias rec="ffmpeg -f x11grab -s 1920x1080 -r 25 -i :0.0 -sameq"
    ;;
  india)
    alias rec="ffmpeg -f x11grab -s 1360x768 -r 25 -i :0.0 -sameq"
    ;;
  n900)
    alias rec="ffmpeg -f x11grab -s 800x480 -r 25 -i :0.0 -sameq"
    ;;
  n950)
    alias rec="ffmpeg -f x11grab -s 854x480 -r 25 -i :0.0 -sameq"
    ;;
  RM680)
    alias rec="ffmpeg -f x11grab -s 854x480 -r 25 -i :0.0 -sameq"
    ;;
  laleh)
    ;;
  *)
    alias rec="ffmpeg -f x11grab -r 25 -i :0.0+840,4 -sameq"
esac

# FIXME such a mess
alias gource='gource -1280x720 --max-files 0 --file-idle-time 0 --bloom-multiplier 0.5 --bloom-intensity 0.9 -e 0.7 --background 121212 -o - | ffmpeg -y -b 3000K -r 60 -f image2pipe -vcodec ppm -i - -vcodec libx264 -vpre slow -threads 0 gource.mp4'
alias logstalgia='logstalgia  japh_selected_log -s 5 --output-ppm-stream - |  ffmpeg -y -b 3000K -r 60 -f image2pipe -vcodec ppm -i - -vcodec libx264 -vpre slow -threads 0 logstalgia.mp4'
alias author='printf "  %s\n  %s\n  %s\n  %s\n" "Magnus Woldrich" "CPAN ID: WOLDRICH" "m@japh.se" "http://japh.se"'
alias osc3= 'printf "\t\033#3trapd00r\n\t\033#4trapd00r\n\tA simple, lightweight Perl hacker\n"'
alias osc3c='printf "\t\033#3\e[38;5;25mt\e[38;5;26mr\e[38;5;27ma\e[38;5;31mp\e[38;5;32md\e[38;5;33m0\e[38;5;33m0\e[38;5;37mr\n\t\033#4\e[38;5;133mt\e[38;5;134mr\e[38;5;135ma\e[38;5;139mp\e[38;5;140md\e[38;5;141m00\e[38;5;145mr\n\t\e[38;5;240mA simple, lightweight Perl hacker\n"'
alias reset='printf "\033c\033(K\033[J\033[0m\033[?25h"'
alias dev_null='rm /dev/null; mknod /dev/null c 1 3'
alias perlu='perl -Mv5.12 -Mutf8 -Mstrict -Mautodie -Mwarnings -Mwarnings=FATAL,utf8 -CSAD -Mopen=:std,:utf8 -Mcharnames=:full -Mfeature=unicode_strings -MEncode=encode,decode -MUnicode-Normalize=NFD,NFC,NFKD,NFKC'
#alias     gcc='gcc -ansi -pedantic -Wextra -Wempty-body -Wfloat-equal -Wignored-qualifiers -Wmissing-declarations -Wmissing-parameter-type -Wmissing-prototypes -Wold-style-declaration -Woverride-init -Wsign-compare -Wstrict-prototypes -Wtype-limits -Wuninitialized -fstack-protector-all -D_FORTIFY_SOURCE=2'
#alias    gccc='gcc -ansi -pedantic -Wall'
