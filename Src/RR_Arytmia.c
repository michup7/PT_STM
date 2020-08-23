#include "RR_Arytmia.h"
#include <stdio.h>      // Remove if not using the standard file functions.
#include <stdlib.h>
#include <stdbool.h>
#define BUFFSIZERR 33 //wielkosc tablicy
    float a = 0.9; //sta³a a z dokumentu 485
    float b = 0.9; //sta³a b z dokumentu 485
    float c = 1.5; //sta³a c z dokumentu 485
    int fifthCounter=0; //liczba wykrytych 5 kategorii z rzêdu
    int categories[BUFFSIZERR-1]; //bufor przechowuj¹cy ostatnie kategorie
    int results[BUFFSIZERR]; //bufor przechowuj¹cy ostatnie interwa³y w milisekundach
    int indeks=0; //indeks ostatniego zapisanego interwa³u w buforze

int ReturnTotalIntervals(void) //zwraca liczbe pomiarow z ostatnich 33 interwa³ów
{
    int totalIntervals=0; //zmienna przechowuj¹ca dane o iloœci pomiarów
    for(int a=0;a<BUFFSIZERR;a++)
    {
    	totalIntervals+=results[a]/5;
    	totalIntervals++;
    }
    return totalIntervals;
}
int IsArythmiaDetected(void) //zwraca informacje czy arytmia zosta³a wykryta
{
	if(indeks!=32) //dla mniejszych ni¿ 32 nie da siê wykryc arytmii, poniewa¿ sprawdzenie robi siê na podstawie 32 bloków.
	{
		return 0;
	}
	else
	{
		int arythmicCounter=0; //zlicza kategorie 2, 3 i 4
		int arythmicFifthCounter=0; //zlicza liczbê 5 kategorii z rzêdu
		for(int a=0;a<32;a++)
		{
			if(categories[a]==5)
			{
				arythmicFifthCounter++;
			}
			else
			{
				if(categories[a]==2||categories[a]==3||categories[a]==4)
				{
					arythmicCounter++;
				}
			}
    		if(arythmicCounter>1||arythmicFifthCounter>3)
    		{
    			return 1; //je¿eli 2. 3. lub 4. kategorii by³o wiêcej ni¿ jedna oraz wykryto cztery 5. kategorie z rzêdu to zwracamy 1
    		}
		}
	}
	return 0; //w przeciwnym wypadku dajemy 0
}
int ReturnCategory(int WhichOneFromTheEnd) //zwraca numer kategorii z bufora categories z ostatnim indeksem lub którymœ od koñca (WhichOneFromTheEnd)
{
	return categories[indeks-WhichOneFromTheEnd-1];
}
void PushInterval(int interval) //zapisuje interwal podany w mainie do buforów i wywo³uje sprawdzenie RRArytmia
{
	if(indeks==BUFFSIZERR-1) //Je¿eli bufory s¹ pe³ne
	{
		for(int a=0;a<(BUFFSIZERR-2);a++) //przesuniêcie poprzednich rezultatów i kategorii o 1 w ty³.
		{
			results[a]=results[a+1];
			categories[a]=categories[a+1];
		}
		results[BUFFSIZERR-2]=results[indeks]; //przesuniêcie ostatniego rezultatu o 1 w ty³
		results[indeks]=interval; //przypisanie nowego interwa³u do bufora na sam koniec.
		RRArytmia(indeks,0); //wywo³anie RRArytmia.
	}
	else
	{
		results[indeks]=interval; //przypisuje ostatniemu indeksowi interwa³
		if(indeks>=2) //je¿eli
		{
			RRArytmia(indeks,0);
		}
		else
		{
			if(indeks==0)
			{
				categories[0]=1;
			}
		}
		indeks++;
	}

}

void RRArytmia(int lastIndex,int state)
{
	categories[(lastIndex - 1)] = 1;
	if ((fifthCounter!=0 || (results[lastIndex - 1] < 600 && results[lastIndex - 1] < results[lastIndex]))&&state==0)
	{
		if (fifthCounter == 0)
	    {
			fifthCounter++;
	        categories[lastIndex - 1] = 5;
	        return;
	    }
	    if ((results[lastIndex - 2] < 800 && results[lastIndex - 1] < 800 &&results[lastIndex] < 800) || (results[lastIndex - 2] + results[lastIndex - 1] + results[lastIndex]) < 1800)
	    {
	    	fifthCounter++;
	    	categories[lastIndex - 1] = 5;
	    	return;
	    }
	    if(fifthCounter<4)
	    {
	    	for (int licznik = 1; licznik <= fifthCounter; licznik++)
	      	{
	    		RRArytmia(lastIndex-licznik,1);
	      	}
	    }
	    fifthCounter = 0;
	}
	if (results[lastIndex - 1] < a * results[lastIndex - 2] && results[lastIndex - 2] < b * results[lastIndex])
	{
		if (results[lastIndex] + results[lastIndex - 1] < 2 * results[lastIndex - 2])
		{
			categories[lastIndex - 1] = 2;
		}
		else
		{
			categories[lastIndex - 1] = 3;
		}
	}
	if (results[lastIndex - 1] > c * results[lastIndex - 2])
	{
		categories[lastIndex - 1] = 4;
	}
	return;
}







