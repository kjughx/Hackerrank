#include <iostream>
using namespace std;
enum class Fruit { apple, orange, pear };
enum class Color { red, green, orange };

template <typename T> struct Traits;
template<>
struct Traits<enum Fruit> {
    static string name(int index) {
        if (index == 0) return "apple";
        else if (index == 1) return "orange";
        else if (index == 2) return "pear";
        return "unknown";
    }
};

template<>
struct Traits<enum Color> {
    static string name(int index) {
        if (index == 0) return "red";
        else if (index == 1) return "green";
        else if (index == 2) return "orange";
        return "unknown";
    }
};

int main() {
    int t = 0;
    std::cin >> t;

    for (int i = 0; i != t; ++i) {
        int index1;
        std::cin >> index1;
        int index2;
        std::cin >> index2;
        cout << Traits<Color>::name(index1) << " ";
        cout << Traits<Fruit>::name(index2) << "\n";
    }
}
