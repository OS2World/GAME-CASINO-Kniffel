/* Kniffel - language table. ASCII only (no accents), see plan section 8.6.
   Order of the strings must match the enum in lang.h. */

#include "lang.h"

int current_lang = LANG_EN;

const char *lang_strings[LANG_COUNT][STR_COUNT] = {

/* ======================= LANG_EN ======================= */
{
    "~Game", "~New Game\tCtrl+N", "~Quit Game\tCtrl+Q", "~High Scores...\tCtrl+H", "E~xit\tCtrl+X",
    "~Options", "~Picture Buttons\tCtrl+B", "~Language", "~Frame Controls\tCtrl+F",
    "~Save settings on exit", "~Help", "~General Help", "Help ~Index",
    "~Help on Help", "~About...",
    "Ones", "Twos", "Threes", "Fours", "Fives", "Sixes", "Sum upper",
    "Three of a kind", "Four of a kind", "Full house", "Small straight", "Large straight",
    "Kniffel", "Chance", "Sum lower", "Total",
    "Roll", "Invert all", "Next player", "Take back", "Abort",
    "%s: press Roll to start your turn",
    "%s: roll %d of 3 - click dice to hold them, roll again or click a free field",
    "%s: press Next player, or take the entry back",
    "New Game", "Number of players", "~Play", "~High Scores", "~Close",
    "Player %d of %d", "Name:", "Symbol:", "~Ok", "Player %d",
    "Result", "Winner:", "Losers:", "(with bonus)", "~Save result", "Play ~again", "~Back",
    "Result of %s at %s:",
    "High Scores", "~Delete list", "No results saved yet.", "Delete the high score list?",
    "Quit the current game?",
    "Kniffel Help", "The help file %s was not found.\nPlease put it in the help folder next to Kniffel.exe.",
    "Choose Game - New Game to start playing"
},

/* ======================= LANG_ES ======================= */
{
    "~Juego", "~Nuevo juego\tCtrl+N", "~Abandonar juego\tCtrl+Q", "~Mejores resultados...\tCtrl+H", "~Salir\tCtrl+X",
    "~Opciones", "~Botones con imagen\tCtrl+B", "~Idioma", "~Controles de marco\tCtrl+F",
    "~Guardar al salir", "A~yuda", "Ayuda ~general", "~Indice de ayuda",
    "Ayuda ~sobre ayuda", "~About...",
    "Unos", "Doses", "Treses", "Cuatros", "Cincos", "Seises", "Suma superior",
    "Trio", "Poker", "Full", "Escalera menor", "Escalera mayor",
    "Kniffel", "Chance", "Suma inferior", "Total",
    "Tirar", "Invertir todos", "Siguiente jugador", "Deshacer", "Abandonar",
    "%s: pulse Tirar para empezar su turno",
    "%s: tirada %d de 3 - pulse los dados para retenerlos, tire otra vez o pulse un campo libre",
    "%s: pulse Siguiente jugador o deshaga la anotacion",
    "Nuevo juego", "Numero de jugadores", "~Jugar", "~Mejores resultados", "~Cerrar",
    "Jugador %d de %d", "Nombre:", "Simbolo:", "~Aceptar", "Jugador %d",
    "Resultado", "Ganador:", "Perdedores:", "(con bonus)", "~Guardar resultado", "Jugar de ~nuevo", "~Volver",
    "Resultado del %s a las %s:",
    "Mejores resultados", "~Borrar lista", "Todavia no hay resultados guardados.", "Borrar la lista de mejores resultados?",
    "Abandonar el juego actual?",
    "Ayuda de Kniffel", "No se encontro el archivo de ayuda %s.\nColoquelo en la carpeta help junto a Kniffel.exe.",
    "Elija Juego - Nuevo juego para empezar a jugar"
},

/* ======================= LANG_NL ======================= */
{
    "~Spel", "~Nieuw spel\tCtrl+N", "S~top spel\tCtrl+Q", "~Hoogste scores...\tCtrl+H", "~Afsluiten\tCtrl+X",
    "~Opties", "~Knoppen met plaatjes\tCtrl+B", "~Taal", "Kader~bediening\tCtrl+F",
    "Instellingen o~pslaan bij afsluiten", "~Help", "Al~gemene Help", "Help-~index",
    "Help ~over Help", "~About...",
    "Enen", "Twees", "Dries", "Viers", "Vijfs", "Zessen", "Som boven",
    "Driemaal", "Viermaal", "Full house", "Kleine straat", "Grote straat",
    "Kniffel", "Kans", "Som onder", "Totaal",
    "Gooien", "Alles omkeren", "Volgende speler", "Terugnemen", "Afbreken",
    "%s: druk op Gooien om uw beurt te beginnen",
    "%s: worp %d van 3 - klik op dobbelstenen om ze vast te houden, gooi opnieuw of klik op een vrij veld",
    "%s: druk op Volgende speler of neem de invoer terug",
    "Nieuw spel", "Aantal spelers", "~Spelen", "~Hoogste scores", "~Sluiten",
    "Speler %d van %d", "Naam:", "Symbool:", "~Ok", "Speler %d",
    "Resultaat", "Winnaar:", "Verliezers:", "(met bonus)", "Resultaat ~opslaan", "Opnieuw ~spelen", "~Terug",
    "Resultaat van %s om %s:",
    "Hoogste scores", "Lijst ~wissen", "Nog geen resultaten opgeslagen.", "De lijst met hoogste scores wissen?",
    "Het huidige spel afbreken?",
    "Kniffel Help", "Het helpbestand %s is niet gevonden.\nPlaats het in de map help naast Kniffel.exe.",
    "Kies Spel - Nieuw spel om te beginnen"
},

/* ======================= LANG_DE ======================= */
{
    "~Spiel", "~Neues Spiel\tCtrl+N", "Spiel a~bbrechen\tCtrl+Q", "Be~stenliste...\tCtrl+H", "Be~enden\tCtrl+X",
    "~Optionen", "~Bilder auf Knoepfen\tCtrl+B", "~Sprache", "~Rahmenelemente\tCtrl+F",
    "Beim Beenden Einstellungen s~ichern", "~Hilfe", "Allgemeine ~Hilfe", "Hilfe~index",
    "Hilfe ~zur Hilfe", "~About...",
    "Einer", "Zweier", "Dreier", "Vierer", "Fuenfer", "Sechser", "Summe oben",
    "Drilling", "Vierling", "Full House", "Kleine Strasse", "Grosse Strasse",
    "Kniffel", "Chance", "Summe unten", "Gesamt",
    "Wuerfeln", "Alle aendern", "Naechster Spieler", "Zuruecknehmen", "Abbruch",
    "%s: Zum Beginn der Runde auf Wuerfeln druecken",
    "%s: Wurf %d von 3 - Wuerfel anklicken zum Halten, nochmal wuerfeln oder ein freies Feld anklicken",
    "%s: Naechster Spieler druecken oder Eintrag zuruecknehmen",
    "Neues Spiel", "Anzahl der Spieler", "~Spielen", "~Bestenliste", "S~chliessen",
    "Spieler %d von %d", "Name:", "Symbol:", "~Ok", "Spieler %d",
    "Ergebnis", "Gewinner:", "Verlierer:", "(mit Bonus)", "Ergebnis ~speichern", "~Weiterspielen", "~Zurueck",
    "Ergebnis vom %s um %s Uhr:",
    "Bestenliste", "Liste ~loeschen", "Noch keine Ergebnisse gespeichert.", "Die Bestenliste loeschen?",
    "Das aktuelle Spiel abbrechen?",
    "Kniffel Hilfe", "Die Hilfedatei %s wurde nicht gefunden.\nBitte legen Sie sie in den Ordner help neben Kniffel.exe.",
    "Waehlen Sie Spiel - Neues Spiel zum Starten"
},

/* ======================= LANG_FR ======================= */
{
    "~Jeu", "~Nouveau jeu\tCtrl+N", "~Quitter la partie\tCtrl+Q", "~Meilleurs scores...\tCtrl+H", "~Sortir\tCtrl+X",
    "~Options", "~Boutons avec images\tCtrl+B", "~Langue", "~Controles du cadre\tCtrl+F",
    "~Enregistrer en quittant", "~Aide", "Aide ~generale", "~Index de l'aide",
    "Aide ~sur l'aide", "~About...",
    "As", "Deux", "Trois", "Quatre", "Cinq", "Six", "Total haut",
    "Brelan", "Carre", "Full", "Petite suite", "Grande suite",
    "Kniffel (Yams)", "Chance", "Total bas", "Total general",
    "Lancer", "Tout inverser", "Joueur suivant", "Annuler", "Abandonner",
    "%s: appuyez sur Lancer pour commencer votre tour",
    "%s: lancer %d sur 3 - cliquez sur les des pour les garder, relancez ou cliquez sur une case libre",
    "%s: appuyez sur Joueur suivant ou annulez la saisie",
    "Nouveau jeu", "Nombre de joueurs", "~Jouer", "~Meilleurs scores", "~Fermer",
    "Joueur %d sur %d", "Nom:", "Symbole:", "~Ok", "Joueur %d",
    "Resultat", "Gagnant:", "Perdants:", "(avec bonus)", "~Enregistrer le resultat", "~Rejouer", "Re~tour",
    "Resultat du %s a %s:",
    "Meilleurs scores", "~Effacer la liste", "Aucun resultat enregistre pour l'instant.", "Effacer la liste des meilleurs scores?",
    "Abandonner la partie en cours?",
    "Aide de Kniffel", "Le fichier d'aide %s est introuvable.\nPlacez-le dans le dossier help a cote de Kniffel.exe.",
    "Choisissez Jeu - Nouveau jeu pour commencer"
},

/* ======================= LANG_IT ======================= */
{
    "~Gioco", "~Nuovo gioco\tCtrl+N", "~Termina gioco\tCtrl+Q", "~Record...\tCtrl+H", "~Esci\tCtrl+X",
    "~Opzioni", "~Pulsanti con immagini\tCtrl+B", "~Lingua", "Controlli ~cornice\tCtrl+F",
    "Sal~va impostazioni all'uscita", "A~iuto", "Guida ~generale", "~Indice della guida",
    "Guida ~sulla guida", "~About...",
    "Uno", "Due", "Tre", "Quattro", "Cinque", "Sei", "Somma alta",
    "Tris", "Poker", "Full", "Scala piccola", "Scala grande",
    "Kniffel (Yahtzee)", "Chance", "Somma bassa", "Totale",
    "Tira", "Inverti tutti", "Prossimo giocatore", "Annulla", "Abbandona",
    "%s: premi Tira per iniziare il turno",
    "%s: lancio %d di 3 - clicca sui dadi per tenerli, tira ancora o clicca un campo libero",
    "%s: premi Prossimo giocatore o annulla la scelta",
    "Nuovo gioco", "Numero di giocatori", "~Gioca", "~Record", "~Chiudi",
    "Giocatore %d di %d", "Nome:", "Simbolo:", "~Ok", "Giocatore %d",
    "Risultato", "Vincitore:", "Perdenti:", "(con bonus)", "~Salva risultato", "Gioca ~ancora", "~Indietro",
    "Risultato del %s alle %s:",
    "Record", "~Cancella elenco", "Nessun risultato salvato finora.", "Cancellare l'elenco dei record?",
    "Abbandonare la partita in corso?",
    "Guida di Kniffel", "Il file della guida %s non e' stato trovato.\nMetterlo nella cartella help accanto a Kniffel.exe.",
    "Scegli Gioco - Nuovo gioco per iniziare"
}

};
