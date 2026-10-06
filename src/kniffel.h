/* Kniffel - resource identifiers (also read by the resource compiler) */

#ifndef KNIFFEL_H
#define KNIFFEL_H

#define VERSION_STR "1.10"

/* Window / resource identifiers */
#define WID_MAIN        1000

/* Game menu (100-199) */
#define IDM_NEWGAME     101
#define IDM_QUIT        102
#define IDM_HITLIST     103
#define IDM_EXIT        104

/* Options menu (200-299) */
#define IDM_PICTURES    201
#define IDM_FRAME       221
#define IDM_SAVEONEXIT  230

/* Language items (300-399) */
#define IDM_LANG_EN     300
#define IDM_LANG_ES     301
#define IDM_LANG_NL     302
#define IDM_LANG_DE     303
#define IDM_LANG_FR     304
#define IDM_LANG_IT     305

/* Help menu (900-999) */
#define IDM_GENERALHELP 901
#define IDM_HELPINDEX   902
#define IDM_HELPONHELP  903
#define IDM_ABOUT       999

/* Submenu cascade identifiers (1000-1099) */
#define IDM_SUBMENU_GAME     1001
#define IDM_SUBMENU_OPTIONS  1004
#define IDM_SUBMENU_HELP     1006
#define IDM_SUBMENU_LANGUAGE 1008

/* Dice bitmaps: 100 = blank, 101..106 = 1..6, 107..112 = 1..6 held */
#define BID_DICE        100

/* Row bitmaps (one, two ... six, three of a kind ... chance) 201..213 */
#define BID_ROW         200

/* Command bitmaps */
#define BID_ABORT       220
#define BID_INVERT      221
#define BID_ROLL        222
#define BID_NEXT        223
#define BID_UNDO        224
#define BID_WINNER      225

/* Default player icons 301..305 */
#define PID_DEFAULT     300

/* Dialogs */
#define IDD_ABOUT       434
#define IDD_START       500
#define IDD_NAMES       510
#define IDD_RESULT      520
#define IDD_HITLIST     530

/* Start dialog */
#define ID_PLAYERS_GRP  501
#define ID_PLAYERS_1    502
#define ID_PLAYERS_2    503
#define ID_PLAYERS_3    504
#define ID_PLAYERS_4    505
#define ID_PLAYERS_5    506
#define ID_HITBTN       507
#define ID_COL_NAME     508
#define ID_COL_SYMBOL   509
#define ID_PL_LBL       580
#define ID_PL_NAME      540
#define ID_PL_ICON      550
#define ID_PL_PREV      560
#define ID_PL_NEXT      570

/* Names dialog */
#define ID_NAME_LBL     511
#define ID_NAME_EDIT    512
#define ID_ICON_LBL     513
#define ID_ICON_PIC     514
#define ID_ICON_PREV    515
#define ID_ICON_NEXT    516

/* Result dialog */
#define ID_RES_TEXT     521
#define ID_RES_LIST     522
#define ID_RES_SAVE     523

/* Hit list dialog */
#define ID_HIT_LIST     531
#define ID_HIT_DELETE   532
#define ID_HIT_EMPTY    533

/* Help panels */
#define HID_MAIN         432
#define HID_SUBTABLE     433
#define HID_GENERAL        1
#define HID_START          2
#define HID_NAMES          3
#define HID_PLAYING        4
#define HID_RULES          5
#define HID_RESULT         6
#define HID_KEYS           7
#define HID_MENUS          8
#define HID_ABOUT          9

#endif /* KNIFFEL_H */
