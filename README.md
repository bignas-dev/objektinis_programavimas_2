# Studentų Valdymo Sistema

## Programos Paleidimas

### 1. Kompiliavimas

```bash
make
```

### 2. Paleidimas

```bash
./main
```

### 3. Meniu Pasirinkimai

```
=== Studentų Duomenų Įvestis ===
Pasirinkite įvesties būdą:
1 - Rankinis įvedimas (konsolė)
2 - Automatinis generavimas
3 - Nuskaitymas iš failo

=== Galutinio Balo Skaičiavimas ===
1 - Vidurkis
2 - Mediana

=== Rūšiavimas ===
1 - Pagal vardą (a-z)
2 - Pagal pavardę (a-z)
3 - Pagal galutinį balą (didėjantis)

=== Rezultatų Išvestis ===
1 - Į ekraną (konsolė)
2 - Į failą
```

---

## Failų Struktūra

```
objektinis_programavimas_2/
├── student.h          # Studentas klasė su perdengtais I/O metodais
├── main.cpp           # Pagrindinė programa (naudoja naujus metodus)
├── generator.cpp      # Duomenų generatorius benchmark'ams
├── test.cpp           # Unit testai
├── benchmark.cpp      # Sparos testai su skirtingomis konteineriais
├── output.txt         # Išvesties failas (sukuria programa)
└── README.md          # Šis dokumentas
```

---

## Klasės Studentas Struktūra

### Privatūs kintamieji

| Kintamasis | Tipas | Aprašymas |
|------------|-------|-----------|
| `vardas` | `std::string` | Studento vardas |
| `pavarde` | `std::string` | Studento pavardė |
| `tarp_rez` | `std::vector<int>` | Tarpinių pažymių sąrašas |
| `egz_rez` | `int` | Egzamino rezultatas (0-10) |
| `galutinis` | `float` | Galutinis balas (apskaičiuotas) |

### Konstruktoriai

| Konstruktorius | Aprašymas |
|----------------|-----------|
| `Studentas()` | Numatytasis konstruktorius |
| `Studentas(vardas, pavarde)` | Konstruktorius su parametrais |
| `Studentas(const Studentas& other)` | Kopijavimo konstruktorius |
| `Studentas(Studentas&& other)` | Perkėlimo konstruktorius |

### Operatoriai

| Operatorius | Paskirtis |
|-------------|-----------|
| `operator<<` | Išvesties srauto operatorius |
| `operator>>` | Įvesties srauto operatorius |
| `operator==`, `operator!=` | Lygybės palyginimas |
| `operator<`, `operator>`, `operator<=`, `operator>=` | Rūšiavimo palyginimai |

---

## Papildomos Funkcijos

| Funkcija | Aprašymas |
|----------|-----------|
| `readFromFile(filename)` | Nuskaityti visus studentus iš failo į `std::vector` |
| `calculateFinalGrade(studentas, choice)` | Apskaičiuoti galutinį balą (vidurkis arba mediana) |
| `displayResults(students, choice)` | Atvaizduoti rezultatus konsolėje |
| `writeResultsToAFile(students, choice, filename)` | Įrašyti rezultatus į failą |

---
