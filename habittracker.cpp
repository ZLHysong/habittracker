#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <sstream>
#include <fstream>
#include <cstddef>
#include <bits/stdc++.h>

using namespace std;

int days[] = { 31, 28, 31, 30, 31, 30, 
               31, 31, 30, 31, 30, 31 }; 
  
// Function to return the day number 
// of the year for the given date 
int dayOfYear(string date) { 
    // Extract the year, month and the 
    // day from the date string 
    int year = stoi(date.substr(0, 4)); 
    int month = stoi(date.substr(5, 2)); 
    int day = stoi(date.substr(8)); 
  
    // If current year is a leap year and the date 
    // given is after the 28th of February then 
    // it must include the 29th February 
    if (month > 2 && year % 4 == 0 
        && (year % 100 != 0 || year % 400 == 0)) { 
        ++day; 
    } 
  
    // Add the days in the previous months 
    while (month-- > 0) { 
        day = day + days[month - 1]; 
    } 
    return day; 
} 

int  getNumberOfDays(int month, int year) {
	//leap year condition, if month is 2
	if( month == 2)
	{
		if((year%400==0) || (year%4==0 && year%100!=0))	
			return 29;
		else	
			return 28;
	}
	//months which has 31 days
	else if(month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month==12)	
		return 31;
	else 		
		return 30;
} 

string getDayOfWeek(int weekday) {
	vector<string> days = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
	string day = days[ weekday ];
	return day;
}

string getMonthIndex( int monthNumber ) {
	vector<string> months = { "January", "February", "March", "April", "May", "June", "July",
	"August", "September", "October", "November", "December" };
   return months[ monthNumber ];
}

int miscDateTimeValues () {
	time_t t = time(NULL);
	tm* timePtr = localtime(&t);
	cout << "The other date time functions I can access quickly are: " << endl;
	cout << "minutes:          " << timePtr->tm_min   << endl;
	cout << "seconds:          " << timePtr->tm_sec   << endl;
	cout << "hours:            " << timePtr->tm_hour  << endl;
	cout << "day of month:     " << timePtr->tm_mday  << endl;
	cout << "month of year:    " << timePtr->tm_mon   << endl;
	cout << "year:             " << timePtr->tm_year  << endl;
	cout << "weekday:          " << timePtr->tm_wday  << endl;
	cout << "day of year:      " << timePtr->tm_yday  << endl;
	cout << "daylight savings: " << timePtr->tm_isdst << endl;
	return 0;
}

int dayNumber(int day, int month, int year) { 
  
    static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 
                       4, 6, 2, 4 }; 
    year -= month < 3; 
    return ( year + year/4 - year/100 + 
             year/400 + t[month-1] + day) % 7; 
}

int drawCalendar(string name) {
	time_t t = time(NULL);
	tm* timePtr = localtime(&t);
	int currDate = timePtr->tm_mday;
	int currMonth = timePtr->tm_mon;
	int currYear = timePtr->tm_year + 1900;	
    int day = timePtr->tm_yday+1;
	int days = getNumberOfDays(currMonth + 1, currYear);
	int firstOfMonth = dayNumber(1, currMonth+1, currYear);
	string month = getMonthIndex(currMonth);
    ifstream in_file("data.txt");
    vector<string> v; 

    if (in_file.is_open()) {
        string line;
        while (getline(in_file, line)) {
            int brk = line.find(":");
            string sub = line.substr(0, brk);
            // printf("%s", sub.c_str());
            if(strcmp(sub.c_str(), name.c_str()) == 0) {
                string values = line.substr(brk + 1);
                // cout << line.substr(brk + 1) << endl;
            
                stringstream ss(values); 
            
                while (ss.good()) { 
                    string substr; 
                    getline(ss, substr, ','); 
                    v.push_back(substr); 
                }
            }
        }
        in_file.close();
    } else {
        cout << "Habit does not exist. Add it with `-a`.";
        return 0;
    }
    
    // cout  << "Dates to check for: ";
    // for (size_t j = 0; j < v.size(); j++)
    // 	cout << v[j].c_str() << ", ";
    // cout << endl;
    
    printf("  %s\n", name.c_str());
	// printf("  %s, %i\n", month.c_str(), currYear);
	// printf("  S  M  T  W  T  F  S\n");

    for (int k = 0; k < firstOfMonth; k++) 
		printf("  "); 

    string printVal;
    
    for (int i = 1; i < days; i++) {
        string yearDayStr;
        if (currMonth < 10) {
            yearDayStr = to_string(currYear) + "-0" + to_string(currMonth+1) + "-" + to_string(i); 
        } else {
            yearDayStr = to_string(currYear) + "-" + to_string(currMonth+1) + "-" + to_string(i);  
        }
        int yearDay = dayOfYear(yearDayStr);
        int dayOfWeek = dayNumber(i, currMonth+1, currYear);

        string key = to_string(yearDay);
        if (i > currDate) {
            printf("%s", "  \033[1;35m∙\033[0m");
        } else {
            if (std::find(v.begin(), v.end(), key) != v.end()){
                if (to_string(yearDay) == to_string(day)) {
                    printVal = "  \033[1;32m◆\033[0m";
                    printf("%s", printVal.c_str());
                } else {
                    printVal = "  ◆";
                    printf("%s", printVal.c_str());
                }
            } else if (to_string(yearDay) == to_string(day)) {
                printVal = "  \033[1;32m◇\033[0m";
                printf("%s", printVal.c_str());
            } else {
                printVal = "  ◇";
                printf("%s", printVal.c_str());
            }
        }
        if (dayOfWeek >= 6) {
            printf("\n");
        }
    }
    printf("\n");
	return 0;
}

