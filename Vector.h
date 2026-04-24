/**
 * @file Vector.h
 * @brief Dinaminis masyvo konteineris (std::vector analogas)
 * 
 * Šis konteineris realizuoja pagrindines std::vector funkcijas:
 * - push_back, pop_back, clear
 * - size, capacity, empty, reserve
 * - operator[], at, front, back, data
 * - begin, end iteratoriai
 * - insert, erase
 * - Copy/Move operacijos
 */

#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>
#include <stdexcept>
#include <initializer_list>

/**
 * @class Vector
 * @brief Dinaminis masyvo konteineris
 * 
 * Vector yra dinaminio dydžio konteineris, kuris automatiškai
 * didina savo talpą kai pridedami nauji elementai.
 * 
 * @tparam T Elemento tipas
 */
template<typename T>
class Vector {
private:
    T* data_;           ///< Rodiklis į duomenų masyvą
    size_t size_;       ///< Esamas elementų skaičius
    size_t capacity_;   ///< Maksimalus elementų skaičius (be reallocation)

    /**
     * @brief Keičia konteinerio talpą
     * @param new_capacity Nauja talpa
     */
    void resize_capacity(size_t new_capacity) {
        T* new_data = new T[new_capacity];
        for (size_t i = 0; i < size_; ++i) {
            new_data[i] = data_[i];
        }
        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
    }

public:
    // ========================================================================
    // KONSTRUKTORIAI IR DESTRUKTORIUS
    // ========================================================================

    /**
     * @brief 1. Numatytasis konstruktorius
     * 
     * Sukuria tuščią Vector su capacity = 0
     */
    Vector() : data_(nullptr), size_(0), capacity_(0) {}

    /**
     * @brief 2. Konstruktorius su pradiniu dydžiu
     * @param n Pradinis elementų skaičius
     * @param value Pradinė reikšmė (numatyta: T())
     */
    explicit Vector(size_t n, const T& value = T()) 
        : data_(n > 0 ? new T[n] : nullptr), size_(n), capacity_(n) {
        for (size_t i = 0; i < n; ++i) {
            data_[i] = value;
        }
    }

    /**
     * @brief 3. Kopijavimo konstruktorius
     * @param other Kopijuojamas Vector
     */
    Vector(const Vector& other) 
        : data_(other.size_ > 0 ? new T[other.capacity_] : nullptr),
          size_(other.size_),
          capacity_(other.capacity_) {
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }

    /**
     * @brief 4. Move konstruktorius
     * @param other Perkeliamas Vector
     */
    Vector(Vector&& other) noexcept 
        : data_(other.data_),
          size_(other.size_),
          capacity_(other.capacity_) {
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }

    /**
     * @brief 5. Konstruktorius iš initializer_list
     * @param init Inicializacijos sąrašas
     */
    Vector(std::initializer_list<T> init) 
        : data_(init.size() > 0 ? new T[init.size()] : nullptr),
          size_(init.size()),
          capacity_(init.size()) {
        size_t i = 0;
        for (const T& value : init) {
            data_[i++] = value;
        }
    }

    /**
     * @brief 6. Destruktorius
     */
    ~Vector() {
        delete[] data_;
    }

    // ========================================================================
    // PRISKYRIMO OPERATORIAI
    // ========================================================================

