#include <array>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdint.h>
#include <assert.h>
#include <bitset>

using namespace std;

/*
__Problem__
    You are given four integers: N,S,P,Q.
    You will use them in order to create the sequence with the following pseudo-code.

    a[0] = S (modulo 2^31)
    for i = 1 to N-1
        a[i] = a[i-1]*P+Q (modulo 2^31) 

    Calculate the number of distinct integers in the sequence.

_Input Format_
    Four space separated integers on a single line, N, S, P and Q respectively.

_Output Format_
    A single integer that denotes the number of distinct integers in the sequence.

_Constraints_
    0 <= N <= 10e8
    0 <= S, P, Q <= 2^31

_Sample Input_
    3 1 1 1

_Sample Output_
    3

_Explanation_
    a = [1, 2, 3]
    Hence, there are different integers in the sequence.
*/

int main() {
    uint32_t N, S, P, Q;
    cin >> N >> S >> P >> Q;
    printf("%u %u %u", S, P, Q);

    std::bitset<499841161> ba = 0;

    int count = 1;
    while (--N) {
        S = S*P+Q;
        if (!ba[S]){
            ba.set(S);
            count += 1;
        }
    }

    printf("%d\n", count); 
    
    return 0;
}
