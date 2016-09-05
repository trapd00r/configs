###< vim: set ft=zsh:fdm=marker:fmr=#<,#>:fdl=0:fen:et:sw=2:fcl=all:
###
#      ${HOME}/etc/zsh/02-alias-suffix.zsh
#   ‗‗‗‗‗‗‗‗‗‗‗‗ ‗‗‗‗‗‗ ‗‗‗‗‗‗‗‗ ‗‗‗‗‗‗‗‗‗‗‗
#         owner  Magnus Woldrich <magnus.woldrich@gmail.com>
#         btime  2009-04-24
#         mtime  2016-09-05 14:56:04
#   permissions  You are free to use things you may find useful here.
#                Would my tweaks happen to give you a raise or fetch you a
#                girlfriend, it goes without saying I'm counting on you
#                to share with me as I've shared with you.
#           git  http://github.com/trapd00r/configs/zsh  (up-to-date)
#           url  http://devel.japh.se/configs/zsh        (sync 1/24h)
#           irc  japh@freenode #zsh #vim #perl
#   ‗‗‗‗‗‗‗‗‗‗‗‗ ‗‗‗‗‗‗‗‗‗‗‗‗‗ ‗‗‗‗ ‗‗‗‗ ‗‗‗‗
###
###>

local -a aliases_suffix_{mplayer,vim,feh}

#< vim
aliases_suffix_vim=(
  asm
  awk
  bash
  c
  cfg
  coffee
  conf
  cpp
  cs
  css
  csv
  diff
  enc
  eps
  etx
  ex
  example
  git
  gitignore
  go
  h
  hs
  htm
  html
  info
  ini
  java
  jhtm
  js
  jsm
  jsm
  json
  jsp
  lisp
  log
  lua
  map
  markdown
  md
  mf
  mfasl
  mi
  mkd
  mtx
  nfo
  pacnew
  patch
  pc
  pfa
  php
  pid
  PKGBUILD
  pl
  PL
  pm
  pod
  py
  rb
  rdf
  ru
  sed
  sfv
  sh
  signature
  sty
  sug
  t
  tcl
  tdy
  tex
  textile
  tfm
  tfnt
  theme
  txt
  urlview
  vim
  viminfo
  xml
  yml
  zsh
)
#>
#< mplayer
aliases_suffix_mplayer=(
  avi
  cue
  dat
  fcm
  flac
  flv
  m3u
  m4
  m4a
  m4v
  mkv
  mov
  mp3
  mp4
  mpeg
  MOV
  mpg
  ogg
  ogm
  ogv
  rmvb
  sample
  spl
  ts
  wmv
)
local MPLAYER_CONFIG=$XDG_CONFIG_HOME/mplayer/config
#>

alias -s $^aliases_suffix_vim="${EDITOR} --"
alias -s $^aliases_suffix_mplayer='mplayer -msgmodule 1 -msgcolor -include $MPLAYER_CONFIG --'
