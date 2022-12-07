#include "discount.h"
#include "schedule.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//import businessdays
//°µQuote rate


struct DZCurve* DZ_Table(struct DZCurve* DZCdata , int DiscountDate[], int TermCount) {


	struct DZCurve* DZT;
	printf("T = %d", TermCount);
	DZT = malloc(TermCount * sizeof * DZT);
	

	for (int i = 0; i < TermCount; i++) {

		DZT[i].Days = DiscountDate[i];

		for (int j = 1; j < LINEC; j++) {

			if (DZCdata[j].Days >= DZT[i].Days && DZCdata[j - 1].Days < DZT[i].Days) {

				DZT[i].Rate = (DZCdata[j].Rate - DZCdata[j - 1].Rate) * (DZT[i].Days - DZCdata[j - 1].Days) / (DZCdata[j].Days - DZCdata[j - 1].Days) + DZCdata[j - 1].Rate;
				printf("%f, ", DZT[i].Rate);
				DZT[i].Discount = exp(-DZT[i].Days * DZT[i].Rate / 36500);	
				printf("%f\n", DZT[i].Discount);
		
				break;
			}	

		}				

	}

	printf("DZT\n");
	printf("%d, %f, %f\n", DZT[3].Days, DZT[3].Rate, DZT[3].Discount);

	return (DZT);
}
