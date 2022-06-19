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
		this->login = "";
		this->website = "";
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

bool contain(std::vector<std::string> v, std::string content) {
	for (std::string s : v) {
		if (s == content) return true;
	}
	return false;
}


void uruchomMenu(){
	std::vector<std::string> kategorie;
	int l = 0;
	std::vector<haslo> hasla;
	std::ifstream file;
	std::string sciezka,line,napis;
	std::string nazwa="", pass = "", kat = "", wariant = "",login="",strona="";
	std::cout << "Witaj w managerze hasel!\n"<<
	"Wpisz nazwe lub sciezke pliku z zapisanymi haslami : ";
	std::cin >> sciezka;
	file.open(sciezka);
	if (!file.is_open()) {
		std::cout << "Nie udalo sie otworzyc: " + sciezka;
		return;
	}
	std::cout << "Otworzylem: " + sciezka << std::endl;
	while (!file.eof()) {
		getline(file, wariant);
		if (wariant == "dpc") {
			getline(file, nazwa);
			getline(file, pass);
			getline(file, kat);
			hasla.push_back(haslo(nazwa, pass, kat));
			kategorie.push_back(kat);
		}
		else if (wariant == "dpcl")
		{
			getline(file, nazwa);
			getline(file, pass);
			getline(file, kat);
			getline(file, login);
			hasla.push_back(haslo(nazwa, pass, kat, login, strona));
			kategorie.push_back(kat);
		}
		else if (wariant == "dpcw") {
			getline(file, nazwa);
			getline(file, pass);
			getline(file, kat);
			getline(file, strona);
			hasla.push_back(haslo(nazwa, pass, kat, login, strona));
			kategorie.push_back(kat);
		}
		else if (wariant == "dpclw") {
			getline(file, nazwa);
			getline(file, pass);
			getline(file, kat);
			getline(file, login);
			getline(file, strona);
			hasla.push_back(haslo(nazwa, pass, kat, login, strona));
			kategorie.push_back(kat);
		}
		wariant = nazwa = pass = kat = login = strona = "";
	}
	
	bool running = true;
	std::string wybor;
	int opcja;
	while (running) {
		std::cout << "Witaj w managerze hasel!" << std::endl << "MENU:" << std::endl;
		std::cout << "1. Wyszukaj hasla" << std::endl;
		std::cout << "2. Posortuj hasla" << std::endl;
		std::cout << "3. Dodaj haslo" << std::endl;
		std::cout << "4. Edytuj hasla" << std::endl;
		std::cout << "5. Usun haslo" << std::endl;
		std::cout << "6. Dodaj kategorie" << std::endl;
		std::cout << "7. Usun kategorie" << std::endl;
		std::cout << "8. Wyjdz" << std::endl;
		std::cin >> wybor; 
		std::vector<haslo> tmp;
		printf("\033c");
		std::string wyraz;
		switch (stoi(wybor)) {
		case 1:
			std::cout << "Wpisz jakie haslo wyszukac: ";
			std::cin >> napis;
			tmp = find(hasla,napis);
			print(tmp);
			break;
		case 2:
			int wyraz1, wyraz2;
			std::cout << "Wedlug jakich dwoch pol mam posortowac 1.haslo 2.opis 3.kategoria 4.login 5.witryna : " << std::endl;
			std::cin >> wyraz1 >> wyraz2;
			std::sort(hasla.begin(), hasla.end(), [wyraz1,wyraz2](const haslo& h1, const haslo& h2) {
				
				if (h1.fun(wyraz1) == h2.fun(wyraz1)) {
					return h1.fun(wyraz2).compare(h2.fun(wyraz2));
				}
				return h1.fun(wyraz1).compare(h2.fun(wyraz1));
				});
			break;
		case 3:

			break;
		case 6:
			std::cout << "Podaj informacje o hasle:" << std::endl;
			std::cout << "Opis: "; std::cin >> nazwa;
			std::cout << "haslo: "; std::cin >> pass;
			do {
				std::cout << "Kategoria: "; std::cin >> kat;
				if (!contain(kategorie, kat)) std::cout << "Podanej kategorii nie ma na liscie.\n";
			} while (!contain(kategorie, kat));
			break;
		case 7:
			std::cout << "Podaj nazwe kategorii do usuniecia: ";
			std::cin >> wyraz;
			for (int i = 0; i <= hasla.size()+1; i++)
			{
				std::cout << hasla.at(i-l).desc << "\n";

				if (hasla.at(i-l).kategoria == wyraz) {
					hasla.erase(hasla.begin() + i-l);
					l++;
				}
			}
			l = 0;
			for (int i = 0; i <= kategorie.size(); i++)
			{
				if (kategorie.at(i-l) == wyraz) {
					kategorie.erase(kategorie.begin() + i-l);
					l++;
				}
			}
			break;
		case 8:
			running = false;
			break;
		}
	}
}
