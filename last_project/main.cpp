#include <iostream>
#include<string>
#include<vector>
#include<cstring>
#include<memory>
class Animal{
protected:
    std::string denumire;
    std::string ip;
    float greutate;
    static int nr_animale;
    int nr_picioare;
    int putere;
public:
    Animal():denumire("necunoscut"),ip("necunoscut"), greutate(0), nr_picioare(0),putere(0){nr_animale++;}
    Animal(std::string sir_denumire,std::string sir_ip, int val_greutate, int val_picioare, int val_putere):denumire(sir_denumire),ip(sir_ip), greutate(val_greutate), nr_picioare(val_picioare), putere(val_putere){nr_animale++;}
    virtual ~Animal(){nr_animale--;}
    Animal(const Animal &ob){
        denumire = ob.denumire;
        ip = ob.ip;
        greutate = ob.greutate;
        nr_picioare = ob.nr_picioare;
        putere = ob.putere;
    }
    std::string get_denumire() const{return denumire;}
    float get_greutate() const{return greutate;}
    std::string get_ip(){return ip;}
    int get_nr_picioare(){return nr_picioare;}
    int get_putere() const{return putere;}
    void set_denumire(std::string sir){denumire = sir;}
    void set_ip(std::string sir){ip = sir;}
    void set_greutate(int val){greutate = val;}
    static int get_nr_animale(){return nr_animale;}
    virtual std::string tip() const = 0;
    virtual std::string sound() const = 0;
    virtual void afisare(std::ostream& os) const = 0;
};
int Animal::nr_animale = 0;

class Carnivor:virtual public Animal{
protected:
    int nr_gheare;
    const std::string consumatie = "carne";
public:
    Carnivor():Animal(), nr_gheare(0){}
    Carnivor(std::string sir_denumire,std::string sir_ip, int val_greutate, int val_picioare,int val_nr_gheare, int val_putere):Animal(sir_denumire,sir_ip, val_greutate, val_picioare, val_putere),nr_gheare(val_nr_gheare){}
    virtual ~Carnivor(){}
    Carnivor(const Carnivor& ob):Animal(ob){nr_gheare = ob.nr_gheare;}
    int get_nr_gheare(){return nr_gheare;}
    void set_nr_gheare(int val){nr_gheare = val;}
    friend std::istream& operator >>(std::istream& is, Carnivor &ob);
    friend std::ostream& operator <<(std::ostream& os,const Carnivor &ob);
    std::string get_consumatie(){return consumatie;}
    std::string tip() const override{return "carnivor";}
    std::string sound() const override{return "roar";}
    void afisare(std::ostream& os) const override {
    os<<"denumire: "<<denumire<<"\n";
    os<<"id: "<<ip<<"\n";
    os<<"tip: "<<tip()<<"\n";
    os<<"greutate: "<<greutate<<" kg"<<"\n";
    os<<"numar picioare: "<<nr_picioare<<"\n";
    os<<"numar gheare: "<<nr_gheare<<"\n";
    os<<"hrana: "<<consumatie<<"\n";
    os<<"putere: "<<putere<<"\n";
}
};
std::istream& operator >>(std::istream& is, Carnivor &ob){
    std::string nume, adresa;
    std::cout<<"denumire: ";
    is>>nume;
    try{//verificam daca numele introdus contine cifre
        std::string sir="0123456789";
        int nr_cifre = 0;
        int i;
        for(i=0;i<nume.size();i++)
            if (sir.find(nume[i]) != std::string::npos)
                nr_cifre++;
        if(nr_cifre==0)
            ob.denumire = nume;
        else
            throw(nume);
    }
    catch(std::string name){std::cout<<"denumirea contine cifre ceea ce nu este posibil \n";}
    std::cout<<"id: ";
    is>>adresa;
    try{//se verifica daca ip-ul contine doar 0, adica daca este invalid
        int nr_zero = 0;
        int i = 0;
        for(i=0;i<adresa.size();i++)
            if(adresa[i]=='0')
                nr_zero++;
        if(nr_zero != adresa.size())
            {std::cout<<"ip-ul este valid \n";
                ob.ip = adresa;}
        else
            throw(adresa);
    }
    catch(std::string sir){std::cout<<"ip-ul este invalid \n";}
    std::cout<<"greutate: ";
    is>>ob.greutate;
    std::cout<<"numar picioare: ";
    is>>ob.nr_picioare;
    std::cout<<"numar gheare: ";
    is>>ob.nr_gheare;
    std::cout<<"putere: ";
    is>>ob.putere;
    return is;
}
std::ostream& operator <<(std::ostream& os,const Carnivor &ob){
    os<<"denumire: "<<ob.denumire<<"\n";
    os<<"id: "<<ob.ip<<"\n";
    os<<"tip: "<<ob.tip()<<"\n";
    os<<"greutate: "<<ob.greutate<<" kg"<<"\n";
    os<<"numar picioare: "<<ob.nr_picioare<<"\n";
    os<<"numar gheare: "<<ob.nr_gheare<<"\n";
    os<<"hrana: "<<ob.consumatie<<"\n";
    os<<"putere: "<<ob.putere<<"\n";
    return os;
}

class Erbivor: virtual public Animal{
protected:
    const std::string mancare = "iarba";
public:
    Erbivor():Animal(){}
    Erbivor(std::string sir_denumire,std::string sir_ip, int val_greutate, int val_picioare, int val_putere):Animal(sir_denumire,sir_ip,val_greutate,val_picioare,val_putere){}
    virtual ~Erbivor(){}
    Erbivor(const Erbivor& ob):Animal(ob){}
    friend std::istream& operator >>(std::istream& is, Erbivor &ob);
    friend std::ostream& operator <<(std::ostream& os,const Erbivor &ob);
    std::string get_mancare(){return mancare;}
    std::string tip() const override{return "erbivor";}
    std::string sound() const override{return "mof mof";}
    void afisare(std::ostream& os) const override {
    os<<"denumire: "<<denumire<<"\n";
    os<<"id: "<<ip<<"\n";
    os<<"tip: "<<tip()<<"\n";
    os<<"greutate: "<<greutate<<" kg"<<"\n";
    os<<"numar picioare: "<<nr_picioare<<"\n";
    os<<"hrana: "<<mancare<<"\n";
    os<<"putere: "<<putere<<"\n";
}
};
std::istream& operator >>(std::istream& is, Erbivor &ob){
   std::string nume, adresa;
    std::cout<<"denumire: ";
    is>>nume;
    try{
        std::string sir="0123456789";
        int nr_cifre = 0;
        int i;
        for(i=0;i<nume.size();i++)
            if (sir.find(nume[i]) != std::string::npos)
                nr_cifre++;
        if(nr_cifre==0)
            ob.denumire = nume;
        else
            throw(nume);
    }
    catch(std::string name){std::cout<<"denumirea contine cifre ceea ce nu este posibil \n";}
    std::cout<<"id: ";
    is>>adresa;
    try{
        int nr_zero = 0;
        int i = 0;
        for(i=0;i<adresa.size();i++)
            if(adresa[i]=='0')
                nr_zero++;
        if(nr_zero != adresa.size())
            {std::cout<<"ip-ul este valid \n";
                ob.ip = adresa;}
        else
            throw(adresa);
    }
    catch(std::string sir){std::cout<<"ip-ul este invalid \n";
    }
    std::cout<<"greutate: ";
    is>>ob.greutate;
    std::cout<<"numar picioare: ";
    is>>ob.nr_picioare;
    std::cout<<"putere: ";
    is>>ob.putere;
    return is;
}
std::ostream& operator <<(std::ostream& os,const Erbivor &ob){
    os<<"denumire: "<<ob.denumire<<"\n";
    os<<"id: "<<ob.ip<<"\n";
    os<<"tip: "<<ob.tip()<<"\n";
    os<<"greutate: "<<ob.greutate<<" kg"<<"\n";
    os<<"numar picioare: "<<ob.nr_picioare<<"\n";
    os<<"hrana: "<<ob.mancare<<"\n";
    os<<"putere: "<<ob.putere<<"\n";
    return os;
}

