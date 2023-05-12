# Féléves feladat leírása
## Buborékrendezés

A feladat célja egy 100000 elemű tömb rendezése szekvenciálisan, majd szálkezeléssel.
Végül a kapott eredményeket összehasonlítjuk és az eredmények alapján eldöntjük, melyik módszer a leggyorsabb.
A programok különböző problémaméretekkel is tudnak dolgozni.

A buborékrendezés egy egyszerű algoritmus, hatékonysága rosszabb, mint a más összehasonlításos rendezési algoritmusoké. Az átlagos és legrosszabb esetben is O(n^2) időkomplexitással rendelkezik, ahol "n" a tömb mérete.

## A feladat felépÍtése
A feladatot négy külön programban oldottam meg, minden technológia külön programban kapott helyet.

# A feladatban használt technológiák

## openMPI (Message Passing Interface) 
A programrész elején inicializáljuk az MPI-t az MPI_Init függvénnyel. Ezután megkapjuk a folyamat sorszámát (rank) és a folyamatok számát (size) az MPI_Comm_rank és MPI_Comm_size függvényekkel.

Létrehozunk egy N méretű egész számokból álló tömböt (arr), amelyet a fő szál (rank 0) fog feltölteni. A malloc függvényt használjuk a dinamikus memóriaterület lefoglalásához.

Az MPI_Scatter függvénnyel a fő szál szétosztja a tömb elemeit a résztömbök között a többi folyamathoz. Ez a függvény a arr tömb tartalmát darabolja fel, és minden folyamatnak átadja a saját résztömbjét (sub_arr).

Az algoritmus egy buborékrendezést végez a résztömbön. A buborékrendezés egy egyszerű rendezési algoritmus, amelyben az elemeket páronként összehasonlítjuk és szükség esetén cseréljük őket, így a legnagyobb elemek a tömb végére "buborékolnak".

Az MPI_Gather függvénnyel a rendezett résztömbök visszakerülnek az arr tömbbe a fő szálon. Ez összegyűjti a résztömböket és visszatölti az eredményeket az arr tömbbe

## Pthread
Az algoritmus ugyanaz a buborékrendezési algoritmus, mint az előző példában. A szálak egymástól függetlenül dolgoznak a saját részükön, és nincs szükségük kommunikációra egymás között.

A szálak létrehozásához és futtatásához a pthread könyvtárat használjuk. A pthread_t típusú handles tömbben tároljuk a szálak kezelőit. A pthread_create függvény létrehozza a szálakat és azokat a bubble_sort függvényt hívja meg. A thread változó az adott szál sorszámát jelöli.

A pthread_join függvénnyel a fő szál megvárja, hogy az összes szál befejezze a futását, mielőtt folytatódna a program.

## OpenMP (Open Multi-Processing)
Az algoritmus a bubble sort ciklusait tartalmazza, de most az OpenMP direktívával párhuzamosítjuk a műveletet. A #pragma omp parallel sorral jelöljük a párhuzamos régiót, és a num_threads(2) opcióval megadjuk, hogy hány szálon szeretnénk futtatni a kódot. Itt például 2 szálat használunk.

Az omp_get_thread_num() függvény visszaadja a folyamat sorszámát, és az omp_get_num_threads() függvény visszaadja a folyamatok számát a párhuzamos régióban. Ezeket a változókat használjuk a buborékrendezés szálankénti felosztásához.

Az algoritmusban a buborékrendezést ugyanúgy végezzük, mint az előző példákban. A különbség az, hogy most a buborékrendezés szálanként történik, és az adott szál csak a hozzárendelt résztömbön dolgozik.

