#include <iostream>
using namespace std;

template<bool... args>
int reversed_binary_value() {
    const size_t size = sizeof...(args);
    bool bools[size] = {args...};
    int res = 0;
    for (size_t i = 0; i < size; i++) {
        res |= bools[i] << i;
    }
    return res;
}

// Below is for testing the solution

template <int n, bool...digits>
struct CheckValues {
  	static void check(int x, int y)
  	{
    	CheckValues<n-1, 0, digits...>::check(x, y);
    	CheckValues<n-1, 1, digits...>::check(x, y);
  	}
};

template <bool...digits>
struct CheckValues<0, digits...> {
  	static void check(int x, int y)
  	{
    	int z = reversed_binary_value<digits...>();
    	std::cout << (z+64*y==x);
  	}
};

int main()
{
  	int t; std::cin >> t;

  	for (int i=0; i!=t; ++i) {
		int x, y;
    	cin >> x >> y;
    	CheckValues<6>::check(x, y);
    	cout << "\n";
  	}
}
