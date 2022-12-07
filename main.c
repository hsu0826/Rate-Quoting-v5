
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "schedule.h"
#include "discount.h"

//待解決:

// shortend?

int main() {

	char Hol[4];
	int PaymentGap;

	int ResetGap; //In advance, 會是負數
	int Conv = 1; //Modified Following;
	int PT = 2; //Payment Delay;	
	int RT = 0; //InAdvance (期間開始前Fix) = 0; InArrear (期間開始後Fix) = 1;
	int EOMA = 0; //no End of Month Adjustment;
	int CcyBasis = 4; //Actual/Actual;
	int Freq = 4; //Quarterly;
	int Span = 0; //ShortEnd;
	int Term;

	struct Date eff, mat;
	struct Date* holidaylist;
	//struct Date referdate;

	char Flow[4];
	char CSA[4];
	
	
	int DD[] = { 90, 180, 270, 360, 450 }; //discount date vector
	int TermCount = sizeof(DD) / sizeof(DD[0]); //要跟Term整合


	struct DZCurve* DZC;
	DZC = malloc(50 * sizeof * DZC);


	/*輸入HolidayFlag eg."USL"*/
	printf("HolidayFlag：\n");
	fgets(Hol, 4, stdin);

	//讀檔
	//holidaylist = Holiday(Hol); 

	/*輸入開始結束日期*/
	printf("Start Date(yyyy-mm-dd): \n");
	scanf("%d-%d-%d", &eff.year, &eff.month, &eff.day);
	printf("End Date(yyyy-mm-dd): \n");
	scanf("%d-%d-%d", &mat.year, &mat.month, &mat.day);


	/*輸入計息頻率 ex: Semianuual freq = 2 */
	//printf("Frequency：\n");
	//scanf("%d", &Freq);
	Term = DateCount(eff, mat, Freq);

	/*輸入 Convention Key*/
	//printf("Convention Key：\nModified Following = 1;\nModified Previous = 2;\nFollowing = 3;\nPreceding = 4\n");
	//scanf("%d", &Conv);

	/*輸入 Pay Type*/
	//printf("Pay Type Flag：\nPlain = 1;\nPayment Delay = 2;\nLookback = 3;\nLookout = 4;\n");
	//scanf("%d", &PT);

	/*輸入 EOM*/
	//printf("EOM: \nEOM False = 0;\nEOM True = 1;\n");
	//scanf("%d", &EOMA);

	/*輸入 Reset Type*/
	// InAdvance(期間開始前Fix) = 0; InArrear(期間開始後Fix) = 1;
	//printf("Reset Type Flag：\nInAdvance(期間開始前做Fixing) = 0;\nInArrear(期間開始後做Fixing) = 1\n");
	//scanf("%d", &RT);

	/*輸入延遲付款日期*/
	printf("Payment Day Gap：\n");
	scanf("%d", &PaymentGap);

	/*輸入計息Reset日期*/
	printf("Reset Day Gap (若In advance調整, 則輸入負數)：\n");
	scanf("%d", &ResetGap);

	/*輸入SpanLogic*/
	//printf("SpanLogic：\n");
	//scanf("%d", &Span);

	/*輸入Day Count Convention Basis*/
	//30/360 = 1;
	//Actual/360 = 2;
	//Actual/365 = 3;
	//Actual/Actual = 4
	//printf("Day Count Convention Basis：\n");
	//scanf("%d", &CcyBasis);

	/*輸入FlowCcy eg."USD"*/
	printf("FlowCcy：\n");
	scanf("%s", &Flow);

	/*輸入CSACcy eg."TWD"*/
	printf("CSACcy：\n");
	scanf("%s", &CSA);


	//測試日期差
	//int d = DateDiff(eff, met, CcyBasis);
	//printf("%d\n", d);


	//測試成功讀檔	
	//printf("%d-%d-%d\n", holidaylist[3].year, holidaylist[3].month, holidaylist[3].day);
	
	//讀檔USD SOFR Zero Curve
	DZC = DZCSelection(Flow, CSA);
	//DZC = DZCAdj(Flow, CSA, DD);
	
	//測試成功讀檔	
	printf("DZC!!:%d;%f;%f\n", DZC[0].Days, DZC[0].Rate, DZC[0].Discount);

	//測試跳過Holiday
	//struct Date refer1 = ConventionAdj(holidaylist, eff, Conv, Hol);
	//printf("Convention Adjustment Start Date = %d-%d-%d\n", refer1.year, refer1.month, refer1.day);


	//測試Start End Date
	//struct Date* SE = StartEndDate(holidaylist, eff, mat, Freq, Hol, Conv, Span);

	//ScheduleTable(SE, holidaylist, Term, Hol, PT, PaymentGap,RT, ResetGap, EOMA);

	struct DZCurve* DZT = DZ_Table(DZC, DD, TermCount); //要改成Days


	free(DZT);
	free(DZC);
	//free(SE);
	//free(holidaylist);

	return 0;
}