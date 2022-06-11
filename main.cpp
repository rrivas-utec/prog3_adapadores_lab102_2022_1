#include <iostream>
#include <stack>
#include <queue>
#include <deque>
#include <fstream>
#include <iterator>
#include <type_traits>
#include <functional>
using namespace std;

template <
        typename T,
        typename ...Params,
        template<typename ...> class Adapter,
        typename Function,
        enable_if_t<is_same<Adapter<T>, queue<T>>::value, bool> = true
        >
void for_adapter(Adapter<T, Params...>& adapter, Function fn) {
    while (!adapter.empty()) {
        fn(adapter.front());
        adapter.pop();
    }
}

template <
        typename T,
        typename ...Params,
        template<typename ...> class Adapter,
        typename Function,
        enable_if_t<!is_same<Adapter<T>, queue<T>>::value, bool> = true>
void for_adapter(Adapter<T, Params...>& adapter,Function fn) {
    while (!adapter.empty()) {
        fn(adapter.top());
        adapter.pop();
    }
}

void ejemplo_1() {
    stack<int> s1;
    s1.push(1);
    s1.push(2);
    s1.push(12);
    s1.push(23);

    // while (s1.size() != 0) {
    for_adapter(s1, [](auto value) {
        cout << value << " ";
    });
    cout << endl;
}

void ejemplo_2() {
    deque<int> dq = {1, 4, 5, 60};
    stack<int> s1(dq);

    for_adapter(s1, [](auto value) {
        cout << value << " ";
    });
    cout << endl;
}

void ejemplo_3() {
    vector<int> vc = {1, 4, 5, 60};
    stack<int, vector<int>> s1(vc);

    for_adapter(s1, [](auto value) {
        cout << value << " ";
    });
    cout << endl;
}

void ejemplo_4() {
    deque<int> dq = {1, 4, 5, 60};
    queue<int> qu(dq);

    for_adapter(qu, [](auto value) {
        cout << value << " ";
    });
    cout << endl;
}

 void ejemplo_5() {
    ifstream file("../in.txt");
    deque<int> dq {istream_iterator<int>(file), istream_iterator<int>() };
    stack<int> s1(dq);

     for_adapter(s1, [](auto value) {
         cout << value << " ";
     });
     cout << endl;
 }

 void ejemplo_6() {
     less<int> lt;
     int x = 10;
     int y = 20;
     cout << boolalpha << (x < y) << endl;
     cout << boolalpha << lt(x, y) << endl;

     greater<int> gt;
     cout << boolalpha << (x > y) << endl;
     cout << boolalpha << gt(x, y) << endl;

 }

 void ejemplo_7() {
     ifstream file("../in.txt");
     priority_queue<int> pq {istream_iterator<int>(file), istream_iterator<int>()};
     for_adapter(pq, [](auto value) {
         cout << value << " ";
     });
     cout << endl;

 }

void ejemplo_8() {
    ifstream file("../in.txt");
    priority_queue<int, vector<int>, greater<>> pq {istream_iterator<int>(file), istream_iterator<int>()};
    for_adapter(pq, [](auto value) {
        cout << value << " ";
    });
    cout << endl;
}

class person_t {
    string name;
    int age;
public:
    person_t(const string& name, int age): name(name), age(age) {}
    bool operator <(const person_t& other) const {
        return name < other.name;
    }
    bool operator >(const person_t& other) const {
        return name > other.name;

    }
    bool operator ==(const person_t& other) const {
        return name == other.name;
    }

    friend ostream& operator << (ostream& os, const person_t& self) {
        os << "nombre: " << self.name << " edad: " << self.age;
        return os;
    }
    string get_name() const { return name; }
    int get_age() const { return age; }
};

void ejemplo_9() {
    priority_queue<person_t> pq1;
    pq1.push(person_t("Rosa", 20));
    pq1.push(person_t("Juan", 22));
    for_adapter(pq1, [](auto value) {
        cout << value << endl;
    });
}

void ejemplo_10() {
    priority_queue<person_t, vector<person_t>, greater<>> pq1;
    pq1.push(person_t("Rosa", 20));
    pq1.push(person_t("Juan", 22));
    pq1.push(person_t("Ana", 18));
    pq1.push(person_t("Cecilia", 25));
    for_adapter(pq1, [](auto value) {
        cout << value << endl;
    });
}

void ejemplo_11() {
    auto compare_by_age = [](auto a, auto b) {
        return a.get_age() < b.get_age();
    };
    auto compare_by_name = [](auto a, auto b) {
        return a.get_name() < b.get_name();
    };
    priority_queue<
            person_t,
            vector<person_t>,
            function<bool(person_t, person_t)>
            > pq1{compare_by_name};
    pq1.push(person_t("Rosa", 20));
    pq1.push(person_t("Juan", 22));
    pq1.push(person_t("Ana", 18));
    pq1.push(person_t("Cecilia", 25));
    for_adapter(pq1, [](auto value) {
        cout << value << endl;
    });
}

void ejemplo_12() {
    auto compare_by_age = [](auto a, auto b) {
        return a.get_age() < b.get_age();
    };
    auto compare_by_name = [](auto a, auto b) {
        return a.get_name() < b.get_name();
    };
    priority_queue<
            person_t,
            vector<person_t>,
            decltype(compare_by_name)
    > pq1{compare_by_name};
    pq1.push(person_t("Rosa", 20));
    pq1.push(person_t("Juan", 22));
    pq1.push(person_t("Ana", 18));
    pq1.push(person_t("Cecilia", 25));
    for_adapter(pq1, [](auto value) {
        cout << value << endl;
    });
}

template <typename T>
stack<T> merge_stacks(const stack<T>& a, const stack<T>& b) {

}

void ejemplo_13() {
    deque<int> d1 = {1, 5, 4, 2};
    deque<int> d2 = {10, 50, 40, 20};
    stack<int> s1(d1);
    stack<int> s2(d2);
    auto result = merge_stacks(s1, s2);
    for_adapter(result, [](auto value) {
        cout << value << " ";
    });
    cout << endl;
}

int main(int argc, char **argv) {
//    ejemplo_1();
//    ejemplo_2();
//    ejemplo_3();
//    ejemplo_4();
//    ejemplo_5();
//    ejemplo_6();
//    ejemplo_7();
//    ejemplo_8();
//    ejemplo_9();
    ejemplo_10();
    cout << "---\n";
    ejemplo_11();
    return 0;
}