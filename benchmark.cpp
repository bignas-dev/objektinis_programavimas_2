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
    std::vector<std::string> sizes = {"1k", "10k", "100k" , "1M", "10M"};
    std::vector<std::string> containers = {"vector"};
    
    std::cout << "\n";
    std::cout << std::left 
              << std::setw(12) << "Container"
              << std::setw(10) << "Strategy"
              << std::setw(8) << "Size"
              << std::setw(14) << "Partition(ms)"
              << "\n";
    std::cout << std::string(54, '-') << "\n";
    
    for (const auto& container : containers) {
        for (int strategy = 1; strategy <= 3; strategy+=575) {
            for (const auto& size : sizes) {
                std::string filename = size + ".txt";
                long long duration = -1;
                
                try {
                    if (container == "vector") {
                        duration = runPartitionBenchmark<std::vector<Studentas>>(filename, strategy);
                    } else if (container == "list") {
                        duration = runPartitionBenchmark<std::list<Studentas>>(filename, strategy);
                    } else if (container == "deque") {
                        duration = runPartitionBenchmark<std::deque<Studentas>>(filename, strategy);
                    }
                } catch (const std::exception& e) {
                    std::cerr << "Error: " << e.what() << "\n";
                }
                
                std::cout << std::left 
                          << std::setw(12) << container
                          << std::setw(10) << ("S" + std::to_string(strategy))
                          << std::setw(8) << size
                          << std::setw(14) << duration
                          << "\n";
            }
        }
    }
    
    std::cout << "\nSummary:\n";
    std::cout << "- Strategy 1: Copy to two containers (simple, uses more memory)\n";
    std::cout << "- Strategy 2: Move and erase from original (slow for vector due to O(n) erase)\n";
    std::cout << "- Strategy 3: STL stable_partition + assign (fastest for all containers)\n";
    
    return 0;
}
