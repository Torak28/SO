#include <iostream>
#include <thread>

using namespace std;

void func1(){
	cout << "Witaj watku" << endl;
}

int main()
{
	thread t1(func1);

	try{
		for (int i = 0; i < 100; ++i){
			cout << "From main: " << i << endl;
		}
	}catch(...){
		t1.join();
		throw;
	}

	t1.join();		//czekamy na t1 do końca

	return 0;
}