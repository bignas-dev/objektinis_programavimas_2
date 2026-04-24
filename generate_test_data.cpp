/**
 * @file generate_test_data.cpp
 * @brief Generuoja testinius studentų duomenis
 */

#include "Vector.h"
#include "student.h"
#include <iostream>
#include <fstream>
#include <iomanip>

void generate_file(const std::string& filename, size_t num_students) {
    std::ofstream out(filename);
    if (!out.is_open()) {
        std::cerr << "Nepavyko atidaryti failo: " << filename << std::endl;
        return;
    }
    
    // Header
    out << "Vardas Pavarde ND1 ND2 ND3 ND4 ND5 Egz\n";
    
    srand(42);
    for (size_t i = 0; i < num_students; ++i) {
        out << "Vardas" << i << " "
            << "Pavarde" << i << " ";
        
        // 5 ND results
        for (int j = 0; j < 5; ++j) {
            out << (rand() % 11) << " ";
        }
        
        // Exam result
        out << (rand() % 11) << "\n";
    }
    
    out.close();
    std::cout << "Sugeneruota: " << filename << " (" << num_students << " studentų)" << std::endl;
}

int main() {
    std::cout << "=== Testinių duomenų generatorius ===\n\n";
    
    generate_file("test_10000.txt", 10000);
    generate_file("test_100000.txt", 100000);
    
    std::cout << "\nBaigta!\n";
    return 0;
}
