#include <iostream>
#include <math.h>
#include <cstdlib>
using namespace std;

class nr_complex
{
private:
    int real;
    int imaginar;
public:
    nr_complex (int, int);                     ///constructor initializare
    nr_complex (nr_complex&);                     ///constructor copiere
    ~nr_complex ();                            ///destructor
    void set_real(int);                     ///set
    void set_imaginar(int);                 ///set
    int get_real()
    {
        return real;
    };           ///get
    int get_imag()
    {
        return imaginar;
    };       ///get
    void afisare(ostream &out);
    void citire(istream &in);
    friend istream& operator>>(istream &in, nr_complex& z);  ///supraincarcare pe >>
    friend ostream& operator<<(ostream &out, nr_complex& z); ///supraincarcare pe <<
    double modul(); ///functia modul
    nr_complex& operator=(nr_complex &z); ///supraincarcarea operatorului de atribuire (doar ca metoda nu ca functie friend)
    friend nr_complex& operator+(nr_complex& z1, nr_complex& z2); ///supraincarcare operator +
    friend nr_complex& operator*(nr_complex& z1, nr_complex& z2); ///supraincarcare operator *
    friend nr_complex& operator/(nr_complex& z1, nr_complex& z2); ///supraincarcare operator /
};

////////////////////////////////////////////////////////////

nr_complex::nr_complex(int real = 0, int imaginar = 0)
{
    this->real = real;
    this->imaginar = imaginar;
}
nr_complex::nr_complex(nr_complex &z)
{
    this->real = z.real;
    this->imaginar = z.imaginar;
}
nr_complex::~nr_complex()
{
    this->real=0;
    this->imaginar=0;
}
void nr_complex::set_real(int x)
{
    real = x;
}
void nr_complex::set_imaginar(int y)
{
    imaginar=y;
}
void nr_complex::citire(istream &in)
{
    cout<<"\nCititi partea reala: ";
    in>>real;
    cout<<"Cititi partea imaginara: ";
    in>>imaginar;
}
istream& operator>>(istream& in,nr_complex& z)
{
    z.citire(in);
    return in;
}
void nr_complex::afisare(ostream &out)
{
    if (imaginar==0)
    {
        out<<real;
    }
    else
    {
        if (imaginar < 0)
        {
            out<<real<<imaginar<<"*i";
        }
        else
        {
            out<<real<<"+"<<imaginar<<"*i";
        }
    }
}
ostream& operator<<(ostream& out, nr_complex& z)
{
    z.afisare(out);
    return out;
}
double nr_complex::modul()
{
    return sqrt(real*real+imaginar*imaginar);
}
nr_complex& nr_complex::operator=(nr_complex &z)
{
    real=z.real;
    imaginar=z.imaginar;
}
inline nr_complex& operator+(nr_complex &z1, nr_complex& z2)
{
    nr_complex *z = new nr_complex;
    z->real = z1.real + z2.real;
    z->imaginar = z1.imaginar + z2.imaginar;
    return *z;
}
inline nr_complex& operator*(nr_complex &z1, nr_complex& z2)
{
    nr_complex *z=new nr_complex;
    z->real = z1.real * z2.real - z1.imaginar * z2.imaginar;
    z->imaginar = z1.real * z2.imaginar + z2.real * z1.imaginar;
    return *z;
}
nr_complex& operator/(nr_complex &z1, nr_complex &z2)
{
    nr_complex *z=new nr_complex;
    z->real = (z1.real*z2.real + z1.imaginar * z2.imaginar) / (z2.real * z2.real + z2.imaginar * z2.imaginar);
    z->imaginar = (z2.real * z1.imaginar - z1.real * z2.imaginar) / (z2.real * z2.real + z2.imaginar * z2.imaginar);
    return *z;
}

/////////////////////////////////

