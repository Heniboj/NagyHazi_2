#include "jegy.hpp"

/// Jegy
ostream& operator<<(ostream& os, const Jegy& j) {
    if(&os == &cout) {
        return os << j.get_nev() << ' ' << j.get_vsz() << ' ' << j.get_ksz() << ' ' << j.get_hely() << ' '
        << j.get_ind_dt() << ' ' << j.get_ind_all() << ' ' << j.get_erkez_dt() << ' ' << j.get_erkez_all()
        << endl;
    } else {
        return os << j.get_nev() << '#' << j.get_ksz() << '#' << j.get_hely() << '#'<< j.get_vsz() << endl;
    }
}

Jegy& Jegy::operator=(const Jegy j) {
    if(this != &j) {
        this->nev = j.get_nev();
        this->kocsiszam = j.get_ksz();
        this->hely = j.get_hely();
        this->vonat = j.get_vonat();
    }
    return *this;
}

bool Jegy::operator==(const Jegy &j) const {
    if(this->nev == j.get_nev() && this->kocsiszam == j.get_ksz() && this->hely == j.get_hely() && this->vonat == j.vonat) {
        return true;
    }
    return false;
}

/// Jegyek
Jegy Jegyek::operator[](size_t i) const {
    return jegyek[i];
}

void Jegyek::add(const Jegy &j) {
    Jegy* temp = new Jegy[meret+1];
    for(size_t i = 0; i < meret; i++) {
        temp[i] = jegyek[i];
    }
    temp[meret] = j;
    delete[] jegyek;
    jegyek = temp;
    meret++;
}

void Jegyek::remove(const char* nev) {
    for(size_t i = 0; i < meret; i++) {
        if(jegyek[i].get_nev() == nev) {
            Jegy* temp = new Jegy[meret-1];
            size_t idx = 0;
            for(size_t j = 0; j < meret; j++) {
                if(jegyek[j].get_nev() != nev) {
                    temp[idx] = jegyek[j];
                    idx++;
                }
            }
            meret--;
            delete[] jegyek;
            jegyek = temp;
            return;
        }
    }
    throw "Ilyen néven nincs foglalás!";
}

bool Jegyek::checkSeat(String azonosito, int kocsiszam, int ulohely) const {
    for(size_t i = 0; i < meret; i++) {
        if(jegyek[i].get_vsz() == azonosito && jegyek[i].get_ksz() == kocsiszam && jegyek[i].get_hely() == ulohely) {
            return true;
        }
    }
    return false;
}

void beolvas(Jaratok& ja, Jegyek& je, const char* fajlnev) {
    ifstream fpp;
    fpp.open(fajlnev);
    if(!fpp) {
        printf("KIVETEL\n");
        throw "QP4TVJ";
    }
    String* adatok = new String[4];
    Vonat v;

    int i = 0;
    while(getline(fpp,adatok[i],'#')) {
        if(i == 2) {
            getline(fpp, adatok[3], '\n');
            for(size_t k = 0; k < ja.size(); k++) {
                if(ja[k].get_vsz() == adatok[3]) {
                    v = ja[k];
                    break;
                }
            }
            Jegy j(adatok[0], stoi(adatok[1]), stoi(adatok[2]), v);
            i = -1;
            je.add(j);
            delete[] adatok;
            adatok = new String[4];
        }
        i++;
    }
    delete[] adatok;
    fpp.close();
}

ostream& operator<<(ostream& os, const Jegyek& j) {
    for(size_t i = 0; i < j.size(); i++) {
        os << j[i];
    }
    return os;
}