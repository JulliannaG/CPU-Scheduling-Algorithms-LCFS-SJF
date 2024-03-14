# CPU-Scheduling-Algorithms-LCFS-SJF
Program symuluje działanie dwóch algorytmów przydziału czasu procesora - LCFS(Last Come First Served), SJF(Shortest Job First).
Algorytmy są testowane dla 100 ciągów. Każdy z ciągów zawiera 100 losowo wygenerowanych wartości czasów przybycia procesów z przedziału [0-20] [s]oraz czasu trwania procesów z przedziału [1-20][s]. Wygenerowane dane wejściowe są takie same dla obu algorytmów. Dane wejściowe są zapisywane do 100 osobnych plików "dane_wejscioweN.csv" dla każdego testowanego ciągu N, a następnie są odczytywane przez program.
Kryteriami oceny algorytmów są średnie wartości czasu oczekiwania na przydzielenie procesora oraz czasu cyklu przetwarzania procesu. Kolejno realizowane procesy wraz z ich czasem oczekiwania i przetwarzania dla pojedynczych ciągów n są zapisywane do osobnych plików, odpowiednio dla każdego algorytmu: "LCFSn.csv" oraz "SJFn.csv". Następnie program wylicza średnie wartości czasów oczekiwania i cyklu przetwarzania dla pojedynczych ciągów oraz dla wszystkich 100 ciągów. Wyniki eksperymentu są zapisywane do pliku "wyniki_eksperymentu.csv". Wszystkie pliki tworzone są w folderze "dane".

