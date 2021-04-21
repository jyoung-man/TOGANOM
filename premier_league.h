#pragma once
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
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
struct teamScore {
	string team;
	int score;
	void scoreGoal() {
		score = score + 1;
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
		cout << "\n다음은 푸아송 분포로 예측한 " << home.getName() << " 와 " << away.getName() << " 의 경기 결과입니다." << endl;
		cout << "--------------------------------------------------------------------------------" << endl;
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
	int time_tick(int target) {
		srand((unsigned int)time(NULL));
		target += 2;
		int num;
		int ran1 = rand();
		int ran2 = rand();
		num = (ran1 % 15) + (ran2%10) + target;

		return num;
	}
	int tikitaka(teamScore team, vector<double> stats, int pass, int t) //홈팀 스탯과 원정팀 수비력을 인자로 받아야 할 듯
	{
		/*
		if (pass >= 5) {
			_sleep(5000);
			if (t%45 < 15)
				announcer(5, t, team);
			else
				announcer(6, t, team);
		}
		*/
		
		if (pass >= 8) //패스 성공 횟수가 8회 이상이면 슛.
		{
			_sleep(3000);
			announcer(2, t + 1, team);
			int isGoal = shoot((int)stats[4], (int)stats[7]);
			pass = 0; //골키퍼가 막든, 슛이 빗겨가든, 골을 먹히든 슛 이후의 경기는 전열 정비 후 진행되기 때문
			
			if (isGoal == 0) //유효슈팅으로 연결되었으나 골키퍼 맞고 골라인 아웃된 상황. 코너킥
			{
				_sleep(3000);
				announcer(4, t + 1, team);
				_sleep(3000);
				announcer(7, t + 1, team);
				team.score = corner_kick(t+1, team);
			}
			else if (isGoal == 2)//득점 상황 
			{
				_sleep(3000);
				announcer(8, t + 1, team);//골이라는 멘트	
				team.scoreGoal();
			}
			else //슈팅이 골대 밖으로 나간 상황. 
			{
				_sleep(3000);
				announcer(3, t + 1, team);//노골이라는 멘트
			}
		}
		return team.score;
	}
	int shootacc()
	{
		int gaebal;
		srand((unsigned int)time(NULL));
		gaebal = rand() % 20;

		return gaebal;
	}
	int shoot(int att, int dfc)
	{

		int t = shootacc();
		dfc -= 50;
		int shootacc[20] = { 0, };
		for (int index = 0; index <= (att - att % 5 - dfc) / 5; index++)
		{
			shootacc[index] = 1;
		}


		if (shootacc[t] == 0) {
			if (t % 2 == 0) {
				//유효슈팅으로 연결되었으나 골키퍼 맞고 골라인 아웃된 상황 가정. 코너킥
				return 0;
			}
			else if (t % 2 == 1)
				return 1;
			//슈팅이 골대 밖으로 나간 상황 가정. 노골이라는 멘트
		}
		else if (shootacc[t] == 1) {
			//슈팅이 골로 연결된 상황 가정

			return 2;
		}
	}
	int pass_play(vector<double> stats, int pass) {
		if (stats[5] + stats[8] - pass >= 70) {
			pass++;
			pass = pass_play(stats, pass);
		}
		else {
			pass -= pass%4;
			//int cut = rand()
			//announcer()
		}
		return pass;
	}
	int corner_kick(int t, teamScore team)
	{
	//코너킥의 실제 득점 성공률은 3.5%이나, 게임이므로 10%이상으로 설정한다.
		srand((unsigned int)time(NULL));
		int result = rand();
		result = result % 5;
		_sleep(3000);
		switch (result)
		{
		case 3:
			announcer(8, t + 1, team);//골이라는 멘트	
			team.scoreGoal();
			break;
		default:
			announcer(9, t + 1, team);//노골이라는 멘트	
			break;
		}
		return team.score;
	}
	int addTime(int tick) {
		srand((unsigned int)time(NULL));
		int losstime = rand();
		losstime = losstime % 5 + 1;
		int t = tick % 45;
		if (t > losstime && t < 10)
			return tick % 45;
		else
			return losstime;
	}
	void announcer(int num, int matchtime, teamScore team)
	{
		switch (num) {
		case 1: cout << "\n'0: " << "경기 시작되었습니다." << endl; break;
		case 2: cout << "'" << matchtime <<": "<< team.team << "의 결정적 찬스!" << endl; break;
		case 3: cout << "'" << matchtime << ": " << "빗나간 슛으로 기회를 놓칩니다." << endl; break;
		case 4: cout << "'" << matchtime << ": " << "슛을 시도하지만 골키퍼에 막힙니다." << endl; break;
		case 5: cout << "'" << matchtime << ": " << "공수 전환되었습니다."<<team.team<<" 의 공격" << endl; break;
		case 6: cout << "'" << matchtime << ": " << team.team << "의 역습 찬스입니다!" << endl; break;
		case 7: cout << "'" << matchtime << ": " << "주심 코너킥을 선언합니다." << endl; break;
		case 8: cout << "'" << matchtime << ": " << "골! "<<team.team<<" 팀의 득점입니다." << endl; break;
		case 9: cout << "'" << matchtime << ": " << "코너킥, 수비수에 막힙니다." << endl; break;
		case 10: cout << "'45: 전반전 추가시간은 " << matchtime << "분입니다. " << endl; break;
		case 12: cout << "'" << "45+" << matchtime - 45 << ": " << "전반전 종료됩니다." << endl; break;
		case 13: cout << "'" << "45: " << "후반전 시작되었습니다." << endl; break;
		case 14: cout << "'" << matchtime << ": " << "패스, 수비수에 막힙니다." << endl; break;
		case 15: cout << "'" << matchtime << ": " << "공이 선수에게 연결되지 않았습니다." << endl; break;
		case 16: cout << "'" << matchtime << ": " << "패스미스가 나왔습니다." << endl; break;
		case 19: cout << "'90: 추가시간 " << matchtime << "분이 주어집니다. " << endl; break;
		case 20: cout << "'" << "90+" << matchtime - 90 <<": " << "주심, 종료휘슬을 불었습니다. " << endl; break;
		}
	}
	match(team home, team away);
	vector<homeVSaway> algorithm1();
	vector<homeVSaway> algorithm2();
	
};
