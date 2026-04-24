@echo off
REM Windows build script for Objektinis Programavimas v3.0

echo === Objektinis Programavimas v3.0 Build Script ===
echo.

REM Check if g++ is available
where g++ >nul 2>nul
if %ERRORLEVEL% neq 0 (
    echo ERROR: g++ not found. Please install MinGW or WSL.
    exit /b 1
)

echo [1/5] Compiling Vector tests...
g++ -O3 -std=c++17 -Wall -Itests -o tests/test_vector.exe tests/test_vector.cpp
if %ERRORLEVEL% neq 0 exit /b 1

echo [2/5] Compiling compatibility tests...
g++ -O3 -std=c++17 -Wall -Itests -o tests/test_vector_std.exe tests/test_vector_std.cpp
if %ERRORLEVEL% neq 0 exit /b 1

echo [3/5] Compiling iterator tests...
g++ -O3 -std=c++17 -Wall -Itests -o tests/test_vector_iterators.exe tests/test_vector_iterators.cpp
if %ERRORLEVEL% neq 0 exit /b 1

echo [4/5] Compiling main program...
g++ -O3 -std=c++17 -Wall -o main_vector.exe main_vector.cpp
if %ERRORLEVEL% neq 0 exit /b 1

echo [5/5] Compiling benchmark...
g++ -O3 -std=c++17 -Wall -o benchmark_vector.exe benchmark_vector.cpp
if %ERRORLEVEL% neq 0 exit /b 1

echo.
echo === Build Complete ===
echo.
echo Run tests: tests/test_vector.exe
echo Run program: main_vector.exe
echo Run benchmark: benchmark_vector.exe
echo.
