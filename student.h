/**
 * @file student.h
 * @brief Studento klase, paveldinti is Zmogus
 * 
 * Realizuoja studento duomenu saugojima ir apdorojima:
 * - Tarpiniai rezultatai (vektorius)
 * - Egzamino rezultatas
 * - Galutinis balas
 */

#ifndef STUDENT_H
#define STUDENT_H

#include "zmogus.h"
#include <vector>
#include <list>
#include <deque>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <stdexcept>

/**
 * @class Studentas
 * @brief Išvestine klase is Zmogus, reprezentuojanti studenta
 * 
 * Studentas turi:
 * - Varda ir pavarde (paveldeta is Zmogus)
 * - Tarpinius rezultatus (std::vector<int>)
 * - Egzamino rezultata (int)
 * - Galutini bala (float)
 * 
 * Implementuoja Rule of Five:
 * 1. Numatytasis konstruktorius
 * 2. Parametrinis konstruktorius
 * 3. Kopijavimo konstruktorius
 * 4. Move konstruktorius
 * 5. Destruktorius
 * 6. Kopijavimo priskyrimo operatorius
 * 7. Move priskyrimo operatorius
 */
class Studentas : public Zmogus {
private:
    std::vector<int> tarp_rez_;   ///< Tarpiniu rezultatu vektorius
    int egz_rez_;                  ///< Egzamino rezultatas
    float galutinis_;              ///< Galutinis balas

public:
    // === RULE OF FIVE ===
    
    /**
     * @brief 1. Numatytasis konstruktorius
     * 
     * Sukuria studenta su tusciais duomenimis.
     * Inicializuoja: egz_rez_ = 0, galutinis_ = 0.0f
     */
    Studentas() : Zmogus(), egz_rez_(0), galutinis_(0.0f) {}
    
    /**
     * @brief 2. Parametrinis konstruktorius
     * @param vardas Studento vardas
     * @param pavarde Studento pavarde
     * 
     * Sukuria studenta su nurodytu vardu ir pavarde.
     * Tarpiniai rezultatai tusti, egz_rez_ = 0, galutinis_ = 0.0f
     */
    Studentas(std::string vardas, std::string pavarde)
        : Zmogus(std::move(vardas), std::move(pavarde)), egz_rez_(0), galutinis_(0.0f) {}
    
    /**
     * @brief 3. Kopijavimo konstruktorius
     * @param other Kopijuojamas Studentas objektas
     * 
     * Sukuria nepriklausoma kopija (gili kopija).
     * Kopijuojami visi duomenys: vardas, pavarde, tarp_rez_, egz_rez_, galutinis_
     */
    Studentas(const Studentas& other)
        : Zmogus(other.vardas_, other.pavarde_),
          tarp_rez_(other.tarp_rez_),
          egz_rez_(other.egz_rez_),
          galutinis_(other.galutinis_) {}
    
    /**
     * @brief 4. Move konstruktorius
     * @param other Perkeliamas Studentas objektas
     * 
     * Perkelia resursus be kopijavimo (efektyvu).
     * Po move operacijos, originalo objektas lieka validus bet su undefined reiksmemis.
     */
    Studentas(Studentas&& other) noexcept
        : Zmogus(std::move(other.vardas_), std::move(other.pavarde_)),
          tarp_rez_(std::move(other.tarp_rez_)),
          egz_rez_(other.egz_rez_),
          galutinis_(other.galutinis_) {
        other.egz_rez_ = 0;
        other.galutinis_ = 0.0f;
    }
    
    /**
     * @brief 5. Destruktorius
     * 
     * Išvalo atminti: tarp_rez_.clear()
     */
    ~Studentas() {
        tarp_rez_.clear();
    }
    
    /**
     * @brief 6. Kopijavimo priskyrimo operatorius
     * @param other Kopijuojamas Studentas objektas
     * @return Nuoroda i save
     * 
     * Apsauga nuo self-assignment.
     * Kopijuoja bazines klases ir išvestines klases narius.
     */
    Studentas& operator=(const Studentas& other) {
        if (this != &other) {
            Zmogus::operator=(other);
            tarp_rez_ = other.tarp_rez_;
            egz_rez_ = other.egz_rez_;
            galutinis_ = other.galutinis_;
        }
        return *this;
    }
    
