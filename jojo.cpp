#pragma warning(disable:4996)
#include <iostream>
using namespace std;
const char star_platinum[4][BUFSIZ] = { "ora barrage\n∞ deals 3.5 dmg for each 2 sp","star finger\n∞ deals 7.5 dmg for 4 sp","ora uppercut\n∞ deals 12.5 dmg for 6 sp","time stop\n∞ skips opponent's turn for 10 sp (locked)" };//Ï‡ÒË‚ Á Ì‡Á‚‡ÏË ‡·≥ÎÓÍ ÒÔ
const int star_platinum_[4] = { 2,4,6,10 };
struct STAND
{
	char sname[BUFSIZ]{ "\0" };
	int cost[4];
	char abilities[4][BUFSIZ]{ "\0" };
	void standchoice(const char*);
	void abilitymenu(const char*);
};
struct PLAYER
{
	char name[BUFSIZ]{ "\0" };
	double hp = 100;
	int sp = 0;
	int resolve = 0;
	STAND stand;
	void stats(const char*);
	int abilitychoice(bool);
};
void orabarrage(PLAYER&, PLAYER&, bool);
void starfinger(PLAYER&);
void orauppercut(PLAYER&);
void timestop(PLAYER&, PLAYER&, bool&);
int inp_num();
int main()
{
	cout << "\tJOJO's BIZZARE ADVENTURE\n     jrpg console game by shyshk4" << endl;
	system("pause");
	bool ts = false;
	PLAYER p1, p2;
	double p1combo, p2combo;
	p1combo = p2combo = 100;
	do
	{
		cout << "p1 write your name:";
		cin.getline(p1.name, BUFSIZ);
	} while (strcmp(p1.name, "\0") == 0);
	do
	{
		cout << "p2 write your name:";
		cin.getline(p2.name, BUFSIZ);
	} while (strcmp(p2.name, "\0") == 0);
	system("CLS");
	cout << "Stand list:\n1.star platinum;\n2.the world(WIP).\n" << endl;
	p1.stand.standchoice(p1.name);
	p2.stand.standchoice(p2.name);
	while (p1.hp > 0 && p2.hp > 0)
	{
		system("CLS");
		if (p1.resolve == 100)
		{
			strcpy(p1.stand.abilities[3], "time stop\n∞ skips opponent's turn for 10 sp");
		}
		p2.stats(p2.name);
		cout << endl;
		p1.stats(p1.name);
		p1.stand.abilitymenu(p1.name);
		switch (p1.abilitychoice(ts))
		{
		case 0:
			if (p1.sp < 10)
			{
				p1.sp++;
			}
			break;
		case 1:
			orabarrage(p1, p2, ts);
			p1.sp -= p1.stand.cost[0];
			break;
		case 2:
			starfinger(p2);
			p1.sp -= p1.stand.cost[1];
			break;
		case 3:
			orauppercut(p2);
			p1.sp -= p1.stand.cost[2];
			break;
		case 4:
			timestop(p1, p2, ts);
			p1.sp -= p1.stand.cost[3];
			break;
		default:
			break;
		}
		if (p1.resolve < 100)
		{
			p1combo = abs(p1combo - p2.hp);
			p1.resolve += (int)p1combo;
			p1combo = p2.hp;
		}
		if (p1.resolve > 100)
		{
			p1.resolve = 100;
		}
		if (p1.hp <= 0 || p2.hp <= 0)
		{
			break;
		}
		system("CLS");
		if (p2.resolve == 100)
		{
			strcpy(p2.stand.abilities[3], "time stop\n∞ skips opponent's turn for 10 sp");
		}
		p1.stats(p1.name);
		cout << endl;
		p2.stats(p2.name);
		p2.stand.abilitymenu(p2.name);
		switch (p2.abilitychoice(ts))
		{
		case 0:
			if (p2.sp < 10)
			{
				p2.sp++;
			}
			break;
		case 1:
			orabarrage(p2, p1, ts);
			p2.sp -= p2.stand.cost[0];
			break;
		case 2:
			starfinger(p1);
			p2.sp -= p2.stand.cost[1];
			break;
		case 3:
			orauppercut(p1);
			p2.sp -= p2.stand.cost[2];
			break;
		case 4:
			timestop(p2, p1, ts);
			p2.sp -= p2.stand.cost[3];
			break;
		default:
			break;
		}
		if (p2.resolve < 100)
		{
			p2combo = abs(p2combo - p1.hp);
			p2.resolve += (int)p2combo;
			p2combo = p1.hp;
		}
		if (p2.resolve > 100)
		{
			p2.resolve = 100;
		}
		if (p1.sp < 10)
		{
			p1.sp++;
		}
		if (p1.resolve < 100)
		{
			p1.resolve++;
		}
		if (p2.sp < 10)
		{
			p2.sp++;
		}
		if (p2.resolve < 100)
		{
			p2.resolve++;
		}
	}
	system("CLS");
	if (p1.hp > 0)
	{
		cout << p1.name << " win" << endl;
	}
	else if (p2.hp > 0)
	{
		cout << p2.name << " win" << endl;
	}
	system("pause");
	return 0;
}

