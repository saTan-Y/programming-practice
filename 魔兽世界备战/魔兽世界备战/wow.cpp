#include <iostream>
#include <cstdio>
#include <string>
using namespace std;
const int WARRIOR_NUM = 5;

/*ºì·½Ë³Ðò£ºiceman lion wolf ninja dragon
À¶·½Ë³Ðò£º lion dragon ninja iceman wolf*/

class Hq;
class Warrior {
private:
	Hq *pHq;
	int TypeNo;
	int No;
public:
	static string Warrior_Type_Lists[WARRIOR_NUM];
	static int initialLifeValue[WARRIOR_NUM];
	Warrior(Hq *p, int No_, int TypeNo_);
	void PrintResult(int time);
};
class Hq {
private:
	int TotalLifeValue;
	bool stopped;
	int TotalWarriroNum;
	int color;
	int CurMakingSeqIdx;
	int warriorNum[WARRIOR_NUM];
	Warrior *pWarrior[1000];
public:
	friend class Warrior;
	static int makingSeq[2][WARRIOR_NUM];
	void Init(int color_, int lv);
	~Hq();
	int Produce(int nTime);
	string getColor();

};

Warrior::Warrior(Hq *p, int no_, int kindno_) {
	No = no_;
	TypeNo = kindno_;
	pHq = p;
}

void Warrior::PrintResult(int nTime) {
	string color = pHq->getColor();
	//004 blue lion 5 born with strength 5,2 lion in red headquarter
	cout << nTime << " " << color << " " << Warrior_Type_Lists[TypeNo] << " " << No << " born with strength " << initialLifeValue[TypeNo] << "," 
		<< " " << pHq->warriorNum[TypeNo] << " "
		<< Warrior_Type_Lists[TypeNo] << " in " << color << " headquarter" << endl;
}

void Hq::Init(int color_, int lv) {
	color = color_;
	TotalLifeValue = lv;
	TotalWarriroNum = 0;
	stopped = false;
	CurMakingSeqIdx = 0;
	for (int i = 0; i < WARRIOR_NUM; i++) {
		warriorNum[i] = 0;
	}
}

Hq::~Hq() {
	for (int i = 0; i < TotalWarriroNum; i++) {
		delete pWarrior[i];
	}
}

int Hq::Produce(int nTime) {
	if (stopped)
		return 0;
	int searchingTime = 0;
	while (Warrior::initialLifeValue[makingSeq[color][CurMakingSeqIdx]] > TotalLifeValue
		&& searchingTime < WARRIOR_NUM) {
		CurMakingSeqIdx = (CurMakingSeqIdx + 1) % WARRIOR_NUM;
		searchingTime++;
	}
	int kindno = makingSeq[color][CurMakingSeqIdx];
	if (Warrior::initialLifeValue[kindno] > TotalLifeValue) {
		stopped = true;// 010 red headquarter stops making warriors
		if (color == 0)
			cout << nTime << "red headquarter stops making warriors" << endl;
		else
			cout << nTime << "blue headquarter stops making warriors" << endl;
		return 0;
	}
	//making warriors
	TotalLifeValue -= Warrior::initialLifeValue[kindno];
	CurMakingSeqIdx = (1 + CurMakingSeqIdx) % WARRIOR_NUM;
	pWarrior[TotalWarriroNum] = new Warrior(this, TotalWarriroNum + 1, kindno);
	warriorNum[kindno]++;
	pWarrior[TotalWarriroNum]->PrintResult(nTime);
	TotalWarriroNum += 1;
	return 1;
}

string Hq::getColor() {
	if (color == 0)
		return "red";
	else
		return "blue";
}

string Warrior::Warrior_Type_Lists[WARRIOR_NUM]{
	"dragon", "ninja", "iceman", "lion", "wolf"
};

int Warrior::initialLifeValue[WARRIOR_NUM];
int Hq::makingSeq[2][WARRIOR_NUM] = { {2,3,4,1,0}, {3,0,1,2,4} };

int main() {
	int t;
	int m;
	Hq Redhead, Bluehead;
	cin >> t;
	int nCaseno = 1;
	while (t--) {
		cin >> m;
		for (int i = 0; i < WARRIOR_NUM; i++) {
			cin >> Warrior::initialLifeValue[i];
		}
		cout << "Case" << nCaseno++ << endl;
		Redhead.Init(0, m);
		Bluehead.Init(1, m);
		int nTime = 0;
		while (true) {
			int temp1 = Redhead.Produce(nTime);
			int temp2 = Bluehead.Produce(nTime);
			if (temp1 == 0 && temp2 == 0) {
				break;
			}
			nTime++;
		}
	}
	return 0;
}
