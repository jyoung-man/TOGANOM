#include <iostream>
#include<string>
#include<algorithm>
#include "premier_league.h"
using namespace std;
vector<homeVSaway> match::algorithm1() {
	vector<homeVSaway> ret;
	double ho_att, aw_dfc, aw_att, ho_dfc;
	double p = -0.88774;//정식 버전에서는 이 변수도 팀의 공격력 수비력을 인자로 받아 프로그램 자체에서 구할 것!
	int homeCount = 0;//홈 팀의 득점(원정 팀의 실점)
	int awayCount = 0;//원정 팀의 득점(홈 팀의 실점)
	double Tt1, Tt2;
	double XX1,XX2;
	double e = exp(1);
	double q1, q2;
	for (awayCount = 0; awayCount < 4; awayCount++) {
		for (homeCount = 0; homeCount < 4; homeCount++) { //xk : yk  -> 홈 : 어웨이에 대한 확률 계산
			//전반전 계산
			ho_att = home.getStat().at(0); ho_dfc = away.getStat().at(1);
			aw_att = away.getStat().at(4); aw_dfc = away.getStat().at(5);
			double lamda1 = ho_att * aw_dfc;//홈 득점률 * 원정 실점률. 참고 논문에선 홈 보정도 포함되었음. 홈 보정은 필요시에 추가 예정.
			double mu1 = ho_dfc * aw_att;
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
			double half1 = pow(XX1, q1);
			//후반전 계산
			ho_att = home.getStat().at(2); ho_dfc = home.getStat().at(3);
			aw_att = away.getStat().at(6); aw_dfc = away.getStat().at(7);
			double lamda2 = ho_att * aw_dfc;//홈 득점률 * 원정 실점률. 참고 논문에선 홈 보정도 포함되었음. 홈 보정은 필요시에 추가 예정.
			double mu2 = ho_dfc * aw_att;
			if (homeCount == 0 && awayCount == 0) {
				Tt2 = 1 - lamda2 * mu2*p;
			}
			else if (homeCount == 0 && awayCount == 1) {
				Tt2 = (1 + lamda2 * p);
			}
			else if (homeCount == 1 && awayCount == 0) {
				Tt2 = 1 + mu2 * p;
			}
			else if (homeCount == 1 && awayCount == 1) {
				Tt2 = 1 - p;
			}
			else {
				Tt2 = 1;
			}
			XX2 = Tt2 * pow(e, lamda2)*pow(lamda2, homeCount)*exp(-mu2)*pow(mu2, awayCount);
			q2 = pow(e, (0.0065 * 90 - 0.0065 * 90));
			double half2 = pow(XX2, q2);
		
			double value =half1+ half2;
			homeVSaway res(homeCount, awayCount, value);
			ret.push_back(res);
		}
	}
	sort(ret.begin(), ret.end());
	return ret;
}
match::match(team home, team away) {
	//생성과 동시에 팀 지정
	this->setHome(home);
	this->setAway(away);
}