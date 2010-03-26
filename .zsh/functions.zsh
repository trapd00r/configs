du1() {
  du -h --max-depth=1 "$@" | sort -k 1,1hr -k 2,2f;
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
horny() {
  wget $(pump -fetch graphics $@);
}
zsh_stats() {
  history|awk '{print $2}'|sort|uniq -c|sort -rn|head
}
function mk() {
  mkdir -p $1
  cd $1
}
