#include <iostream>
#include <vector>
#include <map>
#include <stdlib.h>
#include <random>
#include <ctime>  
using namespace std;

int main(int argc, char **argv){ 

    if( argc !=2) {
        cerr << "Usage: ./generate_map.cpp" << endl;
        return -1;
    }

    map <int, char> eachnum;
	int randomnum;
	const int n = stoi(argv[1]);
	srand (time(NULL));
	
	eachnum.insert(make_pair(1, 'g'));
	eachnum.insert(make_pair(2, 'G'));
	eachnum.insert(make_pair(3, 'f'));
	eachnum.insert(make_pair(4, 'h'));
	eachnum.insert(make_pair(5, 'r'));
	eachnum.insert(make_pair(7, 'm'));

	cout << "6" << '\n';
	cout << "f 3\n" << "g 1\n" << "G 2\n" << "h 4\n" << "m 7\n" << "r 5\n"; 
	cout << n << " " << n << '\n';

	for (int i = 0; i < (n*n); i++) {
		if (i % n == 0 && i != 0)
			cout << '\n'; // this loop prints the map

		    randomnum = rand() % 6 + 1;
		        if (randomnum == 6)
			    randomnum = 7;
		            cout << eachnum.find(randomnum)->second << " ";
	} // here above it randomly chooses and prints out a number 1-6

	cout << "\n0 0\n";
	cout << n-1 << " " << n-1 << '\n';

return 0;
}
