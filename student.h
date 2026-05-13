#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <chrono>
#include <cstring>

class Studentas {
private:
    std::string vardas;
    std::string pavarde;
    std::vector<int> tarp_rez;
    int egz_rez;
    float galutinis;

    float calculateAverage() const {
        if (tarp_rez.empty()) return 0.0f;
        int sum = 0;
        for (int val : tarp_rez) {
            sum += val;
        }
        return static_cast<float>(sum) / static_cast<float>(tarp_rez.size());
    }

    float calculateMedian() const {
        if (tarp_rez.empty()) return 0.0f;
        std::vector<int> sorted = tarp_rez;
        std::sort(sorted.begin(), sorted.end());
        size_t size = sorted.size();
        if (size % 2 == 0) {
            return (sorted[size/2 - 1] + sorted[size/2]) / 2.0f;
        } else {
            return static_cast<float>(sorted[size/2]);
        }
    }

public:
    Studentas() : vardas(""), pavarde(""), egz_rez(0), galutinis(-1.0f) {}

    Studentas(const std::string& firstName, const std::string& lastName)
        : vardas(firstName), pavarde(lastName), egz_rez(0), galutinis(-1.0f) {}

    ~Studentas() {
        vardas.clear();
        pavarde.clear();
        tarp_rez.clear();
        egz_rez = 0;
        galutinis = -1.0f;
    }

    void inputManual();
    void inputAuto();
    bool inputFromFile(const std::string& filename);
    
    void outputToConsole() const;
    void outputToFile(const std::string& filename) const;
    
    void clearData();

    Studentas(const Studentas& other)
        : vardas(other.vardas),
          pavarde(other.pavarde),
          tarp_rez(other.tarp_rez),
          egz_rez(other.egz_rez),
          galutinis(other.galutinis) {}

    Studentas(Studentas&& other) noexcept
        : vardas(std::move(other.vardas)),
          pavarde(std::move(other.pavarde)),
          tarp_rez(std::move(other.tarp_rez)),
          egz_rez(other.egz_rez),
          galutinis(other.galutinis) {
        other.egz_rez = 0;
        other.galutinis = -1.0f;
    }

    Studentas& operator=(const Studentas& other) {
        if (this != &other) {
            vardas = other.vardas;
            pavarde = other.pavarde;
            tarp_rez = other.tarp_rez;
            egz_rez = other.egz_rez;
            galutinis = other.galutinis;
        }
        return *this;
    }

    Studentas& operator=(Studentas&& other) noexcept {
        if (this != &other) {
            vardas = std::move(other.vardas);
            pavarde = std::move(other.pavarde);
            tarp_rez = std::move(other.tarp_rez);
            egz_rez = other.egz_rez;
            galutinis = other.galutinis;
            other.egz_rez = 0;
            other.galutinis = -1.0f;
        }
        return *this;
    }

    const std::string& getFirstName() const { return vardas; }
    const std::string& getLastName() const { return pavarde; }
    const std::vector<int>& getIntermediateGrades() const { return tarp_rez; }
    int getExamGrade() const { return egz_rez; }
    float getFinalGrade() const { return galutinis; }

    void setFirstName(const std::string& v) { vardas = v; }
    void setLastName(const std::string& p) { pavarde = p; }
    void addIntermediateGrade(int grade) { tarp_rez.push_back(grade); }
    void setExamGrade(int egz) { egz_rez = egz; }
    void setFinalGrade(float gal) { galutinis = gal; }

    bool operator<(const Studentas& other) const {
        return vardas < other.vardas;
    }

    bool operator>(const Studentas& other) const {
        return galutinis > other.galutinis;
    }

    bool operator==(const Studentas& other) const {
        return vardas == other.vardas && pavarde == other.pavarde;
    }

    bool operator!=(const Studentas& other) const {
        return !(*this == other);
    }

    bool operator<=(const Studentas& other) const {
        return *this < other || *this == other;
    }

    bool operator>=(const Studentas& other) const {
        return *this > other || *this == other;
    }

    struct CompareByLastName {
        bool operator()(const Studentas& a, const Studentas& b) const {
            return a.pavarde < b.pavarde;
        }
    };

