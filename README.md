# Objektinis Programavimas v3.0

Studentų duomenų apdorojimo sistema su **Vector** konteineriu, unit testais ir Doxygen dokumentacija.

## V3.0 Naujovės

- **Vector konteineris** - pilnas std::vector analogas (30+ funkcijų)
- **Efektyvumo analizė** - Vector vs std::vector palyginimas
- **Unit Testai** - 80+ assertions Vector konteineriui
- **Integracija** - Studentų programa su Vector vietoje std::vector
- **Doxygen dokumentacija** - pilnas Vector API aprašymas

### Vector Efektyvumas

| Testas | std::vector | Vector | Speedup |
|--------|-------------|--------|---------|
| 10K elements | 0.0189 ms | 0.0171 ms | 1.11x |
| 100K elements | 0.2369 ms | 0.1920 ms | 1.23x |
| 1M elements | 2.3343 ms | 1.9234 ms | 1.21x |
| 10M elements | 23.8322 ms | 20.2992 ms | 1.17x |

**Vidutinis speedup:** ~1.2x greitesnis už std::vector

### Atminties Perskirstymai

| Elementai | Perskirstymai |
|-----------|---------------|
| 10K | 15 |
| 100K | 18 |
| 1M | 21 |
| 10M | 25 |
| 100M | 28 |

## V2.0 Naujovės

- **Unit Testai** su Catch2 framework (81 testas, 100% sėkmė)
- **Doxygen dokumentacija** (HTML + LaTeX)
- **Abstrakti bazinė klasė** Žmogus
- **Išvestinė klasė** Studentas
- **Rule of Five** implementacija
- **Polimorfizmo** demonstracija

## Reikalavimai

- g++ (C++17)
- Make
- Doxygen (dokumentacijai)
- Catch2 (unit testams) - atsisiunčiamas automatiškai

## Diegimas

```bash
# Pagrindinė programa
make

# Unit testai (v2.0 + v3.0)
make tests

# Vector benchmark
make benchmark_vector
make run_benchmark

# Studentų programa su Vector
make main_vector
make run_vector

# Doxygen dokumentacija
make doxygen
```

## Paleidimas

```bash
# Programa
make run

# Unit testai
make run_tests

# Atidaryti dokumentaciją
xdg-open docs/html/index.html  # Linux
open docs/html/index.html      # macOS
```

## Vector API

### Pagrindinės funkcijos

| Kategorija | Funkcijos |
|------------|-----------|
| **Constructors** | default, fill, copy, move, initializer_list |
| **Capacity** | size, capacity, empty, reserve, shrink_to_fit |
| **Access** | operator[], at, front, back, data |
| **Modifiers** | push_back, pop_back, clear, insert, erase |
| **Iterators** | begin, end |
| **Operators** | =, ==, !=, [] |

### Naudojimo pavyzdys

```cpp
#include "Vector.h"

Vector<int> v;              // default constructor
Vector<int> v2(5, 42);      // fill constructor
Vector<int> v3{1, 2, 3};    // initializer list

v.push_back(10);            // add element
v.pop_back();               // remove last
v.size();                   // get size
v.capacity();               // get capacity
v[0];                       // access element
v.at(0);                    // access with bounds check
v.reserve(100);             // reserve memory
```

## Klasių Struktūra

```
Zmogus (abstrakti)
    ↑
    | public paveldėjimas
    |
Studentas
```

### Zmogus (abstrakti bazinė klasė)

- Grynas virtualus destruktorius
- 4 grynieji virtualūs metodai
- Negalima sukurti objekto

### Studentas (išvestinė klasė)

- Paveldi vardas_, pavarde_ iš Zmogus
- Turi tarp_rez_, egz_rez_, galutinis_
- Implementuoja Rule of Five
- Override virtualūs metodai

## Unit Testai

Testų failas: `tests/unit_tests.cpp`

| Kategorija | Testai |
|------------|--------|
| Rule of Five | 7 |
| I/O Operatoriai | 3 |
| Polimorfizmas | 3 |
| Abstrakti klasė | 2 |
| Helper funkcijos | 3 |
| Integracija | 2 |
| **Iš viso** | **6 test cases, 81 assertions** |

### Testų vykdymas

```bash
make run_tests
```

Rezultatas:
```
===============================================================================
All tests passed (81 assertions in 6 test cases)
```

## Dokumentacija

### HTML

```bash
make doxygen
xdg-open docs/html/index.html
```

### LaTeX (PDF generavimui)

```bash
make doxygen
cd docs/latex
# Jei turite TeXLive:
make
# Arba naudokite Overleaf:
# 1. Upload docs/latex folderį į Overleaf
# 2. Compile PDF
```

## Įvestis/Išvestis

### operator<<

```cpp
Studentas s("Jonas", "Jonaitis");
s.addTarpRez(8);
s.setEgzRez(10);
std::cout << s;
```

### operator>>

```cpp
Studentas s;
std::cin >> s;  // Formatas: Vardas Pavarde ND1 ND2 ... NDn Egz
```

## Polimorfizmo Pavyzdys

```cpp
std::vector<Zmogus*> people;
people.push_back(new Studentas("S1", "P1"));
people.push_back(new Studentas("S2", "P2"));

for (const auto* p : people) {
    std::cout << p->getVardas() << "\n";
    delete p;
}
```

## Versijų Istorija

| Versija | Data | Aprašymas |
|---------|------|-----------|
| v3.0 | 2026-04-24 | Vector konteineris + efektyvumo analizė |
| v2.0 | 2026-04-24 | Unit Testai (Catch2) + Doxygen dokumentacija |
| v1.5 | 2026-04-24 | Abstrakti klasė Žmogus + Studentas išvestinė |
| v1.2 | 2026-04-24 | Rule of Five + I/O Operatoriai |
| v1.1 | 2026-04 | Konversija į class Studentas |
| v1.0 | 2026-04 | Pradinė versija su struct Mokinys |

## Failų Struktūra

```
.
├── tests/
│   ├── unit_tests.cpp    # Catch2 unit testai
│   └── catch.hpp         # Catch2 header
├── docs/
│   ├── html/             # HTML dokumentacija
│   └── latex/            # LaTeX dokumentacija (PDF)
├── zmogus.h              # Abstrakti bazinė klasė
├── student.h             # Studentas klasė
├── benchmark.h           # Benchmark struktūros
├── benchmark.cpp         # Benchmark implementacija
├── main.cpp              # Pagrindinė programa
├── Makefile              # Kompiliavimo instrukcija
├── Doxyfile              # Doxygen konfigūracija
└── README.md             # Šis dokumentas
```

## V2.0 Detaliau

**Šaka:** `v2.0`

**Realizuota:**
- ✅ Catch2 unit testai (81 assertion)
- ✅ Doxygen HTML + LaTeX dokumentacija
- ✅ Rule of Five testai (būtina)
- ✅ Polimorfizmo testai
- ✅ Abstrakčios klasės testai
- ✅ Švari repozitorija (be build artifact'ų)

**Release:** v2.0 - Unit Testai ir Doxygen Dokumentacija
