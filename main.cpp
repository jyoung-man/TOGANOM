#include <iostream>
#include<fstream>
#include<string>
#include<vector>
#include "premier_league.h"
#define TEAMNUMBER 10
using namespace std;
vector<team> presetting() {
	vector<team> data;
	string teamnumber = to_string(0);
	for (int i = 1; i <= TEAMNUMBER; i++) {
		team temp;
		teamnumber = to_string(i) + ".txt";
		ifstream now(teamnumber);
		string message;
		getline(now, message);
		temp.setName(message);
		for (int j = 0; j < 8; j++) {
			string tempvalue;
			getline(now, tempvalue);
			temp.addstat(tempvalue);
		}
		data.push_back(temp);
	}
	return data;
}
void showteams() {
	cout << "--------------------------------" << endl;
	cout << "팀 목록은 다음과 같습니다" << endl;
	cout << "--------------------------------" << endl;
	vector<string> teams;
	ifstream ifs("teams.txt");
	string teamname;
	int count = 1; 
	while(getline(ifs, teamname)) {
		cout << count++<<" : "<<teamname << endl;
	}
	cout << "--------------------------------" << endl;
}
int main()
{
	vector<match> predict; //match 결과 저장
	vector<team> data = presetting();
	cout << "예측하고자 하는 게임 수를 입력하세요 : ";
	int c;
	cin >> c;
	for (int i = 0; i < c; i++) {
		int home = 0;
		int away = 0;
		string homename;
		string awayname;
		showteams();
		while (home == 0) {
			cout << "홈 팀을 입력해주세요 : ";
			cin >> home;
			if (home >= 1 && home <= TEAMNUMBER) {
				home--;
				cout << data[home].getName() <<" 을 선택하셨습니다"<< endl;
			}
			else {
				cout << "잘못 입력하셨습니다" << endl;
				home = 0;
			}
		}
		homename = data[home].getName();
		while (away == 0) {
			cout << "원정 팀을 입력해주세요 : ";
			cin >> away;
			if (away >= 1 && away <= TEAMNUMBER) {
				away--;
				cout << data[away].getName() << " 을 선택하셨습니다" << endl;
			}
			else {
				cout << "잘못 입력하셨습니다" << endl;
				away = 0;
			}
		}
		awayname = data[away].getName();
		cout << homename << " 과(와) " << awayname << " 의 경기를 진행합니다" << endl;
		match temp(data[home], data[away]);
		temp.setResults(temp.algorithm1());
		predict.push_back(temp);
		//결과 저장
		cout << "결과가 저장되었습니다!" << endl;
	}
	//결과를 모아서 확인하기
	for (int i = 0; i < c; i++) {
		predict[i].showResults();
	}
	//match1.team_select(1, 2);

}
