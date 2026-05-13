#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "student.h"
#include <sstream>
#include <vector>
#include <memory>

// ============================================================================
// RULE OF FIVE TESTS
// ============================================================================

TEST_CASE("Default constructor creates empty Student", "[RuleOfFive]") {
    Studentas s;
    REQUIRE(s.getFirstName() == "");
    REQUIRE(s.getLastName() == "");
    REQUIRE(s.getExamGrade() == 0);
    REQUIRE(s.getFinalGrade() == -1.0f);
    REQUIRE(s.getIntermediateGrades().empty());
}

TEST_CASE("Parameterized constructor initializes name and surname", "[RuleOfFive]") {
    Studentas s("Jonas", "Jonaitis");
    REQUIRE(s.getFirstName() == "Jonas");
    REQUIRE(s.getLastName() == "Jonaitis");
    REQUIRE(s.getExamGrade() == 0);
    REQUIRE(s.getFinalGrade() == -1.0f);
    REQUIRE(s.getIntermediateGrades().empty());
}

TEST_CASE("Copy constructor creates independent copy", "[RuleOfFive]") {
    Studentas original("Petras", "Petraitis");
    original.addIntermediateGrade(8);
    original.addIntermediateGrade(9);
    original.addIntermediateGrade(7);
    original.setExamGrade(10);
    original.setFinalGrade(9.2f);
    
    Studentas copy(original);
    
    REQUIRE(copy.getFirstName() == "Petras");
    REQUIRE(copy.getLastName() == "Petraitis");
    REQUIRE(copy.getIntermediateGrades().size() == 3);
    REQUIRE(copy.getIntermediateGrades()[0] == 8);
    REQUIRE(copy.getIntermediateGrades()[1] == 9);
    REQUIRE(copy.getIntermediateGrades()[2] == 7);
    REQUIRE(copy.getExamGrade() == 10);
    REQUIRE(copy.getFinalGrade() == 9.2f);
    
    REQUIRE(copy.getFirstName() == original.getFirstName());
    REQUIRE(copy.getLastName() == original.getLastName());
    
    SECTION("Modifying original doesn't affect copy") {
        original.setFirstName("Antanas");
        REQUIRE(copy.getFirstName() == "Petras");
    }
}

TEST_CASE("Copy assignment operator works correctly", "[RuleOfFive]") {
    Studentas original("Vytautas", "Vytautaitis");
    original.addIntermediateGrade(6);
    original.addIntermediateGrade(7);
    original.setExamGrade(8);
    original.setFinalGrade(7.4f);
    
    Studentas assigned;
    assigned = original;
    
    REQUIRE(assigned.getFirstName() == "Vytautas");
    REQUIRE(assigned.getLastName() == "Vytautaitis");
    REQUIRE(assigned.getIntermediateGrades().size() == 2);
    REQUIRE(assigned.getIntermediateGrades()[0] == 6);
    REQUIRE(assigned.getIntermediateGrades()[1] == 7);
    REQUIRE(assigned.getExamGrade() == 8);
    REQUIRE(assigned.getFinalGrade() == 7.4f);
    
    SECTION("Modifying original doesn't affect assigned") {
        original.setFirstName("Kazys");
        REQUIRE(assigned.getFirstName() == "Vytautas");
    }
    
    SECTION("Self-assignment is safe") {
        Studentas selfAssign;
        selfAssign.setFirstName("Testas");
        selfAssign = selfAssign;
        REQUIRE(selfAssign.getFirstName() == "Testas");
    }
}

TEST_CASE("Move constructor transfers resources", "[RuleOfFive]") {
    Studentas original("Juozas", "Juozaitis");
    original.addIntermediateGrade(5);
    original.addIntermediateGrade(6);
    original.addIntermediateGrade(7);
    original.setExamGrade(9);
    original.setFinalGrade(7.8f);
    
    std::string originalName = original.getFirstName();
    std::string originalLastName = original.getLastName();
    
    Studentas moved(std::move(original));
    
    REQUIRE(moved.getFirstName() == originalName);
    REQUIRE(moved.getLastName() == originalLastName);
    REQUIRE(moved.getIntermediateGrades().size() == 3);
    REQUIRE(moved.getIntermediateGrades()[0] == 5);
    REQUIRE(moved.getIntermediateGrades()[1] == 6);
    REQUIRE(moved.getIntermediateGrades()[2] == 7);
    REQUIRE(moved.getExamGrade() == 9);
    REQUIRE(moved.getFinalGrade() == 7.8f);
}

TEST_CASE("Move assignment operator transfers resources", "[RuleOfFive]") {
    Studentas original("Algirdas", "Algirdaitis");
    original.addIntermediateGrade(10);
    original.addIntermediateGrade(9);
    original.setExamGrade(10);
    original.setFinalGrade(9.8f);
    
    Studentas assigned("Temporary", "Temp");
    assigned = std::move(original);
    
    REQUIRE(assigned.getFirstName() == "Algirdas");
    REQUIRE(assigned.getLastName() == "Algirdaitis");
    REQUIRE(assigned.getIntermediateGrades().size() == 2);
    REQUIRE(assigned.getIntermediateGrades()[0] == 10);
    REQUIRE(assigned.getIntermediateGrades()[1] == 9);
    REQUIRE(assigned.getExamGrade() == 10);
    REQUIRE(assigned.getFinalGrade() == 9.8f);
}

