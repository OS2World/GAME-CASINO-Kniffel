/*******************************************************************************
*                                                                              *
* KNIFFEL.C                                                                    *
* ---------                                                                    *
*                                                                              *
* Kniffel (Yahtzee) for OS/2 Presentation Manager.                             *
*                                                                              *
* Original program: KNIFFEL, VisPro/REXX, (c) 1996-1999 Andreas Kieser.        *
* 2026: Rewritten in C for Open Watcom by the OS2World community. The rules,   *
*       the player symbols and the hit list file follow the original.          *
*                                                                              *
* Licensed under the GNU General Public License v3 (see doc\LICENSE.txt).      *
*                                                                              *
*******************************************************************************/

#define INCL_WIN
#define INCL_GPI
#define INCL_DOS
#define INCL_WINWORKPLACE

#include <os2.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "kniffel.h"
#include "lang.h"

#pragma off(unreferenced)
static const char bldlevel[] =
    "@#Andreas Kieser:1.10#@##1## 06 Oct 2026 16:00:00      "
    "ARCAOS:::0::::@@Kniffel - Yahtzee dice game for OS/2\r\n\x1a";
#pragma on(unreferenced)

/*** Defines ******************************************************************/

#define MAXPL       5           /* players                                   */
#define NCAT        13          /* scoring fields per player                 */
#define IDX_SUMUP   14          /* pseudo index: sum of the upper section    */
#define IDX_SUMLOW  15          /* pseudo index: sum of the lower section    */
#define IDX_TOTAL   16          /* pseudo index: total                       */
#define NDICE       5
#define MAXICONS    64
#define NAMELEN     12
#define EMPTYCELL   -1

#define LW          1000        /* logical size of the game area             */
#define LH          700
#define TBL_X       20
#define TBL_Y       170
#define LABEL_W     180
#define COL_W       130
#define HEAD_H      40
#define ROW_H       30
#define BTN_X       858
#define BTN_W       134
#define BTN_H       56

enum { B_ROLL = 0, B_INVERT, B_NEXT, B_UNDO, B_ABORT, NBTN };

/*** Variables ****************************************************************/

typedef struct {
    ULONG saveonexit, detaillevel, current_lang, pictures, players;
} SETTINGS;

static SETTINGS  cfg;
static HAB       hab;
static HWND      hwndFrame, hwndClient, hwndMenu, hwndTitleBar, hwndSysMenu,
                 hwndMinMax, hwndPark, hwndHelpInst;
static BOOL      frameHidden;
static CHAR      szExeDir[CCHMAXPATH];
static CHAR      szHelpLib[CCHMAXPATH];

static HBITMAP   hbmDice[13];           /* blank, 1..6, held 1..6            */
static HBITMAP   hbmRow[NCAT + 1];      /* 1..13                             */
static HBITMAP   hbmBtn[NBTN];
static HPOINTER  iconList[MAXICONS];
static int       nIcons;

/* game state */
static BOOL      playing;
static int       nPlayers = 2, curPlayer, rollNo, lastCat;
static BOOL      placed, rollsLocked, rolling;
static int       dice[NDICE], hold[NDICE];
static int       score[MAXPL][NCAT + 1];
static int       upRaw[MAXPL], sumUp[MAXPL], sumLow[MAXPL], total[MAXPL];
static char      plName[MAXPL][NAMELEN + 4];
static int       plIconIdx[MAXPL];

static LONG      gOx, gOyTop;

/*** Prototypes ***************************************************************/

MRESULT EXPENTRY ClientWndProc(HWND, ULONG, MPARAM, MPARAM);
MRESULT EXPENTRY StartDlgProc(HWND, ULONG, MPARAM, MPARAM);
MRESULT EXPENTRY ResultDlgProc(HWND, ULONG, MPARAM, MPARAM);
MRESULT EXPENTRY HitlistDlgProc(HWND, ULONG, MPARAM, MPARAM);
MRESULT EXPENTRY AboutDlgProc(HWND, ULONG, MPARAM, MPARAM);

static void StartNewGame(void);
static void BeginGame(void);
static void SetLanguage(int lang);
static void SetHelpLanguage(int lang);

/*** Settings *****************************************************************/

static void LoadSettings(void)
{
    FILE *fp;

    memset(&cfg, 0, sizeof(cfg));
    cfg.saveonexit   = 1;
    cfg.detaillevel  = 1;
    cfg.current_lang = LANG_EN;
    cfg.pictures     = 0;
    cfg.players      = 2;

    fp = fopen("Kniffel.cfg", "rb");
    if( fp )
    {
        fread(&cfg, 1, sizeof(cfg), fp);
        fclose(fp);
    }

    if( cfg.saveonexit > 1 )                cfg.saveonexit = 1;
    if( cfg.detaillevel > 2 )               cfg.detaillevel = 1;
    if( cfg.current_lang >= LANG_COUNT )    cfg.current_lang = LANG_EN;
    if( cfg.pictures > 1 )                  cfg.pictures = 1;
    if( cfg.players < 1 || cfg.players > MAXPL ) cfg.players = 2;
}

static void SaveSettings(void)
{
    FILE *fp = fopen("Kniffel.cfg", "wb");

    if( fp )
    {
        fwrite(&cfg, 1, sizeof(cfg), fp);
        fclose(fp);
    }
}

/*** Game rules ***************************************************************/

static int ScoreFor(int cat)
{
    int c[7], i, sum = 0, three = 0, four = 0, five = 0, two = 0;

    memset(c, 0, sizeof(c));
    for( i = 0; i < NDICE; i++ )
    {
        c[dice[i]]++;
        sum += dice[i];
    }
    for( i = 1; i <= 6; i++ )
    {
        if( c[i] == 2 )  two = 1;
        if( c[i] == 3 )  three = 1;
        if( c[i] >= 3 )  three = three | 1;
        if( c[i] >= 4 )  four = 1;
        if( c[i] == 5 )  five = 1;
    }

    switch( cat )
    {
        case 1: case 2: case 3: case 4: case 5: case 6:
            return c[cat] >= 3 ? c[cat] * cat : 0;      /* at least three needed */
        case 7:
            return three ? sum : 0;
        case 8:
            return four ? sum : 0;
        case 9:
            for( i = 1; i <= 6; i++ )
                if( c[i] == 3 && two )
                    return 25;
            return five ? 25 : 0;
        case 10:
            for( i = 1; i <= 3; i++ )
                if( c[i] && c[i+1] && c[i+2] && c[i+3] )
                    return 30;
            return 0;
        case 11:
            if( (c[1] && c[2] && c[3] && c[4] && c[5]) ||
                (c[2] && c[3] && c[4] && c[5] && c[6]) )
                return 40;
            return 0;
        case 12:
            return five ? 50 : 0;
        case 13:
            return sum;
    }
    return 0;
}

