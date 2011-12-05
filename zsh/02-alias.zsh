if [ -f "$HOME/.ssh/config" ]; then
  for host in $(
    perl -ne 'print "$1\n" if /^Host\s+(.+)$/' $HOME/.ssh/config
  ); do
    alias $host="ssh $host '$@'"
  done
fi

if [ -d "$HOME/dev/PKGBUILDS" ]; then
  alias pkgclean="\
    yes | rm -r $(find $HOME/dev/PKGBUILDS -name 'pkg' \
        && find $HOME/dev/PKGBUILDS -name 'src')       \
  "
fi

alias foo='rm -r /foo'

# lisp                                                                     {{{
alias bigloo='rlwrap bigloo'
alias clisp=' rlwrap clisp'
#}}}

alias ctags='ctags --format=1'
alias which='type -a'

alias 80='perl -e "print q[x] x 80, qq[\n]"'
alias perlu='perl -Mv5.12 -Mutf8 -Mstrict -Mautodie -Mwarnings -Mwarnings=FATAL,utf8 -CSAD -Mopen=:std,:utf8 -Mcharnames=:full -Mfeature=unicode_strings -MEncode=encode,decode -MUnicode::Normalize=NFD,NFC,NFKD,NFKC'

alias swe='translate -from en -to swe'
alias  en='translate -from swe -to en'

alias          np='pimpd2 -i'
alias         psh='pimpd2 -sh'
alias         sdb='pimpd2 --search-db'
alias         spl='pimpd2 --search-playlist'
alias         sar='pimpd2 --search-artist'
alias         sal='pimpd2 --search-album'
alias         set='pimpd2 --search-title'
alias         add='pimpd2 --add'
alias        play='ossmix mplayer 15 || pimpd2 --play'
alias        stop='ossmix mplayer 0  || pimpd2 --kill'
alias        next='pimpd2 --next && pimpd2 -np'
alias        prev='pimpd2 --prev && pimpd2 -np'
alias        crop='pimpd2 --crop'
alias        love='pimpd2 --love'
alias       slove='pimpd2 --slove'
alias      unlove='pimpd2 --unlove'
alias        rand='pimpd2 --randomize'
alias       randa='pimpd2 --random-album 10|pimpd2 --add && pimpd2 -play'
alias        copy='pimpd2 --copy'
alias       copya='pimpd2 --copy-album'
alias       queue='pimpd2 --queue'
alias       songs='pimpd2 --songs'
alias      albums='pimpd2 --albums'
alias   splaylist='pimpd2 --splaylist'
alias   playlists='pimpd2 --playlists'

alias   today="echo *(e:age today now:)|perl -pe 's/ /\n/g'"
alias    hour="echo *(e-age $(date +%H:00) now-)|perl -pe 's/ /\n/g'"
alias     gcc='gcc -ansi -pedantic -Wextra -Wempty-body -Wfloat-equal -Wignored-qualifiers -Wmissing-declarations -Wmissing-parameter-type -Wmissing-prototypes -Wold-style-declaration -Woverride-init -Wsign-compare -Wstrict-prototypes -Wtype-limits -Wuninitialized -fstack-protector-all -D_FORTIFY_SOURCE=2'
alias    gccc='gcc -ansi -pedantic -Wall'
alias csyntax='gcc -fsyntax-only'
alias   editc='vim -X $HOME/.zsh/01-colors.zsh $HOME/dev/File::LsColor/lib/File/LsColor.pm $HOME/dev/LS_COLORS/LS_COLORS'
alias   share='perl $HOME/dev/cpan-mirror-server-http/bin/cpanmirrorhttpd -root . -port 8080 --verbose'
alias     get='woof -u -U -i 0.0.0.0 -p 4040'
alias     put='woof -u -i 0.0.0.0 -p 4040'

alias docupd='scp -P 19216 -r /mnt/Leftover/doc/* scp1@192.168.1.128:http/japh.se/doc'
alias   sshl='sshfs -p 19216 scp1@192.168.1.128:/var/log/lighttpd /mnt/lighttpd'

alias     gs='git status --short -b'
alias     gc='git commit'
alias     gt='git tag|sort --reverse'
alias     gp='git push'
alias    gdd='git diff'
alias     gc='git commit'
alias    glp='gl -p'
alias    gcu='git commit -m "updates"'
alias github='PAGER=cat perl /home/scp1/bin/github'
alias   what="--stat -p --reverse HEAD@{1}.. | perl -pe 's/^(\++.+).*/\e[38;5;34m\e[1m$1\e[m/; s/^(\-+.*)/\e[38;5;196m\e[1m$1\e[m/'"
#alias     gd='PAGER="" git diff $ | skate --language diff -'

alias      cp='cp -v'
alias      mv='mv -v'
alias      rm='rm -v'
alias    grep='grep -Pi --color=auto'
alias   grepp='grep -Pi --color=auto "^|$@"'
alias    rmvi='rm *.sw*'
alias prename='prename -v'

alias      pc='perlcritic'
alias     pod='grep \=pod -A 9999 "$@"'
alias     pdb='perl -d -e 1'
alias   perlf='ack -f --perl'


