#ifndef _SCHEDULE_H_
#define _SCHEDULE_H_

#define LINE 3300

struct Date { int year; int month; int day; }; /*referred date formatting*/

struct Date* Holiday(char HolFlag[4]); /*holiday selection & read file*/

int DateDiff(struct Date StartDate, struct Date EndDate, int Basis); /*Actual date difference*/


struct Date InArrear(struct Date* holiday, struct Date ReferDate, int DayGap, char Cal[4]); /*In Arrear Adjustment*/
struct Date InAdvance(struct Date* holiday, struct Date ReferDate, int DayGap, char Cal[4]); /*In Advance Adjustment*/
struct Date ConventionAdj(struct Date* holiday, struct Date ReferDate, int CK, char Cal[4]); /*Convention key adjustment*/
struct Date DateAdj(struct Date* holiday, struct Date ReferDate, int DayGap, char Cal[4]); /*Date Adjustment*/


int DateCount(struct Date EffDate, struct Date MatDate, int Freq);
struct Date* StartEndDate(struct Date* holiday, struct Date EffDate, struct Date MatDate, int Freq, char Cal[4], int CK, int SpanLogic);
struct Date PaymentDate(struct Date* holiday, struct Date ReferDate, char Cal[4], int PayTypeFlag, int DayGap, int EOM); //Payment Date Adjustment
struct Date ResetDate(struct Date* holiday, struct Date ReferDate, char Cal[4], int DayGap); //Reset Date Adjustment

void ScheduleTable(struct Date* StartEndDate, struct Date* holiday, int Term, char Cal[4], int PayTypeFlag, int PaymentGap, int ResetTypeFlag, int ResetGap, int EOM);

int days_in_month[13];
int determineDaysInMonth(struct Date d, int Basis);
//int determineDaysInYear(struct Date g, int Basis);

#endif

