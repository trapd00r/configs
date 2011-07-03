#!/usr/bin/zsh
#export RELEASE_TESTING=1
#export PERL5OPT='-Mstrict'

export PATH="$( echo \
  $HOME/dev/utils:\
  ~/bin:\
  /bin:\
  /usr/bin:\
  /usr/local/bin:\
  /usr/bin/site_perl:\
  /usr/bin/core_perl:\
  /usr/bin/vendor_perl:\
  /usr/lib/perl5/site_perl/bin:\
  /usr/lib/perl5/vendor_perl/bin:\
  /usr/lib/perl5/core_perl/bin:\
  /sbin:\
  /usr/sbin:\
  /usr/bin/perlbin/site:\
  /usr/bin/perlbin/vendor:\
  /usr/bin/perlbin/core:\
  /home/scp1/perl5/perlbrew/perls/perl-5.8.3/:\
  $HOME/go/bin:\
  |perl -pe 's/\s+//g'
)"

export FONT='-windows-montecarlo-medium-r-normal--0-0-72-72-c-0-microsoft-cp1252'
export FONT_B='-windows-montecarlo-bold-r-normal--0-0-72-72-c-0-microsoft-cp1252'
export FONT_I='-nil-profont-medium-r-normal--10-100-72-72-c-50-iso8859-1'

export ACKRC="/home/scp1/etc/ackrc"
export BIN_HOME="$HOME/bin"
export BROWSER="/usr/bin/w3m"
export CLIPBORED_DMENU_FONT=${FONT}
export CLIPBORED_DMENU_LINES=30
export CLIPBORED_DMENU_LISTMODE='vertical'
export CLIPBORED_DMENU_NORMAL_BG='#1c1c1c'
export CLIPBORED_DMENU_NORMAL_FG='#484848'
export CLIPBORED_DMENU_SELECT_BG='#292929'
export CLIPBORED_DMENU_SELECT_FG='#1c78ef'
export CLIVE_CONFIG="/home/scp1/etc/cliverc"
export DEVEL_HOME="$HOME/dev"
export DMENU_FONT=${FONT}
export DMENU_LINES='-l 30'
export DMENU_NORMAL_BG='#1c1c1c'
export DMENU_NORMAL_FG='#484848'
export DMENU_SELECT_BG='#292929'
export DMENU_SELECT_FG='#1c78ef'
export DZEN_ALIGNMENT='c'
export DZEN_BG='#1c1c1c'
export DZEN_FG='#ffffff'
export DZEN_FONT=${FONT}
export DZEN_WIDTH=1680
export DZEN_X_POS=0
export DZEN_Y_POS=1040
export EDITOR=vim
export GIST_DIR=$HOME/dev/_gists/
export GOOS='linux'
export GOROOT=$HOME/go
export GO_ARCH=386
export HARNESS_SUMMARY_COL_FAIL="bold red"
export HARNESS_SUMMARY_COL_SUC=" bold cyan"
export HISTFILE=$XDG_DATA_HOME/zsh/history
export HISTIGNORE="&:ls:[bf]g:exit:reset:clear:cd*"
export HISTSIZE=5000
export HOSTNAME="shiva"
export LISTMAX=300
export LP_DEST="Canon_MP150"
export MANPATH=$MANPATH:/usr/local/man:/opt/local/share/man
export MOZ_DISABLE_PANGO=1
export MPD_HOST='192.168.1.128'
export MPD_PASS=`smokingkills`
export MPD_PORT=6600
export MPD_USER='scp1'
export PAGER="vimpager"
export PERL_HACK_LIB="/tmp"
export PERL_MM_USE_DEFAULT=1
export PRINTER="Canon_MP150"
export SAVEHIST=1000000
export VI_QUICKFIX_SOURCEFILE='stdin'
export XAUTHORITY="${XDG_DATA_HOME}/Xauthority"
export XDG_CACHE_HOME="$HOME/etc/cache"
export XDG_CONFIG_HOME="$HOME/etc"
export XDG_DATA_HOME="$HOME/var"
export XDG_DESKTOP_DIR="/tmp/.${UID}"
export XDG_DOCUMENTS_DIR="${HOME}/usr/share/doc"
export XDG_DOWNLOAD_DIR="/tmp/scp1/"
export XDG_MUSIC_DIR="/mnt/Music_1/"
export XDG_PICTURES_DIR="/mnt/Docs/Photo/"
export XDG_PUBLICSHARE_DIR="/tmp/.${UID}"
export XDG_TEMPLATES_DIR="/tmp/.${UID}"
export XDG_VIDEOS_DIR="/mnt/Movies_1/"
export X_OSD_COLOR='#a8ff00'
export ZSH_ACTIVE_COMPLETIONS="$( echo ${(kv)_comps[@]} )"
export ZSH_THEME="trapd00r"


# vim: set et sw=2 ft=sh:
