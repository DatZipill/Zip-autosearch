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
vector<string> allWords;

string word() {
	if (allWords.empty()) {
		cout << "File khong co tu khoa nao" << endl;
		return "";
	}
	int sum = allWords.size();
	int rd = rand() % sum;
	while (mark[rd]) {
		rd++;
		if (rd == sum) rd = 0;
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
	srand(time(0));
	string line;
	ifstream file("keywords.txt");
	if (!file.is_open()) {
		cout << "Khong the mo file" << endl;
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
	int n;
	cout << "Ban muon tim kiem bao nhieu lan: ";
	cin >> n;
	for (int i = 0; i < n; i++) {
		search();
		int rd = (rand() % 6 + 5) * 1000;
		Sleep(rd);
	}
}