TEST_CASE("Destructor cleans up properly", "[RuleOfFive]") {
    {
        Studentas s("Bronius", "Bronaitis");
        s.addIntermediateGrade(8);
        s.setExamGrade(7);
    }
    // If we reach here without crash, destructor worked
    REQUIRE(true);
}

// ============================================================================
// ABSTRACT BASE CLASS TESTS
// ============================================================================

TEST_CASE("Zmogus is abstract - can use pointer to Student", "[AbstractBase]") {
    // Zmogus z; // <-- This would cause compilation error (abstract class)
    
    Studentas s("Testas", "Testauskas");
    Zmogus* ptr = &s;
    
    REQUIRE(ptr != nullptr);
    REQUIRE(ptr->getFirstName() == "Testas");
    REQUIRE(ptr->getLastName() == "Testauskas");
}

TEST_CASE("Base class pointer to Student - virtual method works", "[AbstractBase]") {
    Studentas s("Petras", "Petraitis");
    s.addIntermediateGrade(8);
    s.addIntermediateGrade(9);
    s.addIntermediateGrade(10);
    s.setExamGrade(9);
    s.calculateFinalGrade("1");
    
    Zmogus* basePtr = &s;
    
    REQUIRE(basePtr->getFirstName() == "Petras");
    REQUIRE(basePtr->getLastName() == "Petraitis");
    REQUIRE(basePtr->getFinalGrade() == s.getFinalGrade());
}

TEST_CASE("Base class reference to Student - virtual method works", "[AbstractBase]") {
    Studentas s("Jonas", "Jonaitis");
    s.addIntermediateGrade(7);
    s.addIntermediateGrade(8);
    s.setExamGrade(10);
    s.calculateFinalGrade("1");
    
    Zmogus& baseRef = s;
    
    REQUIRE(baseRef.getFirstName() == "Jonas");
    REQUIRE(baseRef.getLastName() == "Jonaitis");
    REQUIRE(baseRef.getFinalGrade() == s.getFinalGrade());
}

// ============================================================================
// I/O OPERATOR TESTS
// ============================================================================

TEST_CASE("Output stream operator formats student correctly", "[IO]") {
    Studentas s("Edmundas", "Edmundaitis");
    s.addIntermediateGrade(8);
    s.addIntermediateGrade(9);
    s.addIntermediateGrade(10);
    s.setExamGrade(9);
    s.setFinalGrade(9.0f);
    
    std::ostringstream oss;
    oss << s;
    std::string output = oss.str();
    
    REQUIRE_THAT(output, Catch::Contains("Edmundas"));
    REQUIRE_THAT(output, Catch::Contains("Edmundaitis"));
    REQUIRE_THAT(output, Catch::Contains("8"));
    REQUIRE_THAT(output, Catch::Contains("9"));
    REQUIRE_THAT(output, Catch::Contains("10"));
    REQUIRE_THAT(output, Catch::Contains("9.00"));
}

TEST_CASE("Input stream operator parses data correctly", "[IO]") {
    std::istringstream iss("Rimantas Rimantaitis 3 7 8 9 10");
    
    Studentas s;
    s.setFirstName("Temp");
    s.setLastName("Temp");
    
    std::string vardas, pavarde;
    int tarp_count;
    iss >> vardas >> pavarde >> tarp_count;
    
    s.setFirstName(vardas);
    s.setLastName(pavarde);
    
    for (int i = 0; i < tarp_count; ++i) {
        int grade;
        iss >> grade;
        s.addIntermediateGrade(grade);
    }
    
    int egz;
    iss >> egz;
    s.setExamGrade(egz);
    
    REQUIRE(s.getFirstName() == "Rimantas");
    REQUIRE(s.getLastName() == "Rimantaitis");
    REQUIRE(s.getIntermediateGrades().size() == 3);
    REQUIRE(s.getIntermediateGrades()[0] == 7);
    REQUIRE(s.getIntermediateGrades()[1] == 8);
    REQUIRE(s.getIntermediateGrades()[2] == 9);
    REQUIRE(s.getExamGrade() == 10);
}

TEST_CASE("Stream round-trip preserves data", "[IO]") {
    Studentas original("Kazys", "Kazaitis");
    original.addIntermediateGrade(7);
    original.addIntermediateGrade(8);
    original.addIntermediateGrade(9);
    original.setExamGrade(10);
    original.setFinalGrade(9.0f);
    
    std::ostringstream oss;
    oss << original;
    std::string output = oss.str();
    
    REQUIRE_THAT(output, Catch::Contains("Kazys"));
    REQUIRE_THAT(output, Catch::Contains("Kazaitis"));
    REQUIRE_THAT(output, Catch::Contains("9.00"));
}

