#include <iostream>
#include "produs.cpp"
using namespace std;

class produsAlimentar:public produs{
    protected: 
    string expirare;
    int calorii;

    public:
    produsAlimentar(const string &nume, const int &pret, const int &cantitate, const string &expirare, const int &calorii)
    :produs(nume, pret, cantitate), expirare(expirare), calorii(calorii)
    {
        cout<<"Constructor alimentar apelat"<<endl;
    }

    produsAlimentar& operator = (const produsAlimentar &p) {                        // copy assignment operator
        if (this == &p) {                                                           // Item 11: Handle assignment to self in operator=
            cout<<"Asignare la acelasi obiect produsAlimentar "<<endl;
            return *this;
        }
        cout<<"Copy assignment operator produsAlimentar "<<endl;

        produs::operator = (p);
        expirare = p.expirare;                                        // Item 12: Copy all parts of an object
        calorii = p.calorii;

        return *this;                                                 // Item 10: Assignment operator returns a reference to *this
    }

    produsAlimentar& operator += (const produsAlimentar &p) {         // the convention also applies to +=, -=, *=, etc.
        cout<<"Add operator produsAlimentar "<<endl;

        produs::operator += (p);
        expirare = p.expirare;                                        // Item 12: Copy all parts of an object
        calorii += p.calorii;

        return *this;
    }

    void setPret(const int &pretNou){
        produs::setPret(pretNou);
        cout<<"Pretul produsului "<<this->nume<<" a fost modificat: "<<this->pret<<endl;
    }

    void getCalorii() {
        cout<<"Produsul "<<this->nume<<" are "<<this->calorii<<" calorii"<<endl;
    }

    void getExpirare() {
        cout<<"Produsul "<<this->nume<<" expira la data: "<<this->expirare<<endl;
    }
    void setExpirare(const string dataNoua) {
        this->expirare = dataNoua;
        cout<<"Data de expirare a produsului "<<this->nume<<" a fost schimbata: "<<this->expirare<<endl;
    }

    ~produsAlimentar(){ 
     cout<<"Destructor alimentar apelat "<<this->nume<<endl;
   }
};