#pragma once
#include<string>
#include<vector>
using namespace std;
struct homeVSaway {
	int homeScore;
	int awayScore;
	double propability;
	homeVSaway(int h, int a, double p) {
		homeScore = h;
		awayScore = a;
		propability = p;
	}
	bool operator < (const homeVSaway & a) {
		return propability > a.propability; //���� ���� ����
	}
};
class team
{
private:
	string name; //�� �̸�
	vector<double> stat; //���� 0~7������ ���� Ȩ-���Ĺ�-����, �����-���Ĺ�-����
public:
	void setName(string s) {
		name = s;
	}
	void addstat(string s){
		double value = stof(s);
		stat.push_back(value);
	}
	string getName() {
		return name;
	}
	vector<double> getStat() {
		return stat;
	}
};
class match 
{
private:
	team home;
	team away;
	vector<homeVSaway> results; // (Ȩ : ����) �� Ȯ���� �����ϴ� �迭
public:
	bool comparePropability(const homeVSaway &x, const homeVSaway& y) {
		return x.propability > y.propability;
	}
	void showResults() {
		cout << home.getName() << " ��(��) " << away.getName() << " �� ����� ������ �����ϴ�" << endl;
		cout << "------------------------------------------------------------" << endl;
		for (int i = 0; i < results.size(); i++) {
			cout << "(" << results[i].homeScore << " : " << results[i].awayScore << ")";
			cout << " : " << results[i].propability << endl;
		}
	}
	void setHome(team T) {
		home = T;
	}
	void setAway(team T) {
		away = T;
	}
	void setResults(vector<homeVSaway> a) {
		results = a;
	}
	team getHome() {
		return home;
	}
	team getAway() {
		return away;
	}
	match(team home, team away);
	vector<homeVSaway> algorithm1();
	
};