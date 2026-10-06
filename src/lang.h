/* Kniffel - run time language support (see standardization plan, section 8) */

#ifndef LANG_H
#define LANG_H

#define LANG_EN  0
#define LANG_ES  1
#define LANG_NL  2
#define LANG_DE  3
#define LANG_FR  4
#define LANG_IT  5
#define LANG_COUNT 6

enum {
    /* menus */
    STR_MENU_GAME = 0, STR_MENU_NEW, STR_MENU_QUIT, STR_MENU_HITLIST, STR_MENU_EXIT,
    STR_MENU_OPTIONS, STR_MENU_PICTURES, STR_MENU_LANGUAGE, STR_MENU_FRAME,
    STR_MENU_SAVEONEXIT, STR_MENU_HELP, STR_MENU_GENHELP, STR_MENU_HELPINDEX,
    STR_MENU_HELPONHELP, STR_MENU_ABOUT,
    /* score table rows */
    STR_ROW1, STR_ROW2, STR_ROW3, STR_ROW4, STR_ROW5, STR_ROW6, STR_ROW_SUMUP,
    STR_ROW_3KIND, STR_ROW_4KIND, STR_ROW_FULL, STR_ROW_SMALL, STR_ROW_LARGE,
    STR_ROW_KNIFFEL, STR_ROW_CHANCE, STR_ROW_SUMLOW, STR_ROW_TOTAL,
    /* command buttons */
    STR_BTN_ROLL, STR_BTN_INVERT, STR_BTN_NEXT, STR_BTN_UNDO, STR_BTN_ABORT,
    /* information line */
    STR_INFO_START, STR_INFO_ROLLED, STR_INFO_PLACED,
    /* start dialog */
    STR_DLG_START_TITLE, STR_DLG_PLAYERS, STR_DLG_PLAY, STR_DLG_HITLIST, STR_DLG_CLOSE,
    /* names dialog */
    STR_DLG_NAMES_TITLE, STR_DLG_NAME, STR_DLG_SYMBOL, STR_DLG_OK, STR_DEFAULT_NAME,
    /* result dialog */
    STR_DLG_RESULT_TITLE, STR_RES_WINNER, STR_RES_LOSERS, STR_RES_BONUS,
    STR_RES_SAVE, STR_RES_AGAIN, STR_RES_BACK, STR_RES_HEADER,
    /* hit list dialog and questions */
    STR_HIT_TITLE, STR_HIT_DELETE, STR_HIT_EMPTY, STR_HIT_DELASK, STR_QUITASK,
    /* help and idle screen */
    STR_HELP_TITLE, STR_HELP_MISSING, STR_IDLE_HINT,
    STR_COUNT
};

extern int current_lang;
extern const char *lang_strings[LANG_COUNT][STR_COUNT];
#define tr(id) ((char *)lang_strings[current_lang][(id)])

#endif /* LANG_H */
