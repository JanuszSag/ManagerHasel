#define _CRT_SECURE_NO_WARNINGS

#include "Header.h"



class haslo {
private:
	friend std::ostream& operator<<(const std::ostream& o, haslo h);
	friend std::vector<haslo> find(std::vector<haslo> original, std::string szukana);
public:
	std::string pass;
	std::string desc;
	std::string kategoria;
	std::string login;
	std::string website;
	haslo(std::string desc, std::string pass,std::string cat) {
		this->pass = pass;
		this->desc = desc;
		this->kategoria = cat;
		this->login = "null";
		this->website = "null";
	}
	haslo(std::string desc, std::string pass, std::string cat, std::string log, std::string web) {
		this->pass = pass;
		this->desc = desc;
		this->kategoria = cat;
		this->login = log;
		this->website = web;
	}
	void test() {
		std::cout << "Test";
	}
	std::string fun(int x) const {
		switch (x) {
		case 1:
			return pass;
		case 2:
			return desc;
		case 3:
			return kategoria;
		case 4: 
			return login;
		case 5:
			return website;
		}
	}
	~haslo() {

	}
};

std::ostream& operator<<(const std::ostream& o, haslo h) {
	return std::cout <<"Opis: " << h.desc << "\t Haslo: "<< h.pass << "\t Kategoria: " << h.kategoria<<"\t Login: "<<h.login<<"\t Witryna internetowa: "<<h.website;
}
/*
* metoda print wypisuje zawartosc listy
* param list = lista ktora ma byc wypisana
*/
void print(std::vector<haslo> const& list)
{
	for (haslo const& i : list) {
		std::cout <<i << std::endl;
	}
}

/*
* metoda find wyszukuje wartosc szukana w kazdym elemencie na kazdym polu w hasle
* param original = lista hasel w ktorych mamy wyszukiwac napis
* param szukana = wartosc szukana w liscie hasel
* funkcja zwraca vector hasel w ktorych wystepuje wartosc szukana
*/
std::vector<haslo> find(std::vector<haslo> original, std::string szukana) {
	std::vector<haslo> tmp;
	for (haslo p : original) {
		if (p.desc == szukana || p.kategoria == szukana || p.login == szukana || p.pass == szukana || p.website == szukana) {
			tmp.push_back(p);
			std::cout << "ZNALAZLEM!" << std::endl;
		}
	}
	return tmp;
}
/*
* metoda contain zwraca wartosc true lub false, w zaleznosci, czy dany napis wystepuje w wektorze
* param v = vector, ktory ma sprawdzic czy dany element sie w nim znajduje
* param content = napis ktorego szukamy w vectorze
*/
bool contain(std::vector<std::string> v, std::string content) {
	for (std::string s : v) {
		if (s == content) return true;
	}
	return false;
}
std::ifstream file;
std::ofstream output;
int counter = 1;
std::string godzina, minuta, sekunda; 
time_t now;
struct tm* localTime;
/*
*metoda line zwraca wartosc kolejnej lini z pliku otworzonego
*/
std::string line() {


	time(&now);
	localTime = localtime(&now);

	godzina = std::to_string(localTime->tm_hour);
	minuta = std::to_string(localTime->tm_min);
	sekunda = std::to_string(localTime->tm_sec);

	std::string tmp;
	std::getline(file,tmp);
	if (counter == 11) {
		tmp += godzina[0];
		tmp += godzina[1];
	}
	if (counter == 22) {
		tmp += minuta[0];
		tmp += minuta[1];
	}
	if (counter == 33) {
		tmp += sekunda[0];
		tmp += sekunda[1];
	}
	std::string tmp2 = "";
	int i = 0;
	if (counter == 11 || counter == 22 || counter == 33) i = 2;
	while (i < tmp.length()) {
		tmp2 += tmp[i];
		i++;
	}
	return tmp2;
}
/*
* metoda zaszyfruj szyfruje podana w argumenci linie
* param linia = linia do zaszyfrowania
* return zaszyfrowana linia
*/
std::string zaszyfruj(std::string linia) {
	std::string tmp = "";


	for (int i = 0; i < linia.length(); i+=4)
	{	
		tmp += ((linia[i] + '1'));
		if (i + 1 < linia.length())
		tmp += ((linia[i+1] + '2'));
		if (i + 2 < linia.length())
		tmp += ((linia[i+2] + '3'));
		if (i + 3 < linia.length())
		tmp += ((linia[i+3] + '4'));
	}
	return tmp+"\n";
}
/*
* metoda odszyfruj odszyfrowuje podany w argumencie tekst, podanym w argumencie szyfrem
* param tekst = tekst do odszyfrowania
* param szyfr = szyfr do odszyfrowania tekstu
*/
std::string odszyfruj(std::string tekst, std::string szyfr) {
	std::string wynik = "";
	std::string tmp = "";
	if (counter == 11 || counter == 22 || counter == 33) {
		for (int i = 2; i < tekst.length(); i++)
		{
			tmp += tekst[i];
		}
		tekst = tmp;
	}
	for (int i = 0; i < tekst.length(); i+=szyfr.length()){
		for (int j = 0; j < szyfr.length(); j++){
			if (i + j < tekst.length()) {
				wynik += tekst[i + j] - szyfr[j];
			}
		}
	}
	return wynik;
}

