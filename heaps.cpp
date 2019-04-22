#include<iostream>
#include <climits>
#include <vector>
#include "item.h"

using namespace std;

class Heap{
	private:

	int max_size;
	//int size;
	bool ismax = true;

	public:

	int size;
	Heap(int capacity);
	vector<Item> vec;
	void minHeapify(int i);
	void maxHeapify(int i);
	int parent(int i){
		return (i-1)/2;
	}
	int right(int i){
		return (2*i+2);
	}
	int left(int i){
		return (2*i+1);
	}
	void insertKey(int n);
	void deleteKey(int i);
	int extract();
	void convertMaxHeap();
	void convertMinHeap();
};

Heap::Heap(int capacity){
	size = 0;
	max_size = capacity;
	vec.resize(capacity);
}

void Heap::insertKey(int n){
	size++;
	int i = size-1;
	vec[i] = n;

	if(ismax == false){

		while(i != 0 && vec[parent(i)]->damage > vec[i]->damage){
			int temp = vec[i];
			vec[i] = vec[parent(i)];
			vec[parent(i)] = temp;
			i = parent(i);
		}
	}
	else{
		while(i != 0 && vec[i]->damage > vec[parent(i)]->damage){
			int temp = vec[i];
			vec[i] = vec[parent(i)];
			vec[parent(i)] = temp;
			i = parent(i);
		}


	}
}

int Heap::extract(){
	if(size <= 0){
		return -1;
	}
	if(size == 1){
		size--;
		return vec[0];
	}

	int val = vec[0];
	vec[0] = vec[size-1];
	size--;
	if(ismax == false){
		minHeapify(0);
	}
	else{
		maxHeapify(0);
	}

	return val;
}

void Heap::deleteKey(int i){
	if(ismax == false){
		vec[i] = INT_MIN;
		while(i != 0 && vec[parent(i)]->damage > vec[i]->damage){
			int temp = vec[i];
			vec[i] = vec[parent(i)];
			vec[parent(i)] = temp;
			i = parent(i);
		}

		extract();

	}
	else{
		vec[i] = INT_MAX;
		while(i != 0 && vec[parent(i)]->damage < vec[i]->damage){
			int temp = vec[i];
			vec[i] = vec[parent(i)];
			vec[parent(i)] = temp;
			i = parent(i);
		}

		extract();
	}
}

void Heap::maxHeapify(int i){

	int l = left(i);
	int r = right(i);
	int largest = i;
	if(l < size && vec[l]->damage > vec[i]->damage){
		largest = l;
	}
	if(r < size && vec[r]->damage > vec[largest]->damage){
		largest = r;
	}
	if(largest != i){
		int temp = vec[i];
		vec[i] = vec[largest];
		vec[largest] = temp;
		maxHeapify(largest);
	}
}

void Heap::convertMaxHeap(){
	for(int i = (size-2)/2; i >= 0; i--){
		maxHeapify(i);
	}
}
void Heap::minHeapify(int i){

	int l = left(i);
	int r = right(i);
	int smallest = i;

	if(l < size && vec[l]->damage < vec[i]->damage){
		smallest = l;
	}
	if(r < size && vec[r]->damage < vec[smallest]->damage){
		smallest = r;
	}
	if(smallest != i){
		int temp = vec[i];
		vec[i] = vec[smallest];
		vec[smallest] = temp;
		minHeapify(smallest);
	}
}

void Heap::convertMinHeap(){
	for(int i = (size-2)/2; i >= 0; i--){
		minHeapify(i);
	}
}

int main(){

	//inserts values as max heap automatically, call convertMinHeap to change, then convertMaxheap to change back if necessary
	return 0;
}
