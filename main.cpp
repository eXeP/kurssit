#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

int laske();
template <class T>
inline void hash_combine(std::size_t & seed, const T & v)
{
  std::hash<T> hasher;
  seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

namespace std
{
  template<typename S, typename T> struct hash<pair<S, T>>
  {
    inline size_t operator()(const pair<S, T> & v) const
    {
      size_t seed = 0;
      ::hash_combine(seed, v.first);
      ::hash_combine(seed, v.second);
      return seed;
    }
  };
}
using namespace std;
int opiskelijat, kurssit, maxkurssit;
vector<int> op[100020];
vector<int> opkurssilla[100020];
unordered_set<int> lukkari[25];
unordered_set<int> lukkaricopy[25];
ofstream out;
int paikka[100020];
int paikkacopy[100020];
unordered_map<pair<int,int>, int> paalle;
int tulos = 0;
int opn[100020] = {0};
int paras;
void save(){

    ifstream sinv ("out.txt");
    int saveparas; sinv >> saveparas;
    sinv.close();
    if(saveparas > paras)
        return;

    for(int i = 0; i < 25; i++){
        lukkaricopy[i].clear();
        for(int f: lukkari[i])
            lukkaricopy[i].insert(f);

    }
    for(int i = 1; i <= kurssit; i++)
        paikkacopy[i] = paikka[i];

    cout << "DONT STOP ME NOW" << endl;
    out.open("out.txt", std::ios::trunc );

    cout << paras << endl;

    out << paras << endl;
    for(int i = 0; i < 25; i++){
        out << i+1;
        for(int f: lukkari[i])
            out << " " << f;
        out << endl;
    }
    out.close();
    cout << "Go ahead..." << endl;
}
int laskeop(int num){
    int ret = 0;
    bool kay[25] = {0};
    for(int j = 0; j < op[num].size(); j++){
        if(!kay[paikka[op[num][j]]])
            ret++;
        kay[paikka[op[num][j]]] = true;
    }
    return ret;

}
int laske(){
    int ret = 0;

    for(int i = 1; i <= opiskelijat; i++){
        int vanh = ret;
        bool kay[25] = {0};
        for(int j = 0; j < op[i].size(); j++){
            if(!kay[paikka[op[i][j]]])
                ret++;
            kay[paikka[op[i][j]]] = true;
        }
        opn[i] = ret-vanh;
    }
    return ret;
}
int laskepaalle(int num, int uus){
    int ret = 0;
    for(int f: lukkari[uus]){
        pair<int,int> p1 = make_pair(min(num, f), max(num, f));
            if(paalle.count(p1))
                ret+=paalle[p1];
    }
    return ret;
}

int main()
{

    srand (time(NULL));
    cin.sync_with_stdio(0);
    cin.tie(0);
    std::ifstream in("kurssit.txt");
    std::streambuf *cinbuf = std::cin.rdbuf(); //save old buf
    std::cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!
    std::default_random_engine generator;
    std::uniform_int_distribution<int> lukdist(0,24);

    cin >> opiskelijat >> kurssit >> maxkurssit;
    std::uniform_int_distribution<int> kursdist(1,kurssit);
    for(int i = 1; i <= opiskelijat; i++){
        int nu, maara; cin >> nu >> maara;
        for(int j = 0; j < maara; j++){
            int nku; cin >> nku;
            opkurssilla[nku].push_back(nu);
            for(int k = 0; k < op[nu].size(); k++){
                pair<int,int> p1 = make_pair(min(nku, op[nu][k]), max(nku, op[nu][k]));
                if(paalle.count(p1))
                    paalle[p1]++;
                else
                    paalle[p1]=1;
            }
            op[nu].push_back(nku);
        }

    }

    //for(int i = 1; i <= kurssit; i++){
   //     int nluk = rand()%25;

  //     lukkari[nluk].insert(i);
   //     paikka[i] = nluk;
   // }
    std::ifstream in2("out.txt");
    cinbuf = std::cin.rdbuf(); //save old buf
    std::cin.rdbuf(in2.rdbuf()); //redirect std::cin to in.txt!
    string lol;
    getline(cin, lol);
    if(lol.size() == 0){
        for(int i = 1; i <= kurssit; i++){
            int nluk = lukdist(generator);
            lukkari[nluk].insert(i);
            paikka[i] = nluk;
        }
    }
    else{
    while(!cin.eof())
    {
        getline(cin, lol);
        istringstream lols(lol);
        int kunm;
        lols>>kunm;
        kunm--;
        while(!lols.eof())
        {

            int kurr;
            lols>>kurr;
            //cout << kunm << " : " << kurr << endl;
            lukkari[paikka[kurr]].erase(kurr);
            paikka[kurr] = kunm;
            lukkari[kunm].insert(kurr);
        }
    }
    }
    for(int i = 0; i < 25; i++){
        lukkaricopy[i].clear();
        for(int f: lukkari[i])
            lukkaricopy[i].insert(f);

    }
    for(int i = 1; i <= kurssit; i++)
        paikkacopy[i] = paikka[i];
    paras = laske();
    tulos = paras;
    save();
    int e = paras;
    int cc = 0;
    int stuck = 0;
    cout << paras << endl;
    while(true){
        int nidx = kursdist(generator);
        int nluk = lukdist(generator);
        int enev = e;
        int vanhap = paikka[nidx];

        lukkari[paikka[nidx]].erase(nidx);
        lukkari[nluk].insert(nidx);
        paikka[nidx] = nluk;
        for(int i = 0; i < opkurssilla[nidx].size(); i++)
        {
            enev-=opn[opkurssilla[nidx][i]];
            int uusopn = laskeop(opkurssilla[nidx][i]);
            opn[opkurssilla[nidx][i]] = uusopn;
            enev+=uusopn;
        }
        if(enev > paras)
        {
            //cout << cc << " ja " << stuck << endl;

            paras = enev;
            save();
            cc = 0;
            stuck = 1;

        }


        if(cc > 10000){
            //cout << "lopetettu: " << e << endl;

            for(int i = 0; i < 25; i++)
            {
                lukkari[i].clear();
                for(int f: lukkaricopy[i])
                    lukkari[i].insert(f);

            }
            for(int i = 1; i <= kurssit; i++)
                paikka[i] = paikkacopy[i];

            paras = laske();
            //save();
            e = paras;
            cc = 0;
            stuck++;


        }
        ohi:
        double x = ((double) rand() / (RAND_MAX));
        //cout << exp((paras-enev))<< endl;
        if(exp(1.0-exp((paras-enev))) > x){
            cc++;
            e = enev;

            continue;
        }

        lukkari[paikka[nidx]].erase(nidx);
        lukkari[vanhap].insert(nidx);
        paikka[nidx] = vanhap;
        for(int i = 0; i < opkurssilla[nidx].size(); i++){
            int uusopn = laskeop(opkurssilla[nidx][i]);
            opn[opkurssilla[nidx][i]] = uusopn;

        }
    }


    return 0;
}


/*

    for(int i = 1; i <= kurssit; i++){
        int idx = 0;
        int minn = 100000000;
        for(int j = 0; j < 25; j++){
            int pan = 0;
            for(int f: lukkari[j]){
                pair<int,int> p1 = make_pair(min(i, f), max(i, f));
                if(paalle.count(p1))
                    pan+=paalle[p1];
            }
            if(pan < minn){
                minn = pan;
                idx = j;
            }

        }
        lukkari[idx].insert(i);
        paikka[i] = idx;
    }
    save();
    vanha = laske();
    vector<int> jarjest;
    for(int i = 1; i <= kurssit; i++){
        jarjest.push_back(i);
    }
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(jarjest.begin(), jarjest.end(), std::default_random_engine(seed));

    while(true){
        for(int i = 0; i < 25; i++){
            lukkari[i].clear();
        }
        for(int i = 0; i < kurssit; i++){
            int idx = 0;
            int minn = 100000000;
            for(int j = 0; j < 25; j++){
                int pan = 0;
                for(int f: lukkari[j]){
                    pair<int,int> p1 = make_pair(min(jarjest[i], f), max(jarjest[i], f));
                    if(paalle.count(p1))
                        pan+=paalle[p1];
                }
                if(pan < minn){
                    minn = pan;
                    idx = j;
                }

            }
            lukkari[idx].insert(jarjest[i]);
            paikka[jarjest[i]] = idx;
        }
        save();
        seed = std::chrono::system_clock::now().time_since_epoch().count();
        shuffle(jarjest.begin(), jarjest.end(), std::default_random_engine(seed));

    }
    //priority_queue<int, pair<int, int> > siirrot;
    /*int minn = laske();
    for(int i = 1; i <= kurssit; i++){
        int idx = -1;

        for(int j = 0; j < 25; j++){
            lukkari[paikka[i]].erase(i);
            lukkari[j].insert(i);
            paikka[i] = j;
            int uusn = laske();
            if(uusn > minn){
                minn = uusn;
                idx = j;
            }
        }
        if(idx == -1){
            cout << "ei loytynyt parempaa" << endl;
            continue;
        }
        //cout << "loytyi parempi" << endl;
        cout << minn << endl;
        lukkari[paikka[i]].erase(i);
        lukkari[idx].insert(i);
        paikka[i] = idx;
        if(i%10 == 0)
            save();
    }*/
