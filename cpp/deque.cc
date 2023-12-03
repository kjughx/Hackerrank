#include <iostream>
#include <deque> 
using namespace std;

void print_que(std::deque<int> &que) {
    printf("[");
    for(auto &el: que) {
        printf("%d,", el);
    }
    printf("]\n");
}

void printKMax(int arr[], int n, int k){
    int maxid = 0;
    int max;
    std::deque<int> que;
    for(size_t i = 0; i < n; ++i) {
        que.push_back(arr[i]);
        
        if (maxid <= 0){
            max = 0;
            for (size_t j = 0; j < que.size(); j++) {
                if (que[j] > max) {
                    max = que[j];
                    maxid = j;
                }
            }
        }
        if (arr[i] > max) {
            max = arr[i];
            maxid = i % k;
        }
        
        if (que.size() == k) {
            // printf("maxid: %d, max: %d ", maxid, max);
            // print_que(que); 
            printf("%d ", max);
            que.pop_front();
            maxid--;
        }
    }
    printf("\n");
}

int main(){
  
	int t;
	cin >> t;
	while(t>0) {
		int n,k;
    	cin >> n >> k;
    	int i;
    	int arr[n];
    	for(i=0;i<n;i++)
      		cin >> arr[i];
    	printKMax(arr, n, k);
    	t--;
  	}
  	return 0;
}

