setxkbmap se &
urxvtd -q -f &
xmodmap -e 'clear Lock' -e 'keycode 0x42 = Escape' 
xrdb $HOME/.Xresources 
xset m 1 1 
#feh --bg-tile /mnt/Docs/Wallpapers/bg.gif &
xsetroot -solid "#121212" &
#perl $HOME/devel/utils/randwall.pl&

#exec /usr/local/bin/stumpwm
#exec ck-launch-session sbcl --load $HOME/bin/startstump
exec ck-launch-session /usr/local/bin/stumpwm
#subtle








#dwm
#wmii -r $HOME/.wmii-hg/wmiirc.sh
