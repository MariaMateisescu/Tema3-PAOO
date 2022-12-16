#include <iostream>
#include "produsAlimentar.cpp"
#include "produsElectronic.cpp"
#include <memory>
using namespace std;

produs* CreateProdusInstance() {           // method for creating a product instance
    return (new produs("UNT", 13, 6));
}

void lock(produs &produs) {         // method for locking the mutex, isLocked is true
    cout<<"Locking..."<<endl;
    produs.setIsLocked(true);
}

void unlock(produs &produs) {       // method for unlocking the mutex, isLocked is false
    cout<<"Unlocking..."<<endl;
    produs.setIsLocked(false);
}

class Lock {                  // class to manage locks, to make sure you never forget to unlock a locked mutex
    private:
    produs &lockPtr;

    public:
    Lock(produs &ptr):
    lockPtr(ptr) {
        lock(lockPtr);       // acquire resource
    }
    ~Lock() {
        unlock(lockPtr);     // release resource
    }
};

int main() {                                                                            // produs: nume, pret, cantitate
                                                                                        // pAliment: nume, pret, cantitate, expirare, calorii
    produs p1("ZAP", 28, 4);                                                            // pElectronic: nume, pret, cantitate, garantie, consum
    p1.getNume();

    produsAlimentar a2("morcov", 1, 7, "23.12", 15);

    produsElectronic e1("IPHONE", 2300, 12,"2 ani", 97);
    e1.getNume();
    e1.setPret(3200);

    //produsElectronic e2(e1);                                                            // attempt to copy e1, should not compile
    // e2.getNume();

    produsElectronic e4("laptop",4700, 3, "3 ani", 200);
    // e4 = e1;                                                                           // copy assignment operator

    produsAlimentar *a1 = new produsAlimentar("lapte", 6, 2, "13.12", 1100);
    a1->getExpirare();
    a1->setPret(9);
    // delete a1;                                                                         // manually delete a reference, prevents memory leaks

    produsAlimentar a3("oua", 2, 10, "28.12", 130);
    a3.getCalorii();
    a1->getCalorii();
    a3 = a2 = *a1;
    a3.getCalorii();

    a3 += a2 += *a1;
    a3.getCalorii();

    a3.setExpirare("01.01");

    a3.getExpirare();
    a2.getExpirare();
    a2 = a3; 
    a2.getExpirare();

    // Item 13: Use objects to manage resources
    // smart pointers are used to make sure that an object is deleted if it is no longer used

    cout<<"------auto_ptr-----"<<endl;                        // auto_ptr automatically deletes what it points to when destroyed
    {                                                         // copying them sets them to null and the copying pointer assumes sole ownership of the resource
        auto_ptr<produs> autoprodus(CreateProdusInstance());
        autoprodus->getNume();
        auto_ptr<produs> autoprodus2(autoprodus);
        autoprodus2->getNume();
    }

    // auto_ptr was replaced by the unique_ptr due to some design flaws and new features of the language
    cout<<"------unique_ptr-----"<<endl;                     // unique_ptr does not support copying, if we try to copy a unique_ptr => compiler errors
    {                                                        // the pointer is moved from one unique_ptr to another, which invalidates the first unique_ptr
        unique_ptr<produs> uniqueprodus(CreateProdusInstance());
        uniqueprodus->getNume();
        unique_ptr<produs> uniqueprodus2 = move(uniqueprodus);
    }

    cout<<"------shared_ptr-----"<<endl;                     //  keeps track of how many objects point to a particular resource
    {                                                        // automatically deletes the resource when nobody is pointing to it any longer
        shared_ptr<produs> sharedProdus(CreateProdusInstance());
        sharedProdus->getNume();
        cout<<"sharedProdus count = " <<sharedProdus.use_count()<<endl;
        shared_ptr<produs> sharedProdus2(sharedProdus);
        cout<<"sharedProdus count = " <<sharedProdus.use_count()<<endl;
        sharedProdus2->getNume();
        sharedProdus2->setNume("orez");
        sharedProdus->getNume();

        shared_ptr<produs> sharedProdus3 = move(sharedProdus);
        cout<<"sharedProdus count = " <<sharedProdus.use_count()<<endl;
        cout<<"sharedProdus3 count = " <<sharedProdus3.use_count()<<endl;
        sharedProdus3->setNume("faina");
        sharedProdus3->getNume();

        sharedProdus2->getNume();
    }

    //Item 14: Think carefully about copying behavior in resource-managing classes
    produs produsLock("DERO", 21, 4);                   // create an object of type produs
    Lock *locked = new Lock(produsLock);                // when created, it locks the produsLock (isLocked = true)
    produsLock.askResource();
    delete locked;                                      // unlock (isLocked = false)
    produsLock.askResource();

    return 0;
}