class Omnivor: public Carnivor, public Erbivor{
public:
    Omnivor():Animal(),Carnivor(), Erbivor(){}
    Omnivor(std::string sir_denumire,std::string sir_ip, int val_greutate, int val_picioare,int val_nr_gheare, int val_putere):Animal(sir_denumire,sir_ip,val_greutate,val_picioare,val_putere),Carnivor(sir_denumire,sir_ip,val_greutate,val_picioare,val_nr_gheare,val_putere),Erbivor(sir_denumire,sir_ip,val_greutate,val_picioare,val_putere){}
    ~Omnivor(){}
    Omnivor(const Omnivor& ob):Animal(ob),Carnivor(ob),Erbivor(ob){}
    friend std::istream& operator >>(std::istream& is, Omnivor &ob);
    friend std::ostream& operator <<(std::ostream& os,const Omnivor &ob);
    std::string tip() const override{return "omnivor";}
    std::string sound() const override{return "hrr";}
    void afisare(std::ostream& os) const override {
    os<<"denumire: "<<denumire<<"\n";
    os<<"id: "<<ip<<"\n";
    os<<"tip: "<<tip()<<"\n";
    os<<"greutate: "<<greutate<<" kg"<<"\n";
    os<<"numar picioare: "<<nr_picioare<<"\n";
    os<<"numar gheare: "<<nr_gheare<<"\n";
    os<<"hrana: "<<consumatie<<" si "<<mancare<<"\n";
    os<<"putere: "<<putere<<"\n";
}

};
std::istream& operator >>(std::istream& is, Omnivor &ob){

    std::string nume, adresa;
    std::cout<<"denumire: ";
    is>>nume;
    try{
        std::string sir="0123456789";
        int nr_cifre = 0;
        int i;
        for(i=0;i<nume.size();i++)
            if (sir.find(nume[i]) != std::string::npos)
                nr_cifre++;
        if(nr_cifre==0)
            ob.denumire = nume;
        else
            throw(nume);
    }
    catch(std::string name){std::cout<<"denumirea contine cifre ceea ce nu este posibil \n";}
    std::cout<<"id: ";
    is>>adresa;
    try{
        int nr_zero = 0;
        int i = 0;
        for(i=0;i<adresa.size();i++)
            if(adresa[i]=='0')
                nr_zero++;
        if(nr_zero != adresa.size())
            {std::cout<<"ip-ul este valid \n";
                ob.ip = adresa;}
        else
            throw(adresa);
    }
    catch(std::string sir){std::cout<<"ip-ul este invalid \n";
    }
    std::cout<<"greutate: ";
    is>>ob.greutate;
    std::cout<<"numar picioare: ";
    is>>ob.nr_picioare;
    std::cout<<"numar gheare: ";
    is>>ob.nr_gheare;
    std::cout<<"putere: ";
    is>>ob.putere;
    return is;
}

std::ostream& operator <<(std::ostream& os,const Omnivor &ob){
    os<<"denumire: "<<ob.denumire<<"\n";
    os<<"id: "<<ob.ip<<"\n";
    os<<"tip: "<<ob.tip()<<"\n";
    os<<"greutate: "<<ob.greutate<<" kg"<<"\n";
    os<<"numar picioare: "<<ob.nr_picioare<<"\n";
    os<<"numar gheare: "<<ob.nr_gheare<<"\n";
    os<<"hrana: "<<ob.consumatie<<" si "<<ob.mancare<<"\n";
    os<<"putere: "<<ob.putere<<"\n";
    return os;
}

class Pasare{
protected:
    std::string name;
    std::string culoare;
    static int nr_pasari;
public:
    Pasare():name("necunoscut"),culoare("necunoscuta"){nr_pasari++;}
    Pasare(std::string sir_name, std::string sir_culoare):name(sir_name),culoare(sir_culoare){nr_pasari++;}
    virtual ~Pasare(){}
    Pasare(const Pasare& ob):name(ob.name), culoare(ob.culoare){}
    virtual std::string type() const {return "tipul este necunoscut \n";}
    friend std::ostream& operator<<(std::ostream& os,const Pasare& ob);
    virtual void show(std::ostream& os) const = 0;
};
int Pasare::nr_pasari = 0;

std::ostream& operator<<(std::ostream& os,const Pasare& ob){
    os<<"nume: "<<ob.name<<"\n";
    os<<"culoare: "<<ob.culoare<<"\n";
    return os;
}

class Pasare_nezburatoare:public Pasare{
private:
    float viteza_de_alergat;
public:
    Pasare_nezburatoare():Pasare(), viteza_de_alergat(0){}
    Pasare_nezburatoare(std::string sir_name, std::string sir_culoare, float viteza):Pasare(sir_name,sir_culoare),viteza_de_alergat(viteza){}
    ~Pasare_nezburatoare(){}
    Pasare_nezburatoare(const Pasare_nezburatoare &ob):Pasare(ob.name,ob.culoare),viteza_de_alergat(ob.viteza_de_alergat){}
    std::string type() const override{return "Pasare nezburatoare ";}
    friend std::istream& operator>>(std::istream& is, Pasare_nezburatoare &ob);
    friend std::ostream& operator<<(std::ostream & os,const Pasare_nezburatoare &ob);
    void show(std::ostream& os) const override {
    os<<"nume: "<<name<<"\n";
    os<<"tip: "<<type()<<"\n";
    os<<"culoare: "<<culoare<<"\n";
    os<<"viteza de alergat: "<<viteza_de_alergat<<"\n";
}
};
std::istream& operator>>(std::istream& is, Pasare_nezburatoare &ob){
    std::string nume;
    std::cout<<"nume: ";
    is>>nume;
    try{
        std::string sir="0123456789";
        int nr_cifre = 0;
        int i;
        for(i=0;i<nume.size();i++)
            if (sir.find(nume[i]) != std::string::npos)
                nr_cifre++;
        if(nr_cifre==0)
            ob.name = nume;
        else
            throw(nume);
    }
    catch(std::string name){std::cout<<"denumirea contine cifre ceea ce nu este posibil \n";}
    std::cout<<"culoare: ";
    is>>ob.culoare;
    std::cout<<"viteza de alergare: ";
    is>>ob.viteza_de_alergat;
    return is;
}

std::ostream& operator<<(std::ostream& os, const Pasare_nezburatoare &ob){
    os<<"nume: "<<ob.name<<std::endl;
    os<<"culoare: "<<ob.culoare<<std::endl;
    os<<"tip: "<<ob.type()<<std::endl;
    os<<"viteza de alergare: "<<ob.viteza_de_alergat<<" km/h \n";
    return os;
}

class Pasare_zburatoare: public Pasare{
private:
    float viteza_de_zbor;
public:
    Pasare_zburatoare():Pasare(),viteza_de_zbor(0){}
    Pasare_zburatoare(std::string sir_name, std::string sir_culoare, float viteza):Pasare(sir_name,sir_culoare),viteza_de_zbor(viteza){}
    ~Pasare_zburatoare(){}
    Pasare_zburatoare(const Pasare_zburatoare &ob):Pasare(ob.name,ob.culoare),viteza_de_zbor(ob.viteza_de_zbor){}
    std::string type()const override{return "Pasare zburatoare ";}
    friend std::istream& operator>>(std::istream& is, Pasare_zburatoare &ob);
    friend std::ostream& operator<<(std::ostream & os,const Pasare_zburatoare &ob);
    void show(std::ostream& os) const override {
    os<<"nume: "<<name<<"\n";
    os<<"tip: "<<type()<<"\n";
    os<<"culoare: "<<culoare<<"\n";
    os<<"viteza de zbor: "<<viteza_de_zbor<<"\n";
}
};

std::istream& operator>>(std::istream& is, Pasare_zburatoare &ob){
    std::string nume;
    std::cout<<"nume: ";
    is>>nume;
    try{
        std::string sir="0123456789";
        int nr_cifre = 0;
        int i;
        for(i=0;i<nume.size();i++)
            if (sir.find(nume[i]) != std::string::npos)
                nr_cifre++;
        if(nr_cifre==0)
            ob.name = nume;
        else
            throw(nume);
    }
    catch(std::string name){std::cout<<"denumirea contine cifre ceea ce nu este posibil \n";}
    std::cout<<"culoare: ";
    is>>ob.culoare;
    std::cout<<"viteza de zbor: ";
    is>>ob.viteza_de_zbor;
    return is;
}

