#include <iostream>
#include <iomanip>
#include <fstream>
#include <chrono>
#include <vector>
#include <algorithm>
#include <random>
#include <string>

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
    for (int val : arr) sum += val;
    return static_cast<float>(sum) / static_cast<float>(arr.size());
}

inline void calculateFinalGrade(Mokinys& m, const std::string& choice) {
    float tarp = calculateAverage(m.tarp_rez);
    m.galutinis = 0.6f * m.egz_rez + 0.4f * tarp;
}

void generateFile(const std::string& filename, int count) {
    std::ofstream out(filename);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 10);

    out << std::left << std::setw(20) << "Vardas" << std::setw(20) << "Pavarde";
    for (int i = 1; i <= 5; ++i) out << std::setw(10) << "ND" + std::to_string(i);
    out << std::setw(10) << "Egz.\n";

    for (int i = 1; i <= count; ++i) {
        out << std::left << std::setw(20) << ("VardasNR" + std::to_string(i))
            << std::setw(20) << ("PavardeNR" + std::to_string(i));
        for (int j = 0; j < 6; ++j) out << std::setw(10) << dist(gen);
        out << "\n";
    }
    out.close();
}

std::vector<Mokinys> readFromFile(const std::string& filename) {
    std::vector<Mokinys> students;
    std::ifstream file(filename);
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
            if (iss >> grade) m.tarp_rez.push_back(grade);
        }
        iss >> m.egz_rez;
        students.push_back(m);
    }
    file.close();
    return students;
}

int main(int argc, char* argv[]) {
    std::vector<int> sizes = {100000, 1000000};
    std::vector<std::string> names = {"100k", "1M"};
    
    std::cout << "=== STRUCT VERSIJOS SPARTOS TESTAI ===\n\n";
    
    for (size_t i = 0; i < sizes.size(); ++i) {
        std::string filename = "test_" + names[i] + ".txt";
        std::cout << "Generuojamas " << names[i] << " failas...\n";
        generateFile(filename, sizes[i]);
        
        auto t1 = std::chrono::high_resolution_clock::now();
        std::vector<Mokinys> students = readFromFile(filename);
        auto t2 = std::chrono::high_resolution_clock::now();
        
        for (auto& s : students) calculateFinalGrade(s, "1");
        auto t3 = std::chrono::high_resolution_clock::now();
        
        std::sort(students.begin(), students.end(), [](const Mokinys& a, const Mokinys& b) {
            return a.galutinis < b.galutinis;
        });
        auto t4 = std::chrono::high_resolution_clock::now();
        
        std::vector<Mokinys> vargsiukai;
        auto partition_point = std::stable_partition(students.begin(), students.end(), 
            [](const Mokinys& s) { return s.galutinis >= 5.0f; });
        vargsiukai.insert(vargsiukai.end(), partition_point, students.end());
        students.erase(partition_point, students.end());
        auto t5 = std::chrono::high_resolution_clock::now();
        
        double read_t = std::chrono::duration<double>(t2 - t1).count();
        double calc_t = std::chrono::duration<double>(t3 - t2).count();
        double sort_t = std::chrono::duration<double>(t4 - t3).count();
        double split_t = std::chrono::duration<double>(t5 - t4).count();
        double total_t = std::chrono::duration<double>(t5 - t1).count();
        
        std::cout << "STRUCT " << names[i] << ": "
                  << "read=" << std::fixed << std::setprecision(4) << read_t << "s, "
                  << "calc=" << calc_t << "s, "
                  << "sort=" << sort_t << "s, "
                  << "split=" << split_t << "s, "
                  << "TOTAL=" << total_t << "s\n\n";
    }
    
    return 0;
}
