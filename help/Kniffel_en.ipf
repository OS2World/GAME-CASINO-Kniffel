.* Kniffel help - English
:userdoc.

:h1 res=001.General Help
:font facename=Helv size=8x12.
:p.
Kniffel is the dice game known as Yahtzee, for one to five players. Choose a topic&colon.
:p.
:ul compact.
:li.:link reftype=hd res=002.Starting a game:elink.
:li.:link reftype=hd res=003.Player names and symbols:elink.
:li.:link reftype=hd res=004.Playing:elink.
:li.:link reftype=hd res=005.The rules:elink.
:li.:link reftype=hd res=006.Results and high scores:elink.
:li.:link reftype=hd res=007.Keys:elink.
:li.:link reftype=hd res=008.Menus and options:elink.
:li.:link reftype=hd res=009.About Kniffel and license:elink.
:eul.
:p.

:h1 res=002.Starting a game
:font facename=Helv size=8x12.
:p.
Choose :hp2.Game - New Game:ehp2. (Ctrl+N). In the New Game window select the number of players, from one to five, and enter the name and symbol of each player.
:p.
:hp2.Play:ehp2. starts the game. :hp2.High Scores:ehp2. shows the saved results of old games; the button is only available when results have been saved. :hp2.Close:ehp2. leaves the window.

:h1 res=003.Player names and symbols
:font facename=Helv size=8x12.
:p.
Every player enters a name of up to 12 characters and chooses a symbol. The suggested name is marked, so the first key you type replaces it.
:p.
Use the two arrow buttons beside the symbol to look through the symbols. The symbols are the icons found in the :hp2.icons:ehp2. folder next to Kniffel.exe. If there are fewer than five, the program adds some of its own. Children like to recognize themselves by a favourite symbol, so you may copy more icons into the folder.

:h1 res=004.Playing
:font facename=Helv size=8x12.
:p.
The window shows an information line, the five dice, the command buttons on the right and the score table at the bottom, with one column per player. The column of the player whose turn it is has a yellow heading.
:p.
:dl tsize=18.
:dt.:hp2.Roll:ehp2.
:dd.Rolls all dice that are not held. A player may roll three times per turn.
:dt.Click on a die
:dd.Holds the die (it is shown inverted) or releases it again. Held dice are not rolled.
:dt.:hp2.Invert all:ehp2.
:dd.Holds all free dice and releases all held dice.
:dt.Click on a free field
:dd.Enters the points for the current dice into that field of the table. This is possible after the first roll.
:dt.:hp2.Take back:ehp2.
:dd.Cancels the entry, as long as Next player has not been pressed. Rolling is no longer possible then.
:dt.:hp2.Next player:ehp2.
:dd.Hands over to the next player.
:dt.:hp2.Abort:ehp2.
:dd.Ends the game without a result and returns to the start.
:edl.

:h1 res=005.The rules
:font facename=Helv size=8x12.
:p.
Each player fills the 13 fields of the table, one per turn.
:ul compact.
:li.Ones to Sixes&colon. at least three equal dice are needed; only the equal dice count, otherwise the field gets zero.
:li.Bonus&colon. a sum of 63 or more in the upper section adds 35 points. The sum field shows a minus sign until 63 is reached.
:li.Three of a kind and Four of a kind&colon. three or four equal dice are needed; then all five dice count.
:li.Full house&colon. three equal dice and a pair, 25 points.
:li.Small straight&colon. four numbers in a row, 30 points.
:li.Large straight&colon. five numbers in a row (12345 or 23456), 40 points.
:li.Kniffel&colon. five equal dice, 50 points.
:li.Chance&colon. any dice, all five count.
:eul.
:p.
The player with the highest total wins.

:h1 res=006.Results and high scores
:font facename=Helv size=8x12.
:p.
When all fields of all players are filled, the result is shown with the winner and the others. :hp2.Save result:ehp2. appends the result to the file :hp2.hitlist.hgh:ehp2. in the working directory. :hp2.Play again:ehp2. starts a new game with the same players, :hp2.Back:ehp2. returns to the start.
:p.
:hp2.Game - High Scores:ehp2. (Ctrl+H) shows the saved results. With :hp2.Delete list:ehp2. you delete the file after a confirmation.

:h1 res=007.Keys
:font facename=Helv size=8x12.
:p.
:parml compact tsize=14 break=none.
:pt.Space
:pd.Roll
:pt.1 to 5
:pd.Hold / release die 1 to 5
:pt.I
:pd.Invert all
:pt.Enter
:pd.Next player
:pt.Backspace
:pd.Take back
:pt.Ctrl+N
:pd.New game
:pt.Ctrl+Q
:pd.Quit the current game
:pt.Ctrl+H
:pd.High scores
:pt.Ctrl+B
:pd.Picture buttons on / off
:pt.Ctrl+F
:pd.Frame controls on / off
:pt.Ctrl+X
:pd.Exit
:eparml.

:h1 res=008.Menus and options
:font facename=Helv size=8x12.
:p.
:dl tsize=18.
:dt.:hp2.Game:ehp2.
:dd.New Game, Quit Game (ends the game without a result), High Scores and Exit.
:dt.:hp2.Picture Buttons:ehp2.
:dd.Shows pictures instead of text on the buttons and in the table. Pictures are best for small children.
:dt.:hp2.Language:ehp2.
:dd.English, Spanish, Dutch, German, French or Italian. Menus, windows, dialogs and this help change at once.
:dt.:hp2.Frame Controls:ehp2. (Ctrl+F)
:dd.Hides or shows the title bar and the menu.
:dt.:hp2.Save settings on exit:ehp2.
:dd.Saves the settings in Kniffel.cfg when you exit.
:edl.

:h1 res=009.About Kniffel and license
:font facename=Helv size=8x12.
:p.
Kniffel was written for OS/2 in VisPro/REXX by Andreas Kieser between 1996 and 1999, and released as freeware. The Open Watcom version in C was prepared by the OS2World community in 2026.
:p.
Kniffel is free software&colon. you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. It is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY. See the file LICENSE.txt.

:euserdoc.
