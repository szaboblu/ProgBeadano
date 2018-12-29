#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

struct pont {
    double x;
    double y;
    void beolvas(){
        cout << "Adj meg ket szamot, en meg kiirom oket" << endl;
        cin >> x;
        cin >> y;
    }
    void kiir(){
    cout << "A szamok: " << endl;
    cout << x << endl;
    cout << y;
    }

};


int main()
{

    pont p;
    p.beolvas();
    p.kiir();

    return 0;
}