    /**
     * @brief 7. Move priskyrimo operatorius
     * @param other Perkeliamas Studentas objektas
     * @return Nuoroda i save
     * 
     * Perkelia resursus be kopijavimo.
     */
    Studentas& operator=(Studentas&& other) noexcept {
        if (this != &other) {
            Zmogus::operator=(std::move(other));
            tarp_rez_ = std::move(other.tarp_rez_);
            egz_rez_ = other.egz_rez_;
            galutinis_ = other.galutinis_;
            other.egz_rez_ = 0;
            other.galutinis_ = 0.0f;
        }
        return *this;
    }
    
    // === OVERRIDE VIRTUALŪS METODAI ===
    
    /**
     * @brief Gauto vardo metoda (override is Zmogus)
     * @return Studento vardas
     */
    std::string getVardas() const override {
        return vardas_;
    }
    
    /**
     * @brief Gauto pavardes metoda (override is Zmogus)
     * @return Studento pavarde
     */
    std::string getPavarde() const override {
        return pavarde_;
    }
    
    /**
     * @brief Išvesties i srauta metoda (override is Zmogus)
     * @param os Išvesties srautas
     * @return Nuoroda i išvesties srauta
     * 
     * Formatas: Vardas Pavarde ND1 ND2 ... NDn Egz
     */
    std::ostream& print(std::ostream& os) const override {
        os << std::left << std::setw(20) << vardas_
           << std::setw(20) << pavarde_;
        
        for (int rez : tarp_rez_) {
            os << std::setw(6) << rez;
        }
        
        os << std::setw(6) << egz_rez_;
        return os;
    }
    
    /**
     * @brief Įvesties is srauto metoda (override is Zmogus)
     * @param is Įvesties srautas
     * @return Nuoroda i įvesties srauta
     * 
     * Nuskaitymo formatas: Vardas Pavarde ND1 ND2 ... NDn Egz
     * Paskutinis skaicius - egzaminas, visi kiti - tarpiniai rezultatai.
     */
    std::istream& read(std::istream& is) override {
        if (is >> vardas_ >> pavarde_) {
            tarp_rez_.clear();
            std::vector<int> grades;
            int grade;
            while (is >> grade) {
                grades.push_back(grade);
            }
            
            if (!grades.empty()) {
                egz_rez_ = grades.back();
                grades.pop_back();
                tarp_rez_ = std::move(grades);
            }
        }
        return is;
    }
    
    // === I/O OPERATORIAI (friend) ===
    
    /**
     * @brief Išvesties operatorius (friend)
     * @param os Išvesties srautas
     * @param s Studentas objektas
     * @return Nuoroda i išvesties srauta
     * 
     * Naudojimas: std::cout << studentas;
     */
    friend std::ostream& operator<<(std::ostream& os, const Studentas& s) {
        return s.print(os);
    }
    
    /**
     * @brief Įvesties operatorius (friend)
     * @param is Įvesties srautas
     * @param s Studentas objektas
     * @return Nuoroda i įvesties srauta
     * 
     * Naudojimas: std::cin >> studentas;
     */
    friend std::istream& operator>>(std::istream& is, Studentas& s) {
        return s.read(is);
    }
    
    // === GETTER/SETTER ===
    
    /**
     * @brief Gauti tarpiniu rezultatu vektoriu
     * @return Const nuoroda i tarp_rez_
     */
    inline const std::vector<int>& getTarpRez() const { return tarp_rez_; }
    inline int getEgzRez() const { return egz_rez_; }
    inline float getGalutinis() const { return galutinis_; }
    
    inline void addTarpRez(int rez) { tarp_rez_.push_back(rez); }
    inline void setEgzRez(int rez) { egz_rez_ = rez; }
    inline void setGalutinis(float gal) { galutinis_ = gal; }
    inline void clearTarpRez() { tarp_rez_.clear(); }
    
    inline void setVardas(const std::string& vardas) { vardas_ = vardas; }
    inline void setPavarde(const std::string& pavarde) { pavarde_ = pavarde; }
};

/**
 * @brief Apskaiciuoti vidurki
 * @param arr Rezultatu vektorius
 * @return Vidurkis (float)
 */
inline float calculateAverage(const std::vector<int>& arr) {
    if (arr.empty()) return 0.0f;
    int sum = 0;
    for (int val : arr) {
        sum += val;
    }
    return static_cast<float>(sum) / static_cast<float>(arr.size());
}

/**
 * @brief Apskaiciuoti mediana
 * @param arr Rezultatu vektorius
 * @return Mediana (float)
 */
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

