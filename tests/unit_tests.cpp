/**
 * @file unit_tests.cpp
 * @brief Catch2 unit testai Studentas ir Zmogus klasems
 * 
 * Testai apima:
 * - Rule of Five (būtina)
 * - I/O operatoriai
 * - Polimorfizmas
 * - Abstrakti klase
 */

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../student.h"
#include "../zmogus.h"

// ============================================================================
// RULE OF FIVE TESTAI (BŪTINA)
// ============================================================================

TEST_CASE("Studentas Rule of Five", "[Studentas][RuleOfFive]") {
    
    // 1. Numatytasis konstruktorius
    SECTION("Default Constructor") {
        Studentas s;
        REQUIRE(s.getVardas() == "");
        REQUIRE(s.getPavarde() == "");
        REQUIRE(s.getTarpRez().empty());
        REQUIRE(s.getEgzRez() == 0);
        REQUIRE(s.getGalutinis() == 0.0f);
    }
    
    // 2. Parametrinis konstruktorius
    SECTION("Parameterized Constructor") {
        Studentas s("Jonas", "Jonaitis");
        REQUIRE(s.getVardas() == "Jonas");
        REQUIRE(s.getPavarde() == "Jonaitis");
        REQUIRE(s.getTarpRez().empty());
        REQUIRE(s.getEgzRez() == 0);
    }
    
    // 3. Kopijavimo konstruktorius
    SECTION("Copy Constructor") {
        Studentas original("Petras", "Petraitis");
        original.addTarpRez(8);
        original.addTarpRez(9);
        original.setEgzRez(10);
        original.setGalutinis(9.5f);
        
        Studentas copy(original);
        
        REQUIRE(copy.getVardas() == "Petras");
        REQUIRE(copy.getPavarde() == "Petraitis");
        REQUIRE(copy.getTarpRez().size() == 2);
        REQUIRE(copy.getTarpRez()[0] == 8);
        REQUIRE(copy.getTarpRez()[1] == 9);
        REQUIRE(copy.getEgzRez() == 10);
        REQUIRE(copy.getGalutinis() == 9.5f);
        
        // Patikrinti nepriklausomuma
        copy.setVardas("Antanas");
        REQUIRE(original.getVardas() == "Petras");
    }
    
    // 4. Move konstruktorius
    SECTION("Move Constructor") {
        Studentas original("Ona", "Onute");
        original.addTarpRez(7);
        original.addTarpRez(8);
        original.setEgzRez(9);
        original.setGalutinis(8.2f);
        
        std::string originalVardas = original.getVardas();
        Studentas moved(std::move(original));
        
        REQUIRE(moved.getVardas() == originalVardas);
        REQUIRE(moved.getPavarde() == "Onute");
        REQUIRE(moved.getTarpRez().size() == 2);
        REQUIRE(moved.getEgzRez() == 9);
        REQUIRE(moved.getGalutinis() == 8.2f);
    }
    
    // 5. Destruktorius (netiesioginis testas)
    SECTION("Destructor") {
        {
            Studentas s("Temp", "Tempauskas");
            s.addTarpRez(1);
            s.addTarpRez(2);
            s.addTarpRez(3);
            // s bus sunaikintas čia - jei nekrito, testas praeina
        }
        REQUIRE(true);  // Jei nekrito, destruktorius veikia
    }
    
    // 6. Kopijavimo priskyrimo operatorius
    SECTION("Copy Assignment Operator") {
        Studentas s1("Vardas1", "Pavarde1");
        s1.addTarpRez(6);
        s1.addTarpRez(7);
        s1.setEgzRez(8);
        s1.setGalutinis(7.2f);
        
        Studentas s2("Vardas2", "Pavarde2");
        s2 = s1;
        
        REQUIRE(s2.getVardas() == "Vardas1");
        REQUIRE(s2.getPavarde() == "Pavarde1");
        REQUIRE(s2.getTarpRez().size() == 2);
        REQUIRE(s2.getTarpRez()[0] == 6);
        REQUIRE(s2.getGalutinis() == 7.2f);
        
        // Self-assignment apsauga
        s1 = s1;
        REQUIRE(s1.getVardas() == "Vardas1");
    }
    
    // 7. Move priskyrimo operatorius
    SECTION("Move Assignment Operator") {
        Studentas s1("MoveVardas", "MovePavarde");
        s1.addTarpRez(9);
        s1.addTarpRez(10);
        s1.setEgzRez(10);
        s1.setGalutinis(9.8f);
        
        Studentas s2("Target", "Target");
        s2 = std::move(s1);
        
        REQUIRE(s2.getVardas() == "MoveVardas");
        REQUIRE(s2.getPavarde() == "MovePavarde");
        REQUIRE(s2.getTarpRez().size() == 2);
        REQUIRE(s2.getEgzRez() == 10);
        REQUIRE(s2.getGalutinis() == 9.8f);
    }
}