void uruchomMenu(){
	std::vector<std::string> kategorie;
	srand(time(NULL));
	std::vector<haslo> tmp;
	std::vector<std::string> katTMP;
	char left = 'a', right = 'z';
	int l = 0, iloscZnakow, znak;
	std::vector<haslo> hasla;
	
	std::string nazwa = "null", pass = "null", kat = "null", wariant = "null", login = "null", strona = "null", linia, szyfr, sciezka, napis, wyborHasla;
	bool czyDuze, czyZnakiSpecjalne;
	std::cout << "Witaj w managerze hasel!\n"<<
	"Wpisz nazwe lub sciezke pliku z zapisanymi haslami : ";
	std::cin >> sciezka;
	file.open(sciezka);
	if (!file.is_open()) {
		std::cout << "Nie udalo sie otworzyc: " + sciezka;
		return;
	}
	std::cout << "Otworzylem: " + sciezka << std::endl;
	std::cout << "Wpisz szyfr: "; std::cin >> szyfr;
	while (!file.eof()) {
		getline(file, wariant); counter++;
		if (wariant == "dpc") {
			nazwa = odszyfruj(line(), szyfr); counter++;
			pass = odszyfruj(line(), szyfr); counter++;
			kat = odszyfruj(line(), szyfr); counter++;
			hasla.push_back(haslo(nazwa, pass, kat));
			kategorie.push_back(kat);
		}
		else if (wariant == "dpcl")
		{
			nazwa = odszyfruj(line(), szyfr); counter++;
			pass = odszyfruj(line(), szyfr); counter++;
			kat = odszyfruj(line(), szyfr); counter++;
			login = odszyfruj(line(), szyfr); counter++;
			hasla.push_back(haslo(nazwa, pass, kat, login, strona));
			kategorie.push_back(kat);
		}
		else if (wariant == "dpcw") {
			nazwa = odszyfruj(line(), szyfr); counter++;
			pass = odszyfruj(line(), szyfr); counter++;
			kat = odszyfruj(line(), szyfr); counter++;
			strona = odszyfruj(line(), szyfr); counter++;
			hasla.push_back(haslo(nazwa, pass, kat, login, strona));
			kategorie.push_back(kat);
		}
		else if (wariant == "dpclw") {
			nazwa = odszyfruj(line(), szyfr); counter++;
			pass = odszyfruj(line(), szyfr); counter++;
			kat = odszyfruj(line(), szyfr); counter++;
			login = odszyfruj(line(), szyfr); counter++;
			strona = odszyfruj(line(), szyfr); counter++;
			hasla.push_back(haslo(nazwa, pass, kat, login, strona));
			kategorie.push_back(kat);
		}
		wariant = nazwa = pass = kat = login = strona = "";
	}
	counter = 1;

	bool running = true;
	std::string wybor;
	int opcja;
	printf("\033c");
	while (running) {
		std::cout << "Witaj w managerze hasel!" << std::endl << "MENU:" << std::endl;
		std::cout << "1. Wyszukaj hasla" << std::endl;
		std::cout << "2. Posortuj hasla" << std::endl;
		std::cout << "3. Dodaj haslo" << std::endl;
		std::cout << "4. Edytuj hasla" << std::endl;
		std::cout << "5. Usun haslo" << std::endl;
		std::cout << "6. Dodaj kategorie" << std::endl;
		std::cout << "7. Usun kategorie" << std::endl;
		std::cout << "8. Wyjdz i zapisz do pliku" << std::endl;
		std::cin >> wybor; 
		std::vector<haslo> tmp;
		printf("\033c");
		std::string wyraz;
		switch (stoi(wybor)) {
		case 1:
			std::cout << "Wpisz jakie haslo wyszukac: ";
			std::cin >> napis;
			tmp = find(hasla, napis);
			printf("\033c");
			print(tmp);
			system("pause");
			break;
		case 2:
			int wyraz1, wyraz2;
			std::cout << "Wedlug jakich dwoch pol mam posortowac 1.haslo 2.opis 3.kategoria 4.login 5.witryna : " << std::endl;
			std::cin >> wyraz1 >> wyraz2;
			std::sort(hasla.begin(), hasla.end(), [wyraz1, wyraz2](const haslo& h1, const haslo& h2) {

				if (h1.fun(wyraz1) == h2.fun(wyraz1)) {
					return h1.fun(wyraz2).compare(h2.fun(wyraz2));
				}
				return h1.fun(wyraz1).compare(h2.fun(wyraz1));
				});
			printf("\033c");
			break;
		case 3:
			std::cout << "Podaj opis hasla: "; std::cin >> nazwa;
			std::cout << "Czy chcesz podac haslo sam, czy stworzyc ci automatycznie? (y/n) "; std::cin >> wyborHasla;
			if (wyborHasla == "n") {
				std::cout << "podaj ilosc liter w hasle (min. 7)"; std::cin >> iloscZnakow;
				while (iloscZnakow < 7) {
					std::cout<<"podaj ilosc liter w hasle (min. 7)"; std::cin >> iloscZnakow;
				}
				std::cout << "Czy maja byc male i wielkie litery? (y/n) "; std::cin >> wybor;
				if (wybor == "y")czyDuze = true;
				else czyDuze = false;

				std::cout << "Czy maja byc znaki specjalne? (y/n) "; std::cin >> wybor;
				if (wybor == "y")czyZnakiSpecjalne = true;
				else czyZnakiSpecjalne = false;
				for (int i = 0; i < iloscZnakow; i++) {
					if (!czyDuze && !czyZnakiSpecjalne)
					{
						znak = (rand() % ('z' - 'a') + 'a');
						pass += znak;
					}
					if (czyDuze && czyZnakiSpecjalne) {
						znak = (rand() % ('z' - '0') + '0');
						pass += znak;
					}
					if (!czyDuze && czyZnakiSpecjalne) {
						do {
							znak = (rand() % ('z' - '0') + '0');
						} while (znak >= 'A' && znak <= 'Z');
						pass += znak;
					}
					if (czyDuze && !czyZnakiSpecjalne) {
						do {
							znak = (rand() % ('z' - '0') + '0');
						} while ((znak > 'Z'  && znak<'a') || znak < 'A');
						pass += znak;
					}
				}
			}

			if (wyborHasla == "y") {
				std::cout << "Podaj haslo: "; std::cin >> pass;
			}
			wyborHasla = "y";
			std::cout << "Podaj kategorie hasla: "; std::cin >> kat;
			std::cout << "Czy chcesz dodac login (y/n)? "; std::cin >> wybor;
			if (wybor == "y") std::cin >> login;
			std::cout << "Czy chcesz dodac witryne (y/n)? "; std::cin >> wybor;
			if (wybor == "y") std::cin >> strona;
			for (haslo p : hasla) {
				if (p.pass == pass) {
					std::cout << "To haslo zostalo juz wykozystane. Czy chcesz kontynuuowac (y/n)? "; std::cin >> wybor;
					if (wybor == "n") {
						wyborHasla = "n";
					}
				}
			}
			if(wyborHasla == "y")hasla.push_back(haslo(nazwa, pass, kat, login, strona));
			nazwa = pass = kat = login = strona = "";
			break;
			printf("\033c");
		case 4:
			std::cout << "Podaj haslo jakie chcesz zmienic: "; std::cin >> pass;
			std::cout << "Podaj jakie pole chcesz zmienic (1.haslo 2.opis 3.kategoria 4.login 5.witryna) : "; std::cin >> wariant;
			switch (stoi(wariant)) {
			case 1:
				std::cout << "Podaj opis: "; std::cin >> nazwa;
				break;
			case 2:
				std::cout << "Podaj haslo: "; std::cin >> pass;
				break;
			case 3:
				std::cout << "Podaj kategorie: "; std::cin >> kat;
				break;
			case 4:
				std::cout << "Podaj login: "; std::cin >> login;
				break;
			case 5:
				std::cout << "Podaj witryne: "; std::cin >> strona;
				break;
			}
			for (haslo p : hasla) {
				if (p.pass == pass) {
					p.desc = nazwa;
					p.pass = pass;
					p.kategoria = kat;
					p.login = login;
					p.website = strona;
				}
			}
			wariant = nazwa = pass = kat = login = strona = "";

			printf("\033c");
			break;
		case 5:
			std::cout << "Podaj haslo jakie chcesz usunac: "; std::cin >> pass;
			for (haslo p : hasla) {
				if(p.pass!=pass)
				tmp.push_back(p);
			}
			hasla.swap(tmp);
			tmp.clear();
			printf("\033c");
			break;
		case 6:
			std::cout << "Podaj informacje o hasle:" << std::endl;
			std::cout << "Opis: "; std::cin >> nazwa;
			std::cout << "haslo: "; std::cin >> pass;
			do {
				std::cout << "Kategoria: "; std::cin >> kat;
				if (!contain(kategorie, kat)) std::cout << "Podanej kategorii nie ma na liscie.\n";
			} while (!contain(kategorie, kat));
			printf("\033c");
			break;
		case 7:
			std::cout << "Podaj nazwe kategorii do usuniecia: ";
			std::cin >> wyraz;
			for (int i = 0; i < hasla.size(); i++)
			{
				if (hasla.at(i).kategoria == wyraz) {
					continue;
				}
				tmp.push_back(hasla.at(i));
			}
			hasla.swap(tmp);
			tmp.clear();
			l = 0;
			for (int i = 0; i <= kategorie.size(); i++)
			{
				if (kategorie.at(i) == wyraz) {
					continue;
				}
				katTMP.push_back(kategorie.at(i));
			}
			kategorie.swap(katTMP);
			printf("\033c");
			break;
		case 8:
			running = false;
			std::cout << "Do jakiego pliku zapisac: "; std::cin >> sciezka;
			output.open(sciezka);
			counter = 1;
			std::cout << godzina;
			for (haslo p : hasla) {
				if (counter == 11) output << godzina;
				if (counter == 22) output << minuta;
				if (counter++ == 33) output << sekunda;
				output << "dpclw\n";
				if (counter == 11) output << godzina;
				if (counter == 22) output << minuta;
				if (counter++ == 33) output << sekunda;
				output << zaszyfruj(p.desc);
				if (counter == 11) output << godzina;
				if (counter == 22) output << minuta;
				if (counter++ == 33) output << sekunda;
				output << zaszyfruj(p.pass);
				if (counter == 11) output << godzina;
				if (counter == 22) output << minuta;
				if (counter++ == 33) output << sekunda;
				output << zaszyfruj(p.kategoria);
				if (counter == 11) output << godzina;
				if (counter == 22) output << minuta;
				if (counter++ == 33) output << sekunda;
				output << zaszyfruj(p.login);
				if (counter == 11) output << godzina;
				if (counter == 22) output << minuta;
				if (counter++ == 33) output << sekunda;
				output << zaszyfruj(p.website); 
			}
			printf("\033c");
			break;
		}
	}
}
