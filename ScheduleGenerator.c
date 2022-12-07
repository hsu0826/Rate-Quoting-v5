#include "schedule.h"
#include <stdio.h>
#include <stdlib.h>
// #include <string.h>
#include <math.h>


//計算期數
int DateCount(struct Date EffDate, struct Date MatDate, int Freq) {
    int d_count;
    d_count = floor((DateDiff(EffDate, MatDate, 4) * Freq / 365)) + 1;
    //printf("DateDiff %d\n", DateDiff(EffDate, MatDate, 4));
    //printf("DateDiff / 365: %d\n", (DateDiff(EffDate, MatDate, 4) * Freq / 365));
    printf("DateCount: %d\n", d_count);
    return (d_count);
}


/*Start and End Date */
//SpanLogic = 0; ShortEnd;
//SpanLogic = 1; ShortStart;
//Freq: 一年計息幾次; ex: Semiannual freq = 2;
struct Date* StartEndDate(struct Date* holiday, struct Date EffDate, struct Date MatDate, int Freq, char Cal[4], int CK, int SpanLogic) {

    struct Date* StartEnd; //存Start and End Dates

    //每次計息期間間隔日
    int DC = DateCount(EffDate, MatDate, Freq);

    StartEnd = malloc((DC + 2) * sizeof * StartEnd);

    if (SpanLogic == 0) {

        for (int i = 0; i < DC; i++) {
            StartEnd[i] = EffDate;
            StartEnd[i].month = StartEnd[i].month + i * 12 / Freq;
            if (StartEnd[i].month > 12) {
                int Y_plus = ceil(StartEnd[i].month / 12);
                StartEnd[i].year = StartEnd[i].year + Y_plus;
                StartEnd[i].month = StartEnd[i].month % 12;
            }
        }
    }

    else {

        for (int j = 0; j < DC; j++) {
            StartEnd[j] = MatDate;
            StartEnd[j].month = StartEnd[j].month - 12 / Freq * (DC - j);
            if (StartEnd[j].month < 1) {
                int Y_minus = ceil(-(StartEnd[j].month - 1) / 12);
                StartEnd[j].year = StartEnd[j].year - Y_minus;
                StartEnd[j].month = 12 - ((-StartEnd[j].month) % 12);
            }
        }

    }

    StartEnd[0] = EffDate;
    StartEnd[DC] = MatDate;

    //convention adjustment
    for (int n = 0; n < DC + 1; n++) {
        StartEnd[n] = ConventionAdj(holiday, StartEnd[n], CK, Cal);
    }

    return (StartEnd);
}


//Payment Date Adjustment
//Plain = 1;
//Payment Delay = 2;
//Lookback = 3;
//Lookout = 4;
//EOM False = 0;
//EOM True = 1;
struct Date PaymentDate(struct Date* holiday, struct Date ReferDate, char Cal[4], int PayTypeFlag, int DayGap, int EOM) {

    struct Date PayDate;

    if (PayTypeFlag == 1) {
        PayDate = ReferDate;
    }
    else if (PayTypeFlag == 2) {
        PayDate = DateAdj(holiday, ReferDate, DayGap, Cal);
    }

    if (EOM == 1) {
        determineDaysInMonth(PayDate, 4);
        PayDate.day = days_in_month[(PayDate.month)];
    }

    return(PayDate);
}


//Reset Date Adjustment
struct Date ResetDate(struct Date* holiday, struct Date ReferDate, char Cal[4], int DayGap) {

    struct Date FixingDate;

    FixingDate = DateAdj(holiday, ReferDate, DayGap, Cal);

    return(FixingDate);
}


//Aggregation (要改成return array嗎)

void ScheduleTable(struct Date* StartEndDate, struct Date* holiday, int Term, char Cal[4], int PayTypeFlag, int PaymentGap, int ResetTypeFlag, int ResetGap, int EOM) {

    struct Date** S_Table;
    S_Table = malloc( (Term + 2) * sizeof * S_Table);
    for (int t = 0; t < (Term + 1); t++) {
        S_Table[t] = malloc(4 * sizeof * S_Table[t]);
    }
    

    //延後交割
    struct Date* Payment;
    Payment = malloc((Term + 1) * sizeof * Payment);

    for (int p = 0; p < Term + 1; p++) {

        Payment[p] = StartEndDate[p];
        Payment[p] = PaymentDate(holiday, Payment[p], Cal, PayTypeFlag, PaymentGap, EOM);

    }

    //Reset
    struct Date* Reset;
    Reset = malloc((Term + 1) * sizeof * Reset);

    for (int q = 0; q < Term + 1; q++) {

        if (ResetTypeFlag == 0) {
            Reset[q] = StartEndDate[q];
        }

        else {
            Reset[q] = StartEndDate[q + 1];
        }

        Reset[q] = ResetDate(holiday, Reset[q], Cal, ResetGap);

    }


for (int f = 0; f < Term; f++) {

    S_Table[f][0] = StartEndDate[f];
    S_Table[f][1] = StartEndDate[f + 1];
    S_Table[f][2] = Reset[f + 1];
    S_Table[f][3] = Payment[f + 1];
}

printf("Start\t\tEnd\t\tReset\t\tPayment\n");

for (int a = 0; a < Term; a++) {
    for (int b = 0; b < 3; b++) {
        printf("%d-%d-%d\t", S_Table[a][b].year, S_Table[a][b].month, S_Table[a][b].day);
    }
    printf("%d-%d-%d\n", S_Table[a][3].year, S_Table[a][3].month, S_Table[a][3].day);
}


free(Reset);
free(Payment);
for (int w = 0; w < Term + 1; w++)
{
    free(S_Table[w]);
}

free(S_Table);
}