static void Recalc(int p)
{
    int i;

    upRaw[p] = 0;
    sumLow[p] = 0;
    for( i = 1; i <= 6; i++ )
        if( score[p][i] != EMPTYCELL )  upRaw[p] += score[p][i];
    for( i = 7; i <= NCAT; i++ )
        if( score[p][i] != EMPTYCELL )  sumLow[p] += score[p][i];
    sumUp[p] = upRaw[p] + (upRaw[p] > 62 ? 35 : 0);
    total[p] = sumUp[p] + sumLow[p];
}

static BOOL AllDone(void)
{
    int p, i;

    for( p = 0; p < nPlayers; p++ )
        for( i = 1; i <= NCAT; i++ )
            if( score[p][i] == EMPTYCELL )
                return FALSE;
    return TRUE;
}

/*** Layout and painting ******************************************************/

static void Layout(void)
{
    RECTL r;
    LONG  mx, my;

    WinQueryWindowRect(hwndClient, &r);
    mx = (r.xRight - LW) / 2;
    my = (r.yTop - LH) / 2;
    gOx = mx > 0 ? mx : 0;
    gOyTop = r.yTop - (my > 0 ? my : 0);
}

static void LRect(RECTL *r, LONG x, LONG y, LONG w, LONG h)
{
    r->xLeft   = gOx + x;
    r->xRight  = r->xLeft + w;
    r->yTop    = gOyTop - y;
    r->yBottom = r->yTop - h;
}

static void DiceRect(RECTL *r, int i)
{
    LRect(r, 20 + i * 130, 52, 120, 100);
}

static void ButtonRect(RECTL *r, int b)
{
    LRect(r, BTN_X, 60 + b * 65, BTN_W, BTN_H);
}

static int RowToIdx(int rd)
{
    if( rd >= 1 && rd <= 6 )   return rd;
    if( rd == 7 )              return IDX_SUMUP;
    if( rd >= 8 && rd <= 14 )  return rd - 1;
    if( rd == 15 )             return IDX_SUMLOW;
    if( rd == 16 )             return IDX_TOTAL;
    return 0;
}

static void CellRect(RECTL *r, int rd, int col)      /* col -1 = label column  */
{
    LONG y = TBL_Y + (rd == 0 ? 0 : HEAD_H + (rd - 1) * ROW_H);
    LONG h = rd == 0 ? HEAD_H : ROW_H;

    if( col < 0 )
        LRect(r, TBL_X, y, LABEL_W, h);
    else
        LRect(r, TBL_X + LABEL_W + col * COL_W, y, COL_W, h);
}

static BOOL ButtonEnabled(int b)
{
    if( !playing || rolling )
        return FALSE;

    switch( b )
    {
        case B_ROLL:   return !placed && !rollsLocked && rollNo < 3;
        case B_INVERT: return !placed && !rollsLocked && rollNo >= 1 && rollNo < 3;
        case B_NEXT:   return placed;
        case B_UNDO:   return placed;
        case B_ABORT:  return TRUE;
    }
    return FALSE;
}

static void Box(HPS hps, RECTL *r)
{
    POINTL pt;

    GpiSetColor(hps, CLR_BLACK);
    pt.x = r->xLeft;
    pt.y = r->yBottom;
    GpiMove(hps, &pt);
    pt.x = r->xRight - 1;
    pt.y = r->yTop - 1;
    GpiBox(hps, DRO_OUTLINE, &pt, 0, 0);
}

static void DrawBmp(HPS hps, HBITMAP hbm, LONG x, LONG y)
{
    POINTL pt;

    pt.x = x;
    pt.y = y;
    if( hbm )
        WinDrawBitmap(hps, hbm, NULL, &pt, CLR_BLACK, CLR_WHITE, DBM_NORMAL);
}

static void PaintButtons(HPS hps)
{
    static const int strId[NBTN] = { STR_BTN_ROLL, STR_BTN_INVERT, STR_BTN_NEXT,
                                     STR_BTN_UNDO, STR_BTN_ABORT };
    RECTL r;
    int   b;
    BOOL  en;

    for( b = 0; b < NBTN; b++ )
    {
        ButtonRect(&r, b);
        en = ButtonEnabled(b);
        WinFillRect(hps, &r, CLR_PALEGRAY);
        Box(hps, &r);
        if( cfg.pictures && hbmBtn[b] )
        {
            if( en )
                DrawBmp(hps, hbmBtn[b], r.xLeft + (BTN_W - 32) / 2, r.yBottom + (BTN_H - 32) / 2);
        }
        else
        {
            RECTL t = r;
            t.xLeft += 2; t.xRight -= 2;
            WinDrawText(hps, -1, (PCH)tr(strId[b]), &t, en ? CLR_BLACK : CLR_DARKGRAY,
                        CLR_PALEGRAY, DT_CENTER | DT_VCENTER);
        }
    }
}

static void PaintTable(HPS hps)
{
    char  buf[32];
    RECTL r;
    int   rd, p, idx;
    LONG  bg, fg;

    /* header */
    CellRect(&r, 0, -1);
    WinFillRect(hps, &r, CLR_DARKGREEN);
    for( p = 0; p < nPlayers; p++ )
    {
        CellRect(&r, 0, p);
        WinFillRect(hps, &r, p == curPlayer ? CLR_YELLOW : CLR_PALEGRAY);
        Box(hps, &r);
        if( plIconIdx[p] >= 0 && plIconIdx[p] < nIcons )
            WinDrawPointer(hps, r.xLeft + 2, r.yBottom + 4, iconList[plIconIdx[p]], DP_NORMAL);
        {
            RECTL t = r;
            t.xLeft += 38; t.xRight -= 2;
            WinDrawText(hps, -1, (PCH)plName[p], &t, CLR_BLACK,
                        p == curPlayer ? CLR_YELLOW : CLR_PALEGRAY, DT_LEFT | DT_VCENTER);
        }
    }

    for( rd = 1; rd <= 16; rd++ )
    {
        idx = RowToIdx(rd);
        CellRect(&r, rd, -1);
        WinFillRect(hps, &r, CLR_PALEGRAY);
        Box(hps, &r);
        if( cfg.pictures && idx >= 1 && idx <= NCAT && hbmRow[idx] )
            DrawBmp(hps, hbmRow[idx], r.xLeft + 4, r.yBottom + 1);
        else
        {
            RECTL t = r;
            int   sid;
            t.xLeft += 6;
            if( idx >= 1 && idx <= 6 )       sid = STR_ROW1 + idx - 1;
            else if( idx == IDX_SUMUP )      sid = STR_ROW_SUMUP;
            else if( idx == IDX_SUMLOW )     sid = STR_ROW_SUMLOW;
            else if( idx == IDX_TOTAL )      sid = STR_ROW_TOTAL;
            else                             sid = STR_ROW_3KIND + idx - 7;
            WinDrawText(hps, -1, (PCH)tr(sid), &t, CLR_BLACK, CLR_PALEGRAY, DT_LEFT | DT_VCENTER);
        }
        for( p = 0; p < nPlayers; p++ )
        {
            CellRect(&r, rd, p);
            fg = CLR_BLACK;
            buf[0] = 0;
            if( idx <= NCAT )
            {
                bg = (p == curPlayer && score[p][idx] == EMPTYCELL) ? CLR_WHITE : CLR_PALEGRAY;
                if( placed && p == curPlayer && idx == lastCat )
                    bg = CLR_YELLOW;
                if( score[p][idx] != EMPTYCELL )
                {
                    sprintf(buf, "%d", score[p][idx]);
                    if( score[p][idx] == 0 )  fg = CLR_RED;
                }
            }
            else
            {
                bg = CLR_PALEGRAY;
                if( idx == IDX_SUMUP )
                {
                    if( upRaw[p] > 62 ) { sprintf(buf, "%d", sumUp[p]); fg = CLR_DARKGREEN; }
                    else                { sprintf(buf, "-%d", upRaw[p]); fg = CLR_RED; }
                }
                else if( idx == IDX_SUMLOW )  sprintf(buf, "%d", sumLow[p]);
                else                          sprintf(buf, "%d", total[p]);
            }
            WinFillRect(hps, &r, bg);
            Box(hps, &r);
            {
                RECTL t = r;
                t.xLeft += 2; t.xRight -= 2;
                WinDrawText(hps, -1, (PCH)buf, &t, fg, bg, DT_CENTER | DT_VCENTER);
            }
        }
    }
}

