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
		return propability > a.propability; //내림 차순 정렬
	}
};
class team
{
private:
	string name; //팀 이름
	vector<double> stat; //스탯 0~7번지에 저장 홈-전후반-공방, 어웨이-전후반-공방
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
	vector<homeVSaway> results; // (홈 : 원정) 의 확률을 저장하는 배열
public:
	bool comparePropability(const homeVSaway &x, const homeVSaway& y) {
		return x.propability > y.propability;
	}
	void showResults() {
		cout << home.getName() << " 과(와) " << away.getName() << " 의 결과는 다음과 같습니다" << endl;
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