# Quick Start Guide - Objektinis Programavimas v3.0

## 1. Diegimas

### Linux

```bash
# Clone repository
git clone <repo-url>
cd objektinis_programavimas_2
git checkout v3.0

# Build
make

# Run tests
make run_tests

# Run program
make run_vector
```

### Windows

```cmd
# Reikalingas MinGW arba WSL

# Naudojant build.bat
build.bat

# Arba naudojant WSL
wsl
make
```

## 2. Testavimas

```bash
# Visi testai
make run_tests

# Tik Vector testai
./tests/test_vector

# Compatibility testai
./tests/test_vector_std

# Iterator testai
./tests/test_vector_iterators
```

## 3. Efektyvumo Testai

```bash
# Vector vs std::vector
make benchmark_vector
./benchmark_vector

# Studentų programa su Vector
make main_vector
./main_vector
```

## 4. Dokumentacija

```bash
# Generuoti Doxygen dokumentaciją
make doxygen

# Atidaryti HTML
xdg-open docs/html/index.html  # Linux
open docs/html/index.html      # macOS

# PDF generavimui
cd docs/latex
make  # Reikalingas TeXLive
```

## 5. Windows Installer

```bash
# Reikalingas Inno Setup
# Atidaryti setup.iss Inno Setup Compiler
# Build -> Compile
# Sukuria installer/setup.exe
```

## 6. Rezultatų Peržiūra

```bash
# Benchmark rezultatai
cat benchmark_results.txt

# Programos rezultatai
cat rezultatai_vector.txt
```

## 7. Dažniausios Klaidos

### "g++: command not found"
```bash
# Ubuntu/Debian
sudo apt install g++

# NixOS
nix-env -iA nixos.gcc
```

### "make: command not found"
```bash
# Ubuntu/Debian
sudo apt install make

# NixOS
nix-env -iA nixos.gnumake
```

## 8. Papildoma Informacija

- [VECTOR_DOCS.md](VECTOR_DOCS.md) - Pilna Vector dokumentacija
- [README.md](README.md) - Pagrindinė dokumentacija
- [docs/html/](docs/html/) - Doxygen HTML dokumentacija
