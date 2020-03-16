#include <iostream>
#include <math.h>
#include <cstdlib>
#include<cstring>
#include<bits/stdc++.h>
using namespace std;
class actor
{
private:
    char *nume_actor;
    int varsta;
public:
    actor()
    {
        this->varsta=0;
        this->nume_actor=new char[strlen("necunoscut")+1];
        strcpy(this->nume_actor,"necunoscut");
    }
    void set_nume_actor(char *s)
    {
        if(this->nume_actor)
            delete[] this->nume_actor;
        this->nume_actor=new char[strlen(s)+1];
        strcpy(this->nume_actor,s);
    }
    void set_varsta(int v)
    {
        this->varsta=v;
    }
    actor (int v,char *s)
    {
        if(s)
        {
            this->nume_actor=new char[1+strlen(s)];
            strcpy(nume_actor,s);
        }
        else
            nume_actor=new char('\0');
        if(v)
        {
            varsta=v;
        }
        else
            varsta=0;
    }
    actor (const actor&a)
    {
        this->varsta=a.varsta;
        this->nume_actor=new char[1+strlen(a.nume_actor)];
        strcpy(this->nume_actor,a.nume_actor);
    }
    ~actor()
    {
        if(this->nume_actor)
            delete[] this->nume_actor;
    }
    actor operator=(const actor& a)
    {
        if(this->nume_actor)
            delete[] this->nume_actor;
        this->varsta=a.varsta;
        this->nume_actor=new char[1+strlen(a.nume_actor)];
        strcpy(this->nume_actor,a.nume_actor);
        return *this;
    }
    friend ostream& operator<<(ostream &out, actor& a)
    {
        out<<a.nume_actor<<" "<<a.varsta;
        return out;
    }
    friend istream& operator>>(istream &in, actor &a)
    {
        char v[100];
        cout<<"Actor:\n";
        cout<<"Introduceti nume_actor: ";
        in>>v;
        a.nume_actor=new char[strlen(v)+1];
        strcpy(a.nume_actor,v);
        cout<<"Introduceti varsta: ";
        in>>a.varsta;
        return in;
    }
};
class teatru
{
private:
    char *denumire_piesa;
    int numar_actori;
    double rating;
    actor *a;
public:
    friend actor;
    teatru()
    {
        this->numar_actori=0;
        this->rating=0;
        this->denumire_piesa=new char[strlen("necunoscuta")+1];
        strcpy(this->denumire_piesa,"necunoscuta");
    }
    teatru(double r,int nr,actor *act,char *d)
    {
        if(nr)
        {
            this->denumire_piesa=new char[1+strlen(d)];
            strcpy(denumire_piesa,d);
            this->a=new actor[1+nr];
            for(int i=1; i<=nr; i++)
            {
                this->a[i]=act[i];
            }
            this->rating=r;
            this->numar_actori=nr;
        }
        else
        {
            denumire_piesa=new char('\0');
            rating=0;
            numar_actori=0;
        }
    }
    teatru(const teatru&t)
    {
        this->rating=t.rating;
        this->a=t.a;
        this->numar_actori=t.numar_actori;
        this->denumire_piesa=new char[1+strlen(t.denumire_piesa)];
        strcpy(this->denumire_piesa,t.denumire_piesa);
    }
    ~teatru()
    {
        if(this->denumire_piesa)
            delete[] this->denumire_piesa;
    }
    teatru operator=(const teatru& t)
    {
        if(this->denumire_piesa)
            delete[] this->denumire_piesa;
        this->a=t.a;
        this->denumire_piesa=new char[1+strlen(t.denumire_piesa)];
        strcpy(this->denumire_piesa,t.denumire_piesa);
        this->rating=t.rating;
        this->numar_actori=t.numar_actori;
        return *this;
    }
    friend ostream& operator<<(ostream &out, teatru& t)
    {
        out<<"Denumire piesa: "<<t.denumire_piesa<<"\nRating= "<<t.rating<<"\nNumar actori= "<<t.numar_actori<<endl<<"ACTORI:\n";
        for(int i=1; i<=t.numar_actori; i++)
            out<<t.a[i]<<endl;
        return out;
    }
    friend istream& operator>>(istream &in, teatru &t)
    {
        char v[100];
        cout<<"Introduceti denumire_piesa: ";
        in>>v;
        t.denumire_piesa=new char[strlen(v)+1];
        strcpy(t.denumire_piesa,v);
        cout<<"Introduceti ratingul: ";
        in>>t.rating;
        cout<<"Introduceti numarul de actori: ";
        in>>t.numar_actori;
        cout<<"Introduceti actorii:\n";

        t.a=new actor[t.numar_actori+1];
        for(int i=1; i<=t.numar_actori; i++)
        {
            cout<<"Date pentru actorul "<<i<<":\n";
            in>>t.a[i];
        }
        return in;
    }
    int operator<=(teatru &t)
    {
        if(this->rating<=t.rating)
            return 1;
        else
            return 0;
    }
    int operator>=(teatru &t)
    {
        if(this->rating>=t.rating)
            return 1;
        else
            return 0;
    }
    void set_denumire_piesa(char *d)
    {
        if(this->denumire_piesa)
            delete[] this->denumire_piesa;
        this->denumire_piesa=new char[strlen(d)+1];
        strcpy(this->denumire_piesa,d);
    }
    void set_rating(int r)
    {
        this->rating=r;
    }
    void set_numar_actori(int nr)
    {
        this->numar_actori=nr;
    }
    void set_actor(int n,char *s,int v)
    {
        this->a[n].set_varsta(v);
        this->a[n].set_nume_actor(s);
    }
};

