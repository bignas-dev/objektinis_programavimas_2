# Studentų Valdymo Sistema - v1.1

## Apie Projektą

Programa skirta studentų duomenų apdorojimui, rūšiavimui ir skirstymui į dvi kategorijas:
- **"Vargšiukai"** - galutinis balas < 5.0
- **"Kietiakiai"** - galutinis balas >= 5.0

Realizuota naudojant `class` tipo `Mokinys` su pilnai realizuotais konstruktoriais ir destruktoriumi. Atlikta struct vs class spartos analizė su skirtingais optimizavimo lygiais.

## Sistemos Reikalavimai

- **Kompiliatorius:** g++ (C++11+)
- **OS:** Linux/Unix
- **Build:** Make

## Testavimo Sistemos Parametrai

| Komponentas | Specifikacija |
|-------------|---------------|
| **CPU** | AMD Ryzen 5 5600H (6 branduoliai) |
| **RAM** | 14 GB |
| **HDD** | SSD |

## Diegimas

```bash
git clone <repo-url>
cd objektinis_programavimas_2
make main
```

## Naudojimas

```bash
# Pagrindinė programa
make main

# Benchmark testas
make bench

# Duomenų generatorius
make gen

# Išvalyti
make clean
```

## Class Realizacija

```cpp
class Mokinys {
private:
    std::string vardas;
    std::string pavarde;
    std::vector<int> tarp_rez;
    int egz_rez;
    float galutinis;

public:
    Mokinys();
    Mokinys(const std::string& firstName, const std::string& lastName);
    ~Mokinys() = default;
    
    void calculateFinalGrade(const std::string& choice);
};
```

### Konstruktoriai

```cpp
Mokinys() : vardas(""), pavarde(""), egz_rez(0), galutinis(-1.0f) {}

Mokinys(const std::string& firstName, const std::string& lastName)
    : vardas(firstName), pavarde(lastName), egz_rez(0), galutinis(-1.0f) {}
```

## Struct vs Class Analizė

### Metodika
- **Konteineris:** `std::vector`
- **Strategija:** S1 (kopijavimas)
- **Dydžiai:** 100k ir 1M įrašų

### Greičio Palyginimas (ms)

| Versija | Dydis | -O1 | -O2 | -O3 |
|---------|-------|-----|-----|-----|
| Struct | 100k | 25 | 22 | 20 |
| Class | 100k | 23 | 20 | 17 |
| Struct | 1M | 218 | 175 | 168 |
| Class | 1M | 200 | 158 | 154 |

**Išvada:** Class versija ~8-15% greitesnė

### Executable Dydžio Palyginimas (bytes)

| Versija | -O1 | -O2 | -O3 |
|---------|-----|-----|-----|
| Struct | 92,160 | 86,016 | 128,000 |
| Class | 95,272 | 89,640 | 133,632 |

**Išvada:** Class executable ~3-4% didesnis

## Optimizavimo Lygių Analizė

### Veikimo Laikas (ms)

| Dydis | -O1 | -O2 | -O3 |
|-------|-----|-----|-----|
| 1k | 0 | 0 | 0 |
| 10k | 2 | 2 | 1 |
| 100k | 23 | 20 | 17 |
| 1M | 200 | 158 | 154 |
| 10M | 2279 | 2170 | 1787 |

### Executable Dydis (bytes)

| Failas | -O1 | -O2 | -O3 |
|--------|-----|-----|-----|
| main | 95,272 | 89,640 | 133,632 |
| benchmark | 128,144 | 77,184 | 123,104 |

### Rekomendacijos

- **-O1:** Testavimui (greita kompiliacija)
- **-O2:** Atminties ribotumui (mažiausias dydis)
- **-O3:** Produkcijai (maksimali sparta)

## Projekto Struktūra

```
objektinis_programavimas_2/
├── main.cpp
├── student.h
├── benchmark.cpp
├── generator.cpp
├── Makefile
├── README.md
└── .gitignore
```

## Versijų Istorija

| Versija | Aprašymas |
|---------|-----------|
| v1.0 | Bazinė versija su struct |
| v1.1 | Class realizacija, spartos analizė |
