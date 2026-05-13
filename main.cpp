#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include "student.h"

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    int input_mode;
    std::cout << "Pasirinkite įvesties būdą:\n"
              << "1 - Rankinis įvedimas\n"
              << "2 - Atsitiktinis generavimas\n"
              << "3 - Nuskaitymas iš failo\n"
              << "Jūsų pasirinkimas: ";
    std::cin >> input_mode;

    if (std::cin.fail() || input_mode < 1 || input_mode > 3) {
        std::cout << "Neteisinga įvestis: tinka '1', '2' arba '3'.\n";
        return 1;
    }

    std::vector<Mokinys> students;

    if (input_mode == 1) {
        while (true) {
            std::cout << "\nĮveskite " << students.size() + 1 << " studento duomenis:\n";
            Mokinys m;
            readStudentData(m);
            students.push_back(m);

            std::string ans;
            std::cout << "Ar norite įvesti dar vieną studentą? (t/n): ";
            std::cin >> ans;
            if (ans != "T" && ans != "t") {
                break;
            }
        }
    }
    else if (input_mode == 2) {
		std::cout << "\nĮveskite skaiciu kiek studentu sugeneruoti:\n";
		int mokSkaicius;
		std::cin >> mokSkaicius;
		for (int i = 0; i < mokSkaicius; i++) {
			Mokinys m;
			generateRandomData(m);
			students.push_back(m);
		}
		std::cout << "Sugeneruota " << mokSkaicius << " mokiniu ";
    }
    else { 
        std::string filename;
        std::cout << "Įveskite failo pavadinimą: ";
        std::cin >> filename;
        students = readFromFile(filename);
        if (students.empty()) {
            std::cerr << "Nepavyko nuskaityti jokių duomenų iš failo. Programa baigiama." << std::endl;
            return 1;
        }
        std::cout << "Iš failo nuskaityta " << students.size() << " studentų.\n";
    }

    std::string choice;
    std::cout << "\nPasirinkite galutinio balo skaičiavimo būdą:\n"
              << "1 - Vidurkis\n"
              << "2 - Mediana\n"
              << "Jūsų pasirinkimas: ";
    std::cin >> choice;

    if (choice != "1" && choice != "2") {
        std::cout << "Neteisinga įvestis: tinka '1' arba '2'.\n";
        return 1;
    }

    for (auto& m : students) {
        calculateFinalGrade(m, choice);
    }

    int sort_choice;
    std::cout << "\nPasirinkite rūšiavimo kriterijų:\n"
              << "1 - Pagal vardą\n"
              << "2 - Pagal pavardę\n"
              << "3 - Pagal galutinį balą\n"
              << "Jūsų pasirinkimas: ";
    std::cin >> sort_choice;

    if (std::cin.fail() || sort_choice < 1 || sort_choice > 3) {
        std::cout << "Neteisinga įvestis: tinka '1', '2' arba '3'.\n";
        return 1;
    }

    int output_option;
    std::cout << "\nPasirinkite kur pateikti rezultatai:\n"
              << "1 - i terminala\n"
              << "2 - i faila\n"
              << "Jūsų pasirinkimas: ";
    std::cin >> output_option;

    if (std::cin.fail() || output_option < 1 ||  output_option > 3) {
        std::cout << "Neteisinga įvestis: tinka '1' arba '2'\n";
        return 1;
    }

    if (sort_choice == 1) {
        std::sort(students.begin(), students.end());
    } else if (sort_choice == 2) {
        std::sort(students.begin(), students.end(), Mokinys::CompareByLastName());
    } else { 
        std::sort(students.begin(), students.end(), Mokinys::CompareByFinalGradeDesc());
    }

	if (output_option == 1) {
		displayResults(students, choice);
	} else {
		writeResultsToAFile(students, choice, "output.txt");
	}

    return 0;
}