std::ostream& operator<<(std::ostream& os, const Pasare_zburatoare &ob){
    os<<"nume: "<<ob.name<<std::endl;
    os<<"culoare: "<<ob.culoare<<std::endl;
    os<<"tip: "<<ob.type()<<std::endl;
    os<<"viteza de zbor: "<<ob.viteza_de_zbor<<" km/h \n";
    return os;
}

    template<typename T1, typename T2>
        std::string comparaPutere(const T1& a, const T2& b) {
            if (a.get_putere() > b.get_putere())
                return a.get_denumire() + " are puterea mai mare. \n";
            else if (a.get_putere() < b.get_putere())
                return b.get_denumire() + " are puterea mai mare. \n";
            else
                return "Au putere egala. \n";
    }

    template<typename T1, typename T2>
        std::string comparaGreutate(const T1& a, const T2& b) {
            if (a.get_greutate() > b.get_greutate())
                return a.get_denumire() + " este mai greu. \n";
            else if (a.get_greutate() < b.get_greutate())
                return b.get_denumire() + " este mai greu. \n";
            else
                return "Au greutate egala. \n";
    }

class Zoo{
private:
        std::vector<Animal*>v;
        std::vector<Pasare*>w;
        Zoo(){}
        static Zoo* instance;
public:
    static Zoo* getInstance(){
        if(instance==NULL)
            instance = new Zoo();
        return instance;
    }

    ~Zoo(){
        for (auto animal : v) delete animal;
        for(auto pasare : w) delete pasare;
        delete instance;
    }

    void adaugare_animal_carnivor(const Carnivor &ob){v.push_back(new Carnivor(ob));}//upcasting
    void adaugare_animal_erbivor(const Erbivor &ob){v.push_back(new Erbivor(ob));}//upcasting
    void adaugare_animal_omnivor(const Omnivor &ob){v.push_back(new Omnivor(ob));}//upcasting
    void afisare_animale();
    void sterge_animal(int i){

        v.erase(v.begin()+i-1);
}
   void Lupta(int a, int b){
    if(a > 0 && b > 0 && a <= (int)v.size() && b <= (int)v.size()) {
        std::cout << comparaPutere(*v[a - 1], *v[b - 1]);
    } else {
        std::cout << "Index invalid pentru animale.\n";
    }
}
    void Greutate(int a, int b){
    if(a > 0 && b > 0 && a <= (int)v.size() && b <= (int)v.size()) {
        std::cout << comparaGreutate(*v[a - 1], *v[b - 1]);
    } else {
        std::cout << "Index invalid pentru animale.\n";
    }
}
    void adauga_pasare_nezburatoare(const Pasare_nezburatoare& ob){w.push_back(new Pasare_nezburatoare(ob));}//upcasting
    void adauga_pasare_zburatoare(const Pasare_zburatoare& ob){w.push_back(new Pasare_zburatoare(ob));}//upcasting
    void sterge_pasare(int i){

        w.erase(w.begin()+i-1);}
    void afisare_pasari();
};
void Zoo :: afisare_animale(){
    int i;
    if(v.size()==0)
        std::cout<<"nu exista nici un animal la zoo \n";
    else
        for(i=0;i<v.size();i++)
            {
                std::cout<<i+1<<". ";
                v[i]->afisare(std::cout);
                std::cout<<std::endl;
            }
}
Zoo* Zoo::instance = nullptr;
void Zoo :: afisare_pasari(){
    int i;
    if(w.size()==0)
        std::cout<<"nu exista nici un animal la zoo \n";
    else
        for(i=0;i<w.size();i++)
            {
                std::cout<<i+1<<". ";
                w[i]->show(std::cout);
                std::cout<<std::endl;
            }
}


class Peste{
protected:
    std::string culoare;

public:
    Peste():culoare("necunoscuta"){}
    virtual std::string getCuloare() const {return culoare;}
    virtual double getGreutate()const = 0;
    virtual ~Peste(){}
};

class PesteClovn:public Peste{
public:
    PesteClovn(){culoare = "portocaliu";}
    double getGreutate() const override{return 10.0;}
    ~PesteClovn(){}
};

