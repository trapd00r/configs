#!/usr/bin/zsh

if [ $HOST = 'rambo' ]; then
  export DISPLAY=:0.0
fi

export ACKRC="$HOME/etc/ackrc"
export BROWSER="/usr/bin/w3m"
export CLIVE_CONFIG="$HOME/etc/cliverc"
export EDITOR=vim
export VIDIR_EDITOR_ARGS='-c :retab | :set nolist | :set colorcolumn=0'
export GIST_DIR=$HOME/dev/_gists/
export HOSTNAME="shiva"
export LISTMAX=300
export MAILDIR="/mnt/Docs/Mail/inbox/new"
export MOZ_DISABLE_PANGO=1
export PAGER="vimpager"
export VI_QUICKFIX_SOURCEFILE='stdin'
export X_OSD_COLOR='#a8ff00'

# my stuff                                                                   {{{
export OREILLY_BOOKS_DATABASE="$XDG_DOCUMENTS_DIR/oreilly.db"
#}}}
# PATH                                                                       {{{
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
  | perl -pe 's/\s+//g'
)"
export MANPATH=$MANPATH:/usr/local/man:/opt/local/share/man
export AWKPATH=$HOME/dev/lib/awk/
#                                                                            }}}
# xdg specification                                                          {{{
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
#}}}
# zsh                                                                        {{{
export ZSH_ACTIVE_COMPLETIONS="$( echo ${(kv)_comps[@]} )"
export ZSH_THEME="trapd00r"
export WORDCHARS='*?_-.[]~=&;!#$%^(){}<>'
#}}}
# history                                                                    {{{
export HISTFILE=$XDG_DATA_HOME/zsh/history
export HISTIGNORE="&:ls:[bf]g:exit:reset:clear:cd*"
export HISTSIZE=5000
export SAVEHIST=1000000
#}}}
# clipbored ( https://github.com/trapd00r/clipbored )                        {{{
export CLIPBORED_DMENU_FONT=${FONT}
export CLIPBORED_DMENU_LINES=30
export CLIPBORED_DMENU_LISTMODE='vertical'
export CLIPBORED_DMENU_NORMAL_BG='#1c1c1c'
export CLIPBORED_DMENU_NORMAL_FG='#484848'
export CLIPBORED_DMENU_SELECT_BG='#292929'
export CLIPBORED_DMENU_SELECT_FG='#1c78ef'
#                                                                            }}}
# mpd                                                                        {{{
export MPD_HOST='192.168.1.128'
export MPD_PORT=6600
export MPD_USER='scp1'
if [ $HOST = "shiva" ]; then
  export MPD_PASS=`smokingkills`
fi
#}}}
# perl                                                                       {{{
export HARNESS_SUMMARY_COL_FAIL="bold red"
export HARNESS_SUMMARY_COL_SUC=" bold cyan"
export PERLBREW_ROOT="$HOME/usr/share/perl5"
export PERL_HACK_LIB="/tmp"
export PERL_MM_USE_DEFAULT=1
export PERLDOC="-t"

export PERL5OPT="$(echo '
  -Ilib
  -I$HOME/dev/utils/lib
  -MFile::Basename=basename
  -MCarp=carp,croak,confess,cluck
  -Mopen=:std,:utf8
  -Mutf8
  ' | perl -pe 's/\n//g')"
#export RELEASE_TESTING=1
#}}}
# dmenu                                                                      {{{
export DMENU_FONT=${FONT}
export DMENU_LINES='-l 30'
export DMENU_NORMAL_BG='#1c1c1c'
export DMENU_NORMAL_FG='#484848'
export DMENU_SELECT_BG='#292929'
export DMENU_SELECT_FG='#1c78ef'
#                                                                            }}}
# dzen2                                                                      {{{
export DZEN_ALIGNMENT='c'
export DZEN_BG='#1c1c1c'
export DZEN_FG='#ffffff'
export DZEN_FONT=${FONT}
export DZEN_WIDTH=1680
export DZEN_X_POS=0
export DZEN_Y_POS=1040
# }}}
# Fonts of choice                                                            {{{
export FONT='-windows-montecarlo-medium-r-normal--0-0-72-72-c-0-microsoft-cp1252'
export FONT_B='-windows-montecarlo-bold-r-normal--0-0-72-72-c-0-microsoft-cp1252'
export FONT_I='-nil-profont-medium-r-normal--10-100-72-72-c-50-iso8859-1'
#                                                                            }}}
# Go                                                                         {{{
export GOOS='linux'
export GOROOT="$HOME/go"
export GO_ARCH=386
#}}}
# hardcopies                                                                 {{{
export LP_DEST="Canon_MP150"
export PRINTER="Canon_MP150"
#}}}
# vim: set et sw=2 ft=sh fdm=marker:
