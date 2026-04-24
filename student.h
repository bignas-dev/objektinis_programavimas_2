#ifndef STUDENT_H
#define STUDENT_H

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
    
    ~Studentas() {
        tarp_rez_.clear();
    }
    
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
    
    inline friend std::ostream& operator<<(std::ostream& os, const Studentas& studentas) {
        os << std::left << std::setw(20) << studentas.vardas_
           << std::setw(20) << studentas.pavarde_;
        
        const auto& tarp_rez = studentas.tarp_rez_;
        for (int rez : tarp_rez) {
            os << std::setw(6) << rez;
        }
        
        os << std::setw(6) << studentas.egz_rez_;
        return os;
    }
    
    inline friend std::istream& operator>>(std::istream& is, Studentas& studentas) {
        std::string vardas, pavarde;
        if (is >> vardas >> pavarde) {
            studentas.vardas_ = std::move(vardas);
            studentas.pavarde_ = std::move(pavarde);
            
            studentas.tarp_rez_.clear();
            std::vector<int> grades;
            int grade;
            while (is >> grade) {
                grades.push_back(grade);
            }
            
            if (!grades.empty()) {
                studentas.egz_rez_ = grades.back();
                grades.pop_back();
                studentas.tarp_rez_ = std::move(grades);
            }
        }
        return is;
    }
    
    inline std::string getVardas() const { return vardas_; }
    inline std::string getPavarde() const { return pavarde_; }
    inline const std::vector<int>& getTarpRez() const { return tarp_rez_; }
    inline int getEgzRez() const { return egz_rez_; }
    inline float getGalutinis() const { return galutinis_; }
    
    inline void setVardas(const std::string& vardas) { vardas_ = vardas; }
    inline void setPavarde(const std::string& pavarde) { pavarde_ = pavarde; }
    inline void addTarpRez(int rez) { tarp_rez_.push_back(rez); }
    inline void setEgzRez(int rez) { egz_rez_ = rez; }
    inline void setGalutinis(float gal) { galutinis_ = gal; }
    inline void clearTarpRez() { tarp_rez_.clear(); }
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

inline void generateRandomGrades(Studentas& studentas) {
    int tarp_count = rand() % 10 + 1; 
    for (int i = 0; i < tarp_count; ++i) {
        studentas.addTarpRez(rand() % 11);
    }
    studentas.setEgzRez(rand() % 11);
}

inline void calculateFinalGrade(Studentas& studentas, const std::string& choice) {
    float tarp_rez;
    if (choice == "1") {
        tarp_rez = calculateAverage(studentas.getTarpRez());
    } else {
        tarp_rez = calculateMedian(studentas.getTarpRez());
    }
    studentas.setGalutinis(0.6f * studentas.getEgzRez() + 0.4f * tarp_rez);
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

    while (std::getline(file, line)) {
        if (line.empty()) continue; 

        std::istringstream iss(line);
        std::string vardas, pavarde;
        if (!(iss >> vardas >> pavarde)) continue;

        Studentas s(vardas, pavarde);
        int grade;
        for (int i = 0; i < 5; ++i) {
            if (iss >> grade) {
                s.addTarpRez(grade);
            }
        }
        iss >> grade;
        s.setEgzRez(grade);
        students.push_back(s);
    }

    file.close();
    return students;
}

template<typename Container>
void sortStudents(Container& students) {
    std::sort(students.begin(), students.end(), [](const Studentas& a, const Studentas& b) {
        return a.getGalutinis() < b.getGalutinis();
    });
}

template<>
inline void sortStudents<std::list<Studentas>>(std::list<Studentas>& students) {
    students.sort([](const Studentas& a, const Studentas& b) {
        return a.getGalutinis() < b.getGalutinis();
    });
}

template<typename Container>
Container strategy1Split(Container& students) {
    Container vargsiukai;
    for (const auto& s : students) {
        if (s.getGalutinis() < 5.0f) {
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
        if (it->getGalutinis() < 5.0f) {
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
        [](const Studentas& s) { return s.getGalutinis() >= 5.0f; });
    
    vargsiukai.insert(vargsiukai.end(), partition_point, students.end());
    students.erase(partition_point, students.end());
    
    return vargsiukai;
}

template<>
inline std::list<Studentas> strategy3Split<std::list<Studentas>>(std::list<Studentas>& students) {
    std::list<Studentas> vargsiukai;
    auto it = students.begin();
    while (it != students.end()) {
        if (it->getGalutinis() < 5.0f) {
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
