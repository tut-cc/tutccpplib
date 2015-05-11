#include <queue>
#include <unordered_set>
#include <vector>
#include <functional>
#include <iostream>

template <typename S, typename P, typename GS>
struct Dijkstra
{
    struct Hash { size_t operator()(S const& s) const { return s.hash(); } };

    Dijkstra(GS f) : fn(f) {}
    GS fn;

    S solve(S init)
    {
        std::priority_queue<S, std::vector<S>, std::greater<S>> pq;
        std::unordered_set<S, Hash> ss;

        pq.push(init);
        while(!pq.empty()){
            S s = pq.top(); pq.pop();
            auto g = ss.find(s);
            if(g != ss.end()) { if(*g > s) continue; else ss.erase(g); }
            ss.insert(s);
            fn.iterP(s, [&](P const & p){ pq.push(p.apply(s)); });
        }

        auto l = &*(ss.begin());
        for(auto& e: ss)
            if(e > *l)
                l = &e;

        return *l;
    }
};


/** example Project Euler 18
using uint = unsigned int;
std::vector<std::vector<uint>> v = {{75},
{95,64},
{17,47,82},
{18,35,87,10},
{20, 4,82,47,65},
{19, 1,23,75, 3,34},
{88, 2,77,73, 7,63,67},
{99,65, 4,28, 6,16,70,92},
{41,41,26,56,83,40,80,70,33},
{41,48,72,33,47,32,37,16,94,29},
{53,71,44,65,25,43,91,52,97,51,14},
{70,11,33,28,77,73,17,78,39,68,17,57},
{91,71,52,38,17,14,91,43,58,50,27,29,48},
{63,66, 4,68,89,53,67,30,73,16,69,87,40,31},
{04,62,98,27,23, 9,70,98,73,93,38,53,60, 4,23}};

// 状態を表す型
struct S {
    uint i, j, c;

    // 評価値の高さを比較
    bool operator>(S const & e) const { return c > e.c; }

    // 状態が等しいか比較
    bool operator==(S const & e) const { return i == e.i && j == e.j; }

    // ハッシュ関数
    size_t hash() const { return i + j; }
};

// パス(枝)を表す型
struct P {
    uint i, j, c;

    // ある状態から、このパスを通った次の状態への遷移
    S apply(S const & s) const { return {i, j, s.c + c}; }
};

// 全体の状態
struct GS
{
    // ある状態から通ることができるパスを列挙する
    template <typename Fn>
    void iterP(S & s, Fn fn)
    {
        if(s.i == v.size()-1)
            return;

        auto i = s.i+1,
             j = s.j;
        fn({i, j, v[i][j]});
        fn({i, j+1, v[i][j+1]});
    }
};


int main()
{
    GS fn;
    std::cout << Dijkstra<S, P, GS>(fn).solve({0, 0, v[0][0]}).c << std::endl;
    return 0;
}
*/