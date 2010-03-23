setxkbmap se &
urxvtd -q -f &
xmodmap -e 'clear Lock' -e 'keycode 0x42 = Escape' &
xrdb $HOME/.Xresources &
xset m 1 1 &
/usr/local/bin/stumpwm

#dwm
#wmii -r $HOME/.wmii-hg/wmiirc.sh
