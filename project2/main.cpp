#include <iostream>
#include<string>
#include<vector>
using namespace std;

class InsuficientPatients: std::exception {
public:
    virtual const char* what() const throw() {
        return "Nu exista pacienti pe lista";
    }
};

class Adult {
protected:
    string nume;
    int colesterol;
    string data_colesterol; //data cand au fost facute analize de colesterol
    int tensiune_arteriala;
    string data_tensiune_arteriala;
    string adresa;
public:
    Adult():nume("necunoscut"),colesterol(0),data_colesterol("necunoscut"),tensiune_arteriala(0),data_tensiune_arteriala("necunoscut"),adresa("necunoscut"){}
    virtual ~Adult(){}
    Adult(string sir_nume, int val_colesterol, string sir_data_col, int val_tensiune, string sir_data_tensiune, string sir_adresa):nume(sir_nume),colesterol(val_colesterol),data_colesterol(sir_data_col),tensiune_arteriala(val_tensiune),data_tensiune_arteriala(sir_data_tensiune),adresa(sir_adresa){}
    Adult(const Adult& ob):nume(ob.nume), colesterol(ob.colesterol), data_colesterol(ob.data_colesterol), tensiune_arteriala(ob.tensiune_arteriala), data_tensiune_arteriala(ob.data_tensiune_arteriala), adresa(ob.adresa){}
    virtual string RiscCV() const;
    virtual void afisare() const;
    string getNume(){return nume;}
    virtual string getTip()const{return "adult";}
};

string Adult::RiscCV() const {
    int nr = 0;
    if (colesterol > 240)
        nr++;
    if (tensiune_arteriala > 139)
        nr++;
    if (nr == 1)
        return "da";
    else
        if (nr>1)
            return " ridicat";
    else
        return "nu";
}

void Adult::afisare() const {
    cout<<getTip()<<endl;
    cout<<"Nume: "<<nume<<endl;
    cout<<"Adresa: "<<adresa<<endl;
    cout<<"Colesterol("<<data_colesterol<<"): "<<colesterol<<endl;
    cout<<"Tensiune arteriala("<<data_tensiune_arteriala<<"): "<<tensiune_arteriala<<endl;
    cout<<"Risc cardiovascular: "<<RiscCV()<<endl;
}

class Copil: public Adult {
    int proteinaC;
    string data_proteina;
    bool antecedente;
public:
    Copil():Adult(){}
    ~Copil(){}
    Copil(string sir_nume, int val_colesterol, string sir_data_col, int val_tensiune, string sir_data_tensiune, string sir_adresa, int val_proteina, string sir_data_proteina, bool val):Adult(sir_nume, val_colesterol, sir_data_col,val_tensiune, sir_data_tensiune, sir_adresa), proteinaC(val_proteina), data_proteina(sir_data_proteina), antecedente(val){}
    Copil(const Copil&ob):Adult(ob), proteinaC(ob.proteinaC), data_proteina(ob.data_proteina), antecedente(ob.antecedente){}
    string RiscCV() const override;
    void afisare() const override;
    string getTip() const override{return "copil";}
};

string Copil::RiscCV() const {
    int nr = 0;
    if (colesterol > 240)
        nr++;
    if (tensiune_arteriala > 139)
        nr++;
    if (antecedente == true)
        nr++;
    if (nr == 1)
        return "da";
    else
        if (nr>1)
            return " ridicat";
        else
            return "nu";
}

void Copil::afisare() const {
    cout<<getTip()<<endl;
    cout<<"Nume: "<<nume<<endl;
    cout<<"Adresa: "<<adresa<<endl;
    cout<<"Colesterol("<<data_colesterol<<"): "<<colesterol<<endl;
    cout<<"Tensiune arteriala("<<data_tensiune_arteriala<<"): "<<tensiune_arteriala<<endl;
    cout<<"Proteina C("<<data_proteina<<"): "<<proteinaC<<endl;
    cout<<"Risc cardiovascular: "<<RiscCV()<<endl;
}

class Batran:public Adult {
    bool fumator;
    string sedentarism;
public:
    Batran():Adult(){}
    ~Batran(){}
    Batran(string sir_nume, int val_colesterol, string sir_data_col, int val_tensiune, string sir_data_tensiune, string sir_adresa, bool val_fumator, string sir_sedentarism):Adult(sir_nume, val_colesterol, sir_data_col,val_tensiune, sir_data_tensiune, sir_adresa), fumator(val_fumator), sedentarism(sir_sedentarism){}
    Batran(const Batran& ob):Adult(ob), fumator(ob.fumator), sedentarism(ob.sedentarism){}
    string RiscCV() const override;
    void afisare() const override;
    string getTip() const override{return "adult de peste 40 de ani";}
};

string Batran::RiscCV() const {
    int nr = 0;
    if (colesterol > 240)
        nr++;
    if (tensiune_arteriala > 139)
        nr++;
    if (fumator == true)
        nr++;
    if (sedentarism == "ridicat" || sedentarism == "Ridicat")
        nr++;
    if (nr == 1)
        return "da";
    else
        if (nr>1)
            return " ridicat";
        else
            return "nu";
}

