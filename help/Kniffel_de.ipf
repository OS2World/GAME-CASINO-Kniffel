.* Kniffel Hilfe - Deutsch
:userdoc.

:h1 res=001.Allgemeine Hilfe
:font facename=Helv size=8x12.
:p.
Kniffel ist das Wuerfelspiel, das auch als Yahtzee bekannt ist, fuer einen bis fuenf Spieler. Waehlen Sie ein Thema&colon.
:p.
:ul compact.
:li.:link reftype=hd res=002.Spielstart:elink.
:li.:link reftype=hd res=003.Namen und Symbole der Spieler:elink.
:li.:link reftype=hd res=004.Spielen:elink.
:li.:link reftype=hd res=005.Die Regeln:elink.
:li.:link reftype=hd res=006.Ergebnis und Bestenliste:elink.
:li.:link reftype=hd res=007.Tasten:elink.
:li.:link reftype=hd res=008.Menues und Optionen:elink.
:li.:link reftype=hd res=009.Ueber Kniffel und Lizenz:elink.
:eul.
:p.

:h1 res=002.Spielstart
:font facename=Helv size=8x12.
:p.
Waehlen Sie :hp2.Spiel - Neues Spiel:ehp2. (Ctrl+N). Im Fenster Neues Spiel legen Sie die Anzahl der Spieler fest, von eins bis fuenf, und geben Namen und Symbol jedes Spielers ein.
:p.
:hp2.Spielen:ehp2. startet das Spiel. :hp2.Bestenliste:ehp2. zeigt die gesicherten Ergebnisse alter Spiele; der Knopf ist nur verfuegbar, wenn Ergebnisse gesichert sind. :hp2.Schliessen:ehp2. schliesst das Fenster.

:h1 res=003.Namen und Symbole der Spieler
:font facename=Helv size=8x12.
:p.
Jeder Spieler gibt einen Namen mit bis zu 12 Zeichen ein und waehlt ein Symbol. Der vorgeschlagene Name ist markiert, die erste getippte Taste ersetzt ihn also.
:p.
Mit den beiden Pfeilknoepfen neben dem Symbol blaettern Sie durch die Symbole. Die Symbole sind die Icons im Ordner :hp2.icons:ehp2. neben Kniffel.exe. Gibt es weniger als fuenf, ergaenzt das Programm einige eigene. Kinder erkennen sich gern an einem Lieblingssymbol, Sie koennen also weitere Icons in den Ordner kopieren.

:h1 res=004.Spielen
:font facename=Helv size=8x12.
:p.
Das Fenster zeigt eine Infozeile, die fuenf Wuerfel, rechts die Befehlsknoepfe und unten die Punktetabelle mit einer Spalte je Spieler. Die Spalte des Spielers, der an der Reihe ist, hat eine gelbe Ueberschrift.
:p.
:dl tsize=18.
:dt.:hp2.Wuerfeln:ehp2.
:dd.Wuerfelt alle Wuerfel, die nicht gehalten werden. Ein Spieler darf dreimal pro Runde wuerfeln.
:dt.Klick auf einen Wuerfel
:dd.Haelt den Wuerfel (er wird invertiert gezeigt) oder gibt ihn wieder frei. Gehaltene Wuerfel werden nicht gewuerfelt.
:dt.:hp2.Alle aendern:ehp2.
:dd.Haelt alle freien Wuerfel und gibt alle gehaltenen frei.
:dt.Klick auf ein freies Feld
:dd.Traegt die Punkte fuer die aktuellen Wuerfel in dieses Feld der Tabelle ein. Das ist nach dem ersten Wurf moeglich.
:dt.:hp2.Zuruecknehmen:ehp2.
:dd.Nimmt den Eintrag zurueck, solange Naechster Spieler nicht gedrueckt wurde. Danach ist kein Wuerfeln mehr moeglich.
:dt.:hp2.Naechster Spieler:ehp2.
:dd.Gibt an den naechsten Spieler weiter.
:dt.:hp2.Abbruch:ehp2.
:dd.Beendet das Spiel ohne Ergebnis und kehrt zum Start zurueck.
:edl.

