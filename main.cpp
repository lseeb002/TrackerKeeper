#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

struct Entry {
    string date;
    string category;
    string note;
    double amount;
    Entry(string d, string c, string n, double a)
	: date(d),category(c),note(n),amount(a) {}
};

struct Month {
    vector<Entry> entries;
    double totalSpent;
};

int read_entries(string file, Month& m){
    file += ".txt";
    ifstream fin(file.c_str());
    if (!fin.is_open()){
	cout << "Error Opening File" << endl;
	return 1;
    }
    int check = fin.peek();
    if (check == EOF){
	cout << "No entries!" << endl;
	return 0;
    }
    string d, c, n; //date, category, note
    double a; //amount
    while (fin >> d){
	//Create Entry, Add to vector
	string d, c, n; //date, category, note
	double a; //amount
        fin >> c >> n; fin >> a;
	m.totalSpent += a;	//keep track of amount as you read entries
	Entry temp(d,c,n,a);
	m.entries.push_back(temp);
    }
    fin.close();
    return 0;
}

void print_entries(Month& m){
    for (unsigned i=0; i < m.entries.size(); ++i){
	Entry e = m.entries.at(i);
	cout << setw(10) << e.date;
	cout << setw(15) << e.category;
	cout << setw(55) << e.note;
	cout << setw(10) << e.amount << endl;
    }
}

void print_cats(map<string,double> c){
    for (auto const& it : c){
	cout << it.first << " " << it.second << endl;
    }
}

int read_cats(string file, map<string,double>& cats){
    file += "cat.txt";
    ifstream fin(file.c_str());
    if (!fin.is_open()){
        cout << "Error Opening File" << endl;
        return 1;
    }
    string name;
    double total;
    while (fin >> name) {
	fin >> total;
	cats[name] = total;
    }
    return 0;
}

	
int main(){
    cout << "Welcome to Lui's Financial Tracker Keeper!" << endl;
    
    while (true){
	cout << "Which month do you want to look up (ie January15)? ";
	string monthChoice;
	cin >> monthChoice;
	cout << "Loading Data..." << endl;
	
	Month m;
        map<string,double> cats;
	if (read_entries(monthChoice,m) == 1) continue; //Error reading file
	if (read_cats(monthChoice,cats) == 1) continue; //Error reading file

    	cout << "What would you like to do?" << endl;
    	cout << "\t1. List Entries" << endl;
    	cout << "\t2. Add Entry" << endl;
    	cout << "\t3. Get Spending Total" << endl;
    	cout << "\t4. Quit" << endl << endl;
/*
    	int menuChoice = 0;
    	cin >> menuChoice;
        if (menuChoice < 1 || menuChoice > 4){
            cout << "Invalid Option! Please Make Another Choice." << endl;
	    continue;
	}

	switch (menuChoice) {
            case 1: printEntries(); break;
	    case 2: addEntry(); break;
	    case 3: printTotal(); break;
	    case 4: return 0;
	}
*/
    }

    return 0;
}
