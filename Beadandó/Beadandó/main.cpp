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
    vector<int> szin; // RGB 3 elemű vektor (0/1) Fehér (1,1,1) pl piros: 1,0,0
    
    Vonal(int k, int b, int R, int G, int B){
    ki = k;
    be = b;
    szin = {R,G,B};
}
    
    void belsoforgat(int m){ // ide kell rakni eg overflowt, mert ugye ki és be is max 4 lehet
        if(ki + m > 4 || be + m > 4 ){
            ki = ki + m - 4;
            be = be + m - 4;
        }
        else{
            ki += m;
            be += m;
        }
    } // hozzáad m et a ki be paraméterekhez (max 4)
    
};

struct Kep {
    
    int azonosito; //melyik kép pl: 0002 (.png)
    //map<int, int> Be_ki; //hol megy be és hol jut ki pozíció szerint
    //map<Vonal, vector<int>> szinek; // melyik vonal milyen szin (mi legyen string vagy int (itt csak sima összeadás is lehetne az új szín) -> nem jó lila != cian ) -->>-->> RGB kód kell
    vector<Vonal> vonalak;
    bool forgathato = false; //alap nem
    int forgatottsag; // 0,1,2,3 * 90° // vagy ezek többszörösei
    
public:
    Kep(){
        forgatottsag = 0;
    }
    Kep(int az, vector<Vonal> v, bool forg){
        azonosito = az;
        forgatottsag = 0;
        forgathato = forg;
        vonalak = v;
    }
    Kep(int az, vector<Vonal> v){
        azonosito = az;
        forgatottsag = 0;
        vonalak = v;
    }
    
    void forgat(int fok){
        if(forgathato){
           forgatottsag+=fok;
            for(int i = 0; i < vonalak.size(); i++ ){
                vonalak[i].belsoforgat(fok);
            }
        }
    }
    
    friend bool operator < (const Kep& a, const Kep& b){
        return a.azonosito < b.azonosito;
    }
};

struct Halo{
    int pos_x,pos_y;
    vector<Kep> Hurok; // ide menti el a hurok sorrendjét// vagy mentse máshova?
    map<Kep,int> keszlet; //melyik képből mennyi van még map<Kep,mennyi>
    
    void felhasznal(Kep mit){ // felhasznál = elhasznál (melyiket tartsuk meg?)
        if(keszlet[mit] > 0){
            keszlet[mit]--;
        }
    }
    
    void elhasznal(int mit){
        for(auto it : keszlet ){
            if(it.first.azonosito == mit){
                keszlet[it.first]--;
            }
        }
    }
    
    void sorbeolvas(string sor){
        Kep kep;
        int az, m;
        stringstream ss;
        ss << sor;
        ss >> az;
        ss >> m;
        kep.azonosito = az;
        
        string vonal;
        while(getline(ss,vonal,'.')){
            stringstream sf(vonal);
            int be,ki,r,g,b;
            sf >> be >> ki >> r >> g >> b;
            Vonal v(be,ki,r,g,b);
            kep.vonalak.push_back(v);
        }
        keszlet[kep] = m;
    }
    
};


Halo beolvas(){
    Halo halo;
    cout << "Hány féle képpel dolgozik?"<<endl;
    int m;
    cin >> m;
    while (m > 0) {
        cout << "Kép mennyiség be ki r g b. be ki r g b. (...) "<< endl;
        string adat;
        getline(cin,adat);
        halo.sorbeolvas(adat);
        m--;
    }
    return halo;
};



/*
 int utkereses(){
    
    return utkereses();
};
 */

int main(int argc, const char * argv[]) {
    Halo halo = beolvas();
    cout << "Yeah!!!!!" <<endl;
    return 0;
}
