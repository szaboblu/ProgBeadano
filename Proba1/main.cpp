//  main.cpp
//  Proba1
//  Created by Balázs Szabó on 2018. 11. 28..
//  Copyright © 2018. Balázs Szabó. All rights reserved.


#include <iostream>
#include <stdlib.h>
#include <vector>
#include <map>
#include <sstream>


using namespace std;
// Eképzelt működés  eddig:
// először kézzel meg kell adni a bemenetet:melyik .png, melyik vonal hol lép ki és be mi az alapszíne;
// kell egy behívó, feltöltő függvény vagy több,
// kell egy útkereső fv (Kep, hány db, forgatható e...) aminek a kimenete egy vektor<Kep> ? ainek a hossza a hurok hossza
// milyen bejárási algoritmus szükségeltetik ?! leghosszab hurkot kell keresni
// az utkereso kimenetei közül a legnagyobbat kiválasztani (érdemes annyiszor meghívni ahány szín van? vagy többször is)
// honnan induljon?
// az eredmény kiírása vagy kirajzolása legyen? (én nem tudom kirajzolni graphikus libbel)
//

struct Vonal{
    int ki, be; // hol a ki és bemenete => ez alapján azonosítja be
    vector<int> szin; // RGB
    void belsoforgat(int m){ // ide kell rakni eg overflowt, mert ugye ki és be is max 4 lehet
        ki += m;
        be += m;
    }
    Vonal(int k, int b, int R, int G, int B){
        ki = k;
        be = b;
        szin = {R,G,B};
    }
};

struct Kep {
    
    int azonosito; //melyik kép pl: 0002 (.png)
    int db; // mennyi áll rendelkezésre -->> nem itt kéne megadni mert akkor mindegyiknek ugyan annyi lenne az elforgatása
    //map<int, int> Be_ki; //hol megy be és hol jut ki pozíció szerint
    //map<Vonal, vector<int>> szinek; // melyik vonal milyen szin (mi legyen string vagy int (itt csak sima összeadás is lehe;tne az új szín) -> nem jó lila != cian ) -->>-->> RGB kód kell
    vector<Vonal> vonalak;
    bool forgathato; //alap nem
    int forgatottsag; // 0,1,2,3 * 90°
//public:
    Kep(){
        
    };
    Kep(int az, int szam, bool forg, vector<Vonal> v){
        azonosito = az;
        forgatottsag = 0;
        db = szam;
        forgathato = forg;
        vonalak = v;
    }
    void felhasznal(){
        if(db > 0) db--;
    }
    void forgat(int fok){
        if(forgathato){
           forgatottsag+=fok;
            for(int i = 0; i < vonalak.size(); i++ ){
                vonalak[i].belsoforgat(fok);
            }
        }
    }
    void szinek(){
        
    }
    friend bool operator < (const Kep& a, const Kep& b){
        return a.azonosito < b.azonosito;
    }
    
};

struct Halo{
    int pos_x,pos_y;
    vector<Kep> Hurok; // ide menti el a hurok sorrendjét// vagy mentse máshova?
    map<Kep,int> keszlet; //melyik képből mennyi van még map<Kep,mennyi>
    void felhasznal(Kep mit){
        if(keszlet[mit] > 0){
            keszlet[mit]--;
        }
    };
};

void beolvas(){
    Halo halo;
    cout << "Adja meg spacel elválasztva melyik képből mennyit kíván felhasználni, ezeket vesszővel válassza el "<< endl;
    string adat;
    int az,m;
    Kep kep;
    // ezt valahogy elegánsabban kéne.
    while(getline(cin,adat,',')){
        
        stringstream ss;
        ss << adat;
        ss >> az;
        ss >> m;
        kep.azonosito = az;
        halo.keszlet[kep] = m;
    }
    getline(cin,adat,'\n');
    stringstream ss;
    ss << adat;
    ss >> az;
    ss >> m;
    kep.azonosito = az;
    halo.keszlet[kep] = m;
    
    cout<<endl << "A felhasznált képek: "<<endl;
    for(pair<Kep,int> it : halo.keszlet){
        cout << it.first.azonosito << ".png   db: " << it.second <<endl;
    }
    for(int i = 0 ;  i < halo.keszlet.size();i++){
        Kep kep;
        cout<<endl << "Melyik képnek kívánja beállítani a paramétereit (óramutató járásával megegyezően)" <<endl;
        cin >> az;
        cout<<endl << "Paramétereket felülről be ki r g b, be ki r g b formában "<<endl;
        //cin >> halo.keszlet[a...
    }
};

/*
 int utkereses(){
    
    return utkereses();
};
 */

int main(int argc, const char * argv[]) {
    beolvas();
    cout << "Yeah!!!!!" <<endl;
    return 0;
}
