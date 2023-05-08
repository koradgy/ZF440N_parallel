# Féléves feladat leírása
## Buborékrendezzés

A feladat célja egy 100000 elemű tömb rendezése szekvenciálisan, majd szálkezeléssel.
Végül a kapott eredményeket összehasonlítjuk, az eredmények alapján eldöntjük, melyik módszer a leggyorsabb.

## A program felépÍtése
* óra indítása
* kezdeti tömb létrehozása
* tömb feltöltése random számokkal
* a tömb rendezése szálkezelés nélkül, majd pthreads/omp/openMPI technológiákkal 2 illetve 4 szálat használva 
* részidő mérés minden rendezés után
* A kapott eredmények fájlba írása.

## openMPI
A programrész elején inicializáljuk az MPI-t az MPI_Init függvénnyel. Ezután megkapjuk a folyamat sorszámát (rank) és a folyamatok számát (size) az MPI_Comm_rank és MPI_Comm_size függvényekkel.

Létrehozunk egy N méretű egész számokból álló tömböt (arr), amelyet a fő szál (rank 0) fog feltölteni. A malloc függvényt használjuk a dinamikus memóriaterület lefoglalásához.

Az MPI_Scatter függvénnyel a fő szál szétosztja a tömb elemeit a résztömbök között a többi folyamathoz. Ez a függvény a arr tömb tartalmát darabolja fel, és minden folyamatnak átadja a saját résztömbjét (sub_arr).

Az algoritmus egy buborékrendezést végez a résztömbön. A buborékrendezés egy egyszerű rendezési algoritmus, amelyben az elemeket páronként összehasonlítjuk és szükség esetén cseréljük őket, így a legnagyobb elemek a tömb végére "buborékolnak".

Az MPI_Gather függvénnyel a rendezett résztömbök visszakerülnek az arr tömbbe a fő szálon. Ez összegyűjti a résztömböket és visszatölti az eredményeket az arr tömbbe

## Pthreads
Egy ciklusban elindítunk előbb 2 majd 4 szálat, majd, ha elkészültek lezárjuk öket.

## omp
pragma omp parallel num threads() segítsegével hasonló módon először 2 majd 4 szálon rendezzük a tömbböt.
