#include <iostream>
#include <thread>
#include <string>
#include <mutex>
#include <fstream>

using namespace std;

class LogFile{
	mutex _mu;
	mutex _mu2;
	ofstream _f;
public:
	LogFile(){
		_f.open("log.txt");
	}
	void shared_print(string id, int value) {
		unique_locker<mutex> locker(_mu, defer_lock);

		locker.lock();
		cout << "From " << id << ": " << value << endl;
		locker.unlock();
	}
};

void func1(LogFile& log){
	for (int i = 0; i > -100; i--){
		log.shared_print("t1", i);
	}
}

int main(){
	LogFile log;
	thread t1(func1, ref(log));
	for (int i = 0; i < 100; i++){
		log.shared_print(string("From Main: "), i);
	}
	t1.join();
	return 0;
}