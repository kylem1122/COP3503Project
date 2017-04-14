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
    
    //put stuff here!
    
    
    return 0; 
}
