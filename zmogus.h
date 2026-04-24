#ifndef ZMOGUS_H
#define ZMOGUS_H

#include <string>
#include <iostream>
#include <iomanip>

class Zmogus {
protected:
    std::string vardas_;
    std::string pavarde_;

public:
    // Numatytasis konstruktorius
    Zmogus() : vardas_(""), pavarde_("") {}
    
    // Parametrinis konstruktorius
    Zmogus(std::string vardas, std::string pavarde)
        : vardas_(std::move(vardas)), pavarde_(std::move(pavarde)) {}
    
    // Kopijavimo konstruktorius
    Zmogus(const Zmogus& other)
        : vardas_(other.vardas_), pavarde_(other.pavarde_) {}
    
    // Move konstruktorius
    Zmogus(Zmogus&& other) noexcept
        : vardas_(std::move(other.vardas_)), pavarde_(std::move(other.pavarde_)) {}
    
    // GRYNAS VIRTUALUS DESTRUKTORIUS (daro klasę abstrakčia)
    virtual ~Zmogus() = 0;
    
    // Kopijavimo priskyrimas
    Zmogus& operator=(const Zmogus& other) {
        if (this != &other) {
            vardas_ = other.vardas_;
            pavarde_ = other.pavarde_;
        }
        return *this;
    }
    
    // Move priskyrimas
    Zmogus& operator=(Zmogus&& other) noexcept {
        if (this != &other) {
            vardas_ = std::move(other.vardas_);
            pavarde_ = std::move(other.pavarde_);
        }
        return *this;
    }
    
    // GRYNI VIRTUALŪS METODAI (daro klasę abstrakčia)
    virtual std::string getVardas() const = 0;
    virtual std::string getPavarde() const = 0;
    virtual std::ostream& print(std::ostream& os) const = 0;
    virtual std::istream& read(std::istream& is) = 0;
};

// Virtualaus destruktoriaus implementacija (PRIVALOMA!)
inline Zmogus::~Zmogus() {}

#endif
