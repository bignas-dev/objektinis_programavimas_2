#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <list>
#include <deque>
#include <chrono>
#include <sstream>
#include <algorithm>
#include "student.h"


int main() {
    std::vector<std::string> sizes = {"1k", "10k", "100k", "1M", "10M" };
    
    std::cout << "\n";
    std::cout << std::left 
              << std::setw(14) << "Size"
              << std::setw(14) << "Time(ms)"
              << "\n";
    std::cout << std::string(54, '-') << "\n";
    
	for (const auto& size : sizes) {
		std::string filename = size + ".txt";
		long long duration = -1;
		duration = runPartitionBenchmark<std::vector<Studentas>>(filename, 1);
		
		std::cout << std::left 
				  << std::setw(8) << size
				  << std::setw(14) << duration
				  << "\n";
    }
    
    return 0;
}
