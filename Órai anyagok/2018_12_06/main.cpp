#include <iostream>
#include <set>
#include <vector>
using namespace std;

struct A
{
    //...
    // gyerekek //
    string s;
    vector<string> history;
    A()
    {
        s = "AAA_BBB";
    }
    A(const A& a) /// copy konstruktor
    {
        s = a.s;
        history = a.history;
    }
    vector<A> gyerekek ()
    {
        vector<A> res;
        for(int i = 0; i<s.length()-1; i++)
        {
            if(s[i] == 'A' && s[i+1] == '_')
            {
                A uj(*this);
                uj.history.push_back(uj.s);
                uj.s[i] = '_';
                uj.s[i+1] = 'A';
                res.push_back(uj);
            }
            if(s[i+1] == 'B' && s[i] == '_')
            {
                A uj(*this);
                uj.history.push_back(uj.s);
                uj.s[i+1] = '_';
                uj.s[i] = 'B';
                res.push_back(uj);
            }
        }
        for(int i = 0; i<s.length()-2; i++)
        {
            if (s[i] == 'A' && s[i+1] == 'B' && s[i+2] == '_')
            {
                A uj(*this);
                uj.history.push_back(uj.s);
                uj.s[i] = '_';
                uj.s[i+2] = 'A';
                res.push_back(uj);
            }
            if (s[i] == '_' && s[i+1] == 'A' && s[i+2] == 'B')
            {
                A uj(*this);
                uj.history.push_back(uj.s);
                uj.s[i] = 'B';
                uj.s[i+2] = '_';
                res.push_back(uj);
            }
        }
        return res;
    }
};

bool operator<(const A& a, const A& b)
{
    //...
    if (a.s != b.s) return a.s < b.s;
    return a.history < b.history;
}

ostream & operator<<(ostream &out, const A& a)
{
    //...
    for (string s : a.history)
    {
        cout << s << endl;
    }
    out << a.s << endl;

    return out;
}

float value(const A& a)
{
    /// 3 békára
    if(a.s.find("ABB_") != string::npos || a.s.find("_AAB") != string::npos) return 0;
    if(a.s.find("AABA") != string::npos) return 0;
    if(a.s.find("AAB") != string::npos) return 0;
//if(a.s.find("ABBB_") != string::npos || a.s.find("_AAAB") != string::npos) return 0;
//if(a.s.find("AABBA") != string::npos) return 0;
//if(a.s.find("AAB") != string::npos) return 0;
//if(a.s.find("AABA") != string::npos) return 0;
//if(a.s.find("ABB_") != string::npos || a.s.find("_AAB") != string::npos) return 0;
//if(a.s.find("AABB") != string::npos) return 0;
///priority_queue -> gyorsabb
    return 1;
}

bool vegeredmeny(const A& a)
{
    //...
    return a.s == "BBB_AAA";
}

template<typename T>
class NodeSet
{
    set<T> t;
public:
    T pop_max()
    {
        auto it_max = t.begin();
        for (auto it=t.begin(); it!=t.end(); it++)
        {
            if (value(*it) > value(*it_max))
            {
                it_max = it;
            }
        }
        T res = *it_max;
        t.erase(it_max);
        return res;
    }
    void put(T a)
    {
        t.insert(a);
    }
    int size() const
    {
        return t.size();
    }
    void dump(ostream &out = cout)
    {
        for (auto it=t.begin(); it!=t.end(); it++)
        {
            out << *it;
        }
    }
};

int main()
{
    NodeSet<A> ns;
    A kezdet;
    // kezdet = ...
    ns.put(kezdet);
    bool vege = false;
    A legjobb = kezdet; // csak hogy legyen kezdeti ertek
    int lepesszam = 0;
    while(!vege && ns.size())
    {
    lepesszam++;
        A aktualis = ns.pop_max();
        if (vegeredmeny(aktualis))
        {
            legjobb=aktualis;
            vege=true;
        }
        vector<A> gyerekek = aktualis.gyerekek();
        for (A jelolt: gyerekek)
        {
            // if(..) //esetleg
            ns.put(jelolt);
        }
    }
    if (vege) {
    cout << endl << endl << legjobb << "a vegeredmeny" << endl;
    cout << "(" << lepesszam << " lepes, eredmény history: " << legjobb.history.size() << ")" << endl;
    } else {
    cout << "nincs megoldas" << endl;
    }

    return 0;
}
