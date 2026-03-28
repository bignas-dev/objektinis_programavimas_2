#ifndef BENCHMARK_H
#define BENCHMARK_H

#include "student.h"
#include <string>
#include <vector>

struct GenerationResult {
    int count;
    double duration;
    
    GenerationResult() : count(0), duration(0.0) {}
};

struct BenchmarkResult {
    std::string containerType;
    int strategy;
    int recordCount;
    double readDuration;
    double sortDuration;
    double splitDuration;
    double writeDuration;
    double totalDuration;
    
    BenchmarkResult() : strategy(0), recordCount(0), readDuration(0), sortDuration(0), 
                        splitDuration(0), writeDuration(0), totalDuration(0) {}
    
    void reset() {
        readDuration = 0;
        sortDuration = 0;
        splitDuration = 0;
        writeDuration = 0;
        totalDuration = 0;
    }
};

GenerationResult measureFileGeneration(const std::string& filename, int recordCount);

BenchmarkResult runBenchmarkVector(const std::string& filename, int strategy, const std::string& gradeType);
BenchmarkResult runBenchmarkList(const std::string& filename, int strategy, const std::string& gradeType);
BenchmarkResult runBenchmarkDeque(const std::string& filename, int strategy, const std::string& gradeType);

void writeResultsToCSV(const std::string& filename, const std::vector<BenchmarkResult>& results);
void printResultsTable(const std::vector<BenchmarkResult>& results);
void printContainerComparison(const std::vector<BenchmarkResult>& results);

#endif
