# objektinis_programavimas (v1.1)

Objektinio programavimo repozitorija. Ši versija (v1.1) konvertuoja `struct Mokinys` į `class Studentas` su pilnais konstruktoriais, destruktoriumi ir operatoriais.

## Sistemos specifikacijos

| Parametras | Reikšmė |
|------------|---------|
| **CPU** | AMD Ryzen 5 5600H with Radeon Graphics |
| **RAM** | 13 GB DDR4 |
| **Diskas** | NVMe SSD 476.9 GB |
| **OS** | Linux |
| **Kompiliatorius** | g++ (C++17) |
| **Optimizacija** | -O3 (numatytoji) |

## Paleidimo instrukcijos

```bash
# Kompiliavimas
make

# Paleidimas
make run

# Struct vs Class spartos testai
make test

# Skirtingi optimizacijos lygiai
make O1
make O2
make O3

# Valymas
make clean
```

## Studentas klasė

### Konstruktoriai ir destruktorius

```cpp
class Studentas {
public:
    Studentas();                                    // numatytasis
    Studentas(std::string vardas, std::string pavarde);  // parametrinis
    Studentas(const Studentas& other);              // kopijavimo
    Studentas(Studentas&& other) noexcept;          // perkėlimo (move)
    ~Studentas();                                   // destruktorius
    
    Studentas& operator=(const Studentas& other);   // kopijavimo priskyrimas
    Studentas& operator=(Studentas&& other) noexcept; // move priskyrimas
    
    // Getter'ai ir setter'iai
    std::string getVardas() const;
    std::string getPavarde() const;
    float getGalutinis() const;
    void setVardas(const std::string& vardas);
    void setGalutinis(float gal);
    // ...
};
```

## Struct vs Class spartos palyginimas

Tyrimas atliktas su:
- **Konteineris:** std::vector
- **Strategija:** 3 (stable_partition)
- **Failų dydžiai:** 100 000, 1 000 000 įrašų

### O1 optimizacija

| Versija | Įrašai | Bendras laikas | Exe dydis |
|---------|--------|----------------|-----------|
| struct  | 100 000 | 0.0819 s | 68 KB |
| class   | 100 000 | 0.0888 s | 68 KB |
| struct  | 1 000 000 | 0.8712 s | 68 KB |
| class   | 1 000 000 | 0.9523 s | 68 KB |

### O2 optimizacija

| Versija | Įrašai | Bendras laikas | Exe dydis |
|---------|--------|----------------|-----------|
| struct  | 100 000 | 0.0851 s | 60 KB |
| class   | 100 000 | 0.0929 s | 60 KB |
| struct  | 1 000 000 | 0.8869 s | 60 KB |
| class   | 1 000 000 | 0.9663 s | 60 KB |

### O3 optimizacija

| Versija | Įrašai | Bendras laikas | Exe dydis |
|---------|--------|----------------|-----------|
| struct  | 100 000 | 0.0812 s | 67 KB |
| class   | 100 000 | 0.0863 s | 67 KB |
| struct  | 1 000 000 | 0.8562 s | 67 KB |
| class   | 1 000 000 | 0.9269 s | 67 KB |

## Optimizacijos flag'ų palyginimas

### Struct versija

| Flag | 100k laikas | 1M laikas | Exe dydis |
|------|-------------|-----------|-----------|
| O1   | 0.0819 s | 0.8712 s | 68 KB |
| O2   | 0.0851 s | 0.8869 s | 60 KB |
| O3   | 0.0812 s | 0.8562 s | 67 KB |

### Class versija

| Flag | 100k laikas | 1M laikas | Exe dydis |
|------|-------------|-----------|-----------|
| O1   | 0.0888 s | 0.9523 s | 68 KB |
| O2   | 0.0929 s | 0.9663 s | 60 KB |
| O3   | 0.0863 s | 0.9269 s | 67 KB |

## Išvados

### Struct vs Class

1. **Spartuma:** Struct versija yra ~6-8% greitesnė už Class versiją dėl paprastesnės atminties valdymo struktūros (nereikia kvieti getter/setter metodų).

2. **Exe dydžiai:** Beveik tapatūs abiejose versijose. O2 sukuria mažiausius failus.

3. **Optimizavimas:** O3 yra greičiausias, O2 - mažiausias exe failas.

### Rekomendacija

- Naudokite **O3** optimizaciją, jei svarbiausias greitis
- Naudokite **O2** optimizaciją, jei svarbiausias failo dydis
- Class versija rekomenduojama, kai reikalingas geresnis inkapsuliavimas ir duomenų apsauga

## Konteineriai (v1.0 tyrimai)

Programa palaiko tris C++ STL konteinerių tipus:

| Konteineris | Charakteristika |
|-------------|-----------------|
| **std::vector** | Dinaminis masyvas, greita O(1) prieiga, lėtas įterpimas/trynimas viduryje |
| **std::list** | Dvikryptis sąrašas, lėta O(n) prieiga, greitas įterpimas/trynimas |
| **std::deque** | Dvikryptė eilė, greita prieiga, efektyvus įterpimas abiejose pusėse |

## Strategijos

### 1 strategija: Du nauji konteineriai
Bendro studentų konteinerio skaidymas į du naujus to paties tipo konteinerius: "vargšiukų" ir "kietiakų".

### 2 strategija: Vienas naujas + trynimas
Bendro studentų konteinerio skaidymas panaudojant tik vieną naują konteinerį: "vargšiukai".

### 3 strategija: std::stable_partition / splice
Optimizuotas skaidymas naudojant C++ STL algoritmus (greičiausia).

## Failų struktūra

```
.
├── main.cpp           # Pagrindinė programa su tyrimais
├── main_struct.cpp    # Struct versijos spartos testai
├── main_class.cpp     # Class versijos spartos testai
├── benchmark.h        # Benchmark struktūros
├── benchmark.cpp      # Benchmark implementacija
├── student.h          # Studentas klasė
├── student_struct.h   # Mokinys struct (backup)
├── Makefile           # Kompiliavimo instrukcija
└── README.md          # Šis dokumentas
```

## Versijų istorija

| Versija | Aprašymas |
|---------|-----------|
| v1.0 | Pradinė versija su struct Mokinys, 3 konteineriais, 3 strategijomis |
| v1.1 | Konversija į class Studentas su pilnais konstruktoriais/destruktoriumi |
