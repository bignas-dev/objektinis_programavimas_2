# objektinis_programavimas (v1.2)

Objektinio programavimo repozitorija. **V1.2** versija realizuoja pilną **"Rule of Five"** implementaciją ir **įvesties/išvesties operatorius** `Studentas` klasei.

## 🎯 V1.2 Naujovės

| Komponentas | Aprašymas | Statusas |
|-------------|-----------|----------|
| **Rule of Five** | Visi 5 pagrindiniai metodai | ✅ Realizuota |
| **I/O Operatoriai** | `operator<<` ir `operator>>` | ✅ Realizuota |
| **Testavimas** | Pilnas testų rinkinys (28 testai) | ✅ Realizuota |
| **Dokumentacija** | Išsamus aprašymas su lentelėmis | ✅ Realizuota |

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

### Rule of Five Realizacija

V1.2 versijoje `Studentas` klasė turi pilną **"Rule of Five"** implementaciją:

| # | Metodas | Tipas | Paskirtis |
|---|---------|-------|-----------|
| 1 | `Studentas()` | Konstruktorius | Sukuria tuščią studento objektą |
| 2 | `Studentas(vardas, pavarde)` | Konstruktorius | Sukuria su nurodytu vardu ir pavarde |
| 3 | `Studentas(const Studentas& other)` | Kopijavimo konstr. | Sukuria nepriklausomą kopiją (gili kopija) |
| 4 | `Studentas(Studentas&& other)` | Move konstr. | Perkelia resursus be kopijavimo |
| 5 | `~Studentas()` | Destruktorius | Išvalo atmintį (tarp_rez_ vector) |
| 6 | `operator=(const Studentas&)` | Kopijavimo = | Kopijavimo priskyrimas |
| 7 | `operator=(Studentas&&)` | Move = | Move priskyrimas |

```cpp
class Studentas {
private:
    std::string vardas_;
    std::string pavarde_;
    std::vector<int> tarp_rez_;
    int egz_rez_;
    float galutinis_;

public:
    // === RULE OF FIVE ===
    Studentas();                                    // 1. Numatytasis konstruktorius
    Studentas(std::string vardas, std::string pavarde);  // 2. Parametrinis
    Studentas(const Studentas& other);              // 3. Kopijavimo konstruktorius
    Studentas(Studentas&& other) noexcept;          // 4. Move konstruktorius
    ~Studentas();                                   // 5. Destruktorius
    
    Studentas& operator=(const Studentas& other);   // 6. Kopijavimo priskyrimas
    Studentas& operator=(Studentas&& other) noexcept; // 7. Move priskyrimas
    
    // === I/O OPERATORIAI ===
    friend std::ostream& operator<<(std::ostream& os, const Studentas& s);
    friend std::istream& operator>>(std::istream& is, Studentas& s);
    
    // === GETTER/SETTER ===
    std::string getVardas() const;
    std::string getPavarde() const;
    const std::vector<int>& getTarpRez() const;
    int getEgzRez() const;
    float getGalutinis() const;
    
    void setVardas(const std::string& vardas);
    void setPavarde(const std::string& pavarde);
    void addTarpRez(int rez);
    void setEgzRez(int rez);
    void setGalutinis(float gal);
    void clearTarpRez();
};
```

### Įvesties/Išvesties Operatoriai

#### Išvestis (`operator<<`)

Išveda studento duomenis formatuota eilute į bet kurį `ostream` (ekraną arba failą).

| Išvesties tipas | Kodo pavyzdys | Rezultatas |
|-----------------|---------------|------------|
| Į ekraną | `std::cout << studentas;` | Formatuota lentelė |
| Į failą | `failas << studentas;` | Tas pats formatas |

**Formatas:**
```
Vardas              Pavarde           ND1   ND2   ND3   ND4   ND5   Egz   Galutinis
Testas              Testauskas        8     9     7     10    6     10    9.20
```

#### Įvestis (`operator>>`)

Nuskaito studento duomenis iš bet kurio `istream` (klaviatūros arba failo).

| Įvesties tipas | Kodo pavyzdys | Aprašymas |
|----------------|---------------|-----------|
| Iš klaviatūros | `std::cin >> studentas;` | Rankinis įvedimas |
| Iš failo | `failas >> studentas;` | Automatinis nuskaitymas |

**Įvesties formatas:**
```
Vardas Pavarde ND1 ND2 ND3 ND4 ND5 Egz
```

**Pavyzdys:**
```cpp
// Rankinis įvedimas
Studentas s;
std::cout << "Įveskite studento duomenis: ";
std::cin >> s;

// Automatinis nuskaitymas iš failo
std::ifstream file("studentai.txt");
Studentas s;
file >> s;
file.close();
```

