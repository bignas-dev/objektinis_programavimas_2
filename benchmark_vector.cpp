/**
 * @file benchmark_vector.cpp
 * @brief Vector vs std::vector efektyvumo palyginimas
 */

#include "Vector.h"
#include <vector>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <fstream>

using namespace std::chrono;

struct BenchmarkResult {
    std::string test_name;
    double std_vector_time;
    double vector_time;
    double speedup;
};

void print_header() {
    std::cout << "\n";
    std::cout << "╔══════════════════════════════════════════════════════════════════╗\n";
    std::cout << "║         Vector vs std::vector EFEKTYVUMO PALYGINIMAS             ║\n";
    std::cout << "╚══════════════════════════════════════════════════════════════════╝\n";
    std::cout << "\n";
}

void print_result(const BenchmarkResult& r) {
    std::cout << std::left << std::setw(25) << r.test_name
              << std::right << std::setw(12) << std::fixed << std::setprecision(4) << r.std_vector_time << " ms"
              << std::setw(12) << r.vector_time << " ms"
              << std::setw(10) << r.speedup << "x\n";
}

BenchmarkResult benchmark_push_back(size_t size, const std::string& name) {
    BenchmarkResult result;
    result.test_name = name;
    
    // std::vector benchmark
    auto start = high_resolution_clock::now();
    std::vector<int> v1;
    v1.reserve(size);
    for (size_t i = 0; i < size; ++i) {
        v1.push_back(i);
    }
    auto end = high_resolution_clock::now();
    result.std_vector_time = duration<double, std::milli>(end - start).count();
    
    // Vector benchmark
    start = high_resolution_clock::now();
    Vector<int> v2;
    v2.reserve(size);
    for (size_t i = 0; i < size; ++i) {
        v2.push_back(i);
    }
    end = high_resolution_clock::now();
    result.vector_time = duration<double, std::milli>(end - start).count();
    
    result.speedup = result.std_vector_time / result.vector_time;
    
    return result;
}

BenchmarkResult benchmark_push_back_no_reserve(size_t size, const std::string& name) {
    BenchmarkResult result;
    result.test_name = name;
    
    // std::vector benchmark (no reserve)
    auto start = high_resolution_clock::now();
    std::vector<int> v1;
    for (size_t i = 0; i < size; ++i) {
        v1.push_back(i);
    }
    auto end = high_resolution_clock::now();
    result.std_vector_time = duration<double, std::milli>(end - start).count();
    
    // Vector benchmark (no reserve)
    start = high_resolution_clock::now();
    Vector<int> v2;
    for (size_t i = 0; i < size; ++i) {
        v2.push_back(i);
    }
    end = high_resolution_clock::now();
    result.vector_time = duration<double, std::milli>(end - start).count();
    
    result.speedup = result.std_vector_time / result.vector_time;
    
    return result;
}

size_t count_reallocations_push_back(size_t size) {
    size_t reallocations = 0;
    size_t old_capacity = 0;
    
    Vector<int> v;
    for (size_t i = 0; i < size; ++i) {
        if (v.capacity() != old_capacity) {
            reallocations++;
            old_capacity = v.capacity();
        }
        v.push_back(i);
    }
    
    return reallocations;
}

int main() {
    print_header();
    
    std::vector<BenchmarkResult> results;
    
    std::cout << "=== PUSH_BACK (su reserve) ===\n\n";
    std::cout << std::left << std::setw(25) << "Testas"
              << std::right << std::setw(12) << "std::vector"
              << std::setw(12) << "Vector"
              << std::setw(10) << "Speedup\n";
    std::cout << std::string(59, '-') << "\n";
    
    // Benchmark with reserve
    results.push_back(benchmark_push_back(10000, "10K elements"));
    results.push_back(benchmark_push_back(100000, "100K elements"));
    results.push_back(benchmark_push_back(1000000, "1M elements"));
    results.push_back(benchmark_push_back(10000000, "10M elements"));
    
    for (const auto& r : results) {
        print_result(r);
    }
    
    std::cout << "\n=== PUSH_BACK (be reserve) ===\n\n";
    std::cout << std::left << std::setw(25) << "Testas"
              << std::right << std::setw(12) << "std::vector"
              << std::setw(12) << "Vector"
              << std::setw(10) << "Speedup\n";
    std::cout << std::string(59, '-') << "\n";
    
    std::vector<BenchmarkResult> results_no_reserve;
    results_no_reserve.push_back(benchmark_push_back_no_reserve(10000, "10K elements"));
    results_no_reserve.push_back(benchmark_push_back_no_reserve(100000, "100K elements"));
    results_no_reserve.push_back(benchmark_push_back_no_reserve(1000000, "1M elements"));
    
    for (const auto& r : results_no_reserve) {
        print_result(r);
    }
    
    // Memory reallocation counting
    std::cout << "\n=== ATMINTIES PERSKIRSTYMŲ SKAIČIUS ===\n\n";
    std::cout << std::left << std::setw(20) << "Elementų skaičius"
              << std::right << std::setw(20) << "Perskirstymai\n";
    std::cout << std::string(40, '-') << "\n";
    
    std::vector<size_t> sizes = {10000, 100000, 1000000, 10000000, 100000000};
    for (size_t size : sizes) {
        size_t reallocs = count_reallocations_push_back(size);
        std::cout << std::left << std::setw(20) << size
                  << std::right << std::setw(20) << reallocs << "\n";
    }
    
    // Save results to file
    std::ofstream out("benchmark_results.txt");
    out << "Vector vs std::vector Benchmark Results\n";
    out << "========================================\n\n";
    
    out << "PUSH_BACK (su reserve):\n";
    for (const auto& r : results) {
        out << r.test_name << ": std::vector=" << r.std_vector_time 
            << "ms, Vector=" << r.vector_time << "ms, speedup=" << r.speedup << "x\n";
    }
    
    out << "\nPUSH_BACK (be reserve):\n";
    for (const auto& r : results_no_reserve) {
        out << r.test_name << ": std::vector=" << r.std_vector_time 
            << "ms, Vector=" << r.vector_time << "ms, speedup=" << r.speedup << "x\n";
    }
    
    out << "\nMemory Reallocations:\n";
    for (size_t size : sizes) {
        out << size << " elements: " << count_reallocations_push_back(size) << " reallocations\n";
    }
    out.close();
    
    std::cout << "\nRezultatai išsaugoti į benchmark_results.txt\n";
    
    return 0;
}
