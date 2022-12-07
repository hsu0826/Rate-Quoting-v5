#include "discount.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*discount zero curve selection & read file*/
//讀檔存進DZ Curve

struct DZCurve* DZCSelection(char FlowCcy[4], char CSACcy[4]) {


	char* DZCurvePath = (char*)malloc(sizeof(char) * 80);

	/*
	char* DZCurvePath1 = (char*)malloc(sizeof(char) * 80);
	char* DZCurvePath2 = (char*)malloc(sizeof(char) * 80);
	char* DZCurvePath3 = (char*)malloc(sizeof(char) * 80);
	*/

	struct DZCurve* DZ;
	DZ = malloc(LINEC * sizeof * DZ);
	memset(DZ, 1, sizeof(DZ));


	//int TermCount = sizeof(DiscountDate) / sizeof(DiscountDate[0]);
	//struct DZCurve* DZ; //最後輸出結果
	//DZ = malloc(((int)(TermCount)) * sizeof * DZ);
	//memset(DZ, 1, sizeof(DZ));


	/*
	double** DZ_Table;
	DZ_Table = malloc(50 * sizeof * DZ_Table);
	for (int t = 0; t < 50; t++) {
		DZ_Table[t] = malloc(8 * sizeof * DZ_Table[t]);
	}
*/

	strcpy(DZCurvePath, "D:\\Users\\00591875\\Desktop\\Rate_Quoting_Data\\");
	strcat(DZCurvePath, "USD");
	strcat(DZCurvePath, FlowCcy);
	strcat(DZCurvePath, "_DZCurve.csv");

	/*
	strcpy(DZCurvePath1, "D:\\Users\\00591875\\Desktop\\Rate_Quoting_Data\\");
	strcpy(DZCurvePath2, "D:\\Users\\00591875\\Desktop\\Rate_Quoting_Data\\");
	strcpy(DZCurvePath3, "D:\\Users\\00591875\\Desktop\\Rate_Quoting_Data\\");
	strcat(DZCurvePath1, "USD");
	strcat(DZCurvePath1, FlowCcy);
	strcat(DZCurvePath2, CSACcy);
	strcat(DZCurvePath2, CSACcy);
	strcat(DZCurvePath3, CSACcy);
	strcat(DZCurvePath3, "USD");
	strcat(DZCurvePath1, "_DZCurve.csv");
	strcat(DZCurvePath2, "_DZCurve.csv");
	strcat(DZCurvePath3, "_DZCurve.csv");
*/

	FILE* fpDZCurve = NULL;
	fpDZCurve = fopen(DZCurvePath, "r");

	/*
	//讀summit抓下來的Holiday List CSV檔
	FILE* fpDZCurve1 = NULL;
	fpDZCurve1 = fopen(DZCurvePath1, "r");
	FILE* fpDZCurve2 = NULL;
	fpDZCurve2 = fopen(DZCurvePath2, "r");
	FILE* fpDZCurve3 = NULL;
	fpDZCurve3 = fopen(DZCurvePath3, "r");
*/

	int row = 0;
	int column = 0;
	char input1[80]; //每行字串儲存空間

	/*
	while (fgets(input1, 50, fpDZCurve1)) {
		column = 0;
		row++;
*/


	if (fpDZCurve == NULL) {
		exit(1);
	}

	while (fgets(input1, 80, fpDZCurve) != NULL) {

		if (row != 0) {
			sscanf(input1, "%*[^,],%d,%lf,%lf", &DZ[row - 1].Days, &DZ[row - 1].Rate, &DZ[row - 1].Discount);
		}
		row++;
	}

	//printf("%d, %12.9f, %12.9f\n", DZ[3].Days, DZ[3].Rate, DZ[3].Discount);

	fclose(fpDZCurve);
	free(DZCurvePath);

	/*
	fclose(fpDZCurve3);
	fclose(fpDZCurve2);
	fclose(fpDZCurve1);
	free(DZCurvePath3);
	free(DZCurvePath2);
	free(DZCurvePath1);
	*/


	return (DZ);
}
