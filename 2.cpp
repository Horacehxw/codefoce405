#include <cstdio>
#include <iostream>
#include <set>
#include <cmath>
using namespace std;
#define MAX_PEOPLE 150010

typedef struct Mynode {
    int size; // only the father maintains the size
    int father;
}Mynode;

class Mypair {
    int a;
    int b;
    public:
    Mypair(int a, int b) {
        this->a = a;
        this->b = b;
    }
};

Mynode people[MAX_PEOPLE];

//find the father + path compression
int find(int x) {
    if (people[x].father == x) {
        return x;
    }
    return people[x].father = find(people[x].father);
}

//connect to set + restore size in the new father
void connect(int a, int b) {
    int f1 = find(a);
    int f2 = find(b);
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
    int n, m;
    scanf("%d %d", &n, &m);
    for(int i = 0; i < MAX_PEOPLE; i++) { //initialize people
        people[i].size = 1;
        people[i].father = i;
    }
    set<pair<int, int> > pairs;
    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        if (a != b) {
            pairs.insert(*(new pair<int, int>(a, b)));
            pairs.insert(*(new pair<int, int>(b, a)));
            connect(a, b);
        }
    }
    int num_of_edge = pairs.size()/2;
    int expect_edge = 0;
    for (int i = 1; i < MAX_PEOPLE; i++) {
        if (find(i) == i) { // father of the set
            int size_of_this = people[i].size;
            expect_edge += (size_of_this-1)*size_of_this/2;
        }
    }
    if (expect_edge == num_of_edge) {
        printf("YES");
    } else {
        printf("NO");
    }
    return 0;
}
