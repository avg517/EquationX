#pragma once
//sugestion: make the constants be upper_case instead of lower case
#ifndef INCLUDED_TOKENS
#define INCLUDED_TOKENS
//separator and identifier
const int semicolonsign=0;
const int identifiersign=1;
const int backslash=23;
//operators
const int lesssign=2;
const int greatersign=3;
const int equalsign=4;
const int lessequ=5;
const int greaterequsign=6;
const int numbersign=7;
const int equalequsign=16;
//arithmetic operators
const int addsign=17;
const int minussign=18;
const int dividesign=19;
const int multiplysign=20;
const int modsign=26;
/*sugestion:
add square root and ^
*/
//separator
const int dotsign=8;
const int commasign=9;
//{}
const int obracketsign=10;
const int cbracketsign=11;
//()
const int oparantesesign=12;
const int cparantesesign=13;
//[]
const int osquarebracket=14;
const int csquarebracket=15;
//str opps
const int apostrophe=21;
const int quotation=22;
//miscellaneous
const int questionmark=25;

//binary operators (these will be experimental)
//const int andsign=13;
//const int orsign=14;
//const int notsign=15;
#endif
