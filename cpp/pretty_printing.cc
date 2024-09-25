#include <iostream>
#include <iomanip> 
using namespace std;

int main() {
	int T; cin >> T;
	cout << setiosflags(ios::uppercase);
	cout << setw(0xf) << internal;
	while(T--) {
		double A; cin >> A;
		double B; cin >> B;
		double C; cin >> C;

        cout << resetiosflags(ios::uppercase);
        
        std::ios_base::fmtflags ff;
        ff = std::cout.flags();
        ff &= ~std::cout.basefield;   // unset basefield bits
        ff |= std::cout.hex;          // set hex
        ff |= std::cout.showbase;     // set showbase
        std::cout.flags(ff);
        
        cout << setw(0x0) << internal;
        cout << (int)A << endl;
        
        ff &= ~std::cout.hex;
        std::cout.flags(ff);
        std::cout.setf( std::ios::fixed, std:: ios::floatfield );
        std::cout << std::setfill ('_') << std::setw (15);
        
        char number[100000];
        snprintf(number, 100, "%c%.2f", B > 0 ? '+' : '-', B);
        cout << number << endl;
        
        cout << setiosflags(ios::uppercase);
        cout << std::scientific;;
        std::cout.precision(9);
        cout << C << endl;
	}
	return 0;

}
