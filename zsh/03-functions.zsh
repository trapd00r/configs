pacman() {
  sexpac "$@"
}

ossxmix() {
  /usr/bin/ossxmix &
  (sleep 7; killall ossxmix)
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

256co() {
  for line in {0..15}; do for col in {0..15}; do
    local code=$(( $col * 16 + ${line} ))
    printf $'\e[38;05;%dm %03d' ${code} ${code}
  done
  print; done
}

apvlv() {
  /usr/bin/apvlv -c $XDG_CONFIG_HOME/apvlvrc "$@"
}

cpan_up() {
  cpan_upload "$@" && mv -v "$@" /mnt/Docs/Backup/
}

neverball() {
  /usr/bin/neverball --data $XDG_CONFIG_HOME/neverball/
}

mplayer() {
  /usr/bin/mplayer -include $XDG_CONFIG_HOME/mplayer/config -profile $HOST "$@"
}

mplayer_headphones() {
  /usr/bin/mplayer \
    -msgmodule 1 -msgcolor -include $XDG_CONFIG_HOME/mplayer/config \
    -channels 6 -af resample=48000,hrtf "$@"
}

zc() {
  for z in $HOME/etc/zsh/*.zsh $HOME/.zshrc; do
    zcompile $z
    echo "Compiled $z"
  done
}

tig() {
  TERM=xterm-256color /usr/bin/tig
}

mutt() {
  TERM=xterm-256color /usr/bin/mutt -F /home/scp1/etc/muttrc "$@"
}

re() {
  [[ $1 =~ $REPLY ]]
}

vimconfig() {
  $HOME/dev/time-spent-in-vim/vim $HOME/.vim{rc,/*.vim}
}

zshconfig() {
  $HOME/dev/time-spent-in-vim/vim $XDG_CONFIG_HOME/zsh/*.{zsh,theme}
}

commands() {
  echo -n $PATH | xargs -d : -I {} find {} -maxdepth 1 \
       -executable -type f -printf '%P\n' | sort -u
}

daemon() {
  echo '
sub daemonize {
  my $daemon_log = shift // q{/dev/null};
  use POSIX q{setsid};
  my $PID = fork();
  exit(0) if($PID); #parent
  exit(1) if(!defined($PID)); # out of resources

  setsid();
  $PID = fork();
  exit(1) if(!defined($PID));

  if($PID) { # parent
    waitpid($PID, 0);
    unlink($pidfile_daemon); # remove the lock when child have died
    exit(0);
  }
  elsif($PID == 0) { # child
    open(my $fh, q{>}, $pidfile_daemon)
      or die(qq{Cant open $pidfile_daemon: $!});
    print $fh $$;
    close($fh);
    open(STDOUT, q{>}, $daemon_log);
    open(STDERR, q{>}, q{/dev/null});
    open(STDIN,  q{<}, q{/dev/null});
  }
}
sub killkid {
  open(my $fh, q{<}, $pidfile_pimpd) or return 1; # for now
  my $pimpd_player = <$fh>;
  close($fh);
  return 0;
}'
}


doc() {
  builtin cd $HOME/doc
  if [[ $(pwd) == "$HOME/doc" ]]; then
    find . -maxdepth 1 -regextype posix-extended  -regex '^[.]/[^\.].+' \
           -type f -printf "%f\n"| sort | ls_color
  fi
}

du1() {
  du -h --max-depth=1 "$@" | sort -k 1,1hr -k 2,2f;
}

horny() { feh -FZrD3 /mnt/Porn/00-pics/ && printf "Done!\n" }

vimp() {
  /home/scp1/dev/time-spent-in-vim/vim $(find . |grep -Pi '.+(?:pl|pm)$'|grep -v 'blib'|perl -pe 's/\n/ /')
}

vimgo() {
  /home/scp1/dev/time-spent-in-vim/vim $(find . |grep -Pi '.+(?:go)$'|perl -pe 's/\n/ /')
}


cd() {
  builtin cd "$@"; ls
}
regcheck() {
  emulate -L zsh
  zmodload -i zsh/pcre
  pcre_compile $1 && \
  pcre_match $2 && echo 'matches' || echo 'no match'
}
zsh_stats() {
  history|awk '{print $2}'|sort|uniq -c|sort -rn|head
}
mk() {
  mkdir -p $1
  cd $1
}

absurl() {
  perl -MWWW::Mechanize -e "$m = WWW::Mechanize->new;$u=shift;$m->get($u)||die;print $_->url_abs, "\n" for  $m->links;"
}

tf() {
    val=$?
    if [ "$val" = "0" ]
    then
        echo ":-)"
    else
        echo ":-("
    fi
}

goto() { [ -d "$1" ] && cd "$1" || cd "$(dirname "$1")"; }
cpf() { cp "$@" && goto "$_"; }
mvf() { mv "$@" && goto "$_"; }

# vim: ft=sh:
