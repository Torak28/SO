/*Nie wyświetla kolejki na poczatek to jest smutne :c ALe wypełnianie bajer*/

#include "header.h"

using namespace std;

class Klient
{
public:
	int id;
	string Imie;
	int stan;
	Klient(int i, string m, int s) {
		id = i;
		Imie = m;
		stan = s;
	}
};

class Kelner
{
public:
	int id;
	string Imie;
	int stan;
	Kelner(int i, string m, int s) {
		id = i;
		Imie = m;
		stan = s;
	}
};

class Kucharz
{
public:
	int id;
	string Imie;
	int stan;
	Kucharz(int i, string m, int s) {
		id = i;
		Imie = m;
		stan = s;
	}
};



//MUTEX
mutex mxKlienciStoliki;
mutex mxKelnerzy;
mutex mxKucharze;

//Watki:
void ProducentKlientow(int ile);
void KlienciDoStolikow(int ile);
void ProducentKelnerow(int ile);
void ProducentKucharzy(int ile);
void Ncurses();

//Zasoby:
vector <Kelner> Kelnerzy;
vector <Kucharz> Kucharze;
vector <Klient> KolejkaCzekajaca;
vector <Klient> Stolik1;
vector <Klient> Stolik2;
vector <Klient> Stolik3;
vector <Klient> Stolik4;


//Zmienne:
string Imiona[8] = {"Jarek", "Pawel", "Marek", "Asia", "Ryszard", "Dorota", "Kasia", "Monika" };
string ImionaKelnerow[4] = { "Mike", "Jane", "Nick", "Kate" };
string ImionaKucharzy[2] = { "Juan", "Miguel" };
int wielkoscStolika = 4;


bool run = true;
int KlienciPrzyStolach = 0;
condition_variable gotowe;

int main()
{
	srand(time(NULL));

	//watki
	thread TProducenci(ProducentKelnerow, 4);
	thread TProducencii(ProducentKucharzy, 2);
	thread TProducenic(ProducentKlientow, 10);
	thread TPrzetwarzacze = thread(KlienciDoStolikow, 10);
	thread TNcurses = thread(Ncurses);

	//łaczenie
	TNcurses.join();
	TProducenic.join();
	TProducenci.join();
	TProducencii.join();
	TPrzetwarzacze.join();
	return 0;
}


void ProducentKlientow(int ile)
{
	srand(time(NULL));
	int iter = 1;
	do {
		Klient k1(iter, Imiona[rand() % (sizeof(Imiona) / sizeof(*Imiona))], 1);
		unique_lock<mutex> locker(mxKlienciStoliki);
		KolejkaCzekajaca.push_back(k1);
		locker.unlock();
		this_thread::sleep_for(std::chrono::milliseconds(500));
		iter++;
		ile--;
	} while (ile);
}


void ProducentKelnerow(int ile)
{
	srand(time(NULL));
	int iter = 1;
	do {
		Kelner k1(iter, ImionaKelnerow[rand() % (sizeof(ImionaKelnerow)/ sizeof(*ImionaKelnerow))], 1);
		unique_lock<mutex> locker(mxKelnerzy);
		gotowe.wait(locker, [] {return KlienciPrzyStolach == 1; });
		Kelnerzy.push_back(k1);
		locker.unlock();
		this_thread::sleep_for(std::chrono::milliseconds(500));
		iter++;
		ile--;
	} while (ile);
}


void ProducentKucharzy(int ile)
{
	srand(time(NULL));
	int iter = 1;
	do {
		Kucharz k1(iter, ImionaKucharzy[rand() % (sizeof(ImionaKucharzy) / sizeof(*ImionaKucharzy))], 1);
		unique_lock<mutex> locker(mxKucharze);
		gotowe.wait(locker, [] {return KlienciPrzyStolach == 1; });
		Kucharze.push_back(k1);
		locker.unlock();
		this_thread::sleep_for(std::chrono::milliseconds(500));
		iter++;
		ile--;
	} while (ile);
}

