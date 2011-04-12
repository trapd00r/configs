

re() {
  [[ $1 =~ $REPLY ]]
}

vimconfig() {
  $HOME/devel/time-spent-in-vim/vim $HOME/.vim{rc,/*.vim}
}

zshconfig() {
  $HOME/devel/time-spent-in-vim/vim $HOME/.zsh{rc,/*.{theme,zsh}}
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

horny() { feh -FZrD3 /mnt/Porn/00-Pics/** && printf "Done!\n" }

vimp() {
  /home/scp1/devel/time-spent-in-vim/vim $(find . |grep -Pi '.+(?:pl|pm)$'|grep -v 'blib'|perl -pe 's/\n/ /')
}

vimgo() {
  /home/scp1/devel/time-spent-in-vim/vim $(find . |grep -Pi '.+(?:go)$'|perl -pe 's/\n/ /')
}


cd() {
  builtin cd $@; ls
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
