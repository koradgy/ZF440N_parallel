# Féléves feladat leírása
## Miller-Rabin prímkereső módszer
A Miller-Rabin prímteszt egy hatékony és megbízható algoritmus a prímek gyors és hatékony tesztelésére. Azonban a nagyobb számoknál már a szekvenciális implementáció is lassú lehet. A feladat célja az algoritmus hatékonyságának növelése párhuzamosítással.

A célunk ebben a projektben az lesz, hogy implementáljuk a Miller-Rabin prímtesztet párhuzamos algoritmusok segítségével. Konkrétan, az alábbi párhuzamos megoldásokat készítjük el:

* Szekvenciális megoldás
* POSIX szálak
* OpenMP
* MPI

A projekt során implementáljuk az összes fenti megoldást, és összehasonlítjuk azok teljesítményét különböző méretű inputokkal. Végül a kaptt eredményeket összehasonlítjuk, ezzel vizsgálva, hogy a felhasznált technológiák közül, melyik a legalkalmasabb a feladat megoldásához.

## Párhuzamosítás

A feladatban létrehozunk egy 40 elemű halmazt, amely a vizsgálandó számokat tartalmazza, majd ezeket a számokat osztjuk szét a szálak között vizsgálatra, a felsorolt technológiákat alkalmazva 1, 2 illetve 4 szál használatával.
