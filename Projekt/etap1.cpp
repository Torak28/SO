/*Przy wyświetlaniu jest opóźnienie :c no i dodatkowo to jest tylko czekanie na jeden wątek i potem na drugi :c*/

#include "header.h"

using namespace std;

class Klient
{
public:
	int id;
	string Imie;
	Klient(int i, string s) {
		id = i;
		Imie = s;
	}
};



//MUTEX
mutex mx;
mutex mc;

//Watki:
void ProducentKlientow(int ile);
void PodchodzenieDoStolikow(int ile);
void Ncurses();

//Zasoby:
vector <Klient> KolejkaCzekajaca;
vector <Klient> Stolik1;
vector <Klient> Stolik2;
vector <Klient> Stolik3;
vector <Klient> Stolik4;

//Zmienne:
string Imiona[8] = {"Jarek", "Pawel", "Marek", "Asia", "Ryszard", "Dorota", "Kasia", "Monika" };
int wielkoscStolika = 4;


bool run = true;
int zapelniona = 0;
condition_variable gotowe;

int main()
{
	srand(time(NULL));

	//watki
	thread TProducenic(ProducentKlientow, 10);
	thread TPrzetwarzacze = thread(PodchodzenieDoStolikow, 10);
	thread TNcurses = thread(Ncurses);

	//łaczenie
	TNcurses.join();
	TProducenic.join();
	TPrzetwarzacze.join();
	return 0;
}


void ProducentKlientow(int ile)
{
	srand(time(NULL));
	do {
		Klient k1(ile, Imiona[rand() % 8]);
		unique_lock<mutex> locker(mx);
		KolejkaCzekajaca.push_back(k1);
		locker.unlock();
		this_thread::sleep_for(std::chrono::seconds(1));
		ile--;
	} while (ile);
	zapelniona = 1;
	gotowe.notify_all();
}

void PodchodzenieDoStolikow(int ile)
{
	unique_lock<mutex> locker(mx);
	gotowe.wait(locker, [] {return zapelniona == 1; });
	if (KolejkaCzekajaca.size() == 10) {
		do {
			if (!KolejkaCzekajaca.empty()) {
				if (Stolik1.size() < wielkoscStolika) {
					unique_lock<mutex> lockerMC(mc);
					Stolik1.push_back(KolejkaCzekajaca.front());
					KolejkaCzekajaca.erase(KolejkaCzekajaca.begin());
					lockerMC.unlock();
				}
				else if (Stolik2.size() < wielkoscStolika) {
					unique_lock<mutex> lockerMC(mc);
					Stolik2.push_back(KolejkaCzekajaca.front());
					KolejkaCzekajaca.erase(KolejkaCzekajaca.begin());
					lockerMC.unlock();
				}
				else if (Stolik3.size() < wielkoscStolika) {
					unique_lock<mutex> lockerMC(mc);
					Stolik3.push_back(KolejkaCzekajaca.front());
					KolejkaCzekajaca.erase(KolejkaCzekajaca.begin());
					lockerMC.unlock();
				}
				else if (Stolik4.size() < wielkoscStolika) {
					unique_lock<mutex> lockerMC(mc);
					Stolik4.push_back(KolejkaCzekajaca.front());
					KolejkaCzekajaca.erase(KolejkaCzekajaca.begin());
					lockerMC.unlock();
				}
				else {
					continue;
				}
			}
			ile--;
		} while (ile);
	}
	locker.unlock();
	run = false;
}

void wypiszKolejke() {
	unique_lock<mutex> locker(mx);
	if (!KolejkaCzekajaca.empty()) {
		cout << "Kolejka: " << endl;
		for (int i = 0; i < KolejkaCzekajaca.size(); i++)
		{
			cout << KolejkaCzekajaca[i].id << ": " << KolejkaCzekajaca[i].Imie << endl;
		}
	}
	locker.unlock();
}

void wypiszStolik(vector<Klient> x, int i) {
	unique_lock<mutex> lockerMC(mc);
	if (!x.empty()) {
		cout << "Stolik " << i << ": " << endl;
		for (int i = 0; i < x.size(); i++)
		{
			cout << x[i].id << ": " << x[i].Imie << endl;
			this_thread::sleep_for(std::chrono::seconds(1));
		}
	}
	lockerMC.unlock();
}

void Ncurses()
{
	for (;;){
		system("cls");
		wypiszKolejke();
		wypiszStolik(Stolik1, 1);
		wypiszStolik(Stolik2, 2);
		wypiszStolik(Stolik3, 3);
		wypiszStolik(Stolik4, 4);
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}