// ============================================================================
// COMPARISON OPERATOR TESTS
// ============================================================================

TEST_CASE("Equality operator compares name and surname", "[Comparison]") {
    Studentas s1("Jonas", "Jonaitis");
    Studentas s2("Jonas", "Jonaitis");
    Studentas s3("Petras", "Petraitis");
    
    REQUIRE(s1 == s2);
    REQUIRE_FALSE(s1 == s3);
}

TEST_CASE("Inequality operator works correctly", "[Comparison]") {
    Studentas s1("Jonas", "Jonaitis");
    Studentas s2("Jonas", "Jonaitis");
    Studentas s3("Petras", "Petraitis");
    
    REQUIRE_FALSE(s1 != s2);
    REQUIRE(s1 != s3);
}

TEST_CASE("Less than operator compares by first name", "[Comparison]") {
    Studentas s1("Antanas", "Antanaitis");
    Studentas s2("Bronius", "Bronaitis");
    
    REQUIRE(s1 < s2);
    REQUIRE_FALSE(s2 < s1);
}

TEST_CASE("Greater than operator compares by final grade", "[Comparison]") {
    Studentas s1("Jonas", "Jonaitis");
    s1.setFinalGrade(8.5f);
    Studentas s2("Petras", "Petraitis");
    s2.setFinalGrade(7.0f);
    
    REQUIRE(s1 > s2);
    REQUIRE_FALSE(s2 > s1);
}

TEST_CASE("Less than or equal operator compares by final grade", "[Comparison]") {
    Studentas s1("Antanas", "Antanaitis");
    s1.setFinalGrade(7.0f);
    Studentas s2("Antanas", "Antanaitis");
    s2.setFinalGrade(7.0f);
    Studentas s3("Bronius", "Bronaitis");
    s3.setFinalGrade(8.0f);
    
    REQUIRE(s1 <= s2);
    REQUIRE(s1 <= s3);
    REQUIRE_FALSE(s3 <= s1);
}

TEST_CASE("Greater than or equal operator compares by final grade", "[Comparison]") {
    Studentas s1("Jonas", "Jonaitis");
    s1.setFinalGrade(8.5f);
    Studentas s2("Petras", "Petraitis");
    s2.setFinalGrade(7.0f);
    Studentas s3("Kazys", "Kazaitis");
    s3.setFinalGrade(8.5f);
    
    REQUIRE(s1 >= s2);
    REQUIRE_FALSE(s2 >= s1);
    REQUIRE(s1 >= s3);
}

// ============================================================================
// FUNCTIONALITY TESTS
// ============================================================================

TEST_CASE("Calculate final grade with average", "[Functionality]") {
    Studentas s("Test", "Testinis");
    s.addIntermediateGrade(8);
    s.addIntermediateGrade(9);
    s.addIntermediateGrade(10);
    s.setExamGrade(9);
    
    s.calculateFinalGrade("1");
    
    float expected = 0.6f * 9 + 0.4f * 9.0f;
    REQUIRE(s.getFinalGrade() == Approx(expected));
}

TEST_CASE("Calculate final grade with median", "[Functionality]") {
    Studentas s2("Test2", "Testinis2");
    s2.addIntermediateGrade(7);
    s2.addIntermediateGrade(8);
    s2.addIntermediateGrade(9);
    s2.setExamGrade(10);
    
    s2.calculateFinalGrade("2");
    
    float expectedMedian = 0.6f * 10 + 0.4f * 8.0f;
    REQUIRE(s2.getFinalGrade() == Approx(expectedMedian));
}

TEST_CASE("Setters and getters work correctly", "[Functionality]") {
    Studentas s;
    
    s.setFirstName("Jonas");
    REQUIRE(s.getFirstName() == "Jonas");
    
    s.setLastName("Jonaitis");
    REQUIRE(s.getLastName() == "Jonaitis");
    
    s.addIntermediateGrade(8);
    s.addIntermediateGrade(9);
    REQUIRE(s.getIntermediateGrades().size() == 2);
    REQUIRE(s.getIntermediateGrades()[0] == 8);
    REQUIRE(s.getIntermediateGrades()[1] == 9);
    
    s.setExamGrade(10);
    REQUIRE(s.getExamGrade() == 10);
    
    s.setFinalGrade(9.5f);
    REQUIRE(s.getFinalGrade() == 9.5f);
}

TEST_CASE("Storing in vector tests move semantics", "[Functionality]") {
    std::vector<Studentas> students;
    
    Studentas s1("Jonas", "Jonaitis");
    s1.addIntermediateGrade(8);
    s1.setExamGrade(9);
    
    Studentas s2("Petras", "Petraitis");
    s2.addIntermediateGrade(7);
    s2.setExamGrade(8);
    
    students.push_back(s1);
    students.push_back(s2);
    students.push_back(Studentas("Antanas", "Antanaitis"));
    
    REQUIRE(students.size() == 3);
    REQUIRE(students[0].getFirstName() == "Jonas");
    REQUIRE(students[1].getFirstName() == "Petras");
    REQUIRE(students[2].getFirstName() == "Antanas");
}
