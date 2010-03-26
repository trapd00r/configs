setxkbmap se &
urxvtd -q -f &
xmodmap -e 'clear Lock' -e 'keycode 0x42 = Escape' &
xrdb $HOME/.Xresources &
xset m 1 1 &
xset -dpms &
nitrogen --restore &
/usr/local/bin/stumpwm







#$(which i3)

#dwm
#wmii -r $HOME/.wmii-hg/wmiirc.sh

erresources=$HOME/.Xresources
usermodmap=$HOME/.Xmodmap
sysresources=/etc/X11/xinit/.Xresources
sysmodmap=/etc/X11/xinit/.Xmodmap

case "$1" in
    openbox) exec ck-launch-session openbox-session ;;
    fluxbox) exec ck-launch-session startfluxbox ;;
    xfce4) exec ck-launch-session startxfce4 ;;
    kde4) exec ck-launch-session startkde ;;
    gnome) exec ck-launch-session gnome-session ;;
    e17) exec ck-launch-session /usr/bin/enlightenment_start ;;
    e16) exec ck-launch-session /usr/bin/starte16 ;;
    pekwm) exec ck-launch-session /usr/bin/pekwm ;;
    ratpoison) exec ck-launch-session ratpoison ;;
    awesome) exec ck-launch-session $HOME/bin/run_awesome ;;
    dwm) exec ck-launch-session $HOME/bin/dwm_run ;;
    wmii) until wmii; do true ; done  ;;
    icewm) exec icewm-session ;;
    xmonad) exec ck-launch-session xmonad ;;
    blackbox) exec ck-launch-session blackbox ;;
    *) exec ck-launch-session openbox-session ;;
esac
