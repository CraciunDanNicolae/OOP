#include <iostream>
#include<vector>
#include<string>
using namespace std;

class Insuficientstations: public std::exception {
public:
    virtual const char* what() const throw(){
        return "Nu exista statii";
    }
};
class Statie {
protected:
    string adresa;
    vector<string> autobuze;
    string nume;
    int numar_de_ordine;
    static int nr_statii;
public:
    Statie():adresa("necunoscut"), nume("necunoscut"),numar_de_ordine(nr_statii++){}
    virtual ~Statie(){}
    Statie(string sir_adresa, vector<string>sir,string sir_nume):adresa(sir_adresa), autobuze(sir), nume(sir_nume),numar_de_ordine(nr_statii++){}
    virtual string returnCode() const = 0;
    virtual void afisare() const = 0;
    virtual string getType()const = 0;
    Statie(const Statie &ob):adresa(ob.adresa), autobuze(ob.autobuze),nume(ob.nume),numar_de_ordine(ob.numar_de_ordine){}
    string getNume(){return nume;}
    string getAdress(){return adresa;}
    vector<string> getAutobuze(){return autobuze;}
};
int Statie::nr_statii = 1;

class Urbana: public Statie {
public:
    Urbana():Statie(){}
    ~Urbana(){}
    Urbana(string sir_adresa, vector<string>sir, string sir_nume):Statie( sir_adresa, sir,  sir_nume){}
    Urbana(const Urbana &ob):Statie(ob){}
    string getType() const override{return "urbana";}
    string returnCode() const override {
        string numar;
        numar = to_string(numar_de_ordine);
        return "SU-"+numar;
    }
    void afisare() const override {
        cout<<"Numele Statiei: "<<nume<<endl;
        cout<<"Adresa: "<<adresa<<endl;
        cout<<"Autobuze care trec prin statie: ";
        int i;
        for (i=0; i<autobuze.size();i++)
            cout<<autobuze[i]<<", ";
        cout<<endl;
        cout<<"Codul statie: "<<returnCode()<<endl;
        cout<<"Numarul de ordine: "<<numar_de_ordine<<endl;
        cout<<"Tipul statiei: urbana"<<endl;

    }
};

class ExtraUrbana: public Statie {
public:
    ExtraUrbana():Statie(){}
    ~ExtraUrbana(){}
    ExtraUrbana(string sir_adresa, vector<string>sir, string sir_nume):Statie( sir_adresa, sir,  sir_nume){}
    ExtraUrbana(const Urbana &ob):Statie(ob){}
    string getType() const override{return "extraurbana";}

    string returnCode() const override {
        string numar;
        numar = to_string(numar_de_ordine);
        return "SE-"+numar;
    }
    void afisare() const override {
        cout<<"Numele Statiei: "<<nume<<endl;
        cout<<"Adresa: "<<adresa<<endl;
        cout<<"Autobuze care trec prin statie: ";
        int i;
        for (i=0; i<autobuze.size();i++)
            cout<<autobuze[i]<<", ";
        cout<<endl;
        cout<<"Codul statie: "<<returnCode()<<endl;
        cout<<"Numarul de ordine: "<<numar_de_ordine<<endl;
        cout<<"Tipul statiei: extraurbana"<<endl;

    }
};