    struct CompareByFinalGradeDesc {
        bool operator()(const Studentas& a, const Studentas& b) const {
            return a.galutinis > b.galutinis;
        }
    };

    void calculateFinalGrade(const std::string& choice) {
        float tarp_rez_val;
        if (choice == "1") {
            tarp_rez_val = calculateAverage();
        } else {
            tarp_rez_val = calculateMedian();
        }
        galutinis = 0.6f * egz_rez + 0.4f * tarp_rez_val;
    }

    friend std::ostream& operator<<(std::ostream& out, const Studentas& studentas);
    friend std::istream& operator>>(std::istream& in, Studentas& studentas);
};

std::ostream& operator<<(std::ostream& out, const Studentas& studentas) {
    out << studentas.vardas << " " << studentas.pavarde;
    out << " Tarpiniai pazymiai: [";
    for (size_t i = 0; i < studentas.tarp_rez.size(); ++i) {
        if (i > 0) out << ", ";
        out << studentas.tarp_rez[i];
    }
    out << "] Egzaminas: " << studentas.egz_rez;
    if (studentas.galutinis >= 0.0f) {
        out << " Galutinis: " << std::fixed << std::setprecision(2) << studentas.galutinis;
    }
    return out;
}

std::istream& operator>>(std::istream& in, Studentas& studentas) {
    std::cout << "Iveskite varda: ";
    in >> studentas.vardas;
    
    std::cout << "Iveskite pavarde: ";
    in >> studentas.pavarde;
    
    std::cout << "Iveskite tarpiniu pazymiu skaiciu: ";
    int tarp_count;
    in >> tarp_count;
    
    studentas.tarp_rez.clear();
    for (int i = 0; i < tarp_count; ++i) {
        std::cout << "Iveskite " << (i + 1) << "-aji pazymi: ";
        int grade;
        in >> grade;
        if (grade < 0 || grade > 10) {
            std::cout << "Neteisingas pazymys (turi buti 0-10), praleidziama.\n";
            continue;
        }
        studentas.tarp_rez.push_back(grade);
    }
    
    std::cout << "Iveskite egzamino rezultata (0-10): ";
    int egz;
    in >> egz;
    if (egz < 0 || egz > 10) {
        std::cout << "Neteisingas egzamino pazymys, nustatoma 0.\n";
        egz = 0;
    }
    studentas.egz_rez = egz;
    studentas.galutinis = -1.0f;
    
    return in;
}

const std::string vardai[] = {"Jonas", "Petras", "Antanas", "Vytautas", "Kazys", "Juozas", "Algirdas", "Bronius", "Edmundas", "Rimantas"};
const std::string pavardes[] = {"Jonaitis", "Petraitis", "Antanaitis", "Vytautaitis", "Kazaitis", "Juozaitis", "Algirdaitis", "Bronaitis", "Edmundaitis", "Rimantaitis"};

int getVarduKiekis() { return 10; }
int getPavardziuKiekis() { return 10; }

void generateRandomGrades(Studentas& studentas) {
    int tarp_count = rand() % 10 + 1;
    for (int i = 0; i < tarp_count; ++i) {
        studentas.addIntermediateGrade(rand() % 11);
    }
}

float calculateAverage(const std::vector<int>& arr) {
    if (arr.empty()) return 0.0f;
    int sum = 0;
    for (int val : arr) {
        sum += val;
    }
    return static_cast<float>(sum) / static_cast<float>(arr.size());
}

float calculateMedian(std::vector<int> arr) {   
    if (arr.empty()) return 0.0f;
    std::sort(arr.begin(), arr.end());
    size_t size = arr.size();
    if (size % 2 == 0) {
        return (arr[size/2 - 1] + arr[size/2]) / 2.0f;
    } else {
        return static_cast<float>(arr[size/2]);
    }
}

void generateRandomData(Studentas& studentas) {
    studentas.setFirstName(vardai[rand() % getVarduKiekis()]);
    studentas.setLastName(pavardes[rand() % getPavardziuKiekis()]);

    int tarp_count = rand() % 10 + 1; 
    for (int i = 0; i < tarp_count; ++i) {
        studentas.addIntermediateGrade(rand() % 11); 
    }
    studentas.setExamGrade(rand() % 11);
}

