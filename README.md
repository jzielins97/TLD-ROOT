# TLD-ROOT

Jest to kod do tworzenia wykresów z TLD i obliczania współczynnika kalibracji (tego na razie nie jestem pewny czy jest dobrze)

Pliki z danymi zostały zmienione tak aby łatwo się obrabiało je w root

## Korzystanie

aby uruchomić program należy upewnić się, że pliki z danymi jak i bibioteka TLD.h znajdują się w tym samym folderze co kod TLD.C. Następnie wpisać "root -l TLD.C" w terminalu. 
Jeśli chcemy Włączyć program ale nie chcemy zapisywać wykresów, robimy: 
"root -l"
".x TLD.C(0,1)"

Jeśli nie interesują nas wykresy z anilacji, należy ustawić drugi argument na 0: ".x TLD.C(0, 0)" lub ".x TLD.C(1,0)" jeśli chcemy zapisać wykresy!

Plik output.txt zawiera tabelki z wynikami analizy, na obecną chwilę są to współczynniki kalibracji dla wszystkich kasetek i średnie współczynniki dla poszególnych pastylek (pierwsze cztery pastylki są dla bety, pozostałe dla gammy). Wszystkie wartości są podawane z niepewnościami.

~Jakub Zieliński