class PesteDecorator: public Peste{
protected:
        std::unique_ptr<Peste> peste;
public:
    PesteDecorator(std::unique_ptr<Peste>p):peste(std::move(p)){}
    virtual ~PesteDecorator() = default;
};

class PesteClovnCopil:public PesteDecorator{
public:
        PesteClovnCopil(std::unique_ptr<Peste>p):PesteDecorator(std::move(p)){}
        std::string getCuloare() const override{return peste->getCuloare()+", dungi albe";}
        double getGreutate() const override{return peste->getGreutate() - 5.00;}
        ~PesteClovnCopil(){}
};

class PesteClovnAdult:public PesteDecorator{
public:
        PesteClovnAdult(std::unique_ptr<Peste>p):PesteDecorator(std::move(p)){}
        std::string getCuloare() const override{return peste->getCuloare()+", dungi albe cu negru";}
        double getGreutate() const override{return peste->getGreutate() + 5.00;}
        ~PesteClovnAdult(){}
};

class Acvariu{
    std::vector<std::unique_ptr <Peste>> v;
    static Acvariu* instanta;
    Acvariu(){}
public:
    static Acvariu* getInstanta(){
        if(instanta == nullptr)
            instanta = new Acvariu();
        return instanta;
    }
void adaugaPeste(std::unique_ptr<Peste> p) {
        v.push_back(std::move(p));
    }

    void afiseazaPesti() const {
        for (const auto& p : v) {
            std::cout << "Culoare: " << p->getCuloare()
                      << ", Greutate: " << p->getGreutate() << "\n";
        }
    }

};

Acvariu* Acvariu::instanta = nullptr;

class Reptila {
protected:
    std::unique_ptr<Reptila> urmatoarea;

public:
    void seteazaUrmatoarea(std::unique_ptr<Reptila> urm) {
        urmatoarea = std::move(urm);
    }

    virtual void proceseazaHrana(const std::string& hrana) {
        if (urmatoarea)
            urmatoarea->proceseazaHrana(hrana);
        else
            std::cout << "Nicio reptilă nu poate consuma: " << hrana << "\n";
    }

    virtual ~Reptila() = default;
};

class Soparla : public Reptila {
public:
    void proceseazaHrana(const std::string& hrana) override {
        if (hrana == "insecte") {
            std::cout << "Soparla mananca insecte.\n";
        } else {
            Reptila::proceseazaHrana(hrana);
        }
    }
};

class BroascaTestoasa : public Reptila {
public:
    void proceseazaHrana(const std::string& hrana) override {
        if (hrana == "frunze") {
            std::cout << "Broasca testoasa mananca frunze.\n";
        } else {
            Reptila::proceseazaHrana(hrana);
        }
    }
};

class Sarpe : public Reptila {
public:
    void proceseazaHrana(const std::string& hrana) override {
        if (hrana == "rozatoare") {
            std::cout << "Sarpele mananca rozatoare.\n";
        } else {
            Reptila::proceseazaHrana(hrana);
        }
    }
};


