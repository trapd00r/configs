urxvt -name URxvt.shiva &
setxkbmap se &
xmodmap -e 'clear Lock' -e 'keycode 0x42 = Escape' &
xrdb $HOME/.Xresources &
xset m 1 1 &
/usr/local/bin/stumpwm
#startkde

