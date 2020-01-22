#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <new>


using namespace std;

string* grafs = new string[20];	// stringi potrzebne do rysowania grafu w petli

int main()
{
	string *linie = new string[10]; //tablica do linii
	int licznik_lin = 0;
	string *poloczenia = new string[10];//tablica do poloczen
	int licznik_pol = 0;
	string *wagi = new string[10];//tablica do wag
	int licznik_wag = 0;

	string znak = "->";
	string linia;

	fstream dane;
	dane.open("notatnik.txt", ios::in);  //txt od Grzesia

	if (dane.good() == false)
	{
		cout << "Nie mozna otworzyc pliku";
		exit(0);
	}
	else
	{
		int i = 0;
		while (getline(dane, linia))          //petla zczutyjaca ilosc linie
		{
			cout << linia << endl;
			linie[i] = linia;
			licznik_lin++;
			i++;
			if (linia == "dane") break;
		}

		i = 0;
		while (getline(dane, linia))          //petla zczytujaca poloczenia miedzy plikami
		{
			cout << linia << endl;
			poloczenia[i] = linia;
			licznik_pol++;
			i++;
			if (linia == "dane") break;
		}

		i = 0;
		while (getline(dane, linia))         //petla zczytujaca wagi
		{
			cout << linia << endl;
			wagi[i] = linia;
			licznik_wag++;
			i++;
			if (linia == "dane") break;
		}

		int rozmiar_dynamicznej = licznik_wag;	//licznik wag jest jednoznaczny z iloscia polaczen
		string *all = new string[rozmiar_dynamicznej];

		i = 0;
		int j;
		for (j = 0; j < rozmiar_dynamicznej; j++)	//all to sa te dlugie stringi, które wsadzamy do grafu
		{											//tworzymy ich tyle ile jest polaczen
			all[j] = poloczenia[i] +"_"+ linie[i] + znak + poloczenia[i + 1]+"_" + linie[i + 1];
			i = i + 2;

		//	cout << "polaczenia: " << all[j] << endl;;
		}

		int igraf;
		for (igraf = 0; igraf < rozmiar_dynamicznej-1; igraf++)	//funkcji przekazuje te dlugie stringi zawierajace polaczenia i ilosci linii, wagi i jeszcze licznik
		{
			grafs[igraf] = all[igraf] + "[label = " + wagi[igraf] + "];\n";
		}
		string graph= "digraph G {";
		for (igraf = 0; igraf < rozmiar_dynamicznej; igraf++)	// tworzenie polecenia do stworzenia grafu w petli
		{
			graph += grafs[igraf];
		}
		graph+= "}";

		string dotPath = "C:\\Users\\rafal\\Desktop\\Studia\\IOPROJEKT\\IO-projekt-final\\Projekt_IO_oddawanie\\release\\bin\\dot.exe"; //link do biblioteki
		string tempFile = "temp.dot";
		string outFile = "out.png";

		ofstream out;
		out.open(tempFile.c_str(), std::ios::out);
		out << graph << std::endl;
		out.close();

		system((dotPath + " " + tempFile + " -Tpng -o " + outFile).c_str());	//tworzenie grafu
		dane.close();
	}

	delete[] linie;
	delete[] poloczenia;
	delete[] wagi;



	system("PAUSE");
	return 0;
}
