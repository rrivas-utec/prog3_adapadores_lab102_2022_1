#include <iostream>
#include <stack>
#include <queue>
#include <deque>
#include <fstream>
#include <iterator>
using namespace std;

void ejemplo_1() {
    stack<int> s1;
    s1.push(1);
    s1.push(2);
    s1.push(12);
    s1.push(23);

    // while (s1.size() != 0) {
    while (!s1.empty()) {
        cout << s1.top() << endl;
        s1.pop();
    }
}

void ejemplo_2() {
    deque<int> dq = {1, 4, 5, 60};
    stack<int> s1(dq);

    while (!s1.empty()) {
        cout << s1.top() << endl;
        s1.pop();
    }
}

void ejemplo_3() {
    vector<int> vc = {1, 4, 5, 60};
    stack<int, vector<int>> s1(vc);

    while (!s1.empty()) {
        cout << s1.top() << endl;
        s1.pop();
    }
}

void ejemplo_4() {
    deque<int> dq = {1, 4, 5, 60};
    queue<int> qu(dq);

    while(!qu.empty()) {
        cout << qu.front() << endl;
        qu.pop();
    }
}

// VERSIONES SUPERIORES o IGUALES a C++23
// void ejemplo_4() {
//   ifstream file("in.txt");
//   vector<int> vc = {1, 4, 5, 60};
//   stack<int> s1(begin(vc), end(vc));

//   while (!s1.empty()) {
//     cout << s1.top() << endl;
//     s1.pop();
//   }
// }

int main(int argc, char **argv) {
    ejemplo_1();
    ejemplo_2();
    ejemplo_3();
    ejemplo_4();
    return 0;
}