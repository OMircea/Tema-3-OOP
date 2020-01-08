#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <typeinfo>

using namespace std;

class ContBancar
{
private:
    string detinator;
    int data_deschidere;
    int sold;

public:
    ContBancar();
    ContBancar(string, int, int);
    friend istream& operator>>(istream&, ContBancar&);
    friend ostream& operator<<(ostream&, ContBancar&);
    void operator=(ContBancar CB);
    virtual void citire();
    virtual void afisare();
    int getsold();
    void setsold(int v);
    ~ContBancar();
};

ContBancar::ContBancar()
{
    detinator = " ";
    data_deschidere = 0;
    sold = 0;
    try {
        if(typeid(data_deschidere).name()!=typeid(int).name())
            throw data_deschidere;
        if(typeid(sold).name()!=typeid(int).name())
            throw sold;
    }
    catch (int a)
    {
        cout<<"Diferit";
    }
}

ContBancar::ContBancar(string d, int dt, int s)
{
    detinator = d;
    data_deschidere = dt;
    sold = s;
}

istream&operator>>(istream& in, ContBancar& CB)
{
    in>>CB.detinator>>CB.data_deschidere>>CB.sold;
    return in;
}

ostream&operator<<(ostream& out, ContBancar& CB)
{
    out<<CB.detinator<<" "<<CB.data_deschidere<<" "<<CB.sold<<endl;
    return out;
}

void ContBancar::operator=(ContBancar CB)
{
    detinator = CB.detinator;
    data_deschidere = CB.data_deschidere;
    sold = CB.sold;
}

void ContBancar::citire()
{
    cin>>detinator>>data_deschidere>>sold;
}

void ContBancar::afisare()
{
    cout<<detinator<<" "<<data_deschidere<<" "<<sold<<endl;
}

ContBancar::~ContBancar()
{
    detinator = " ";
    data_deschidere = 0;
    sold = 0;
}

int ContBancar::getsold()
{
    return sold;
}

void ContBancar::setsold(int v)
{
    sold = v;
}

class ContEconomii : public ContBancar
{
private:
    int rata_dobanda;
    int istoric[100];
    int c;

public:
    ContEconomii();
    ContEconomii(string d, int dt, int s, int rd):ContBancar(d, dt, s)
    {
        if(typeid(rd).name()=="i")
        {
            rata_dobanda = rd;
            c = 1;
            istoric[c] = s;
            for(int i = 2; i<100; i++)
                istoric[i] = INT_MAX;
        }
    };
    friend istream& operator>>(istream&, ContEconomii&);
    friend ostream& operator<<(ostream&, ContEconomii&);
    void operator=(ContEconomii CE);
    void citire();
    void afisare();
    void specializare();

    void depunere(int);
    void retragere(int);

    ~ContEconomii();
};

ContEconomii::ContEconomii()
{
    ContBancar();
    rata_dobanda = 0;
    c=0;
    for(int i=0; i<100; i++)
        istoric[i] = INT_MAX;
}

istream& operator>>(istream& in, ContEconomii& CE)
{
    in>>dynamic_cast<ContBancar&>(CE);
    in>>CE.rata_dobanda;
    return in;
}

ostream& operator<<(ostream& out, ContEconomii& CE)
{
    out<<CE.rata_dobanda;
    return out;
}

void ContEconomii::depunere(int val)
{
    int vnou;
    c++;
    vnou = getsold();
    vnou+=val;
    setsold(vnou);
    istoric[c] = vnou;
}

void ContEconomii::retragere(int val)
{
    int vnou;
    c++;
    vnou = getsold();
    vnou-=val;
    setsold(vnou);
    istoric[c] = vnou;
}

void ContEconomii::citire()
{
    ContBancar::citire();
    cin>>rata_dobanda;
    c=1;
    istoric[c] = getsold();
    for(int i = 2; i<100; i++)
        istoric[i] = INT_MAX;
}

void ContEconomii::afisare()
{
    ContBancar::afisare();
    cout<<rata_dobanda<<endl;
    cout<<"Istoricul soldului: ";
    for(int i = 1; i <= c; i++)
        cout<<istoric[i]<<" ";
    cout<<endl;
}

ContEconomii::~ContEconomii()
{
    rata_dobanda = 0;
    c = 0;
    for(int i= 0 ; i>100; i++)
        istoric[i] = 0;
}

void ContEconomii::operator=(ContEconomii CE)
{
    rata_dobanda = CE.rata_dobanda;
    c=CE.c;
    for(int i=0; i<100; i++)
        istoric[i] = CE.istoric[i];
}

void ContEconomii::specializare()
{
    if(rata_dobanda==12)
        ContEconomii::afisare();
}

class ContCurent : public ContBancar
{
private:
    int nrTranzactiiGratuite;
    int nrTranzactiiCC;
    int pretTCC;
public:
    ContCurent();
    ContCurent(string d, int dt, int s, int g, int cc, int pretcc):
        ContBancar(d, dt, s)
    {
        nrTranzactiiGratuite = g;
        nrTranzactiiCC = cc;
        pretTCC = pretcc;
    }
    friend istream& operator>>(istream&, ContCurent&);
    friend ostream& operator<<(ostream&, ContCurent&);
    void operator=(ContCurent CC);

    void citire();
    void afisare();

    void depunere(int);
    void retragere(int);

    ~ContCurent();
};

ContCurent::ContCurent()
{
    ContBancar();
    nrTranzactiiGratuite = 0;
    nrTranzactiiCC = 0;
    pretTCC = 0;
}

istream& operator>>(istream& in, ContCurent& CC)
{
    in>>CC.nrTranzactiiGratuite>>CC.nrTranzactiiCC>>CC.pretTCC;
    return in;
}

