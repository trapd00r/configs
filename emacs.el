(setq auto-save-default nil)

(add-to-list 'load-path "~/.emacs.d/")
(add-to-list 'load-path "~/.emacs.d/evil")
(add-to-list 'load-path "~/.emacs.d/themes")

(require 'color-theme-gruber-darker)
(require 'evil)
(evil-mode 1)

(setq color-theme-is-global t)

(color-theme-gruber-darker)
