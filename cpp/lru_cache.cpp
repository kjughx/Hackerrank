#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <cassert>
using namespace std;

struct Node{
   Node* next;
   Node* prev;
   int value;
   int key;
   Node(Node* p, Node* n, int k, int val):prev(p),next(n),key(k),value(val){};
   Node(int k, int val):prev(NULL),next(NULL),key(k),value(val){};
};

class Cache{
   
   protected: 
   map<int,Node*> mp; //map the key to the node in the linked list
   int cp;  //capacity
   Node* tail; // double linked list tail pointer
   Node* head; // double linked list head pointer
   virtual void set(int, int) = 0; //set function
   virtual int get(int) = 0; //get function

};


class LRUCache : public Cache {


    public:
        LRUCache(int cap){
            cp = cap;
			head = NULL;
			tail = NULL;
        }

    void set(int key, int val){

		if (mp.size() == 0)	{
			Node *newNode = new Node(key, val);
			head = newNode;
			tail = newNode;
			mp.insert(pair<int, Node*>(key, newNode));
		}
        else if(mp.size() == 1 && mp.find(key) != mp.end()){
            mp.find(key)->second->value = val;
        }
		else if (mp.size() < cp && mp.find(key) == mp.end()) {
			Node *newNode = new Node(NULL, head, key, val);
			head->prev = newNode;
			if(cp == 1){
				tail->prev = head;
			}
			head = newNode;
			mp.insert(pair<int, Node*>(key, newNode));	
		}
		else if(mp.size() < cp && mp.find(key) != mp.end()){
			Node *node = mp.find(key)->second;
			if(node->next != NULL && node->prev != NULL){
				node->value = val;
				node->next->prev = node->prev;
				node->prev->next = node->next;
				node->next = head;
				head = node;
				node->prev = NULL;
				node->next->prev = node;
			}
			else if(node->next == NULL){
				node->value = val;
				node->prev->next = NULL;
				node->next = head;
				tail = node->prev;
				head = node;
				node->prev = NULL;
				node->next->prev = node;
			}
			else if(node->prev == NULL){
				node->value = val;	
			}
		}
		else if(mp.size() == cp && mp.find(key) == mp.end()){
			Node *newNode = new Node(NULL, head, key, val);
			head->prev = newNode;
			mp.erase(tail->key);
			tail = tail->prev;
			tail->next = NULL;
			head = newNode;
			mp.insert(pair<int, Node*>(key, newNode));
		}
		else if(mp.size() == cp && mp.find(key) != mp.end()){
			Node *node = mp.find(key)->second;

			if(node->next != NULL && node->prev != NULL){
				node->value = val;
				node->next->prev = node->prev;
				node->prev->next = node->next;
				node->next = head;
				head = node;
				node->prev = NULL;
				node->next->prev = node;
			}
			else if(node->next == NULL){
				node->value = val;
				node->prev->next = NULL;
				node->next = head;
				tail = node->prev;
				head = node;
				node->prev = NULL;
				node->next->prev = node;
			}
			else if(node->prev == NULL){
				node->value = val;
			}
		}
		
    }

	int get(int key){
		if(mp.find(key) != mp.end()){
			return mp.find(key)->second->value;
		}
		return -1;
	}

	void display(){
		Node *node = head;
		Node *last;
		cout << "Forward: " ;
		if(node->prev == NULL){
			cout << "NULL ";
		}
		while(node != NULL) {
			cout << "(" << node->key << ", " << node->value << ")";
			last = node;
			node = last->next;
			if(node != NULL){
				cout << "<==>";
			}
			if(node == NULL){
				cout << " NULL";
			}
		}
	   cout << endl;	
	   node = tail;
	   Node *next;
	   cout << "Backward: ";
	   if(node->next== NULL){
		   cout << "NULL ";
	   }
	   while(node != NULL){
		   cout << "(" <<  node->key << ", " << node->value << ")";
		   next = node;
		   node = node->prev;
		   if(node != NULL){
			   cout << "<==>";
		   }
		   if(node == NULL){
			   cout << " NULL";
		   }
	   }
	   cout << endl;

		cout << "Map: ";
		for(auto const& m : mp){
			cout << "(" << m.first << ", " << m.second->value << ")";
		}
		cout << endl;

	}

};


int main() {
   int n, capacity,i;
   cin >> n >> capacity;
   LRUCache l(capacity);
   for(i=0;i<n;i++) {
      string command;
      cin >> command;
      if(command == "get") {
         int key;
         cin >> key;
         cout << l.get(key) << endl;
      }
      else if(command == "set") {
         int key, value;
         cin >> key >> value;
         l.set(key,value);
      }
   }
   return 0;
}
