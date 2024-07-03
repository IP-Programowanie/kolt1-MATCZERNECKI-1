#include "Wybor.h"
#include <cstring>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <cassert>

using namespace std;

/*
* Uwaga: Zadania kod rozwiazania zaania umieszczaæ pomiêdzy #ifdef a #endif.
*/

#ifdef Kol_2

enum class Dopuszczenie {dopuszczony, niedopuszczony};

class Wlasciciel{};

class Samochod
{
protected:
	char rejestracja[9];
	int licznik;
	Dopuszczenie dopuszczenie;
	Wlasciciel* wlasciciel;
	double war_pocz;
	static Samochod* wzor;
public:
	void setlicznik(int l) 
	{
		if (l < 0)
		{
			throw invalid_argument("Stan licznika nie moze byc ujemny");
		}
		else {
			licznik = l;
		}
	}
	int getlicznik() { return licznik; }
	const char* getrejestracja() { return rejestracja; }
	Dopuszczenie getdopuszczenie() { return dopuszczenie; }
	Wlasciciel* getwlasciciel() { return wlasciciel; }
	double getwarpocz() { return war_pocz; }
	Samochod(const char* rej, int l, Dopuszczenie d, Wlasciciel* w, double war)
		: dopuszczenie(d), wlasciciel(w), war_pocz(war)
	{
		strcpy(rejestracja, rej);
		setlicznik(l);
	}
	Samochod()
	{
		if (wzor == nullptr)
		{
			throw invalid_argument("brak instancji wzorcowej");
		}
		else {
			strcpy(rejestracja, wzor->rejestracja);
			licznik = wzor->licznik;
			dopuszczenie = wzor->dopuszczenie;
			wlasciciel = wzor->wlasciciel;
			war_pocz = wzor->war_pocz;
		}
	}
	bool czyDopuszczony(Dopuszczenie d)
	{
		if (d == Dopuszczenie::dopuszczony)
		{
			return true;
		}
		else {
			return false;
		}
	}
	virtual double zasieg()
	{
		if (czyDopuszczony(this->dopuszczenie))
		{
			return 800.0;
		}
		else {
			throw ("samochod niedopuszczony");
		}
	}
	operator double()
	{
		double wsp_sparw;
		if (this->dopuszczenie == Dopuszczenie::dopuszczony)
		{
			wsp_sparw = 1.0;
		}
		else {
			wsp_sparw = 0.2;
		}
		double wartosc = (war_pocz - (0.2 * licznik)) * wsp_sparw;
		if (wartosc < 400.0)
		{
			wartosc = 400.0;
		}
		return wartosc;
	}
	bool operator !=(Samochod& s)
	{
		return (abs(licznik - s.licznik) > 20 || dopuszczenie != s.dopuszczenie);
	}
};

class SamochodElektryczny : public Samochod
{
private:
	int stanbaterii;
public:
	void setstanbaterii(int b)
	{
		if (b >= 0 && b <= 100)
		{
			stanbaterii = b;
		}
		else {
			throw invalid_argument("bledna wartosc stanu baterii");
		}
	}
	SamochodElektryczny(Samochod* s, int stan)
	{
		strcpy(this->rejestracja, s->getrejestracja());
		setlicznik(s->getlicznik());
		dopuszczenie = s->getdopuszczenie();
		wlasciciel = s->getwlasciciel();
		war_pocz = s->getwarpocz();
		setstanbaterii(stan);
	}
	double zasieg() override
	{
		if (czyDopuszczony(this->dopuszczenie))
		{
			return (2.5*stanbaterii);
		}
		else {
			throw ("Samochod niedopuszczony");
		}
	}
	operator double()
	{
		double wartosc = Samochod::operator double();
		wartosc *= 0.7;
		return wartosc;
	}
};

Samochod* Samochod::wzor = nullptr;

int main()
{

}

#endif
