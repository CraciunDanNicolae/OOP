#include <iostream>
#include <vector>
#include<string>
using namespace std;
 class Insuficientworkers:std::exception {
 public:
     virtual const char* what() const throw() {
         return "Nu exista angajati";
     }
 };
class Angajat {
protected:
    static int const prima_fixa;
    string nume;
    string prenume;
    string data_intrare;//data inceperii contractului
public:
    Angajat():nume("necunoscut"), prenume("necunoscut"),data_intrare("necunoscut"){}
    virtual ~Angajat(){}
    Angajat(string sir_nume, string sir_prenume, string data):nume(sir_nume), prenume(sir_prenume), data_intrare(data){}
    Angajat(const Angajat& ob):nume(ob.nume), prenume(ob.prenume), data_intrare(ob.data_intrare){}
    virtual void afisare() = 0;
    virtual string tipLucru() const = 0;
    virtual float Prima()  = 0;
    virtual string Activitate()const = 0;
    virtual int Criteriu() = 0; //functie care impplineste crietriile de afisare pentru fiecare tip de angajat
};
int const Angajat::prima_fixa = 400;

class TESA: public Angajat {
    int weekend;
public:
    TESA():Angajat(), weekend(0){}
    ~TESA(){}
    TESA(string sir_nume, string sir_prenume, string data, int val_weekend):Angajat(sir_nume, sir_prenume,  data), weekend(val_weekend){}
    TESA(const TESA&ob):Angajat(ob), weekend(ob.weekend){}
    string Activitate()const{return "TESA";}
    string tipLucru() const override{return "contract permanent";}
    void afisare()  override;
    float Prima() override;
    int Criteriu() override{
        if (weekend == 2)
            return 1;
        return 0;
    }
};
float TESA::Prima(){return prima_fixa;}
void TESA::afisare() {
    cout<<nume<<" "<<prenume<<", "<<tipLucru()<<", "<<data_intrare<<", "<<Activitate()<<", "<<"weekend "<<weekend<<", "<<"prima: "<<Prima()<<endl;
}

class Lucrativ: public Angajat {
    int nr_copii;
public:
    Lucrativ():Angajat(), nr_copii(0){}
    ~Lucrativ(){}
    Lucrativ(string sir_nume, string sir_prenume, string data, int val_copii):Angajat(sir_nume, sir_prenume,  data), nr_copii(val_copii){}
    Lucrativ(const Lucrativ& ob):Angajat(ob), nr_copii(ob.nr_copii){}
    string Activitate()const override{return "lucrativ";}
    string tipLucru() const override{return "contract permanent";}
    void afisare()  override;
    float Prima() override;
    int Criteriu() override{return nr_copii;}
};
float Lucrativ::Prima() {
    int vechime, an = 0;
    int nr = 1000;
    int i;
    for (i=7;i<data_intrare.size();i++) {
        an = an + (data_intrare[i] - '0')*nr;
        nr = nr/10;
    }
    vechime = 2014 - an;
    return prima_fixa + nr_copii*((vechime*prima_fixa)/100);

}
void Lucrativ::afisare() {
    cout<<nume<<" "<<prenume<<", "<<tipLucru()<<", "<<data_intrare<<", "<<Activitate()<<", "<<"copii: "<<nr_copii<<", "<<"prima: "<<Prima()<<endl;
}


class AngajatCuOra:public Angajat {
    string data_terminare;
public:
    AngajatCuOra():Angajat(), data_terminare("necunoscut"){}
    ~AngajatCuOra(){}
    AngajatCuOra(string sir_nume, string sir_prenume, string data, string sir_data):Angajat(sir_nume, sir_prenume,  data), data_terminare(sir_data){}
    AngajatCuOra(const AngajatCuOra& ob):Angajat(ob), data_terminare(ob.data_terminare){}
    string tipLucru() const override{return "plata cu ora";}
    void afisare() override;
    float Prima() override;
    string Activitate() const override{return "angajat cu ora";}
    int Criteriu() override {
        int an, luna;
        int nr1 = 1000, nr2 = 10;
        int i;
        for (i=7;i<data_intrare.size();i++) {
            an = an + (data_intrare[i] - '0')*nr1;
            nr1 = nr1/10;
        }
        for (i=3;i<5;i++) {
            luna = luna + (data_intrare[i] - '0')*nr2;
            nr2 = nr2/10;
        }
        if (luna < 3 && an <2015)
            return 0;

        return 1;

    }
};
float AngajatCuOra::Prima() {
    int  an = 0;
    int nr = 1000;
    int i;
    for (i=7;i<data_intrare.size();i++) {
        an = an + (data_intrare[i] - '0')*nr;
        nr = nr/10;
    }
    if (an==2015) {
        return prima_fixa;
    }
    return prima_fixa/2;
}
void AngajatCuOra::afisare() {
    cout<<nume<<" "<<prenume<<", "<<tipLucru()<<", "<<data_intrare<<"-"<<data_terminare<<", "<<"copii: "<<"prima: "<<Prima()<<endl;
}