static void PaintDice(HPS hps)
{
    RECTL r;
    int   i, id;

    for( i = 0; i < NDICE; i++ )
    {
        DiceRect(&r, i);
        id = dice[i] == 0 ? 0 : (hold[i] ? 6 + dice[i] : dice[i]);
        DrawBmp(hps, hbmDice[id], r.xLeft, r.yBottom);
    }
}

static void PaintInfo(HPS hps)
{
    char  buf[256];
    RECTL r;

    LRect(&r, 10, 6, 980, 36);
    if( !placed && rollNo == 0 )
        sprintf(buf, tr(STR_INFO_START), plName[curPlayer]);
    else if( !placed )
        sprintf(buf, tr(STR_INFO_ROLLED), plName[curPlayer], rollNo > 3 ? 3 : rollNo);
    else
        sprintf(buf, tr(STR_INFO_PLACED), plName[curPlayer]);

    WinFillRect(hps, &r, CLR_PALEGRAY);
    Box(hps, &r);
    r.xLeft += 8; r.xRight -= 8;
    WinDrawText(hps, -1, (PCH)buf, &r, CLR_BLACK, CLR_PALEGRAY, DT_LEFT | DT_VCENTER);
}

static void PaintIdle(HPS hps)
{
    RECTL r;
    LRect(&r, 0, 260, LW, 40);
    WinDrawText(hps, -1, (PCH)"Kniffel", &r, CLR_YELLOW, CLR_DARKGREEN, DT_CENTER | DT_VCENTER);
    LRect(&r, 0, 320, LW, 30);
    WinDrawText(hps, -1, (PCH)tr(STR_IDLE_HINT), &r, CLR_WHITE, CLR_DARKGREEN, DT_CENTER | DT_VCENTER);
}

/*** Game actions *************************************************************/

static void Redraw(void)
{
    WinInvalidateRect(hwndClient, NULL, FALSE);
}

static void UpdateMenus(void)
{
    WinEnableMenuItem(hwndMenu, IDM_NEWGAME, !playing);
    WinEnableMenuItem(hwndMenu, IDM_QUIT, playing);
}

static void NewTurn(void)
{
    int i;

    rollNo = 0;
    placed = FALSE;
    rollsLocked = FALSE;
    lastCat = 0;
    for( i = 0; i < NDICE; i++ )
    {
        dice[i] = 0;
        hold[i] = 0;
    }
}

static void BeginGame(void)
{
    int p, i;

    for( p = 0; p < MAXPL; p++ )
    {
        for( i = 0; i <= NCAT; i++ )
            score[p][i] = EMPTYCELL;
        Recalc(p);
    }
    curPlayer = 0;
    playing = TRUE;
    NewTurn();
    UpdateMenus();
    Redraw();
    WinSetFocus(HWND_DESKTOP, hwndClient);
}

static void DoRoll(void)
{
    int      i, f;
    RECTL    r, all;

    if( !ButtonEnabled(B_ROLL) )
        return;

    rolling = TRUE;
    DiceRect(&r, 0);
    all = r;
    DiceRect(&r, NDICE - 1);
    all.xRight = r.xRight;

    for( f = 0; f < 8; f++ )
    {
        for( i = 0; i < NDICE; i++ )
            if( !hold[i] )
                dice[i] = 1 + rand() % 6;
        WinInvalidateRect(hwndClient, &all, FALSE);
        WinUpdateWindow(hwndClient);
        DosSleep(45);
    }
    rolling = FALSE;
    rollNo++;
    Redraw();
}

static void PlaceScore(int cat)
{
    if( !playing || rolling || placed || rollNo < 1 || score[curPlayer][cat] != EMPTYCELL )
        return;

    score[curPlayer][cat] = ScoreFor(cat);
    Recalc(curPlayer);
    placed = TRUE;
    lastCat = cat;
    Redraw();
}

static void DoUndo(void)
{
    if( !ButtonEnabled(B_UNDO) )
        return;

    score[curPlayer][lastCat] = EMPTYCELL;
    Recalc(curPlayer);
    placed = FALSE;
    rollsLocked = TRUE;     /* after taking back, no more rolling */
    Redraw();
}

static void FormatTime(char *date, char *clock)
{
    time_t     t = time(NULL);
    struct tm *tmv = localtime(&t);

    sprintf(date, "%02d.%02d.%04d", tmv->tm_mday, tmv->tm_mon + 1, tmv->tm_year + 1900);
    sprintf(clock, "%02d:%02d", tmv->tm_hour, tmv->tm_min);
}

static int BuildRanking(int order[MAXPL])
{
    int i, j, t;

    for( i = 0; i < nPlayers; i++ )
        order[i] = i;
    for( i = 0; i < nPlayers - 1; i++ )
        for( j = i + 1; j < nPlayers; j++ )
            if( total[order[j]] > total[order[i]] )
            {
                t = order[i]; order[i] = order[j]; order[j] = t;
            }
    return nPlayers;
}