:h1 res=005.Die Regeln
:font facename=Helv size=8x12.
:p.
Jeder Spieler fuellt die 13 Felder der Tabelle, eines pro Runde.
:ul compact.
:li.Einer bis Sechser&colon. mindestens drei gleiche Wuerfel sind noetig; nur die gleichen Wuerfel zaehlen, sonst erhaelt das Feld null.
:li.Bonus&colon. eine Summe von 63 oder mehr im oberen Teil bringt 35 Punkte. Das Summenfeld zeigt ein Minuszeichen, bis 63 erreicht sind.
:li.Drilling und Vierling&colon. drei bzw. vier gleiche Wuerfel sind noetig; dann zaehlen alle fuenf Wuerfel.
:li.Full House&colon. drei gleiche Wuerfel und ein Paar, 25 Punkte.
:li.Kleine Strasse&colon. vier Augenzahlen in Folge, 30 Punkte.
:li.Grosse Strasse&colon. fuenf Augenzahlen in Folge (12345 oder 23456), 40 Punkte.
:li.Kniffel&colon. fuenf gleiche Wuerfel, 50 Punkte.
:li.Chance&colon. beliebige Wuerfel, alle fuenf zaehlen.
:eul.
:p.
Es gewinnt der Spieler mit der hoechsten Gesamtpunktzahl.

:h1 res=006.Ergebnis und Bestenliste
:font facename=Helv size=8x12.
:p.
Sind alle Felder aller Spieler gefuellt, wird das Ergebnis mit dem Gewinner und den Verlierern gezeigt. :hp2.Ergebnis speichern:ehp2. haengt das Ergebnis an die Datei :hp2.hitlist.hgh:ehp2. im Arbeitsverzeichnis an. :hp2.Weiterspielen:ehp2. startet ein neues Spiel mit denselben Spielern, :hp2.Zurueck:ehp2. kehrt zum Start zurueck.
:p.
:hp2.Spiel - Bestenliste:ehp2. (Ctrl+H) zeigt die gesicherten Ergebnisse. Mit :hp2.Liste loeschen:ehp2. loeschen Sie die Datei nach einer Rueckfrage.

:h1 res=007.Tasten
:font facename=Helv size=8x12.
:p.
:parml compact tsize=14 break=none.
:pt.Leertaste
:pd.Wuerfeln
:pt.1 bis 5
:pd.Wuerfel 1 bis 5 halten / freigeben
:pt.I
:pd.Alle aendern
:pt.Eingabe
:pd.Naechster Spieler
:pt.Rueck
:pd.Zuruecknehmen
:pt.Ctrl+N
:pd.Neues Spiel
:pt.Ctrl+Q
:pd.Aktuelles Spiel abbrechen
:pt.Ctrl+H
:pd.Bestenliste
:pt.Ctrl+B
:pd.Bilder auf Knoepfen ein / aus
:pt.Ctrl+F
:pd.Rahmenelemente ein / aus
:pt.Ctrl+X
:pd.Beenden
:eparml.

:h1 res=008.Menues und Optionen
:font facename=Helv size=8x12.
:p.
:dl tsize=18.
:dt.:hp2.Spiel:ehp2.
:dd.Neues Spiel, Spiel abbrechen (beendet das Spiel ohne Ergebnis), Bestenliste und Beenden.
:dt.:hp2.Bilder auf Knoepfen:ehp2.
:dd.Zeigt Bilder statt Text auf den Knoepfen und in der Tabelle. Bilder sind fuer kleine Kinder am besten.
:dt.:hp2.Sprache:ehp2.
:dd.Englisch, Spanisch, Niederlaendisch, Deutsch, Franzoesisch oder Italienisch. Menues, Fenster, Dialoge und diese Hilfe wechseln sofort.
:dt.:hp2.Rahmenelemente:ehp2. (Ctrl+F)
:dd.Blendet die Titelleiste und das Menue aus oder ein.
:dt.:hp2.Beim Beenden Einstellungen sichern:ehp2.
:dd.Speichert die Einstellungen beim Beenden in Kniffel.cfg.
:edl.

:h1 res=009.Ueber Kniffel und Lizenz
:font facename=Helv size=8x12.
:p.
Kniffel wurde zwischen 1996 und 1999 von Andreas Kieser fuer OS/2 in VisPro/REXX geschrieben und als Freeware veroeffentlicht. Die Open-Watcom-Version in C wurde 2026 von der OS2World-Gemeinschaft erstellt.
:p.
Kniffel ist freie Software&colon. Sie koennen es unter den Bedingungen der GNU General Public License, wie von der Free Software Foundation veroeffentlicht, weitergeben und/oder aendern, entweder gemaess Version 3 der Lizenz oder (nach Ihrer Wahl) jeder spaeteren Version. Es wird in der Hoffnung verbreitet, dass es nuetzlich ist, aber OHNE JEDE GEWAEHRLEISTUNG. Siehe die Datei LICENSE.txt.

:euserdoc.
