#ifndef STUDENT_STRUCT_H
#define STUDENT_STRUCT_H

#include <string>
#include <vector>
#include <list>
#include <deque>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <chrono>

struct Mokinys {
    std::string vardas;
    std::string pavarde;
    std::vector<int> tarp_rez;
    int egz_rez;
    float galutinis;
    
    Mokinys() : egz_rez(0), galutinis(0.0f) {}
};

inline float calculateAverage(const std::vector<int>& arr) {
    if (arr.empty()) return 0.0f;
    int sum = 0;
    for (int val : arr) {
        sum += val;
    }
    return static_cast<float>(sum) / static_cast<float>(arr.size());
}

inline float calculateMedian(std::vector<int> arr) {   
    if (arr.empty()) return 0.0f;
    std::sort(arr.begin(), arr.end());
    size_t size = arr.size();
    if (size % 2 == 0) {
        return (arr[size/2 - 1] + arr[size/2]) / 2.0f;
    } else {
        return static_cast<float>(arr[size/2]);
    }
}

inline void generateRandomGrades(Mokinys& mokinys) {
    int tarp_count = rand() % 10 + 1; 
    mokinys.tarp_rez.reserve(tarp_count);
    for (int i = 0; i < tarp_count; ++i) {
        mokinys.tarp_rez.push_back(rand() % 11); 
    }
    mokinys.egz_rez = rand() % 11;
}

inline void readStudentData(Mokinys& mokinys) {
    std::cout << "Įveskite vardą: ";
    std::cin >> mokinys.vardas;
    std::cout << "Įveskite pavardę: ";
    std::cin >> mokinys.pavarde;

    while (true) {
        std::cout << "Įveskite " << mokinys.tarp_rez.size() + 1
                  << " tarpinį rezultatą (arba -1, jei baigėte): ";
        int grade;
        if (!(std::cin >> grade)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Neteisinga įvestis. Bandykite dar kartą.\n";
            continue;
        }

        if (grade == -1) {
            break;
        }
        if (grade < 0 || grade > 10) {
            std::cout << "Rezultatas turi būti nuo 0 iki 10. Bandykite dar kartą.\n";
            continue;
        }
        mokinys.tarp_rez.push_back(grade);
    }

    if (mokinys.tarp_rez.empty()) {
        std::cout << "Turite įvesti bent vieną tarpinį rezultatą. Generuojami atsitiktiniai.\n";
        generateRandomGrades(mokinys);
    }

    std::cout << "Įveskite egzamino rezultatą: ";
    while (!(std::cin >> mokinys.egz_rez) || mokinys.egz_rez < 0 || mokinys.egz_rez > 10) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Neteisinga įvestis (0-10). Bandykite dar kartą: ";
    }
}

inline void calculateFinalGrade(Mokinys& mokinys, const std::string& choice) {
    float tarp_rez;
    if (choice == "1") {
        tarp_rez = calculateAverage(mokinys.tarp_rez);
    } else {
        tarp_rez = calculateMedian(mokinys.tarp_rez);
    }
    mokinys.galutinis = 0.6f * mokinys.egz_rez + 0.4f * tarp_rez;
}

inline void displayResults(const std::vector<Mokinys>& students, const std::string& choice) { 
    std::ostream& out = std::cout;
    const int langelio_ilgis = 20;
    std::string kategorija = (choice == "1") ? "Galutinis (Vid.)" : "Galutinis (Med.)";

    out << std::left;  
    out << std::setw(langelio_ilgis) << "Pavardė"
        << std::setw(langelio_ilgis) << "Vardas"
        << std::setw(langelio_ilgis) << kategorija << '\n';
    out << std::string(3 * langelio_ilgis, '-') << '\n';

    for (const auto& m : students) {
        out << std::setw(langelio_ilgis) << m.pavarde
            << std::setw(langelio_ilgis) << m.vardas
            << std::setw(langelio_ilgis) << std::fixed << std::setprecision(2) << m.galutinis
            << '\n';
    }
}

template<typename Container>
Container readFromFile(const std::string& filename) {
    Container students;
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Klaida: nepavyko atidaryti failo " + filename);
    }

    std::string line;
    std::getline(file, line);

    Mokinys m;
    while (std::getline(file, line)) {
        if (line.empty()) continue; 

        std::istringstream iss(line);
        if (!(iss >> m.vardas >> m.pavarde)) continue;

        m.tarp_rez.clear();
        int grade;
        for (int i = 0; i < 5; ++i) {
            if (iss >> grade) {
                m.tarp_rez.push_back(grade);
            }
        }
        iss >> m.egz_rez;
        students.push_back(m);
    }

    file.close();
    return students;
}

template<typename Container>
void sortStudents(Container& students) {
    std::sort(students.begin(), students.end(), [](const Mokinys& a, const Mokinys& b) {
        return a.galutinis < b.galutinis;
    });
}

template<>
inline void sortStudents<std::list<Mokinys>>(std::list<Mokinys>& students) {
    students.sort([](const Mokinys& a, const Mokinys& b) {
        return a.galutinis < b.galutinis;
    });
}

template<typename Container>
Container strategy1Split(Container& students) {
    Container vargsiukai;
    for (const auto& s : students) {
        if (s.galutinis < 5.0f) {
            vargsiukai.push_back(s);
        }
    }
    return vargsiukai;
}

template<typename Container>
Container strategy2Split(Container& students) {
    Container vargsiukai;
    auto it = students.begin();
    while (it != students.end()) {
        if (it->galutinis < 5.0f) {
            vargsiukai.push_back(*it);
            it = students.erase(it);
        } else {
            ++it;
        }
    }
    return vargsiukai;
}

template<typename Container>
Container strategy3Split(Container& students) {
    Container vargsiukai;
    auto partition_point = std::stable_partition(students.begin(), students.end(), 
        [](const Mokinys& s) { return s.galutinis >= 5.0f; });
    
    vargsiukai.insert(vargsiukai.end(), partition_point, students.end());
    students.erase(partition_point, students.end());
    
    return vargsiukai;
}

template<>
inline std::list<Mokinys> strategy3Split<std::list<Mokinys>>(std::list<Mokinys>& students) {
    std::list<Mokinys> vargsiukai;
    auto it = students.begin();
    while (it != students.end()) {
        if (it->galutinis < 5.0f) {
            vargsiukai.splice(vargsiukai.end(), students, it++);
        } else {
            ++it;
        }
    }
    return vargsiukai;
}

struct ProcessingResult {
    double readDuration;
    double sortDuration;
    double splitDuration;
    double writeDuration;
    double totalDuration;
    std::string containerType;
    int strategy;
    
    ProcessingResult() : readDuration(0), sortDuration(0), splitDuration(0), 
                         writeDuration(0), totalDuration(0), strategy(0) {}
};

#endif