int main()
{
    Zoo* zoo = Zoo::getInstance();
    Acvariu* acvariu = Acvariu::getInstanta();
    auto soparla = std::make_unique<Soparla>();
    auto broasca = std::make_unique<BroascaTestoasa>();
    auto sarpe = std::make_unique<Sarpe>();
    broasca->seteazaUrmatoarea(std::move(sarpe));
    soparla->seteazaUrmatoarea(std::move(broasca));
    std::cout<<"1.Adauga un animal carnivor la zoo \n";
    std::cout<<"2.Adauga un animal erbivor la zoo \n";
    std::cout<<"3.Adauga un animal omnivor la zoo \n";
    std::cout<<"4.Afiseaza lista cu animalele de la gradina zoologica \n";
    std::cout<<"5.Sterge un animal de la gradina zoologica \n";
    std::cout<<"6.Adauga o pasare nezburatoare la zoo \n";
    std::cout<<"7.Adauga o pasare zburatoare la zoo \n";
    std::cout<<"8.Afiseaza lista cu pasarile de la gradina zoologica \n";
    std::cout<<"9.Sterge o pasare de la gradina zoologica \n";
    std::cout<<"10.Adauga peste in acvariu \n";
    std::cout<<"11.Afiseaza lista pestilor \n";
    std::cout<<"12.Hraneste reptilele \n";
    std::cout<<"13.Lupta animale \n";
    std::cout<<"14.Compara greutatea dintre 2 animale \n";
    std::cout<<"0.Exit \n";
    int a;
    std::cin>>a;
    while(a!=0){
        if(a==1){
            Carnivor ob;
            std::cin>>ob;
            zoo->adaugare_animal_carnivor(ob);
        }
        if(a==2){
            Erbivor ob1;
            std::cin>>ob1;
            zoo->adaugare_animal_erbivor(ob1);
        }
        if(a==3){
            Omnivor ob2;
            std::cin>>ob2;
            zoo->adaugare_animal_omnivor(ob2);
        }
        if(a==4){zoo->afisare_animale();}
        if(a==5){
            zoo->afisare_animale();
            std::cout<<"Selectati numarul unui animal \n";
            int b;
            std::cin>>b;
            zoo->sterge_animal(b-1);
        }
        if(a==6){
            Pasare_nezburatoare ob3;
            std::cin>>ob3;
            zoo->adauga_pasare_nezburatoare(ob3);
        }
        if(a==7){
            Pasare_zburatoare ob4;
            std::cin>>ob4;
            zoo->adauga_pasare_zburatoare(ob4);
        }
        if(a==8){zoo->afisare_pasari();}
        if(a==9){
            zoo->afisare_pasari();
            std::cout<<"Selectati numarul unui animal \n";
            int c;
            std::cin>>c;
            zoo->sterge_pasare(c-1);
        }
        if(a==10){
            int b;
            std::cout<<"ce peste ati dori sa introduceti \n";
            std::cout<<"1.Copil \n";
            std::cout<<"2.Adult \n";
            std::cin>>b;
            if(b==1){
                std::unique_ptr<Peste> pesteCopil = std::make_unique<PesteClovnCopil>(std::make_unique<PesteClovn>());
                acvariu->adaugaPeste(std::move(pesteCopil));
            }
            else
                if(b==2){
                    std::unique_ptr<Peste> pesteAdult = std::make_unique<PesteClovnAdult>(std::make_unique<PesteClovn>());
                    acvariu->adaugaPeste(std::move(pesteAdult));
            }
        }
        if(a==11){acvariu->afiseazaPesti();}
        if(a==12){
            std::string sir;
            std::cout<<"Introduceti hrana pe care vreti sa o oferiti reptilelor. Va aducem la cunostina ca soparlele mananca insecte, testoasele mananca frunze, iar serpii rozatoare \n";
            std::cin>>sir;
            soparla->proceseazaHrana(sir);

        }
        if(a==13){
            zoo->afisare_animale();
            std::cout<<"Selecteaza indexii a doua animale \n";
            int a, b;
            std::cin>>a;
            std::cin>>b;
            zoo->Lupta(a,b);
        }
        if(a==14){
            zoo->afisare_animale();
            std::cout<<"Selecteaza indexii a doua animale \n";
            int a, b;
            std::cin>>a;
            std::cin>>b;
            zoo->Greutate(a,b);
        }
        std::cout<<"1.Adauga un animal carnivor la zoo \n";
        std::cout<<"2.Adauga un animal erbivor la zoo \n";
        std::cout<<"3.Adauga un animal omnivor la zoo \n";
        std::cout<<"4.Afiseaza lista cu animalele de la gradina zoologica \n";
        std::cout<<"5.Sterge un animal de la gradina zoologica \n";
        std::cout<<"6.Adauga o pasare nezburatoare la zoo \n";
        std::cout<<"7.Adauga o pasare zburatoare la zoo \n";
        std::cout<<"8.Afiseaza lista cu pasarile de la gradina zoologica \n";
        std::cout<<"9.Sterge o pasare de la gradina zoologica \n";
        std::cout<<"10.Adauga peste in acvariu \n";
        std::cout<<"11.Afiseaza lista pestilor \n";
        std::cout<<"12.Hraneste reptilele \n";
        std::cout<<"13.Lupta animale \n";
        std::cout<<"14.Compara greutatea dintre 2 animale \n";
        std::cout<<"0.Exit \n";
        std::cin>>a;
    }

    return 0;
}