/* The result text, one line per entry; returns the number of lines */
static int BuildResultLines(char lines[][96])
{
    int order[MAXPL], n = 0, i, p;
    char entry[64];

    BuildRanking(order);
    if( nPlayers > 1 )
    {
        sprintf(lines[n++], "%s", tr(STR_RES_WINNER));
        for( i = 0; i < nPlayers; i++ )
        {
            p = order[i];
            sprintf(entry, "    %-15s%4d%s%s", plName[p], total[p],
                    upRaw[p] > 62 ? " " : "", upRaw[p] > 62 ? tr(STR_RES_BONUS) : "");
            if( i == 1 )
            {
                lines[n++][0] = 0;
                sprintf(lines[n++], "%s", tr(STR_RES_LOSERS));
            }
            sprintf(lines[n++], "%s", entry);
        }
    }
    else
    {
        p = order[0];
        sprintf(lines[n++], "    %-15s%4d%s%s", plName[p], total[p],
                upRaw[p] > 62 ? " " : "", upRaw[p] > 62 ? tr(STR_RES_BONUS) : "");
    }
    return n;
}

static BOOL HitlistExists(void)
{
    FILE *fp = fopen("hitlist.hgh", "rb");

    if( fp )
    {
        fclose(fp);
        return TRUE;
    }
    return FALSE;
}

static void ShowResults(void)
{
    ULONG rc;

    playing = FALSE;
    UpdateMenus();
    Redraw();
    WinUpdateWindow(hwndClient);

    rc = WinDlgBox(HWND_DESKTOP, hwndFrame, ResultDlgProc, NULLHANDLE, IDD_RESULT, NULL);
    if( rc == DID_OK )
        BeginGame();                    /* play again, same players */
    else
        WinPostMsg(hwndClient, WM_COMMAND, MPFROM2SHORT(IDM_NEWGAME, 0), 0);
}

static void DoNext(void)
{
    if( !ButtonEnabled(B_NEXT) )
        return;

    if( AllDone() )
    {
        ShowResults();
        return;
    }
    curPlayer = (curPlayer + 1) % nPlayers;
    NewTurn();
    Redraw();
}

static void DoAbort(void)
{
    if( !playing )
        return;
    if( WinMessageBox(HWND_DESKTOP, hwndFrame, (PSZ)tr(STR_QUITASK), (PSZ)"Kniffel", 0,
                      MB_YESNO | MB_QUERY | MB_MOVEABLE) != MBID_YES )
        return;

    playing = FALSE;
    UpdateMenus();
    Redraw();
    WinPostMsg(hwndClient, WM_COMMAND, MPFROM2SHORT(IDM_NEWGAME, 0), 0);
}

static void ToggleHold(int i)
{
    if( placed || rollsLocked || rolling || rollNo < 1 || rollNo >= 3 )
        return;
    hold[i] = !hold[i];
    Redraw();
}

static void DoInvert(void)
{
    int i;

    if( !ButtonEnabled(B_INVERT) )
        return;
    for( i = 0; i < NDICE; i++ )
        hold[i] = !hold[i];
    Redraw();
}

static BOOL Inside(RECTL *r, LONG x, LONG y)
{
    return x >= r->xLeft && x < r->xRight && y >= r->yBottom && y < r->yTop;
}

static void OnClick(LONG x, LONG y)
{
    RECTL r;
    int   i, rd, idx;

    if( !playing || rolling )
        return;

    for( i = 0; i < NDICE; i++ )
    {
        DiceRect(&r, i);
        if( Inside(&r, x, y) )
        {
            ToggleHold(i);
            return;
        }
    }
    for( i = 0; i < NBTN; i++ )
    {
        ButtonRect(&r, i);
        if( Inside(&r, x, y) && ButtonEnabled(i) )
        {
            switch( i )
            {
                case B_ROLL:   DoRoll();   break;
                case B_INVERT: DoInvert(); break;
                case B_NEXT:   DoNext();   break;
                case B_UNDO:   DoUndo();   break;
                case B_ABORT:  DoAbort();  break;
            }
            return;
        }
    }
    for( rd = 1; rd <= 16; rd++ )
    {
        idx = RowToIdx(rd);
        if( idx > NCAT )
            continue;
        CellRect(&r, rd, curPlayer);
        if( Inside(&r, x, y) )
        {
            PlaceScore(idx);
            return;
        }
    }
}

/*** Icons ********************************************************************/

static void BuildIconList(void)
{
    HDIR          hdir = HDIR_CREATE;
    FILEFINDBUF3  ff;
    ULONG         cnt = 1;
    CHAR          path[CCHMAXPATH], pattern[CCHMAXPATH];
    HPOINTER      hp;
    int           k;

    nIcons = 0;
    strcpy(pattern, szExeDir);
    strcat(pattern, "icons\\*.ico");

    if( DosFindFirst((PSZ)pattern, &hdir, FILE_NORMAL, &ff, sizeof(ff), &cnt, FIL_STANDARD) == 0 )
    {
        do
        {
            strcpy(path, szExeDir);
            strcat(path, "icons\\");
            strcat(path, ff.achName);
            hp = WinLoadFileIcon((PSZ)path, FALSE);
            if( hp && nIcons < MAXICONS )
                iconList[nIcons++] = hp;
            cnt = 1;
        } while( DosFindNext(hdir, &ff, sizeof(ff), &cnt) == 0 );
        DosFindClose(hdir);
    }

    /* fewer than five icons: the program offers its own ones */
    for( k = 0; nIcons < 5; k++ )
        iconList[nIcons++] = WinLoadPointer(HWND_DESKTOP, NULLHANDLE, PID_DEFAULT + 1 + k);
}

/*** Dialogs ******************************************************************/


MRESULT EXPENTRY AboutDlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
    switch( msg )
    {
        case WM_COMMAND:
            switch( SHORT1FROMMP(mp1) )
            {
                case DID_OK:
                case DID_CANCEL:
                    WinDismissDlg(hwnd, TRUE);
                    return 0;
            }
            break;
    }
    return WinDefDlgProc(hwnd, msg, mp1, mp2);
}

