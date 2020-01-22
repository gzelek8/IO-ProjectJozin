#pragma once
#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <new>


using namespace std;

class Dane
{
public:
	int i = 0;		//zmienne pomocnicze
	int j = 0;
	int igraf = 0;

	int rozmiar_pliku=0; //ilosc linijek w naszym pliku, wyrazama przez funkcjce rozmiar_plik
	string znak = "->";
	const string quote = "\"";
	string linia;
	string linia2;
	fstream dane;


	//poczatek polecnenia do grafu, parametry: od lewej do prawej, gradient dwukolorowy w tle
	string graph = "digraph G {graph [rankdir = \"LR\" bgcolor = \"antiquewhite:aquamarine\" style = \"filled\" gradientangle = 270]; ";

	string dotPath = "C:\\Users\\micha\\Downloads\\graphviz-2.38\\release\\bin\\dot.exe"; //link do biblioteki
	string notatnik = "graf_jozin9.txt"; // nazwa notatnika
	string tempFile = "temp.dot"; //nazwa pliku pomocniczego
	string outFile = "out.png"; //nazwa pliku png z grafem
};

class Funkcje : public Dane
{
public:
	// stringi potrzebne do rysowania grafu w petli
	string* wagi = new string[rozmiar_plik()]();		// tablica do wag
	string* poloczenia = new string[rozmiar_plik()];	//tablica do poloczen
	string* grafs = new string[rozmiar_plik()];			//tablica pomocnicza
	string* funkcja = new string[rozmiar_plik()];		//tablica do wszystkich funkcji (wezlow)
	string* complexity = new string[rozmiar_plik()];	//tablica complexity


	void draw() {
		dane.open(notatnik, ios::in);  //txt od Grzesia
		string gitcommit;
		if (dane.good() == false)
		{
			cout << "Nie mozna otworzyc pliku";		//hash commit git
			exit(0);
		}
		else
		{
			while (getline(dane, linia))
			{
				if (linia == "HASH_COMMIT") //pobieranie hash commit z notatnika
				{
					break;
				}
			}
			getline(dane, linia);
			gitcommit = linia;
		}
		dane.close();

		graph += "overlap=false \n"		//konczymy tworzenie grafu
			"label = " + gitcommit + " \n"
			"fontsize = 12; \n"
			"}";
		//1 cout << graph << endl;
		ofstream out;
		out.open(tempFile.c_str(), std::ios::out);
		out << graph << std::endl;
		out.close();

		system((dotPath + " " + tempFile + " -Tpng -o " + outFile).c_str());	//tworzenie grafu
	}
	bool czy_istnieje_plik()
	{
		dane.open(notatnik, ios::in);  //txt od Grzesia

		if (dane.good() == false)
		{
			cout << "Nie mozna otworzyc pliku";
			exit(0);
			return false;
		}

		else cout << "mozna otworzyc pliku";
		dane.close();
		return true;
	}

	int rozmiar_plik() //ilosc liniejk w pliku txt
	{
		rozmiar_pliku = 0;
		dane.open(notatnik, ios::in);
		ifstream file("graf_jozin9.txt");	

		
			while (!file.eof()) {
				getline(file, linia2);
				rozmiar_pliku++;
			}
			dane.close();
		

		return rozmiar_pliku;
	}


	void szukanie_naglowka(string nazwa)
	{
		dane.open(notatnik, ios::in);
		while (getline(dane, linia))
		{
			if (linia == nazwa) {
				break;
			}
		}
	}


	void poloczenia_miedzy_plikami(string* poloczenia, string nazwa)
	{
		szukanie_naglowka(nazwa);
		while (getline(dane, linia))          //petla zczytujaca poloczenia miedzy plikami
		{
			poloczenia[i] = linia;
			i++;
			if (linia == "dane") break;
		}
		dane.close();
		
	}


	int ilosc_polaczen(string nazwa)  //liczba polonczen plikow miedzy plikami
	{
		int l_polaczen = 0;
		dane.open(notatnik, ios::in);
		while (getline(dane, linia))
		{
			if (linia == nazwa) {
				break;
			}
		}
		while (getline(dane, linia))          //petla zczytujaca poloczenia miedzy plikami
		{
			l_polaczen++;

			if (linia == "dane") break;
		}
		dane.close();
		return l_polaczen;
	}


