#include "benchmark.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <chrono>
#include <vector>
#include <list>
#include <deque>
#include <algorithm>
#include <random>
#include <map>

GenerationResult measureFileGeneration(const std::string& filename, int recordCount) {
    auto start = std::chrono::high_resolution_clock::now();
    
    std::ofstream out(filename);
    if (!out.is_open()) {
        throw std::runtime_error("Nepavyko atidaryti failo rašymui: " + filename);
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 10);

    out << std::left << std::setw(20) << "Vardas" 
        << std::setw(20) << "Pavarde";
    for (int i = 1; i <= 5; ++i) {
        out << std::setw(10) << "ND" + std::to_string(i);
    }
    out << std::setw(10) << "Egz." << "\n";

    for (int i = 1; i <= recordCount; ++i) {
        out << std::left << std::setw(20) << ("VardasNR" + std::to_string(i))
            << std::setw(20) << ("PavardeNR" + std::to_string(i));
        
        for (int j = 0; j < 5; ++j) {
            out << std::setw(10) << dist(gen);
        }
        out << std::setw(10) << dist(gen) << "\n";
    }

    out.close();
    
    auto end = std::chrono::high_resolution_clock::now();
    
    GenerationResult res;
    res.count = recordCount;
    res.duration = std::chrono::duration<double>(end - start).count();
    return res;
}

template<typename Container>
BenchmarkResult runBenchmark(const std::string& filename, int strategy, const std::string& gradeType, const std::string& containerName) {
    BenchmarkResult res;
    res.containerType = containerName;
    res.strategy = strategy;
    
    auto total_start = std::chrono::high_resolution_clock::now();
    
    auto read_start = std::chrono::high_resolution_clock::now();
    Container students = readFromFile<Container>(filename);
    auto read_end = std::chrono::high_resolution_clock::now();
    
    auto sort_start = std::chrono::high_resolution_clock::now();
    for (auto& s : students) {
        calculateFinalGrade(s, gradeType);
    }
    sortStudents(students);
    auto sort_end = std::chrono::high_resolution_clock::now();
    
    auto split_start = std::chrono::high_resolution_clock::now();
    Container vargsiukai;
    switch (strategy) {
        case 1:
            vargsiukai = strategy1Split(students);
            break;
        case 2:
            vargsiukai = strategy2Split(students);
            break;
        case 3:
            vargsiukai = strategy3Split(students);
            break;
    }
    auto split_end = std::chrono::high_resolution_clock::now();
    
    auto write_start = std::chrono::high_resolution_clock::now();
    auto write_to_file = [&](const std::string& fname, const Container& list) {
        std::ofstream out(fname);
        out << std::left << std::setw(20) << "Vardas" << std::setw(20) << "Pavarde" << "Galutinis\n";
        for (const auto& s : list) {
            out << std::left << std::setw(20) << s.getVardas() << std::setw(20) << s.getPavarde() 
                << std::fixed << std::setprecision(2) << s.getGalutinis() << "\n";
        }
        out.close();
    };
    
    write_to_file("vargsiukai.txt", vargsiukai);
    write_to_file("kietiakiai.txt", students);
    auto write_end = std::chrono::high_resolution_clock::now();
    
    auto total_end = std::chrono::high_resolution_clock::now();
    
    res.readDuration = std::chrono::duration<double>(read_end - read_start).count();
    res.sortDuration = std::chrono::duration<double>(sort_end - sort_start).count();
    res.splitDuration = std::chrono::duration<double>(split_end - split_start).count();
    res.writeDuration = std::chrono::duration<double>(write_end - write_start).count();
    res.totalDuration = std::chrono::duration<double>(total_end - total_start).count();
    
    return res;
}

BenchmarkResult runBenchmarkVector(const std::string& filename, int strategy, const std::string& gradeType) {
    return runBenchmark<std::vector<Studentas>>(filename, strategy, gradeType, "vector");
}

BenchmarkResult runBenchmarkList(const std::string& filename, int strategy, const std::string& gradeType) {
    return runBenchmark<std::list<Studentas>>(filename, strategy, gradeType, "list");
}

BenchmarkResult runBenchmarkDeque(const std::string& filename, int strategy, const std::string& gradeType) {
    return runBenchmark<std::deque<Studentas>>(filename, strategy, gradeType, "deque");
}

void writeResultsToCSV(const std::string& filename, const std::vector<BenchmarkResult>& results) {
    std::ofstream out(filename);
    if (!out.is_open()) {
        std::cerr << "Klaida: nepavyko atidaryti failo " << filename << " rašymui\n";
        return;
    }
    out << "Konteineris,Strategija,Irasu_kiekis,Nuskaitymas_s,Rusiavimas_s,Dalijimas_s,Isvedimas_s,Bendra_s\n";
    for (const auto& r : results) {
        out << r.containerType << ","
            << r.strategy << ","
            << r.recordCount << ","
            << std::fixed << std::setprecision(6) << r.readDuration << ","
            << r.sortDuration << ","
            << r.splitDuration << ","
            << r.writeDuration << ","
            << r.totalDuration << "\n";
    }
    out.close();
}

void printResultsTable(const std::vector<BenchmarkResult>& results) {
    std::cout << "\n" << std::string(100, '=') << "\n";
    std::cout << std::left << std::setw(15) << "Konteineris" 
              << std::setw(12) << "Strategija" 
              << std::setw(14) << "Nuskaitymas" 
              << std::setw(14) << "Rūšiavimas" 
              << std::setw(14) << "Dalijimas" 
              << std::setw(14) << "Išvedimas" 
              << std::setw(14) << "Bendra" << "\n";
    std::cout << std::string(100, '-') << "\n";
    
    for (const auto& r : results) {
        std::cout << std::left << std::setw(15) << r.containerType 
                  << std::setw(12) << r.strategy 
                  << std::setw(14) << std::fixed << std::setprecision(4) << r.readDuration 
                  << std::setw(14) << r.sortDuration 
                  << std::setw(14) << r.splitDuration 
                  << std::setw(14) << r.writeDuration 
                  << std::setw(14) << r.totalDuration << "\n";
    }
    std::cout << std::string(100, '=') << "\n";
}

void printContainerComparison(const std::vector<BenchmarkResult>& results) {
    std::cout << "\n=== KONTEINERIŲ PALYGINIMAS (vidurkis) ===\n";
    std::map<std::string, double> containerTotals;
    std::map<std::string, int> containerCounts;
    
    for (const auto& r : results) {
        containerTotals[r.containerType] += r.totalDuration;
        containerCounts[r.containerType]++;
    }
    
    std::cout << std::left << std::setw(15) << "Konteineris" 
              << std::setw(15) << "Vid. laikas (s)" << "\n";
    std::cout << std::string(30, '-') << "\n";
    
    for (const auto& p : containerTotals) {
        double avg = p.second / containerCounts[p.first];
        std::cout << std::setw(15) << p.first 
                  << std::setw(15) << std::fixed << std::setprecision(4) << avg << "\n";
    }
}