void PLAYER::stats(const char* msg)
{
	cout << msg << "'s stats:" << endl;
	cout << "health:";
	cout << hp << endl;
	cout << "stamina:";
	cout << sp << endl;
	cout << "resolve:";
	cout << resolve << endl;
}

int PLAYER::abilitychoice(bool ts)
{
	cout << endl;
	int choice;
	cout << name << "'s turn:";
	choice = inp_num();
	switch (choice)
	{
	case 0:
		return choice;
	case 1:
		if (sp >= stand.cost[0])
		{
			return choice;
		}
		else
			return abilitychoice(ts);
	case 2:
		if (sp >= stand.cost[1])
		{
			return choice;
		}
		else
			return abilitychoice(ts);
	case 3:
		if (sp >= stand.cost[2])
		{
			return choice;
		}
		else
			return abilitychoice(ts);
	case 4:
		if (sp >= stand.cost[3] && !ts && resolve == 100)
		{
			return choice;
		}
		else
			return abilitychoice(ts);
	default:
		return abilitychoice(ts);
	}
}

void orabarrage(PLAYER& p1, PLAYER& p2, bool ts)
{
	if (p1.sp > 2)
	{
		p2.hp -= 3.5 * p1.sp/2;
		if (!ts)
			p1.sp = 2;
	}
	else
	{
		p2.hp -= 1.5;
	}
}

void starfinger(PLAYER& p2)
{
	p2.hp -= 7.5;
}

void orauppercut(PLAYER& p2)
{
	p2.hp -= 12.5;
}

void timestop(PLAYER& p1, PLAYER& p2, bool& ts)
{
	ts = true;
	cout << "\nStar Platinum Za Warudo!\n*Flow of the time has been stopped*" << endl;
	switch (p1.abilitychoice(ts))
	{
	case 0:
		if (p1.sp < 10)
		{
			p1.sp++;
		}
		break;
	case 1:
		orabarrage(p1, p2, ts);
		break;
	case 2:
		starfinger(p2);
		break;
	case 3:
		orauppercut(p2);
		break;
	default:
		break;
	}
	switch (p1.abilitychoice(ts))
	{
	case 0:
		if (p1.sp < 10)
		{
			p1.sp++;
		}
		break;
	case 1:
		orabarrage(p1, p2, ts);
		break;
	case 2:
		starfinger(p2);
		break;
	case 3:
		orauppercut(p2);
		break;
	default:
		break;
	}
	ts = false;
}

void STAND::standchoice(const char* msg)
{
	int choice;
	cout << msg << " choose your stand:";
	choice = inp_num();
	switch (choice)
	{
	case 1:
		strcpy(sname, "star platinum");
		for (int i = 0; i < 4; i++)
			cost[i] = star_platinum_[i];
		for (int i = 0; i < 4; i++)
			strcpy(abilities[i], star_platinum[i]);
		break;
	default:
		return standchoice(msg);
	}
}

void STAND::abilitymenu(const char* msg)
{
	cout << endl;
	cout << msg << " stand's abilities:" << endl;
	cout << "0.pose\n∞ regens +1 sp" << endl;
	for (int i = 0; i < 4; i++)
		cout << i + 1 << "." << abilities[i] << endl;
}
int inp_num()
{
	char num[10];
	fgets(num, 10, stdin);
	return atoi(num);
}