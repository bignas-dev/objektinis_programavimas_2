#include "student.h"
#include <iostream>
#include <sstream>
#include <cassert>
#include <cmath>
#include <fstream>

class V15Test {
private:
    int passedTests = 0;
    int totalTests = 0;
    
    void testResult(bool condition, const std::string& testName) {
        totalTests++;
        if (condition) {
            passedTests++;
            std::cout << "✅ [PASS] " << testName << "\n";
        } else {
            std::cout << "❌ [FAIL] " << testName << "\n";
        }
    }
    
    bool floatEquals(float a, float b, float epsilon = 0.01f) {
        return std::abs(a - b) < epsilon;
    }

public:
    void testAbstractClass() {
        std::cout << "\n=== Abstrakčios klasės Žmogus testas ===\n";
        
        // Šis kodas NETURI kompiliuotis (komentuotas):
        // Zmogus z;  // KLAIDA: negalima sukurti abstrakčios klasės objekto
        // Zmogus z("Vardas", "Pavarde");  // KLAIDA
        
        // Galima sukurti rodyklę į bazinę klasę
        Zmogus* z = nullptr;
        testResult(z == nullptr, "Galima sukurti nullptr rodyklę į Zmogus");
        
        // Galima sukurti Studentas objektą per bazinės klasės rodyklę
        z = new Studentas("Testas", "Testauskas");
        testResult(z != nullptr, "Galima nukreipti rodyklę į Studentas objektą");
        testResult(z->getVardas() == "Testas", "Bazinė rodyklė pasiekia getVardas()");
        delete z;
        
        testResult(true, "Zmogus yra abstrakti klasė - negalima sukurti objekto");
    }
    
    void testDefaultConstructor() {
        std::cout << "\n--- Numatytasis konstruktorius ---\n";
        Studentas s;
        testResult(s.getVardas() == "", "Numatytasis konstruktorius: vardas");
        testResult(s.getPavarde() == "", "Numatytasis konstruktorius: pavarde");
        testResult(s.getTarpRez().empty(), "Numatytasis konstruktorius: tarp_rez");
        testResult(s.getEgzRez() == 0, "Numatytasis konstruktorius: egz_rez");
        testResult(floatEquals(s.getGalutinis(), 0.0f), "Numatytasis konstruktorius: galutinis");
    }
    
    void testParameterizedConstructor() {
        std::cout << "\n--- Parametrinis konstruktorius ---\n";
        Studentas s("Jonas", "Jonaitis");
        testResult(s.getVardas() == "Jonas", "Parametrinis konstruktorius: vardas");
        testResult(s.getPavarde() == "Jonaitis", "Parametrinis konstruktorius: pavarde");
        testResult(s.getTarpRez().empty(), "Parametrinis konstruktorius: tarp_rez");
        testResult(s.getEgzRez() == 0, "Parametrinis konstruktorius: egz_rez");
    }
    
    void testCopyConstructor() {
        std::cout << "\n--- Kopijavimo konstruktorius ---\n";
        Studentas original("Petras", "Petraitis");
        original.addTarpRez(8);
        original.addTarpRez(9);
        original.setEgzRez(10);
        original.setGalutinis(9.5f);
        
        Studentas kopija(original);
        testResult(kopija.getVardas() == "Petras", "Kopijavimo konstr.: vardas");
        testResult(kopija.getPavarde() == "Petraitis", "Kopijavimo konstr.: pavarde");
        testResult(kopija.getTarpRez().size() == 2, "Kopijavimo konstr.: tarp_rez dydis");
        testResult(kopija.getTarpRez()[0] == 8, "Kopijavimo konstr.: pirmas rez");
        testResult(kopija.getTarpRez()[1] == 9, "Kopijavimo konstr.: antras rez");
        testResult(kopija.getEgzRez() == 10, "Kopijavimo konstr.: egz_rez");
        testResult(floatEquals(kopija.getGalutinis(), 9.5f), "Kopijavimo konstr.: galutinis");
        
        testResult(kopija.getVardas() == "Petras", "Kopijavimo konstr.: kopijos vardas");
        kopija.setVardas("Antanas");
        testResult(original.getVardas() == "Petras", "Kopijavimo konstr.: nepriklausomumas");
    }
    