class matrice_complexa
{
private:
    int l;
    int c;
    nr_complex **a;
public:
    friend nr_complex;
    matrice_complexa(int linii=0,int coloane=0)
    {
        l=linii;
        c=coloane;
        a=new nr_complex*[l+1];
        for(int i=1; i<=l; i++)
            a[i]=new nr_complex[c+1];
        for(int i=1; i<=l; i++)
            for(int j=1; j<=c; j++)
            {
                a[i][j].set_real(0);
                a[i][j].set_imaginar(0);
            }
        cout<<"\nSe executa constructorul default pentru linii="<<l<<" si coloane="<<c;
    }
    matrice_complexa(nr_complex,int,int);
    matrice_complexa(const matrice_complexa&);
    ~matrice_complexa();
    friend ostream &operator<<(ostream& out, matrice_complexa& m);
    matrice_complexa& operator=(const matrice_complexa&);
    matrice_complexa operator+(const matrice_complexa&);
    matrice_complexa operator*(const matrice_complexa&);
    friend istream& operator>>(istream &in, matrice_complexa& m);

};

matrice_complexa::matrice_complexa(nr_complex z, int linii,int col)
{
    l=linii;
    c=col;
    a=new nr_complex*[l+1];
    for(int i=1; i<=l; i++)
        a[i]=new nr_complex[c+1];
    for(int i=1; i<=l; i++)
        for(int j=1; j<=c; j++)
            a[i][j]=z;
    cout<<"\nSe executa constructorul pentru: z="<<z<<", l="<<l<<" si c="<<c<<".\n";
}

matrice_complexa::matrice_complexa(const matrice_complexa& m)
{
    l=m.l;
    c=m.c;
    a=new nr_complex*[l+1];
    for(int i=1; i<=l; i++)
        a[i]=new nr_complex[c+1];
    for(int i=1; i<=l; i++)
        for(int j=1; j<=c; j++)
            a[i][j]=m.a[i][j];
    cout<<"\nSe executa copierea.\n";
}

matrice_complexa::~matrice_complexa()
{
    for(int i=1; i<=l; i++)
        delete[] a[i];
    delete[] a;
    cout<<"\nSe executa destructorul.\n";
}

ostream &operator<<(ostream & out,matrice_complexa &m)
{
    out<<"\nMatricea este:\n";
    if(m.l==0 || m.c==0)
    {
        cout<<"Matricea nu exista.\n";
        return out;
    }
    for(int i=1; i<=m.l; i++)
    {
        for(int j=1; j<=m.c; j++)
            out<<m.a[i][j]<<" ";
        out<<endl;
    }
    return out;
}

matrice_complexa& matrice_complexa::operator=(const matrice_complexa& m)
{
    matrice_complexa m2(l,c);
    for(int i=1; i<=l; i++)
        for(int j=1; j<=c; j++)
            a[i][j]=m.a[i][j];
    cout<<"\nse executa =\n";
    return m2;
}
matrice_complexa matrice_complexa::operator*(const matrice_complexa& m)
{
    if(c!=m.l || l!=m.c)
    {
        cout<<"\nNumarul de coloane al primei matrice nu este egal cu numarul de linii al celei de-a doua.\n";
        matrice_complexa mat;
        return mat;
    }
    matrice_complexa m2(l,m.c);
    for(int i=1; i<=l; ++i)
        for(int j=1; j<=m.c; ++j)
            for(int k=1; k<=c; ++k)
                m2.a[i][j]=m2.a[i][j]+a[i][j]*m.a[i][j];
    return m2;
}
matrice_complexa matrice_complexa::operator+(const matrice_complexa& m)
{
    if(l!=m.l || c!=m.c)
    {
        cout<<"\nMatricele nu au aceeasi dimensiune.\n";
        matrice_complexa mat;
        return mat;
    }
    matrice_complexa m2(l,c);
    for(int i=1; i<=l; i++)
        for(int j=1; j<=c; j++)
            m2.a[i][j]=a[i][j]+m.a[i][j];
    cout<<"\nSe executa operatorul +.\n";
    return m2;
}

