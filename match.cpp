#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "premier_league.h"
using namespace std;
vector<homeVSaway> match::algorithm1() {
	vector<homeVSaway> ret;
	double ho_att, aw_dfc, aw_att, ho_dfc;
	int homeCount = 0;//홈 팀의 득점(원정 팀의 실점)
	int awayCount = 0;//원정 팀의 득점(홈 팀의 실점)
	double Tt1;
	double XX1;
	double e = exp(1);
	double q1,p1,p2;
	for (awayCount = 0; awayCount < 4; awayCount++) {
		for (homeCount = 0; homeCount < 4; homeCount++) { //xk : yk  -> 홈 : 어웨이에 대한 확률 계산
			//전반전 계산
			ho_att = home.getStat().at(0); ho_dfc = home.getStat().at(1);
			aw_att = away.getStat().at(2); aw_dfc = away.getStat().at(3);
			double lamda1 = ho_att * aw_dfc;//홈 득점률 * 원정 실점률. 참고 논문에선 홈 보정도 포함되었음. 홈 보정은 필요시에 추가 예정.
			double mu1 = ho_dfc * aw_att;
			double p;
			p1 = max(-1 / lamda1, -1 / mu1);
			p2 = min(1/(lamda1 * mu1), 1.00);
			if (p2<1&&p2>p1)
				p = p1;
			else
				p = p2;
			if (homeCount == 0 && awayCount == 0) {
				Tt1 = 1 - lamda1 * mu1*p;
			}
			else if (homeCount == 0 && awayCount == 1) {
				Tt1 = (1 + lamda1 * p);
			}
			else if (homeCount == 1 && awayCount == 0) {
				Tt1 = 1 + mu1 * p;
			}
			else if (homeCount == 1 && awayCount == 1) {
				Tt1 = 1 - p;
			}
			else {
				Tt1 = 1;
			}
			XX1 = Tt1 * pow(e, lamda1)*pow(lamda1, homeCount)*exp(-mu1)*pow(mu1, awayCount);
			q1 = pow(e, (0.0065 * 45 - 0.0065 * 90));
			double value  = pow(XX1, q1);
			homeVSaway res(homeCount, awayCount, value);
			ret.push_back(res);
		}
	}
	sort(ret.begin(), ret.end());
	return ret;
}
vector<homeVSaway> match::algorithm2() {
	vector<homeVSaway> ret;
	int pass, advantage1, advantage2, tick;	
	pass = advantage1 = advantage2 = 0;//패스 연결 횟수, 능력치 보정을 위한 변수
	tick = 0; //시간 표시를 위한 변수
	vector <double> homeStats = home.getStat();
	vector <double> awayStats = away.getStat();
	homeStats.push_back(away.getStat().at(6)); //홈팀 스탯 벡터에 원정팀의 수비력도 포함시켰음
	awayStats.push_back(home.getStat().at(6)); //원정팀 스탯 벡터에 홈팀의 수비력도 포함시켰음
	homeStats.push_back(advantage1);//보정치
	awayStats.push_back(advantage2);
	teamScore hometeam = { home.getName(), 0 };
	teamScore awayteam = { away.getName(), 0 };
	_sleep(3000);
	announcer(1, 0, hometeam);
	tick = time_tick(0);
	while (tick < 30) {//45분 - 랜덤 시간 15분
		pass = pass_play(homeStats, pass);
		hometeam.score = tikitaka(hometeam, homeStats, pass, tick);
		//announcer(5, tick, awayteam);
		tick = time_tick(tick);//공격 전개 도중에 경기를 끝내진 않으므로, 찬스가 끝나고 나서 시간 갱신
		pass = pass_play(awayStats, pass);
		awayteam.score = tikitaka(awayteam, awayStats, pass, tick);
		//announcer(5, tick, hometeam);
		tick = time_tick(tick);
	}
	_sleep(5000);
	int addtime = addTime(tick);
	announcer(10, addtime, hometeam);
	_sleep(3000);
	announcer(12, 45 + addtime, hometeam);
	_sleep(5000);
	pass = 0;//패스 연결 횟수 초기화
	tick = 45;//전반전 종료, 시간 초기화
	announcer(13, 45, hometeam);
	tick = time_tick(45);
	while (tick < 75) { //90분 - 랜덤 시간 15분
		pass = pass_play(awayStats, pass);
		awayteam.score = tikitaka(awayteam, awayStats, pass, tick);
		//announcer(5, tick, hometeam);
		tick = time_tick(tick);
		pass = pass_play(homeStats, pass);
		hometeam.score = tikitaka(hometeam, homeStats, pass, tick);
		//announcer(5, tick, awayteam);
		tick = time_tick(tick);
	}
	_sleep(5000);
	addtime = addTime(tick);
	announcer(19, addtime, hometeam);
	_sleep(3000);
	announcer(20, 90+addtime, hometeam);
	cout << "최종스코어 "<< hometeam.team << " " << hometeam.score << " - " << awayteam.score << " " << awayteam.team << endl;
	_sleep(5000);
	return ret;
}

match::match(team home, team away) {
	//생성과 동시에 팀 지정
	this->setHome(home);
	this->setAway(away);
}