void readStudentData(Studentas& studentas) {
    std::string firstName, lastName;
    std::cout << "Iveskite varda: ";
    std::cin >> firstName;
    studentas.setFirstName(firstName);
    
    std::cout << "Iveskite pavarde: ";
    std::cin >> lastName;
    studentas.setLastName(lastName);

    while (true) {
        std::cout << "Iveskite " << studentas.getIntermediateGrades().size() + 1
                  << " tarpini rezultata (arba -1, jei baigete): ";
        int grade;
        if (!(std::cin >> grade)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Neteisinga ivedis. Bandykite dar karta.\n";
            continue;
        }

        if (grade == -1) {
            break;
        }
        if (grade < 0 || grade > 10) {
            std::cout << "Rezultatas turi buti nuo 0 iki 10. Bandykite dar karta.\n";
            continue;
        }
        studentas.addIntermediateGrade(grade);
    }

    if (studentas.getIntermediateGrades().empty()) {
        std::cout << "Turite ivesti bent viena tarpini rezultata. Generuojami atsitiktiniai.\n";
        generateRandomGrades(studentas);
    }

    std::cout << "Iveskite egzamino rezultata: ";
    int egz;
    while (!(std::cin >> egz) || egz < 0 || egz > 10) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Neteisinga ivedis (0-10). Bandykite dar karta: ";
    }
    studentas.setExamGrade(egz);
}

std::vector<Studentas> readFromFile(const std::string& filename) {
    std::vector<Studentas> students;
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Klaida: nepavyko atidaryti failo " + filename);
    }

    std::string line;
    std::getline(file, line);

    while (std::getline(file, line)) {
        if (line.empty()) continue; 

        std::istringstream iss(line);
        Studentas s;
        std::string firstName, lastName;
        if (!(iss >> firstName >> lastName)) continue;
        s.setFirstName(firstName);
        s.setLastName(lastName);

        int grade;
        for (int i = 0; i < 5; ++i) {
            if (iss >> grade) {
                s.addIntermediateGrade(grade);
            }
        }
        int egz;
        iss >> egz;
        s.setExamGrade(egz);
        students.push_back(s);
    }

    file.close();
    return students;
}

void calculateFinalGrade(Studentas& studentas, const std::string& choice) {
    studentas.calculateFinalGrade(choice);
}

void printResults(const std::vector<Studentas>& students,
                  const std::string& choice,
                  std::ostream& out)
{
    const int langelio_ilgis = 20;
    std::string kategorija = (choice == "1") ? "Galutinis (Vid.)" : "Galutinis (Med.)";

    out << std::left;
    out << std::setw(langelio_ilgis) << "Pavarde"
        << std::setw(langelio_ilgis) << "Vardas"
        << std::setw(langelio_ilgis) << kategorija << '\n';
    out << std::string(3 * langelio_ilgis, '-') << '\n';

    for (const auto& s : students) {
        out << std::setw(langelio_ilgis) << s.getLastName()
            << std::setw(langelio_ilgis) << s.getFirstName()
            << std::setw(langelio_ilgis) << std::fixed << std::setprecision(2) << s.getFinalGrade()
            << '\n';
    }
}

void displayResults(const std::vector<Studentas>& students, const std::string& choice) {
    printResults(students, choice, std::cout);
}

void writeResultsToAFile(const std::vector<Studentas>& students, const std::string& choice, const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile) {
        std::cerr << "Failed to open the file.\n";
        return; 
    }
    printResults(students, choice, outFile);
}

void runGenerationTest(const std::string& filename, int count) {
	auto start = std::chrono::high_resolution_clock::now();

	std::vector<Studentas> students;
	students.reserve(count);

	for (int j = 0; j < count; j++) {
		Studentas s;
		generateRandomData(s);
		students.push_back(s);
	}

	std::ofstream outFile(filename);
	outFile << std::left << std::setw(20) << "Vardas" << std::setw(20) << "Pavarde";
	for (int i = 0; i < 5; i++) {
		outFile << std::setw(10) << "Pazymys";
	}
	outFile << std::setw(10) << "Egzaminas\n";

	for (const auto& s : students) {
		outFile << std::left << std::setw(20) << s.getFirstName() << std::setw(20) << s.getLastName();
		for (int grade : s.getIntermediateGrades()) {
			outFile << std::setw(10) << grade;
		}
		outFile << std::setw(10) << s.getExamGrade() << "\n";
	}
	outFile.close();

	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	std::cout << filename << " generated " << count << " students in " << duration << "ms\n";
}