MRESULT EXPENTRY HitlistDlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
    FILE *fp;
    char  line[200];
    int   n, len;
    HWND  hl;

    switch( msg )
    {
        case WM_INITDLG:
            WinSetWindowText(hwnd, (PSZ)tr(STR_HIT_TITLE));
            WinSetDlgItemText(hwnd, DID_OK, (PSZ)tr(STR_DLG_CLOSE));
            WinSetDlgItemText(hwnd, ID_HIT_DELETE, (PSZ)tr(STR_HIT_DELETE));
            WinSetDlgItemText(hwnd, ID_HIT_EMPTY, (PSZ)tr(STR_HIT_EMPTY));
            hl = WinWindowFromID(hwnd, ID_HIT_LIST);
            WinSetPresParam(hl, PP_FONTNAMESIZE, 12, (PVOID)"10.System Monospaced");
            n = 0;
            fp = fopen("hitlist.hgh", "r");
            if( fp )
            {
                while( fgets(line, sizeof(line), fp) )
                {
                    len = strlen(line);
                    while( len > 0 && (line[len-1] == '\n' || line[len-1] == '\r') )
                        line[--len] = 0;
                    WinSendMsg(hl, LM_INSERTITEM, MPFROM2SHORT(LIT_END, 0), MPFROMP(line));
                    n++;
                }
                fclose(fp);
            }
            WinShowWindow(WinWindowFromID(hwnd, ID_HIT_EMPTY), n == 0);
            WinEnableControl(hwnd, ID_HIT_DELETE, n != 0);
            break;

        case WM_COMMAND:
            switch( SHORT1FROMMP(mp1) )
            {
                case ID_HIT_DELETE:
                    if( WinMessageBox(HWND_DESKTOP, hwnd, (PSZ)tr(STR_HIT_DELASK), (PSZ)"Kniffel", 0,
                                      MB_YESNO | MB_QUERY | MB_MOVEABLE) == MBID_YES )
                    {
                        remove("hitlist.hgh");
                        WinSendDlgItemMsg(hwnd, ID_HIT_LIST, LM_DELETEALL, 0, 0);
                        WinShowWindow(WinWindowFromID(hwnd, ID_HIT_EMPTY), TRUE);
                        WinEnableControl(hwnd, ID_HIT_DELETE, FALSE);
                    }
                    return 0;
                case DID_OK:
                case DID_CANCEL:
                    WinDismissDlg(hwnd, TRUE);
                    return 0;
            }
            break;
    }
    return WinDefDlgProc(hwnd, msg, mp1, mp2);
}

static int dlgIcon[MAXPL];
static int dlgCount;

/* The player symbols are drawn by the dialog itself, at 154,y in dialog units */
static void IconPos(HWND hwnd, int i, POINTL *pt)
{
    pt->x = 154;
    pt->y = 40 + (MAXPL - 1 - i) * 28 + 2;
    WinMapDlgPoints(hwnd, pt, 1, TRUE);
}

static void ShowRowIcon(HWND hwnd, int i)
{
    POINTL pt;
    RECTL  r;

    IconPos(hwnd, i, &pt);
    r.xLeft = pt.x;
    r.yBottom = pt.y;
    r.xRight = pt.x + 36;
    r.yTop = pt.y + 36;
    WinInvalidateRect(hwnd, &r, TRUE);
}

static void DrawRowIcons(HWND hwnd)
{
    HPS    hps = WinGetPS(hwnd);
    POINTL pt;
    int    i;

    for( i = 0; i < dlgCount; i++ )
    {
        IconPos(hwnd, i, &pt);
        WinDrawPointer(hps, pt.x, pt.y, iconList[dlgIcon[i]], DP_NORMAL);
    }
    WinReleasePS(hps);
}
static void EnableRows(HWND hwnd, int n)
{
    int i;

    for( i = 0; i < MAXPL; i++ )
    {
        WinEnableControl(hwnd, ID_PL_LBL + i, i < n);
        WinEnableControl(hwnd, ID_PL_NAME + i, i < n);
        WinEnableControl(hwnd, ID_PL_PREV + i, i < n);
        WinEnableControl(hwnd, ID_PL_NEXT + i, i < n);
    }
    dlgCount = n;
    WinInvalidateRect(hwnd, NULL, TRUE);
}

MRESULT EXPENTRY StartDlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
    int   i, id;
    char  buf[NAMELEN + 4];
    HWND  hEdit;

    switch( msg )
    {
        case WM_INITDLG:
            WinSetWindowText(hwnd, (PSZ)tr(STR_DLG_START_TITLE));
            WinSetDlgItemText(hwnd, ID_PLAYERS_GRP, (PSZ)tr(STR_DLG_PLAYERS));
            WinSetDlgItemText(hwnd, ID_COL_NAME, (PSZ)tr(STR_DLG_NAME));
            WinSetDlgItemText(hwnd, ID_COL_SYMBOL, (PSZ)tr(STR_DLG_SYMBOL));
            WinSetDlgItemText(hwnd, DID_OK, (PSZ)tr(STR_DLG_PLAY));
            WinSetDlgItemText(hwnd, ID_HITBTN, (PSZ)tr(STR_DLG_HITLIST));
            WinSetDlgItemText(hwnd, DID_CANCEL, (PSZ)tr(STR_DLG_CLOSE));
            WinCheckButton(hwnd, ID_PLAYERS_1 + (nPlayers - 1), 1);
            WinEnableControl(hwnd, ID_HITBTN, HitlistExists());
            for( i = 0; i < MAXPL; i++ )
            {
                hEdit = WinWindowFromID(hwnd, ID_PL_NAME + i);
                WinSendMsg(hEdit, EM_SETTEXTLIMIT, MPFROMLONG(NAMELEN), 0);
                if( plName[i][0] )
                    WinSetWindowText(hEdit, (PSZ)plName[i]);
                else
                {
                    sprintf(buf, tr(STR_DEFAULT_NAME), i + 1);
                    WinSetWindowText(hEdit, (PSZ)buf);
                }
                dlgIcon[i] = (plName[i][0] && plIconIdx[i] >= 0 && plIconIdx[i] < nIcons)
                             ? plIconIdx[i] : i % nIcons;
                ShowRowIcon(hwnd, i);
            }
            EnableRows(hwnd, nPlayers);
            break;

        case WM_PAINT:
            {
                MRESULT mr = WinDefDlgProc(hwnd, msg, mp1, mp2);
                DrawRowIcons(hwnd);
                return mr;
            }

        case WM_CONTROL:
            id = SHORT1FROMMP(mp1);
            if( id >= ID_PLAYERS_1 && id <= ID_PLAYERS_5 && SHORT2FROMMP(mp1) == BN_CLICKED )
                EnableRows(hwnd, id - ID_PLAYERS_1 + 1);
            break;

        case WM_COMMAND:
            id = SHORT1FROMMP(mp1);
            if( id >= ID_PL_PREV && id < ID_PL_PREV + MAXPL )
            {
                i = id - ID_PL_PREV;
                dlgIcon[i] = (dlgIcon[i] + nIcons - 1) % nIcons;
                ShowRowIcon(hwnd, i);
                return 0;
            }
            if( id >= ID_PL_NEXT && id < ID_PL_NEXT + MAXPL )
            {
                i = id - ID_PL_NEXT;
                dlgIcon[i] = (dlgIcon[i] + 1) % nIcons;
                ShowRowIcon(hwnd, i);
                return 0;
            }
            switch( id )
            {
                case ID_HITBTN:
                    WinDlgBox(HWND_DESKTOP, hwnd, HitlistDlgProc, NULLHANDLE, IDD_HITLIST, NULL);
                    WinEnableControl(hwnd, ID_HITBTN, HitlistExists());
                    return 0;
                case DID_OK:
                    for( i = 0; i < MAXPL; i++ )
                        if( WinQueryButtonCheckstate(hwnd, ID_PLAYERS_1 + i) )
                            nPlayers = i + 1;
                    cfg.players = nPlayers;
                    for( i = 0; i < MAXPL; i++ )
                    {
                        WinQueryDlgItemText(hwnd, ID_PL_NAME + i, NAMELEN + 1, (PSZ)plName[i]);
                        if( plName[i][0] == 0 )
                            sprintf(plName[i], tr(STR_DEFAULT_NAME), i + 1);
                        plIconIdx[i] = dlgIcon[i];
                    }
                    WinDismissDlg(hwnd, DID_OK);
                    return 0;
                case DID_CANCEL:
                    WinDismissDlg(hwnd, DID_CANCEL);
                    return 0;
            }
            break;
    }
    return WinDefDlgProc(hwnd, msg, mp1, mp2);
}
MRESULT EXPENTRY ResultDlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
    static BOOL saved;
    char   lines[16][96], date[16], clock[16], head[96];
    int    n, i;
    FILE  *fp;

    switch( msg )
    {
        case WM_INITDLG:
            saved = FALSE;
            WinSetWindowText(hwnd, (PSZ)tr(STR_DLG_RESULT_TITLE));
            WinSetDlgItemText(hwnd, DID_OK, (PSZ)tr(STR_RES_AGAIN));
            WinSetDlgItemText(hwnd, ID_RES_SAVE, (PSZ)tr(STR_RES_SAVE));
            WinSetDlgItemText(hwnd, DID_CANCEL, (PSZ)tr(STR_RES_BACK));
            FormatTime(date, clock);
            sprintf(head, tr(STR_RES_HEADER), date, clock);
            WinSetDlgItemText(hwnd, ID_RES_TEXT, (PSZ)head);
            WinSetPresParam(WinWindowFromID(hwnd, ID_RES_LIST), PP_FONTNAMESIZE, 12, (PVOID)"10.System Monospaced");
            n = BuildResultLines(lines);
            for( i = 0; i < n; i++ )
                WinSendDlgItemMsg(hwnd, ID_RES_LIST, LM_INSERTITEM, MPFROM2SHORT(LIT_END, 0), MPFROMP(lines[i]));
            break;

        case WM_COMMAND:
            switch( SHORT1FROMMP(mp1) )
            {
                case ID_RES_SAVE:
                    if( !saved )
                    {
                        FormatTime(date, clock);
                        n = BuildResultLines(lines);
                        fp = fopen("hitlist.hgh", "ab");
                        if( fp )
                        {
                            sprintf(head, tr(STR_RES_HEADER), date, clock);
                            fprintf(fp, "\r\n%s\r\n===================================\r\n\r\n", head);
                            for( i = 0; i < n; i++ )
                                fprintf(fp, "%s\r\n", lines[i]);
                            fclose(fp);
                        }
                        saved = TRUE;
                        WinEnableControl(hwnd, ID_RES_SAVE, FALSE);
                    }
                    return 0;
                case DID_OK:
                    WinDismissDlg(hwnd, DID_OK);
                    return 0;
                case DID_CANCEL:
                    WinDismissDlg(hwnd, DID_CANCEL);
                    return 0;
            }
            break;
    }
    return WinDefDlgProc(hwnd, msg, mp1, mp2);
}