/**
 * @brief Sugeneruoti atsitiktinius pazymius
 * @param studentas Studentas objektas
 * 
 * Generuoja 1-10 atsitiktiniu tarpiniu rezultatu (0-10).
 * Egzamino rezultatas taip pat atsitiktinis (0-10).
 */
inline void generateRandomGrades(Studentas& studentas) {
    int tarp_count = rand() % 10 + 1; 
    for (int i = 0; i < tarp_count; ++i) {
        studentas.addTarpRez(rand() % 11);
    }
    studentas.setEgzRez(rand() % 11);
}

/**
 * @brief Apskaiciuoti galutini bala
 * @param studentas Studentas objektas
 * @param choice "1" - vidurkis, kitu atveju - mediana
 * 
 * Formulė: 0.6 * egzaminas + 0.4 * (vidurkis ARBA mediana)
 */
inline void calculateFinalGrade(Studentas& studentas, const std::string& choice) {
    float tarp_rez;
    if (choice == "1") {
        tarp_rez = calculateAverage(studentas.getTarpRez());
    } else {
        tarp_rez = calculateMedian(studentas.getTarpRez());
    }
    studentas.setGalutinis(0.6f * studentas.getEgzRez() + 0.4f * tarp_rez);
}

/**
 * @brief Nuskaityti studentus is failo
 * @tparam Container Konteinerio tipas (vector, list, deque)
 * @param filename Failo pavadinimas
 * @return Konteineris su Studentas objektais
 * @throws std::runtime_error Jei nepavyko atidaryti failo
 */
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

/**
 * @brief Rusiuoti studentus pagal galutini bala
 * @tparam Container Konteinerio tipas
 * @param students Studentu konteineris
 */
template<typename Container>
void sortStudents(Container& students) {
    std::sort(students.begin(), students.end(), [](const Studentas& a, const Studentas& b) {
        return a.getGalutinis() < b.getGalutinis();
    });
}

/**
 * @brief Rusiuoti studentus (specializacija list konteineriui)
 * @param students Studentu sarasas
 */
template<>
inline void sortStudents<std::list<Studentas>>(std::list<Studentas>& students) {
    students.sort([](const Studentas& a, const Studentas& b) {
        return a.getGalutinis() < b.getGalutinis();
    });
}

/**
 * @brief 1 strategija: Skaidymas i du naujus konteinerius
 * @tparam Container Konteinerio tipas
 * @param students Studentu konteineris
 * @return Vargsiuku konteineris (galutinis < 5.0)
 */
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

/**
 * @brief 2 strategija: Vienas naujas + trynimas is originalo
 * @tparam Container Konteinerio tipas
 * @param students Studentu konteineris
 * @return Vargsiuku konteineris (galutinis < 5.0)
 */
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

/**
 * @brief 3 strategija: std::stable_partition (greiciausia)
 * @tparam Container Konteinerio tipas
 * @param students Studentu konteineris
 * @return Vargsiuku konteineris (galutinis < 5.0)
 */
template<typename Container>
Container strategy3Split(Container& students) {
    Container vargsiukai;
    auto partition_point = std::stable_partition(students.begin(), students.end(), 
        [](const Studentas& s) { return s.getGalutinis() >= 5.0f; });
    
    vargsiukai.insert(vargsiukai.end(), partition_point, students.end());
    students.erase(partition_point, students.end());
    
    return vargsiukai;
}

/**
 * @brief 3 strategija (specializacija list konteineriui)
 * @param students Studentu sarasas
 * @return Vargsiuku konteineris (galutinis < 5.0)
 */
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

/**
 * @struct ProcessingResult
 * @brief Apdorojimo rezultatu struktura
 * 
 * Saugo laiko matavimus kiekvienam etapu ir konteinerio tipa.
 */
struct ProcessingResult {
    double readDuration;    ///< Nuskaitymo laikas (s)
    double sortDuration;    ///< Rusiavimo laikas (s)
    double splitDuration;   ///< Dalijimo laikas (s)
    double writeDuration;   ///< Išvedimo laikas (s)
    double totalDuration;   ///< Bendras laikas (s)
    std::string containerType;  ///< Konteinerio tipas
    int strategy;           ///< Strategijos numeris (1-3)
    
    ProcessingResult() : readDuration(0), sortDuration(0), splitDuration(0), 
                         writeDuration(0), totalDuration(0), strategy(0) {}
};

#endif