    void testMoveConstructor() {
        std::cout << "\n--- Move (perkėlimo) konstruktorius ---\n";
        Studentas original("Ona", "Onutė");
        original.addTarpRez(7);
        original.addTarpRez(8);
        original.setEgzRez(9);
        original.setGalutinis(8.2f);
        
        std::string originalVardas = original.getVardas();
        Studentas perkeltas(std::move(original));
        
        testResult(perkeltas.getVardas() == originalVardas, "Move konstr.: vardas perkeltas");
        testResult(perkeltas.getPavarde() == "Onutė", "Move konstr.: pavarde perkelta");
        testResult(perkeltas.getTarpRez().size() == 2, "Move konstr.: tarp_rez perkeltas");
        testResult(perkeltas.getEgzRez() == 9, "Move konstr.: egz_rez perkeltas");
        testResult(floatEquals(perkeltas.getGalutinis(), 8.2f), "Move konstr.: galutinis perkeltas");
    }
    
    void testCopyAssignment() {
        std::cout << "\n--- Kopijavimo priskyrimo operatorius ---\n";
        Studentas s1("Vardas1", "Pavarde1");
        s1.addTarpRez(6);
        s1.addTarpRez(7);
        s1.setEgzRez(8);
        s1.setGalutinis(7.2f);
        
        Studentas s2("Vardas2", "Pavarde2");
        s2 = s1;
        
        testResult(s2.getVardas() == "Vardas1", "Kopijavimo =: vardas");
        testResult(s2.getPavarde() == "Pavarde1", "Kopijavimo =: pavarde");
        testResult(s2.getTarpRez().size() == 2, "Kopijavimo =: tarp_rez dydis");
        testResult(s2.getTarpRez()[0] == 6, "Kopijavimo =: pirmas rez");
        testResult(floatEquals(s2.getGalutinis(), 7.2f), "Kopijavimo =: galutinis");
        
        s1 = s1;
        testResult(s1.getVardas() == "Vardas1", "Self-assignment: apsauga");
    }
    
    void testMoveAssignment() {
        std::cout << "\n--- Move priskyrimo operatorius ---\n";
        Studentas s1("MoveVardas", "MovePavarde");
        s1.addTarpRez(9);
        s1.addTarpRez(10);
        s1.setEgzRez(10);
        s1.setGalutinis(9.8f);
        
        Studentas s2("Target", "Target");
        s2 = std::move(s1);
        
        testResult(s2.getVardas() == "MoveVardas", "Move =: vardas perkeltas");
        testResult(s2.getPavarde() == "MovePavarde", "Move =: pavarde perkelta");
        testResult(s2.getTarpRez().size() == 2, "Move =: tarp_rez perkeltas");
        testResult(s2.getEgzRez() == 10, "Move =: egz_rez perkeltas");
        testResult(floatEquals(s2.getGalutinis(), 9.8f), "Move =: galutinis perkeltas");
    }
    
    void testOutputStreamOperator() {
        std::cout << "\n--- Išvesties operatorius (operator<<) ---\n";
        Studentas s("Testas", "Testauskas");
        s.addTarpRez(8);
        s.addTarpRez(9);
        s.addTarpRez(7);
        s.setEgzRez(10);
        s.setGalutinis(9.2f);
        
        std::ostringstream oss;
        oss << s;
        std::string output = oss.str();
        
        testResult(output.find("Testas") != std::string::npos, "operator<<: vardas išvestas");
        testResult(output.find("Testauskas") != std::string::npos, "operator<<: pavarde išvesta");
        testResult(output.find("10") != std::string::npos, "operator<<: egz_rez išvestas");
        testResult(output.find("8") != std::string::npos, "operator<<: tarp_rez išvesti");
        
        std::cout << "   Išvestis: " << output << "\n";
    }
    
    void testInputStreamOperator() {
        std::cout << "\n--- Įvesties operatorius (operator>>) ---\n";
        std::istringstream iss("Jonas Jonaitis 7 8 9 6 5 10");
        Studentas s;
        iss >> s;
        
        testResult(s.getVardas() == "Jonas", "operator>>: vardas nuskaitytas");
        testResult(s.getPavarde() == "Jonaitis", "operator>>: pavarde nuskaityta");
        testResult(s.getTarpRez().size() == 5, "operator>>: tarp_rez dydis (5)");
        testResult(s.getTarpRez()[0] == 7, "operator>>: pirmas rez");
        testResult(s.getTarpRez()[4] == 5, "operator>>: penktas tarp_rez");
        testResult(s.getEgzRez() == 10, "operator>>: egz_rez nuskaitytas");
    }
    