	int ilosc_dynamicznej(string nazwa) //licznik wag jest jednoznaczny z iloscia polaczen
	{
		int rozmiar_dynamicznej = 0; ///u nas 22 w plikach
		i = 0;

		dane.open(notatnik, ios::in);

		while (getline(dane, linia))
		{
			if (linia == nazwa) {
				break;
			}
		}
		while (getline(dane, linia))          //petla zczytujaca poloczenia miedzy plikami
		{
			if (linia == "dane") break;
		}

		while (getline(dane, linia))         //petla zczytujaca wagi
		{

			rozmiar_dynamicznej++;			//licznik wag jest jednoznaczny z iloscia polaczen
			if (linia == "dane")
			{
				break;
			}
		}
		dane.close();
		return rozmiar_dynamicznej;
	}

	//dla sprawdzania co wypisze nie potrzebana w programie
	
	void czytaj_wagi(string nazwa, string* wagi) //petla zczytujaca wagi
	{

		i = 0;

		dane.open(notatnik, ios::in);
		cout << "WAGI" << endl;
		while (getline(dane, linia))
		{
			if (linia == nazwa) {
				break;
			}
		}
		while (getline(dane, linia))          //przechodizmy w txt do wlasnicwego miejsca
		{
			if (linia == "dane") break;
		}

		while (getline(dane, linia))         //petla zczytujaca wagi
		{
			wagi[i] = linia;
		
			if (linia == "dane")
			{
				wagi[i] = "0";		//waga od i zeby nie byla rowna "dane"
				break;
			}
			i++;
		}
		dane.close();
	
	}

	void czytaj_complexity()
	{
		dane.open(notatnik, ios::in);
		while (getline(dane, linia))
		{
			if (linia == "CYCLOMATIC_COMPLEXITY")
			{
				break;
			}
		}

		i = 0;
		char delimeter(' ');
		cout << "COMPLEXY" << endl;
		while (getline(dane, linia))          //petla zczytujaca funkcje i complexity
		{
			if (linia == "dane") break;
			funkcja[i] = linia;
			funkcja[i].erase(funkcja[i].find(' '));
			complexity[i] = linia;
			complexity[i].erase(complexity[i].begin(), complexity[i].end() - 4); //ostatnie 4 znaki do tablicy complexity
			i++;
		}
		dane.close();
	}

	int liczba_funkcji()
	{
		int l_funkcji = 0;
		dane.open(notatnik, ios::in);
		while (getline(dane, linia))
		{
			if (linia == "CYCLOMATIC_COMPLEXITY")
			{
				break;
			}
		}
		while (getline(dane, linia))          //petla zczytujaca liczbe funckji
		{
			l_funkcji++;
		}
		dane.close();
		return l_funkcji;
	}


	void rysuj_graf(string color, string* wagi, string* poloczenia, string* all, string* grafs, int wynik_dynamicznej, int wynik_polonczen, string nazwa)
	{
		i = 0;

		for (j = 0; j < wynik_dynamicznej - 1; j++)	//all to sa te dlugie stringi, które wsadzamy do grafu
		{											//tworzymy ich tyle ile jest polaczen


			if (wagi[j] == "0")								//sprawdzamy czy musimy tworzyc polaczenie czy wolny wezel
			{
				all[j] = quote + poloczenia[i] + quote + ";\n" + quote + poloczenia[i + 1] + quote;
				grafs[j] = all[j] + ";\n";
				i = i + 2;
			}
			else {

				all[j] = quote + poloczenia[i] + quote + znak + quote + poloczenia[i + 1] + quote;
				grafs[j] = all[j] + "[label = " + wagi[j] + "];\n";
				i = i + 2;
			}
		
		}

		int k = 0;
		int l_funkcji = liczba_funkcji()-1;
		czytaj_complexity();
		if (nazwa == "FUNCTIONS")
		{
			for (k = 0; k < l_funkcji; k++)
			{
				if (complexity[k] != " [0]"){
					graph += "" + quote + funkcja[k] + quote + " [style =filled, color=" + color + " xlabel=" + quote + complexity[k] + quote + "]; \n";
				}
				else {
					graph += "" + quote + poloczenia[k] + quote + " [style =filled, color=" + color + "]; \n";
				}
			}
		}
		else {
			for (igraf = 0; igraf < wynik_polonczen - 1; igraf++)	// tworzenie polecenia do stworzenia grafu w petli
			{
				//tworzenie samych wezlow o kolorze
				graph += "" + quote + poloczenia[igraf] + quote + " [style =filled, color=" + color + "]; \n";
			}
		}
		for (igraf = 0; igraf < wynik_dynamicznej; igraf++)
		{
			//dodajemy do polecenia
			graph += grafs[igraf];
		}

		delete[] poloczenia;
		delete[] wagi;
		delete[] grafs;
		delete[] all;
	}
	void zeruj_tab_wag(string* wagi)
	{
		for (int i = 0; i < rozmiar_plik(); i++)
			wagi[i] = "0";

	}
	void zeruj_tab_complex(string* complexity)
	{
		for (int i = 0; i < rozmiar_plik(); i++)
			complexity[i] = "0";
	}


