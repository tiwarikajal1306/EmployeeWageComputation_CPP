#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

int main() {
	srand(time(0));
	int is_Present = rand() % 2 +1;
	if(is_Present == 1){
		cout<< "Employee is present";
	}
	else{
		cout<< "Employee is absent";
	}
return 0;

}
