#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <stdlib.h>
#include <string>
#include <set>
#include <ctime>
#include <cstdlib>


using namespace std;

string dec_gray ( int n ) // decimalni u gray
{  // valja
    char tmp;
    string niz(9,'0');
    int k , znam, poz = 8;
    k =(n ^ (n >> 1) );

    while (k!= 0)
    {
        znam = k%2;
        k/=2;
        tmp = '0'+znam;
        niz[poz--]=tmp;
    }

    return niz;
}


 double gray_double (string s) // treba pretvoriti u dec , pa dec_gray vratiti u dec
                                // dobijem gray
    {   // moram grey u pravi broj s nulama i jedinicama

        int  j, poz = 8, sum = 0, znam;
int a[10],i=0,c=0;
        char d ;

        while ( poz >= 0 )
        {
            d = s[poz--];
            znam = d-'0';

            sum += znam*pow(10.0,i++ );
        }  // dec radi kako spada


i = 0;
    while(sum!=0)
        {
            a[i]=sum%10;
            sum/=10;
            i++;
            c++;
        }
    for(i=c-1;i>=0;i--)
        {
            if(a[i]==1)
            {
                if(a[i-1]==1)
                    a[i-1]=0;
                else
                    a[i-1]=1;
            }
        }

    int suma = 0;
    for(i=c-1;i>=0;i--)
    suma += a[i]*pow(2.0, i);

    return suma*(3.0/511.0) ;

    }


string rekombiniraj ( string a, string b ) // break nakon 4. elementa
{
    int i;
    string c ;
    c=a;
    for ( i = 4; i<9 ; ++i )
            c[i]=b[i];


    return  c;
}

 double f( double broj)
{
    return (((broj-1.5)*(broj-1.5)*10*(broj-2.0)*(broj-0.5)*(broj-2.5)*(broj - 2.5)*(broj - 1.0)*(broj - 1.0))+1.0);
    //(((broj-1.5)*(broj-1.5)*(broj-1.7)*10*(broj-2.8)*(broj-2.5)*(broj - 1.8))+1.0);
    //  ((sin(broj)*(broj-1.0)*(broj-1.0)*5*(broj-2.0)*(broj-2.5)+1.0));
    //(((broj-1.5)*(broj-1.5)*10*(broj-2.0)*(broj-0.5)*(broj-2.5)*(broj - 2.5)*(broj - 1.0)*(broj - 1.0))+1.0);
}

set<int> komplement ( set<int> s )
{
    int i;
    set<int> vrati;
    for (i = 0; i < 12 ; ++i )
        if ( s.count(i) == 0 ) vrati.insert(i);


    return vrati;
}


string promijeni (string rijec)

{
    //int r = rand() % 9;
    if (rijec [2] == '1') rijec[2] = '0';
        else rijec[2]='1';
    return rijec;
}


