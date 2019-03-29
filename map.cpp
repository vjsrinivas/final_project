#include "map.h"

Map::Map(ifstream& FILE){
	if(FILE.is_open()){
		string buffer;
		while(cin >> buffer){
			printf("%s\n", buffer.c_str());
		}
	}
	else{
		printf("Error: file is not opened\n");	
	}
}

Map::Map(){}


