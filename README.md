# Badanie Wydajności Tablic Haszujących (Hash Tables Benchmark)

Projekt realizuje i porównuje trzy popularne metody rozwiązywania kolizji w tablicach haszujących. Celem badań było empiryczne zweryfikowanie teoretycznej złożoności obliczeniowej operacji wstawiania (`insert`) oraz usuwania (`remove`) dla różnych stopniu zagęszczenia danych.

## 🚀 Zaimplementowane Struktury

Wszystkie klasy dziedziczą po wspólnym interfejsie `IHashTable` i operują na liczbach całkowitych (`int`), co pozwoliło na zminimalizowanie narzutu systemowego i badanie czystej wydajności algorytmów:

1. **Separate Chaining (Metoda Łańcuchowa)** – rozwiązywanie kolizji za pomocą list/wektorów dynamicznych przypisanych do każdego slotu.
2. **Linear Probing (Próbkowanie Liniowe)** – adresowanie otwarte z liniowym przeszukiwaniem kolejnych komórek ($idx + i$).
3. **Quadratic Probing (Próbkowanie Kwadratowe)** – adresowanie otwarte z przesunięciem kwadratowym ($idx + i^2$), redukujące zjawisko klastrowania pierwotnego.

---

## 📊 Scenariusze Testowe

Wydajność struktur została przetestowana dla $N = 2000$ elementów przy rozmiarze tablicy `TABLE_SIZE = 5003` w trzech przypadkach:

* **Przypadek Najlepszy (Optymistyczny):** Dane unikalne i dobrze rozproszone, brak kolizji na startowych indeksach.
* **Przypadek Średni:** Tablica wstępnie zapełniona w ~50% losowymi danymi przed uruchomieniem właściwego testu.
* **Przypadek Najgorszy (Pesymistyczny):** Celowe wymuszenie maksymalnej liczby kolizji (wszystkie generowane klucze haszują się do indeksu `0`).

---

## 📈 Wyniki Eksperymentu

Pomiary czasu wykonania operacji dla 2000 elementów (w mikrosekundach $\mu s$):

| Metoda | Przypadek | Czas dodawania [µs] | Czas usuwania [µs] |
| :--- | :--- | :--- | :--- |
| **Separate Chaining** | Najlepszy | 230 | 181 |
| **Linear Probing** | Najlepszy | 24 | 32 |
| **Quadratic Probing** | Najlepszy | 82 | 53 |
| **Separate Chaining** | Średni | 236 | 239 |
| **Linear Probing** | Średni | 58 | 36 |
| **Quadratic Probing** | Średni | 33 | 33 |
| **Separate Chaining** | Najgorszy | 45 | 537 |
| **Linear Probing** | Najgorszy | 7450 | 7612 |
| **Quadratic Probing** | Najgorszy | 8638 | 8722 |

### 💡 Główne Wnioski
1. **Adresowanie otwarte górą w optymistycznych warunkach:** Dzięki doskonałej lokalności danych w pamięci podręcznej (cache), `Linear Probing` i `Quadratic Probing` osiągają czasy kilkukrotnie niższe niż `Separate Chaining`, która wymaga alokacji nowych węzłów.
2. **Degradacja do $O(n)$:** W przypadku najgorszym, kiedy wszystkie elementy trafiają pod ten sam indeks, metody adresowania otwartego odnotowują potężny skok czasu (z kilkudziesięciu $\mu s$ do ponad $7-8\ ms$). `Separate Chaining` zachowuje stabilny czas wstawiania ($O(1)$ na koniec listy), ale czas usuwania rośnie ze względu na konieczność przeszukania całego łańcucha.

---

## 🛠️ Uruchomienie Projektu

Projekt wykorzystuje system budowania **CMake**.

```bash
# Sklonuj repozytorium (upewnij się, że jesteś na branchu benchmarks)
git clone <link-do-twojego-repozytorium>
cd <katalog-projektu>

# Skompiluj i uruchom program
mkdir build && cd build
cmake ..
cmake --build .
./main