static void StartNewGame(void)
{
    if( playing )
        return;

    nPlayers = (int)cfg.players;
    if( WinDlgBox(HWND_DESKTOP, hwndFrame, StartDlgProc, NULLHANDLE, IDD_START, NULL) != DID_OK )
        return;

    BeginGame();
}

/*** Menus, language and help *************************************************/

typedef struct { USHORT id; int str; } MENUTEXT;

static const MENUTEXT mtAll[] = {
    { IDM_SUBMENU_GAME,     STR_MENU_GAME },     { IDM_SUBMENU_OPTIONS,  STR_MENU_OPTIONS },
    { IDM_SUBMENU_HELP,     STR_MENU_HELP },     { IDM_SUBMENU_LANGUAGE, STR_MENU_LANGUAGE },
    { IDM_NEWGAME,          STR_MENU_NEW },      { IDM_QUIT,             STR_MENU_QUIT },
    { IDM_HITLIST,          STR_MENU_HITLIST },  { IDM_EXIT,             STR_MENU_EXIT },
    { IDM_PICTURES,         STR_MENU_PICTURES }, { IDM_FRAME,            STR_MENU_FRAME },
    { IDM_SAVEONEXIT,       STR_MENU_SAVEONEXIT },{ IDM_GENERALHELP,     STR_MENU_GENHELP },
    { IDM_HELPINDEX,        STR_MENU_HELPINDEX },{ IDM_HELPONHELP,       STR_MENU_HELPONHELP },
    { IDM_ABOUT,            STR_MENU_ABOUT }
};

static HWND GetSubMenu(HWND hMenu, USHORT id)
{
    MENUITEM mi;

    memset(&mi, 0, sizeof(mi));
    if( (BOOL)WinSendMsg(hMenu, MM_QUERYITEM, MPFROM2SHORT(id, FALSE), MPFROMP(&mi)) )
        return mi.hwndSubMenu;
    return NULLHANDLE;
}

static void ApplyMenuTable(HWND hMenu)
{
    int i;

    for( i = 0; i < (int)(sizeof(mtAll) / sizeof(mtAll[0])); i++ )
        WinSendMsg(hMenu, MM_SETITEMTEXT, MPFROMSHORT(mtAll[i].id), MPFROMP(tr(mtAll[i].str)));
}

static void RelabelMenu(void)
{
    static const USHORT subs[] = { IDM_SUBMENU_GAME, IDM_SUBMENU_OPTIONS, IDM_SUBMENU_HELP };
    int  i;
    HWND hSub;

    ApplyMenuTable(hwndMenu);
    for( i = 0; i < 3; i++ )
    {
        hSub = GetSubMenu(hwndMenu, subs[i]);
        if( hSub )
        {
            ApplyMenuTable(hSub);
            if( subs[i] == IDM_SUBMENU_OPTIONS )
            {
                hSub = GetSubMenu(hSub, IDM_SUBMENU_LANGUAGE);
                if( hSub )
                    ApplyMenuTable(hSub);
            }
        }
    }
}

static void SyncMenus(void)
{
    int i;

    for( i = 0; i < LANG_COUNT; i++ )
        WinCheckMenuItem(hwndMenu, (USHORT)(IDM_LANG_EN + i), i == current_lang);
    WinCheckMenuItem(hwndMenu, IDM_PICTURES, cfg.pictures != 0);
    WinCheckMenuItem(hwndMenu, IDM_SAVEONEXIT, cfg.saveonexit != 0);
    WinCheckMenuItem(hwndMenu, IDM_FRAME, frameHidden);
    UpdateMenus();
}