	void Functions()
	{
		
		int wynik_dynamicznej = ilosc_dynamicznej("FUNCTIONS");
		int wynik_polonczen = ilosc_polaczen("FUNCTIONS");
		
		string* all = new string[wynik_dynamicznej];
		
		szukanie_naglowka("FUNCTIONS");
		zeruj_tab_wag(wagi);
		poloczenia_miedzy_plikami(poloczenia, "FUNCTIONS");
		czytaj_wagi("FUNCTIONS", wagi);
		rysuj_graf("lightskyblue1", wagi, poloczenia, all, grafs, wynik_dynamicznej, wynik_polonczen, "FUNCTIONS");

		draw();
	}

	void Files()
	{
	
		
		int wynik_dynamicznej = ilosc_dynamicznej("FILES");
		int wynik_polonczen = ilosc_polaczen("FILES");
		
		string* all = new string[wynik_dynamicznej];
		

		zeruj_tab_wag(wagi);
		poloczenia_miedzy_plikami(poloczenia, "FILES");
		czytaj_wagi("FILES", wagi);
		rysuj_graf("gold1", wagi, poloczenia, all, grafs, wynik_dynamicznej, wynik_polonczen, "FILES");
		draw();
	}
	
	
	void Modules()
	{
		
		int wynik_dynamicznej = ilosc_dynamicznej("MODULES");
		int wynik_polonczen = ilosc_polaczen("MODULES");
		string* all = new string[wynik_dynamicznej];
		
		zeruj_tab_wag(wagi);
		poloczenia_miedzy_plikami(poloczenia, "MODULES");
		czytaj_wagi("MODULES", wagi);
		rysuj_graf("burlywood2", wagi, poloczenia, all, grafs, wynik_dynamicznej, wynik_polonczen, "MODULES");
		draw();
	}

	void PlikiFunkcje()
	{
		
		int wynik_dynamicznej = ilosc_dynamicznej("FILES");
		int wynik_polonczen = ilosc_polaczen("FILES");
		
		string* all = new string[wynik_dynamicznej];

		zeruj_tab_wag(wagi);
		poloczenia_miedzy_plikami(poloczenia, "FILES");
		czytaj_wagi("FILES", wagi);
		rysuj_graf("gold1", wagi, poloczenia, all, grafs, wynik_dynamicznej, wynik_polonczen,"FILES");


		
		string* wagi = new string[rozmiar_plik()]();
		string* poloczenia = new string[rozmiar_plik()];
		string* grafs = new string[rozmiar_plik()];
		
	
		int wynik_dynamicznej1 = ilosc_dynamicznej("FUNCTIONS");
		int wynik_polonczen1 = ilosc_polaczen("FUNCTIONS");

		string* all1 = new string[wynik_dynamicznej1];

		zeruj_tab_wag(wagi);
		poloczenia_miedzy_plikami(poloczenia, "FUNCTIONS");
		czytaj_wagi("FUNCTIONS", wagi);
		rysuj_graf("lightskyblue1", wagi, poloczenia, all1, grafs, wynik_dynamicznej1, wynik_polonczen1, "FUNCTIONS");

		draw();
	}

