#include <iostream>
#include "produs.cpp"
using namespace std;

class produsElectronic:public produs{
    protected: 
    string garantie;
    int consum;

    public:
    produsElectronic(const string &nume, const int &pret, const int &cantitate, const string &garantie, const int &consum)
    :produs(nume, pret, cantitate), garantie(garantie), consum(consum)
    {
        cout<<"Constructor electronic apelat"<<endl;
    }

    produsElectronic& operator = (const produsElectronic &p) {                        // copy assignment operator
        if (this == &p) {                                                             // Item 11: Handle assignment to self in operator=
            cout<<"Asignare la acelasi obiect produsElectronic "<<endl;
            return *this;
        }
        cout<<"Copy assignment operator produsElectronic "<<endl;

        produs::operator = (p);
        garantie = p.garantie;                                         // Item 12: Copy all parts of an object
        consum = p.consum;

        return *this;                                                  // Item 10: Assignment operator returns a reference to *this
    }

    produsElectronic& operator += (const produsElectronic &p) {         // the convention also applies to +=, -=, *=, etc.
        cout<<"Add operator produsElectronic "<<endl;

        produs::operator += (p);
        garantie += p.garantie;                                         // Item 12: Copy all parts of an object
        consum += p.consum;

        return *this;
    }

    void setPret(const int &pretNou){
        produs::setPret(pretNou);
        cout<<"Pretul produsului "<<this->nume<<" a fost modificat: "<<this->pret<<endl;
    }

    void getConsum() {
        cout<<"Produsul "<<this->nume<<" consuma: "<<this->consum<<"KWh"<<endl;
    }

    void getGarantie() {
        cout<<"Produsul "<<this->nume<<" are garantie: "<<this->garantie<<endl;
    }

    void setGarantie(const string &garantieNoua) {
        cout<<"Garantia produsului "<<this->nume<<" a fost modificata: "<<this->garantie<<endl;
    }

    ~produsElectronic(){ 
     cout<<"Destructor electronic apelat "<<this->nume<<endl;
   }

};