#include <iostream>
#include <thread>

using namespace std;

class Fctor{
public:
	void operator()(string &msg){
		cout<< "T1 says: " << msg << endl;
		msg = "Hello from the other side";
	}
};

int main()
{
	string s = "Hello World";
	thread t1((Fctor()), ref(s));

	t1.join();		//czekamy na t1 do końca

	cout << "Main says: " << s << endl;

	return 0;
}