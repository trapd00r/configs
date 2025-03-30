#!/bin/bash

source ~/.secret_zshrc

log_debug() {
    echo "[DEBUG] $*" >&2
}

# List items
items=$(bw list items --session "$BW_SESSION" | jq -r '.[] | "\(.name) | \(.login.username) | \(.id)"' | rofi -normal-window -dmenu -p "Select item to edit")
[ -z "$items" ] && notify-send "Bitwarden" "Cancelled" && exit

# Extract ID
id=$(echo "$items" | awk -F'|' '{print $3}' | xargs)
log_debug "Selected ID: $id"

# Choose action
action=$(printf "Edit\nDelete\nCancel" | rofi -normal-window -dmenu -p "Action")
[ "$action" = "Cancel" ] || [ -z "$action" ] && notify-send "Bitwarden" "Cancelled" && exit
log_debug "Action: $action"

if [ "$action" = "Delete" ]; then
    confirm=$(printf "No\nYes" | rofi -normal-window -dmenu -p "Really delete?")
    [ "$confirm" != "Yes" ] && notify-send "Bitwarden" "Cancelled" && exit
    bw delete item "$id" --session "$BW_SESSION"
    notify-send "Bitwarden" "Deleted"
    exit
fi

# --- EDIT FLOW ---

# Get current info
item=$(bw get item "$id" --session "$BW_SESSION")
domain=$(echo "$item" | jq -r '.name')
username=$(echo "$item" | jq -r '.login.username')
password=$(echo "$item" | jq -r '.login.password')

# Prompt for new values (pre-filled)
new_domain=$(echo "$domain" | rofi -normal-window -dmenu -p "Domain:")
[ -z "$new_domain" ] && notify-send "Bitwarden" "Cancelled" && exit

new_username=$(echo "$username" | rofi -normal-window -dmenu -p "Username:")
[ -z "$new_username" ] && notify-send "Bitwarden" "Cancelled" && exit

new_password=$(echo "$password" | rofi -normal-window -password -dmenu -p "Password:")
[ -z "$new_password" ] && notify-send "Bitwarden" "Cancelled" && exit

# Build new payload
payload=$(jq -n --arg domain "$new_domain" --arg username "$new_username" --arg password "$new_password" '{
    object: "item",
    type: 1,
    name: $domain,
    favorite: false,
    notes: null,
    reprompt: 0,
    login: {
        username: $username,
        password: $password,
        totp: null,
        uris: [{ uri: ("http://" + $domain) }]
    }
}')

# Encode and update
encoded=$(echo "$payload" | bw encode --session "$BW_SESSION")
echo "$encoded" | bw edit item "$id" --session "$BW_SESSION" && notify-send "Bitwarden" "Item updated"
