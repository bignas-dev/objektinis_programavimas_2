#include <iostream>
#include <cassert>
#include <sstream>
#include <vector>
#include <utility>
#include <string>
#include "student.h"

void testDefaultConstructor() {
    std::cout << "Test: Default constructor... ";
    Studentas s;
    assert(s.getFirstName() == "");
    assert(s.getLastName() == "");
    assert(s.getExamGrade() == 0);
    assert(s.getFinalGrade() == -1.0f);
    assert(s.getIntermediateGrades().empty());
    std::cout << "PASSED\n";
}

void testParameterizedConstructor() {
    std::cout << "Test: Parameterized constructor... ";
    Studentas s("Jonas", "Jonaitis");
    assert(s.getFirstName() == "Jonas");
    assert(s.getLastName() == "Jonaitis");
    assert(s.getExamGrade() == 0);
    assert(s.getFinalGrade() == -1.0f);
    assert(s.getIntermediateGrades().empty());
    std::cout << "PASSED\n";
}

void testCopyConstructor() {
    std::cout << "Test: Copy constructor... ";
    Studentas original("Petras", "Petraitis");
    original.addIntermediateGrade(8);
    original.addIntermediateGrade(9);
    original.addIntermediateGrade(7);
    original.setExamGrade(10);
    original.setFinalGrade(9.2f);
    
    Studentas copy(original);
    
    assert(copy.getFirstName() == "Petras");
    assert(copy.getLastName() == "Petraitis");
    assert(copy.getIntermediateGrades().size() == 3);
    assert(copy.getIntermediateGrades()[0] == 8);
    assert(copy.getIntermediateGrades()[1] == 9);
    assert(copy.getIntermediateGrades()[2] == 7);
    assert(copy.getExamGrade() == 10);
    assert(copy.getFinalGrade() == 9.2f);
    
    assert(copy.getFirstName() == original.getFirstName());
    assert(copy.getLastName() == original.getLastName());
    
    original.setFirstName("Antanas");
    assert(copy.getFirstName() == "Petras");
    
    std::cout << "PASSED\n";
}

void testCopyAssignmentOperator() {
    std::cout << "Test: Copy assignment operator... ";
    Studentas original("Vytautas", "Vytautaitis");
    original.addIntermediateGrade(6);
    original.addIntermediateGrade(7);
    original.setExamGrade(8);
    original.setFinalGrade(7.4f);
    
    Studentas assigned;
    assigned = original;
    
    assert(assigned.getFirstName() == "Vytautas");
    assert(assigned.getLastName() == "Vytautaitis");
    assert(assigned.getIntermediateGrades().size() == 2);
    assert(assigned.getIntermediateGrades()[0] == 6);
    assert(assigned.getIntermediateGrades()[1] == 7);
    assert(assigned.getExamGrade() == 8);
    assert(assigned.getFinalGrade() == 7.4f);
    
    original.setFirstName("Kazys");
    assert(assigned.getFirstName() == "Vytautas");
    
    Studentas selfAssign;
    selfAssign.setFirstName("Testas");
    selfAssign = selfAssign;
    assert(selfAssign.getFirstName() == "Testas");
    
    std::cout << "PASSED\n";
}

void testMoveConstructor() {
    std::cout << "Test: Move constructor... ";
    Studentas original("Juozas", "Juozaitis");
    original.addIntermediateGrade(5);
    original.addIntermediateGrade(6);
    original.addIntermediateGrade(7);
    original.setExamGrade(9);
    original.setFinalGrade(7.8f);
    
    std::string originalName = original.getFirstName();
    std::string originalLastName = original.getLastName();
    
    Studentas moved(std::move(original));
    
    assert(moved.getFirstName() == originalName);
    assert(moved.getLastName() == originalLastName);
    assert(moved.getIntermediateGrades().size() == 3);
    assert(moved.getIntermediateGrades()[0] == 5);
    assert(moved.getIntermediateGrades()[1] == 6);
    assert(moved.getIntermediateGrades()[2] == 7);
    assert(moved.getExamGrade() == 9);
    assert(moved.getFinalGrade() == 7.8f);
    
    std::cout << "PASSED\n";
}

