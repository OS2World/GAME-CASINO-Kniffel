# Kniffel for ArcaOS / eComStation / OS/2

Kniffel is the German name of the dice game Yahtzee, for one to five players,
for the OS/2 Presentation Manager.

![Kniffel ScreenShot](/doc/Kniffel.png)

Originally written by Andreas Kieser in 1996-1999 (VisPro/REXX).

## Version

1.10

## License

GNU General Public License v3 - see `doc/LICENSE.txt`

## Features

- 1 to 5 players with names and player symbols (icons from the `icons` folder)
- Dice rolling with hold, take back and next player
- Original Kniffel rules (bonus 35 at 63, full house 25, straights 30/40,
  Kniffel 50)
- Results can be saved to a hit list (`hitlist.hgh`)
- 6-language UI: English, Spanish, Dutch, German, French, Italian
- Online help in the six languages
- Picture buttons or text buttons
- Frame Controls (Ctrl+F)
- Settings saved to `Kniffel.cfg`

## Compile Tools

- Open Watcom 2.0 (`wmake`, `wcc386`, `wlink`, `wrc`, `wipfc`)
- OS/2 Toolkit 4.5

## Build

```
compile-wat.cmd
```

Output: `bin\Kniffel.exe`, `bin\help\Kniffel_xx.hlp` and `bin\icons\`

## Requirements

- OS/2 Warp 4, eComStation, or ArcaOS
- 32-bit Presentation Manager

## Authors

- Original: Andreas Kieser - 1996-1999
- OS/2 port: OS2World community - 2026

## Links

- OS2World: https://www.os2world.com
