#include "schedule.h"
/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
*/

int days_in_year;
int days_in_month[13] = { 31, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
int day_31[8] = { 0, 1, 3, 5, 7, 8, 10, 12 };



/*判斷是否閏年*/
int leapYear(int year) {
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
        return 1;
    }
    else {
        return 0;
    }
}


/*每月天數*/
//30/360 = 1;
//Actual/360 = 2;
//Actual/365 = 3;
//Actual/Actual = 4
//待解決：用過1怎麼回去預設值
int determineDaysInMonth(struct Date d, int Basis)
{

    if (Basis != 1) {
        for (int l = 0; l < 13; l++) {
            for (int k = 0; k < 8; k++) {
                if (l == day_31[k]) {
                    days_in_month[l] = 31;
                    break;
                }
                else {
                    days_in_month[l] = 30;
                }

            }
        }

        if (leapYear(d.year)) {

            days_in_month[2] = 29;
        }

        else {

            days_in_month[2] = 28;
        }
        return 1;
    }

    else {

        for (int m = 0; m < 13; m++) {
            days_in_month[m] = 30;
        }
        return 1;
    }

}

int determineDaysInYear(int y, int Basis)
{

    if (Basis == 1 || Basis == 2) {

        days_in_year = 360;
    }

    else if (Basis == 3) {

        days_in_year = 365;
    }

    else {

        if (leapYear(y)) {

            days_in_year = 366;
        }
        else {

            days_in_year = 365;
        }
    }
    return 1;
}

//天數計算 since 2003
int days_date(struct Date s, int Basis) {

    determineDaysInMonth(s, Basis);

    int sum = 0;

    for (int i = 2003; i < s.year; i++) {

        determineDaysInYear(i, Basis);

        sum += days_in_year;
    }

    for (int k = 1; k < s.month; k++) {

        sum += days_in_month[k];
    }

    return sum + s.day;
}

//計算日期差
int DateDiff(struct Date StartDate, struct Date EndDate, int Basis) {

    int diff = days_date(EndDate, Basis) - days_date(StartDate, Basis);
    return (diff);
}


/*Date Adjustment*/
//End of Month???

//In Arrear
struct Date InArrear(struct Date* holiday, struct Date ReferDate, int DayGap, char Cal[4]) {

    determineDaysInMonth(ReferDate, 4);
    int DayGapFlag = 0;
    struct Date ReferDateAdj;
    ReferDateAdj = ReferDate;

    while (DayGapFlag < DayGap) {
        ReferDateAdj.day = ReferDateAdj.day + 1;
        DayGapFlag = DayGapFlag + 1;

        if (ReferDateAdj.day > (days_in_month[ReferDateAdj.month])) {
            ReferDateAdj.day = ReferDateAdj.day - days_in_month[ReferDateAdj.month];
            ReferDateAdj.month = ReferDateAdj.month + 1;
            if (ReferDateAdj.month > 12) {
                ReferDateAdj.month = ReferDateAdj.month - 12;
                ReferDateAdj.year = ReferDateAdj.year + 1;
            }
        }

        for (int j = 0; j < LINE; j++) {
            //Skip Holiday
            if (holiday[j].year == ReferDateAdj.year && holiday[j].month == ReferDateAdj.month && holiday[j].day == ReferDateAdj.day) {
                DayGapFlag = DayGapFlag - 1;
                break;
            }

        }
    }
    return (ReferDateAdj);
}



//In Advance
struct Date InAdvance(struct Date* holiday, struct Date ReferDate, int DayGap, char Cal[4]) {

    determineDaysInMonth(ReferDate, 4);
    int DayGapFlag = 0;
    struct Date ReferDateAdj;
    ReferDateAdj = ReferDate;

    while (DayGapFlag < -DayGap) {
        ReferDateAdj.day = ReferDateAdj.day - 1;
        DayGapFlag = DayGapFlag + 1;

        if (ReferDateAdj.day < 1) {
            ReferDateAdj.day = ReferDateAdj.day + days_in_month[ReferDateAdj.month - 1];
            ReferDateAdj.month = ReferDateAdj.month - 1;
            if (ReferDateAdj.month < 1) {
                ReferDateAdj.month = ReferDateAdj.month + 12;
                ReferDateAdj.year = ReferDateAdj.year - 1;
            }
        }
        for (int j = 0; j < LINE; j++) {
            //Skip Holiday
            if (holiday[j].year == ReferDateAdj.year && holiday[j].month == ReferDateAdj.month && holiday[j].day == ReferDateAdj.day) {
                DayGapFlag = DayGapFlag - 1;
                break;
            }

        }
    }
    return (ReferDateAdj);
}


/*Convention Key Adjustment*/
//Modified Following = 1;
//Modified Previous = 2;
//Following = 3;
//Preceding = 4
struct Date ConventionAdj(struct Date* holiday, struct Date ReferDate, int CK, char Cal[4]) {
    if (CK == 1) {
        if (InArrear(holiday, ReferDate, 1, Cal[4]).month != ReferDate.month) {
            return (InAdvance(holiday, InArrear(holiday, ReferDate, 1, Cal[4]), -1, Cal[4]));
        }
        else {
            return (InArrear(holiday, ReferDate, 1, Cal[4]));
        }
    }
    else if (CK == 2) {
        if (InAdvance(holiday, ReferDate, -1, Cal[4]).month != ReferDate.month) {
            return (InArrear(holiday, InAdvance(holiday, ReferDate, -1, Cal[4]), 1, Cal[4]));
        }
        else {
            return (InAdvance(holiday, ReferDate, -1, Cal[4]));
        }
    }
    else if (CK == 3) {
        return (InArrear(holiday, ReferDate, 1, Cal[4]));
    }
    else if (CK == 4) {
        return (InAdvance(holiday, ReferDate, -1, Cal[4]));
    }
}


/*Date Adjustment*/
struct Date DateAdj(struct Date* holiday, struct Date ReferDate, int DayGap, char Cal[4]) {
    if (DayGap > 0) {
        return(InArrear(holiday, ReferDate, DayGap, Cal[4]));
    }
    else {
        return(InAdvance(holiday, ReferDate, DayGap, Cal[4]));
    }
}




    