void meniu_output()
{
    cout<<"\nPetcu David 211 - Proiect Teatru\n";
    cout<<"\n\tMENIU:\n";
    cout<<"\n----------------------------------";
    cout<<"\n1. Contructor pentru initializarea unui obiect de tip teatru.";
    cout<<"\n2. Constructor pentru initializarea default a unui obiect de tip teatru.";
    cout<<"\n3. Supraincarcarea operatorilor >> si <<.";
    cout<<"\n4. Supraincarcarea operatorului =.";
    cout<<"\n5. Supraincarcarea operatorului <=.";
    cout<<"\n6. Supraincarcarea operatorului >=.";
    cout<<"\n7. Modificarea unei informatii a unui obiect.";
    cout<<"\n0. Iesire.\n";
}


void meniu()
{
    int option=0;
    do
    {
        meniu_output();
        cout<<"\nIntroduceti numarul actiunii: ";
        cin>>option;
        if(option==1)
        {
            actor *a;
            int n;
            cout<<"Introduceti numarul de actori= ";
            cin>>n;
            a=new actor[n];
            for(int j=1; j<=n; j++)
            {
                cin>>a[j];
            }
            char s[10];
            cout<<"Introduceti denumirea piesei: ";
            cin>>s;
            cout<<"Introduceti rating-ul= ";
            int r;
            cin>>r;
            teatru tr(r,n,a,s);
            cout<<"\n"<<tr;
        }
        if(option==2)
        {
            int n;
            cout<<"Dati numarul de obiecte: ";
            cin>>n;
            teatru *s=new teatru[n+1];
            for(int i=1;i<=n;i++)
            {
                cout<<"Piesa "<<i<<":\n";
                cout<<s[i];
            }
        }
        if(option==3)
        {
            int n;
            cout<<"Dati numarul de obiecte: ";
            cin>>n;
            teatru *s=new teatru[n+1];
            for(int i=1;i<=n;i++)
            {
                cout<<"Obiectul "<<i<<":\n";
                cin>>s[i];
            }
            for(int i=1;i<=n;i++)
            {
                cout<<s[i];
            }
        }
        if(option==4)
        {
            teatru tr;
            cout<<"Se citeste obiectul: \n";
            cin>>tr;
            teatru cop=tr;
            cout<<"Noul obiect este:\n"<<cop;
        }
        if(option==5)
        {
            teatru t1;
            cout<<"Se citeste obiectul1: \n";
            cin>>t1;
            teatru t2;
            cout<<"Se citeste obiectul1: \n";
            cin>>t2;
            cout<<"Se afiseaza daca primul obiect are rating mai mic decat al doilea.\n";
            if(t1<=t2)
                cout<<"DA.\n";
            else cout<<"NU.\n";
        }
        if(option==6)
        {
            teatru t1;
            cout<<"Se citeste obiectul1: \n";
            cin>>t1;
            teatru t2;
            cout<<"Se citeste obiectul2: \n";
            cin>>t2;
            cout<<"Se afiseaza daca primul obiect are rating mai mare decat al doilea.\n";
            if(t1>=t2)
                cout<<"DA.\n";
            else cout<<"NU.\n";
        }
        if(option==7)
        {
            teatru t;
            cout<<"Se citeste obiectul: \n";
            cin>>t;
            int n;
            cout<<"1-Modificarea denumirii piesei\n2-Modificarea numarului de actori\n3-Modificarea rating-ului\n4-Modificarea unui actor\n";
            cin>>n;
            if(n==1)
            {
                char s[10];
                cout<<"Introduceti noua denumire: ";
                cin>>s;
                t.set_denumire_piesa(s);
                cout<<t;
            }
            if(n==2)
            {
                int nr;
                cout<<"Introduceti noul numar de actori: ";
                cin>>nr;
                t.set_numar_actori(nr);
                cout<<t;
            }
            if(n==3)
            {
                double r;
                cout<<"Introduceti noul rating: ";
                cin>>r;
                t.set_rating(r);
                cout<<t;
            }
            if(n==4)
            {
                int n;
                cout<<"Alegeti carui actor ii modificam datele: ";
                cin>>n;
                cout<<"Introduceti noile date: ";
                char s[10];
                int v;
                cout<<"\nNoul nume: ";
                cin>>s;
                cout<<"Noua varsta: ";
                cin>>v;
                t.set_actor(n,s,v);
                cout<<t;
            }
        }
        system("pause");
        system("cls");
    }
    while(option!=0);
}

int main()
{
    meniu();
    return 0;
}