	void PlikiModuly()
	{
		
		int wynik_dynamicznej = ilosc_dynamicznej("FILES");
		int wynik_polonczen = ilosc_polaczen("FILES");
		
		string* all = new string[wynik_dynamicznej];

		zeruj_tab_wag(wagi);
		poloczenia_miedzy_plikami(poloczenia, "FILES");
		czytaj_wagi("FILES", wagi);
		rysuj_graf("gold1", wagi, poloczenia, all, grafs, wynik_dynamicznej, wynik_polonczen, "FILES");


		string* wagi = new string[rozmiar_plik()]();
		string* poloczenia = new string[rozmiar_plik()];
		string* grafs = new string[rozmiar_plik()];

		
		int wynik_dynamicznej1 = ilosc_dynamicznej("MODULES");
		int wynik_polonczen1 = ilosc_polaczen("MODULES");

		string* all1 = new string[wynik_dynamicznej1];

		zeruj_tab_wag(wagi);
		poloczenia_miedzy_plikami(poloczenia, "MODULES");
		czytaj_wagi("MODULES", wagi);
		rysuj_graf("burlywood2", wagi, poloczenia, all1, grafs, wynik_dynamicznej1, wynik_polonczen1, "MODULES");

		draw();
	}

	void FunkcjeModuly()
	{
	
		int wynik_dynamicznej = ilosc_dynamicznej("FUNCTIONS");
		int wynik_polonczen = ilosc_polaczen("FUNCTIONS");
		string* all = new string[ilosc_dynamicznej("FUNCTIONS")];
		
		szukanie_naglowka("FUNCTIONS");
		zeruj_tab_wag(wagi);
		poloczenia_miedzy_plikami(poloczenia, "FUNCTIONS");
		czytaj_wagi("FUNCTIONS", wagi);
		rysuj_graf("lightskyblue1", wagi, poloczenia, all, grafs, wynik_dynamicznej, wynik_polonczen, "FUNCTIONS");

		string* wagi = new string[rozmiar_plik()]();
		string* poloczenia = new string[rozmiar_plik()];
		string* grafs = new string[rozmiar_plik()];


		int wynik_dynamicznej1 = ilosc_dynamicznej("MODULES");
		int wynik_polonczen1 = ilosc_polaczen("MODULES");

		string* all1 = new string[wynik_dynamicznej1];

		zeruj_tab_wag(wagi);
		poloczenia_miedzy_plikami(poloczenia, "MODULES");
		czytaj_wagi("MODULES", wagi);
		rysuj_graf("burlywood2", wagi, poloczenia, all1, grafs, wynik_dynamicznej1, wynik_polonczen1, "MODULES");

		draw();
	}

	void FunkcjeModulyPliki()
	{
	
		int wynik_dynamicznej = ilosc_dynamicznej("FUNCTIONS");
		int wynik_polonczen = ilosc_polaczen("FUNCTIONS");
		string* all = new string[ilosc_dynamicznej("FUNCTIONS")];
		
		szukanie_naglowka("FUNCTIONS");
		zeruj_tab_wag(wagi);
		poloczenia_miedzy_plikami(poloczenia, "FUNCTIONS");
		czytaj_wagi("FUNCTIONS", wagi);
		rysuj_graf("lightskyblue1", wagi, poloczenia, all, grafs, wynik_dynamicznej, wynik_polonczen, "FUNCTIONS");

		
		string* wagi = new string[rozmiar_plik()]();
		string* poloczenia = new string[rozmiar_plik()];
		string* grafs = new string[rozmiar_plik()];
		
		
		int wynik_dynamicznej1 = ilosc_dynamicznej("MODULES");
		int wynik_polonczen1 = ilosc_polaczen("MODULES");

		string* all1 = new string[wynik_dynamicznej1];

		zeruj_tab_wag(wagi);
		poloczenia_miedzy_plikami(poloczenia, "MODULES");
		czytaj_wagi("MODULES", wagi);
		rysuj_graf("burlywood2", wagi, poloczenia, all1, grafs, wynik_dynamicznej1, wynik_polonczen1, "MODULES");



		string* wagi1 = new string[rozmiar_plik()]();
		string* poloczenia1 = new string[rozmiar_plik()];
		string* grafs1 = new string[rozmiar_plik()];

	
		int wynik_dynamicznej2 = ilosc_dynamicznej("FILES");
		int wynik_polonczen2 = ilosc_polaczen("FILES");
		string* all2 = new string[wynik_dynamicznej2];

		zeruj_tab_wag(wagi1);
		poloczenia_miedzy_plikami(poloczenia1, "FILES");
		czytaj_wagi("FILES", wagi1);
		rysuj_graf("gold1", wagi1, poloczenia1, all2, grafs1, wynik_dynamicznej2, wynik_polonczen2, "FILES");
		draw();
	}

};