istream& operator>>(istream& in,matrice_complexa& m)
{
    cout<<"Cititi numarul de linii: ";
    in>>m.l;
    cout<<"Cititi numarul de coloane: ";
    in>>m.c;
    //cout<<"\n"<<m.l<<" "<<m.c;
    m.a=new nr_complex*[m.l+1];
    for(int i=1; i<=m.l; i++)
        m.a[i]=new nr_complex[m.c+1];
    for(int i=1; i<=m.l; i++)
        for(int j=1; j<=m.c; j++)
        {
            cout<<"a["<<i<<"]["<<j<<"]=";
            in>>m.a[i][j];
        }
    return in;
}
///////////////////////////
void meniu_output()
{
    cout<<"\nPetcu Gabriela-Camelia 211 - Proiect Matrice Complexa\n";
    cout<<"\n\tMENIU:\n";
    cout<<"\n----------------------------------";
    cout<<"\n1. Contructor pentru initializarea unui numar complex dat pe toate componentele.";
    cout<<"\n2. Constructor pentru initializarea cu 0 pe toate componentele.";
    cout<<"\n3. Supraincarcarea operatorilor >> si <<.";
    cout<<"\n4. Supraincarcarea operatorului =.";
    cout<<"\n5. Supraincarcarea operatorului +.";
    cout<<"\n6. Supraincarcarea operatorului *.";
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
            int n;
            cout<<"\nIntroduceti numarul de matrice: ";
            cin>>n;
            int o;
            cout<<"\nDaca doriti sa introduceti de la tastatura nr complex, nr de linii si de coloane apasati 1, daca nu, apasati 2.\n";
            cin>>o;
            if(o==2)
            {
                for(int i=1; i<=n; i++)
                {
                    int nr_real=(rand() % 40) + 1, nr_imag=(rand() % 40) + 1;
                    int l=(rand() % 5) + 1,c=(rand() % 5) + 1;
                    nr_complex z(nr_real,nr_imag);
                    matrice_complexa mat(z,l,c);
                    cout<<"\nS-a construit matricea:\n";
                    cout<<mat;
                }
            }
            else
            {
                for(int i=1; i<=n; i++)
                {
                    int l,c;
                    nr_complex z;
                    cout<<"l=";
                    cin>>l;
                    cout<<"c=";
                    cin>>c;
                    cout<<"z=";
                    cin>>z;
                    matrice_complexa a(z,l,c);
                    cout<<"\nS-a construit matricea:\n";
                    cout<<a;
                }
            }
        }
        if(option==2)
        {
            int n;
            cout<<"\nIntroduceti numarul de matrice: ";
            cin>>n;
            int o;
            cout<<"\nDaca doriti sa introduceti de la tastatura nr de linii si de coloane apasati 1, daca nu, apasati 2.\n";
            cin>>o;
            if(o==2)
            {
                for(int i=1; i<=n; i++)
                {
                    int l=(rand() % 5) + 1,c=(rand() % 5) + 1;
                    matrice_complexa a(l,c);
                    cout<<"\nS-a construit matricea:\n";
                    cout<<a;
                }
            }
            else
            {
                for(int i=1; i<=n; i++)
                {
                    int l,c;
                    cout<<"l=";
                    cin>>l;
                    cout<<"c=";
                    cin>>c;
                    matrice_complexa a(l,c);
                    cout<<"\nS-a construit matricea:\n";
                    cout<<a;
                }
            }
        }
        if(option==3)
        {
            int n;
            cout<<"\nIntroduceti numarul de matrice: ";
            cin>>n;
            matrice_complexa *a;
            a=new matrice_complexa[n];
            for(int i=1; i<=n; i++)
            {
                cout<<"\nDati valori pentru matricea "<<i<<":\n";
                cin>>*a;
                cout<<*a;
            }
        }
        if(option==4)
        {
            int o;
            cout<<"\nDaca doriti sa introduceti de la tastatura o matrice apasati 1, daca nu, apasati 2.\n";
            cin>>o;
            if(o==1)
            {
                matrice_complexa a;
                cout<<"\nDati valori pentru matricea A:\n";
                cin>>a;
                cout<<a;
                matrice_complexa b=a;
                cout<<"\nMatricea B:\n";
                cout<<b;
            }
            else
            {
                int nr_real=(rand() % 40) + 1, nr_imag=(rand() % 40) + 1;
                int l=(rand() % 5) + 1,c=(rand() % 5) + 1;
                nr_complex z(nr_real,nr_imag);
                matrice_complexa a(z,l,c);
                cout<<"\nMatricea A:\n"<<a;
                matrice_complexa b=a;
                cout<<"\nMatricea B:\n"<<b;
            }
        }
        if(option==5)
        {
            int o;
            cout<<"\nDaca doriti sa introduceti de la tastatura cele 2 matrice apasati 1, daca nu, apasati 2.\n";
            cin>>o;
            if(o==1)
            {
                matrice_complexa a;
                cout<<"\nATENTIE: L1=L2 SI C1=C2.\n";
                cout<<"\nDati valori pentru matricea A:\n";
                cin>>a;
                cout<<a;
                matrice_complexa b;
                cout<<"\nDati valori pentru matricea B:\n";
                cin>>b;
                cout<<b;
                cout<<"Rezultatul C=A+B:\n";
                matrice_complexa mat=a+b;
                cout<<mat;
            }
            else
            {
                int nr_real1=(rand() % 40) + 1, nr_imag1=(rand() % 40) + 1;
                int l=(rand() % 5) + 1,c=(rand() % 5) + 1;
                int nr_real2=(rand() % 40) + 1, nr_imag2=(rand() % 40) + 1;

                nr_complex z1(nr_real1,nr_imag1);
                nr_complex z2(nr_real2,nr_imag2);
                matrice_complexa a(z1,l,c),b(z2,l,c);

                cout<<"\nMatricea A:\n"<<a;
                cout<<"\nMatricea B:\n"<<b;
                cout<<"Rezultatul C=A+B:\n";
                matrice_complexa mat=a+b;
                cout<<mat;
            }
        }
        if(option==6)
        {
            int o;
            cout<<"\nDaca doriti sa introduceti de la tastatura cele 2 matrice apasati 1, daca nu, apasati 2.\n";
            cin>>o;
            if(o==1)
            {
                matrice_complexa a;
                cout<<"\nATENTIE: L1=C2 si C1=L2.\n";
                cout<<"\nDati valori pentru matricea A:\n";
                cin>>a;
                cout<<a;
                matrice_complexa b;
                cout<<"\nDati valori pentru matricea B:\n";
                cin>>b;
                cout<<b;
                cout<<"Rezultatul C=A*B:\n";
                matrice_complexa mat=a*b;
                cout<<mat;
            }
            else
            {
                int nr_real1=(rand() % 40) + 1, nr_imag1=(rand() % 40) + 1;
                int l1=(rand() % 5) + 1,c1=(rand() % 5) + 1;
                int c2=(rand() % 5) + 1;
                int nr_real2=(rand() % 40) + 1, nr_imag2=(rand() % 40) + 1;

                nr_complex z1(nr_real1,nr_imag1);
                nr_complex z2(nr_real2,nr_imag2);
                matrice_complexa a(z1,l1,c1),b(z2,c1,c2);

                cout<<"\nMatricea A:\n"<<a;
                cout<<"\nMatricea B:\n"<<b;
                cout<<"Rezultatul C=A*B:\n";
                matrice_complexa mat=a*b;
                cout<<mat;
            }
        }
        system("pause");
        system("cls");
    }
    while(option!=0);
}

//////////////////////////
int main()
{
    meniu();
    return 0;
}