void Batran::afisare() const {
        cout<<getTip()<<endl;
        cout<<"Nume: "<<nume<<endl;
        cout<<"Adresa: "<<adresa<<endl;
        cout<<"Colesterol("<<data_colesterol<<"): "<<colesterol<<endl;
        cout<<"Tensiune arteriala("<<data_tensiune_arteriala<<"): "<<tensiune_arteriala<<endl;
        cout<<"Fumator: ";
        if (fumator == true)
            cout<<"da"<<endl;
        else
            cout<<"nu"<<endl;
        cout<<"Sedentarism: "<<sedentarism<<endl;
        cout<<"Risc cardiovascular: "<<RiscCV()<<endl;

}

class Meniu {
    static Meniu* instance;
    vector<Adult*> pacienti;
    Meniu(){}
public:
    static Meniu* getInstance() {
        if (instance==nullptr)
            instance = new Meniu();
        return instance;
    }
    ~Meniu() {
        for (auto i:pacienti)
            delete i;
    }
    void AdaugaPacient() {
        string sir_nume;
        int val_colesterol;
        string sir_data_colesterol; //data cand au fost facute analize de colesterol
        int val_tensiune_arteriala;
        string sir_data_tensiune_arteriala;
        string sir_adresa;
        cout<<"Nume: ";
        cin>>sir_nume;
        cout<<"Colesterol: ";
        cin>>val_colesterol;
        cout<<"Data Analize Colesterol: ";
        cin>>sir_data_colesterol;
        cout<<"Tensiune Arteriala: ";
        cin>>val_tensiune_arteriala;
        cout<<"Data analize tensiune arteriala: ";
        cin>>sir_data_tensiune_arteriala;
        cout<<"Adresa: ";
        cin>>sir_adresa;
        int varsta;
        cout<<"varsta: ";
        cin>>varsta;
        if (varsta<18) {
            int val_proteina;
            string sir_data_proteina;
            bool antecedente;
            cout<<"Proteina C: ";
            cin>>val_proteina;
            cout<<"data analize proteina: ";
            cin>>sir_data_proteina;
            cout<<"Antecedente (da-true, nu-false): ";
            cin>>antecedente;
            pacienti.push_back(new Copil(sir_nume,val_colesterol,sir_data_colesterol,val_tensiune_arteriala,sir_data_tensiune_arteriala,sir_adresa,val_proteina,sir_data_proteina,antecedente));

        }
        else
            if (varsta > 40) {
                bool val_fumator;
                string sir_sedentarism;
                cout<<"Fumator(da-true, nu-false): ";
                cin>>val_fumator;
                cout<<"Sedentarism: ";
                cin>>sir_sedentarism;
                pacienti.push_back(new Batran(sir_nume,val_colesterol,sir_data_colesterol,val_tensiune_arteriala,sir_data_tensiune_arteriala,sir_adresa,val_fumator,sir_sedentarism));

            }
        else
            pacienti.push_back(new Adult(sir_nume,val_colesterol,sir_data_colesterol,val_tensiune_arteriala,sir_data_tensiune_arteriala,sir_adresa));
    }
    void afisareAdult() {
        if (pacienti.size()==0)
            throw InsuficientPatients();
        else {
            for (auto i:pacienti)
                if ( i-> getTip()=="adult peste 40 de ani" || i->getTip()=="adult" && i->RiscCV()=="ridicat")
                    i->afisare();
        }
    }
    void afisareCopii() {
        if (pacienti.size()==0)
            throw InsuficientPatients();
       else {
           for (auto i:pacienti)
               if (i->getTip()=="copil" )
                   if (i->RiscCV()=="ridicat" || i->RiscCV()=="da")
                       i->afisare();
       }
    }
    void afisareDupaNume(string sir_nume) {
        if (pacienti.size()==0)
            throw InsuficientPatients();
        else {
            for (auto i:pacienti)
                if (i->getNume() == sir_nume)
                    i->afisare();
        }
    }

};

Meniu* Meniu::instance = nullptr;

int main() {
    Meniu* meniu = Meniu::getInstance();
    int choice;
    cout<<"1.Adauga un pacient"<<endl;
    cout<<"2.Afiseaza toti pacientii adulti cu risc cardiovascular ridicat"<<endl;
    cout<<"3.Afiseaza toti pacientii copii cu risc cardiovascular"<<endl;
    cout<<"4. Afiseaza toti pacientii cu un anumit nume"<<endl;
    cout<<"0.Exit"<<endl;
    cin>>choice;
    while (choice != 0) {
        if (choice == 1)
            meniu->AdaugaPacient();
        else
            if (choice == 2) {
                try{meniu->afisareAdult();}
                catch(InsuficientPatients& e){cout<<e.what()<<endl;}
            }
        else
            if (choice == 3) {
                try{meniu->afisareCopii();}
                catch(InsuficientPatients& e){cout<<e.what()<<endl;}
            }
        else
            if (choice == 4) {
                string sir_nume;
                cout<<"Introduceti numele: ";
                cin>>sir_nume;
                meniu->afisareDupaNume(sir_nume);
            }
        cout<<"1.Adauga un pacient"<<endl;
        cout<<"2.Afiseaza toti pacientii adulti cu risc cardiovascular ridicat"<<endl;
        cout<<"3.Afiseaza toti pacientii copii cu risc cardiovascular"<<endl;
        cout<<"4. Afiseaza toti pacientii cu un anumit nume"<<endl;
        cout<<"0.Exit"<<endl;
        cin>>choice;

    }
    return 0;
}

// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.