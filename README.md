# Objektinis Programavimas (v1.5)

Šiame projekte realizuota studentų duomenų apdorojimo sistema su abstrakčia bazine klase.

## V1.5 Naujovės

- Abstrakti bazinė klasė `Žmogus` su grynaisiais virtualiais metodais
- Išvestinė klasė `Studentas` paveldinti iš `Žmogus`
- Pilna "Rule of Five" implementacija
- Įvesties/išvesties operatoriai
- Polimorfizmo demonstracija
- 69 testai (100% sėkmė)

## Sistemos specifikacijos

| Parametras | Reikšmė |
|------------|---------|
| CPU | AMD Ryzen 5 5600H |
| RAM | 13 GB DDR4 |
| OS | Linux |
| Kompiliatorius | g++ (C++17) |
| Optimizacija | -O3 |

## Paleidimas

```bash
make              # Kompiliuoti
make run          # Paleisti programą
make test         # Struct vs Class testai
make test_v1.5    # V1.5 testai
make run_test_v1.5 # Paleisti V1.5 testus
make test_all     # Visi testai
make clean        # Išvalyti
```

## Klasių Struktūra

### Abstrakti klasė Žmogus

```cpp
class Zmogus {
protected:
    std::string vardas_;
    std::string pavarde_;

public:
    virtual ~Zmogus() = 0;  // Grynas virtualus destruktorius
    virtual std::string getVardas() const = 0;
    virtual std::string getPavarde() const = 0;
    virtual std::ostream& print(std::ostream& os) const = 0;
    virtual std::istream& read(std::istream& is) = 0;
};
```

**Svarbu:** Negalima sukurti `Zmogus` objekto:
```cpp
Zmogus z("Vardas", "Pavarde");  // KLAIDA: abstrakti klasė
```

### Išvestinė klasė Studentas

```
Zmogus (abstrakti)
    ↑
    | public paveldėjimas
    |
Studentas
    - tarp_rez_: vector<int>
    - egz_rez_: int
    - galutinis_: float
```

Studentas klasė realizuoja visus virtualius metodus ir turi Rule of Five metodus:
- Numatytasis konstruktorius
- Parametrinis konstruktorius
- Kopijavimo konstruktorius
- Move konstruktorius
- Destruktorius
- Kopijavimo priskyrimo operatorius
- Move priskyrimo operatorius

### Polimorfizmo pavyzdys

```cpp
// Bazinės klasės rodyklė į Studentas
Zmogus* z = new Studentas("Jonas", "Jonaitis");
std::cout << z->getVardas();  // "Jonas"
delete z;

// Vector of base class pointers
std::vector<Zmogus*> people;
people.push_back(new Studentas("Studentas1", "Pavarde1"));
people.push_back(new Studentas("Studentas2", "Pavarde2"));

for (Zmogus* p : people) {
    std::cout << p->getVardas() << "\n";
    delete p;
}
```

## Įvestis/Išvestis

### operator<<

```cpp
Studentas s("Jonas", "Jonaitis");
s.addTarpRez(8);
s.addTarpRez(9);
s.setEgzRez(10);

std::cout << s;  // Arba: failas << s;
```

Formatas:
```
Vardas              Pavarde           8     9     10
Jonas               Jonaitis          8     9     10
```

### operator>>

```cpp
Studentas s;
std::cin >> s;  // Arba: failas >> s;
```

Įvesties formatas: `Vardas Pavarde ND1 ND2 ND3 ND4 ND5 Egz`

## Testai

### V1.5 Testų rezultatai

Testų failas: `test_v1.5.cpp`

| Kategorija | Testai |
|------------|--------|
| Abstrakti klasė Žmogus | 4 |
| Konstruktoriai | 14 |
| Priskyrimo operatoriai | 11 |
| I/O operatoriai | 10 |
| Failo I/O | 4 |
| Destruktorius | 2 |
| Polimorfizmas | 7 |
| Keliu studentų I/O | 4 |
| Integracija | 4 |
| **Iš viso** | **69** |

Visi 69 testai praeina (100% sėkmė).

## Strukt vs Class spartos testai (v1.1)

Tyrimas su 100k ir 1M įrašų, O3 optimizacija:

| Versija | 100k | 1M | Exe dydis |
|---------|------|-----|-----------|
| struct | 0.0812 s | 0.8562 s | 67 KB |
| class | 0.0863 s | 0.9269 s | 67 KB |

Struct versija ~6% greitesnė.

## Konteineriai

Programa naudoja tris STL konteinerius:
- `std::vector` - greita prieiga, lėtas trynimas
- `std::list` - lėta prieiga, greitas trynimas
- `std::deque` - balansas tarp vector ir list

## Strategijos

1. **Du nauji konteineriai** - skaidymas į "vargšiukus" ir "kietiakus"
2. **Vienas naujas + trynimas** - sukurti vargšiukus, trinti iš originalo
3. **stable_partition** - optimizuotas skaidymas (greičiausia)

## Failų struktūra

```
.
├── main.cpp           # Pagrindinė programa
├── benchmark.h        # Benchmark struktūros
├── benchmark.cpp      # Benchmark implementacija
├── zmogus.h           # Abstrakti bazinė klasė (v1.5)
├── student.h          # Studentas klasė
├── test_v1.5.cpp      # V1.5 testai
├── test_v1.2.cpp      # V1.2 testai
├── Makefile
└── README.md
```

## Versijų istorija

| Versija | Aprašymas |
|---------|-----------|
| v1.0 | Pradinė versija su struct Mokinys |
| v1.1 | Konversija į class Studentas |
| v1.2 | Rule of Five + I/O operatoriai |
| v1.5 | Abstrakti klasė Žmogus + Studentas išvestinė |

## V1.5 Detaliau

**Šaka:** `v1.5`

**Realizuota:**
- Abstrakti bazinė klasė `Žmogus` su grynaisiais virtualiais metodais
- Išvestinė klasė `Studentas : public Zmogus`
- 7 Rule of Five metodai
- Virtualių metodų override
- 69 testai visiems metodams

**Pagrindiniai failai:**
- `zmogus.h` - abstrakti bazinė klasė
- `student.h` - Studentas klasė
- `test_v1.5.cpp` - testai
