#include <iostream>
#include <iomanip>
#include <fstream>
#include <chrono>
#include <vector>
#include <algorithm>
#include <random>
#include <string>

class Studentas {
private:
    std::string vardas_;
    std::string pavarde_;
    std::vector<int> tarp_rez_;
    int egz_rez_;
    float galutinis_;

public:
    Studentas() : egz_rez_(0), galutinis_(0.0f) {}
    Studentas(std::string vardas, std::string pavarde) 
        : vardas_(std::move(vardas)), pavarde_(std::move(pavarde)), egz_rez_(0), galutinis_(0.0f) {}
    Studentas(const Studentas& other) 
        : vardas_(other.vardas_), pavarde_(other.pavarde_), tarp_rez_(other.tarp_rez_),
          egz_rez_(other.egz_rez_), galutinis_(other.galutinis_) {}
    Studentas(Studentas&& other) noexcept 
        : vardas_(std::move(other.vardas_)), pavarde_(std::move(other.pavarde_)),
          tarp_rez_(std::move(other.tarp_rez_)), egz_rez_(other.egz_rez_), galutinis_(other.galutinis_) {
        other.egz_rez_ = 0;
        other.galutinis_ = 0.0f;
    }
    ~Studentas() = default;
    
    Studentas& operator=(const Studentas& other) {
        if (this != &other) {
            vardas_ = other.vardas_;
            pavarde_ = other.pavarde_;
            tarp_rez_ = other.tarp_rez_;
            egz_rez_ = other.egz_rez_;
            galutinis_ = other.galutinis_;
        }
        return *this;
    }
    
    Studentas& operator=(Studentas&& other) noexcept {
        if (this != &other) {
            vardas_ = std::move(other.vardas_);
            pavarde_ = std::move(other.pavarde_);
            tarp_rez_ = std::move(other.tarp_rez_);
            egz_rez_ = other.egz_rez_;
            galutinis_ = other.galutinis_;
            other.egz_rez_ = 0;
            other.galutinis_ = 0.0f;
        }
        return *this;
    }
    
    std::string getVardas() const { return vardas_; }
    std::string getPavarde() const { return pavarde_; }
    const std::vector<int>& getTarpRez() const { return tarp_rez_; }
    int getEgzRez() const { return egz_rez_; }
    float getGalutinis() const { return galutinis_; }
    
    void setVardas(const std::string& v) { vardas_ = v; }
    void setPavarde(const std::string& p) { pavarde_ = p; }
    void addTarpRez(int r) { tarp_rez_.push_back(r); }
    void setEgzRez(int r) { egz_rez_ = r; }
    void setGalutinis(float g) { galutinis_ = g; }
};

inline float calculateAverage(const std::vector<int>& arr) {
    if (arr.empty()) return 0.0f;
    int sum = 0;
    for (int val : arr) sum += val;
    return static_cast<float>(sum) / static_cast<float>(arr.size());
}

inline void calculateFinalGrade(Studentas& s, const std::string& choice) {
    float tarp = calculateAverage(s.getTarpRez());
    s.setGalutinis(0.6f * s.getEgzRez() + 0.4f * tarp);
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

std::vector<Studentas> readFromFile(const std::string& filename) {
    std::vector<Studentas> students;
    std::ifstream file(filename);
    std::string line;
    std::getline(file, line);

    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::istringstream iss(line);
        std::string vardas, pavarde;
        if (!(iss >> vardas >> pavarde)) continue;
        
        Studentas s(vardas, pavarde);
        int grade;
        for (int i = 0; i < 5; ++i) {
            if (iss >> grade) s.addTarpRez(grade);
        }
        iss >> grade;
        s.setEgzRez(grade);
        students.push_back(s);
    }
    file.close();
    return students;
}

int main(int argc, char* argv[]) {
    std::vector<int> sizes = {100000, 1000000};
    std::vector<std::string> names = {"100k", "1M"};
    
    std::cout << "=== CLASS VERSIJOS SPARTOS TESTAI ===\n\n";
    
    for (size_t i = 0; i < sizes.size(); ++i) {
        std::string filename = "test_" + names[i] + ".txt";
        std::cout << "Generuojamas " << names[i] << " failas...\n";
        generateFile(filename, sizes[i]);
        
        auto t1 = std::chrono::high_resolution_clock::now();
        std::vector<Studentas> students = readFromFile(filename);
        auto t2 = std::chrono::high_resolution_clock::now();
        
        for (auto& s : students) calculateFinalGrade(s, "1");
        auto t3 = std::chrono::high_resolution_clock::now();
        
        std::sort(students.begin(), students.end(), [](const Studentas& a, const Studentas& b) {
            return a.getGalutinis() < b.getGalutinis();
        });
        auto t4 = std::chrono::high_resolution_clock::now();
        
        std::vector<Studentas> vargsiukai;
        auto partition_point = std::stable_partition(students.begin(), students.end(), 
            [](const Studentas& s) { return s.getGalutinis() >= 5.0f; });
        vargsiukai.insert(vargsiukai.end(), partition_point, students.end());
        students.erase(partition_point, students.end());
        auto t5 = std::chrono::high_resolution_clock::now();
        
        double read_t = std::chrono::duration<double>(t2 - t1).count();
        double calc_t = std::chrono::duration<double>(t3 - t2).count();
        double sort_t = std::chrono::duration<double>(t4 - t3).count();
        double split_t = std::chrono::duration<double>(t5 - t4).count();
        double total_t = std::chrono::duration<double>(t5 - t1).count();
        
        std::cout << "CLASS " << names[i] << ": "
                  << "read=" << std::fixed << std::setprecision(4) << read_t << "s, "
                  << "calc=" << calc_t << "s, "
                  << "sort=" << sort_t << "s, "
                  << "split=" << split_t << "s, "
                  << "TOTAL=" << total_t << "s\n\n";
    }
    
    return 0;
}
