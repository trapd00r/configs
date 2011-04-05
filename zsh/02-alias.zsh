#vim: tw=0 nowrap ts=2 ft=sh:
alias -s {pl,pm,c,cpp,h,sh}='vim'
alias -s {mkv,avi}='mplayer'
alias -s chm='xchm'
alias -s PKGBUILD='vim'

#alias perlbrew='PERLBREW_ROOT="/mnt/Leftover/Perl5" perlbrew'

alias swe='translate -from en -to swe'
alias  en='translate -from swe -to en'

alias          np='pimpd -i'
alias         np2='pimpd2 -i'
alias         psh='pimpd2 -sh'
alias         sdb='pimpd2 --search-db'
alias         spl='pimpd2 --search-playlist'
alias         sar='pimpd2 --search-artist'
alias         sal='pimpd2 --search-album'
alias         set='pimpd2 --search-title'
alias         add='pimpd2 --add'
alias        play='pimpd2 --play'
alias        stop='pimpd2 --kill'
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
alias   editc='vim $HOME/.zsh/colors.zsh $HOME/devel/File::LsColor/lib/File/LsColor.pm'
alias   share='perl $HOME/devel/CPAN::Mirror::Server::HTTP/bin/cpanmirrorhttpd -root . -port 8080 --verbose'
alias     get='woof -u -U -i 0.0.0.0 -p 4040'
alias     put='woof -u -i 0.0.0.0 -p 4040'

alias   ssh='ssh -p 19216'
alias   scp='scp -P 19216'

alias brutus='ssh scp1@brutus.ethup.se'
alias macosx='ssh trapd00r@90.225.22.81'
alias macoss='ssh scp1@industrialrefuge.com'
alias  india='ssh scp1@192.168.1.102 -p 19216'
alias   dvdc='ssh scp1@192.168.1.100 -p 19216'
alias   n900='ssh -p 19216 user@192.168.1.112'

alias   sshl='sshfs -p 19216 scp1@192.168.1.100:/var/log/lighttpd /mnt/lighttpd'

alias     gs='git status --short -b'
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
alias     pod='grep \=pod -C 999999 "$@"'
alias     pdb='perl -d -e 1'
alias   perlf='ack -f --perl'


#alias upstream='cd $HOME/bin/upstream && git-rec -d . -c pull -b master'
alias        r='perl $HOME/devel/App::Rel/rel/'

alias     x='cd $XDG_CONFIG_HOME'
alias     h='cd $HOME/devel/trapd00r.se'
alias    vb='cd $HOME/configs/vim/bundle'
alias tests='cd $HOME/devel/CPANTS'

alias     b='cd $HOME/bin'
alias     c='cd $HOME/configs'
alias     d='cd $HOME/devel'
alias     u='cd $HOME/devel/utils'
alias     g='cd $HOME/bin/upstream'
alias     z='cd $HOME/.zsh'
alias    aa='cd $HOME/devel/App::Autotest'
alias    ap='cd $HOME/devel/App::Pimpd'
alias    pp='cd $HOME/devel/App::Pimpd'
alias   apl='cd $HOME/devel/App::Pimpd_Legacy'
alias     p='cd $HOME/devel/App::Pimpd_Legacy'
alias     q='cd $HOME/devel/App::Pickyfont'
alias   apf='cd $HOME/devel/App::Pickyfont'
alias    ar='cd $HOME/devel/App::Rel/'
alias   RPD='cd $HOME/devel/App::RPD'
alias    at='cd $HOME/devel/App::Ttycolor'
alias    dm='cd $HOME/devel/Daemon::Mplayer'
alias   flc='cd $HOME/devel/File::LsColor'
alias   tec='cd $HOME/devel/Term::ExtendedColor'
alias   tet='cd $HOME/devel/Term::ExtendedColor::TTY'
alias   tex='cd $HOME/devel/Term::ExtendedColor::Xresources'
alias   mll='cd $HOME/devel/Module::LocalLoad'
alias   mnp='cd $HOME/devel/Mplayer::NowPlaying-CPAN'
alias xxlfd='cd $HOME/devel/Xorg::XLFD'
alias   mp3='cd /mnt/Leftover/TransferMusic'
alias     t='mkdr /tmp/scp1 ; cd /tmp/scp1'
alias    tt='cd $HOME/bin/upstream'

alias lsusb='lsusb | matchline -random'
alias lspci='lspci | matchline -lspci'

alias  ls=' ls++'
alias lso='\ls | pv -qL 10'
alias lsq='\ls --color=always --time-style=full-iso -AlQ'
alias lsl='\ls --color=auto   --group-directories-first -Ah'
alias lss='\ls --color=auto -1 | grep "(^\w*[^_-])"'
alias ls1='\ls -1'
alias lsa='\ls --color=auto --time-style=full-iso'
alias lsd='find . -maxdepth 2 -type d | sort|ls_color'


alias       ps='$HOME/bin/cope/ps'
alias     nmap='$HOME/bin/cope/nmap'
alias  netstat='$HOME/bin/cope/netstat'
alias ifconfig='$HOME/bin/cope/ifconfig'
alias     free='$HOME/bin/cope/free'
alias    fdisk='$HOME/bin/cope/fdisk'
alias       df='$HOME/bin/cope/df'

alias sortbycolumn='sort -n -k3'
alias            R='rehash'
alias           qi='qemu -cdrom iso -boot d hd'
alias           ss='source $HOME/configs/.zshrc'
alias          npd='srinfo -np'
alias         scat='source-highlight -o STDOUT -f esc -i'

