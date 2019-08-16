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
	cout << "�� ����� ������ �����ϴ�" << endl;
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
	vector<match> predict; //match ��� ����
	vector<team> data = presetting();
	cout << "�����ϰ��� �ϴ� ���� ���� �Է��ϼ��� : ";
	int c;
	cin >> c;
	for (int i = 0; i < c; i++) {
		int home = 0;
		int away = 0;
		string homename;
		string awayname;
		showteams();
		while (home == 0) {
			cout << "Ȩ ���� �Է����ּ��� : ";
			cin >> home;
			if (home >= 1 && home <= TEAMNUMBER) {
				home--;
				cout << data[home].getName() <<" �� �����ϼ̽��ϴ�"<< endl;
			}
			else {
				cout << "�߸� �Է��ϼ̽��ϴ�" << endl;
				home = 0;
			}
		}
		homename = data[home].getName();
		while (away == 0) {
			cout << "���� ���� �Է����ּ��� : ";
			cin >> away;
			if (away >= 1 && away <= TEAMNUMBER) {
				away--;
				cout << data[away].getName() << " �� �����ϼ̽��ϴ�" << endl;
			}
			else {
				cout << "�߸� �Է��ϼ̽��ϴ�" << endl;
				away = 0;
			}
		}
		awayname = data[away].getName();
		cout << homename << " ��(��) " << awayname << " �� ��⸦ �����մϴ�" << endl;
		match temp(data[home], data[away]);
		temp.setResults(temp.algorithm1());
		predict.push_back(temp);
		//��� ����
		cout << "����� ����Ǿ����ϴ�!" << endl;
	}
	//����� ��Ƽ� Ȯ���ϱ�
	for (int i = 0; i < c; i++) {
		predict[i].showResults();
	}
	//match1.team_select(1, 2);

}