    /**
     * @brief 7. Kopijavimo priskyrimo operatorius
     * @param other Kopijuojamas Vector
     * @return Nuoroda į save
     */
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] data_;
            size_ = other.size_;
            capacity_ = other.capacity_;
            data_ = capacity_ > 0 ? new T[capacity_] : nullptr;
            for (size_t i = 0; i < size_; ++i) {
                data_[i] = other.data_[i];
            }
        }
        return *this;
    }

    /**
     * @brief 8. Move priskyrimo operatorius
     * @param other Perkeliamas Vector
     * @return Nuoroda į save
     */
    Vector& operator=(Vector&& other) noexcept {
        if (this != &other) {
            delete[] data_;
            data_ = other.data_;
            size_ = other.size_;
            capacity_ = other.capacity_;
            other.data_ = nullptr;
            other.size_ = 0;
            other.capacity_ = 0;
        }
        return *this;
    }

    // ========================================================================
    // CAPACITY METODAI
    // ========================================================================

    /**
     * @brief Grąžina elementų skaičių
     * @return size_t Elementų skaičius
     */
    size_t size() const { return size_; }

    /**
     * @brief Grąžina maksimalų elementų skaičių be reallocation
     * @return size_t Talpa
     */
    size_t capacity() const { return capacity_; }

    /**
     * @brief Patikrina ar konteineris tuščias
     * @return true jei tuščias, false kitu atveju
     */
    bool empty() const { return size_ == 0; }

    /**
     * @brief Rezervuoja atmintį
     * @param new_capacity Nauja talpa
     */
    void reserve(size_t new_capacity) {
        if (new_capacity > capacity_) {
            resize_capacity(new_capacity);
        }
    }

    /**
     * @brief Panaikina nepanaudotą talpą
     */
    void shrink_to_fit() {
        if (size_ < capacity_) {
            resize_capacity(size_);
        }
    }

    // ========================================================================
    // ELEMENTŲ PRIEIGA
    // ========================================================================

    /**
     * @brief 9. Elemento prieiga per operator[]
     * @param index Elemento indeksas
     * @return T& Nuoroda į elementą
     */
    T& operator[](size_t index) { return data_[index]; }

    /**
     * @brief 10. Elemento prieiga per operator[] (const)
     * @param index Elemento indeksas
     * @return const T& Const nuoroda į elementą
     */
    const T& operator[](size_t index) const { return data_[index]; }

    /**
     * @brief 11. Elemento prieiga su ribų patikrinimu
     * @param index Elemento indeksas
     * @return T& Nuoroda į elementą
     * @throws std::out_of_range jei index >= size
     */
    T& at(size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Vector::at - index out of range");
        }
        return data_[index];
    }

    /**
     * @brief 12. Elemento prieiga su ribų patikrinimu (const)
     * @param index Elemento indeksas
     * @return const T& Const nuoroda į elementą
     * @throws std::out_of_range jei index >= size
     */
    const T& at(size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Vector::at - index out of range");
        }
        return data_[index];
    }

    /**
     * @brief 13. Pirmo elemento prieiga
     * @return T& Nuoroda į pirmą elementą
     */
    T& front() { return data_[0]; }

    /**
     * @brief 14. Pirmo elemento prieiga (const)
     * @return const T& Const nuoroda į pirmą elementą
     */
    const T& front() const { return data_[0]; }

    /**
     * @brief 15. Paskutinio elemento prieiga
     * @return T& Nuoroda į paskutinį elementą
     */
    T& back() { return data_[size_ - 1]; }

    /**
     * @brief 16. Paskutinio elemento prieiga (const)
     * @return const T& Const nuoroda į paskutinį elementą
     */
    const T& back() const { return data_[size_ - 1]; }

    /**
     * @brief 17. Gauti duomenų masyvo rodiklį
     * @return T* Rodiklis į pirmą elementą
     */
    T* data() { return data_; }

    /**
     * @brief 18. Gauti duomenų masyvo rodiklį (const)
     * @return const T* Const rodiklis į pirmą elementą
     */
    const T* data() const { return data_; }

    // ========================================================================
    // MODIFIKATORIAI
    // ========================================================================

    /**
     * @brief 19. Pridėti elementą į galą
     * @param value Pridedama reikšmė
     */
    void push_back(const T& value) {
        if (size_ == capacity_) {
            size_t new_capacity = capacity_ == 0 ? 1 : capacity_ * 2;
            resize_capacity(new_capacity);
        }
        data_[size_++] = value;
    }

    /**
     * @brief 20. Pridėti elementą į galą (move)
     * @param value Perkielama reikšmė
     */
    void push_back(T&& value) {
        if (size_ == capacity_) {
            size_t new_capacity = capacity_ == 0 ? 1 : capacity_ * 2;
            resize_capacity(new_capacity);
        }
        data_[size_++] = std::move(value);
    }

    /**
     * @brief 21. Pašalinti paskutinį elementą
     */
    void pop_back() {
        if (size_ > 0) {
            --size_;
        }
    }

    /**
     * @brief 22. Išvalyti visus elementus
     */
    void clear() {
        size_ = 0;
    }

    /**
     * @brief 23. Įterpti elementą į poziciją
     * @param pos Pozicija
     * @param value Įterpiama reikšmė
     * @return Iteratorius į įterptą elementą
     */
    T* insert(size_t pos, const T& value) {
        if (pos > size_) {
            throw std::out_of_range("Vector::insert - position out of range");
        }
        if (size_ == capacity_) {
            size_t new_capacity = capacity_ == 0 ? 1 : capacity_ * 2;
            resize_capacity(new_capacity);
        }
        for (size_t i = size_; i > pos; --i) {
            data_[i] = data_[i - 1];
        }
        data_[pos] = value;
        ++size_;
        return &data_[pos];
    }

    /**
     * @brief 24. Pašalinti elementą iš pozicijos
     * @param pos Pozicija
     * @return Iteratorius į sekantį elementą
     */
    T* erase(size_t pos) {
        if (pos >= size_) {
            throw std::out_of_range("Vector::erase - position out of range");
        }
        for (size_t i = pos; i < size_ - 1; ++i) {
            data_[i] = data_[i + 1];
        }
        --size_;
        return pos < size_ ? &data_[pos] : nullptr;
    }

    // ========================================================================
    // ITERATORIAI
    // ========================================================================

    /**
     * @brief 25. Iteratorius į pradžią
     * @return T* Rodiklis į pirmą elementą
     */
    T* begin() { return data_; }

    /**
     * @brief 26. Iteratorius į pabaigą
     * @return T* Rodiklis už paskutinio elemento
     */
    T* end() { return data_ + size_; }

    /**
     * @brief 27. Const iteratorius į pradžią
     * @return const T* Const rodiklis į pirmą elementą
     */
    const T* begin() const { return data_; }

    /**
     * @brief 28. Const iteratorius į pabaigą
     * @return const T* Const rodiklis už paskutinio elemento
     */
    const T* end() const { return data_ + size_; }

    // ========================================================================
    // PALYGINIMO OPERATORIAI
    // ========================================================================

    /**
     * @brief 29. Lygybės operatorius
     * @param other Lyginamas Vector
     * @return true jei lygūs, false kitu atveju
     */
    bool operator==(const Vector& other) const {
        if (size_ != other.size_) return false;
        for (size_t i = 0; i < size_; ++i) {
            if (data_[i] != other.data_[i]) return false;
        }
        return true;
    }

    /**
     * @brief 30. Nelygybės operatorius
     * @param other Lyginamas Vector
     * @return true jei nelygūs, false kitu atveju
     */
    bool operator!=(const Vector& other) const {
        return !(*this == other);
    }
};

#endif
