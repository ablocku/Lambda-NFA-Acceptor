#include <iostream>
#include <fstream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <cstring>
using namespace std;

ifstream f("date.in");
ofstream g("date.out");

unordered_map<char, vector<int>>mat[41];
char muc[40];
int qf[51];
int n,m,q0,k,l,x,y;
char c;
char sir[256];

int viz[51];
queue<int> c1,c2; //c1 - coada in care tin starile unde pot ajunge fara litere sau cu lambda-miscari,
                  //in c2 retin starile in care ajung cu o litera din alfabet


bool evaluate(char s[]) // s - cuvantul
{
    int lg = strlen(s);
    c1.push(q0);
    viz[q0] = 1;
    for(int poz = 0; poz < lg ; ++poz)
        {
        if(c1.empty()) //daca nu am putut ajunge in nicio stare, cuvantul nu este acceptat
            return false;
        while(!c1.empty())
            {
            int x = c1.front();
            c1.pop();
            c2.push(x); // "varsam" din c1 in c2 fiecare stare, deoarece putem ajunge in aceeasi stare fara caractere
            for(int stare: mat[x]['$'])
                if(viz[stare] != poz + 1)
                    {
                    viz[stare] = poz + 1;
                    c1.push(stare);
                    }
            }
        while(!c2.empty())
            {
            int x = c2.front();
            c2.pop();
            for(int stare: mat[x][s[poz]])
                if(viz[stare] != poz + 2)
                    {
                    viz[stare] = poz + 2;
                    c1.push(stare);
                    }
            }
        }
    while(!c1.empty()) //desi cuvantul s-a terminat, mai verificam daca mai avem stari in c1 din care putem pleca cu '$'
        {
        int x = c1.front();
        c1.pop();
        c2.push(x);
        for(int stare: mat[x]['$'])
            if(viz[stare] != lg + 1)
                {
                viz[stare] = lg + 1;
                c1.push(stare);
                }
        }
    while(!c2.empty())
        {
        int x = c2.front();
        c2.pop();
        for(int i = 0; i < k; ++i)
            if(x == qf[i]) // daca cel putin o stare din c2 este finala, atunci cuvantul este acceptat
                return true;
        }
    return false; // daca niciuna din starile ramase in c2 nu este finala, cuvantul nu este acceptat
}

int main()
{
int i;
f>>n>>m;
for(i = 0; i < m; ++i)
    f>>muc[i];
f>>q0;
f>>k;
for(i = 0; i < k; ++i)
    f>>qf[i];
f>>l;
for(i = 0; i < l; ++i)
    {
    f>>x>>c>>y;
    mat[x][c].push_back(y);
    }
f>>sir;
if(evaluate(sir))
    g<<"Cuvantul este acceptat";
else
    g<<"Cuvantul nu este acceptat";
return 0;
}