template<typename Container>
void runGenerationTestT(const std::string& filename, int count) {
	auto start = std::chrono::high_resolution_clock::now();
	Container students;
	for (int j = 0; j < count; j++) {
		Studentas s;
		generateRandomData(s);
		students.push_back(s);
	}
	std::ofstream outFile(filename);
	outFile << std::left << std::setw(20) << "Vardas" << std::setw(20) << "Pavarde";
	for (int i = 0; i < 5; i++) outFile << std::setw(10) << "Pazymys";
	outFile << std::setw(10) << "Egzaminas\n";
	for (const auto& s : students) {
		outFile << std::left << std::setw(20) << s.getFirstName() << std::setw(20) << s.getLastName();
		for (int grade : s.getIntermediateGrades()) outFile << std::setw(10) << grade;
		outFile << std::setw(10) << s.getExamGrade() << "\n";
	}
	outFile.close();
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	std::cout << filename << " generated " << count << " students in " << duration << "ms\n";
}

void runProcessingTest(const std::string& filename) {
    auto read_start = std::chrono::high_resolution_clock::now();
    std::vector<Studentas> students = readFromFile(filename);
    auto read_end = std::chrono::high_resolution_clock::now();
	auto read_duration = std::chrono::duration_cast<std::chrono::milliseconds>(read_end - read_start).count();
	std::cout << filename << " read " << read_duration << "ms\n";
    
    auto sort_start = std::chrono::high_resolution_clock::now();
    for (auto& s : students) {
        s.calculateFinalGrade("1");
    }
    
    std::vector<Studentas> vargsiukai;
    std::vector<Studentas> kietiakiai;
    
    for (const auto& s : students) {
        if (s.getFinalGrade() < 5.0f) {
            vargsiukai.push_back(s);
        } else {
            kietiakiai.push_back(s);
        }
    }
    auto sort_end = std::chrono::high_resolution_clock::now();
	auto sort_duration = std::chrono::duration_cast<std::chrono::milliseconds>(sort_end - sort_start).count();
	std::cout << filename << " sort " << sort_duration << "ms\n";
    
    auto write_start = std::chrono::high_resolution_clock::now();
    auto write_to_file = [&](const std::string& fname, const std::vector<Studentas>& list) {
        std::ofstream out(fname);
        out << std::left << std::setw(20) << "Vardas" << std::setw(20) << "Pavarde" << "Galutinis\n";
        for (const auto& s : list) {
            out << std::left << std::setw(20) << s.getFirstName() << std::setw(20) << s.getLastName() 
                << std::fixed << std::setprecision(2) << s.getFinalGrade() << "\n";
        }
        out.close();
    };
    
    write_to_file("vargsiukai.txt", vargsiukai);
    write_to_file("kietiakai.txt", kietiakiai);
    auto write_end = std::chrono::high_resolution_clock::now();
	auto write_duration = std::chrono::duration_cast<std::chrono::milliseconds>(write_end - write_start).count();
	std::cout << filename << " write " << write_duration << "ms\n";
    
	auto total_duration = std::chrono::duration_cast<std::chrono::milliseconds>(write_end - read_start).count();
	std::cout << filename << " all " << total_duration << "ms\n";
}

template<typename Container>
Container readFromFileGeneric(const std::string& filename) {
    Container students;
    std::ifstream file(filename);
    if (!file.is_open()) throw std::runtime_error("Cannot open: " + filename);
    std::string line;
    std::getline(file, line);
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::istringstream iss(line);
        Studentas s;
        std::string firstName, lastName;
        iss >> firstName >> lastName;
        s.setFirstName(firstName);
        s.setLastName(lastName);
        int grade;
        for (int i = 0; i < 5; ++i) {
            if (iss >> grade) s.addIntermediateGrade(grade);
        }
        int egz;
        iss >> egz;
        s.setExamGrade(egz);
        s.calculateFinalGrade("1");
        students.push_back(s);
    }
    return students;
}

