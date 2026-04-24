# Objektinis Programavimas v2.0

Studentų duomenų apdorojimo sistema su abstrakčia bazine klase, unit testais ir Doxygen dokumentacija.

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

# Unit testai
make tests

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
