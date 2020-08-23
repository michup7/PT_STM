#include "RR_Arytmia.h"
#include <stdio.h>      // Remove if not using the standard file functions.
#include <stdlib.h>
#include <stdbool.h>
#define BUFFSIZERR 33 //wielkosc tablicy
    float a = 0.9; //sta�a a z dokumentu 485
    float b = 0.9; //sta�a b z dokumentu 485
    float c = 1.5; //sta�a c z dokumentu 485
    int fifthCounter=0; //liczba wykrytych 5 kategorii z rz�du
    int categories[BUFFSIZERR-1]; //bufor przechowuj�cy ostatnie kategorie
    int results[BUFFSIZERR]; //bufor przechowuj�cy ostatnie interwa�y w milisekundach
    int indeks=0; //indeks ostatniego zapisanego interwa�u w buforze

int ReturnTotalIntervals(void) //zwraca liczbe pomiarow z ostatnich 33 interwa��w
{
    int totalIntervals=0; //zmienna przechowuj�ca dane o ilo�ci pomiar�w
    for(int a=0;a<BUFFSIZERR;a++)
    {
    	totalIntervals+=results[a]/5;
    	totalIntervals++;
    }
    return totalIntervals;
}
int IsArythmiaDetected(void) //zwraca informacje czy arytmia zosta�a wykryta
{
	if(indeks!=32) //dla mniejszych ni� 32 nie da si� wykryc arytmii, poniewa� sprawdzenie robi si� na podstawie 32 blok�w.
	{
		return 0;
	}
	else
	{
		int arythmicCounter=0; //zlicza kategorie 2, 3 i 4
		int arythmicFifthCounter=0; //zlicza liczb� 5 kategorii z rz�du
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
    			return 1; //je�eli 2. 3. lub 4. kategorii by�o wi�cej ni� jedna oraz wykryto cztery 5. kategorie z rz�du to zwracamy 1
    		}
		}
	}
	return 0; //w przeciwnym wypadku dajemy 0
}
int ReturnCategory(int WhichOneFromTheEnd) //zwraca numer kategorii z bufora categories z ostatnim indeksem lub kt�rym� od ko�ca (WhichOneFromTheEnd)
{
	return categories[indeks-WhichOneFromTheEnd-1];
}
void PushInterval(int interval) //zapisuje interwal podany w mainie do bufor�w i wywo�uje sprawdzenie RRArytmia
{
	if(indeks==BUFFSIZERR-1) //Je�eli bufory s� pe�ne
	{
		for(int a=0;a<(BUFFSIZERR-2);a++) //przesuni�cie poprzednich rezultat�w i kategorii o 1 w ty�.
		{
			results[a]=results[a+1];
			categories[a]=categories[a+1];
		}
		results[BUFFSIZERR-2]=results[indeks]; //przesuni�cie ostatniego rezultatu o 1 w ty�
		results[indeks]=interval; //przypisanie nowego interwa�u do bufora na sam koniec.
		RRArytmia(indeks,0); //wywo�anie RRArytmia.
	}
	else
	{
		results[indeks]=interval; //przypisuje ostatniemu indeksowi interwa�
		if(indeks>=2) //je�eli
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