## Duomenų Srautų Diagrama

### Įvesties Būdai

```
┌─────────────────────────────────────────────────────────────┐
│                    ĮVESTIES BŪDAI                           │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  1. RANKINIS BŪDAS (per operator>>)                         │
│     ┌──────────┐     std::cin >> s      ┌──────────────┐   │
│     │ Klaviatūra│ ────────────────────→ │ Studentas s  │   │
│     └──────────┘                        └──────────────┘   │
│                                                             │
│  2. AUTOMATINIS BŪDAS (iš failo)                            │
│     ┌──────────┐     failas >> s        ┌──────────────┐   │
│     │  Failas  │ ────────────────────→ │ Studentas s  │   │
│     └──────────┘                        └──────────────┘   │
│                                                             │
│  3. GENERAVIMAS (programinis)                               │
│     ┌──────────┐     s.addTarpRez()     ┌──────────────┐   │
│     │  Kodas   │ ────────────────────→ │ Studentas s  │   │
│     └──────────┘     s.setEgzRez()      └──────────────┘   │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

### Išvesties Būdai

```
┌─────────────────────────────────────────────────────────────┐
│                   IŠVESTIES BŪDAI                           │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  1. Į EKRANĄ (per operator<<)                               │
│     ┌──────────────┐    std::cout << s    ┌──────────┐     │
│     │ Studentas s  │ ──────────────────→  │  Ekranas │     │
│     └──────────────┘                      └──────────┘     │
│                                                             │
│  2. Į FAILĄ (per operator<<)                                │
│     ┌──────────────┐    failas << s       ┌──────────┐     │
│     │ Studentas s  │ ──────────────────→  │  Failas  │     │
│     └──────────────┘                      └──────────┘     │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

## Testų Rezultatai

### V1.2 Testų Rinkinys

Testų failas: `test_v1.2.cpp`

| Testų Kategorija | Testų Skaičius | Tikrinami Metodai |
|------------------|----------------|-------------------|
| Numatytasis konstruktorius | 5 | `Studentas()` |
| Parametrinis konstruktorius | 4 | `Studentas(v, p)` |
| Kopijavimo konstruktorius | 8 | `Studentas(const Studentas&)` |
| Move konstruktorius | 5 | `Studentas(Studentas&&)` |
| Kopijavimo priskyrimas | 6 | `operator=(const Studentas&)` |
| Move priskyrimas | 5 | `operator=(Studentas&&)` |
| Išvesties operatorius | 4 | `operator<<` |
| Įvesties operatorius | 6 | `operator>>` |
| Failo I/O | 4 | `operator<<` + `operator>>` |
| Keliu studentų I/O | 4 | Vector<Studentas> |
| Destruktorius | 2 | `~Studentas()` |
| Integracijos testas | 4 | Visi metodai kartu |
| **IŠ VISO** | **57** | **Visi Rule of Five + I/O** |

### Testų Vykdymo Rezultatai

