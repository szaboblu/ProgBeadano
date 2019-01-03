//  main.cpp
//  Proba1
//  Created by Balázs Szabó on 2018. 11. 28..
//  Copyright © 2018. Balázs Szabó. All rights reserved.

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <map>
#include <sstream>
#include <list>

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
    int szin [3]; // RGB 3 elemű vektor (0/1) Fehér (1,1,1) pl piros: 1,0,0
    
    Vonal(int k, int b, int R, int G, int B){
    ki = k;
    be = b;
    szin [0] = R;
    szin [1] = G;
    szin [2] = B;
}
    
    void belsoforgat(int m){ // ide kell rakni eg overflowt, mert ugye ki és be is max 4 lehet
        if(ki + m > 4 || be + m > 4 ){ // ezt meg kell írni mert más lett az input
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
    map<int,vector<int>> oldalak;
    bool forgathato = false; //alap nem majd vegyük ki mert globális
    int forgatottsag; // 0,1,2,3 * 90° // vagy ezek többszörösei
    
public:
    Kep(){
        forgatottsag = 0;
        azonosito = 0;
        //oldalak =
    }
    
    /*Kep(int az, vector<Vonal> v, bool forg){
        azonosito = az;
        forgatottsag = 0;
        forgathato = forg;
        vonalak = v;
    }*/
    
    Kep(int az, vector<Vonal> v){
        azonosito = az;
        forgatottsag = 0;
        vonalak = v;
    }
    
    void oldaltolt(){
        cout<< endl << azonosito << " azonosítójú" << endl;
        for(int i = 1; i <=4; i++){
            vector<int> oldali = {0,0,0}; // alapból 0 0 0;
            for(int j = 0; j < vonalak.size(); j++){
                if(vonalak[j].be == i || vonalak[j].ki == i){
                    oldali[0]+= vonalak[j].szin[0];
                    oldali[1]+= vonalak[j].szin[1];
                    oldali[2]+= vonalak[j].szin[2];
                }
            }
            cout << i<<". oldal: " << oldali[0] << oldali[1] << oldali[2] << endl;
            oldalak[i] = oldali;
        }
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

map<vector<Kep>,vector<int>> csatlakozik(Kep k1, Kep k2){
    map<vector<Kep>,vector<int>> csatlakozasok;
    cout << endl;
    for(int i = 1; i <= k1.oldalak.size(); i ++){
        //int forgat;
        for(int j = 1; j <= k2.oldalak.size(); j++){
            if((i + j) == 5 && k1.oldalak[i] == k2.oldalak[j]){
                vector<Kep> kepvektor;
                kepvektor.push_back(k1);
                kepvektor.push_back(k2);
                
                csatlakozasok[kepvektor].push_back(i);
                //k2.forgat(forgat);
                csatlakozasok[kepvektor].push_back(j);
                cout << kepvektor[0].azonosito << " Azonosítójú a " << i << ". oldalával csatlakozik " <<kepvektor[1].azonosito << " azonosítójú " << j << ". oldalához "<< endl;
            }
        }
    }
    return csatlakozasok;
}

struct Keszlet{
    //int pos_x,pos_y;
    //vector<Kep> Hurok; // ide menti el a hurok sorrendjét// vagy mentse máshova?
    map<Kep,int> keszlet; //melyik képből mennyi van még map<Kep,mennyi>
    
    Keszlet(){};
    void hozzaad(Kep k, int sz){
        keszlet[k] = sz;
    };
    
    void felhasznal(Kep mit){ // felhasznál = elhasznál (melyiket tartsuk meg?)
        if(keszlet[mit] > 0){
            keszlet[mit]--;
        }
        else keszlet.erase(mit);
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
    
    void beolvas(){
        cout << "Hány féle képpel dolgozik?"<<endl;
        string M;
        int m;
        getline(cin,M);
        stringstream ss;
        ss << M;
        ss >> m;
        for(int i = 0; i < m; i++) {
            cout << "Kép mennyiség be ki r g b. be ki r g b. (...) "<< endl;
            string adat;
            getline(cin,adat);
            sorbeolvas(adat);
        }
    }
    
    void kiir(){
        for(auto it : keszlet){
            cout << endl << "Azonosító: "<< it.first.azonosito<<" db: "<<it.second<< endl;
            for(int j = 0; j < it.first.vonalak.size();j++){
                cout <<"Vonal"<<j+1<< ": " <<it.first.vonalak[j].ki <<"->"<< it.first.vonalak[j].be <<" ["<< it.first.vonalak[j].szin[0]<<" "<< it.first.vonalak[j].szin[1] <<" "<< it.first.vonalak[j].szin[2]<<"] "<< endl;
                
            }
            Kep k = it.first;
            k.oldaltolt();
        }
        
    }
    
    /*
    int utkereses(){
        int hossz;
    }*/
};

struct Halo{
    vector<list<Kep>> grafok;
    
    int utkereses(Keszlet k){
        int meret = 0;
        /*for(int i= 0; i<k.keszlet.size();i++){
            for(int j= 0; j<k.keszlet.size();j++){
                if(csatlakozik(k.keszlet[], <#Kep k2#>))
            }
        }*/
        for(auto i : k.keszlet){
            for(auto j: k.keszlet){
                if(csatlakozik(i.first, j.first).size() >  0){
                    
                }
            }
        };
        
        return meret;
    };
};

int main(int argc, const char * argv[]) {
    //Keszlet keszlet;
    //keszlet.beolvas();
    //keszlet.kiir();
    /*Vonal v1(2,3,0,1,0), v2(2,4,0,0,1),v3(4,3,1,0,0);
    Kep k1(1,{v1,v2,v3});
    k1.oldaltolt();
    Vonal v4(1,3,0,0,1),v5(2,3,0,1,0),v6(2,4,1,0,0);
    Kep k2(2,{v4,v5,v6});
    k2.oldaltolt();
     
    Vonal h1(1,4,1,1,0),h2(2,3,0,0,1);
    Vonal h3(1,3,0,0,1),h4(1,4,1,1,0);
    Kep k3(3,{h1,h2}), k4(4,{h3,h4});
    k3.oldaltolt();
    k4.oldaltolt();
    Keszlet keszlet;
    keszlet.hozzaad(k3,2);
    keszlet.hozzaad(k4,3);
    csatlakozik(k3,k4);*/
    
    Vonal h1(1,2,1,1,1),h2(2,4,1,1,1);
    Vonal h3(4,3,1,1,1),h4(1,3,1,1,1);
    Kep k1(1,{h1}), k2(2,{h2}) , k3(3,{h3}) , k4(4,{h4});
    k1.oldaltolt();
    k2.oldaltolt();
    k3.oldaltolt();
    k4.oldaltolt();
    Keszlet keszlet;
    keszlet.hozzaad(k1,1);
    keszlet.hozzaad(k2,1);keszlet.hozzaad(k3,1);keszlet.hozzaad(k4,1);
    csatlakozik(k3,k4);
    
    // ide kell az algoritmus
    cout << "Yeah!!!!!" <<endl;
    return 0;
}
