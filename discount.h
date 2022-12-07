#pragma once
#ifndef DISCOUNT_H_
#define _DISCOUNT_H_

#define LINEC 50

struct DZCurve { int Days; double Rate; double Discount; };
struct DZCurve* DZCSelection(char FlowCcy[4], char CSACcy[4]); //ÅªÀÉ
struct DZCurve* DZ_Table(struct DZCurve* DZC, int DiscountDate[], int TermCount); //²£¥XCash Flow Table DZ Curve
//struct DZCurve* DZAdj(char FlowCcy[4], char CSACcy[4], int DiscountDate[]);


#endif