static const char *szHelpFiles[LANG_COUNT] =
{
    "Kniffel_en.hlp", "Kniffel_es.hlp", "Kniffel_nl.hlp",
    "Kniffel_de.hlp", "Kniffel_fr.hlp", "Kniffel_it.hlp"
};

static void SetHelpLanguage(int lang)
{
    HELPINIT mainHelp;
    FILE    *fp;
    char     szMsg[CCHMAXPATH + 160];

    if( hwndHelpInst != NULLHANDLE )
    {
        WinAssociateHelpInstance(NULLHANDLE, hwndFrame);
        WinDestroyHelpInstance(hwndHelpInst);
        hwndHelpInst = NULLHANDLE;
    }

    strcpy(szHelpLib, szExeDir);
    strcat(szHelpLib, "help\\");
    strcat(szHelpLib, szHelpFiles[lang]);
    fp = fopen(szHelpLib, "rb");
    if( fp )
        fclose(fp);
    else
        strcpy(szHelpLib, szHelpFiles[lang]);

    memset(&mainHelp, 0, sizeof(mainHelp));
    mainHelp.cb = sizeof(HELPINIT);
    mainHelp.phtHelpTable = (PHELPTABLE)MAKEULONG(HID_MAIN, 0xFFFF);
    mainHelp.pszHelpWindowTitle = (PSZ)tr(STR_HELP_TITLE);
    mainHelp.fShowPanelId = CMIC_HIDE_PANEL_ID;
    mainHelp.pszHelpLibraryName = (PSZ)szHelpLib;

    hwndHelpInst = WinCreateHelpInstance(hab, &mainHelp);
    if( hwndHelpInst != NULLHANDLE )
        WinAssociateHelpInstance(hwndHelpInst, hwndFrame);
    else if( mainHelp.ulReturnCode != 0 )
    {
        sprintf(szMsg, tr(STR_HELP_MISSING), szHelpFiles[lang]);
        WinMessageBox(HWND_DESKTOP, hwndFrame, (PSZ)szMsg, (PSZ)"Kniffel", 0, MB_OK | MB_WARNING | MB_MOVEABLE);
    }
}

static void SetLanguage(int lang)
{
    if( lang < 0 || lang >= LANG_COUNT )
        lang = LANG_EN;

    current_lang = lang;
    cfg.current_lang = lang;
    RelabelMenu();
    SyncMenus();
    SetHelpLanguage(lang);
    Redraw();
}

static void ToggleFrameControls(void)
{
    RECTL rcl;
    HWND  hwndNew;

    WinQueryWindowRect(hwndClient, &rcl);       /* the client keeps its size */
    hwndNew = frameHidden ? hwndFrame : hwndPark;
    WinSetParent(hwndTitleBar, hwndNew, FALSE);
    WinSetParent(hwndSysMenu, hwndNew, FALSE);
    WinSetParent(hwndMinMax, hwndNew, FALSE);
    WinSetParent(hwndMenu, hwndNew, FALSE);
    frameHidden = !frameHidden;

    WinSendMsg(hwndFrame, WM_UPDATEFRAME,
               MPFROMLONG(FCF_TITLEBAR | FCF_SYSMENU | FCF_MINMAX | FCF_MENU), 0);
    WinCalcFrameRect(hwndFrame, &rcl, FALSE);
    WinSetWindowPos(hwndFrame, HWND_TOP, 0, 0, rcl.xRight - rcl.xLeft,
                    rcl.yTop - rcl.yBottom, SWP_SIZE);
    WinInvalidateRect(hwndFrame, NULL, TRUE);
    WinUpdateWindow(hwndFrame);
    WinCheckMenuItem(hwndMenu, IDM_FRAME, frameHidden);
}

/*** Window procedure *********************************************************/

static void LoadBitmaps(void)
{
    HPS hps = WinGetPS(hwndClient);
    int i;

    for( i = 0; i < 13; i++ )
        hbmDice[i] = GpiLoadBitmap(hps, NULLHANDLE, BID_DICE + i, 0, 0);
    for( i = 1; i <= NCAT; i++ )
        hbmRow[i] = GpiLoadBitmap(hps, NULLHANDLE, BID_ROW + i, 0, 0);
    hbmBtn[B_ROLL]   = GpiLoadBitmap(hps, NULLHANDLE, BID_ROLL, 0, 0);
    hbmBtn[B_INVERT] = GpiLoadBitmap(hps, NULLHANDLE, BID_INVERT, 0, 0);
    hbmBtn[B_NEXT]   = GpiLoadBitmap(hps, NULLHANDLE, BID_NEXT, 0, 0);
    hbmBtn[B_UNDO]   = GpiLoadBitmap(hps, NULLHANDLE, BID_UNDO, 0, 0);
    hbmBtn[B_ABORT]  = GpiLoadBitmap(hps, NULLHANDLE, BID_ABORT, 0, 0);
    WinReleasePS(hps);
}

static void FreeBitmaps(void)
{
    int i;

    for( i = 0; i < 13; i++ )
        if( hbmDice[i] ) GpiDeleteBitmap(hbmDice[i]);
    for( i = 1; i <= NCAT; i++ )
        if( hbmRow[i] ) GpiDeleteBitmap(hbmRow[i]);
    for( i = 0; i < NBTN; i++ )
        if( hbmBtn[i] ) GpiDeleteBitmap(hbmBtn[i]);
}

