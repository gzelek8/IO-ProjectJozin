#include "pch.h"
#include "..//Jozin_Team/Header.h"
Funkcje* p = new Funkcje;

TEST(Zerowanie, Tab_complexity) {
	p->zeruj_tab_complex(p->complexity);
	for (int i = 0; i < p->liczba_funkcji(); i++)
	{
		EXPECT_EQ("0", p->complexity[i]);
	}
}
TEST(Zerowanie, Tab_wag) {
	p->zeruj_tab_wag(p->wagi);
	for (int i = 0; i < p->ilosc_dynamicznej("FILES"); i++)
	{
		EXPECT_EQ("0", p->wagi[i]);
	}
}
TEST(Naglowek, Modules)
{
	p->szukanie_naglowka("MODULES");
	string wynik = p->linia;
	EXPECT_EQ("MODULES", wynik);
}

TEST(Complexity, Czy_nie_pusta)
{
	p->czytaj_complexity();
	for (int i = 0; i < p->liczba_funkcji(); i++)
	{
		if (p->funkcja[i] != "0")
			EXPECT_TRUE(true);
		else EXPECT_TRUE(false);
	}
}
TEST(Poloczenia_plik, Functions)
{
	p->poloczenia_miedzy_plikami(p->poloczenia, "FUNCTIONS");
	for (int i = 0; i < p->ilosc_polaczen("FUNCTIONS"); i++)
	{
		EXPECT_NE("0", p->poloczenia[i]);
	}
}
TEST(Poloczenia_plik, Files)
{
	p->poloczenia_miedzy_plikami(p->poloczenia, "FILES");
	for (int i = 0; i < p->ilosc_polaczen("FILES"); i++)
	{
		EXPECT_NE("0", p->poloczenia[i]);
	}
}
TEST(Poloczenia_plik, Modules)
{
	p->poloczenia_miedzy_plikami(p->poloczenia, "MODULES");
	for (int i = 0; i < p->ilosc_polaczen("MODULES"); i++)
	{
		EXPECT_NE("0", p->poloczenia[i]);
	}
}
TEST(Plik, Rozmiar_pliku)
{
	int wynik = p->rozmiar_plik();
	EXPECT_EQ(293, wynik);
}
TEST(Plik, Czy_istnieje_plik)
{
	EXPECT_TRUE(p->czy_istnieje_plik());
}
TEST(Plik, l_funkcji)
{
	int wynik = p->liczba_funkcji();
	EXPECT_EQ(55, wynik);
}
TEST(Files, i_polonczen)
{
	int wynik = p->ilosc_polaczen("FILES");
	EXPECT_EQ(43, wynik);
}
TEST(Files, i_dynamicznej)
{
	int wynik = p->ilosc_dynamicznej("FILES");
	EXPECT_EQ(22, wynik);
}

TEST(Wagi_Files, File_FUunctions_Modulos)
{
	p->czytaj_wagi("FILES", p->wagi);
	for (int i = 0; i < p->ilosc_dynamicznej("FILES"); i++)
	{
		if (p->wagi[i] != "NULL")
			EXPECT_TRUE(true);
		else EXPECT_TRUE(false);
	}

	p->czytaj_wagi("FUNCTIONS", p->wagi);
	for (int i = 0; i < p->ilosc_dynamicznej("FUNCTIONS"); i++)
	{
		if (p->wagi[i] != "NULL")
			EXPECT_TRUE(true);
		else EXPECT_TRUE(false);
	}

	p->czytaj_wagi("MODULES", p->wagi);
	for (int i = 0; i < p->ilosc_dynamicznej("MODULES"); i++)
	{
		if (p->wagi[i] != "NULL")
			EXPECT_TRUE(true);
		else EXPECT_TRUE(false);
	}
}

TEST(FUNCTIONS, i_polonczen)
{
	int wynik = p->ilosc_polaczen("FUNCTIONS");
	EXPECT_EQ(57, wynik);
}
TEST(FUNCTIONS, i_dynamicznej)
{
	int wynik = p->ilosc_dynamicznej("FUNCTIONS");
	EXPECT_EQ(29, wynik);
}
TEST(MODULES, i_polonczen)
{
	int wynik = p->ilosc_polaczen("MODULES");
	EXPECT_EQ(53, wynik);
}
TEST(MODULES, i_dynamicznej)
{
	int wynik = p->ilosc_dynamicznej("MODULES");
	EXPECT_EQ(27, wynik);
}
