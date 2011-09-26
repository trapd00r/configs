# zex: `ex'ish for zsh.

# Author: Takeshi Banse <takebi@laafc.net>
# Licence: Public Domain

# Thank you very much, tyru!
# I want to use ex in zsh. I can do it with iex eventually.

# To use this,
# 1) install iex and add it to your $PATH.
# http://github.com/tyru/iex
# 2) source this file.
# % source zex.zsh
# 3) add default key bindings.
# % zex-install-keys
#
# *Optionally* you can use the zcompiled file with the autoloading for a
# little faster loading on every shell startup, if you zcompile the
# necessary functions.
# *1) zcompile the defined functions and the install command.
# (generates ~/.zsh/zfunc/{zex,zex-install}.zwc)
# % O=~/path/to/zex.zsh; (zsh -c "source $O && zex-zcompile $O ~/.zsh/zfunc")
# *2) source the zcompiled install command file insted of this file.
# % source ~/.zsh/zfunc/zex-install; zex-install; zex-install-keys

# Note:
# zex-install-keys replaces some keymap entries. Please beware of.
# -- >8 --
# '^[:' zex-edit-command-line (emacs)
# ':'   zex-edit-command-line (vicmd)
# -- 8< --

# TODO: execute updated command directly.
# TODO: a standalone function.
# TODO: disable undo when editing the iex buffer or better.

# History

# v0.0.1
# Initial version.

# Code

bindkey -N zex emacs
zex_BUFFER=
zexes=()

zex-accept-line () {
  # $BUFFER holds the ex commands string at this point.
  [[ -n $BUFFER ]] && {
    print -s -- "${(S)"${(q)BUFFER}"//$\'\\n\'/\\n}"
    local result="$(zex-iex "$BUFFER" "$zex_BUFFER")"
    (($? == 0)) && {
      zex_BUFFER="$result"
      zle .accept-line
      return
    }
  }
  zle .send-break
}; zle -N zex-accept-line

zex-iex () {
  iex -e "$1" <(echo "$2")
}

with-zex () {
  {
    local old_buffer="$BUFFER"
    local ps=$PS1
    local cs=$CURSOR
    local zex_ps=$(echo "%{\e[1;37m%}:%{\e[0m%}")
    PS1="$ps$BUFFER
$zex_ps"
    zle reset-prompt
    { local k=; "$@" k; [[ -n $k ]] && eval $k }
  } always {
    PS1=$ps
    zle reset-prompt # or zle -I
    CURSOR=$cs
  }
}

zex-recursive-edit () {
  local kplace="$@[$#@]"
  local zhistf="$1"
  zex_BUFFER="$BUFFER"
  fc -ap ${zhistf}
  local h=; zex-histno h "${zhistf}"; ((h++))
  local HISTNO=$h
  BUFFER=
  zle recursive-edit -K zex && {
    # XXX: 'fc -p' in this recursive-edit case,
    # the HISTNO manipulation *IS NEEDED* for the up-line-or-history etc,
    # but 'print -s' does the job as yet.
    # XXX: This HISTNO manupilation forces to update the BUFFER outside of
    # its dynamic environment like this.
    : ${(P)kplace::='BUFFER=$zex_BUFFER'}
  } || {
    : ${(P)kplace::='BUFFER=$old_buffer'}
  }
}