class Meniu {
    vector<Statie*>statii;
public:
    Meniu(){}
    ~Meniu() {
        for (auto i:statii)
            delete i;
    }
    void AdaugaStatie() {
        string sir_adresa,   sir_nume;

         vector<string>sir;
        string autobuz;
        int nr;
        cout<<"INTRODUCETI"<<endl;
        cout<<"Adresa: ";
        cin>>sir_adresa;
        cout<<"Nume statie: ";
        cin>>sir_nume;
        cout<<"Cate autobuze vreti sa treaca prin aceasta statie: ";
        cin>>nr;
        for (int i = 1; i<= nr; i++) {
            cout<<"Cod autobuz: ";
            cin>>autobuz;
            sir.push_back(autobuz);
        }
       int a;
        cout<<"Doriti ca statia sa fie urbana(1) sau extraurbana(2): ";
        cin>>a;
        if (a==1)
            statii.push_back(new Urbana(sir_adresa,sir, sir_nume ));
        else
            statii.push_back(new ExtraUrbana(sir_adresa,sir, sir_nume ));
    }
    void AfisareDetalii(string sir) {
        if (statii.size()==0)
            throw Insuficientstations();
        else {
            for (auto i:statii)
                if (i->getAdress()==sir || i->getNume()==sir || i->returnCode()==sir)
                    i->afisare();
        }

    }
    void AfisareStatiiAutobuz(string cod_autobuz) {
        for (auto i:statii) {
            vector<string> sir;
            sir = i->getAutobuze();
            for (auto j:sir)
                if (j==cod_autobuz) {
                    i->afisare();
                    break;
                }
        }
    }
    void afisareStatii() {
        for (int i  = 0 ; i<statii.size();i++) {
            cout<<i+1<<". ";
            statii[i]->afisare();
        }

    }
    int AutobuzComun(int indice1, int indice2) {
        vector<string> sir1;
        vector<string>sir2;
        sir1 = statii[indice1]->getAutobuze();
        sir2 = statii[indice2]->getAutobuze();
        for (auto i:sir1)
            for (auto j:sir2)
                if (i==j)
                    return 1;
        return 0;
    }
    float Pret(int indice1, int indice2) {
        float pret = 2;
        if (statii[indice1]->getType()=="urbana" && statii[indice2]->getType()=="urbana" && !AutobuzComun(indice1, indice2))
            pret = pret + 15*pret/100;
        else
            if (statii[indice1]->getType()=="extraurbana" && statii[indice2]->getType()=="extraurbana" && AutobuzComun(indice1, indice2))
                pret = pret + 20*pret/100;
        else
            if (statii[indice1]->getType()=="extraurbana" && statii[indice2]->getType()=="extraurbana" && AutobuzComun(indice1, indice2))
                pret = pret + 25*pret/100;
        else
            if (statii[indice1]->getType()!= statii[indice2]->getType() && AutobuzComun(indice1, indice2))
                pret = pret + 30*pret/100;
        else
            if (statii[indice1]->getType()!= statii[indice2]->getType() && !AutobuzComun(indice1, indice2))
                pret = pret + 40*pret/100;
        return pret;
    }
};
int main() {
    Meniu meniu;
    int choice;
    cout<<"1.Adaugati o statie"<<endl;
    cout<<"2. Afisati detalii strada"<<endl;
    cout<<"3. Afisati statiile prin care trece un autobuz"<<endl;
    cout<<"4. Pretul dintre 2 statii"<<endl;
    cout<<"0.Exit"<<endl;
    cin>>choice;
    while (choice!=0) {
        if (choice == 1)
            meniu.AdaugaStatie();
        else
            if (choice == 2) {
                string sir;
                cout<<"Ingtroduceti datele unei strazi(nume,adresa sau cod): ";
                cin>>sir;
               try{ meniu.AfisareDetalii(sir);}
                catch (Insuficientstations& e){cout<<e.what()<<endl;}
            }
        else
            if (choice == 3) {
                string cod_autobuz;
                cout<<"introduceti cod autobuz: ";
                cin>>cod_autobuz;
                meniu.AfisareStatiiAutobuz(cod_autobuz);
            }
        else
            if (choice == 4) {
                meniu.afisareStatii();
                int indice1, indice2;
                cout<<"Selectati indicii a doua strazi: ";
                cin>>indice1>>indice2;
                cout<<meniu.Pret(indice1-1,indice2-1)<<endl;
            }
        cout<<"1.Adaugati o statie"<<endl;
        cout<<"2. Afisati detalii strada"<<endl;
        cout<<"3. Afisati statiile prin care trece un autobuz"<<endl;
        cout<<"4. Pretul dintre 2 statii"<<endl;
        cout<<"0.Exit"<<endl;
        cin>>choice;
    }

    return 0;
}

// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.