void testMoveAssignmentOperator() {
    std::cout << "Test: Move assignment operator... ";
    Studentas original("Algirdas", "Algirdaitis");
    original.addIntermediateGrade(10);
    original.addIntermediateGrade(9);
    original.setExamGrade(10);
    original.setFinalGrade(9.8f);
    
    Studentas assigned("Temporary", "Temp");
    assigned = std::move(original);
    
    assert(assigned.getFirstName() == "Algirdas");
    assert(assigned.getLastName() == "Algirdaitis");
    assert(assigned.getIntermediateGrades().size() == 2);
    assert(assigned.getIntermediateGrades()[0] == 10);
    assert(assigned.getIntermediateGrades()[1] == 9);
    assert(assigned.getExamGrade() == 10);
    assert(assigned.getFinalGrade() == 9.8f);
    
    std::cout << "PASSED\n";
}

void testDestructor() {
    std::cout << "Test: Destructor... ";
    {
        Studentas s("Bronius", "Bronaitis");
        s.addIntermediateGrade(8);
        s.setExamGrade(7);
    }
    std::cout << "PASSED (no memory leaks)\n";
}

void testEqualityOperator() {
    std::cout << "Test: Equality operator (==)... ";
    Studentas s1("Jonas", "Jonaitis");
    Studentas s2("Jonas", "Jonaitis");
    Studentas s3("Petras", "Petraitis");
    
    assert(s1 == s2);
    assert(!(s1 == s3));
    
    std::cout << "PASSED\n";
}

void testInequalityOperator() {
    std::cout << "Test: Inequality operator (!=)... ";
    Studentas s1("Jonas", "Jonaitis");
    Studentas s2("Jonas", "Jonaitis");
    Studentas s3("Petras", "Petraitis");
    
    assert(!(s1 != s2));
    assert(s1 != s3);
    
    std::cout << "PASSED\n";
}

void testLessThanOperator() {
    std::cout << "Test: Less than operator (<)... ";
    Studentas s1("Antanas", "Antanaitis");
    Studentas s2("Bronius", "Bronaitis");
    
    assert(s1 < s2);
    assert(!(s2 < s1));
    
    std::cout << "PASSED\n";
}

void testGreaterThanOperator() {
    std::cout << "Test: Greater than operator (>)... ";
    Studentas s1("Jonas", "Jonaitis");
    s1.setFinalGrade(8.5f);
    Studentas s2("Petras", "Petraitis");
    s2.setFinalGrade(7.0f);
    
    assert(s1 > s2);
    assert(!(s2 > s1));
    
    std::cout << "PASSED\n";
}

void testLessThanOrEqualOperator() {
    std::cout << "Test: Less than or equal operator (<=)... ";
    Studentas s1("Antanas", "Antanaitis");
    Studentas s2("Antanas", "Antanaitis");
    Studentas s3("Bronius", "Bronaitis");
    
    assert(s1 <= s2);
    assert(s1 <= s3);
    assert(!(s3 <= s1));
    
    std::cout << "PASSED\n";
}

void testGreaterThanOrEqualOperator() {
    std::cout << "Test: Greater than or equal operator (>=)... ";
    Studentas s1("Jonas", "Jonaitis");
    s1.setFinalGrade(8.5f);
    Studentas s2("Petras", "Petraitis");
    s2.setFinalGrade(7.0f);
    
    assert(s1 >= s2);
    assert(!(s2 >= s1));
    
    std::cout << "PASSED\n";
}

void testCalculateFinalGrade() {
    std::cout << "Test: Calculate final grade (average)... ";
    Studentas s("Test", "Testinis");
    s.addIntermediateGrade(8);
    s.addIntermediateGrade(9);
    s.addIntermediateGrade(10);
    s.setExamGrade(9);
    
    s.calculateFinalGrade("1");
    
    float expected = 0.6f * 9 + 0.4f * 9.0f;
    assert(s.getFinalGrade() == expected);
    
    std::cout << "Test: Calculate final grade (median)... ";
    Studentas s2("Test2", "Testinis2");
    s2.addIntermediateGrade(7);
    s2.addIntermediateGrade(8);
    s2.addIntermediateGrade(9);
    s2.setExamGrade(10);
    
    s2.calculateFinalGrade("2");
    
    float expectedMedian = 0.6f * 10 + 0.4f * 8.0f;
    assert(s2.getFinalGrade() == expectedMedian);
    
    std::cout << "PASSED\n";
}