int main ()
{

 int j, k, m, i, broji = 0, count = 0, upamti, za_set = 0, za_ispisati = 0, pazi = 0, konacni_prekid = 0;
 double r, interval, maksimum, kontrola = 100.0, a, b, ograda = 100.0, mut;

  int l = 0, zaokruzi, brojac = 0, indeks = 0;

string jedan(9,'0'), dva(9,'0');

vector<int> zapamti(2), pom;
vector <double> polje_dablova, backup;
vector <string> polje_gray ;
vector <double> fitnessi(12);
vector <double> postotci(12);
set <int> temp, drugi, privremeni;
set<int>::iterator si;

srand( time(0));

zaokruzi = ceil(log(301)/log(2)); // == 9
interval = 3.0 / 511.0 ; // ode samo gg-dg = 3

for ( k = 0 ; k < 3 ; ++k )
{

    for ( j = 0; j < 4 ; ++j)
        {
            r = (rand() % 100 + l ) / 100.0;

            if ( pazi == 0 ) {maksimum = r; pazi = 1;}

            if (  abs (f(r)) >= abs( f(maksimum) )) maksimum = r; // maksimum ce biti ode los izbor, recimo
            polje_dablova.push_back(r);//

            m  = int ( trunc (r / interval) );
            polje_gray.push_back(dec_gray(m));
        }

    l += 100;

}


backup = polje_dablova;



 for ( i = 0; i<12; ++i)
    {
     fitnessi[i] = abs(f(maksimum))- abs(f(polje_dablova[i])); // treba oduzimat  vrijednost
        } //što veci fitness - bolja je tocka






// 1. generirati pocetnu populaciju potencijalnih rjesenja - done
// 2. izracunati prilagodenost svake jedinke u populaciji - done
// 3. izvrsavaj petlju dok nije ispunjen uvjet
    // - izaberi iz populacije skup jedinki za reprodukciju / recimo k = 6 done
    // - generiraj novu reneraciju ( radi krizanje i mutaciju ) - vise mutacija ode, ali kasnije
    // - izracunaj prilagodenost novogeneriranih jedinki
    // - zamijeni najlosije u generaciji novogeneriranim jedinkama
// 4.  vrati najkvalitetniju jedinku u tekucoj populaciji

while ( 1 )
    {
        while ( 1 )  // izaberi random 6 brojeva i tu radi nesto
            {          // dobar za sve brojeve iscrpiti // ne uzimamo one koje smo gledali
                r = (rand() % 12 + 0 );
                if ( temp.count(r) == 0 ) {temp.insert(r); ++brojac;}

                if ( brojac == 6 )
                    {
                        ++za_set ;  // za_ set resetirati
                        break;

                    }

            }

        if ( za_set == 1 ) drugi = temp;

         else if ( za_set == 2 )
        {
            drugi = komplement ( drugi );
            za_set = 0;
        }

        privremeni = drugi;


        for ( j = 0; j<2 ; ++j) // nadi dvojicu s najmanjim fitnessom i makni ih iz drugi
        { // komentirano zašto dvojicu od 6

                for( si = privremeni.begin(); si != privremeni.end(); ++si )
                {
                    if (  fitnessi[*si] < kontrola )
                    {
                        kontrola = fitnessi[*si];
                        zapamti[indeks] = *si;
                    }
                }
            privremeni.erase(zapamti[indeks]);
            ++indeks;
            kontrola = 100.0;
        }



        // rekombiniraj 2 i 2 preostala
        for( si = privremeni.begin(); si != privremeni.end(); ++si )
           pom.push_back(*si) ; // napravim vector od ova 4 ostala
        // kombiniram 2 i to 2 puta ( vrati mi jednoga samo fja )


           jedan = rekombiniraj (polje_gray[pom[0]] , polje_gray[pom[2]] );
           dva = rekombiniraj (polje_gray[pom[3]] , polje_gray[pom[1]] );


// eventualno ako ne ude u ovu mutaciju
           polje_gray[zapamti[0]] = jedan;
           polje_gray[zapamti[1]] = dva;


        // ode mutacija ide, paziti na postotak
           mut = (rand() % 101 ) / 100.0;   // zelim rand broj izmedu 0 i 1
           if ( mut <= 0.3) // ovo ce biti varijabilno !!!
                {
                    polje_gray[zapamti[0]] = promijeni (polje_gray[zapamti[0]]);
                    polje_gray[zapamti[1]] = promijeni (polje_gray[zapamti[1]]);

                    ++za_ispisati;

                }






        // tog jednog pretvorim u n , pa u decimalni onaj neki broj, pa od njega
        // nadem fitness, ubacim u fitness, ubacim ga na mjesto ovog nekog kojeg sam izbacio
        // ponovim sve to 2 puta
        a = gray_double ( polje_gray[zapamti[0]] ); // da mi double za gledat fitenss
        b = gray_double ( polje_gray[zapamti[1]] );


        polje_dablova[zapamti[0]] = a;
        polje_dablova[zapamti[1]] = b;

        if (  abs(f(a)) > abs(f(maksimum)) ) maksimum = a;
        if (  abs(f(b)) > abs(f(maksimum)) ) maksimum = b;
        // ode dobro radi jer je ovo samo za sluèaj kad dobijem lošiji broj pa da ga pomakne
        // kad imam dovoljno dobru ocjenu od max-a - dobar sam

        for ( i = 0; i<12 ; ++i)
            fitnessi[i]= abs(f(maksimum))-abs(f(polje_dablova[i]));




// objašnjeno kako imam 2 kontrolna uvjeta



        indeks = 0;
        brojac = 0;
        ++broji;  // broji mi sluzi za 2x6 = cijeli set brojeva
        if ( broji == 2 )
        {
            temp.clear();
            broji = 0;
        }


        ++count;

        for( i = 0; i<12; ++i)
            if( polje_dablova[i] == polje_dablova[0] ) ++konacni_prekid;


        if ( konacni_prekid == 12 || count == 1000 )
        {
            for ( i = 0 ; i < 12 ; ++i)
                if ( f(polje_dablova[i]) <= ograda   )
                    {
              //          cout << " brojevi u polje_dablova : " << polje_dablova[i] << endl;
                        ograda = f(polje_dablova[i]);
                        upamti = i;
                    }


            cout << "Rjesenje je : " << polje_dablova[upamti]<<" i postigli smo ga u "<< count <<" koraka."<< endl;
            cout << "U njemu fja ima vrijednost : " << f(polje_dablova[upamti]);
            if ( za_ispisati != 0 ) cout << ", a mutacija se dogodila "<< za_ispisati << " puta" ;
            return 0;

        }

    pom.clear();
    konacni_prekid = 0;
    }

return 0;

}
