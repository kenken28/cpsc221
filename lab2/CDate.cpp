// ..................................................  
// CPSC221 Lab 2: CDate lab exercise
// Adapted from Hagit Schechter, Jan 2007
// ..................................................

#include <iostream>
#include <string>
#include "CDate.h"

using namespace std;

CDate::CDate( void )
{
	m_year = m_month = m_day = 0;
}

CDate::CDate( int year, int month, int day )
{
	setDate( year, month, day );        
}

CDate::CDate( int year, string month, int day )
{
	// you need to set the code here
	setDate( year, month, day );
}

bool CDate::isValidDate( int year, int month, int day )
{
	// you need to fill in the code here (replace the return below)
	// and check the validy of a day, month, and year.
        if (isValidDay(year, month, day) && year >= 0) {
            return true;
        }
        return false;
}

bool CDate::isValidDate( int year, string month, int day)
{
	// you need to fill in the code here (replace the return below)
	// hint it is very similar to the int month routine, but you need to 
	// use monthStr2Num here
	return isValidDate(year, monthStr2Num(month), day);
}

int CDate::monthStr2Num(string month)
{
	// you need to fill in the code here (replace the return below)
	int numMonth = -1;
	
	if (month == "Janurary") {
            numMonth = 1;
	} else if (month == "February") {
            numMonth = 2;
	} else if (month == "March") {
            numMonth = 3;
	} else if (month == "April") {
            numMonth = 4;
	} else if (month == "May") {
            numMonth = 5;
	} else if (month == "June") {
            numMonth = 6;
	} else if (month == "July") {
            numMonth = 7;
	} else if (month == "August") {
            numMonth = 8;
	} else if (month == "September") {
            numMonth = 9;
	} else if (month == "October") {
            numMonth = 10;
	} else if (month == "November") {
            numMonth = 11;
	} else if (month == "December") {
            numMonth = 12;
	}
	
	return numMonth;
}

bool CDate::isValidDay(int year, int month, int day)
{
	if ((day<1) || (day>31)) return false;

	bool valid;

	switch (month) {
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			// you need to fill in the code here
			(day<=31) ? valid=true : valid=false;
			break;
		case 2:
			if ( ((year % 4) == 0 && (year % 100) != 0) || (year % 400) == 0) {
				(day<=29) ? valid=true : valid=false;
			} else {
				(day<=28) ? valid=true : valid=false;
			}
			break;
		case 4:
		case 6:
		case 9:
		case 11:
			// you need to fill in the code herehere
			(day<=30) ? valid=true : valid=false;
			break;
		default:
			// you need to fill in the code here
			valid=false;
			break;
	}

	return valid;
}

void CDate::setDate( int year, int month, int day )
{
	if( isValidDate( year, month, day ) )
	{    
		m_year = year;
		m_month = month;
		m_day = day;
	}
	else {
		m_year = m_month = m_day = 0;
	}
}


void CDate::setDate( int year, string month, int day )
{
	// you need to fill in the code here
	// hint: use monthStr2Num here
        setDate(year, monthStr2Num(month), day);
}

void CDate::print( void )
{
	cout << m_day << "/" << m_month << "/" << m_year << endl;
}

// main
int main(void)
{
	CDate myDate0(2000,5,25);
	CDate myDate1(-1,"May",25);
	CDate myDate2(2000,"April",31);
	CDate myDate3(2001,"February",29);
	CDate myDate4(2000,"February",29);
	CDate myDate5(2000,"December",32);
	CDate myDate6(2000,"December",31);
	CDate myDate7(2000,"November",31);
	CDate myDate8(2000,"November",30);

	myDate0.print();
	myDate1.print();
	myDate2.print();
	myDate3.print();
	myDate4.print();
	myDate5.print();
	myDate6.print();
	myDate7.print();
	myDate8.print();

#ifdef _WIN32
	system("PAUSE"); // needed for windows to prevent the program from terminating and the command window to close
#endif

	return 0;
}