MRESULT EXPENTRY ClientWndProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
    HPS    hps;
    RECTL  rcl;
    ULONG  fs;
    USHORT ch, vk;
    HWND   hwndHelp;

    switch( msg )
    {
        case WM_CREATE:
            hwndClient = hwnd;
            LoadBitmaps();
            break;

        case WM_PAINT:
            hps = WinBeginPaint(hwnd, NULLHANDLE, &rcl);
            Layout();
            WinFillRect(hps, &rcl, CLR_DARKGREEN);
            if( playing )
            {
                PaintInfo(hps);
                PaintDice(hps);
                PaintButtons(hps);
                PaintTable(hps);
            }
            else
                PaintIdle(hps);
            WinEndPaint(hps);
            return 0;

        case WM_BUTTON1CLICK:
        case WM_BUTTON1DBLCLK:
            Layout();
            OnClick((SHORT)SHORT1FROMMP(mp1), (SHORT)SHORT2FROMMP(mp1));
            WinSetFocus(HWND_DESKTOP, hwnd);
            return (MRESULT)TRUE;

        case WM_CHAR:
            fs = SHORT1FROMMP(mp1);
            if( (fs & KC_KEYUP) || !playing )
                break;
            ch = SHORT1FROMMP(mp2);
            vk = SHORT2FROMMP(mp2);
            if( (fs & KC_CHAR) && ch == ' ' )
                { DoRoll(); return (MRESULT)TRUE; }
            if( (fs & KC_CHAR) && ch >= '1' && ch <= '5' )
                { ToggleHold(ch - '1'); return (MRESULT)TRUE; }
            if( (fs & KC_CHAR) && (ch == 'i' || ch == 'I') )
                { DoInvert(); return (MRESULT)TRUE; }
            if( fs & KC_VIRTUALKEY )
            {
                if( vk == VK_NEWLINE || vk == VK_ENTER )
                    { DoNext(); return (MRESULT)TRUE; }
                if( vk == VK_BACKSPACE )
                    { DoUndo(); return (MRESULT)TRUE; }
            }
            break;

        case WM_COMMAND:
            switch( SHORT1FROMMP(mp1) )
            {
                case IDM_NEWGAME:   StartNewGame();                       break;
                case IDM_QUIT:      DoAbort();                            break;
                case IDM_HITLIST:
                    WinDlgBox(HWND_DESKTOP, hwndFrame, HitlistDlgProc, NULLHANDLE, IDD_HITLIST, NULL);
                    break;
                case IDM_EXIT:      WinPostMsg(hwnd, WM_QUIT, 0, 0);      break;
                case IDM_PICTURES:
                    cfg.pictures = !cfg.pictures;
                    SyncMenus();
                    Redraw();
                    break;
                case IDM_FRAME:     ToggleFrameControls();                break;
                case IDM_SAVEONEXIT:
                    cfg.saveonexit = !cfg.saveonexit;
                    SyncMenus();
                    break;
                case IDM_LANG_EN: case IDM_LANG_ES: case IDM_LANG_NL:
                case IDM_LANG_DE: case IDM_LANG_FR: case IDM_LANG_IT:
                    SetLanguage(SHORT1FROMMP(mp1) - IDM_LANG_EN);
                    break;
                case IDM_ABOUT:
                    WinDlgBox(HWND_DESKTOP, hwndFrame, AboutDlgProc, NULLHANDLE, IDD_ABOUT, NULL);
                    break;
                case IDM_GENERALHELP:
                    hwndHelp = WinQueryHelpInstance(hwnd);
                    if( hwndHelp )
                        WinSendMsg(hwndHelp, HM_DISPLAY_HELP, MPFROMSHORT(HID_GENERAL), MPFROMSHORT(HM_RESOURCEID));
                    break;
                case IDM_HELPINDEX:
                    hwndHelp = WinQueryHelpInstance(hwnd);
                    if( hwndHelp )
                        WinSendMsg(hwndHelp, HM_HELP_INDEX, 0, 0);
                    break;
                case IDM_HELPONHELP:
                    hwndHelp = WinQueryHelpInstance(hwnd);
                    if( hwndHelp )
                        WinSendMsg(hwndHelp, HM_DISPLAY_HELP, 0, 0);
                    break;
            }
            return 0;

        case WM_DESTROY:
            FreeBitmaps();
            break;
    }
    return WinDefWindowProc(hwnd, msg, mp1, mp2);
}

/*** Main *********************************************************************/

int main(void)
{
    HMQ    hmq;
    QMSG   qmsg;
    ULONG  flFrame = FCF_TITLEBAR | FCF_SYSMENU | FCF_SIZEBORDER | FCF_MINMAX |
                     FCF_TASKLIST | FCF_MENU | FCF_ICON | FCF_ACCELTABLE;
    LONG   cxScreen, cyScreen, winW, winH, winX, winY;
    PTIB   ptib;
    PPIB   ppib;
    CHAR  *p;

    if( bldlevel[0] != '@' )        /* keeps the BLDLEVEL string in the executable */
        return 1;

    srand((unsigned)time(NULL));

    szExeDir[0] = 0;
    if( DosGetInfoBlocks(&ptib, &ppib) == 0 )
        if( DosQueryModuleName(ppib->pib_hmte, sizeof(szExeDir), szExeDir) == 0 )
        {
            p = strrchr(szExeDir, '\\');
            if( p )  *(p + 1) = 0;
            else     szExeDir[0] = 0;
        }

    LoadSettings();
    current_lang = (int)cfg.current_lang;
    nPlayers = (int)cfg.players;

    hab = WinInitialize(0);
    hmq = WinCreateMsgQueue(hab, 0);

    WinRegisterClass(hab, "KniffelClient", ClientWndProc, CS_SIZEREDRAW, 0);

    hwndFrame = WinCreateStdWindow(HWND_DESKTOP, 0, &flFrame, "KniffelClient", "Kniffel",
                                   0, NULLHANDLE, WID_MAIN, &hwndClient);
    if( !hwndFrame )
        return 2;

    hwndMenu     = WinWindowFromID(hwndFrame, FID_MENU);
    hwndTitleBar = WinWindowFromID(hwndFrame, FID_TITLEBAR);
    hwndSysMenu  = WinWindowFromID(hwndFrame, FID_SYSMENU);
    hwndMinMax   = WinWindowFromID(hwndFrame, FID_MINMAX);
    hwndPark     = WinCreateWindow(HWND_OBJECT, WC_FRAME, "", 0L, 0, 0, 0, 0,
                                   NULLHANDLE, HWND_TOP, 0, NULL, NULL);

    BuildIconList();
    SetLanguage(current_lang);

    /* 1024x768 (or the whole screen if smaller), centered */
    cxScreen = WinQuerySysValue(HWND_DESKTOP, SV_CXSCREEN);
    cyScreen = WinQuerySysValue(HWND_DESKTOP, SV_CYSCREEN);
    winW = (cxScreen >= 1024L) ? 1024L : cxScreen;
    winH = (cyScreen >= 768L)  ? 768L  : cyScreen;
    winX = (cxScreen - winW) / 2;
    winY = (cyScreen - winH) / 2;
    WinSetWindowPos(hwndFrame, HWND_TOP, winX, winY, winW, winH,
                    SWP_SIZE | SWP_MOVE | SWP_ACTIVATE | SWP_SHOW);

    WinPostMsg(hwndClient, WM_COMMAND, MPFROM2SHORT(IDM_NEWGAME, 0), 0);

    while( WinGetMsg(hab, &qmsg, 0, 0, 0) )
        WinDispatchMsg(hab, &qmsg);

    if( cfg.saveonexit )
        SaveSettings();

    if( frameHidden )
    {
        WinSetParent(hwndTitleBar, hwndFrame, FALSE);
        WinSetParent(hwndSysMenu, hwndFrame, FALSE);
        WinSetParent(hwndMinMax, hwndFrame, FALSE);
        WinSetParent(hwndMenu, hwndFrame, FALSE);
    }
    WinDestroyWindow(hwndPark);
    if( hwndHelpInst )
    {
        WinAssociateHelpInstance(NULLHANDLE, hwndFrame);
        WinDestroyHelpInstance(hwndHelpInst);
    }
    WinDestroyWindow(hwndFrame);
    WinDestroyMsgQueue(hmq);
    WinTerminate(hab);
    return 0;
}
