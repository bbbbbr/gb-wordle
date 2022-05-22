# gb-wordyl

A Wordle clone for the Nintendo Game Boy / Color and Analogue Pocket!

This is a re-written and greatly expanded fork (by [bbbbbr](https://github.com/bbbbbr/gb-wordle)) of the original version by [stacksmashing](https://github.com/stacksmashing/gb-wordle) ([twitter](http://twitter.com/ghidraninja)).

It adds a full dictionary (versus the bloom filter), thousands more solution words, multiple dictionary languages, Game Boy Color support, and many other features.


### Download ROMs and Play Online

Downloads and online playable version are at: https://bbbbbr.itch.io/gb-wordyl

- [User's Manual](Manual.md)

![GB-Wordyl gameplay](/info/gb-wordyl_demo_cgb.gif)


### Credits, Contributors and Thanks

Language / UI Translation credits:
  - German: Skite2001 - https://twitter.com/skite2001
  - Dutch: Ferrante Crafts - https://ferrantecrafts.com
  - Brazilian Portuguese: Daniel Tolentino - https://github.com/DanielTolentino
  - Cornish:
    - SJD (https://sjd-sjd.itch.io/)
    - Niwlen Ster
    - Kamm Cam
    - Dyski Kernowek Discord Group
    - Steve Harris (https://kerdle.vercel.app and https://an-wiasva.herokuapp.com)
    - Gerlyver Kernewek (https://cornishdictionary.org.uk)


Additional code and contributions from:
  - Daeo : Cart and box Graphics
  - [Coffee "Valen" Bat](https://twitter.com/cofebbat) : Game Sound FX and [CBTFX Driver](https://github.com/datguywitha3ds/CBT-FX)
  - [toxa](https://github.com/untoxa/) : Ferrante Crafts 31k ROM + 1k Flash cart support
  - [arpruss](https://github.com/arpruss/gb-fiver) : Highlighting fixes, Improved Dictionary compression and lookup speed
  - [zeta_two](https://github.com/ZetaTwo/gb-wordle) : Previous dictionary compression
  - [stacksmashing](https://github.com/stacksmashing/gb-wordle) : original base code (mostly now rewritten)

Built using [GBDK-2020](https://github.com/gbdk-2020/gbdk-2020) (4.0.6 / 4.1.0-Pre+)

### Features
  - Game stats: Won, Lost, Streak & Win Percentage
  - Hard mode
  - Auto-fill letters of previous exact matches
  - Skip Auto-filled letters for faster letter entry
  - Full official English answer word list and dictionary less a couple cringy words (~12,900 words)
  - Super Game Boy Border
  - All in a 32K ROM
  - Multiple language dictionaries (different ROM for each)
    - Deutsch (DE), English (EN), Español (ES), Français (FR), Italiano (IT), Nederlands (NL), Latin (LA), Português Brasileiro (PT-BR)
    - No words with special chars, just English A-Z letters
    - Translated UI text for Deutsch (DE), English (EN), Español (ES), Nederlands (NL), Português Brasileiro (PT-BR)

### Controls:
  - A: Add Letter
  - B: Remove Letter
  - START: Submit guess
  - SELECT + B: Move Board Cursor Left
  - SELECT + A:  Move Board Cursor Right
  - SELECT + START: Auto-fill exact matches of previous guesses
  - 3 x SELECT: Options menu (Stats, Reset Stats, Forfeit Round)
  - ARROW KEYS: Move Keyboard Cursor


![GB-Wordyl gameplay](/info/gb-wordyl_demo.gif)


