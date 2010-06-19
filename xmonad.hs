import qualified XMonad.StackSet as W
import System.Exit
import XMonad
import qualified Data.Map as M
import Graphics.X11.Xlib
import XMonad.Util.EZConfig
import Data.List
import XMonad.Hooks.DynamicLog
import System.IO 
import XMonad.Util.Run
import XMonad.Hooks.ManageDocks
import XMonad.Util.EZConfig
--import XMonad.Layout.SimplestFloat

main = do

	xmonad $ defaultConfig
		{ borderWidth        = 0
		, terminal           = "urxvtc -name URxvt.india"
		, normalBorderColor  = "#030303"
		, focusedBorderColor = "#ee0732" 
		, keys 				       = myKeys
		, layoutHook         = myLayout
		, manageHook         = manageDocks
		} 


myLayout = avoidStruts (tall ||| Mirror tall )
                 where  tall = Tall 1 (3/100) (1/2)


myKeys = \c -> mkKeymap c $
  [ ("C-f c", spawn "urxvtc -name URxvt.india")
   ,("C-f e", spawn "sh $HOME/bin/dmenu.sh")
   
  -- ,("C-f h", windows W.focusLeft)
   ,("C-f j", windows W.focusDown)
   ,("C-f k", windows W.focusUp)
  -- ,("C-f l", windows W.focusRight)
  ]

--myKeys conf@(XConfig {XMonad.modMask = modm}) = M.fromList $
--	[ ((modm .|. shiftMask, xK_Return), spawn $ XMonad.terminal conf)
--	, ((modm,               xK_p     ), spawn "exe=`dmenu_path | dmenu` && eval \"exec $exe\"")
--	, ((modm,               xK_a     ), spawn "mpc pause")
--	, ((modm,               xK_o     ), spawn "mpc play")
--	, ((modm,               xK_e     ), spawn "mpc prev")
--	, ((modm,               xK_u     ), spawn "mpc next")
--	, ((modm              , xK_b     ), sendMessage ToggleStruts)
--	, ((modm .|. shiftMask, xK_c     ), kill)
--	, ((modm,               xK_space ), sendMessage NextLayout)
--	, ((modm,               xK_j     ), windows W.focusDown)
--	, ((modm,               xK_k     ), windows W.focusUp  )
--	, ((modm,               xK_Return), windows W.swapMaster)
--	, ((modm .|. shiftMask, xK_j     ), windows W.swapDown  )
--	, ((modm .|. shiftMask, xK_k     ), windows W.swapUp    )
--  , ((modm,               xK_h     ), windows W.focusLeft)
--  , ((modm,               xK_l     ), windows W.focusRight)
--	, ((modm,.|. shiftMask, xK_h     ), sendMessage Shrink)
--	, ((modm,.|. shiftMask, xK_l     ), sendMessage Expand)
--	, ((modm,               xK_t     ), withFocused $ windows . W.sink)
--	, ((modm              , xK_comma ), sendMessage (IncMasterN 1))
--	, ((modm              , xK_period), sendMessage (IncMasterN (-1)))
--	, ((modm .|. shiftMask, xK_q     ), io (exitWith ExitSuccess))
--	, ((modm              , xK_q     ), spawn "xmonad --recompile; xmonad --restart")
--	]