template<typename Container>
void partitionStrategy1(const Container& students, Container& vargsiukai, Container& kietiakiai) {
    for (const auto& s : students) {
        if (s.getFinalGrade() < 5.0f) vargsiukai.push_back(s);
        else kietiakiai.push_back(s);
    }
}

template<typename Container>
void partitionStrategy2(Container& students, Container& vargsiukai) {
    for (auto it = students.begin(); it != students.end(); ) {
        if (it->getFinalGrade() < 5.0f) {
            vargsiukai.push_back(std::move(*it));
            it = students.erase(it);
        } else {
            ++it;
        }
    }
}

template<typename Container>
void partitionStrategy3(Container& students, Container& vargsiukai, Container& kietiakiai) {
    auto partition_it = std::stable_partition(students.begin(), students.end(),
        [](const Studentas& s) { return s.getFinalGrade() >= 5.0f; });
    kietiakiai.assign(students.begin(), partition_it);
    vargsiukai.assign(partition_it, students.end());
}

template<typename Container>
long long runPartitionBenchmark(const std::string& filename, int strategy) {
    Container students = readFromFileGeneric<Container>(filename);
    for (auto& s : students) {
        s.calculateFinalGrade("1");
    }
    
    auto part_start = std::chrono::high_resolution_clock::now();
    Container vargsiukai, kietiakiai;
    
    if (strategy == 1) {
        partitionStrategy1(students, vargsiukai, kietiakiai);
    } else if (strategy == 2) {
        partitionStrategy2(students, vargsiukai);
    } else {
        partitionStrategy3(students, vargsiukai, kietiakiai);
    }
    
    auto part_end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(part_end - part_start).count();
}

void Studentas::clearData() {
    vardas.clear();
    pavarde.clear();
    tarp_rez.clear();
    egz_rez = 0;
    galutinis = -1.0f;
}

void Studentas::inputManual() {
    clearData();
    std::cout << "Įveskite vardą: ";
    std::cin >> vardas;
    
    std::cout << "Įveskite pavardę: ";
    std::cin >> pavarde;
    
    std::cout << "Įveskite tarpinių pažymių skaičių: ";
    int tarp_count;
    std::cin >> tarp_count;
    
    for (int i = 0; i < tarp_count; ++i) {
        std::cout << "Įveskite " << (i + 1) << "-ąjį pažymį: ";
        int grade;
        std::cin >> grade;
        if (grade >= 0 && grade <= 10) {
            tarp_rez.push_back(grade);
        }
    }
    
    std::cout << "Įveskite egzamino rezultatą (0-10): ";
    std::cin >> egz_rez;
}

void Studentas::inputAuto() {
    clearData();
    generateRandomData(*this);
}

bool Studentas::inputFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;
    
    clearData();
    std::string line;
    std::getline(file, line);
    
    if (std::getline(file, line) && !line.empty()) {
        std::istringstream iss(line);
        std::string firstName, lastName;
        if (iss >> firstName >> lastName) {
            vardas = firstName;
            pavarde = lastName;
            
            int grade;
            for (int i = 0; i < 5; ++i) {
                if (iss >> grade) {
                    tarp_rez.push_back(grade);
                }
            }
            iss >> egz_rez;
        }
    }
    file.close();
    return !vardas.empty();
}

void Studentas::outputToConsole() const {
    std::cout << std::left << std::setw(20) << pavarde
              << std::setw(20) << vardas;
    
    if (galutinis >= 0.0f) {
        std::cout << std::fixed << std::setprecision(2) << galutinis;
    } else {
        std::cout << "Nėra";
    }
    std::cout << std::endl;
}

void Studentas::outputToFile(const std::string& filename) const {
    std::ofstream file(filename, std::ios::app);
    if (file.is_open()) {
        file << std::left << std::setw(20) << pavarde
             << std::setw(20) << vardas
             << std::fixed << std::setprecision(2) << galutinis << "\n";
        file.close();
    }
}

#endif
