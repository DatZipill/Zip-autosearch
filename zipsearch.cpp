#include <windows.h>
#include <shellapi.h>
#include <string>
#include <iostream>
#include <stdlib.h> 
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

int mark[1000] = {0};

string word() {
	string line;
	vector<string> allWords;
	ifstream file("keywords.txt");
	if (!file.is_open()) {
		cout << "Khong the mo file" << endl;
		return "";
	}
	while (getline(file, line)) {
		if (!line.empty()) {
			stringstream ss(line);
			string word;
			while (ss >> word) {
				allWords.push_back(word);
			}
		}
	}
	file.close();
	if (allWords.empty()) {
		cout << "File khong co tu khoa nao" << endl;
		return "";
	}
	srand(time(0));
	int sum = allWords.size();
	int rd = rand() % sum;
	while (mark[rd]) {
		rd = rand() % sum;
	}
	mark[rd] = 1;
	return allWords[rd];
}

string urlGen() {
	string urlBase = "https://www.bing.com/search?q=";
	string keyword = word();
	for (char &c : keyword) {
        if (c == ' ') {
            c = '+';
        }
    }
    return urlBase + keyword + "&form=EDGTCT&PC=U316";;
}

void search() {
	string url = urlGen();
	HINSTANCE result = ShellExecuteA(
		NULL,
		"open",
		url.c_str(),
		NULL, 
		NULL,
		SW_MINIMIZE
	);
	INT_PTR checkResult = reinterpret_cast<INT_PTR>(result);
	if ((int)checkResult <= 32) {
		cout << "Search that bai" << endl;
	} else {
		cout << "Da tim kiem thanh cong" << endl;
	}
}

int main() {
	int n;
	cout << "Ban muon tim kiem bao nhieu lan: ";
	cin >> n;
	for (int i = 0; i < n; i++) {
		search();
		int rd = (rand() % 11) * 1000;
		Sleep(rd);
	}
}
