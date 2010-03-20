setxkbmap se &
urxvtd -q -f &
xmodmap -e 'clear Lock' -e 'keycode 0x42 = Escape' &
xrdb $HOME/.Xresources &
xset m 1 1 &
/usr/local/bin/stumpwm
#startkde
#/home/scp1/temp/wmii+ixp-3.9b1/cmd/wmii.out