// ============================================================================
// I/O OPERATORIŲ TESTAI
// ============================================================================

TEST_CASE("Studentas I/O Operators", "[Studentas][IO]") {
    
    SECTION("Output Operator (operator<<)") {
        Studentas s("Testas", "Testauskas");
        s.addTarpRez(8);
        s.addTarpRez(9);
        s.addTarpRez(7);
        s.setEgzRez(10);
        
        std::ostringstream oss;
        oss << s;
        std::string output = oss.str();
        
        REQUIRE(output.find("Testas") != std::string::npos);
        REQUIRE(output.find("Testauskas") != std::string::npos);
        REQUIRE(output.find("10") != std::string::npos);
        REQUIRE(output.find("8") != std::string::npos);
    }
    
    SECTION("Input Operator (operator>>)") {
        std::istringstream iss("Jonas Jonaitis 7 8 9 6 5 10");
        Studentas s;
        iss >> s;
        
        REQUIRE(s.getVardas() == "Jonas");
        REQUIRE(s.getPavarde() == "Jonaitis");
        REQUIRE(s.getTarpRez().size() == 5);
        REQUIRE(s.getTarpRez()[0] == 7);
        REQUIRE(s.getTarpRez()[4] == 5);
        REQUIRE(s.getEgzRez() == 10);
    }
    
    SECTION("File I/O") {
        Studentas s("Failas", "Failauskas");
        s.addTarpRez(5);
        s.addTarpRez(6);
        s.addTarpRez(7);
        s.addTarpRez(8);
        s.addTarpRez(9);
        s.setEgzRez(10);
        
        std::ofstream out("test_io_temp.txt");
        REQUIRE(out.is_open());
        out << s << "\n";
        out.close();
        
        std::ifstream in("test_io_temp.txt");
        REQUIRE(in.is_open());
        Studentas s2;
        in >> s2;
        in.close();
        
        REQUIRE(s2.getVardas() == "Failas");
        REQUIRE(s2.getPavarde() == "Failauskas");
        REQUIRE(s2.getTarpRez().size() == 5);
        REQUIRE(s2.getEgzRez() == 10);
        
        std::remove("test_io_temp.txt");
    }
}

// ============================================================================
// POLIMORFIZMO TESTAI
// ============================================================================

TEST_CASE("Polymorphism", "[Zmogus][Polymorphism]") {
    
    SECTION("Base class pointer to derived") {
        Zmogus* z = new Studentas("Polis", "Poliauskas");
        
        REQUIRE(z->getVardas() == "Polis");
        REQUIRE(z->getPavarde() == "Poliauskas");
        
        delete z;
    }
    
    SECTION("Vector of base class pointers") {
        std::vector<Zmogus*> people;
        people.push_back(new Studentas("S1", "P1"));
        people.push_back(new Studentas("S2", "P2"));
        people.push_back(new Studentas("S3", "P3"));
        
        REQUIRE(people.size() == 3);
        REQUIRE(people[0]->getVardas() == "S1");
        REQUIRE(people[1]->getVardas() == "S2");
        REQUIRE(people[2]->getVardas() == "S3");
        
        // Išvalyti atminti
        for (auto p : people) {
            delete p;
        }
    }
    
    SECTION("Dynamic cast from base to derived") {
        Zmogus* z = new Studentas("Cast", "Castauskas");
        
        Studentas* s = dynamic_cast<Studentas*>(z);
        REQUIRE(s != nullptr);
        REQUIRE(s->getVardas() == "Cast");
        
        delete z;
    }
}

// ============================================================================
// ABSTRAKČIOS KLASĖS TESTAI
// ============================================================================

