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

	int rozmiar_pliku = 0;
	string znak = "->";
	const string quote = "\"";
	string linia;
	fstream dane;
	int rozmiar_dynamicznej = 0;

	//poczatek polecnenia do grafu, parametry: od lewej do prawej, gradient dwukolorowy w tle
	string graph = "digraph G {graph [rankdir = \"LR\" bgcolor = \"antiquewhite:aquamarine\" style = \"filled\" gradientangle = 270]; ";	
		
	string dotPath = "C:\\Users\\Tycjan\\Documents\\release\\bin\\dot.exe"; //link do biblioteki
	string notatnik = "graf_jozin.txt";		//nazwa notatnika
	string tempFile = "temp.dot";			//nazwa pliku pomocniczego
	string outFile = "out.png";				//nazwa pliku png z grafem
};

class Funkcje : public Dane
{
public:
	void draw() {
		dane.open(notatnik, ios::in); 
		string gitcommit;
		if (dane.good() == false)
		{
			cout << "Nie mozna otworzyc pliku";	
			exit(0);
		}
		else
		{
			while (getline(dane, linia))		//pobieranie hash commit z notatnika
			{
				if (linia == "HASH_COMMIT") {
					break;
				}
			}
			getline(dane, linia);
			gitcommit = linia;
		}
		dane.close();

		graph += "overlap=false \n"		//konczymy tworzenie grafu
			"label = "+ gitcommit +" \n"
			"fontsize = 12; \n"
			"}";
		cout << "TWORZENIE GRAFU W  TOKU" << endl;
		ofstream out;
		out.open(tempFile.c_str(), std::ios::out);
		out << graph << std::endl;
		out.close();

		system((dotPath + " " + tempFile + " -Tpng -o " + outFile).c_str());	//tworzenie grafu
	}
	void polaczenia(string nazwa, string color) {


		rozmiar_dynamicznej = 0;	//zerujemy rozmiar dla wielukrotnego wywolania funkcji

		dane.open(notatnik, ios::in);  //txt od Grzesia

		if (dane.good() == false)
		{
			cout << "Nie mozna otworzyc pliku";
			exit(0);
		}
		else
		{
			ifstream file(notatnik);		//sprawdzanie rozmiaru pliku do stworzenia tablic dynamicznych
			while (getline(file, linia))		//przechodzimy pierwszy po pliku, liczymy rozmiar zeby stworzyc dynamiczne tablice
				rozmiar_pliku++;

			// stringi potrzebne do rysowania grafu w petli
			string* grafs = new string[rozmiar_pliku];		//tablica pomocnicza
			string* poloczenia = new string[rozmiar_pliku];//tablica do poloczen
			string* wagi = new string[rozmiar_pliku]();//tablica do wag

			string* funkcja = new string[rozmiar_pliku];//tablica do wszystkich funkcji (wezlow)
			string* complexity = new string[rozmiar_pliku]; //tablica complexity

			for (int i = 0; i < rozmiar_pliku; i++)
				wagi[i] = "0";			//zerujemy tablice wag

			for (int i = 0; i < rozmiar_pliku; i++)	//zerujemy complexity
				complexity[i] = "0";

			int l_funkcji = 0;
			int l_polaczen = 0;
			i = 0;

			while (getline(dane, linia))	//przeszukujemy az do nazwy (files,functions itp)
			{
				if (linia == nazwa) {
					break;
				}
			}

			i = 0;
			while (getline(dane, linia))          //petla zczytujaca poloczenia miedzy plikami
			{
				poloczenia[i] = linia;
				l_polaczen++;
				i++;
				if (linia == "dane") break;
			}

			i = 0;
			while (getline(dane, linia))         //petla zczytujaca wagi
			{
				wagi[i] = linia;
				rozmiar_dynamicznej++;			//licznik wag jest jednoznaczny z iloscia polaczen
				if (linia == "dane")
				{
					wagi[i] = "0";		//waga od i zeby nie byla rowna "dane"
					break;
				}
				i++;
			}

			while (getline(dane, linia))
			{
				if (linia == "CYCLOMATIC_COMPLEXITY") 
				{
					break;
				}
			}

			i = 0;
			while (getline(dane, linia))          //petla zczytujaca funkcje i complexity
			{
				if (linia == "dane") break;
				funkcja[i] = linia;
				funkcja[i].erase(funkcja[i].find(' '));		//nazwa funkcji z jej waga do tablicy funkcja

				complexity[i] = linia;
				complexity[i].erase(complexity[i].begin(), complexity[i].end() - 4); //ostatnie 4 znaki do tablicy complexity
				l_funkcji++;
				i++;
				
			}
			

			string* all = new string[rozmiar_dynamicznej];

			i = 0;
			for (j = 0; j < rozmiar_dynamicznej - 1; j++)	//all to sa te dlugie stringi, które wsadzamy do grafu
			{											//tworzymy ich tyle ile jest polaczen


				if (wagi[j] == "0")								//sprawdzamy czy musimy tworzyc polaczenie czy wolny wezel
				{
					all[j] = quote + poloczenia[i] + quote +  ";\n" +quote + poloczenia[i + 1] + quote;
					grafs[j] = all[j] + ";\n";
					i = i + 2;
				}
				else {

					all[j] = quote + poloczenia[i] + quote +  znak + quote + poloczenia[i + 1] + quote;
					grafs[j] = all[j] + "[label = " + wagi[j] + "];\n";
					i = i + 2;
				}
			}


			int k=0;
			if (nazwa == "FUNCTIONS")		//complexity tylko dla funkcji
			{
				for (k = 0; k < l_funkcji; k++)
				{ 
					if (complexity[k] != " [0]") {		//sprawdzamy czy complexity jest rowne 0, jesli nie to wypisujemy je
						graph += "" + quote + funkcja[k] + quote + " [style =filled, color=" + color + " xlabel=" + quote + complexity[k] + quote + "]; \n";
					}
					else {
						graph += "" + quote + poloczenia[k] + quote + " [style =filled, color=" + color + "]; \n";
					}

				}
			}
			else {
				for (igraf = 0; igraf < l_polaczen - 1; igraf++)	// tworzenie polecenia do stworzenia grafu w petli
				{
					//tworzenie samych wezlow o kolorze
					graph += "" + quote + poloczenia[igraf] + quote + " [style =filled, color=" + color + "]; \n";
				}
			}
			for (igraf = 0; igraf < rozmiar_dynamicznej; igraf++)	
			{
				//dodajemy do polecenia
				graph += grafs[igraf];
			}


			delete[] poloczenia;
			delete[] wagi;
			delete[] grafs;
			delete[] complexity;
			delete[] funkcja;
		}

		dane.close();
	}
	

	void Functions()
	{
		polaczenia("FUNCTIONS", "lightskyblue1");

		draw();
	}
	void Files()
	{
		polaczenia("FILES", "gold1");
		draw();
	}
	void Modules()
	{
		polaczenia("MODULES","burlywood2");
		draw();
	}
	void PlikiFunkcje()
	{
		polaczenia("FILES", "gold1");
		polaczenia("FUNCTIONS", "lightskyblue1");
		draw();

	}
	void PlikiModuly()
	{
		polaczenia("FILES", "gold1");
		polaczenia("MODULES", "burlywood2");
		draw();
	}
	void FunkcjeModuly()
	{
		polaczenia("FUNCTIONS", "lightskyblue1");
		polaczenia("MODULES", "burlywood2");
		draw();
	}
	void FunkcjeModulyPliki()
	{
		polaczenia("FUNCTIONS", "lightskyblue1");
		polaczenia("FILES", "gold1");
		polaczenia("MODULES", "burlywood2");


		draw();
	}
};
