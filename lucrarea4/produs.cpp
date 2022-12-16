#include <iostream>
using namespace std;

#ifndef produs_cpp
#define produs_cpp

class produs {
    protected:                                                        // protected members cannot be accessed from outside the class
    string nume;
    int pret;
    int cantitate;
    bool isLocked = false;                       // isLocked initialization with false

    private: 
    produs(const produs &p);                     // copy constructor restriction (does not allow creating a new object by copying an existing one)/ prevent copying

    public:
    produs(const string &nume, const int &pret, const int &cantitate)
    :nume(nume), pret(pret), cantitate(cantitate)                                                               // member initialization list (item 4)
    {
        cout<<"Constructor baza apelat "<<endl;
    }

    produs& operator = (const produs &p) {                        // copy assignment operator
        if (this == &p) {                                         // Item 11: Handle assignment to self in operator=
            cout<<"Asignare la acelasi obiect produs "<<endl;
            return *this;
        }
        cout<<"Copy assignment operator produs "<<endl;

        nume = p.nume;                                            // Item 12: Copy all parts of an object
        pret = p.pret;
        cantitate = p.cantitate;

        return *this;                                             // Item 10: Assignment operator returns a reference to *this
    }

    produs& operator += (const produs &p) {                       // the convention also applies to +=, -=, *=, etc.
        cout<<"Add operator produs "<<endl;

        nume = p.nume;
        pret += p.pret;
        cantitate += p.cantitate;

        return *this;
    }

    void getNume() {
        cout<<"Numele produsului este: "<<this->nume<<endl;
    }

    void setNume(const string numeNou) {
        this->nume = numeNou;
    }

    virtual void setPret(const int &pretNou){      // virtual => declared in the base class and re-defined (overridden) by a derived class => polymorphism
        this->pret = pretNou;
    }

    //destructor 
    ~produs() { 
     cout<<"Destructor baza called "<<this->nume<<endl;
   }

   void setIsLocked(bool isLocked) {      // setter for isLocked variable
       this->isLocked = isLocked;
   }

   void askResource() {                          // method for verifying if isLocked is true or false (has access or not)
       if (this->isLocked) {
           cout<<"No access!"<<endl;
       } else {
           cout<<"Access!"<<endl;
       }
   }

};
#endif