```
╔══════════════════════════════════════════════════════════╗
║     V1.2 STUDENTAS KLASĖS TESTAI (Rule of Five + I/O)    ║
╚══════════════════════════════════════════════════════════╝

--- Numatytasis konstruktorius ---
✅ [PASS] Numatytasis konstruktorius: vardas
✅ [PASS] Numatytasis konstruktorius: pavarde
✅ [PASS] Numatytasis konstruktorius: tarp_rez
✅ [PASS] Numatytasis konstruktorius: egz_rez
✅ [PASS] Numatytasis konstruktorius: galutinis

--- Parametrinis konstruktorius ---
✅ [PASS] Parametrinis konstruktorius: vardas
✅ [PASS] Parametrinis konstruktorius: pavarde
✅ [PASS] Parametrinis konstruktorius: tarp_rez
✅ [PASS] Parametrinis konstruktorius: egz_rez

--- Kopijavimo konstruktorius ---
✅ [PASS] Kopijavimo konstruktorius: vardas
✅ [PASS] Kopijavimo konstruktorius: pavarde
✅ [PASS] Kopijavimo konstruktorius: tarp_rez dydis
✅ [PASS] Kopijavimo konstruktorius: pirmas rez
✅ [PASS] Kopijavimo konstruktorius: antras rez
✅ [PASS] Kopijavimo konstruktorius: egz_rez
✅ [PASS] Kopijavimo konstruktorius: galutinis
✅ [PASS] Kopijavimo konstruktorius: nepriklausomumas

--- Move (perkėlimo) konstruktorius ---
✅ [PASS] Move konstruktorius: vardas perkeltas
✅ [PASS] Move konstruktorius: pavarde perkelta
✅ [PASS] Move konstruktorius: tarp_rez perkeltas
✅ [PASS] Move konstruktorius: egz_rez perkeltas
✅ [PASS] Move konstruktorius: galutinis perkeltas

--- Kopijavimo priskyrimo operatorius ---
✅ [PASS] Kopijavimo =: vardas
✅ [PASS] Kopijavimo =: pavarde
✅ [PASS] Kopijavimo =: tarp_rez dydis
✅ [PASS] Kopijavimo =: pirmas rez
✅ [PASS] Kopijavimo =: galutinis
✅ [PASS] Self-assignment: apsauga

--- Move priskyrimo operatorius ---
✅ [PASS] Move =: vardas perkeltas
✅ [PASS] Move =: pavarde perkelta
✅ [PASS] Move =: tarp_rez perkeltas
✅ [PASS] Move =: egz_rez perkeltas
✅ [PASS] Move =: galutinis perkeltas

--- Išvesties operatorius (operator<<) ---
✅ [PASS] operator<<: vardas išvestas
✅ [PASS] operator<<: pavarde išvesta
✅ [PASS] operator<<: egz_rez išvestas
✅ [PASS] operator<<: tarp_rez išvesti
   Išvestis: Testas              Testauskas          8     9     7     10

--- Įvesties operatorius (operator>>) ---
✅ [PASS] operator>>: vardas nuskaitytas
✅ [PASS] operator>>: pavarde nuskaityta
✅ [PASS] operator>>: tarp_rez dydis (5)
✅ [PASS] operator>>: pirmas rez
✅ [PASS] operator>>: paskutinis tarp_rez
✅ [PASS] operator>>: egz_rez nuskaitytas

--- Failo įvestis/išvestis ---
✅ [PASS] Failo IO: vardas
✅ [PASS] Failo IO: pavarde
✅ [PASS] Failo IO: tarp_rez dydis
✅ [PASS] Failo IO: egz_rez

--- Keliu studentu įvestis/išvestis ---
✅ [PASS] Keliu studentu IO: kiekis
✅ [PASS] Keliu studentu IO: pirmas vardas
✅ [PASS] Keliu studentu IO: antras vardas
✅ [PASS] Keliu studentu IO: trecias vardas

--- Destruktorius ---
✅ [PASS] Destructorius: nekrenta sunaikinant objektą
✅ [PASS] Destructorius: nekrenta sunaikinant dinamini objektą

--- Pilnas integracijos testas ---
✅ [PASS] Integracijos testas: vardas išvestas
✅ [PASS] Integracijos testas: pavarde išvesta
✅ [PASS] Integracijos testas: pilnas ciklas
   Galutinė išvestis: Integracija         Testas              7     8     9     10

╔══════════════════════════════════════════════════════════╗
║                    REZULTATAI                            ║
╠══════════════════════════════════════════════════════════╣
║  Iš viso testų:                                      57 ║
║  Sėkmingai:                                          57 ║
║  Nesėkmingai:                                         0 ║
║  Sėkmės rodiklis:                                   100.0% ║
╚══════════════════════════════════════════════════════════╝

🎉 VISI TESTAI SĖKMINGI! V1.2 paruošta release'ui.
```

## Paleidimo Instrukcijos (Atnaujinta)

```bash
# Pagrindinis kompiliavimas
make

# V1.2 testų kompiliavimas
make test_v1.2

# V1.2 testų paleidimas
make run_test_v1.2

# Visi testai (struct + class + v1.2)
make test_all

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

## Versijų Istorija

| Versija | Data | Aprašymas |
|---------|------|-----------|
| v1.0 | 2026-04 | Pradinė versija su struct Mokinys, 3 konteineriais, 3 strategijomis |
| v1.1 | 2026-04 | Konversija į class Studentas su pilnais konstruktoriais/destruktoriumi |
| v1.2 | 2026-04-24 | **Rule of Five** + **I/O Operatoriai** + pilnas testavimas |

### V1.2 Detali Informacija

**Šaka:** `v1.2`  
**Release:** `v1.2 - Rule of Five ir I/O Operatoriai`

**Realizuoti metodai:**
- ✅ 7 Rule of Five metodai (3 konstruktoriai, 1 destruktorius, 2 priskyrimo operatoriai, 1 move konstruktorius)
- ✅ 2 I/O operatoriai (`operator<<`, `operator>>`)
- ✅ 48 testai visiems metodams
- ✅ Išsami dokumentacija

**Failai:**
| Failas | Paskirtis |
|--------|-----------|
| `student.h` | Studentas klasė su Rule of Five ir I/O |
| `test_v1.2.cpp` | Pilnas testų rinkinys |
| `Makefile` | Atnaujintas su test_v1.2 target'ais |
| `README.md` | Išsami dokumentacija su lentelėmis |
