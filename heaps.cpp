#include<iostream>
#include <climits>
#include <vector>

using namespace std;

class Heap{
	private:

	int max_size;
	int size;
	bool ismax;

	public:

	Heap(int capacity);
	vector<int> vec;
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
	int r, l;
	int temp;
	ismax = true;

	while(1){
		l = left(i);
		r = right(i);

		if(l >= size){
			return;
		}

		if(r == size || vec[l] >= vec[r]){
			if(vec[l] > vec[i]){
				temp = vec[l];
				vec[l] = vec[i];
				vec[i] = temp;
				i = l;
			}
			else{
				return;
			}
		}
		else if(vec[r] > vec[i]){
			temp = vec[r];
			vec[r] = vec[i];
			vec[i] = temp;
			i = r;
		}
		else{
			return;
		}
	}
}

void Heap::minHeapify(int i){

	int r, l;
	int temp;
	ismax = false;

	while(1){
		l = left(i);
		r = right(i);

		if(l >= size){
			return;
		}

		if(r == size || vec[l] <= vec[r]){
			if(vec[l] < vec[i]){
				temp = vec[l];
				vec[l] = vec[i];
				vec[i] = temp;
				i = l;
			}
			else{
				return;
			}
		}
		else if(vec[r] < vec[i]){
			temp = vec[r];
			vec[r] = vec[i];
			vec[i] = temp;
			i = r;
		}
		else{
			return;
		}
	}
}

int main(){
	Heap h(10);

	h.insertKey(10);
	h.insertKey(2);
	h.insertKey(12);
	h.insertKey(1);
	h.insertKey(5);
	h.insertKey(7);

	h.maxHeapify(0);

	for(int i = 0; i < 10; i++){
		cout << h.vec[i] << " ";
	}
	cout << endl;

	return 0;
}
