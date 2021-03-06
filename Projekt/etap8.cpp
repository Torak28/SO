/*Nie wyświetla kolejki na poczatek to jest smutne :c ALe wypełnianie bajer*/

#include "header.h"

using namespace std;

class Klient
{
public:
	int id;
	string Imie;
	int stan;
	string zamowienie;
	int stolik;
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
	int idZam;
	string Zam;
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
	int idZam;
	string Zam;
	Kucharz(int i, string m, int s) {
		id = i;
		Imie = m;
		stan = s;
	}
};

class Zamowienie
{
public:
	int id;
	int stan;
	string nazwa;
	Zamowienie(int i, string m, int s) {
		id = i;
		nazwa = m;
		stan = s;
	}
};

//MUTEX
mutex mxKlienciStoliki;
mutex mxKelnerzy;
mutex mxKucharze;
mutex mxZamowienia;

//Watki:
void ProducentKlientow(int ile);
void KlienciDoStolikow(int ile);
void ProducentKelnerow(int ile);
void ProducentKucharzy(int ile);
void WyborPotrawy(int ile);
void Gotowanie(int wiela);
void Ncurses();

//Zasoby:
vector <Kelner> Kelnerzy;
vector <Kucharz> Kucharze;
vector <Klient> KolejkaCzekajaca;
vector <Klient> Klienci;
vector <Zamowienie> Zamowienia;


//Zmienne Tablicowe:
string Imiona[8] = { "Jarek", "Pawel", "Marek", "Asia", "Ryszard", "Dorota", "Kasia", "Monika" };
string ImionaKelnerow[4] = { "Mike", "Jane", "Nick", "Kate" };
string ImionaKucharzy[2] = { "Juan", "Miguel" };
string Potrawy[6] = { "Stek", "Pomidorowa", "Carbonara", "Nalesniki", "Jajecznica", "Tosty" };

//Zmienne statyczne:
int static wielkoscStolika = 4;
int static iloscKlientow = 10;
int static ilosdKelnerow = 4;
int static iloscKucharzy = 2;

//Reszta zmiennych
int iter1, iter2, iter3, iter4 = 0;
int ile = 0;
int iterKelner = 0;
int iterKucharz = 0;
int TimeRng = 5;
int TimeRng2 = 10;
vector <string> Kopia;
bool run = true;
bool start = false;


//ZmienneWarunkowe
int KlienciPrzyStolach = 0;
int KelnerzyGotowi = 0;
int KucharzeGotowi = 0;
int potrawyGotowe = 0;
int ugotowaneGotowe = 0;
condition_variable gotoweUgotowane;
condition_variable gotowePotrawy;
condition_variable gotoweKlient;
condition_variable gotoweKelner;
condition_variable gotoweKucharz;

int main()
{
	srand(time(NULL));

	//watki
	thread TNcurses(Ncurses);
	thread TProducenic(ProducentKlientow, iloscKlientow);
	thread TPrzetwarzacze(KlienciDoStolikow, iloscKlientow);
	thread TProducenci(ProducentKelnerow, ilosdKelnerow);
	thread TProducencii(ProducentKucharzy, iloscKucharzy);
	thread TZamowienia(WyborPotrawy, iloscKlientow);
	thread TJedz(Gotowanie, iloscKlientow);

	//łaczenie
	TProducenic.join();
	TPrzetwarzacze.join();
	TProducenci.join();
	TProducencii.join();
	TZamowienia.join();
	TJedz.join();
	TNcurses.join();
	
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
		Kelner k1(iter, ImionaKelnerow[rand() % (sizeof(ImionaKelnerow) / sizeof(*ImionaKelnerow))], 1);
		unique_lock<mutex> locker(mxKelnerzy);
		gotoweKlient.wait(locker, [] {return KlienciPrzyStolach == 1; });
		Kelnerzy.push_back(k1);
		locker.unlock();
		this_thread::sleep_for(std::chrono::milliseconds(500));
		iter++;
		ile--;
	} while (ile);
	KelnerzyGotowi = 1;
	gotoweKelner.notify_all();
}