    void testFileIO() {
        std::cout << "\n--- Failo įvestis/išvestis ---\n";
        Studentas s("Failas", "Failauskas");
        s.addTarpRez(5);
        s.addTarpRez(6);
        s.addTarpRez(7);
        s.addTarpRez(8);
        s.addTarpRez(9);
        s.setEgzRez(10);
        s.setGalutinis(8.8f);
        
        std::ofstream out("test_io_temp.txt");
        if (out.is_open()) {
            out << s << "\n";
            out.close();
            
            std::ifstream in("test_io_temp.txt");
            Studentas s2;
            in >> s2;
            in.close();
            
            testResult(s2.getVardas() == "Failas", "Failo IO: vardas");
            testResult(s2.getPavarde() == "Failauskas", "Failo IO: pavarde");
            testResult(s2.getTarpRez().size() == 5, "Failo IO: tarp_rez dydis");
            testResult(s2.getEgzRez() == 10, "Failo IO: egz_rez");
            
            std::remove("test_io_temp.txt");
        } else {
            testResult(false, "Failo IO: nepavyko atidaryti failo");
        }
    }
    
    void testDestructor() {
        std::cout << "\n--- Destruktorius ---\n";
        {
            Studentas s("Temp", "Tempauskas");
            s.addTarpRez(1);
            s.addTarpRez(2);
            s.addTarpRez(3);
            s.addTarpRez(4);
            s.addTarpRez(5);
        }
        testResult(true, "Destructorius: nekrenta sunaikinant objektą");
        
        Studentas* dynamicStudent = new Studentas("Dynamic", "Dynamicauskas");
        dynamicStudent->addTarpRez(10);
        delete dynamicStudent;
        testResult(true, "Destructorius: nekrenta sunaikinant dinamini objektą");
    }
    
    void testPolymorphism() {
        std::cout << "\n--- Polimorfizmo testas ---\n";
        
        Zmogus* z = new Studentas("Polis", "Poliauskas");
        testResult(z->getVardas() == "Polis", "Polimorfizmas: getVardas per bazinę");
        testResult(z->getPavarde() == "Poliauskas", "Polimorfizmas: getPavarde per bazinę");
        
        // Cast'iname atgal į Studentas* kad naudoti operator<<
        Studentas* s_ptr = dynamic_cast<Studentas*>(z);
        testResult(s_ptr != nullptr, "Polimorfizmas: dynamic_cast veikia");
        
        std::ostringstream oss;
        oss << *s_ptr;
        testResult(oss.str().find("Polis") != std::string::npos, "Polimorfizmas: operator<< per cast");
        
        delete z;
        
        // Vector of base class pointers
        std::vector<Zmogus*> people;
        people.push_back(new Studentas("Studentas1", "Pavarde1"));
        people.push_back(new Studentas("Studentas2", "Pavarde2"));
        
        testResult(people.size() == 2, "Polimorfizmas: vector<Zmogus*> dydis");
        testResult(people[0]->getVardas() == "Studentas1", "Polimorfizmas: pirmas vardas");
        testResult(people[1]->getVardas() == "Studentas2", "Polimorfizmas: antras vardas");
        
        for (auto p : people) {
            delete p;
        }
    }
    
    void testFullIntegration() {
        std::cout << "\n--- Pilnas integracijos testas ---\n";
        
        Studentas s1("Integracija", "Testas");
        s1.addTarpRez(7);
        s1.addTarpRez(8);
        s1.addTarpRez(9);
        s1.setEgzRez(10);
        calculateFinalGrade(s1, "1");
        
        Studentas s2(s1);
        Studentas s3(std::move(s2));
        Studentas s4;
        s4 = s3;
        
        std::ostringstream oss;
        oss << s4;
        std::string output = oss.str();
        
        testResult(output.find("Integracija") != std::string::npos, 
                   "Integracijos testas: vardas išvestas");
        testResult(output.find("Testas") != std::string::npos, 
                   "Integracijos testas: pavarde išvesta");
        testResult(!output.empty(), "Integracijos testas: pilnas ciklas");
        testResult(floatEquals(s4.getGalutinis(), 9.2f), 
                   "Integracijos testas: galutinis apskaiciuotas");
        
        std::cout << "   Galutinė išvestis: " << output << "\n";
    }
    
