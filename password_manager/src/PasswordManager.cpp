#include <PasswordManager/PasswordManager.h>

namespace password_manager
{
	class haslo
	{
	private:
		friend std::ostream &operator<<(const std::ostream &o, haslo h);
		std::string pass;
		std::string desc;
		int id;

	public:
		static int identyfikator;
		haslo(std::string pass, std::string desc)
		{
			this->pass = pass;
			this->desc = desc;
			this->id = identyfikator++;
		}
	};

	std::ostream &operator<<(const std::ostream &o, haslo h)
	{
		return std::cout << h.pass << " " << h.desc;
	}
	int haslo::identyfikator = 0;
	void print(std::list<haslo> const &list)
	{
		for (haslo const &i : list)
		{
			std::cout << i << std::endl;
		}
	}
	void UruchomMenu()
	{
		std::list<haslo> hasla;
		std::ifstream file;
		std::string sciezka;
		std::string line;
		std::cout << "Witaj w managerze hasel!\n"
				  << "Wpisz nazwe lub sciezke pliku z zapisanymi haslami : ";
		std::cin >> sciezka;
		file.open(sciezka);
		if (!file.is_open())
		{
			std::cout << "Nie udalo sie otworzyc: " + sciezka;
			return;
		}
		std::string wyraz;
		std::string wyraz2;
		std::cout << "Otworzylem: " + sciezka << std::endl;
		while (file >> wyraz >> wyraz2)
		{
			hasla.push_back(haslo(wyraz, wyraz2));
		}
		print(hasla);
	}
} // namespace password_manager