alias       v+='ossmix vmix0.pcm8 -- +2'
alias       v-='ossmix vmix0.pcm8 -- -2'
alias      v++='ossmix vmix0.pcm9 -- +2'
alias      v--='ossmix vmix0.pcm9 -- -2'

alias      wmp='wminput -c mplayer&'
alias      win='wminput -c ir_ptr -w -c neverball&'
alias      wir='wminput -c ir_ptr -w -c ir_ptr&'
alias      wim='wminput -c ir_ptr -w -c buttons-mame&'
alias      wig='wminput -c gamepad&'
alias      wit='wminput -c buttons-term&'

alias       fevil='find . -regextype posix-extended -regex'
alias         rec='ffmpeg -f x11grab -s 3360x1050 -r 150 -i :0.0 -sameq /tmp/foo.mpg'
alias         feh='feh -Fzrd'
alias     rampeak='dd if=/dev/mem|\cat|strings'
alias  seen_movie='chmod +t,o+w "$@"'
alias mountfixbug='echo 64 > /sys/block/sdn/device/max_sectors && mount -a'
alias     getmail='getmail --rcfile /home/scp1/.getmail/magnus_at_trapd00r.se \
              && getmail --rcfile /home/scp1/.getmail/trapd00r_at_trapd00r.se'

alias        i='echo http://i.japh.se && echo http://i.japh.se|xclip'
alias        l='echo http://l.japh.se && echo http://l.japh.se|xclip'
alias     japh='echo http://japh.se && echo http://japh.se|xclip'
alias      pst='echo http://p.japh.se && echo http://p.japh.se|xclip'
alias     todo='$HOME/devel/time-spent-in-vim/vim $HOME/doc/TODO'

alias    dmesg='$HOME/devel/Term::ExtendedColor/bin/colored_dmesg|grep -v TCP'
alias      vim='/home/scp1/devel/time-spent-in-vim/vim'
alias  vimtime='/home/scp1/devel/time-spent-in-vim/vim --total'
alias    vimsh='vim *.sh'
alias    vimpm='vim *.pm'
alias    vimpl='vim *.pl'
alias     cpan='cpanm'
alias    flash=' clive --stream-exec="mplayer -really-quiet %i" --stream=10'
alias      cat='v'
alias      scx='TERM=xterm;screen -x'
alias      top='cc-grey-ansi;top;cc-x-color-scheme-trapd00r'
alias     make='/home/scp1/devel/utils/mymake'
alias     wimp='(wminput -c mplayer&); mplayer'
alias  mplayer='mplayer -msgmodule 1 -msgcolor'
alias       :q='exit'
alias    urxvt='urxvt -name URxvt.shiva'
alias     less='vimpager'
alias     wget='wget --no-check-certificate -U=Mozilla'
alias     ptop='watch -n1 ps aux --sort=+%cpu'
alias     tree='tree -dA'
alias      mem='su -c mem'
alias  ncmpcpp='colorcoke -r 105 -g 30 -b 50 -s 0 -e 15&&ncmpcpp; \
                  cc-x-color-scheme-trapd00r'
alias    devel='echo http://devel.japh.se/ \
                  && echo http://devel.japh.se/|xclip'


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
  $HOME/devel/App::Pimpd/lib/App/Pimpd/Validate.pm |
  tail -1|perl -pe 's/^\s+\$str =~ //'"

alias gource='gource -1280x720 --max-files 0 --file-idle-time 0 --bloom-multiplier 0.5 --bloom-intensity 0.9 -e 0.7 --background 121212 -o - | ffmpeg -y -b 3000K -r 60 -f image2pipe -vcodec ppm -i - -vcodec libx264 -vpre slow -threads 0 gource.mp4'
alias logstalgia='logstalgia  japh_selected_log -s 5 --output-ppm-stream - |  ffmpeg -y -b 3000K -r 60 -f image2pipe -vcodec ppm -i - -vcodec libx264 -vpre slow -threads 0 logstalgia.mp4'

alias testfetch='sync_cpantesters -a WOLDRICH -d $HOME/devel/CPANTS \
                    && cd $HOME/devel/CPANTS'

alias pkgclean="yes |
                  rm -r $(find $HOME/devel/PKGBUILDS -name 'pkg' \
                    && find $HOME/devel/PKGBUILDS -name 'src')"

alias   iostat='iostat -mtx'
alias     cpuu='ps -eo pcpu,pid,user,args | sort -k 1 -r | head -10'
alias memusage='ps -e -orss=,args= | sort -b -k1,1n|pr -TW$COLUMNS'
alias    shiva='ps -eo pcpu,pid,user,args \
                  | sort -k 1 -r \
                  | head -10 && iostat -mtx && mpstat -P 'ALL' && sar'


alias a='printf "  %s\n  %s\n  %s\n  %s\n" "Magnus Woldrich" "CPAN ID: WOLDRICH" "magnus@trapd00r.se" "http://japh.se"'
alias trapd00r='printf "\t\033#3trapd00r\n\t\033#4trapd00r\n\tA simple, lightweight Perl hacker\n"'
alias trapd00rc='printf "\t\033#3\e[38;5;25mt\e[38;5;26mr\e[38;5;27ma\e[38;5;31mp\e[38;5;32md\e[38;5;33m0\e[38;5;33m0\e[38;5;37mr\n\t\033#4\e[38;5;133mt\e[38;5;134mr\e[38;5;135ma\e[38;5;139mp\e[38;5;140md\e[38;5;141m00\e[38;5;145mr\n\t\e[38;5;240mA simple, lightweight Perl hacker\n"'
alias reset='printf "\033c\033(K\033[J\033[0m\033[?25h"'
