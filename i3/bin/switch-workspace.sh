#!/bin/bash

# use mod+1, mod+2 etc to switch to workspaces on different monitors
# there is 9 workspaces on all monitors (except laptop's built-in display)
# workspace 6,7 on left monitor is treated like workspace 1,2 so
# we can use the same keybindings to switch to them
# in practice, emulating a more sane workspace setup (ratpoison, sdorfehs)

# Get the name of the active output
focused_output=$(i3-msg -t get_workspaces | jq -r '.[] | select(.focused==true).output')

# Define outputs for desktop and laptop
DESKTOP_OUTPUTS=("DP-2" "DP-0" "DP-5" "HDMI-0")
LAPTOP_OUTPUTS=("DP-4-1-5" "DP-1" "DP-4-1-6" "eDP-1")

switch_workspace() {
    case "$1" in
        "DP-0"|"DP-1")  # Left monitor on desktop or laptop
            case "$2" in
                1) i3-msg workspace number 10 ;;
                2) i3-msg workspace number 11 ;;
                3) i3-msg workspace number 12 ;;
                4) i3-msg workspace number 13 ;;
                5) i3-msg workspace number 14 ;;
                6) i3-msg workspace number 15 ;;
                7) i3-msg workspace number 16 ;;
                8) i3-msg workspace number 17 ;;
                9) i3-msg workspace number 18 ;;
            esac
            ;;
        "DP-5"|"DP-3-1-6")  # Top monitor on desktop or laptop
            case "$2" in
                1) i3-msg workspace number 19 ;;
                2) i3-msg workspace number 20 ;;
                3) i3-msg workspace number 21 ;;
                4) i3-msg workspace number 22 ;;
                5) i3-msg workspace number 23 ;;
                6) i3-msg workspace number 24 ;;
                7) i3-msg workspace number 25 ;;
                8) i3-msg workspace number 26 ;;
                9) i3-msg workspace number 27 ;;
            esac
            ;;
        "DP-2"|"DP-3-1-5" | "eDP-1")  # Middle monitor on desktop or laptop, or undocked laptop screen
            case "$2" in
                1) i3-msg workspace number 1 ;;
                2) i3-msg workspace number 2 ;;
                3) i3-msg workspace number 3 ;;
                4) i3-msg workspace number 4 ;;
                5) i3-msg workspace number 5 ;;
                6) i3-msg workspace number 6 ;;
                7) i3-msg workspace number 7 ;;
                8) i3-msg workspace number 8 ;;
                9) i3-msg workspace number 9 ;;
            esac
            ;;
        "HDMI-0"|"eDP-1")  # Behind monitor on desktop or laptop's built-in display
            echo "Output not configured for specific workspace switches." ;;
        *)
            echo "No matching output for keybinding."
            ;;
    esac
}

# Check if we are on desktop or laptop based on available outputs
if xrandr | grep -q "DP-2"; then
    # Desktop setup
    switch_workspace "$focused_output" "$1"
elif xrandr | grep -q "eDP-1"; then
    # Laptop setup
    switch_workspace "$focused_output" "$1"
else
    notify-send "i3 workspace switch" "No known setup detected."
    echo "No known setup detected."
fi

# ########################## i3 config ##########################
#
# #--------------------------------------
# # persistent workspaces on 4 monitors
# #--------------------------------------
#
# # Dont forget to patch i3 first to enable persistent workspaces
# # https://gist.github.com/trapd00r/1914f83477fb126f737fa764083a2627
#
# # define outputs
# set $middle DP-3-1-5
# set $left DP-1
# set $top DP-3-1-6
# set $laptop eDP-1
#
# set $ws1 1
# set $ws2 2
# set $ws3 3
# set $ws4 4
# set $ws5 5
# set $ws6 6
# set $ws7 7
# set $ws8 8
# set $ws9 9
# set $ws10 10
# set $ws11 11
# set $ws12 12
# set $ws13 13
# set $ws14 14
# set $ws15 15
#
# # lock workspaces to outputs
# workspace $ws1 output $middle
# workspace $ws2 output $middle
# workspace $ws3 output $middle
# workspace $ws4 output $middle
# workspace $ws5 output $middle
#
# workspace $ws6 output $left
# workspace $ws7 output $left
# workspace $ws8 output $left
# workspace $ws9 output $left
# workspace $ws10 output $left
#
# workspace $ws11 output $top
# workspace $ws12 output $top
# workspace $ws13 output $top
# workspace $ws14 output $top
# workspace $ws15 output $top
#
# # workspace 1 on different monitors
# # in reality we switch to workspace 6,7 etc
# bindsym $mod+1 exec --no-startup-id /bin/bash ~/etc/i3/bin/switch-workspace.sh 1
# bindsym $mod+2 exec --no-startup-id /bin/bash ~/etc/i3/bin/switch-workspace.sh 2
# bindsym $mod+3 exec --no-startup-id /bin/bash ~/etc/i3/bin/switch-workspace.sh 3
# bindsym $mod+4 exec --no-startup-id /bin/bash ~/etc/i3/bin/switch-workspace.sh 4
# bindsym $mod+5 exec --no-startup-id /bin/bash ~/etc/i3/bin/switch-workspace.sh 5
#
# # bindsym $mod+3 workspace number $ws3
# # bindsym $mod+4 workspace number $ws4
# # bindsym $mod+5 workspace number $ws5
#
# # Mod1+L to switch to the next workspace
# bindsym $mod+Shift+l workspace next
#
# # Mod1+H to switch to the previous workspace
# bindsym $mod+Shift+h workspace prev
#
#
#
# #--------------------------------------
# # exec
# #--------------------------------------
#
# exec --no-startup-id /usr/lib/polkit-gnome/polkit-gnome-authentication-agent-1
#
# # better tiling
# exec --no-startup-id ~/etc/i3/bin/i3-auto-tiling_launch.sh
