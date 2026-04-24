/**
 * @file zmogus.h
 * @brief Abstrakti bazine klase, apibudinanti zmogu
 * 
 * Siame faile apibrežta abstrakti klase Zmogus, kuri negali tureti objektu.
 * Naudojama kaip bazine klase išvestinems klasems (pvz., Studentas).
 */

#ifndef ZMOGUS_H
#define ZMOGUS_H

#include <string>
#include <iostream>
#include <iomanip>

/**
 * @class Zmogus
 * @brief Abstrakti klase, reprezentuojanti zmogu
 * 
 * Klase turi grynuosius virtualius metodus, todėl negalima sukurti
 * Zmogus tipo objekto. Tik išvestines klases gali buti instancijuojamos.
 * 
 * @note Šis kodas NEKOMPILIUOSI: Zmogus z("Vardas", "Pavarde");
 */
class Zmogus {
protected:
    std::string vardas_;    ///< Zmogaus vardas
    std::string pavarde_;   ///< Zmogaus pavarde

public:
    /**
     * @brief Numatytasis konstruktorius
     * 
     * Sukuria zmogu su tusciais vardu ir pavarde.
     */
    Zmogus() : vardas_(""), pavarde_("") {}
    
    /**
     * @brief Parametrinis konstruktorius
     * @param vardas Zmogaus vardas
     * @param pavarde Zmogaus pavarde
     */
    Zmogus(std::string vardas, std::string pavarde)
        : vardas_(std::move(vardas)), pavarde_(std::move(pavarde)) {}
    
    /**
     * @brief Kopijavimo konstruktorius
     * @param other Kopijuojamas Zmogus objektas
     */
    Zmogus(const Zmogus& other)
        : vardas_(other.vardas_), pavarde_(other.pavarde_) {}
    
    /**
     * @brief Move konstruktorius
     * @param other Perkeliamas Zmogus objektas
     */
    Zmogus(Zmogus&& other) noexcept
        : vardas_(std::move(other.vardas_)), pavarde_(std::move(other.pavarde_)) {}
    
    /**
     * @brief Grynas virtualus destruktorius
     * 
     * Dar klase abstrakcia. Privalo buti implementuotas išvestinese klasese.
     */
    virtual ~Zmogus() = 0;
    
    /**
     * @brief Kopijavimo priskyrimo operatorius
     * @param other Kopijuojamas Zmogus objektas
     * @return Nuoroda i save
     */
    Zmogus& operator=(const Zmogus& other) {
        if (this != &other) {
            vardas_ = other.vardas_;
            pavarde_ = other.pavarde_;
        }
        return *this;
    }
    
    /**
     * @brief Move priskyrimo operatorius
     * @param other Perkeliamas Zmogus objektas
     * @return Nuoroda i save
     */
    Zmogus& operator=(Zmogus&& other) noexcept {
        if (this != &other) {
            vardas_ = std::move(other.vardas_);
            pavarde_ = std::move(other.pavarde_);
        }
        return *this;
    }
    
    /**
     * @brief Grynas virtualus metodas vardui gauti
     * @return Zmogaus vardas
     */
    virtual std::string getVardas() const = 0;
    
    /**
     * @brief Grynas virtualus metodas pavardei gauti
     * @return Zmogaus pavarde
     */
    virtual std::string getPavarde() const = 0;
    
    /**
     * @brief Grynas virtualus metodas išvesciai i srauta
     * @param os Išvesties srautas
     * @return Nuoroda i išvesties srauta
     */
    virtual std::ostream& print(std::ostream& os) const = 0;
    
    /**
     * @brief Grynas virtualus metodas įvesciai is srauto
     * @param is Įvesties srautas
     * @return Nuoroda i įvesties srauta
     */
    virtual std::istream& read(std::istream& is) = 0;
};

// Virtualaus destruktoriaus implementacija (PRIVALOMA!)
inline Zmogus::~Zmogus() {}

#endif
