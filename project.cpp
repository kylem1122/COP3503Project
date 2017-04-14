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
	
    //load file into array
	ifstream in;
    	string file = "likelihood.txt";
    
   	 in.open(file);
    
    if (!in.is_open()) {
        cerr << "Missing file" << endl;
        return 1;
    }
    
    int almostNum;
    int chanceArray [10][10];
    int a = 0;
    int b = 0;
    while (in >> almostNum){
        chanceArray[a][b] = almostNum;
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

	
    //put stuff here!
    
    
    return 0; 
}
