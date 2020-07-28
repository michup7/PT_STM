#include "RR_Arytmia.h"
#include <stdio.h>      // Remove if not using the standard file functions.
#include <stdlib.h>
#include <stdbool.h>
    float a = 0.9;
    float b = 0.9;
    float c = 1.5;
    int Category;
    int State;


int RR_Arytmia(int Sample1, int Sample2, int Sample3, int State)//czasy w ms, flaga pulsu (n+1<4)---
{	if (State==0){
    Category=1;//2

    if ((Sample2 < 600)&&(Sample2>Sample3)){ //3
	Category=5;

	if (((Sample1<800)&&(Sample2<800)&&(Sample3<800))||((Sample1+Sample2+Sample3<1800))){//3a
    	Category=5;
    }

}else{
	State=1;
}

}
if (State==1){//jesli spelniony warunek z 3b
	if ((Sample2<a*Sample1)&&(Sample1<b*Sample3)){//4
		if ((Sample2+Sample3<2*Sample1)){//4a
			Category=2;
		}else{//4b
			Category=3;
		}
	}
	if (Sample2>c*Sample1){
		Category=4;
	}
}
return Category;
}