void KlienciDoStolikow(int ile)
{
	if (KolejkaCzekajaca.size() != 0) {
		do {
			if (!KolejkaCzekajaca.empty()) {
				if (Stolik1.size() < wielkoscStolika) {
					unique_lock<mutex> locker(mxKlienciStoliki);
					Stolik1.push_back(KolejkaCzekajaca.front());
					KolejkaCzekajaca.erase(KolejkaCzekajaca.begin());
					locker.unlock();
				}
				else if (Stolik2.size() < wielkoscStolika) {
					unique_lock<mutex> locker(mxKlienciStoliki);
					Stolik2.push_back(KolejkaCzekajaca.front());
					KolejkaCzekajaca.erase(KolejkaCzekajaca.begin());
					locker.unlock();
				}
				else if (Stolik3.size() < wielkoscStolika) {
					unique_lock<mutex> locker(mxKlienciStoliki);
					Stolik3.push_back(KolejkaCzekajaca.front());
					KolejkaCzekajaca.erase(KolejkaCzekajaca.begin());
					locker.unlock();
				}
				else if (Stolik4.size() < wielkoscStolika) {
					unique_lock<mutex> locker(mxKlienciStoliki);
					Stolik4.push_back(KolejkaCzekajaca.front());
					KolejkaCzekajaca.erase(KolejkaCzekajaca.begin());
					locker.unlock();
				}
				else {
					continue;
				}
			}
			this_thread::sleep_for(std::chrono::seconds(1));
			ile--;
		} while (ile != 0);
	}
	KlienciPrzyStolach = 1;
	gotowe.notify_all();
	run = false;
}

void wypiszStolik(vector<Klient> x, int i) {
	unique_lock<mutex> locker(mxKlienciStoliki);
	cout << "Stolik " << i << ": " << endl;
	if (!x.empty()) {
		string stan = "czeka na posilek";
		for (int i = 0; i < x.size(); i++)
		{
			if (x[i].stan != 1) {
				stan = "coś innego xd";
			}
			cout << setw(3) << x[i].id << setw(2) << ": " << setw(7) << x[i].Imie << setw(3) << " " << setw(10) << stan << endl;
		}
	}else {
		cout << "  Nie ma nikogo" << endl;
	}
	cout << endl;
	locker.unlock();
}

void wypiszKolejke() {
	unique_lock<mutex> locker(mxKlienciStoliki);
	cout << "Kolejka: " << endl;
	if (!KolejkaCzekajaca.empty()) {
		for (int i = 0; i < KolejkaCzekajaca.size(); i++)
		{
			cout << KolejkaCzekajaca[i].id << ": " << KolejkaCzekajaca[i].Imie << endl;
		}
	}else {
		cout << "  Nie ma nikogo" << endl;
	}
	cout << endl << endl;
	locker.unlock();
}

void wypiszKelnerow() {
	unique_lock<mutex> locker(mxKelnerzy);
	string stan = "czeka na klienta";
	cout << "\n\nKelnerzy: " << endl;
	if (!Kelnerzy.empty()) {
		for (int i = 0; i < Kelnerzy.size(); i++)
		{
			if (Kelnerzy[i].stan != 1) {
				stan = "coś innego xd";
			}
			cout << setw(3) << Kelnerzy[i].id << setw(2) << ": " << setw(7) << Kelnerzy[i].Imie << setw(3) << " " << setw(10) << stan << endl;
		}
	}else {
		cout << "  Nie ma nikogo" << endl;
	}
	cout << endl << endl;
	locker.unlock();
}


void wypiszKucharzy() {
	unique_lock<mutex> locker(mxKucharze);
	string stan = "czeka na zamowienie";
	cout << "\n\nKucharze: " << endl;
	if (!Kucharze.empty()) {
		for (int i = 0; i < Kucharze.size(); i++)
		{
			if (Kucharze[i].stan != 1) {
				stan = "coś innego xd";
			}
			cout << setw(3) << Kucharze[i].id << setw(2) << ": " << setw(7) << Kucharze[i].Imie << setw(3) << " " << setw(10) << stan << endl;
		}
	}else {
		cout << "  Nie ma nikogo" << endl;
	}
	cout << endl << endl;
	locker.unlock();
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
		wypiszKelnerow();
		wypiszKucharzy();
		this_thread::sleep_for(std::chrono::seconds(1));
	}
}


