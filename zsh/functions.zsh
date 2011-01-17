du1() {
  du -h --max-depth=1 "$@" | sort -k 1,1hr -k 2,2f;
}

horny() { feh -FZrD3 /mnt/Porn/00-Pics/** && printf "Done!\n" }

vimp() {
  /home/scp1/devel/time-spent-in-vim/vim $(find . |grep -Pi '.+(?:pl|pm)$'|grep -v 'blib'|perl -pe 's/\n/ /')
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