void ProducentKucharzy(int ile)
{
	srand(time(NULL));
	int iter = 1;
	do {
		Kucharz k1(iter, ImionaKucharzy[rand() % (sizeof(ImionaKucharzy) / sizeof(*ImionaKucharzy))], 1);
		unique_lock<mutex> locker(mxKucharze);
		gotoweKelner.wait(locker, [] {return KelnerzyGotowi == 1; });
		Kucharze.push_back(k1);
		locker.unlock();
		this_thread::sleep_for(std::chrono::milliseconds(500));
		iter++;
		ile--;
	} while (ile);
	KucharzeGotowi = 1;
	gotoweKucharz.notify_all();
}


void KlienciDoStolikow(int ile)
{
	int stolik1 = 0;
	int stolik2 = 0;
	int stolik3 = 0;
	int stolik4 = 0;
	if (KolejkaCzekajaca.size() != 0) {
		do {
			if (!KolejkaCzekajaca.empty()) {
				if (stolik1 < wielkoscStolika) {
					unique_lock<mutex> locker(mxKlienciStoliki);
					KolejkaCzekajaca.front().stolik = 1;
					Klienci.push_back(KolejkaCzekajaca.front());
					KolejkaCzekajaca.erase(KolejkaCzekajaca.begin());
					stolik1++;
					locker.unlock();
				}
				else if (stolik2 < wielkoscStolika) {
					unique_lock<mutex> locker(mxKlienciStoliki);
					KolejkaCzekajaca.front().stolik = 2;
					Klienci.push_back(KolejkaCzekajaca.front());
					KolejkaCzekajaca.erase(KolejkaCzekajaca.begin());
					stolik2++;
					locker.unlock();
				}
				else if (stolik3 < wielkoscStolika) {
					unique_lock<mutex> locker(mxKlienciStoliki);
					KolejkaCzekajaca.front().stolik = 3;
					Klienci.push_back(KolejkaCzekajaca.front());
					KolejkaCzekajaca.erase(KolejkaCzekajaca.begin());
					stolik3++;
					locker.unlock();
				}
				else if (stolik4 < wielkoscStolika) {
					unique_lock<mutex> locker(mxKlienciStoliki);
					KolejkaCzekajaca.front().stolik = 4;
					Klienci.push_back(KolejkaCzekajaca.front());
					KolejkaCzekajaca.erase(KolejkaCzekajaca.begin());
					stolik4++;
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
	gotoweKlient.notify_all();
	run = false;
}

void Gotowanie(int wiela) {
	srand(time(NULL));
	do {
		if (Zamowienia.empty()) {
			continue;
		}
		else {
			unique_lock<mutex> locker(mxZamowienia);
			gotowePotrawy.wait(locker, [] {return potrawyGotowe == 1; });
			Zamowienia[ile].stan = 2;
			Klienci[ile].stan = 3;

			unique_lock<mutex> locker4(mxKelnerzy);
			for (int i = 0; i < Kelnerzy.size(); i++)
			{
				if (Kelnerzy[i].idZam == Zamowienia[ile].id) {
					if (Kelnerzy[i].idZam + ilosdKelnerow <= iloscKlientow) {
						Kelnerzy[i].stan = 2;

						Kelnerzy[i].idZam += ilosdKelnerow;
						int xd = Kelnerzy[i].idZam;
						xd--;
						Kelnerzy[i].Zam = Kopia.back();
						
					}
					else {
						Kelnerzy[i].stan = 3;
					}
				}
			}
			locker4.unlock();

			unique_lock<mutex> locker5(mxKucharze);
			for (int i = 0; i < Kucharze.size(); i++)
			{
				if (Kucharze[i].idZam == Zamowienia[ile].id) {
					if (Kucharze[i].idZam + iloscKucharzy <= iloscKlientow) {
						Kucharze[i].stan = 2;

						Kucharze[i].idZam += iloscKucharzy;
						int xd = Kucharze[i].idZam;
						xd--;
						Kucharze[i].Zam = Kopia.back();

					}
					else {
						Kucharze[i].stan = 3;
					}
				}
			}
			locker5.unlock();

			locker.unlock();
			ile++;
			wiela--;
			if (ile == 7) {
				ugotowaneGotowe = 1;
				gotoweUgotowane.notify_all();
			}
			
		}
		int zmienaCzasowa = 1;// rand() % TimeRng2;
		this_thread::sleep_for(std::chrono::seconds(zmienaCzasowa));
	} while (wiela);
}

void WyborPotrawy(int ile) {
	srand(time(NULL));
	for (int ile = 0; ile < Klienci.size(); ile++) {
		unique_lock<mutex> locker(mxKlienciStoliki);
		gotoweKucharz.wait(locker, [] {return KucharzeGotowi == 1; });
		if (Klienci[ile].stan == 1) {
			Klienci[ile].stan = 2;
			string s = Potrawy[rand() % (sizeof(Potrawy) / sizeof(*Potrawy))];
			Klienci[ile].zamowienie = s;
			Kopia.push_back(s);

			unique_lock<mutex> locker4(mxZamowienia);
			Zamowienie z1(Klienci[ile].id, Klienci[ile].zamowienie, 1);
			Zamowienia.push_back(z1);
			

			int iterKelner = ile % ilosdKelnerow;
			unique_lock<mutex> locker2(mxKelnerzy);
			if (Kelnerzy[iterKelner].stan == 1) {
				Kelnerzy[iterKelner].stan = 2;

				Kelnerzy[iterKelner].idZam = Zamowienia[ile].id;
				Kelnerzy[iterKelner].Zam = Zamowienia[ile].nazwa;
			}
			locker2.unlock();



			int iterKucharz = ile % iloscKucharzy;
			unique_lock<mutex> locker3(mxKucharze);
			if (Kucharze[iterKucharz].stan == 1) {
				Kucharze[iterKucharz].stan = 2;

				Kucharze[iterKucharz].idZam = Zamowienia[ile].id;
				Kucharze[iterKucharz].Zam = Zamowienia[ile].nazwa;
			}
			locker3.unlock();

			locker4.unlock();

		}
		if (Zamowienia.size() == 5) {
			potrawyGotowe = 1;
			gotowePotrawy.notify_all();
		}
		locker.unlock();
		int zmienaCzasowa = 1;// rand() % TimeRng;
		this_thread::sleep_for(std::chrono::seconds(zmienaCzasowa));
	}
}

void wypiszStolik() {
	unique_lock<mutex> locker(mxKlienciStoliki);
	bool juz1 = false;
	bool juz2 = false;
	bool juz3 = false;
	bool juz4 = false;
	if (!Klienci.empty()) {
		string stan;
		cout << "Stolik 1:" << endl;
		for (int i = 0; i < Klienci.size(); i++) {
			if (Klienci[i].stolik == 1) {
				if (Klienci[i].stan == 2) {
					stan = "Zamawiam " + Klienci[i].zamowienie;
				}
				else if(Klienci[i].stan == 3){
					stan = "Jem " + Klienci[i].zamowienie;
				}
				else {
					stan = "czeka na Kelnera";
				}
				cout << setw(3) << Klienci[i].id << setw(2) << ": " << setw(7) << Klienci[i].Imie << setw(3) << " " << setw(10) << stan << endl;
				iter1++;
			}
			else {
				if (!juz1 && iter1 == 0) {
					cout << "  Nie ma nikogo" << endl;
					juz1 = true;
				}
				else {
					continue;
				}

			}
		}
		cout << "Stolik 2:" << endl;
		for (int i = 0; i < Klienci.size(); i++) {
			if (Klienci[i].stolik == 2) {
				if (Klienci[i].stan == 2) {
					stan = "Zamawiam " + Klienci[i].zamowienie;
				}
				else if (Klienci[i].stan == 3) {
					stan = "Jem " + Klienci[i].zamowienie;
				}
				else {
					stan = "czeka na Kelnera";
				}
				cout << setw(3) << Klienci[i].id << setw(2) << ": " << setw(7) << Klienci[i].Imie << setw(3) << " " << setw(10) << stan << endl;
				iter2++;
			}
			else {
				if (!juz2 && iter2 == 0) {
					cout << "  Nie ma nikogo" << endl;
					juz2 = true;
				}
				else {
					continue;
				}

			}
		}
		cout << "Stolik 3:" << endl;
		for (int i = 0; i < Klienci.size(); i++) {
			if (Klienci[i].stolik == 3) {
				if (Klienci[i].stan == 2) {
					stan = "Zamawiam " + Klienci[i].zamowienie;
				}
				else if (Klienci[i].stan == 3) {
					stan = "Jem " + Klienci[i].zamowienie;
				}
				else {
					stan = "czeka na Kelnera";
				}
				cout << setw(3) << Klienci[i].id << setw(2) << ": " << setw(7) << Klienci[i].Imie << setw(3) << " " << setw(10) << stan << endl;
				iter3++;
			}
			else {
				if (!juz3 && iter3 == 0) {
					cout << "  Nie ma nikogo" << endl;
					juz3 = true;
				}
				else {
					continue;
				}

			}
		}
		cout << "Stolik 4:" << endl;
		for (int i = 0; i < Klienci.size(); i++) {
			if (Klienci[i].stolik == 4) {
				if (Klienci[i].stan == 2) {
					stan = "Zamawiam " + Klienci[i].zamowienie;
				}
				else if (Klienci[i].stan == 3) {
					stan = "Jem " + Klienci[i].zamowienie;
				}
				else {
					stan = "czeka na Kelnera";
				}
				cout << setw(3) << Klienci[i].id << setw(2) << ": " << setw(7) << Klienci[i].Imie << setw(3) << " " << setw(10) << stan << endl;
				iter4++;
			}
			else {
				if (!juz4 && iter4 == 0) {
					cout << "  Nie ma nikogo" << endl;
					juz4 = true;
				}
				else {
					continue;
				}

			}
		}
	}
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
	}
	else {
		cout << "  Nie ma nikogo" << endl;
	}
	cout << endl << endl;
	locker.unlock();
}


void wypiszZamowinia() {
	unique_lock<mutex> locker(mxZamowienia);
	string stan;
	cout << "Zamowiania: " << endl;
	if (!Zamowienia.empty()) {
		for (int i = 0; i < Zamowienia.size(); i++)
		{
			if (Zamowienia[i].stan == 1) {
				stan = " otrzymane";
			}
			else if(Zamowienia[i].stan == 2) {
				stan = " ugotowane";
			}
			cout << setw(3) << Zamowienia[i].id << setw(2) << ": " << setw(10) << Zamowienia[i].nazwa << setw(5) << stan << endl;
		}
	}
	else {
		cout << "  Nie ma niczego" << endl;
	}
	cout << Zamowienia.size() << endl;
	locker.unlock();
}

void wypiszKelnerow() {
	unique_lock<mutex> locker(mxKelnerzy);
	string stan;
	cout << "\n\nKelnerzy: " << endl;
	if (!Kelnerzy.empty()) {
		for (int i = 0; i < Kelnerzy.size(); i++)
		{
			if (Kelnerzy[i].stan == 1) {
				stan = "czeka na klienta ";
			}
			else if (Kelnerzy[i].stan == 2) {
				string s1 = "Zamowienie nr." + to_string((int)Kelnerzy[i].idZam);
				string s2 = " na danie: " + (string)Kelnerzy[i].Zam;
				stan = s1 + s2;
			}
			else {
				stan = "czeka na klienta ";
			}
			cout << setw(3) << Kelnerzy[i].id << setw(2) << ": " << setw(7) << Kelnerzy[i].Imie << setw(3) << " " << setw(10) << stan << endl;
		}
	}
	else {
		cout << "  Nie ma nikogo" << endl;
	}
	cout << endl << endl;
	locker.unlock();
}

void wypiszKucharzy() {
	unique_lock<mutex> locker(mxKucharze);
	string stan;
	cout << "\n\nKucharze: " << endl;
	if (!Kucharze.empty()) {
		for (int i = 0; i < Kucharze.size(); i++)
		{
			if (Kucharze[i].stan == 1) {
				stan = "czeka na zamowienia ";
			}
			else if (Kucharze[i].stan == 2) {
				string s1 = "Zamowienie nr." + to_string((int)Kucharze[i].idZam);
				string s2 = " na danie: " + (string)Kucharze[i].Zam;
				stan = s1 + s2;
			}
			else {
				stan = "czeka na zamowienia";
			}
			cout << setw(3) << Kucharze[i].id << setw(2) << ": " << setw(7) << Kucharze[i].Imie << setw(3) << " " << setw(10) << stan << endl;
		}
	}
	else {
		cout << "  Nie ma nikogo" << endl;
	}
	cout << Kucharze.size() << endl;
	locker.unlock();
}

void Ncurses()
{
	for (;;) {
		system("cls");
		wypiszKolejke();
		wypiszStolik();
		wypiszKelnerow();
		wypiszKucharzy();
		wypiszZamowinia();
		this_thread::sleep_for(std::chrono::seconds(1));
	}
}