int printToday() {
	time_t t = time(NULL);
	tm* timePtr = localtime(&t);
	
	printf("Today is %s, %s %i, %i\n",
			getDayOfWeek(timePtr->tm_wday).c_str(),
			getMonthIndex(timePtr->tm_mon).c_str(),
			timePtr->tm_mday,
			timePtr->tm_year + 1900);
    return 0;
}

int getData() {
    string line;
    ifstream datafile ("data.txt");
    
    if (datafile.is_open())
    {
        while ( getline (datafile,line) )
        {
        cout << line << endl;
        }
        datafile.close();
    }

  else cout << "Unable to open file"; 
    return 0;
}

int checkIfHabitExists(string name) {
    // cout << "Looking for: " << name << "\n";
    ifstream file("data.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            int brk = line.find(":");
            string sub = line.substr(0,brk);
            // printf("%s", sub.c_str());
            if(strcmp(sub.c_str(), name.c_str()) == 0) {
                // printf("Habit exists\n");
                return 1;
            }
        }
        file.close();
    }
    return 0;
}

int deleteHabit(string name) {
    cout << "TODO: delete row from file." << endl;
    return 0;
}

int uncompleteHabit(string name) {
    cout << "TODO: delete day from habit." << endl;
    return 0;
}

int putNewHabit(string name) {
    fstream fs;
    printf("%s added.\n", name.c_str());
    fs.open("data.txt", fstream::app);
    fs << name << ":\n";
    return 0;
}

int getHabits() {
    ifstream file("data.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            int brk = line.find(":");
            string sub = line.substr(0,brk);
            printf("%s\n", sub.c_str());
        }
    }
    return 0;
}

int completeHabit(string name) {
	time_t t = time(NULL);
	tm* timePtr = localtime(&t);
    int day = timePtr->tm_yday+1;
    char oldname[] = "data.txt";
    char newname[] = "data.bak";
    ifstream in_file("data.txt");
    ofstream out_file("data.tmp");

    if(!in_file || !out_file)
    {
        cout << "Error opening files!" << endl;
        return 1;
    }

    if (in_file.is_open()) {
        string line;
        while (getline(in_file, line)) {
            int brk = line.find(":");
            string sub = line.substr(0,brk);
            // printf("%s", sub.c_str());
            if(strcmp(sub.c_str(), name.c_str()) == 0) {
                char lastTwo = line.at(line.length() - 2 );
                size_t checkComma = line.find_last_of(',');
                size_t checkColon = line.find(":");
                string lastVal;
                string today;
                if (checkComma <= line.length()) {
                    lastVal = line.substr(checkComma);
                    today = "," + to_string(day);
                } else {
                    if (checkColon) {
                        lastVal = line.substr(checkColon);
                        today = ":" + to_string(day);
                    }
                }
                if (today == lastVal) {
                    printf("You have already marked this as complete today.\n");
                    return 1;
                }
                char lastChar = line.at(line.length() - 1 );
                if (lastChar != ':') {
                    line += ",";
                }
                line += to_string(day);
                out_file << line << "\n";
            } else {
                out_file << line << "\n";
            }
        }
        if(rename(oldname, newname) != 0 ) {
            cout << "Error renaming file.\n";
            return 1;
        } else {          
            if(rename("data.tmp", "data.txt") != 0 ) {
                cout << "Error renaming file.\n";
                return 1;
            } else {
                cout << "File renamed successfully\n";
                
            }
        }
        in_file.close();
        return 1;
    } else {
        cout << "Habit does not exist. Add it with `-a`.";
        return 0;
    }
    return 0;
}

