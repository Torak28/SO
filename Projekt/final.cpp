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
void usuwaniekolejki(int ile);
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
int zapelniona = 0;
condition_variable gotowe;
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
	thread TUsuw(usuwaniekolejki, iloscKlientow);

	//łaczenie
	TProducenic.join();
	TPrzetwarzacze.join();
	TProducenci.join();
	TProducencii.join();
	TZamowienia.join();
	TJedz.join();
	TUsuw.join();
	TNcurses.join();
	
	return 0;
}


void ProducentKlientow(int ile)
{
	srand(time(NULL));
	int iter = 1;
	do {
		Klient k1(iter, Imiona[rand() % (sizeof(Imiona) / sizeof(*Imiona))], 1);
		mxKlienciStoliki.lock();
		KolejkaCzekajaca.push_back(k1);
		mxKlienciStoliki.unlock();
		this_thread::sleep_for(std::chrono::seconds(1));
		iter++;
		ile--;
	} while (ile);
	zapelniona = 1;
	gotowe.notify_all();
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
		this_thread::sleep_for(std::chrono::seconds(1));
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
		this_thread::sleep_for(std::chrono::seconds(1));
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
	unique_lock<mutex> locker(mxKlienciStoliki);
	gotowe.wait(locker, [] {return zapelniona == 1; });
	locker.unlock();
	if (KolejkaCzekajaca.size() != 0) {
		do {
			if (!KolejkaCzekajaca.empty()) {
				if (stolik1 < wielkoscStolika) {
					mxKlienciStoliki.lock();	
					KolejkaCzekajaca.front().stolik = 1;
					Klienci.push_back(KolejkaCzekajaca.front());
					KolejkaCzekajaca.erase(KolejkaCzekajaca.begin());
					mxKlienciStoliki.unlock();
					stolik1++;
				}
				else if (stolik2 < wielkoscStolika) {
					mxKlienciStoliki.lock();
					KolejkaCzekajaca.front().stolik = 2;
					Klienci.push_back(KolejkaCzekajaca.front());
					KolejkaCzekajaca.erase(KolejkaCzekajaca.begin());
					mxKlienciStoliki.unlock();
					stolik2++;
				}
				else if (stolik3 < wielkoscStolika) {
					mxKlienciStoliki.lock();
					KolejkaCzekajaca.front().stolik = 3;
					Klienci.push_back(KolejkaCzekajaca.front());
					KolejkaCzekajaca.erase(KolejkaCzekajaca.begin());
					mxKlienciStoliki.unlock();
					stolik3++;
				}
				else if (stolik4 < wielkoscStolika) {
					mxKlienciStoliki.lock();
					KolejkaCzekajaca.front().stolik = 4;
					Klienci.push_back(KolejkaCzekajaca.front());
					KolejkaCzekajaca.erase(KolejkaCzekajaca.begin());
					mxKlienciStoliki.unlock();
					stolik4++;
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
			for (int i = 0; i < (int)Kelnerzy.size(); i++)
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
			for (int i = 0; i < (int)Kucharze.size(); i++)
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
			if (ile == iloscKlientow) {
				ugotowaneGotowe = 1;
				gotoweUgotowane.notify_all();
			}
			
		}
		int zmienaCzasowa =  rand() % TimeRng;//1
		this_thread::sleep_for(std::chrono::seconds(zmienaCzasowa));
	} while (wiela);
}

void usuwaniekolejki(int ile) {
	srand(time(NULL));
	do {
		unique_lock<mutex> locker(mxKlienciStoliki);
		gotoweUgotowane.wait(locker, [] {return ugotowaneGotowe == 1; });

		Klienci.erase(Klienci.begin());
		Zamowienia.erase(Zamowienia.begin());

		locker.unlock();
		int zmienaCzasowa =  rand() % TimeRng;//1
		this_thread::sleep_for(std::chrono::seconds(zmienaCzasowa));
		ile--;
	} while (ile);
}

void WyborPotrawy(int ile) {
	srand(time(NULL));
	unique_lock<mutex> locker(mxKlienciStoliki);
	gotoweKucharz.wait(locker, [] {return KucharzeGotowi == 1; });
	locker.unlock();
	for (int ile = 0; ile < (int)Klienci.size(); ile++) {
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
		int zmienaCzasowa =  rand() % TimeRng;//1
		this_thread::sleep_for(std::chrono::seconds(zmienaCzasowa));
	}
}

void wypiszStolik() {
	init_pair(1,COLOR_GREEN,COLOR_BLACK);
    	init_pair(2,COLOR_MAGENTA,COLOR_BLACK);
    	init_pair(3,COLOR_RED,COLOR_BLACK);
    	init_pair(4,COLOR_YELLOW,COLOR_BLACK);
	unique_lock<mutex> locker(mxKlienciStoliki);
	bool juz1 = false;
	bool juz2 = false;
	bool juz3 = false;
	bool juz4 = false;
		string stan;
		attron(COLOR_PAIR(1));
		printw("Stolik 1:\n");
		attroff(COLOR_PAIR(1));
		for (int i = 0; i < (int)Klienci.size(); i++) {
			if (Klienci[i].stolik == 1) {
				if (Klienci[i].stan == 2) {
					attron(COLOR_PAIR(3));
					stan = "Zamawiam " + Klienci[i].zamowienie;
					printw("  %-2d: %s\t\t%s\n", Klienci[i].id, Klienci[i].Imie.c_str(), stan.c_str());
					attroff(COLOR_PAIR(3));
				}
				else if(Klienci[i].stan == 3){
					attron(COLOR_PAIR(2));
					stan = "Jem " + Klienci[i].zamowienie;
					printw("  %-2d: %s\t\t%s\n", Klienci[i].id, Klienci[i].Imie.c_str(), stan.c_str());
					attroff(COLOR_PAIR(2));
				}
				else {
					attron(COLOR_PAIR(4));
					stan = "czeka na Kelnera";
					printw("  %-2d: %s\t\t%s\n", Klienci[i].id, Klienci[i].Imie.c_str(), stan.c_str());
					attroff(COLOR_PAIR(4));
				}
				iter1++;
			}
			else {
				if (!juz1 && iter1 == 0) {
					printw("  Nie ma nikogo\n");
					juz1 = true;
				}
				else {
					continue;
				}

			}
		}
		attron(COLOR_PAIR(1));
		printw("Stolik 2:\n");
		attroff(COLOR_PAIR(1));
		for (int i = 0; i < (int)Klienci.size(); i++) {
			if (Klienci[i].stolik == 2) {
				if (Klienci[i].stan == 2) {
					attron(COLOR_PAIR(3));
					stan = "Zamawiam " + Klienci[i].zamowienie;
					printw("  %-2d: %s\t\t%s\n", Klienci[i].id, Klienci[i].Imie.c_str(), stan.c_str());
					attroff(COLOR_PAIR(3));
				}
				else if (Klienci[i].stan == 3) {
					attron(COLOR_PAIR(2));
					stan = "Jem " + Klienci[i].zamowienie;
					printw("  %-2d: %s\t\t%s\n", Klienci[i].id, Klienci[i].Imie.c_str(), stan.c_str());
					attroff(COLOR_PAIR(2));
				}
				else {
					attron(COLOR_PAIR(4));
					stan = "czeka na Kelnera";
					printw("  %-2d: %s\t\t%s\n", Klienci[i].id, Klienci[i].Imie.c_str(), stan.c_str());
					attroff(COLOR_PAIR(4));
				}
				iter2++;
			}
			else {
				if (!juz2 && iter2 == 0) {
					printw("  Nie ma nikogo\n");
					juz2 = true;
				}
				else {
					continue;
				}

			}
		}
		attron(COLOR_PAIR(1));
		printw("Stolik 3:\n");
		attroff(COLOR_PAIR(1));
		for (int i = 0; i < (int)Klienci.size(); i++) {
			if (Klienci[i].stolik == 3) {
				if (Klienci[i].stan == 2) {
					attron(COLOR_PAIR(3));
					stan = "Zamawiam " + Klienci[i].zamowienie;
					printw("  %-2d: %s\t\t%s\n", Klienci[i].id, Klienci[i].Imie.c_str(), stan.c_str());
					attroff(COLOR_PAIR(3));
				}
				else if (Klienci[i].stan == 3) {
					attron(COLOR_PAIR(2));
					stan = "Jem " + Klienci[i].zamowienie;
					printw("  %-2d: %s\t\t%s\n", Klienci[i].id, Klienci[i].Imie.c_str(), stan.c_str());
					attroff(COLOR_PAIR(2));
				}
				else {
					attron(COLOR_PAIR(4));
					stan = "czeka na Kelnera";
					printw("  %-2d: %s\t\t%s\n", Klienci[i].id, Klienci[i].Imie.c_str(), stan.c_str());
					attroff(COLOR_PAIR(4));
				}
				iter3++;
			}
			else {
				if (!juz3 && iter3 == 0) {
					printw("  Nie ma nikogo\n");
					juz3 = true;
				}
				else {
					continue;
				}

			}
		}
		attron(COLOR_PAIR(1));
		printw("Stolik 4:\n");
		attroff(COLOR_PAIR(1));
		for (int i = 0; i < (int)Klienci.size(); i++) {
			if (Klienci[i].stolik == 4) {
				if (Klienci[i].stan == 2) {
					attron(COLOR_PAIR(3));
					stan = "Zamawiam " + Klienci[i].zamowienie;
					printw("  %-2d: %s\t\t%s\n", Klienci[i].id, Klienci[i].Imie.c_str(), stan.c_str());
					attroff(COLOR_PAIR(3));
				}
				else if (Klienci[i].stan == 3) {
					attron(COLOR_PAIR(2));
					stan = "Jem " + Klienci[i].zamowienie;
					printw("  %-2d: %s\t\t%s\n", Klienci[i].id, Klienci[i].Imie.c_str(), stan.c_str());
					attroff(COLOR_PAIR(2));
				}
				else {
					attron(COLOR_PAIR(4));
					stan = "czeka na Kelnera";
					printw("  %-2d: %s\t\t%s\n", Klienci[i].id, Klienci[i].Imie.c_str(), stan.c_str());
					attroff(COLOR_PAIR(4));
				}
				iter4++;
			}
			else {
				if (!juz4 && iter4 == 0) {
					printw("  Nie ma nikogo\n");
					juz4 = true;
				}
				else {
					continue;
				}

			}
		}
	locker.unlock();
}

void wypiszKolejke() {


	init_pair(1,COLOR_GREEN,COLOR_BLACK);
    	init_pair(2,COLOR_MAGENTA,COLOR_BLACK);
    	init_pair(3,COLOR_RED,COLOR_BLACK);
    	init_pair(4,COLOR_YELLOW,COLOR_BLACK);
	unique_lock<mutex> locker(mxKlienciStoliki);

	attron(COLOR_PAIR(1));
	printw("Kolejka:\n");
	attroff(COLOR_PAIR(1));
	if (!KolejkaCzekajaca.empty()) {
		for (int i = 0; i < (int)KolejkaCzekajaca.size(); i++)
		{
			printw("  %-2d: %s\n", KolejkaCzekajaca[i].id, KolejkaCzekajaca[i].Imie.c_str());
		}
	}
	else {
		printw("  Nie ma nikogo\n");
	}
	printw("\n\n");
	locker.unlock();
}


void wypiszZamowinia() {
	init_pair(1,COLOR_GREEN,COLOR_BLACK);
    	init_pair(2,COLOR_MAGENTA,COLOR_BLACK);
    	init_pair(3,COLOR_RED,COLOR_BLACK);
    	init_pair(4,COLOR_YELLOW,COLOR_BLACK);
	unique_lock<mutex> locker(mxZamowienia);
	string stan;
	attron(COLOR_PAIR(1));
	printw("Zamowienia:\n");
	attroff(COLOR_PAIR(1));
	if (!Zamowienia.empty()) {
		for (int i = 0; i < (int)Zamowienia.size(); i++)
		{
			if (Zamowienia[i].stan == 1) {
				attron(COLOR_PAIR(4));
				stan = " otrzymane";
				printw("  %-2d: %-10s %-20s\n", Zamowienia[i].id, Zamowienia[i].nazwa.c_str(), stan.c_str());
				attroff(COLOR_PAIR(4));
			}
			else if(Zamowienia[i].stan == 2) {
				attron(COLOR_PAIR(3));
				stan = " ugotowane";
				printw("  %-2d: %-10s %-20s\n", Zamowienia[i].id, Zamowienia[i].nazwa.c_str(), stan.c_str());
				attroff(COLOR_PAIR(3));
			}
		}
	}
	else {
		printw("  Nie ma nikogo\n");
	}
	printw("\n\n");
	locker.unlock();
}

void wypiszKelnerow() {
	init_pair(1,COLOR_GREEN,COLOR_BLACK);
    	init_pair(2,COLOR_MAGENTA,COLOR_BLACK);
    	init_pair(3,COLOR_RED,COLOR_BLACK);
    	init_pair(4,COLOR_YELLOW,COLOR_BLACK);
	unique_lock<mutex> locker(mxKelnerzy);
	string stan;
	attron(COLOR_PAIR(1));
	printw("\n\nKelnerzy:\n");
	attroff(COLOR_PAIR(1));
	if (!Kelnerzy.empty()) {
		for (int i = 0; i < (int)Kelnerzy.size(); i++)
		{
			if (Kelnerzy[i].stan == 1) {
				attron(COLOR_PAIR(4));
				stan = "czeka na klienta ";
				printw("  %-2d: %s\t\t%s\n", Kelnerzy[i].id, Kelnerzy[i].Imie.c_str(), stan.c_str());
				attroff(COLOR_PAIR(4));
			}
			else if (Kelnerzy[i].stan == 2) {
				attron(COLOR_PAIR(3));
				string s1 = "Zamowienie nr." + to_string((int)Kelnerzy[i].idZam);
				string s2 = " na danie: " + (string)Kelnerzy[i].Zam;
				stan = s1 + s2;
				printw("  %-2d: %s\t\t%s\n", Kelnerzy[i].id, Kelnerzy[i].Imie.c_str(), stan.c_str());
				attroff(COLOR_PAIR(4));
			}
			else {
				attron(COLOR_PAIR(4));
				stan = "czeka na klienta ";
				printw("  %-2d: %s\t\t%s\n", Kelnerzy[i].id, Kelnerzy[i].Imie.c_str(), stan.c_str());
				attroff(COLOR_PAIR(4));
			}
		}
	}
	else {
		printw("  Nie ma nikogo\n");
	}
	printw("\n\n");
	locker.unlock();
}

void wypiszKucharzy() {
	init_pair(1,COLOR_GREEN,COLOR_BLACK);
    	init_pair(2,COLOR_MAGENTA,COLOR_BLACK);
    	init_pair(3,COLOR_RED,COLOR_BLACK);
    	init_pair(4,COLOR_YELLOW,COLOR_BLACK);
	unique_lock<mutex> locker(mxKucharze);
	string stan;
	attron(COLOR_PAIR(1));
	printw("\n\nKucharze:\n");
	attroff(COLOR_PAIR(1));
	if (!Kucharze.empty()) {
		for (int i = 0; i < (int)Kucharze.size(); i++)
		{
			if (Kucharze[i].stan == 1) {
				attron(COLOR_PAIR(4));
				stan = "czeka na zamowienia ";
				printw("  %-2d: %s\t\t%s\n", Kucharze[i].id, Kucharze[i].Imie.c_str(), stan.c_str());
				attroff(COLOR_PAIR(4));
			}
			else if (Kucharze[i].stan == 2) {
				attron(COLOR_PAIR(3));
				string s1 = "Zamowienie nr." + to_string((int)Kucharze[i].idZam);
				string s2 = " na danie: " + (string)Kucharze[i].Zam;
				stan = s1 + s2;
				printw("  %-2d: %s\t\t%s\n", Kucharze[i].id, Kucharze[i].Imie.c_str(), stan.c_str());
				attroff(COLOR_PAIR(3));
			}
			else {
				attron(COLOR_PAIR(4));
				stan = "czeka na zamowienia";
				printw("  %-2d: %s\t\t%s\n", Kucharze[i].id, Kucharze[i].Imie.c_str(), stan.c_str());
				attroff(COLOR_PAIR(4));
			}
		}
	}
	else {
		printw("  Nie ma nikogo\n");
	}
	printw("\n\n");
	locker.unlock();
}

void Ncurses()
{
	initscr();
	start_color();
	init_pair(5,COLOR_BLUE,COLOR_BLACK);
	for (;;) {
		clear();
		attron(COLOR_PAIR(5));
		printw("Jaroslaw Ciolek-Zelechowski, 218386. Restouracja na watkach.\n\n");
		attroff(COLOR_PAIR(5));
		wypiszKolejke();
		wypiszStolik();
		wypiszKelnerow();
		wypiszKucharzy();
		wypiszZamowinia();
		refresh();
		this_thread::sleep_for(std::chrono::seconds(1));
	}
	getch();
	endwin();
}
