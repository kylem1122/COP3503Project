#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include "project.h"

using namespace std;


int main(int argc, char ** argv){
  	string fileLoad;
  	transform(fileLoad.begin(), fileLoad.end(), fileLoad.begin(), ::tolower);

	if (argc >= 2) {
	    fileLoad = argv[1];
	}
	else {
		cout << "Invalid choice. Try again." << endl;
		return -1;
	}
	if(fileLoad != "erase" || fileLoad != "load"){
		cout << "Invalid choice. Try again." << endl;
		return -1;
	}
	
	int chanceArray [10][10];
    //load file into array
	if(fileLoad == "load"){
    ifstream in;
    string file = "likelihood.txt";
    
    in.open(file.c_str());
    
    if (!in.is_open()) {
        cerr << "Missing file" << endl;
        return 1;
    }
    
    int num;
    int chanceArray [10][10];
    int a = 0;
    int b = 0;
    
    while (in >> num){
        chanceArray[a][b] = num;
        b++;
        if(b == 10){
            a++;
            b = 0;
        }
        if(a == 10){
            break;
        }
    }
    
    for(int i = 0; i <10; i++){
        for(int j = 0; j < 10; j++){
            cout<< chanceArray[i][j] << " ";
        }
        cout << endl;
    }
    
    in.close();
	}
	else{
		for(int i = 0; i <10; i++){
			for(int j = 0; j < 10; j++){
				chanceArray[i][j] = 1;
			}
		}
	}

	
    //put stuff here!
    
    
    return 0; 
}
