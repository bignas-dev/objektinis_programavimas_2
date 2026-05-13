#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <iomanip>
#include <fstream>
#include <random>
#include <stdexcept>
#include <chrono>
#include <sstream>
#include <algorithm>
#include "student.h"


int main(int argc, char* argv[]) {
    std::vector<int> sizes = {1000, 10000, 100000, 1000000, 10000000};
    std::vector<std::string> size_names = {"1k", "10k", "100k", "1M", "10M"};
    std::vector<std::string> containers = {"vector", "list", "deque"};

    std::cout << "Pradedami spartos tyrimai...\n";

	for (size_t i = 0; i < sizes.size(); ++i) {
		std::cout << "\n" << size_names[i] << ":\n";
		runGenerationTestT<std::vector<Studentas>>(size_names[i] + ".txt", sizes[i]);
	}
	for (const auto& container : containers) {
		std::cout << "\n" << container << ":\n";
		for (size_t i = 0; i < sizes.size(); ++i) {
			std::string filename = size_names[i] + ".txt";
			if (container == "vector") {
				runProcessingTest(filename);
			} else if (container == "list") {
				runProcessingTest(filename);
			} else if (container == "deque") {
				runProcessingTest(filename);
			}
		}
	}
    std::cout << "\nTyrimai baigti.\n";
    return 0;
}
