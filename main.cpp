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
    string d, c, n; //date, category, note
    double a = 0.0; //amount
    int check = fin.peek();
    while (check != EOF){
	//Create Entry, Add to vector
	string d, c, n; //date, category, note
	double a; //amount
        fin >> d >> c >> a; fin.ignore(1,' '); getline(fin,n);
	m.totalSpent += a;	//keep track of amount as you read entries
	Entry temp(d,c,n,a);
	m.entries.push_back(temp);
	check = fin.peek();
    }
    fin.close();
    return 0;
}

void print_entries(const Month& m){
    if (m.entries.size() == 0){
	cout << "No entries!" << endl << endl;
    }
    for (unsigned i=0; i < m.entries.size(); ++i){
	Entry e = m.entries.at(i);
	cout << setw(8) << e.date;
	cout << setw(15) << e.category;
	cout << setw(15) << e.note;
	cout << setw(10) << e.amount << endl;
    }
}

void print_cats(const map<string,double>& c){
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
    fin.close();
    return 0;
}

void add_entry(Month& m, map<string,double>& c){
    string date, category, note; double amount = 0.0;
    cout << "Date: "; cin >> date;
    cout << "Category: "; cin >> category;
    cout << "Note: "; cin.ignore(256,'\n'); getline(cin,note);
    cout << "Amount: "; cin >> amount;
    m.entries.push_back(Entry(date,category,note,amount));
    m.totalSpent += amount;
    if (c.count(category) == 0) 
        c[category] = amount;
    else
	c[category] += amount;
    cout << "Entry added successfully!" << endl << endl;
}

void get_total(const Month& m, map<string,double>& c){
    cout << "Category to look up (type \"all\" for total spending): ";
    string cat; cin >> cat;
    if (cat == "all") {
	cout << "Total monthly spending: $" << m.totalSpent << endl << endl;
    }
    else {
	cout << "Total " << cat << " spending: $" << c[cat] << endl << endl;
    }
}

void save_data(string month, const Month& m, const map<string,double>& c){
    cout << "Saving Data... " << endl;
    string file = month + ".txt";
    ofstream fout(file.c_str(), ios::out | ios::trunc);
    if (!fout.is_open()){
        cout << "Error saving data" << endl;
	return;
    }
    for (auto it : m.entries){
	fout << it.date << " " << it.category << " " << it.amount << " "
	    << it.note << endl;
    }
    fout.close();
    file = month + "cat.txt";
    ofstream fout2(file.c_str(), ios::out | ios::trunc);
    if (!fout2.is_open()){
	cout << "Error saving data (2)" << endl;
	return;
    }
    for (auto itr : c){
	fout2 << itr.first << " " << itr.second << endl;
    }
    fout2.close();
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

    	int menuChoice = 0;
	do {
    	    cout << "What would you like to do?" << endl;
    	    cout << "\t1. List Entries" << endl;
    	    cout << "\t2. Add Entry" << endl;
    	    cout << "\t3. Get Spending Total" << endl;
	    cout << "\t4. Choose Another Month" << endl;
    	    cout << "\t5. Quit" << endl << endl;

    	    cout << ">" ; cin >> menuChoice;
            if (menuChoice < 1 || menuChoice > 5){
                cout << "Invalid Option! Please Make Another Choice." << endl;
	        continue;
	    }

	    switch (menuChoice) {
                case 1:  print_entries(m); break;
	        case 2:  add_entry(m,cats); break;
	        case 3:  get_total(m,cats); break;
	        case 4:  break;
		case 5:  save_data(monthChoice,m,cats); return 0;
	    }
	} while (menuChoice != 4);
    }

    return 0;
}
