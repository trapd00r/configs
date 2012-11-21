#!/bin/zsh
# vim: ft=sh et sw=2 cc:
(
  xrandr --output  HDMI-0 --mode 1920x1080 --pos 0x0 --rotate left \
         --output DVI-D-0 --mode 1920x1080 --pos 1080x525 \
)&

#unclutter -idle 4 &
#xset m 2 1 &
#xsetroot  -cursor_name left_ptr
setxkbmap -option terminate:ctrl_alt_bksp &
setxkbmap se -variant progqwerty \
  || setxkbmap se -variant nodeadkeys
xmodmap $HOME/etc/xmodmaprc &
xrdb $HOME/etc/Xresources   &
#urxvtd -q -f -o                     &
#(sleep .4; urxvtc -name URxvt.vim) &

# git[master]# pacman -S openbox lxappearance-obconf obmenu perlpanel obconf dwm wmii-hg i3{-wm,status,lock}^C
#exec openbox-session
#exec  dwm
#exec  wmiii
#exec  i3
#exec enlightenment_start -no-precache
#exec evilwm
#exec antiwm
#exec /home/scp1/bin/wrxvt -name sid -chdir ~/dev &
exec wrxvt &
nvidia-settings -a GlyphCache=1 &
nvidia-settings -a InitialPixmapPlacement=2 &
exec ratpoison
