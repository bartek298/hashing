#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include "SeparateChainingTable.hpp"
#include "LinearProbingTable.hpp"
#include "QuadraticProbingTable.hpp"
#include <iomanip>
#include <fstream>
const int N = 2000;
const int TABLE_SIZE = 5003;
std::vector<int> generateRandomData(int count) {
    std::vector<int> data;
    for (int i = 0; i < count; i++) {
        data.push_back(i * 17 + 1); // unikalne, dobrze rozproszone liczby
    }
    return data;
}
std::vector<int> generateWorstCaseData(int count) {
    std::vector<int> data;
    for (int i = 0; i < count; i++) {
        data.push_back(i * TABLE_SIZE); // Każda ta liczba % TABLE_SIZE da dokładnie 0!
    }
    return data;
}
void runBenchmark(IHashTable* table, const std::string& tableName, const std::string& caseName,
                  const std::vector<int>& insertData, const std::vector<int>& removeData,
                  std::ofstream& file) {

    std::cout << "\n--- Testy dla: " << tableName << " (" << caseName << ") ---" << std::endl;

    // 1. POMIAR DODAWANIA
    auto startInsert = std::chrono::high_resolution_clock::now();
    for (int key : insertData) { // <-- Zmienione z const auto& key na zwykłe int key (lub auto key)
        table->insert(key);
    }
    auto endInsert = std::chrono::high_resolution_clock::now();
    auto durationInsert = std::chrono::duration_cast<std::chrono::microseconds>(endInsert - startInsert).count();
    std::cout << "  Czas dodawania " << insertData.size() << " elementow: " << durationInsert << " us" << std::endl;

    // 2. POMIAR USUWANIA
    auto startRemove = std::chrono::high_resolution_clock::now();
    for (int key : removeData) { // <-- Zmienione na int key
        table->remove(key);
    }
    auto endRemove = std::chrono::high_resolution_clock::now();
    auto durationRemove = std::chrono::duration_cast<std::chrono::microseconds>(endRemove - startRemove).count();
    std::cout << "  Czas usuwania " << removeData.size() << " elementow: " << durationRemove << " us" << std::endl;

    // ZAPIS DO PLIKU
    if (file.is_open()) {
        file << tableName << ";" << caseName << ";" << durationInsert << ";" << durationRemove << "\n";
    }
}
int main() {
    srand(time(nullptr));

    // Otwieramy plik do zapisu wyników
    std::ofstream wynikiPlik("wyniki_benchmarku1.csv");

    // Zapisujemy nagłówek kolumn w pliku CSV
    if (wynikiPlik.is_open()) {
        wynikiPlik << "Metoda;Przypadek;CzasDodawania_us;CzasUsuwania_us\n";
    }

    std::cout << "====================================================" << std::endl;
    std::cout << "   ROZPOCZECIE BADAN WYDAJNOSCIOWYCH TABLIC HASZ" << std::endl;
    std::cout << "====================================================" << std::endl;

    // Generujemy paczki danych do testów
    auto bestInsertData = generateRandomData(N);
    auto bestRemoveData = bestInsertData;

    auto averageInsertData = generateRandomData(N);
    auto averageRemoveData = averageInsertData;

    auto worstInsertData = generateWorstCaseData(N);
    auto worstRemoveData = worstInsertData;

    // =================================================================
    // 1. CASE: NAJLEPSZY
    // =================================================================
    std::cout << "\n>>>> 1. PRZYPADEK NAJLEPSZY (Brak kolizji) <<<<" << std::endl;

    IHashTable* scBest = new SeparateChainingTable(TABLE_SIZE);
    IHashTable* lpBest = new LinearProbingTable(TABLE_SIZE);
    IHashTable* qpBest = new QuadraticProbingTable(TABLE_SIZE);

    runBenchmark(scBest, "Separate Chaining", "Najlepszy", bestInsertData, bestRemoveData, wynikiPlik);
    runBenchmark(lpBest, "Linear Probing", "Najlepszy", bestInsertData, bestRemoveData, wynikiPlik);
    runBenchmark(qpBest, "Quadratic Probing", "Najlepszy", bestInsertData, bestRemoveData, wynikiPlik);

    delete scBest; delete lpBest; delete qpBest;

    // =================================================================
    // 2. CASE: ŚREDNI
    // =================================================================
    std::cout << "\n====================================================" << std::endl;
    std::cout << ">>>> 2. PRZYPADEK SREDNI (Zapełnienie ~50%) <<<<" << std::endl;

    IHashTable* scAvg = new SeparateChainingTable(TABLE_SIZE);
    IHashTable* lpAvg = new LinearProbingTable(TABLE_SIZE);
    IHashTable* qpAvg = new QuadraticProbingTable(TABLE_SIZE);

    auto preFillData = generateRandomData(TABLE_SIZE / 2);
    for (const auto& key : preFillData) {
        scAvg->insert(key); lpAvg->insert(key); qpAvg->insert(key);
    }

    runBenchmark(scAvg, "Separate Chaining", "Sredni", averageInsertData, averageRemoveData, wynikiPlik);
    runBenchmark(lpAvg, "Linear Probing", "Sredni", averageInsertData, averageRemoveData, wynikiPlik);
    runBenchmark(qpAvg, "Quadratic Probing", "Sredni", averageInsertData, averageRemoveData, wynikiPlik);

    delete scAvg; delete lpAvg; delete qpAvg;

    // =================================================================
    // 3. CASE: NAJGORSZY
    // =================================================================
    std::cout << "\n====================================================" << std::endl;
    std::cout << ">>>> 3. PRZYPADEK NAJGORSZY (Maksymalne kolizje) <<<<" << std::endl;

    IHashTable* scWorst = new SeparateChainingTable(TABLE_SIZE);
    IHashTable* lpWorst = new LinearProbingTable(TABLE_SIZE);
    IHashTable* qpWorst = new QuadraticProbingTable(TABLE_SIZE);

    runBenchmark(scWorst, "Separate Chaining", "Najgorszy", worstInsertData, worstRemoveData, wynikiPlik);
    runBenchmark(lpWorst, "Linear Probing", "Najgorszy", worstInsertData, worstRemoveData, wynikiPlik);
    runBenchmark(qpWorst, "Quadratic Probing", "Najgorszy", worstInsertData, worstRemoveData, wynikiPlik);

    delete scWorst; delete lpWorst; delete qpWorst;

    // Zamykamy plik po zakończeniu wszystkich testów
    wynikiPlik.close();
    std::cout << "\n[INFO] Wyniki zostaly pomyslnie zapisane do pliku 'wyniki_benchmarku.csv'!" << std::endl;

    return 0;
}