#alias upstream='cd $HOME/bin/upstream && git-rec -d . -c pull -b master'
alias        r='perl $HOME/dev/App::Rel/rel/'

alias     x='cd $XDG_CONFIG_HOME'
alias     h='cd $HOME/dev/trapd00r.se'
alias    vb='cd $HOME/etc/vim/bundle'
alias tests='cd $HOME/dev/CPANTS'

alias     b='cd $HOME/bin'
alias     c='cd $HOME/etc'
alias     d='cd $HOME/dev'
alias     u='cd $HOME/dev/utils'
alias     g='cd $HOME/bin/upstream'
alias     z='cd $HOME/.zsh'
alias    aa='cd $HOME/dev/App::Autotest'
alias    ap='cd $HOME/dev/App::Pimpd'
alias    pp='cd $HOME/dev/App::Pimpd'
alias   apl='cd $HOME/dev/App::Pimpd_Legacy'
alias     p='cd $HOME/dev/App::Pimpd_Legacy'
alias     q='cd $HOME/dev/pickyfont'
alias    ar='cd $HOME/dev/App::Rel/'
alias   RPD='cd $HOME/dev/App::RPD'
alias    at='cd $HOME/dev/ttycolor'
alias    dm='cd $HOME/dev/Daemon::Mplayer'
alias   flc='cd $HOME/dev/File::LsColor'
alias   tec='cd $HOME/dev/Term::ExtendedColor'
alias   tet='cd $HOME/dev/Term::ExtendedColor::TTY'
alias   tex='cd $HOME/dev/Term::ExtendedColor::Xresources'
alias   mll='cd $HOME/dev/Module::LocalLoad'
alias   mnp='cd $HOME/dev/Mplayer::NowPlaying-CPAN'
alias xxlfd='cd $HOME/dev/Xorg::XLFD'
alias   mp3='cd /mnt/Leftover/TransferMusic'
alias     t='mkdr /tmp/scp1 ; cd /tmp/scp1'
alias    tt='cd $HOME/dev/_upstream'

alias lsusb='lsusb | matchline -random'
alias lspci='lspci | matchline -lspci'

if [ "$TERM" = 'linux' ]; then
  alias  ls=' ls++ -ansi'
else
  alias ls='ls++'
fi

alias lso='\ls | pv -qL 10'
alias lsq='\ls --color=always --time-style=full-iso -AlQ'
alias lsl='\ls --color=auto   --group-directories-first -Ah'
alias lss='\ls --color=auto -1 | grep "(^\w*[^_-])"'
alias ls1='\ls -1'
alias lsa='\ls --color=auto --time-style=full-iso'
alias lsd='/bin/ls -FAv | grep /$ | column'


if [ -d $HOME/bin/cope ]; then
  alias       ps='$HOME/bin/cope/ps'
  alias     nmap='$HOME/bin/cope/nmap'
  alias  netstat='$HOME/bin/cope/netstat'
  alias ifconfig='$HOME/bin/cope/ifconfig'
  alias     free='$HOME/bin/cope/free'
  alias    fdisk='$HOME/bin/cope/fdisk'
  alias       df='$HOME/bin/cope/df'
fi

alias sortbycolumn='sort -n -k3'
alias            R='rehash'
alias           qi='qemu -cdrom iso -boot d hd'
alias           ss='source $XDG_CONFIG_HOME/zsh/zshrc'
alias          npd='srinfo -np'
alias         scat='source-highlight -o STDOUT -f esc -i'

if [ -f '/etc/rc.d/oss' ]; then
  alias        v+='ossmix vmix0.pcm8  -- +2'
  alias        v-='ossmix vmix0.pcm8  -- -2'
  alias       v++='ossmix vmix0.pcm9  -- +2'
  alias       v--='ossmix vmix0.pcm9  -- -2'
  alias      v+++='ossmix vmix0.pcm10 -- +2'
  alias      v+++='ossmix vmix0.pcm10 -- +2'
fi

alias      wmp='wminput -c mplayer&'
alias      win='wminput -c ir_ptr -w -c neverball&'
alias      wir='wminput -c ir_ptr -w -c ir_ptr&'
alias      wim='wminput -c ir_ptr -w -c buttons-mame&'
alias      wig='wminput -c gamepad&'
alias      wit='wminput -c buttons-term&'

alias       fevil='find . -regextype posix-extended -regex'

case $HOST in
  'shiva'*)
    host_res='3360x1050'
    ;;
  'rambo'*)
    host_res='1920x1080'
    ;;
  'india'*)
    host_res='1360x1024'
    ;;
  'n900'*)
    host_res='800x480'
    ;;
  'laleh'*)
    host_res='800x600'
    ;;
  *)
    host_res='undef'
    exit 1
esac

if [ $host_res != 'undef' ]; then
  alias rec="ffmpeg -f x11grab -s $host_res -r 150 -i $DISPLAY -sameq foo.mpg"
fi