    void testMultipleStudentsIO() {
        std::cout << "\n--- Keliu studentu įvestis/išvestis ---\n";
        
        std::vector<Studentas> students;
        students.emplace_back("Studentas1", "Pavarde1");
        students.emplace_back("Studentas2", "Pavarde2");
        students.emplace_back("Studentas3", "Pavarde3");
        
        students[0].addTarpRez(5);
        students[0].setEgzRez(6);
        students[0].setGalutinis(5.5f);
        
        students[1].addTarpRez(7);
        students[1].addTarpRez(8);
        students[1].setEgzRez(9);
        students[1].setGalutinis(8.2f);
        
        students[2].addTarpRez(10);
        students[2].setEgzRez(10);
        students[2].setGalutinis(10.0f);
        
        std::ofstream out("test_multiple.txt");
        for (const auto& s : students) {
            out << s << "\n";
        }
        out.close();
        
        std::ifstream in("test_multiple.txt");
        std::vector<Studentas> loadedStudents;
        std::string line;
        while (std::getline(in, line)) {
            if (!line.empty()) {
                std::istringstream iss(line);
                Studentas s;
                iss >> s;
                loadedStudents.push_back(s);
            }
        }
        in.close();
        
        testResult(loadedStudents.size() == 3, "Keliu studentu IO: kiekis");
        testResult(loadedStudents[0].getVardas() == "Studentas1", "Keliu studentu IO: pirmas vardas");
        testResult(loadedStudents[1].getVardas() == "Studentas2", "Keliu studentu IO: antras vardas");
        testResult(loadedStudents[2].getVardas() == "Studentas3", "Keliu studentu IO: trecias vardas");
        
        std::remove("test_multiple.txt");
    }
    
    void runAllTests() {
        std::cout << "\n";
        std::cout << "╔══════════════════════════════════════════════════════════╗\n";
        std::cout << "║    V1.5 TESTAI (Abstrakti klasė + Rule of Five + I/O)    ║\n";
        std::cout << "╚══════════════════════════════════════════════════════════╝\n";
        
        testAbstractClass();
        testDefaultConstructor();
        testParameterizedConstructor();
        testCopyConstructor();
        testMoveConstructor();
        testCopyAssignment();
        testMoveAssignment();
        testOutputStreamOperator();
        testInputStreamOperator();
        testFileIO();
        testDestructor();
        testPolymorphism();
        testMultipleStudentsIO();
        testFullIntegration();
        
        std::cout << "\n";
        std::cout << "╔══════════════════════════════════════════════════════════╗\n";
        std::cout << "║                    REZULTATAI                            ║\n";
        std::cout << "╠══════════════════════════════════════════════════════════╣\n";
        std::cout << "║  Iš viso testų:    " << std::setw(34) << totalTests << " ║\n";
        std::cout << "║  Sėkmingai:        " << std::setw(34) << passedTests << " ║\n";
        std::cout << "║  Nesėkmingai:      " << std::setw(34) << (totalTests - passedTests) << " ║\n";
        
        float percentage = (totalTests > 0) ? (100.0f * passedTests / totalTests) : 0.0f;
        std::cout << "║  Sėkmės rodiklis:  " << std::fixed << std::setprecision(1) 
                  << std::setw(30) << percentage << "% ║\n";
        std::cout << "╚══════════════════════════════════════════════════════════╝\n";
        
        if (passedTests == totalTests) {
            std::cout << "\n🎉 VISI TESTAI SĖKMINGI! V1.5 paruošta release'ui.\n\n";
        } else {
            std::cout << "\n⚠️  KAI KURIE TESTAI NEPRAEJO. Reikia patikrinti klaidas.\n\n";
        }
    }
};

int main() {
    srand(42);
    
    V15Test test;
    test.runAllTests();
    
    return 0;
}