class Meniu {
    static Meniu* instance;
    vector<Angajat*> angajati;
    Meniu(){}
public:
    static Meniu* getInstance() {
        if (instance==nullptr)
            instance = new Meniu();
        return instance;
    }
    ~Meniu() {
        for (auto i:angajati)
            delete i;
    }
    void AdaugaAngajat(){
        string sir_nume;
        string sir_prenume;
        string sir_data_intrare;
        cout<<"Nume: ";
        cin>>sir_nume;
        cout<<"preunme: ";
        cin>>sir_prenume;
        cout<<"Data de inceput a contractului: ";
        cin>>sir_data_intrare;
        int nr;
        cout<<"Itnroduceti tipul activitatii TESA-1, Lucrativ - 2, Plata cu ora - 3: ";
        cin>>nr;
        if (nr == 1) {
            int val_weekend;
            cout<<"Introduceti weekendul ales liber: ";
            cin>>val_weekend;
            angajati.push_back(new TESA(sir_nume,sir_prenume,sir_data_intrare,val_weekend));
        }
        else if (nr==2) {
            int copii;
            cout<<"Introduceti numarul de copii de care are grija angajatul: ";
            cin>>copii;
            angajati.push_back(new Lucrativ(sir_nume,sir_prenume,sir_data_intrare,copii));
        }
        else
            if (nr==3) {
                string sir_data;
                cout<<"introduceti data de terminare a contractului: ";
                cin>>sir_data;
                angajati.push_back(new AngajatCuOra(sir_nume,sir_prenume,sir_data_intrare,sir_data));
            }
    }

    void AfisareAngajati() {
        if (angajati.size()==0)
            throw Insuficientworkers();
        else
            for (auto i:angajati)
                i->afisare();
    }

    void AfisareLucrativCopii() {
        if (angajati.size()==0)
            throw Insuficientworkers();
        else {
            for (auto i:angajati)
                if (i->Activitate()=="lucrativ" && i->Criteriu())
                    i->afisare();
            }
    }

    void AfisareWeekend2() {
        if (angajati.size()==0)
            throw Insuficientworkers();
        else {
            for (auto i:angajati)
                if (i->Activitate()=="TESA" && i->Criteriu())
                    i->afisare();
        }
    }
    void AfisarePlataOra() {
        if (angajati.size()==0)
            throw Insuficientworkers();
        else {
            for (auto i:angajati)
                if (i->Activitate()=="angajat cu ora" && i->Criteriu())
                    i->afisare();
        }
    }
};
Meniu* Meniu::instance = nullptr;
int main() {
    Meniu* meniu = Meniu::getInstance();
    cout<<"1. Adauga angajat"<<endl;
    cout<<"2.Afisarea tuturor angajatilor"<<endl;;
    cout<<"3. Afisarea angajatilor TESA ce au facut rezervare la munte in al doilea weekend din decembrie."<<endl;
    cout<<"4. Afisarea angajatilor lucrativi care se ocupa de copii"<<endl;
    cout<<"5.Afișarea tuturor angajaților in regim de plata cu ora, care au contract pana cel putin in martie 2015"<<endl;
    cout<<"0.Exit"<<endl;
    int choice;
    cin>>choice;
    while (choice != 0) {
        if (choice == 1)
            meniu->AdaugaAngajat();
        else
            if (choice == 2) {
                try{meniu->AfisareAngajati();}
                catch(Insuficientworkers& e){cout<<e.what()<<endl;}

            }
        else
            if (choice == 3) {
                try{meniu->AfisareWeekend2();}
                catch(Insuficientworkers& e){cout<<e.what()<<endl;}

            }
        else
            if (choice == 4) {
                try{meniu->AfisareLucrativCopii();}
                catch(Insuficientworkers& e){cout<<e.what()<<endl;}
            }
        else
            if (choice == 5) {
                try{meniu->AfisarePlataOra();}
                catch(Insuficientworkers& e){cout<<e.what()<<endl;}
            }
        cout<<"1. Adauga angajat"<<endl;
        cout<<"2.Afisarea tuturor angajatilor"<<endl;;
        cout<<"3. Afisarea angajatilor TESA ce au facut rezervare la munte in al doilea weekend din decembrie."<<endl;
        cout<<"4. Afisarea angajatilor lucrativi care se ocupa de copii"<<endl;
        cout<<"5.Afișarea tuturor angajaților in regim de plata cu ora, care au contract pana cel putin in martie 2015"<<endl;
        cout<<"0.Exit"<<endl;

        cin>>choice;

    }

    return 0;
}

// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.