#include <iostream>
#include <thread>
#include <string>
#include <mutex>

using namespace std;

mutex mu;

void shared_print(string msg, int id) {
	//mu.lock();	//To może być teoretycznie niebezpieczne, więc
	lock_guard<mutex> guard(mu);
	cout << msg << id << endl;
	//mu.unlock();
}

void func1() {
	for (int i = 0; i > -100; i--) {
		shared_print(string("From t1: "), i);
	}
}

int main()
{
	thread t1(func1);

	for (int i = 0; i < 100; i++) {
		shared_print(string("From main: "), i);
	}

	t1.join();		//czekamy na t1 do końca

	system("pause");
	return 0;
}