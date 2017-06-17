#include <iostream>
#include <thread>

using namespace std;

void func1(){
	cout << "Witaj watku" << endl;
}

int main()
{
	thread t1(func1);

	//t1.join();		//czekamy na t1 do końca
	t1.detach();	//Nieczakmy na t1, działą on jako Demon, gdy main się skończy wcześniej

	if(t1.joinable()){
		t1.join();
	}

	return 0;
}