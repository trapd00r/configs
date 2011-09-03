;; File:     ~/.emacs.d/emacs-init.el
;; Author:   Burke Libbey <burke@burkelibbey.org>

;;-----[ Feature Selection ]---------------------------------------------------
(setq save-interprogram-paste-before-kill t)

(require 'facemenu)
(require 'font-lock)

(setq features 
      `((ack              . t)
        (browse-kill-ring . t)
        (cedet            . nil)
        (edit-server      . t)
        (elpa             . nil)
        (eshell           . t)
        (html5            . t)
        (ido              . t)
        (linum            . t)
        (magit            . t)
        (override-copy    . ,window-system)
        (font             . ,window-system)
        (rdebug           . t)
        (rvm              . nil)
        (smart-tab        . t)
        (color-theme      . ,window-system)
        (speedbar         . ,window-system)
        (starter-kit-js   . t)
        (timestamp        . t)
        (yasnippet        . nil)))

(defmacro feature (feature &rest args)
  `(when (cdr (assoc (quote ,feature) features))
     ,@args))

;;-----[ ELPA ]--------------------------------------------------------

(feature elpa
         (require 'package)
         (setq package-archives (cons '("tromey" . "http://tromey.com/elpa/") package-archives))
         (package-initialize))

;;-----[ Housekeeping ]--------------------------------------------------------
(require 'cl)

(defvar *user-name*  "Burke Libbey")
(defvar *short-name* "burke")
(defvar *user-email* "burke@burkelibbey.org")
(defvar *emacs-config-directory* "~/.emacs.d")

(let ((private-el (concat *emacs-config-directory* "/private.el")))
  (when (file-exists-p private-el)
    (load-file private-el)))

(setq max-lisp-eval-depth 500000)
(setq max-specpdl-size 500000)

(setq site-lisp-path (concat *emacs-config-directory* "/site-lisp/"))

(defmacro add-path (path)
  `(add-to-list 'load-path (concat site-lisp-path ,path)))

(add-path "")

(global-set-key "\C-q" (make-sparse-keymap))
(global-set-key "\C-q\C-r" 'query-replace-regexp)

;;-----[ Custom ]--------------------------------------------------------------
(custom-set-faces
  ;; custom-set-faces was added by Custom.
  ;; If you edit it by hand, you could mess it up, so be careful.
  ;; Your init file should contain only one such instance.
  ;; If there is more than one, they won't work right.
 '(diff-added ((t (:foreground "#559944"))))
 '(diff-context ((t nil)))
 '(diff-file-header ((((class color) (min-colors 88) (background dark)) (:foreground "RoyalBlue1"))))
 '(diff-function ((t (:foreground "#00bbdd"))))
 '(diff-header ((((class color) (min-colors 88) (background dark)) (:foreground "RoyalBlue1"))))
 '(diff-hunk-header ((t (:foreground "#fbde2d"))))
 '(diff-nonexistent ((t (:inherit diff-file-header :strike-through nil))))
 '(diff-refine-change ((((class color) (min-colors 88) (background dark)) (:background "#182042"))))
 '(diff-removed ((t (:foreground "#de1923"))))

 '(default ((t (:slant normal :weight normal :height 120 :family "pragmata tt"))) t)
 '(mode-line ((t (:inherit default))) t)
 '(minibuffer ((t (:inherit default))) t)
 '(minibuffer-prompt ((t (:inherit default))) t)
 '(echo-area ((t (:inherit default))) t)
 '(mode-line-inactive ((t (:inherit default))) t))

;;-----[ Custom-set-variables ]------------------------------------------------

(custom-set-variables
  '(global-font-lock-mode    t nil (font-lock)) ;; Syntax higlighting
  ;; buffers with duplicate names will be dir/file, not file<n>
  '(uniquify-buffer-name-style (quote forward) nil (uniquify))
  '(minibuffer-max-depth     nil)        ;; enable multiple minibuffers
  '(indent-tabs-mode         nil)        ;; soft tabs
  '(default-tab-width        2)          ;; tabs of width 8
  '(scroll-bar-mode          nil)        ;; no scroll bar
  '(tool-bar-mode            nil)        ;; eww. bad.
  '(menu-bar-mode            nil)        ;; eww. bad.
  '(column-number-mode       t)          ;; show column number in mode line
  '(show-paren-mode          t)          ;; highlight matching paren on hover
  '(case-fold-search         t)          ;; case-insensitive search
  '(transient-mark-mode      t)          ;; highlight the marked region
  '(inhibit-startup-screen   t)
  '(inhibit-startup-message  t)          ;; no startup message
  '(default-major-mode       'text-mode) ;; open unknown in text mode
  '(ring-bell-function       'ignore)    ;; turn off system beep
  '(c-default-style          "bsd")     ;; use k&r style for C indentation
  '(ruby-deep-arglist        nil)
  '(ruby-deep-indent-paren   nil)
  '(make-backup-files        nil)
  '(ns-antialias-text        nil)
  '(auto-save-default        nil)
  '(ruby-deep-indent-paren-style nil)
  '(default-major-mode (quote text-mode)))


;;-----[ Features! ]-----------------------------------------------------------

(feature ack
         (require 'ack)
         (global-set-key (kbd "A-F") 'ack))

(feature browse-kill-ring
         (require 'browse-kill-ring)
         (global-set-key "\C-c\C-k" 'browse-kill-ring))

(feature cedet
         (load-file (concat site-lisp-path "cedet-1.0pre4/common/cedet.el"))
         (semantic-load-enable-code-helpers))

(feature color-theme
         (load-theme 'wombat))

(feature eshell
         (require 'eshell)
         (require 'em-smart)
         (setq eshell-where-to-jump 'begin)
         (setq eshell-review-quick-commands nil)
         (setq eshell-smart-space-goes-to-end t)
         
         (defmacro runner-genner (alias command title)
           `(defun ,alias (&rest args)
              (let* ((cmd1 (cons ,command args))
                     (cmd2 (eshell-flatten-and-stringify cmd1))
                     (display-type (framep (selected-frame))))
                (cond
                 ((and (eq display-type 't) (getenv "STY"))
                  (send-string-to-terminal (format "\033]83;screen %s\007" cmd2)))
                 ((eq display-type 'x)
                  (eshell-do-eval (eshell-parse-command (format "rxvt -e %s &" cmd2)))
                  nil)
                 (t
                  (apply 'eshell-exec-visual cmd1))))))
         
         (runner-genner eshell/ss "script/server"  "%SERVER")
         (runner-genner eshell/sc "script/console" "%CONSOLE"))

(feature edit-server
         (server-start))

(feature html5
         (add-path "html5-el")
         (eval-after-load "rng-loc"
           '(add-to-list 'rng-schema-locating-files (concat site-lisp-path "/html5-el/schemas.xml")))
         (require 'whattf-dt))

(feature ido
         (require 'ido)
         (ido-mode t)
         (setq ido-create-new-buffer 'always)
         (setq ido-enable-flex-matching t))

(feature linum
         (require 'linum))

(feature magit
         (add-path "magit")
         (autoload 'magit-status "magit" nil t)
         (global-set-key "\C-qs"    'magit-status)
         (global-set-key "\C-q\C-s" 'magit-status)
         (global-set-key "\C-ql"    'magit-log)
         (global-set-key "\C-q\C-l" 'magit-log)
         (global-set-key "\C-q\C-r" 'magit-goto-next-section)
         (global-set-key "\C-q\C-]" 'magit-toggle-section)
         (global-set-key "\C-qh"    'magit-reflog))

(feature override-copy
         (defun pbcopy ()
           (interactive)
           (shell-command-on-region (point) (mark) "pbcopy"))
         (global-set-key (kbd "s-c") 'pbcopy))

(feature font
;         (set-frame-font "Envy Code R-12"))
         (set-frame-font "Pragmata TT-12"))

(feature rdebug
         (add-path "rdebug")
         (require 'rdebug))

(feature rvm
         (require 'rvm)
         (rvm-use-default))

(feature smart-tab
         (require 'hippie-exp)
         
         (setq hippie-expand-try-functions-list
               '(yas/hippie-try-expand
                 try-expand-dabbrev
                 try-expand-dabbrev-all-buffers
                 try-expand-dabbrev-from-kill
                 try-complete-file-name
                 try-complete-lisp-symbol))
         
         (defun dbl:smart-tab ()
           "If mark is active, indents region. Else if point is at the end of a symbol,
           expands it. Else indents the current line. Acts as normal in minibuffer."
           (interactive)
                                        ;(if (yas/next-field)
                                        ;   ()
           (if (boundp 'ido-cur-item)
               (ido-complete)
             (if (minibufferp)
                 (minibuffer-complete)
               (if mark-active
                   (indent-region (region-beginning) (region-end))
                 (if (and (looking-at "\\_>") (not (looking-at "end")))
                     (hippie-expand nil)
                   (indent-for-tab-command))))))
         
         (global-set-key [(tab)] 'dbl:smart-tab)
         (add-hook 'term-mode-hook '(lambda ()
                                      (local-set-key [(tab)] 'term-send-raw))))


(feature speedbar
         (autoload 'speedbar "speedbar" nil t)
         (eval-after-load "speedbar"
           '(progn (speedbar-disable-update)))
         (global-set-key "\C-c\C-s" 'speedbar))

(feature starter-kit-js
  (require 'starter-kit-js))

(feature timestamp
         ;; When files have "Modified: <>" in their first 8 lines, fill it in on save.
         (add-hook 'before-save-hook 'time-stamp)
         (setq time-stamp-start  "Modified:[   ]+\\\\?[\"<]+")
         (setq time-stamp-end    "\\\\?[\">]")
         (setq time-stamp-format "%:y-%02m-%02d %02H:%02M:%02S %Z"))

(feature yasnippet
         (require 'yasnippet)
         (yas/initialize)
         (yas/load-directory (concat *emacs-config-directory* "/snippets")))

;;-----[ Name/date insertion ]-------------------------------------------------

(defun dbl:sign ()
  (interactive)
  (insert (concat " --" *short-name* "@" 
                  (format-time-string "%Y-%m-%d"))))
(global-set-key "\C-c[" 'dbl:sign)

(defun dbl:insert-name-email ()
  (interactive)
  (insert (concat *user-name* " <" *user-email* ">")))
(global-set-key "\C-ce" 'dbl:insert-name-email)

(defun dbl:insert-date (prefix)
  "Insert the current date. With prefix-argument, use ISO format. With
  two prefix arguments, write out the day and month name."
  (interactive "P")
  (let ((format (cond
        ((not prefix) "%Y-%m-%d")
        ((equal prefix '(4)) "%d.%m.%Y")
        ((equal prefix '(16)) "%A, %d. %B %Y")))
      (system-time-locale "en_US"))
    (insert (format-time-string format))))
(global-set-key "\C-cd" 'dbl:insert-date)

;;-----[ Miscellaneous Keybinds ]----------------------------------------------

(global-set-key "\C-q\C-q" 'quoted-insert)

(global-set-key "\C-q\C-c" 'eshell)
(global-set-key "\C-q0" 'linum-mode)

(global-set-key (kbd "C-,") 'undo)
(global-set-key "\C-h" 'delete-backward-char)


(global-set-key "\C-c\C-r" 'align-regexp)

(put 'scroll-left 'disabled nil)

(defun dbl:dired (&optional arg)
  (interactive "P")
  (if arg
      (ido-dired)
      (dired ".")))

(global-set-key "\C-x\C-d"   'dbl:dired)

(global-set-key "\C-c\C-f"   'fill-region)

;; How did I live without this?
(global-set-key "\C-w"       'backward-kill-word)
(global-set-key "\C-x\C-k"   'kill-region)

;; Select all. Apparently some morons bind this to C-a.
(global-set-key "\C-c\C-a"   'mark-whole-buffer)

(global-set-key "\C-ct"      '(lambda () (interactive) (ansi-term "/bin/zsh")))

;; Alternative to RSI-inducing M-x, and extra insurance.
(global-set-key "\C-xm"      'execute-extended-command)
(global-set-key "\C-cm"      'execute-extended-command)
(global-set-key "\C-x\C-m"   'execute-extended-command)
(global-set-key "\C-c\C-m"   'execute-extended-command)

(global-set-key "\C-x\C-r"   'query-replace-regexp)

(global-set-key "\C-cw"      'toggle-truncate-lines)

(global-set-key "\C-cg"      'goto-line)
(global-set-key "\C-cG"      'goto-char)

;; I'll take "functions that should have keybindings" for 100, Alex.
(global-set-key "\C-cc"      'comment-region)
(global-set-key "\C-cu"      'uncomment-region)

;; Next and previous for grep and compile errors
(global-set-key "\C-cn"      'next-error)
(global-set-key "\C-cp"      'previous-error)

;; Disable right click. yuck.
(global-set-key (kbd "<down-mouse-2>")  '())
(global-set-key (kbd "<mouse-2>")       '())

;;-----[ Autoindent ]----------------------------------------------------------

(defun dbl:set-autoindent (hooks)
  (when hooks
    (add-hook (car hooks)
              (lambda () (local-set-key "\C-m" 'newline-and-indent)))
    (dbl:set-autoindent (cdr hooks))))

(dbl:set-autoindent '(c-mode-common-hook
                      ruby-mode-hook
                      java-mode-hook
                      python-mode-hook
                      lisp-mode-hook
                      yaml-mode-hook))

;;-----[ Autoload and auto-mode ]----------------------------------------------

(autoload 'js2-mode  "js2-mode"  nil t)
(setq js2-basic-offset 2)

(setq-default c-basic-offset 2)

(autoload 'ruby-mode     "ruby-mode" nil t)
(autoload 'haml-mode     "haml-mode" nil t)
(autoload 'markdown-mode "markdown-mode" nil t)
(autoload 'textile-mode  "textile-mode" nil t)
(autoload 'yaml-mode     "yaml-mode" nil t)
(autoload 'sass-mode     "sass-mode" nil t)
(autoload 'coffee-mode   "coffee-mode" nil t)
; (autoload 'mustache-mode "mustache-mode" nil t)

(setq auto-mode-alist
  (nconc
    '(("COMMIT_EDITMSG$"  . diff-mode))
    '(("\\.xml$"          . nxml-mode))
    '(("\\.html$"         . nxml-mode))
    '(("\\.coffee$"       . coffee-mode))
    '(("\\.hbs$"          . mustache-mode))
    '(("\\.m$"            . objc-mode))
    '(("\\.haml$"         . haml-mode))
    '(("\\.scss$"         . css-mode))
    '(("\\.yml$"          . yaml-mode))
    '(("\\.yaml$"         . yaml-mode))
    '(("\\.json$"         . yaml-mode))
    '(("\\.mustache$"     . mustache-mode))
    '(("\\.rb$"           . ruby-mode))
    '(("\\.gemspec$"      . ruby-mode))
    '(("\\.md$"           . markdown-mode))
    '(("\\.textile$"      . textile-mode))
    '(("\\.zsh$"          . sh-mode))
    '(("\\.sass$"         . sass-mode))
    '(("\\.js$"           . js2-mode))
    '(("\\.js.erb$"       . js2-mode))
    '(("\\.j$"            . objj-mode))
    '(("\\.rake$"         . ruby-mode))
    '(("Gemfile$"         . ruby-mode))
    '(("Rakefile$"        . ruby-mode))
    '(("\\.js\\.erb$"     . js2-mode))
    '(("\\.coffee\\.erb$" . coffee-mode))
    auto-mode-alist))

(setq magic-mode-alist ())

;;-----[ Very miscellaneous ]--------------------------------------------------

(when window-system
  (global-unset-key "\C-z"))

(setq tramp-default-method "scpc")

(set-register ?E '(file . "~/.emacs.d/emacs-init.el"))    ;; C-x r j E
(set-register ?Z '(file . "~/.config.d/zsh/zshrc.zsh"))   ;; C-x r j Z
(set-register ?A '(file . "~/.config.d/zsh/aliases.zsh")) ;; C-x r j A

;; Don't ask me 'yes' or 'no'. Ask me 'y' or 'n'.
(fset 'yes-or-no-p 'y-or-n-p)

(defun highlight-todo ()
  (font-lock-add-keywords nil
    '(("\\(REVIEW\\|FIXME\\|TODO\\|BUG\\)" 1 font-lock-warning-face t))))
(add-hook 'c-mode-common-hook 'highlight-todo)
(add-hook 'ruby-mode-hook 'highlight-todo)

(defun yaml-mode-hook ()
  (autoload 'yaml-mode "yaml-mode" nil t)
  (add-to-list 'auto-mode-alist '("\\.yml$" . yaml-mode))
  (add-to-list 'auto-mode-alist '("\\.yaml$" . yaml-mode)))

(defun css-mode-hook ()
  (autoload 'css-mode "css-mode" nil t)
  (add-hook 'css-mode-hook '(lambda ()
                              (setq css-indent-level 2)
                              (setq css-indent-offset 2))))

(global-set-key (kbd "<f8>") 'recompile)

(fset 'ruby-insert-end
      [?e ?n ?d ?  tab backspace return])
(fset 'ruby-method-definition
   [tab ?d ?e ?f ?  ?a return ?e ?n ?d ?  tab backspace ?\C-p ?\C-e backspace])

(global-set-key "\C-x\C-a" '(lambda ()(interactive)(ansi-term "/bin/zsh")))

(when window-system
  (global-set-key (kbd "<s-return>") 'ns-toggle-fullscreen))

(add-hook 'ruby-mode-hook '(lambda ()
                             (local-set-key (kbd "C-i") 'ruby-insert-end)
                             (local-set-key (kbd "C-q C-j") 'ruby-method-definition)))


(setq inhibit-eol-conversion t)
(prefer-coding-system 'utf-8)
(setq locale-coding-system 'utf-8)
(set-terminal-coding-system 'utf-8)
(set-keyboard-coding-system 'utf-8)
(set-selection-coding-system 'utf-8)
(setq file-name-coding-system 'utf-8)
(setq coding-system-for-read 'utf-8)
(setq coding-system-for-write 'utf-8)

;; make zap-to-char act like zap-up-to-char
(defadvice zap-to-char (after my-zap-to-char-advice (arg char) activate)
  "Kill up to the ARG'th occurence of CHAR, and leave CHAR.
  The CHAR is replaced and the point is put before CHAR."
  (insert char)
  (forward-char -1))

