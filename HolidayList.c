#include "schedule.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*holiday selection & read file*/

struct Date* Holiday(char HolFlag[4]) {

	char* holidayPath = (char*)malloc(sizeof(char)*80);
	struct Date* holiday;
	holiday = malloc(5000 * sizeof * holiday);
	memset(holiday, 1, sizeof(holiday));
	

	strcpy(holidayPath, "D:\\Users\\00591875\\Desktop\\Rate_Quoting_Data\\");
	strcat(holidayPath, HolFlag);
	strcat(holidayPath, "_Holidays.csv");

	printf("%s\n", holidayPath);
	
	/*讀summit抓下來的Holiday List CSV檔*/
	FILE* fpHoliday = NULL;
	fpHoliday = fopen(holidayPath, "r");

	int line = 0; /*行數*/
	char input[20]; /*每行字串儲存空間*/
	//	holiday = (struct Date*)malloc(2000 * sizeof(struct Date));

	/*int** h = (int**)malloc(sizeof(int*) * 300);
	for (int i = 0; i < 300; i++) {
		h[i] = (int*)calloc(3, sizeof(int));}*/

	if (fpHoliday == NULL) {
		exit(1);
	}

	else {
		for (line = 0; line < LINE; line++) {
			fscanf(fpHoliday, "%d/%d/%d", &holiday[line].year, &holiday[line].month, &holiday[line].day);
			//printf("%d-%d-%d\n", holiday[line].year, holiday[line].month, holiday[line].day);
		}
	}

	fclose(fpHoliday);
	free(holidayPath);

	return (holiday);
}