zex-histno () {
  local place="$1"
  local zhist="$2"
  : ${(P)place::=${${(z)${"$({{
    zsh -c "HISTSIZE=1;fc -p $zhistf && fc -l"
    (($?==0)) || echo " 0 $?"
  } 2> /dev/null})"}}[1]}}
}

zex-edit-command-line () {
  zex with-zex zex-recursive-edit "${HOME}/.zex_history"
}; zle -N zex-edit-command-line
zexes+=zex-edit-command-line

# Entry point.
zex () {
  # to implement autoloading easier,
  # all of the zex commands will be called through this func.
  zex1 "$@"
}
zex1 () { "$@" }

zex-install () {
  bindkey -N zex emacs
  bindkey -M zex "^M" zex-accept-line
}; zexes+=zex-install
zex-install

zex-install-keys () {
  {
    BK () {
      bindkey -M vicmd "$1" $2
      { bindkey -M afu-vicmd "$1" $2 } > /dev/null 2>&1
      bindkey -M emacs "^[$1" $2
      { bindkey -M afu "^[$1" $2 } > /dev/null 2>&1
    }
    BK ":" zex-edit-command-line
  } always {
    unfunction BK
  }
}; zexes+=zex-install-keys

# zcompiling code.

zex-clean () {
  local d=${1:-~/.zsh/zfunc}
  rm -f ${d}/{zex,zex.zwc*(N)}
  rm -f ${d}/{zex-install,zex-install.zwc*(N)}
}

zex-install-installer () {
  local match mbegin mend
  eval ${${"$(<=(cat <<"EOT"
    zex-install-after-load () {
      { $body }
      typeset -g zex_BUFFER=
      zex_loaded_p=t
    }
    zex-install-maybe () {
      [[ -z ${zex_loaded_p-} ]] || return
      zex-install-after-load
    }
    # redefine zex
    zex () {
      zex-install-maybe
      zex1 "$@"
    }
EOT
  ))"}/\$body/
  $(print -l \
    "# zex's zle widget used on zex keymap" \
    ${${${(M)${(@f)"$(zle -l)"}:#(zex*)}:#(${~${(j:|:)zexes}})}/(#b)(*)/zle -N ${(qqq)match}})}
}

zex-zcompile () {
  #local zex_zcompiling_p=t
  local s=${1:?Please specify the source file itself.}
  local d=${2:?Please specify the directory for the zcompiled file.}
  emulate -L zsh
  setopt extended_glob no_shwordsplit

  echo "** zcompiling zex in ${d} for a little faster startups..."
  [[ -n ${ZEX_PARANOID-} ]] && {
    echo "* reloading ${s}"
    source ${s} >/dev/null 2>&1
  }
  echo "mkdir -p ${d}" | sh -x
  zex-clean ${d}
  zex-install-installer

  local g=${d}/zex
  echo "* writing code ${g}"
  {
    local -a fs
    : ${(A)fs::=${(Mk)functions:#(*zex*)}}
    echo "#!zsh"
    echo "# NOTE: Generated from zex.zsh ($0). Please DO NOT EDIT."; echo
    echo "$(functions \
      ${fs:#(def-*|*register*|zex-clean|zex-install-installer|zex-zcompile|\
        ${~${(j:|:)zexes}})})"
    echo "\nzex \"\$@\""
  }>! ${g}

  local gi=${d}/zex-install
  echo "* writing code ${gi}"
  {
    echo "#!zsh"
    echo "# NOTE: Generated from zex.zsh ($0). Please DO NOT EDIT."; echo
    echo "$(functions $zexes)"
    print -l \
      "# zex's zle widget used on main keymap" \
      ${${(M)${(M)${(@f)"$(zle -l)"}:#(zex*)}:#(${~${(j:|:)zexes}})}/(#b)(*)/zle -N ${(qqq)match}}
  }>! ${gi}

  [[ -z ${ZEX_NOZCOMPILE-} ]] || return
  autoload -U zrecompile && {
    Z () { echo -n "* "; zrecompile -p -R "$1" }; Z ${g} && Z ${gi}
  } && {
    zmodload zsh/datetime
    touch --date="$(strftime "%F %T" $((EPOCHSECONDS + 10)))" {${g},${gi}}.zwc
    [[ -z ${ZEX_ZCOMPILE_NOKEEP-} ]] || { echo "rm -f ${g} ${gi}" | sh -x }
    echo "** All done."
    echo "** Please update your .zshrc to load the zcompiled file like this,"
    cat <<EOT
-- >8 --
## zex.zsh stuff.
# source ${s/$HOME/~}
{ . ${gi/$HOME/~}; zex-install; zex-install-keys; }
-- 8< --
EOT
  }
}
zex-install-keys
