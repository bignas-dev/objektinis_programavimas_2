# Vector Konteineris - V3.0 Dokumentacija

## Apžvalga

Vector yra dinaminio dydžio konteineris, realizuojantis pagrindines `std::vector` funkcijas.

## Funkcijų Sąrašas

### Konstrukoriai (5)

| Funkcija | Aprašymas |
|----------|-----------|
| `Vector()` | Numatytasis konstruktorius |
| `Vector(size_t n, const T& value)` | Konstruktorius su dydžiu ir reikšme |
| `Vector(const Vector& other)` | Kopijavimo konstruktorius |
| `Vector(Vector&& other)` | Move konstruktorius |
| `Vector(std::initializer_list<T>)` | Inicializacijos sąrašo konstruktorius |

### Capacity (5)

| Funkcija | Aprašymas |
|----------|-----------|
| `size()` | Grąžina elementų skaičių |
| `capacity()` | Grąžina maksimalų elementų skaičių |
| `empty()` | Patikrina ar tuščias |
| `reserve(n)` | Rezervuoja atmintį |
| `shrink_to_fit()` | Panaikina nepanaudotą talpą |

### Element Access (5)

| Funkcija | Aprašymas |
|----------|-----------|
| `operator[]` | Elemento prieiga be patikrinimo |
| `at()` | Elemento prieiga su ribų patikrinimu |
| `front()` | Pirmo elemento prieiga |
| `back()` | Paskutinio elemento prieiga |
| `data()` | Gauti duomenų masyvo rodiklį |

### Modifiers (6)

| Funkcija | Aprašymas |
|----------|-----------|
| `push_back()` | Pridėti elementą į galą |
| `pop_back()` | Pašalinti paskutinį elementą |
| `clear()` | Išvalyti visus elementus |
| `insert()` | Įterpti elementą |
| `erase()` | Pašalinti elementą |
| `operator=` | Priskyrimo operatorius |

### Iterators (2)

| Funkcija | Aprašymas |
|----------|-----------|
| `begin()` | Iteratorius į pradžią |
| `end()` | Iteratorius į pabaigą |

### Operators (3)

| Funkcija | Aprašymas |
|----------|-----------|
| `operator==` | Lygybės operatorius |
| `operator!=` | Nelygybės operatorius |
| `operator[]` | Elemento prieigos operatorius |

**Iš viso:** 26 funkcijos

## Efektyvumas

### push_back() Greitis

| Elementai | std::vector | Vector | Speedup |
|-----------|-------------|--------|---------|
| 10K | 0.0189 ms | 0.0171 ms | 1.11x |
| 100K | 0.2369 ms | 0.1920 ms | 1.23x |
| 1M | 2.3343 ms | 1.9234 ms | 1.21x |
| 10M | 23.8322 ms | 20.2992 ms | 1.17x |

### Atminties Perskirstymai

| Elementai | Perskirstymai |
|-----------|---------------|
| 10K | 15 |
| 100K | 18 |
| 1M | 21 |
| 10M | 25 |
| 100M | 28 |

## Naudojimo Pavyzdžiai

### Bazinis naudojimas

```cpp
#include "Vector.h"

Vector<int> v;
v.push_back(1);
v.push_back(2);
v.push_back(3);

std::cout << v.size() << std::endl;  // 3
std::cout << v[0] << std::endl;      // 1
```

### Su reserve

```cpp
Vector<int> v;
v.reserve(1000);  // Rezervuoti atmintį iš anksto

for (int i = 0; i < 1000; ++i) {
    v.push_back(i);  // Nėra reallocation
}
```

### Iterators

```cpp
Vector<int> v{1, 2, 3, 4, 5};

for (auto it = v.begin(); it != v.end(); ++it) {
    std::cout << *it << std::endl;
}

// Arba range-based for
for (int val : v) {
    std::cout << val << std::endl;
}
```

### Copy ir Move

```cpp
Vector<int> v1{1, 2, 3};

// Copy
Vector<int> v2 = v1;

// Move
Vector<int> v3 = std::move(v1);
// v1 dabar tuščias
```

## Testavimas

Vector konteineris yra pilnai ištestuotas naudojant Catch2 framework:

- 9 test cases
- 90+ assertions
- 100% test coverage

```bash
make test_vector
./tests/test_vector
```

## Diegimas

```bash
make main_vector    # Sukompiliuoti
./main_vector       # Paleisti
```