# feh[theme][recursive?][slide-delay?]                                       {{{
# theme = [f]ullscreen | [i]ndex | [j]ust | [t]humbnail
# recursive: r for recursive, nothing otherwise
# slide-delay:
#     none   - no slideshow
#     x      - slideshow, seconds will be specified on commandline
#              (like "fehfrx 7 .")

alias feh='feh -FZ --quiet --verbose --action "rm '\'%f\'\"
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

alias     rampeak='dd if=/dev/mem|\cat|strings'
alias  seen_movie='chmod +t,o+w "$@"'
alias mountfixbug='echo 64 > /sys/block/sdn/device/max_sectors && mount -a'

alias        i='echo http://i.japh.se && echo http://i.japh.se|xclip'
alias     japh='echo http://japh.se && echo http://japh.se|xclip'
alias      pst='echo http://p.japh.se && echo http://p.japh.se|xclip'
alias     todo='$HOME/dev/time-spent-in-vim/vim $HOME/doc/TODO'

alias    dmesg='$HOME/dev/Term::ExtendedColor/bin/colored_dmesg|grep -v TCP'
alias  vimtime='/home/scp1/dev/time-spent-in-vim/vim --total'
alias    vimsh='vim -X *.sh'
alias    vimpm='vim -X *.pm'
alias    vimpl='vim -X *.pl'
alias     vimc='vim -X *.{c,h}'
alias      vim='vim -X'
alias     cpan='cpanm'
alias    flash=' clive --stream-exec="mplayer -really-quiet %i" --stream=10'
alias      cat='v'
alias      scx='screen -x'
alias     make='/home/scp1/dev/utils/mymake'
alias     wimp='(wminput -c mplayer&); mplayer'
alias       :q='exit'
alias       :q!='kill -9 $$'
alias      die='kill -9 $$'
alias    urxvt="urxvt -name $HOST $@"
alias     less='vimpager'
alias     wget='wget --no-check-certificate -U=Mozilla'
alias     ptop='watch -n1 ps aux --sort=+%cpu'
alias     tree='tree -dA'
alias      mem='su -c mem'

alias   1='printf "\e]710;%s\007" "9x15bold,xft:Kochi Gothic"'
alias   2='pickyfont -f speedy2'
alias   3='pickyfont -f progsole'
alias  pf='pickyfont ter7'
alias  jj='pickyfont -f terminus2'
alias   j='pickyfont -f terminus1'
alias   k='pickyfont -f proggy1'
alias lll='pickyfont -f profont4'
alias  ll='pickyfont -f profont2'
alias  hh='pickyfont -f fixed7'
alias  kk='pickyfont -f clea3'
alias   f='pickyfont monte1 normal \
            && pickyfont monte2 bold \
            && pickyfont pro1 italic'

alias evil="grep 'sub escape' -A 2 \
  $HOME/dev/App::Pimpd/lib/App/Pimpd/Validate.pm |
  tail -1|perl -pe 's/^\s+\$str =~ //'"

alias gource='gource -1280x720 --max-files 0 --file-idle-time 0 --bloom-multiplier 0.5 --bloom-intensity 0.9 -e 0.7 --background 121212 -o - | ffmpeg -y -b 3000K -r 60 -f image2pipe -vcodec ppm -i - -vcodec libx264 -vpre slow -threads 0 gource.mp4'
alias logstalgia='logstalgia  japh_selected_log -s 5 --output-ppm-stream - |  ffmpeg -y -b 3000K -r 60 -f image2pipe -vcodec ppm -i - -vcodec libx264 -vpre slow -threads 0 logstalgia.mp4'

alias testfetch='sync_cpantesters -a WOLDRICH -d $HOME/dev/CPANTS \
                    && cd $HOME/dev/CPANTS'

alias   iostat='iostat -mtx'
alias     cpuu='ps -eo pcpu,pid,user,args | sort -k 1 -r | head -10'
alias memusage='ps -e -orss=,args= | sort -b -k1,1n|pr -TW$COLUMNS'
alias    shiva='ps -eo pcpu,pid,user,args \
                  | sort -k 1 -r \
                  | head -10 && iostat -mtx && mpstat -P 'ALL' && sar'


alias a='printf "  %s\n  %s\n  %s\n  %s\n" "Magnus Woldrich" "CPAN ID: WOLDRICH" "m@japh.se" "http://japh.se"'
alias trapd00r='printf "\t\033#3trapd00r\n\t\033#4trapd00r\n\tA simple, lightweight Perl hacker\n"'
alias trapd00rc='printf "\t\033#3\e[38;5;25mt\e[38;5;26mr\e[38;5;27ma\e[38;5;31mp\e[38;5;32md\e[38;5;33m0\e[38;5;33m0\e[38;5;37mr\n\t\033#4\e[38;5;133mt\e[38;5;134mr\e[38;5;135ma\e[38;5;139mp\e[38;5;140md\e[38;5;141m00\e[38;5;145mr\n\t\e[38;5;240mA simple, lightweight Perl hacker\n"'
alias reset='printf "\033c\033(K\033[J\033[0m\033[?25h"'
alias dev_null='rm /dev/null; mknod /dev/null c 1 3'


#vim: tw=0 nw ft=sh fdm=marker:

