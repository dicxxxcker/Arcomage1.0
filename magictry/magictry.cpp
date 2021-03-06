// magictry.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include <fstream>
#include <cstdlib>
#include <string.h>
#include <stdio.h>
#include <stack>
#include <locale>
#include <algorithm>
#include <time.h>



using namespace std;

int lucky = 11;                                                                                                                        //幸运数
class Player;
int f = 0;																																//回合标志
bool use(Player* , Player* , int);
int castle=50;                                                                          //城堡建多高获胜
int brick=50,monster=50,jewel=50;                                                       //资源累积多少获胜

class Player {                                                                          //玩家类
	string name = "computer";
	int cas = 25, wall = 10, bri = 10, mon = 10, jew = 10;
	int sbri = 2, smon = 2, sjew = 2;
public:
	int handcard[20] = { 0 };
	int judge();
	int getCas() { return cas; };                                                      //获取
	int getWall() { return wall; };
	int getBri() { return bri; };
	int getMon() { return mon; };
	int getJew() { return jew; };
	int getSbri() { return sbri; };
	int getSmon() { return smon; };
	int getSjew() { return sjew; };
	void chaCas(int n) { cas += n; };                                                  //改变
	void chaBri(int n) { bri += n; };
	void chaMon(int n) { mon += n; };
	void chaJew(int n) { jew += n; };
	void chaWall(int n) { wall += n; };
	void chaSbri(int n) { sbri += n; };
	void chaSmon(int n) { smon += n; };
	void chaSjew(int n) { sjew += n; };
	void defeat(int n){ for(;n>0;n--) {if(wall>0) wall--;else cas--; }};                 //受伤
	void getCard(int n);																//抽牌
	void changeCard(int n);
	void printname() { cout << name; }
	stack<int> cardstack;            //出牌栈
	void writename() { char s[30] = { 0 }; cin.clear(); cin.getline(s, 29); name = s; };
};

void printscreen(Player*, Player*);
void play(Player* p1, Player* p2, int n) {if (n) { if (use(p1, p2, p1->handcard[n - 1])) p1->getCard(p1->handcard[n-1]); }
											else { cout << "你选择弃第<数字>张牌。";    int t; cin >> t; p1->changeCard(p1->handcard[t-1]); }
};																																					//出牌

void Player::getCard(int n) {																													//抽牌
	srand(unsigned int(time(NULL)*17));
	  for (int i = 0,flag=1; flag&&handcard[i] != 0;i++) if (handcard[i] == n)  handcard[i] = rand() % 87 + 1,flag=0 ;  
	 };

void Player::changeCard(int n) {																												//换牌                                 
	srand(unsigned int(time(NULL)*11));
	if (n != 16) { for (int i = 0, flag = 1; flag&&handcard[i] != 0; i++) if (handcard[i] == n)  handcard[i] = rand() % 87 + 1, flag = 0; }
	else cout << "这张牌不能换，只能使用，行动失败！\n";
};


int Player::judge() {                                                                   //结算并判断胜负
	if (bri >= brick && mon >= monster && jew >= jewel || cas >= castle) return 1;
	if (cas <= 0) return -1;
	return 0;
}
	void fail(Player* player1, Player* player2) {                                                                      //出牌失败
		cout << "   资源不足，请重新选择要出的牌！你选择出（数字）\n";
		int n; cin >> n; play(player1, player2, n);
	}
	void again(Player* player1, Player* player2) {																	//再次出牌
		if(f) printscreen(player1, player2);
		else printscreen(player2, player1);
		player1->printname(); cout << "         请再次出牌，你选择出（数字）\n";
		int n; cin >> n; play(player1, player2, n);
	}

	bool check (Player* p,int n,int t) {                                                                                     //检查使用条件是否合格
		switch (n / 3) {
		case 0:  if (p->getBri() >= t) return 1; break;
		case 1:  if (p->getJew() >= t) return 1; break;
		case 2:  if (p->getMon() >= t) return 1; break;
		}
		return 0;
	}


	void acc(Player*, Player*);

	



	bool use(Player* player1, Player* player2, int n) {
		srand(rand());																																	//随机化种子
		switch (n%3) {																														//使用牌
		case 0: switch (n / 3) {
					case 1: player1->cardstack.push(n),player1->getCard(n), player1->chaBri(-8), player2->chaBri(-8); break;                                                       //砖头牌
					case 2: player1->cardstack.push(n),player1->getCard(n), player1->chaBri(2), player1->chaJew(2); again(player1, player2); break;           //?
					case 3: if (player1->getJew() >= 1) player1->cardstack.push(n),player1->getCard(n), player1->chaBri(-1), player1->chaWall(1), again(player1, player2);
				else fail(player1, player2);return false; break;
					case 4: if (player1->getBri() >= 3) player1->cardstack.push(n),player1->getCard(n), player1->chaBri(-3), player1->chaSbri(1);
				else fail(player1, player2);return false; break;
					case 5: if (player1->getBri() >= 4) { player1->cardstack.push(n),player1->getCard(n), player1->chaBri(-4); if (player1->getSbri() < player2->getSbri())player1->chaSbri(2); else player1->chaSbri(1); }
				else fail(player1, player2);return false; break;
					case 6: if (player1->getBri() >= 7) player1->cardstack.push(n),player1->getCard(n), player1->chaBri(-7), player1->chaWall(4), player1->chaSbri(1);
				else fail(player1, player2);return false; break;
					case 7: if (player1->getBri() >= 2) player1->cardstack.push(n),player1->getCard(n), player1->chaBri(-2), player1->chaWall(5), player1->chaJew(-6);
				else fail(player1, player2);return false; break;
					case 8: if (player1->getBri() >= 5) { player1->cardstack.push(n),player1->getCard(n), player1->chaBri(-5); if (player1->getBri() < player2->getBri()) player1->chaBri(player2->getBri() - player1->getBri()); break; }
				else fail(player1, player2);return false; break;
					case 9: if (player1->getBri() >= 2) player1->cardstack.push(n),player1->getCard(n), player1->chaBri(-2), player1->chaWall(3);
				else fail(player1, player2);return false; break;
					case 10:if (player1->getBri() >= 3) player1->cardstack.push(n),player1->getCard(n), player1->chaBri(-3), player1->chaWall(4);
				else fail(player1, player2);return false; break;
					case 11:if (player1->getBri() >= 2) player1->cardstack.push(n),player1->getCard(n), player1->chaBri(-2), player1->chaSbri(1), player2->chaSbri(1), player1->chaJew(4);
				else fail(player1, player2);return false; break;
					case 13:if (player1->getBri() >= 7) player1->cardstack.push(n),player1->getCard(n), player1->chaBri(-7), player1->chaWall(-5), player2->chaWall(-5), again(player1, player2);
				else fail(player1, player2);return false; break;
					case 12:if (player1->getBri() >= 3) { player1->cardstack.push(n),player1->getCard(n), player1->chaBri(-3); if (player1->getWall() == 0) player1->chaWall(6); else player1->chaWall(3); }
				else fail(player1, player2);return false; break;
					case 14:if (player1->getBri() >= 8) player1->cardstack.push(n),player1->getCard(n), player1->chaBri(-8), player1->chaSjew(1), again(player1, player2);
				else fail(player1, player2);return false; break;
					case 15: player1->cardstack.push(n),player1->getCard(n), player1->chaSbri(-1); player2->chaSbri(-1);
					case 16:if (player1->getBri() >= 5) player1->cardstack.push(n),player1->getCard(n), player1->chaBri(-5), player1->chaWall(5);
				else fail(player1, player2);return false; break;
					case 17:if (player1->getBri() >= 4) player1->cardstack.push(n),player1->getCard(n), player1->chaBri(-4), player2->chaSbri(-1);
				else fail(player1, player2);return false; break;
					case 18:if (player1->getBri() >= 6) player1->cardstack.push(n),player1->getCard(n), player1->chaBri(-6), player1->chaSbri(2);
				else fail(player1, player2);return false; break;
					case 19: player1->cardstack.push(n),player1->getCard(n), player1->chaSbri(-1); player1->chaWall(10); player1->chaJew(5);
					case 20:if (player1->getBri() >= 8) player1->cardstack.push(n),player1->getCard(n), player1->chaBri(-8), player1->chaWall(8);
				else fail(player1, player2);return false; break;
					case 21:if (player1->getBri() >= 9) player1->cardstack.push(n),player1->getCard(n), player1->chaBri(-9), player1->chaWall(5), player1->chaSmon(1);
				else fail(player1, player2);return false; break;
					case 22:if (player1->getBri() >= 9) player1->cardstack.push(n),player1->getCard(n), player1->chaBri(-9), player1->chaWall(7), player1->chaJew(7);
				else fail(player1, player2);return false; break;
					case 23:if (player1->getBri() >= 11) player1->cardstack.push(n),player1->getCard(n), player1->chaBri(-11), player1->chaWall(6), player1->chaCas(3);
				else fail(player1, player2);return false; break;
					case 24:if (player1->getBri() >= 13) player1->cardstack.push(n),player1->getCard(n), player1->chaBri(-13), player1->chaWall(12);
				else fail(player1, player2);return false; break;
					case 25:if (player1->getBri() >= 15) player1->cardstack.push(n),player1->getCard(n), player1->chaBri(-15), player1->chaWall(8), player1->chaCas(5);
				else fail(player1, player2);return false; break;
					case 26:if (player1->getBri() >= 16) player1->cardstack.push(n),player1->getCard(n), player1->chaBri(-16), player1->chaWall(15);
				else fail(player1, player2);return false; break;
					case 27:if (player1->getBri() >= 18) player1->cardstack.push(n),player1->getCard(n), player1->chaBri(-18), player1->chaWall(6), player2->chaWall(-10);
				else fail(player1, player2);return false; break;
					case 28:if (player1->getBri() >= 24) player1->cardstack.push(n),player1->getCard(n), player1->chaBri(-24), player1->chaWall(20), player1->chaCas(8);
				else fail(player1, player2);return false; break;
					case 29:if (player1->getBri() >= 7) player1->cardstack.push(n),player1->getCard(n), player1->chaBri(-7), player1->chaWall(9), player1->chaMon(-5);
				else fail(player1, player2);return false; break;
		}								break;																														//第一类牌结束
		case 1: switch (n / 3) {
		case 0:if (player1->getJew() >= 1) player1->cardstack.push(n),player1->getCard(n), player1->chaJew(-1), player1->chaCas(1), again(player1, player2);                  //宝石
				else fail(player1, player2);return false; break;
		case 1:if (player1->getJew() >= 2) player1->cardstack.push(n),player1->getCard(n), player1->chaJew(-2), player2->chaCas(-1), again(player1, player2);
				else fail(player1, player2);return false; break;
		case 2:if (player1->getJew() >= 2) player1->cardstack.push(n),player1->getCard(n), player1->chaJew(-2), player1->chaCas(3);
				else fail(player1, player2);return false; break;
		case 3:if (player1->getJew() >= 3) player1->cardstack.push(n),player1->getCard(n), player1->chaJew(-3), player1->chaSjew(1);
				else fail(player1, player2);return false; break;
		case 4:if (player1->getJew() >= 2) player1->cardstack.push(n),player1->getCard(n), player1->chaJew(-2), player1->getCard(n), again(player1, player2);
				else fail(player1, player2);return false; break;
		case 5:if (player1->getJew() >= 5) player1->cardstack.push(n),player1->getCard(n), player1->chaJew(-5), player1->chaCas(3);
				else fail(player1, player2);return false; break;
		case 6:if (player1->getJew() >= 4) player1->cardstack.push(n),player1->getCard(n), player1->chaJew(-4), player1->chaCas(2), player2->chaCas(-2);
				else fail(player1, player2);return false; break;
		case 7:if (player1->getJew() >= 6) player1->cardstack.push(n),player1->getCard(n), player1->chaJew(-6), player1->chaCas(3), player1->chaSjew(1), player2->chaCas(1);
				else fail(player1, player2);return false; break;
		case 8:if (player1->getJew() >= 2) player1->cardstack.push(n),player1->getCard(n), player1->chaJew(-2), player2->chaCas(-3);
				else fail(player1, player2);return false; break;
		case 9:if (player1->getJew() >= 3) player1->cardstack.push(n),player1->getCard(n), player1->chaJew(-3), player1->chaCas(5);
				else fail(player1, player2);return false; break;
		case 10:if (player1->getJew() >= 4) player1->cardstack.push(n),player1->getCard(n), player1->chaJew(-4), player2->chaCas(-5);
				else fail(player1, player2);return false; break;
		case 11:if (player1->getJew() >= 3) player1->cardstack.push(n),player1->getCard(n), player1->chaJew(-3), player1->chaCas(-5), player1->chaSjew(2);
				else fail(player1, player2);return false; break;
		case 12:if (player1->getJew() >= 7) player1->cardstack.push(n),player1->getCard(n), player1->chaJew(-7), player1->chaCas(3), player1->chaSjew(1), player1->chaWall(3);
				else fail(player1, player2);return false; break;
		case 13:if (player1->getJew() >= 7) {
			player1->cardstack.push(n),player1->getCard(n), player1->chaJew(-7);
			if (player1->getSjew() > player2->getSjew()) player2->chaSjew(player1->getSjew() - player2->getSjew());
			else player1->chaSjew(player2->getSjew() - player1->getSjew());
		}
				else fail(player1, player2);return false; break;
		case 14:if (player1->getJew() >= 6) player1->cardstack.push(n),player1->getCard(n), player1->chaJew(-6), player1->chaCas(8);
				else fail(player1, player2);return false; break;
		case 15:if (player1->getJew() >= 9) player1->cardstack.push(n),player1->getCard(n), player1->chaJew(-9), player1->chaCas(5), player1->chaSjew(1);
				else fail(player1, player2);return false; break;
		case 16:if (player1->getJew() >= 8) player1->cardstack.push(n),player1->getCard(n), player1->chaJew(-8), player1->chaSjew(-1), player2->chaCas(-9);
				else fail(player1, player2);return false; break;
		case 17:if (player1->getJew() >= 7) player1->cardstack.push(n),player1->getCard(n), player1->chaJew(-7), player1->chaCas(5), player2->chaBri(-6);
				else fail(player1, player2);return false; break;
		case 18:if (player1->getJew() >= 10) player1->cardstack.push(n),player1->getCard(n), player1->chaJew(-10), player1->chaCas(11);
				else fail(player1, player2);return false; break;
		case 19:if (player1->getJew() >= 5) player1->cardstack.push(n),player1->getCard(n), player1->chaJew(-5), player1->chaCas(-7), player2->chaCas(-7), player1->chaSjew(-1), player2->chaSjew(-1);
				else fail(player1, player2);return false; break;
		case 20:if (player1->getJew() >= 13) player1->cardstack.push(n),player1->getCard(n), player1->chaJew(-13), player1->chaCas(6), player2->chaCas(-4);
				else fail(player1, player2);return false; break;
		case 21:if (player1->getJew() >= 4) player1->cardstack.push(n),player1->getCard(n), player1->chaJew(-4), player1->chaBri(-10), player1->chaCas(7);
				else fail(player1, player2);return false; break;
		case 22:if (player1->getJew() >= 12) player1->cardstack.push(n),player1->getCard(n), player1->chaJew(-12), player1->chaWall(3), player1->chaCas(8);
				else fail(player1, player2);return false; break;
		case 23:if (player1->getJew() >= 14) player1->cardstack.push(n),player1->getCard(n), player1->chaJew(-14), player1->chaSmon(1), player1->chaCas(8);
				else fail(player1, player2);return false; break;
		case 24:if (player1->getJew() >= 16) player1->cardstack.push(n),player1->getCard(n), player1->chaJew(-16), player1->chaCas(15);
				else fail(player1, player2);return false; break;
		case 25:if (player1->getJew() >= 15) player1->cardstack.push(n),player1->getCard(n), player1->chaJew(-15), player1->chaWall(5), player1->chaCas(10), player1->chaMon(5);
				else fail(player1, player2);return false; break;
		case 26:if (player1->getJew() >= 17) player1->cardstack.push(n),player1->getCard(n), player1->chaJew(-17), player1->chaCas(12), player2->chaCas(-6);
				else fail(player1, player2);return false; break;
		case 27:if (player1->getJew() >= 21) player1->cardstack.push(n),player1->getCard(n), player1->chaJew(-21), player1->chaCas(20);
				else fail(player1, player2);return false; break;
		case 28:if (player1->getJew() >= 8) player1->cardstack.push(n),player1->getCard(n), player1->chaJew(-8), player1->chaWall(-6), player1->chaCas(11);
				else fail(player1, player2);return false; break;																																//宝石牌结束
		}      break;

		case 2: switch(n/3){																																				//怪兽牌
		case 0:player1->cardstack.push(n),player1->getCard(n), player1->chaMon(-6), player2->chaMon(-6);		
		case 1:if (player1->getMon() >= 1) player1->cardstack.push(n),player1->getCard(n), player1->chaMon(-1), player2->defeat(2),again(player1,player2);
				else fail(player1, player2);return false; break;
		case 2:if (player1->getMon() >= 1) player1->cardstack.push(n),player1->getCard(n), player1->chaMon(-1), player2->defeat(4),player1->chaJew(-3);
				else fail(player1, player2);return false; break;
		case 3:if (player1->getMon() >= 3) player1->cardstack.push(n),player1->getCard(n), player1->chaMon(-3), player1->chaSmon(1);
				else fail(player1, player2);return false; break;
		case 4:if (player1->getMon() >= 2) player1->cardstack.push(n),player1->getCard(n), player1->chaMon(-2), player1->getCard(n),again(player1,player2);
				else fail(player1, player2);return false; break;
		case 5:if (player1->getMon() >= 3) player1->cardstack.push(n),player1->getCard(n), player1->chaMon(-3), player2->defeat(6), player1->defeat(3);
				else fail(player1, player2);return false; break;
		case 6:if (player1->getMon() >= 4) player1->cardstack.push(n),player1->getCard(n), player1->chaMon(-4), player2->chaCas(-3), player1->chaCas(-1);
				else fail(player1, player2);return false; break;
		case 7:if (player1->getMon() >= 6) player1->cardstack.push(n),player1->getCard(n), player1->chaMon(-6), player2->chaCas(-2), again(player1,player2);
				else fail(player1, player2);return false; break;
		case 8:if (player1->getMon() >= 3) player1->cardstack.push(n),player1->getCard(n), player1->chaMon(-3), player2->defeat(5);
				else fail(player1, player2);return false; break;
		case 9:if (player1->getMon() >= 5) player1->cardstack.push(n),player1->getCard(n), player1->chaMon(-5), player2->defeat(4), player1->chaWall(3);
				else fail(player1, player2);return false; break;
		case 10:if (player1->getMon() >= 6) player1->cardstack.push(n),player1->getCard(n), player1->chaMon(-6), player2->chaCas(-4);
				else fail(player1, player2);return false; break;
		case 11:if (player1->getMon() >= 7) player1->cardstack.push(n),player1->getCard(n), player1->chaMon(-7), player1->chaSmon(2);
				else fail(player1, player2);return false; break;
		case 12:if (player1->getMon() >= 8) player1->cardstack.push(n),player1->getCard(n), player1->chaMon(-8), player2->defeat(2), player1->chaWall(4),player1->chaCas(2);
				else fail(player1, player2);return false; break;
		case 13:if (player1->getMon() >= 5) player1->cardstack.push(n),player1->getCard(n), player1->chaMon(-5), player2->defeat(6);
				else fail(player1, player2);return false; break;
		case 14: player1->cardstack.push(n),player1->getCard(n), player2->chaSmon(1), player1->chaMon(3), player1->chaSmon(1); break;
		case 15:if (player1->getMon() >= 6) player1->cardstack.push(n),player1->getCard(n), player1->chaMon(-6), player2->defeat(7);
				else fail(player1, player2);return false; break;
		case 16:if (player1->getMon() >= 6) player1->cardstack.push(n),player1->getCard(n), player1->chaMon(-6), player2->defeat(6), player2->chaMon(-3);
				else fail(player1, player2);return false; break;
		case 17:if (player1->getMon() >= 5) {
			player1->cardstack.push(n),player1->getCard(n), player1->chaMon(-5), player2->defeat(6), player1->chaBri(-5), player2->chaBri(-5);
			player1->chaJew(-5); player2->chaJew(-5); player1->chaMon(-5); player2->chaMon(-5);
		}
              	else fail(player1, player2);return false; break;
		case 18:if (player1->getMon() >= 8) { player1->cardstack.push(n),player1->getCard(n), player1->chaMon(-8); if (player2->getWall() == 0) player2->defeat(10);else player2->defeat(6); }
				else fail(player1, player2);return false; break;
		case 19:if (player1->getMon() >= 9) player1->cardstack.push(n),player1->getCard(n), player1->chaMon(-9), player2->defeat(9);
				else fail(player1, player2);return false; break;
		case 20:if (player1->getMon() >= 11) { player1->cardstack.push(n),player1->getCard(n), player1->chaMon(-11); if (player2->getWall() == 0) player2->defeat(7);else player2->defeat(10); }
				else fail(player1, player2);return false; break;
		case 21:if (player1->getMon() >= 9) { player1->cardstack.push(n),player1->getCard(n), player1->chaMon(-9); if (player1->getSjew() > player2->getSjew()) player2->defeat(12);else player2->defeat(8); }
				else fail(player1, player2);return false; break;
		case 22:if (player1->getMon() >= 10) { player1->cardstack.push(n),player1->getCard(n), player1->chaMon(-10); if (player1->getWall() < player2->getWall()) player2->defeat(6);else player2->chaCas(-6); }
				else fail(player1, player2);return false; break;
		case 23:if (player1->getMon() >= 14) player1->cardstack.push(n),player1->getCard(n), player1->chaMon(-14), player2->chaMon(-8), player2->chaCas(-5);
		        else fail(player1, player2);return false; break;
		case 24:if (player1->getMon() >= 11) player1->cardstack.push(n),player1->getCard(n), player1->chaMon(-11), player2->defeat(8), player2->chaSbri(-1);
				else fail(player1, player2);return false; break; 
		case 25:if (player1->getMon() >= 12) player1->cardstack.push(n),player1->getCard(n), player1->chaMon(-12), player2->chaJew(-10), player1->chaJew(5),player1->chaBri(2),player2->chaBri(-5);
				else fail(player1, player2);return false; break;
		case 26:if (player1->getMon() >= 15) player1->cardstack.push(n),player1->getCard(n), player1->chaMon(-15), player2->defeat(10), player1->chaWall(4);
				else fail(player1, player2);return false; break;
		case 27:if (player1->getMon() >= 17) player1->cardstack.push(n),player1->getCard(n), player1->chaMon(-17), player2->defeat(10), player2->chaMon(-5),player2->chaSmon(-1);
				else fail(player1, player2);return false; break;
		case 28:if (player1->getMon() >= 25) player1->cardstack.push(n),player1->getCard(n), player1->chaMon(-25), player2->defeat(20), player2->chaJew(-10),player2->chaSmon(-1);
				else fail(player1, player2);return false; break;																											//怪兽牌结束

		}




			
		}
		acc(player1, player2);
		return true;
}

class Card {
	protected:		
		string name="";
		string effe="";
		string kind="";
public:
	int num;
	int cons;
	virtual void printCard();
	Card(int n);
	};

	void Card:: printCard() {                                                                                      //打印牌
		cout << '<' <<name<< '>' << '(' << kind << cons << ')' << effe<<'\n';
	}
	void printcard(int n) { Card thecard(n); thecard.printCard(); }

	Card::Card(int n) {
		switch (n % 3)
		{
		case 0:   switch (n / 3) {
		case 1: { name = "生死抗争";  kind = "砖头 ";  effe = "双方同时失去八块砖头 "; num = n; cons = 0; }        break;
		case 2: { name="幸运宝藏";  kind="砖头 ";  effe="砖头+2，宝石+2，再次出牌 "; num = n; cons = 0; }         break;
		case 3: { name="友谊之地";  kind="砖头 ";  effe="城墙+1，再次出牌 "; num = n; cons = 1; }        break;
		case 4: { name="伟大矿工";  kind="砖头 ";  effe="砖头产量+1 "; num = n; cons = 3; }        break;
		case 5: { name="矿石之脉";  kind="砖头 ";  effe="如果砖头产量小于对手，则砖头产量+2，否则+1 "; num = n; cons = 4; }        break;
		case 6: { name="矮人之矿";  kind="砖头 ";  effe="城墙+4，砖头产量+1 "; num = n; cons = 7; }        break;
		case 7: { name="努力工作";  kind="砖头 ";  effe="城墙+5，宝石-6 "; num = n; cons = 2; }        break;
		case 8: { name="幻影之手";  kind="砖头 ";  effe="如果砖头产量小于对手，则砖头产量等于对手 "; num = n; cons = 5; }        break;
		case 9: { name="基础之墙";  kind="砖头 ";  effe="城墙+3 "; num = n; cons = 2; }        break;
		case 10: { name="稳固之墙";  kind="砖头 ";  effe="城墙+4 "; num = n; cons = 3; }        break;
		case 11: { name="发明创造";  kind="砖头 ";  effe="得到四个宝石，双方砖头产量同时+1 "; num = n; cons = 2; }        break;
		case 12: { name="稳固基础";  kind="砖头 ";  effe="如果没有城墙，城墙+6，否则+4 "; num = n; cons = 3; }        break;
		case 13: { name="颤动之境";  kind="砖头 ";  effe="双方城墙同时-5，再次出牌 "; num = n; cons = 7; }        break;
		case 14: { name="神秘小屋";  kind="砖头 ";  effe="宝石产量+1，再次出牌 "; num = n; cons = 8; }        break;
		case 15: { name="山崩地裂";  kind="砖头 ";  effe="双方砖头产量同时-1 "; num = n; cons = 0; }        break;
		case 16: { name="雄伟之墙";  kind="砖头 ";  effe="城墙+6 "; num = n; cons = 5; }        break;
		case 17: { name="粉碎之锤";  kind="砖头 ";  effe="对手砖头产量-1 "; num = n; cons = 4; }        break;
		case 18: { name="完美工具";  kind="砖头 ";  effe="砖头产量+2 "; num = n; cons = 6; }        break;
		case 19: { name="矮人之锤";  kind="砖头 ";  effe="砖头产量-1，城墙+10，宝石+5 "; num = n; cons = 0; }        break;
		case 20: { name="神奇之石";  kind="砖头 ";  effe="城墙+8 "; num = n; cons = 8; }        break;
		case 21: { name="神秘之力";  kind="砖头 ";  effe="城墙+5，怪物产量+1 "; num = n; cons = 9; }        break;
		case 22: { name="奇幻宝石";  kind="砖头 ";  effe="城墙+7，宝石+7 "; num = n; cons = 9; }        break;
		case 23: { name="幻想乐曲";  kind="砖头 ";  effe="城墙+6，城堡+3 "; num = n; cons = 11; }        break;
		case 24: { name="牢不可破";  kind="砖头 ";  effe="城墙+12 "; num = n; cons = 13; }        break;
		case 25: { name="完美设计";  kind="砖头 ";  effe="城墙+8，城堡+5 "; num = n; cons = 15; }        break;
		case 26: { name="魔幻之墙";  kind="砖头 ";  effe="城墙+15 "; num = n; cons = 16; }        break;
		case 27: { name="巨石轰击";  kind="砖头 ";  effe="城墙+6，对手城墙-10 "; num = n; cons = 18; }        break;
		case 28: { name="神龙之心";  kind="砖头 ";  effe="城墙+20，城堡+8 "; num = n; cons = 24; }        break;
		case 29: { name="死命工作";  kind="砖头 ";  effe="城墙+9，怪物-9 "; num = n; cons = 7; }        break;
		                         } break;
		case 1:   switch (n / 3) {
		case 0:		{ name="蓝色宝石";  kind="宝石 ";  effe="城堡+1，再次出牌 "; num = n; cons =1 ;}        break;
		case 1:		{ name="奇幻之烟";  kind="宝石 ";  effe="对手城堡-1，再次出牌 "; num = n; cons =2 ;}        break;
		case 2:		{ name="迷幻之手";  kind="宝石 ";  effe="城堡+3 "; num = n; cons =2 ;}        break;
		case 3:		{ name="魔法高手";  kind="宝石 ";  effe="宝石产量+1 "; num = n; cons =3 ;}        break;
		case 4:		{ name="三棱魔镜";  kind="宝石 ";  effe="换一张牌后再次出牌 "; num = n; cons =2 ;}        break;
		case 5:		{ name="怪石缠身";  kind="宝石 ";  effe="城堡+3，这张牌不能换，只能使用 "; num = n; cons =5 ;}        break;
		case 6:		{ name="阳光普照";  kind="宝石 ";  effe="城堡+2，对手城堡-2 "; num = n; cons =4 ;}        break;
		case 7:		{ name="钻石魔阵";  kind="宝石 ";  effe="宝石产量+1，城堡+3，对手城堡+1 "; num = n; cons =6 ;}        break;
		case 8:		{ name="宝石裂痕";  kind="宝石 ";  effe="对手城堡-3 "; num = n; cons =2 ;}        break;
		case 9:		{ name="神红宝石";  kind="宝石 ";  effe="城堡+5 "; num = n; cons =3 ;}        break;
		case 10:	{ name="水晶之矛";  kind="宝石 ";  effe="对手城堡-5 "; num = n; cons =4 ;}        break;
		case 11:	{ name="焚心以火";  kind="宝石 ";  effe="宝石产量+2，城堡-5 "; num = n; cons =3 ;}        break;
		case 12	:	{ name="忠诚代价";  kind="宝石 ";  effe="宝石产量+1，城堡+3，城墙+3 "; num = n; cons =7 ;}        break;
		case 13	:	{ name="公平竞争";  kind="宝石 ";  effe="双方宝石产量都等于量高的一方 "; num = n; cons =7 ;}        break;
		case 14	:	{ name="神奇翡翠";  kind="宝石 ";  effe="城堡+8 "; num = n; cons =6 ;}        break;
		case 15	:	{ name="智慧珍珠";  kind="宝石 ";  effe="宝石产量+1，城堡+5 "; num = n; cons =9 ;}        break;
		case 16:	{ name="赌命狂徒";  kind="宝石 ";  effe="宝石产量-1，对手城堡-9 "; num = n; cons =8 ;}        break;
		case 17:	{ name="崩溃之石";  kind="宝石 ";  effe="城堡+5，对手砖头-6 "; num = n; cons =7 ;}        break;
		case 18:	{ name="蓝色水晶";  kind="宝石 ";  effe="城堡+11 "; num = n; cons =10 ;}        break;
		case 19:	{ name="生死相斗";  kind="宝石 ";  effe="双方宝石产量同时-1，城堡同时-7 "; num = n; cons =5 ;}        break;
		case 20:	{ name="幻火之石";  kind="宝石 ";  effe="城堡+6，对手城堡-4 "; num = n; cons =13 ;}        break;
		case 21:	{ name="巨人奴仆";  kind="宝石 ";  effe="城堡+7，砖头-10 "; num = n; cons =4 ;}        break;
		case 22:	{ name="水晶护身";  kind="宝石 ";  effe="城堡+8，城墙+3 "; num = n; cons =12 ;}        break;
		case 23:	{ name="心领神会";  kind="宝石 ";  effe="城堡+8，怪物产量+1 "; num = n; cons =14 ;}        break;
		case 24:	{ name="钻石永恒";  kind="宝石 ";  effe="城堡+15 "; num = n; cons =16 ;}        break;
		case 25:	{ name="神圣领地";  kind="宝石 ";  effe="城堡+10，城墙+5，怪物+5 "; num = n; cons =15 ;}        break;
		case 26:	{ name="岩浆飞溅";  kind="宝石 ";  effe="城堡+12，对手城堡-6 "; num = n; cons =17 ;}        break;
		case 27:	{ name="神龙之眼";  kind="宝石 ";  effe="城堡+20 "; num = n; cons =21 ;}        break;
		case 28:	{ name="魔幻宝石";  kind="宝石 ";  effe="城堡+11，城墙-6 "; num = n; cons =8 ;}        break;
							         } break;
		case 2:   switch (n / 3) {

			case 0:	 {name="凶恶蛮牛";  kind="怪兽 ";  effe="双方怪物同时-6 "; num = n; cons = 0; break;	}
			case 1:	 {name="幻境仙女";  kind="怪兽 ";  effe="两点攻击，再次出牌 "; num = n; cons = 1; break;	}
			case 2:	 {name="狂野蛮族";  kind="怪兽 ";  effe="4点攻击，宝石-3 "; num = n; cons = 1; break;	}
			case 3:	 {name="百科全书";  kind="怪兽 ";  effe="怪物产量+1 "; num = n; cons = 3; break;	}
			case 4:	 {name="精灵密探";  kind="怪兽 ";  effe="换一张牌后再次出牌 "; num = n; cons = 2; break;	}
			case 5:	 {name="敌我不分";  kind="怪兽 ";  effe="6点攻击，己方遭受3点攻击 "; num = n; cons = 3; break;	}
			case 6:	 {name="野蛮箭手";  kind="怪兽 ";  effe="对手城堡-3，己方城堡-1 "; num = n; cons = 4; break;	}
			case 7:	 {name="神奇仙女";  kind="怪兽 ";  effe="对手城堡-2，再次出牌 "; num = n; cons = 6; break;	}
			case 8:	 {name="食人巨魔";  kind="怪兽 ";  effe="5点攻击 "; num = n; cons = 3; break;	}
			case 9:	 {name="矮人工匠";  kind="怪兽 ";  effe="4点攻击，城墙+3 "; num = n; cons = 5; break;	}
			case 10:	 {name="灵蛇剧毒";  kind="怪兽 ";  effe="对手城堡-4 "; num = n; cons = 6; break;	}
			case 11:	 {name="驯兽专家";  kind="怪兽 ";  effe="怪物产量+2 "; num = n; cons = 7; break;	}
			case 12:	 {name="高塔之妖";  kind="怪兽 ";  effe="2点攻击，城墙+4，城堡+2 "; num = n; cons = 8; break;	}
			case 13:	 {name="月圆之夜";  kind="怪兽 ";  effe="双方怪兽产量同时+1，你再得到三个怪兽 "; num = n; cons = 0; break;	}
			case 14:	 {name="杀手无情";  kind="怪兽 ";  effe="6点攻击 "; num = n; cons = 5; break;	}
			case 15:	 {name="嗜血巨魔";  kind="怪兽 ";  effe="7点攻击 "; num = n; cons = 6; break;	}
			case 16:	 {name="恶灵魔兽";  kind="怪兽 ";  effe="6点攻击，对手怪物-3 "; num = n; cons = 6; break;	}
			case 17:	 {name="恶鬼作怪";  kind="怪兽 ";  effe="6点攻击，双方砖头怪物和宝石同时-5 "; num = n; cons = 5; break;	}
			case 18:	 {name="喷火甲虫";  kind="怪兽 ";  effe="对手没有城墙时10点攻击，否则6点攻击 "; num = n; cons = 8; break;	}
			case 19:	 {name="半人半狼";  kind="怪兽 ";  effe="9点攻击 "; num = n; cons = 9; break;	}
			case 20:	 {name="冷血杀手";  kind="怪兽 ";  effe="对手没有城墙时7点攻击，否则10点攻击 "; num = n; cons = 11; break;	}
			case 21:	 {name="独角神兽";  kind="怪兽 ";  effe="宝石产量多于对手时12点攻击，否则8点攻击 "; num = n; cons = 9; break;	}
			case 22:	 {name="精灵射手";  kind="怪兽 ";  effe="城墙少于对手时6点攻击，否则对手城堡-6 "; num = n; cons = 10; break;	}
			case 23:	 {name="绝命女妖";  kind="怪兽 ";  effe="对手城堡-5，怪物-8 "; num = n; cons = 14; break;	}
			case 24:	 {name="上古魔兽";  kind="怪兽 ";  effe="8点攻击，对手砖头产量-1 "; num = n; cons = 11; break;	}
			case 25:	 {name="无影神偷";  kind="怪兽 ";  effe="对手宝石-10，砖头-5，你得到其中的一半 "; num = n; cons = 12; break;	}
			case 26:	 {name="岩石巨人";  kind="怪兽 ";  effe="10点攻击，城墙+4 "; num = n; cons = 15; break;	}
			case 27:	 {name="吸血僵尸";  kind="怪兽 ";  effe="10点攻击，对手怪物-5，怪物产量-1 "; num = n; cons = 17; break;	}
			case 28:	 {name="无敌天龙";  kind="怪兽 ";  effe="20点攻击，对手宝石-10，怪物产量-1 "; num = n; cons = 25; break;	}
			
		                             }
		}







		}
	
	
	
	
	
	
	
	
		
	

		



	void account(Player* p) {                                                                                   //简单结算
		if (p->getBri()<0) p->chaBri(0 - p->getBri());
		if (p->getJew()<0) p->chaJew(0 - p->getJew());
		if (p->getMon()<0) p->chaMon(0 - p->getMon());
		if (p->getWall()<0) p->chaWall(0 - p->getWall());
		if (p->getSbri()<0) p->chaSbri(0 - p->getSbri());
		if (p->getSjew()<0) p->chaSjew(0 - p->getSjew());
		if (p->getSmon()<0) p->chaSmon(0 - p->getSmon());
		if (p->getCas()<0) p->chaCas(0 - p->getCas());
	}
void acc(Player* player1,Player* player2){                                                                      //简单结算
	account(player1); account(player2);
}






void printwall(int n, int &cas1, int &cas2, int &wall1, int &wall2) {                          //打印第n层城堡和城墙
	if (cas1 > (n - 1) * 10 || cas2 > (n - 1) * 10 || wall1 > (n - 1) * 10 || wall2 > (n - 1) * 10) {
		int t;
		for (t = min(10,10 * n - cas1); t > 0; t--)cout << ' ';  while (cas1 > (n - 1) * 10) { cout << "S"; cas1--; } cout << " ";
		for (t = min(10,10 * n - wall1); t > 0; t--)cout << ' ';  while (wall1 > (n - 1) * 10) { cout << "M"; wall1--; } cout << "                                                                           ";
		for (t = min(10,10 * n - wall2); t > 0; t--)cout << ' ';  while (wall2 > (n - 1) * 10) { cout << "W"; wall2--; } cout << " ";
		for (t = min(10,10 * n - cas2); t > 0; t--)cout << ' ';  while (cas2 > (n - 1) * 10) { cout << "T"; cas2--; }cout<<'\n';
	};
}
	int roundnumber = 50,clocktime=0;															//游戏时钟
	void printscreen(Player* player1, Player* player2) {                                        //打印游戏界面
		system("cls");
		acc(player1, player2);
		int cas1 = player1->getCas();
		int cas2 = player2->getCas();
		int wall1 = player1->getWall();
		int wall2 = player2->getWall();
		player1->printname(); cout << "					回合（"
			<< clocktime << "/" << roundnumber << ")					"; player2->printname(); cout << '\n';
		cout << "砖头" << player1->getBri() << "(" << player1->getSbri() << ")   ";
		cout << "宝石" << player1->getJew() << "(" << player1->getSjew() << ")   ";
		cout << "怪物" << player1->getMon() << "(" << player1->getSmon() << ")   "; cout << "                                                   ";
		cout << "砖头" << player2->getBri() << "(" << player2->getSbri() << ")   ";
		cout << "宝石" << player2->getJew() << "(" << player2->getSjew() << ")   ";
		cout << "怪物" << player2->getMon() << "(" << player2->getSmon() << ")   ";
		cout << "\n                        player1上回合出牌：";  while (!player1->cardstack.empty()) { printcard(player1->cardstack.top()), player1->cardstack.pop(); }
		cout << "\n                        player2上回合出牌：";  while (!player2->cardstack.empty()) { printcard(player2->cardstack.top()), player2->cardstack.pop(); }
		cout << endl;
		for (int i = 20; i > 0; i--) printwall(i, cas1, cas2, wall1, wall2);
		if (f) cout << "player1的回合，请出牌<数字> 或按（0）放弃出牌并弃一张牌！\nPLAYER的手牌:\n";
		else  cout << "player2的回合，请出牌<数字> 或按（0）放弃出牌并弃一张牌！\n                                                                                           PLAYER的手牌:\n";
		if (f) {for (int i = 0; player1->handcard[i] != 0; i++) printcard(player1->handcard[i]);}
			else { for (int i = 0; player2->handcard[i] != 0; i++) cout<<"\t\t\t\t\t\t",printcard(player2->handcard[i]); }

	
};

void incr(Player* p) {																		//结算，资源增加函数
	p->chaBri(p->getSbri());
	p->chaMon(p->getSmon());
	p->chaJew(p->getSjew());
}                      

void rule() {																				//打印游戏规则
	cout << "  1. 游戏双方拥有一个城堡和一堵可以保护城堡的城墙，以及三种资源：砖、宝石、怪物。\n";
	cout << "游戏开始时，可设定双方城堡和墙的高度（默认25和10），";
		cout << "初始资源（默认均为10），每回合资源的产量（默认均为2）。每回合玩家动作前，先生产资源，资源量按回合产量累积。";
		cout << "\n  2. 游戏有87张卡牌，游戏开始时双方各拿6张初始卡牌。每回合轮流出一张卡牌，出牌后自动拿一张卡牌。";
		cout << "有些卡牌可以让玩家再出一次牌。卡牌分为三类，按卡牌上的描述，出牌时分别消耗砖、宝石、怪物三种资源中的一种，以及获得出牌的效果。";
			cout << "如果资源不足，则不能出牌，但可以弃牌。一般来说，消耗砖的卡牌和建设城墙有关，消耗宝石的卡牌和建设城堡有关，消耗怪物的卡牌和攻击对方有关。";
			cout << "卡牌说明中“N点攻击”优先攻击城墙，在城墙高度为0时攻击城堡，总攻击点数为N。";
			cout << "\n  3. 游戏目标是摧毁对方的城堡（将对方城堡减为0），或者将自己的城堡加盖到某个高度（默认50），或者将自己的三种资源都累计到某个数量（默认50）。如果到了某个回合数（默认30）双方都没有胜利，则为平局。\n";
			system("pause");
}


void setname(Player* p1,Player* p2) {
	system("cls");
	cout << "请输入player1的姓名:\n";
	p1->writename();
	p1->writename();
	cout << "请输入player2的姓名:\n";
	p2->writename();
}

void set() {																						//游戏设置
	char t = '5';
	while (t != 'd')
	{   
		system("cls");
		cout << "您要修改哪个游戏参数:\n";
		cout << "(a)达成胜利方式1的城堡高度(50)\n（b）游戏判定平局的最大持续轮数(50) \n（c）达成胜利方式2的资源收集要求(各50) \n（d）不修改";
		cin.get(t);
		if (t == 'a' || t == 'b' || t == 'c') {
			if (t == 'c') cout << "你想修改资源收集要求中的 （1）砖头\n（2）宝石\n（3）怪物\n";
			cout << "你想将之改为:";
			int num;
			cin >> num;
			switch (t) {
			case 'a':   castle = num; break;
			case 'b':   roundnumber = num; break;
			case '1':   brick = num; break;
			case '2':   jewel = num; break;
			case '3':   monster = num; break;
			}
		}
	}
}

void start() {																				//游戏开始
	system("color F0");
	cout << "						欢迎来到魔幻牌\n";
	cout <<"                                              welcome to acromage\n";
cout << "           按任意键开始游戏                      按数字0查看游戏规则\n";
    char t='5';
	cin.get(t);
	cin.clear();
	if (t == '0') rule();
};                                                                                     //登入界面

void init() {
	cout << "                                   若要修改游戏设置请按0";
	char t = '5';
	cin.get(t);
	cin.clear();
	if (t == '0') set();
	system("cls");
	cout << "请选择你的幸运数\n";                                                        //初始化
	cin >> lucky;
	srand(lucky);	
};                                                   

                                                                                   
int judge(Player *player1, Player *player2) {
	if (player1->judge()) return player1->judge();                                                //判断胜负
	if (player2->judge()) return player2->judge();
	return 0;
}

int main(int argc, char *argv[])
{

	start();
	init();
	Player player1, player2;
	setname(&player1, &player2);
	for (int i = 0; i < 6;i++) {player1.handcard[i] = rand()%87+1; player2.handcard[i] = rand()%87+1;
}
	while (clocktime<=roundnumber&&!judge(&player1, &player2))
	{
		int n = 0;
		f = 1;
		printscreen(&player1,&player2);
		cin >> n;
		play(&player1, &player2, n);
		f = 0;
		printscreen(&player1,&player2);
		cin >> n;
		play(&player2, &player1, n);
		clocktime++;
		incr(&player1); 
		incr(&player2);
	}
	if (clocktime > roundnumber) cout << "时间已到，未分出胜负，平局。\n";
	else	if (player1.judge() == 1 || player2.judge() == -1) { cout << "胜负已分！     Player1:"; player1.printname(); cout << "赢了！\n"; }
	else {cout << "胜负已分！     Player2:"; player2.printname(); cout << "赢了！\n";}
    return 0;
}