int printHelp() {
    printf(" NAME\n");
    printf("     Habit Tracker\n");
    printf(" SYNOPSIS\n");
    printf("     habittracker [OPTION] [HABIT]\n");
    printf(" DESCRIPTION\n");
    printf("     Habit Tracker is a simple meant to help you track your daily tasks in a way that is simple and easy to use.\n");
    printf("     The basic concept is that you will have a list of things you do every day, meditate, study, exercise,\n");
    printf("     hydrate, etc. This application will put those into a simple, pretty calendar so you can see with one line\n");
    printf("     whether you met your goals for each day this month.\n");
    printf(" TODO\n");
    printf("     - Delete a Habit\n");
    printf("     - Uncomplete a Habit\n");
    printf("     - Show all Calendars from one command\n");
    printf(" OPTIONS\n");
    printf("     `-a`, `--add`\n");
    printf("         Add a new habit\n");
    printf("     `-d`, `--delete` (THIS FEATURE IS NOT CURRENTLY FUNCTIONAL)\n");
    printf("         Delete a habit\n");
    printf("     `-c`, `--complete`\n");
    printf("         Mark habit complete\n");
    printf("     `-i`, `--incomplete` (THIS FEATURE IS NOT CURRENTLY FUNCTIONAL)\n");
    printf("         Mark habit incomplete\n");
    printf("     `-l`, `--list`\n");
    printf("         List all habits\n");
    printf("     `-s`, `--show`\n");
    printf("        Show habit calendar\n");
    printf("     `-h`, `--help`\n");
    printf("        Show program help\n");
    printf(" LEGEND\n");
    printf("     ◆ Task Complete (Previous Day)\n");
    printf("     \033[1;32m◆\033[0m Task Complete (Today)\n");
    printf("     ◇ Task Incomplete (Previous Day)\n");
    printf("     \033[1;32m◇\033[0m Task Incomplete (Today)\n");
    printf("     \033[1;35m∙\033[0m Day Not Happened Yet\n");
    printf(" AUTHOR\n");
    printf("     Zachery Hysong\n");
    printf(" REPORTING BUGS AND MAKING SUGGESTIONS\n");
    printf("     Feel free to email me with any bugs or suggestions at `zlhysong@gmail.com`\n");
    printf(" COPYRIGHT\n");
    printf("     Copyright © 2020 Zachery Hysong. License GPLv3+: GNU GPL version 3 or later <https://gnu.org/licenses/gpl.html>.\n");
    printf("     This is free software: you are free to change and redistribute it.  There is NO WARRANTY, to the extent permitted by law.\n");
    return 0;
}

//Main program
int main(int argc, char* argv[]) {
    if (argc < 2) {
        printHelp();
        return 0;
    }
    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];
        
        if ((arg == "-h") || (arg == "--help")) {
            printHelp();
            return 0;
        } else if ((arg == "-a") || (arg == "--add")) {
            if (i + 1 < argc) { // Make sure we aren't at the end of argv!
                int exists = checkIfHabitExists(argv[2]);
                if (!exists) {
                    putNewHabit(argv[2]);
                } else {
                    printf("Habit exists. Complete it with `-c`\n");
                }
            } else { // Uh-oh, there was no argument to the destination option.
                  cerr << "(-a / --add) option requires one argument." << endl;
                return 0;
            }
        } else if ((arg == "-c") || (arg == "--complete")) {
            if (i + 1 < argc) { // Make sure we aren't at the end of argv!
                int exists = checkIfHabitExists(argv[2]);
                if (exists) {
                    completeHabit(argv[2]);
                } else {
                    printf("Habit does not exist. Add it with `-a`\n");
                }
            } else { // Uh-oh, there was no argument to the destination option.
                  cerr << "(-c / --complete) option requires one argument." << endl;
                return 0;
            }
        } else if ((arg == "-d") || (arg == "--delete")) {
            if (i + 1 < argc) { // Make sure we aren't at the end of argv!
                int exists = checkIfHabitExists(argv[2]);
                if (exists) {
                    deleteHabit(argv[2]);
                } else {
                    printf("Habit does not exist.\n");
                }
            } else { // Uh-oh, there was no argument to the destination option.
                  cerr << "(-d / --delete) option requires one argument." << endl;
                return 0;
            }
        } else if ((arg == "-l") || (arg == "--list")) {
            if (i + 1 < argc) { // Make sure we aren't at the end of argv!
                int exists = checkIfHabitExists(argv[2]);
                if (exists) {
                    drawCalendar(argv[2]);
                } else {
                    printf("Habit does not exist. Add it with `-a`\n");
                }
            } else { // Uh-oh, there was no argument to the destination option.
                  cerr << "(-l / --list) option requires one argument." << endl;
                return 0;
            }
        } else if ((arg == "-g") || (arg == "--gethabits")) {
            getHabits();
        } else if ((arg == "-u") || (arg == "--uncomplete")) {
            if (i + 1 < argc) { // Make sure we aren't at the end of argv!
                int exists = checkIfHabitExists(argv[2]);
                if (exists) {
                    uncompleteHabit(argv[2]);
                } else {
                    printf("Habit does not exist. Add it with `-a`\n");
                }
            } else { // Uh-oh, there was no argument to the destination option.
                  cerr << "(-u / --uncomplete) option requires one argument." << endl;
                return 0;
            }
        }
    }

	return 0;
}