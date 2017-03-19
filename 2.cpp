// #include <cstdio>
#include <iostream>
#include <set>
#include <cmath>
using namespace std;
#define MAX_PEOPLE 150010

typedef struct Mynode {
    long long size; // only the father maintains the size
    long long father;
}Mynode;

// class Mypair {
//     long long a;
//     long long b;
//     public:
//     Mypair(long long a, long long b) {
//         this->a = a;
//         this->b = b;
//     }
// };

Mynode people[MAX_PEOPLE];

//find the father + path compression
long long find(long long x) {
    if (people[x].father == x) {
        return x;
    }
    return people[x].father = find(people[x].father);
}

//connect to set + restore size in the new father
void connect(long long a, long long b) {
    long long f1 = find(a);
    long long f2 = find(b);
    if (f1 == f2) {
        return;
    }
    if (people[f1].size > people[f2].size) {
        people[f1].size += people[f2].size;
        people[f2].father = f1;
    } else {
        people[f2].size += people[f1].size;
        people[f1].father = f2;
    }
}

int main() {
    long long n, m;
    cin >> n >> m;
    for(long long i = 0; i <= n; i++) { //initialize people
        people[i].size = 1;
        people[i].father = i;
    }
    set<pair<long long, long long> > pairs;
    for (long long i = 0; i < m; i++) {
        long long a, b;
        cin >> a >> b;
        if (a != b) {
            pairs.insert(*(new pair<long long, long long>(a, b)));
            pairs.insert(*(new pair<long long, long long>(b, a)));
            connect(a, b);
        }
    }
    long long num_of_edge = pairs.size()/2;
    long long expect_edge = 0;
    for (long long i = 1; i <= n; i++) {
        if (find(i) == i) { // father of the set
            long long size_of_this = people[i].size;
            expect_edge += (size_of_this-1)*size_of_this/2;
        }
    }
    if (expect_edge == num_of_edge) {
        cout << "YES";
    } else {
        cout << "NO";
    }
    return 0;
}
