/**
 * @file main_vector.cpp
 * @brief Studentų programa naudojant Vector konteinerį vietoje std::vector
 */

#include "Vector.h"
#include "student.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>

using namespace std::chrono;

int main() {
    std::cout << "\n=== Studentų Programa su Vector Konteineriu ===\n\n";
    
    // Generuoti testinius duomenis
    const size_t NUM_STUDENTS = 10000;
    std::cout << "Generuojama " << NUM_STUDENTS << " studentų...\n";
    
    auto start = high_resolution_clock::now();
    
    Vector<Studentas> students;
    students.reserve(NUM_STUDENTS);
    
    srand(42);
    for (size_t i = 0; i < NUM_STUDENTS; ++i) {
        Studentas s("Vardas" + std::to_string(i), "Pavarde" + std::to_string(i));
        generateRandomGrades(s);
        calculateFinalGrade(s, "1");
        students.push_back(s);
    }
    
    auto end = high_resolution_clock::now();
    double generation_time = duration<double, std::milli>(end - start).count();
    
    std::cout << "Sugeneruota per " << std::fixed << std::setprecision(2) 
              << generation_time << " ms\n\n";
    
    // Rūšiavimas
    std::cout << "Rūšiuojama pagal galutinį balą...\n";
    start = high_resolution_clock::now();
    
    // Bubble sort (simple, works with Vector)
    for (size_t i = 0; i < students.size() - 1; ++i) {
        for (size_t j = 0; j < students.size() - i - 1; ++j) {
            if (students[j].getGalutinis() > students[j + 1].getGalutinis()) {
                Studentas temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
    
    end = high_resolution_clock::now();
    double sort_time = duration<double, std::milli>(end - start).count();
    
    std::cout << "Surūšiuota per " << std::fixed << std::setprecision(2) 
              << sort_time << " ms\n\n";
    
    // Išvestis
    std::cout << "Pirmi 5 studentai (geriausi):\n";
    std::cout << std::left << std::setw(20) << "Vardas" 
              << std::setw(20) << "Pavarde"
              << std::setw(10) << "Galutinis\n";
    std::cout << std::string(50, '-') << "\n";
    
    for (size_t i = 0; i < 5 && i < students.size(); ++i) {
        const Studentas& s = students[students.size() - 1 - i];
        std::cout << std::left << std::setw(20) << s.getVardas()
                  << std::setw(20) << s.getPavarde()
                  << std::setw(10) << std::fixed << std::setprecision(2) 
                  << s.getGalutinis() << "\n";
    }
    
    std::cout << "\nPirmi 5 studentai (prasčiausi):\n";
    for (size_t i = 0; i < 5 && i < students.size(); ++i) {
        const Studentas& s = students[i];
        std::cout << std::left << std::setw(20) << s.getVardas()
                  << std::setw(20) << s.getPavarde()
                  << std::setw(10) << std::fixed << std::setprecision(2) 
                  << s.getGalutinis() << "\n";
    }
    
    // Išvestis į failą
    std::ofstream out("rezultatai_vector.txt");
    if (out.is_open()) {
        out << "Studentų sąrašas (Vector konteineris)\n";
        out << "=====================================\n\n";
        
        for (size_t i = 0; i < students.size() && i < 100; ++i) {
            out << students[i].getVardas() << " " 
                << students[i].getPavarde() << " "
                << students[i].getGalutinis() << "\n";
        }
        out.close();
        std::cout << "\nRezultatai išsaugoti į rezultatai_vector.txt\n";
    }
    
    std::cout << "\n=== Programa baigė darbą ===\n";
    
    return 0;
}