ostream& operator<<(ostream& out, ContCurent& CC)
{
    out<<CC.nrTranzactiiGratuite<<" "<<CC.nrTranzactiiCC<<" "<<CC.pretTCC<<endl;
    return out;
}

void ContCurent::operator=(ContCurent CC)
{
    nrTranzactiiGratuite = CC.nrTranzactiiGratuite;
    nrTranzactiiCC = CC.nrTranzactiiCC;
    pretTCC = CC.pretTCC;
}

void ContCurent::citire()
{
    ContBancar::citire();
    cin>>nrTranzactiiGratuite>>nrTranzactiiCC>>pretTCC;
}

void ContCurent::afisare()
{
    ContBancar::afisare();
    cout<<endl;
    cout<<nrTranzactiiGratuite<<" "<<nrTranzactiiCC<<" "<<pretTCC;
    cout<<endl;
}

ContCurent::~ContCurent()
{
    nrTranzactiiGratuite = 0;
    nrTranzactiiCC = 0;
    pretTCC = 0;
}

void ContCurent::depunere(int val)
{
    int vnou = getsold();

    if(nrTranzactiiGratuite==0)
        if(nrTranzactiiCC == 0)
            cout<<"Depunerea nu se poate efectua intrucat nu exista tranzactii disponibile.";

    if(nrTranzactiiGratuite!=0)
    {
        nrTranzactiiGratuite--;
        vnou+=val;
        setsold(vnou);
        cout<<endl;
        cout<<"Am depus "<< val <<" in cont.";
    }

    if(nrTranzactiiGratuite==0)
        if(nrTranzactiiCC!=0)
        {
            nrTranzactiiCC--;
            vnou+=val;
            vnou-=pretTCC;
            setsold(vnou);
            cout<<endl;
            cout<<"Am depus "<< val <<" in cont contra unei sume de " << pretTCC <<".";
        }
}

void ContCurent::retragere(int val)
{
    int vnou = getsold();

    int opt;
    cout<<"Retragere normala - 1"<<endl;
    cout<<"Alta retragere (plata online), retragere de la alt bancomat, etc"<<endl;
    cin>>opt;
    cout<<endl;

    if(opt==1)
    {
        if(nrTranzactiiCC==0 && nrTranzactiiGratuite==0)
            cout<<"Retragerea nu se poate efectua intrucat nu exista tranzactii disponibile.";

        if(nrTranzactiiGratuite!=0)
        {
            nrTranzactiiGratuite--;
            vnou-=val;
            setsold(vnou);
            cout<<endl;
            cout<<"Am retras "<< val <<" din cont.";
        }

        if(nrTranzactiiGratuite==0 && nrTranzactiiCC!=0)
        {
            nrTranzactiiCC--;
            vnou=vnou-val-pretTCC;
            setsold(vnou);
            cout<<endl;
            cout<<"Am retras "<< val <<" din cont contra unei sume de " << pretTCC <<".";
        }
    }

    if(opt==2)
    {
        int comision = 5;
        if(nrTranzactiiCC==0 && nrTranzactiiGratuite==0)
            cout<<"Retragerea nu se poate efectua intrucat nu exista tranzactii disponibile.";

        if(nrTranzactiiGratuite!=0)
        {
            nrTranzactiiGratuite--;
            vnou=vnou-val-comision;
            setsold(vnou);
            cout<<endl;
            cout<<"Am retras "<< val <<" din cont impreuna cu un comision de "<<comision<<".";
        }

        if(nrTranzactiiGratuite==0 && nrTranzactiiCC!=0)
        {
            nrTranzactiiCC--;
            vnou=vnou-val-pretTCC-comision;
            setsold(vnou);
            cout<<endl;
            cout<<"Am retras "<< val <<" din cont contra unei sume de " << pretTCC <<", impreuna cu un comision de "<<comision<<".";
        }
    }
}

template <class T> class GestionareConturi
{
    static int d;
    int index;
    vector<T*>v;
public:
    int getindex() const
    {
        return index;
    };
    GestionareConturi();
    ~GestionareConturi();
    void operator+=(T cont)
    {
        v.push_back(cont);
    }
    GestionareConturi(const GestionareConturi&);
    GestionareConturi& operator=(const GestionareConturi&);
};

template <class T>
GestionareConturi<T>::GestionareConturi()
{
    index=0;
    v=NULL;
}

template <class T>
GestionareConturi<T>::~GestionareConturi()
{
    index = 0;
    v = NULL;
}

template <class T>
GestionareConturi<T>::GestionareConturi(const GestionareConturi &gc)
{
    d = gc.d;
    index=gc.index;
    v=gc.v;
}

template <class T>
GestionareConturi<T>&GestionareConturi<T>::operator=(const GestionareConturi &gc)
{
    d = gc.d;
    index=gc.index;
    v=gc.v;
}

int main()
{
    ContEconomii CE("Alex", 22042006, 50, 3);
    CE.depunere(30);
    CE.depunere(20);
    CE.depunere(55);
    CE.afisare();
    CE.retragere(20);
    CE.afisare();

    cout<<endl<<endl<<endl;


    ContCurent a("Andrei", 30042000, 50, 3, 3, 17);

    a.afisare();

    cout<<endl<<endl<<endl<<endl;;

    vector<ContBancar> vect;
    ContBancar A, B, C;
    vect.push_back(A);
    vect.push_back(B);
    vect.push_back(C);

    /*int n;
    vector<ContBancar> V;
    ContBancar CCC;
    cin>>n;
    for(int i=0; i<n; i++)
    {
        cin>>CCC;
        V.push_back(CCC);
    }

    for(auto i = V.begin(); i != V.end(); ++i)
        cout << *i << " ";*/
}
