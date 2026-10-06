Kniffel for OS/2 - Version 1.10
===============================

OVERVIEW
--------
Kniffel is the German name of the dice game Yahtzee. This is a game for one
to five players on the OS/2 Presentation Manager. Each player has a column in
the score table and fills its 13 fields, one per turn, with up to three rolls
of five dice.

Original program: Andreas Kieser, 1996-1999 (VisPro/REXX, freeware, German).
Rewritten in C for Open Watcom (ArcaOS / OS/2 Warp 4) by the OS2World
community, 2026. The rules, the player symbols and the hit list follow the
original program.

HOW TO PLAY
-----------
Choose Game - New Game (Ctrl+N), select the number of players (1 to 5) and
enter a name and choose a symbol for each player in the same window.

On your turn press Roll. Click dice to hold them (they are shown inverted),
roll again (three rolls at most), then click a free field of your column to
enter the points. Press Next player to hand over; before that you can take
the entry back. When every player has filled all 13 fields the result is shown
and can be saved to the hit list.

RULES
-----
  Ones to Sixes     at least three equal dice needed; only the equal dice
                    count, otherwise the field gets zero
  Bonus             35 points for 63 or more in the upper section (the sum
                    field shows a minus sign until 63 is reached)
  Three of a kind   three equal dice, all five dice count
  Four of a kind    four equal dice, all five dice count
  Full house        three equal dice and a pair, 25 points
  Small straight    four numbers in a row, 30 points
  Large straight    12345 or 23456, 40 points
  Kniffel           five equal dice, 50 points
  Chance            any dice, all five count

CONTROLS
--------
Mouse: click a die to hold it, click the buttons on the right, click a free
field of your column to enter the points.

  Space      Roll
  1 to 5     Hold / release die 1 to 5
  I          Invert all dice
  Enter      Next player
  Backspace  Take back the entry
  Ctrl+N     New game
  Ctrl+Q     Quit the current game
  Ctrl+H     High scores (hit list)
  Ctrl+B     Picture Buttons on / off (off by default)
  Ctrl+F     Frame Controls on / off (hides title bar and menu)
  Ctrl+X     Exit

MENUS
-----
  Game      New Game, Quit Game, High Scores, Exit
  Options   Picture Buttons (pictures or text on buttons and rows), Language,
            Frame Controls, Save settings on exit
  Help      General Help, Help Index, Help on Help, About

Languages: English, Spanish, Dutch, German, French and Italian. Menus,
windows, dialogs and the online help switch at run time.

PLAYER SYMBOLS
--------------
The symbols are the icon files (*.ICO) in the "icons" folder next to
Kniffel.exe. Copy your favourite icons there. With fewer than five icons the
program adds five of its own.

FILE LIST
---------
  Kniffel.exe          The game
  help\Kniffel_en.hlp  Online help, one file per language: en, es, nl, de, fr, it
  icons\*.ico          Player symbols
  Readme.txt, Changelog.txt, LICENSE.txt

  Created by the game in the working directory:
  Kniffel.cfg          Settings
  hitlist.hgh          Saved results (text file)

DISCLAIMER
----------
Kniffel is free software under the GNU General Public License v3, WITHOUT ANY
WARRANTY. See LICENSE.txt.

AUTHOR
------
Original game: Andreas Kieser (1996-1999).
OS/2 Open Watcom port: OS2World community (2026).