TEST_CASE("Abstract Class Zmogus", "[Zmogus][Abstract]") {
    
    SECTION("Cannot instantiate Zmogus directly") {
        // Zmogus z; // Šis kodas NEKOMPILIUOSI - compile-time error
        // Tai patikrinama kompiliatoriaus, ne runtime
        
        // Galima sukurti nullptr rodykle
        Zmogus* z = nullptr;
        REQUIRE(z == nullptr);
        
        // Galima nukreipti i Studentas
        z = new Studentas("Test", "Testas");
        REQUIRE(z != nullptr);
        REQUIRE(z->getVardas() == "Test");
        
        delete z;
    }
    
    SECTION("Zmogus pointer can call virtual methods") {
        Zmogus* z = new Studentas("Virtual", "Virtualauskas");
        
        // Castinti atgal i Studentas* kad naudoti metodus
        Studentas* s = dynamic_cast<Studentas*>(z);
        REQUIRE(s != nullptr);
        
        s->addTarpRez(8);
        s->addTarpRez(9);
        s->setEgzRez(10);
        
        REQUIRE(z->getVardas() == "Virtual");
        REQUIRE(z->getPavarde() == "Virtualauskas");
        
        // I/O per Studentas*
        std::ostringstream oss;
        oss << *s;
        REQUIRE(oss.str().find("Virtual") != std::string::npos);
        
        delete z;
    }
}

// ============================================================================
// HELPER FUNCTION TESTAI
// ============================================================================

TEST_CASE("Helper Functions", "[Helpers]") {
    
    SECTION("calculateAverage") {
        std::vector<int> grades = {5, 6, 7, 8, 9};
        float avg = calculateAverage(grades);
        REQUIRE(avg == 7.0f);
        
        std::vector<int> empty;
        REQUIRE(calculateAverage(empty) == 0.0f);
    }
    
    SECTION("calculateMedian") {
        std::vector<int> odd = {1, 3, 5, 7, 9};
        REQUIRE(calculateMedian(odd) == 5.0f);
        
        std::vector<int> even = {1, 2, 3, 4, 5, 6};
        REQUIRE(calculateMedian(even) == 3.5f);
        
        std::vector<int> empty;
        REQUIRE(calculateMedian(empty) == 0.0f);
    }
    
    SECTION("calculateFinalGrade") {
        Studentas s("Test", "Testas");
        s.addTarpRez(8);
        s.addTarpRez(9);
        s.addTarpRez(10);
        s.setEgzRez(10);
        
        calculateFinalGrade(s, "1");  // Vidurkis
        float expected = 0.6f * 10 + 0.4f * 9.0f;  // 9.6
        REQUIRE(s.getGalutinis() == Approx(expected).epsilon(0.01));
    }
}

// ============================================================================
// INTEGRACIJOS TESTAI
// ============================================================================

TEST_CASE("Full Integration", "[Integration]") {
    
    SECTION("Complete workflow") {
        // Sukurti studenta
        Studentas s1("Integracija", "Testas");
        s1.addTarpRez(7);
        s1.addTarpRez(8);
        s1.addTarpRez(9);
        s1.setEgzRez(10);
        calculateFinalGrade(s1, "1");
        
        // Kopijuoti
        Studentas s2(s1);
        
        // Perkelti
        Studentas s3(std::move(s2));
        
        // Priskyrimas
        Studentas s4;
        s4 = s3;
        
        // Išvestis
        std::ostringstream oss;
        oss << s4;
        
        REQUIRE(oss.str().find("Integracija") != std::string::npos);
        REQUIRE(oss.str().find("Testas") != std::string::npos);
        REQUIRE(s4.getGalutinis() == Approx(9.2f).epsilon(0.01));
    }
    
    SECTION("Multiple students with polymorphism") {
        std::vector<Zmogus*> people;
        
        auto s1 = new Studentas("S1", "P1");
        s1->addTarpRez(5);
        s1->setEgzRez(6);
        calculateFinalGrade(*s1, "1");
        
        auto s2 = new Studentas("S2", "P2");
        s2->addTarpRez(8);
        s2->setEgzRez(9);
        calculateFinalGrade(*s2, "1");
        
        people.push_back(s1);
        people.push_back(s2);
        
        REQUIRE(people.size() == 2);
        REQUIRE(people[0]->getVardas() == "S1");
        REQUIRE(people[1]->getVardas() == "S2");
        
        // Išvestis per Studentas* (Zmogus* neturi operator<<)
        std::ostringstream oss;
        for (const auto* p : people) {
            const Studentas* s = dynamic_cast<const Studentas*>(p);
            REQUIRE(s != nullptr);
            oss << *s << "\n";
        }
        
        REQUIRE(oss.str().find("S1") != std::string::npos);
        REQUIRE(oss.str().find("S2") != std::string::npos);
        
        for (auto p : people) {
            delete p;
        }
    }
}