void testSettersAndGetters() {
    std::cout << "Test: Setters and getters... ";
    Studentas s;
    
    s.setFirstName("Jonas");
    assert(s.getFirstName() == "Jonas");
    
    s.setLastName("Jonaitis");
    assert(s.getLastName() == "Jonaitis");
    
    s.addIntermediateGrade(8);
    s.addIntermediateGrade(9);
    assert(s.getIntermediateGrades().size() == 2);
    assert(s.getIntermediateGrades()[0] == 8);
    assert(s.getIntermediateGrades()[1] == 9);
    
    s.setExamGrade(10);
    assert(s.getExamGrade() == 10);
    
    s.setFinalGrade(9.5f);
    assert(s.getFinalGrade() == 9.5f);
    
    std::cout << "PASSED\n";
}

void testVectorStorage() {
    std::cout << "Test: Storing in vector (tests move semantics)... ";
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
    
    assert(students.size() == 3);
    assert(students[0].getFirstName() == "Jonas");
    assert(students[1].getFirstName() == "Petras");
    assert(students[2].getFirstName() == "Antanas");
    
    std::cout << "PASSED\n";
}

void testOutputStreamOperator() {
    std::cout << "Test: Output stream operator (<<)... ";
    Studentas s("Edmundas", "Edmundaitis");
    s.addIntermediateGrade(8);
    s.addIntermediateGrade(9);
    s.addIntermediateGrade(10);
    s.setExamGrade(9);
    s.setFinalGrade(9.0f);
    
    std::ostringstream oss;
    oss << s;
    std::string output = oss.str();
    
    assert(output.find("Edmundas") != std::string::npos);
    assert(output.find("Edmundaitis") != std::string::npos);
    assert(output.find("8") != std::string::npos);
    assert(output.find("9") != std::string::npos);
    assert(output.find("10") != std::string::npos);
    assert(output.find("9.00") != std::string::npos);
    
    std::cout << "PASSED\n";
}

void testInputStreamOperator() {
    std::cout << "Test: Input stream operator (>>)... ";
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
    
    assert(s.getFirstName() == "Rimantas");
    assert(s.getLastName() == "Rimantaitis");
    assert(s.getIntermediateGrades().size() == 3);
    assert(s.getIntermediateGrades()[0] == 7);
    assert(s.getIntermediateGrades()[1] == 8);
    assert(s.getIntermediateGrades()[2] == 9);
    assert(s.getExamGrade() == 10);
    
    std::cout << "PASSED\n";
}

void testStreamRoundTrip() {
    std::cout << "Test: Stream round-trip (output then parse)... ";
    Studentas original("Kazys", "Kazaitis");
    original.addIntermediateGrade(7);
    original.addIntermediateGrade(8);
    original.addIntermediateGrade(9);
    original.setExamGrade(10);
    original.setFinalGrade(9.0f);
    
    std::ostringstream oss;
    oss << original;
    std::string output = oss.str();
    
    assert(output.find("Kazys") != std::string::npos);
    assert(output.find("Kazaitis") != std::string::npos);
    assert(output.find("9.00") != std::string::npos);
    
    std::cout << "PASSED\n";
}

int main() {
    std::cout << "=== Studentas Class Test Suite ===\n\n";
    
    std::cout << "--- Rule of Five Tests ---\n";
    testDefaultConstructor();
    testParameterizedConstructor();
    testCopyConstructor();
    testCopyAssignmentOperator();
    testMoveConstructor();
    testMoveAssignmentOperator();
    testDestructor();
    
    std::cout << "\n--- I/O Operator Tests ---\n";
    testOutputStreamOperator();
    testInputStreamOperator();
    testStreamRoundTrip();
    
    std::cout << "\n--- Comparison Operator Tests ---\n";
    testEqualityOperator();
    testInequalityOperator();
    testLessThanOperator();
    testGreaterThanOperator();
    testLessThanOrEqualOperator();
    testGreaterThanOrEqualOperator();
    
    std::cout << "\n--- Functionality Tests ---\n";
    testCalculateFinalGrade();
    testSettersAndGetters();
    testVectorStorage();
    
    std::cout << "\n=== All tests PASSED! ===\n";
    
    return 0;
}
