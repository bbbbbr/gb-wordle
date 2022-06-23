# gb-wordyl

A Wordle clone for the Nintendo Game Boy / Color and Analogue Pocket!

This is a re-written and greatly expanded fork (by [bbbbbr](https://github.com/bbbbbr/gb-wordle)) of the original version by [stacksmashing](https://github.com/stacksmashing/gb-wordle) ([twitter](http://twitter.com/ghidraninja)).

It adds a full dictionary (versus the bloom filter), thousands more solution words, multiple dictionary languages, Game Boy Color support, and many other features.


### Physical Cartridge available at Ferrante Crafts:

https://www.etsy.com/listing/1251187027/gb-wordyl-game-cartridge-for-game-boy

![GB-Wordyl cart and box](/info/gb-wordyl-box-cart.jpg)


### Download ROMs and Play Online

Downloads and online playable version are at: https://bbbbbr.itch.io/gb-wordyl

- [User's Manual](Manual.md)

![GB-Wordyl gameplay](/info/gb-wordyl_demo_cgb.gif)

### Features
  - Game stats: Won, Lost, Streak & Win Percentage
  - Hard mode
  - Auto-fill letters of previous exact matches
  - Skip Auto-filled letters for faster letter entry
  - Full official English answer word list and dictionary less a couple cringy words (~12,900 words)
  - Super Game Boy Border
  - All in a 32K ROM
  - Multiple language dictionaries (different ROM for each)
    - Deutsch (DE), English (EN), Español (ES), Français (FR), Italiano (IT), Nederlands (NL), Latin (LA), Português Brasileiro (PT-BR), Cornish (KW), català (CA)
    - No words with special chars, just English A-Z letters
    - Translated UI text for Deutsch (DE), English (EN), Español (ES), Nederlands (NL), Português Brasileiro (PT-BR), Cornish (KW), català (CA)

### Controls:
  - A: Add Letter
  - B: Remove Letter
  - START: Submit guess
  - SELECT + B: Move Board Cursor Left
  - SELECT + A:  Move Board Cursor Right
  - SELECT + START: Auto-fill exact matches of previous guesses
  - 3 x SELECT: Options menu (Stats, Reset Stats, Forfeit Round)
  - ARROW KEYS: Move Keyboard Cursor


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
  - Catalan:
    - [@urixturing](https://twitter.com/urixturing)
    - [@alvaromartinezmajado](https://github.com/alvaromartinezmajado)
    - Their web version is at: https://factorialunar.github.io/vocable/
    - For this repo see the [lang_catalan branch](https://github.com/bbbbbr/gb-wordle/tree/feature/lang_catalan)

Additional code and contributions from:
  - Daeo : Cart and box Graphics
  - [Coffee "Valen" Bat](https://twitter.com/cofebbat) : Game Sound FX and [CBTFX Driver](https://github.com/datguywitha3ds/CBT-FX)
  - [toxa](https://github.com/untoxa/) : Ferrante Crafts 31k ROM + 1k Flash cart support
  - [arpruss](https://github.com/arpruss/gb-fiver) : Highlighting fixes, Improved Dictionary compression and lookup speed
  - [zeta_two](https://github.com/ZetaTwo/gb-wordle) : Previous dictionary compression
  - [stacksmashing](https://github.com/stacksmashing/gb-wordle) : original base code (mostly now rewritten)

Built using [GBDK-2020](https://github.com/gbdk-2020/gbdk-2020) (4.0.6 / 4.1.0-Pre+)

![GB-Wordyl gameplay](/info/gb-wordyl_demo.gif)


### Building from source:

  - Compress the dictionaries: `make dictionaries`
  - Build the ROM: `make` (default language `en` and default cart `31k_1kflash`)
    - Language option: `make LANG_CODE=<lowercase 2 letter language code>`
    - Cart option: `CART_TYPE=<cart type>` (`mbc5`, `31k_1kflash`. `32k_nosave`)


