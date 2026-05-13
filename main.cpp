#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include <fstream>
#include <list>
#include <deque>
#include <iomanip>
#include <random>
#include <chrono>
#include <sstream>
#include "student.h"

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    int input_mode;
    std::cout << "=== Studentų Duomenų Įvestis ===\n"
              << "Pasirinkite įvesties būdą:\n"
              << "1 - Rankinis įvedimas (konsolė)\n"
              << "2 - Automatinis generavimas\n"
              << "3 - Nuskaitymas iš failo\n"
              << "4 - Automatinis generavimas (failų kūrimas)\n"
              << "5 - Failo apdorojimas (skaidymas)\n"
              << "Jūsų pasirinkimas: ";
    std::cin >> input_mode;

    if (std::cin.fail() || input_mode < 1 || input_mode > 5) {
        std::cout << "Neteisinga įvestis: tinka '1', '2', '3', '4' arba '5'.\n";
        return 1;
    }

    std::vector<Studentas> students;

    if (input_mode == 1) {
        std::cout << "\n--- Rankinė Įvestis ---\n";
        while (true) {
            std::cout << "\nĮveskite " << students.size() + 1 << " studento duomenis:\n";
            Studentas s;
            s.inputManual();
            students.push_back(s);

            std::string ans;
            std::cout << "Ar norite įvesti dar vieną studentą? (t/n): ";
            std::cin >> ans;
            if (ans != "T" && ans != "t") break;
        }
    }
    else if (input_mode == 2) {
        std::cout << "\n--- Automatinis Generavimas ---\n";
        std::cout << "Įveskite studentų skaičių: ";
        int mokSkaicius;
        std::cin >> mokSkaicius;
        
        for (int i = 0; i < mokSkaicius; i++) {
            Studentas s;
            s.inputAuto();
            students.push_back(s);
        }
        std::cout << "Sugeneruota " << mokSkaicius << " studentų.\n";
    }
    else if (input_mode == 3) {
        std::cout << "\n--- Įvestis iš Failo ---\n";
        std::string filename;
        std::cout << "Įveskite failo pavadinimą: ";
        std::cin >> filename;
        
        students = readFromFile(filename);
        
        if (students.empty()) {
            std::cerr << "Nepavyko nuskaityti duomenų.\n";
            return 1;
        }
        std::cout << "Nuskaityta " << students.size() << " studentų.\n";
    }
    else if (input_mode == 4) {
        std::cout << "\n--- Automatinis Generavimas (Failų Kūrimas) ---\n";
        std::vector<int> sizes = {1000, 10000, 100000, 1000000, 10000000};
        std::vector<std::string> size_names = {"1k", "10k", "100k", "1M", "10M"};

        std::cout << "Pradedami spartos tyrimai...\n";
        std::cout << "Ar norite į failus: 'taip' jeigu taip\n";
        std::string answer;
        std::cin >> answer;

        if (answer == "taip") {
            for (size_t i = 0; i < sizes.size(); ++i) {
                std::cout << "\n" << size_names[i] << ":\n";
                runGenerationTestT<std::vector<Studentas>>(size_names[i] + ".txt", sizes[i]);
            }
        }

        std::cout << "\nTyrimai baigti.\n";
        return 0;
    }
    else {
        std::cout << "\n--- Failo Apdorojimas (Skaidymas) ---\n";
        std::string filename;
        std::cout << "Kokį failą padalinti į kietakus ir vargsiukus: ";
        std::cin >> filename;

        runProcessingTest(filename);

        std::cout << "\nApdorojimas baigtas.\n";
        return 0;
    }

    std::string choice;
    std::cout << "\n=== Galutinio Balo Skaičiavimas ===\n"
              << "Pasirinkite būdą:\n"
              << "1 - Vidurkis\n"
              << "2 - Mediana\n"
              << "Jūsų pasirinkimas: ";
    std::cin >> choice;

    if (choice != "1" && choice != "2") {
        std::cout << "Neteisinga įvestis: tinka '1' arba '2'.\n";
        return 1;
    }

    for (auto& s : students) {
        s.calculateFinalGrade(choice);
    }

    int sort_choice;
    std::cout << "\n=== Rūšiavimas ===\n"
              << "Pasirinkite kriterijų:\n"
              << "1 - Pagal vardą (a-z)\n"
              << "2 - Pagal pavardę (a-z)\n"
              << "3 - Pagal galutinį balą (didėjantis)\n"
              << "Jūsų pasirinkimas: ";
    std::cin >> sort_choice;

    if (sort_choice < 1 || sort_choice > 3) {
        std::cout << "Neteisinga įvestis.\n";
        return 1;
    }

    if (sort_choice == 1) {
        std::sort(students.begin(), students.end());
    } else if (sort_choice == 2) {
        std::sort(students.begin(), students.end(), Studentas::CompareByLastName());
    } else {
        std::sort(students.begin(), students.end(), Studentas::CompareByFinalGradeDesc());
    }

    int output_option;
    std::cout << "\n=== Rezultatų Išvestis ===\n"
              << "Pasirinkite išvesties būdą:\n"
              << "1 - Į ekraną (konsolė)\n"
              << "2 - Į failą\n"
              << "Jūsų pasirinkimas: ";
    std::cin >> output_option;

    if (output_option < 1 || output_option > 2) {
        std::cout << "Neteisinga įvestis: tinka '1' arba '2'.\n";
        return 1;
    }

    std::cout << "\n=== Rezultatai ===\n";
    
    if (output_option == 1) {
        const int langelio_ilgis = 20;
        std::string kategorija = (choice == "1") ? "Galutinis (Vid.)" : "Galutinis (Med.)";
        
        std::cout << std::left;
        std::cout << std::setw(langelio_ilgis) << "Pavardė"
                  << std::setw(langelio_ilgis) << "Vardas"
                  << std::setw(langelio_ilgis) << kategorija << '\n';
        std::cout << std::string(3 * langelio_ilgis, '-') << '\n';
        
        for (const auto& s : students) {
            s.outputToConsole();
        }
    } else {
        std::string filename = "output.txt";
        std::remove(filename.c_str());
        
        std::ofstream outFile(filename);
        if (outFile.is_open()) {
            const int langelio_ilgis = 20;
            std::string kategorija = (choice == "1") ? "Galutinis (Vid.)" : "Galutinis (Med.)";
            
            outFile << std::left;
            outFile << std::setw(langelio_ilgis) << "Pavardė"
                    << std::setw(langelio_ilgis) << "Vardas"
                    << std::setw(langelio_ilgis) << kategorija << '\n';
            outFile << std::string(3 * langelio_ilgis, '-') << '\n';
            outFile.close();
            
            for (const auto& s : students) {
                s.outputToFile(filename);
            }
            std::cout << "Rezultatai įrašyti į failą: " << filename << "\n";
        }
    }

    return 0;
}
