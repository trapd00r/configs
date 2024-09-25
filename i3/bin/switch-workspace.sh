#!/bin/bash

# use mod+1, mod+2 etc to switch to workspaces on different monitors
# there is 5 workspaces on the main monitor, but on the other ones there is only 2
# workspace 6,7 on left monitor is treated like workspace 1,2 so
# we can use the same keybindings to switch to them
# in practice, emulating a more sane workspace setup (ratpoison, sdorfehs)

# Get the name of the active output
focused_output=$(i3-msg -t get_workspaces | jq -r '.[] | select(.focused==true).output')

# Define outputs for desktop and laptop
DESKTOP_OUTPUTS=("DP-2" "DP-0" "DP-5" "HDMI-0")
LAPTOP_OUTPUTS=("DP-3-1-5" "DP-1" "DP-3-1-6" "eDP-1")

switch_workspace() {
    case "$1" in
        "DP-0"|"DP-1")  # Left monitor on desktop or laptop
            case "$2" in
                1) i3-msg workspace number 6 ;;
                2) i3-msg workspace number 7 ;;
            esac
            ;;
        "DP-5"|"DP-3-1-6")  # Top monitor on desktop or laptop
            case "$2" in
                1) i3-msg workspace number 8 ;;
                2) i3-msg workspace number 9 ;;
            esac
            ;;
        "DP-2"|"DP-3-1-5")  # Middle monitor on desktop or laptop
            case "$2" in
                1) i3-msg workspace number 1 ;;
                2) i3-msg workspace number 2 ;;
                3) i3-msg workspace number 3 ;;
                4) i3-msg workspace number 4 ;;
                5) i3-msg workspace number 5 ;;
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
    echo "No known setup detected."
fi


# i3 config:

# # define outputs
# set $middle DP-2
# set $left DP-0
# set $top DP-5
# set $behind HDMI-0
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
#
# # lock workspaces to outputs
# workspace $ws1 output $middle
# workspace $ws2 output $middle
# workspace $ws3 output $middle
# workspace $ws4 output $middle
# workspace $ws5 output $middle
# workspace $ws6 output $left
# workspace $ws7 output $left
# workspace $ws8 output $top
# workspace $ws9 output $top
#
#
# # workspace 1 on different monitors
# # in reality we switch to workspace 6,7 etc
# bindsym $mod+1 exec --no-startup-id /bin/bash ~/etc/i3/bin/switch-workspace.sh 1
# bindsym $mod+2 exec --no-startup-id /bin/bash ~/etc/i3/bin/switch-workspace.sh 2
#
# bindsym $mod+3 workspace number $ws3
# bindsym $mod+4 workspace number $ws4
# bindsym $mod+5 workspace number $ws5
