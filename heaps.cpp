#include<iostream>
#include <climits>
#include <vector>

using namespace std;

class Heap{
	private:

	vector<int> vec;
	int max_size;
	int size;
	bool ismax;

	public:

	Heap(int capacity);
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

		while(i != 0 && vec[parent(i)] > vec[i]){
			int temp = vec[i];
			vec[i] = vec[parent(i)];
			vec[parent(i)] = temp;
			i = parent(i);
		}
	}
	else{
		while(i != 0 && vec[i] > vec[parent(i)]){
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
		while(i != 0 && vec[parent(i)] > vec[i]){
			int temp = vec[i];
			vec[i] = vec[parent(i)];
			vec[parent(i)] = temp;
			i = parent(i);
		}

		extract();
	}
	else{
		vec[i] = INT_MAX;
		while(i != 0 && vec[parent(i)] < vec[i]){
			int temp = vec[i];
			vec[i] = vec[parent(i)];
			vec[parent(i)] = temp;
			i = parent(i);
		}

		extract();
	}
}

void Heap::maxHeapify(int i){
	int r = right(i);
	int l = left(i);
	int max = i;

	if(l < size && vec[l] > vec[i]){
		max = l;
	}
	if(r < size && vec[r] > vec[i]){
		max = r;
	}
	if(max != i){
		int temp = vec[max];
		vec[max] = vec[i];
		vec[i] = temp;
		maxHeapify(max);
	}

	ismax = true;
}

void Heap::minHeapify(int i){

	int r = right(i);
	int l = left(i);
	int min = i;

	if(l < size && vec[l] < vec[i]){
		min = l;
	}
	if(r < size && vec[r] < vec[i]){
		min = r;
	}
	if(min != i){
		int temp = vec[min];
		vec[min] = vec[i];
		vec[i] = temp;
		minHeapify(min);
	}

	ismax = false;
}

int main(){

	return 0;
}