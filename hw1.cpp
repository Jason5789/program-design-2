#include <iostream>
#include <string>
using namespace std;

int main(int  argc, char**  argv) {
	int num=stoi(argv[1]);
	int max=0;

	for(int i=0 ; i<=num ; i++){
		cout << "(" << i << "," << num-i << ")" <<endl;
		if( max < i*(num-i) ){
			max = i*(num-i);
		}
	}

	cout << max <<endl;

	return 0;
}
