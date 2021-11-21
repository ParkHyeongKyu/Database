#include <cstdio>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <cstring>
using namespace std;

typedef class user {
public:
	string getlname() { return lname; }
	int getzone() { return zone; }
	bool getactive() { return active; }
	void putlname(string _lname) { lname = _lname; }
	void putzone(int _zone) { zone = _zone; }
	void notactive() { active = false; }
	void isactive() { active = true; }
private:
	string lname;
	int zone;
	bool active;
}user;


typedef class zonecost {
public:
	int getzoneid() { return zoneid; }
	string getzonedesc() { return zonedesc; }
	void putzoneid(int _id) { zoneid = _id; }
	void putzonedesc(string desc) { zonedesc = desc; }
private:
	int zoneid;
	string zonedesc;
}zonecost;

typedef class item {
public:
	int getcount() { return count; }
	int getbarcode() { return barcode; }
	void putbar(int bar) { barcode = bar; }
	void putpro(string _pro) { proddesc = _pro; }
	void pluscount() { count++; }
	void zerocount() { count = 0; }
	void putuser(string _user) { userlist.push_back(_user); }
	void vectorclear() { userlist.clear(); }
	string getproddesc() { return proddesc; }
	vector<string> getuserlist() { return userlist; }
	vector<string> userlist;
private:
	int barcode;
	int count;
	string proddesc;
}item;

typedef class itemlist {
public:
	itemlist() : count(0) {}
	int getcount() { return count; }
	vector<item> getlist() { return list; }
	void putitem(item _item) { list.push_back(_item); count++; }
	vector<item> list;
private:
	int count;
}itemlist;

int main(int argc, char** argv)
{
	if (!strcmp(argv[1], "q1"))
	{
		int c = 0, p = 0;
		string temp, temp2, lname, zonedesc, act, zone, zoneid;
		int act_i, zone_i, zoneid_i;
		user newuser;
		zonecost newzonecost;
		vector<user> vu;
		vector<zonecost> vz;
		vector<user>::iterator uitor;
		vector<zonecost>::iterator zitor;
		ifstream userfile;
		ifstream costfile;
		userfile.open(argv[2]);
		costfile.open(argv[3]);
		//userfile.open("customer.txt");
		//costfile.open("zonecost.txt");

		if (userfile.is_open())
		{
			while (!userfile.eof())
			{
				if (c == 0 || c == 1)
				{
					getline(userfile, temp);
					c++;
				}
				else
				{
					getline(userfile, temp);
					if (temp == "")
					{
						if (costfile.is_open())
						{
							while (!costfile.eof())
							{
								if (p == 0 || p == 1)
								{
									getline(costfile, temp2);
									p++;
								}
								else
								{
									getline(costfile, temp2);
									if (temp2 == "") //토론토에 사는 활성화된 사람 찾기
									{
										for (uitor = vu.begin(); uitor != vu.end(); uitor++)
										{
											for (zitor = vz.begin(); zitor != vz.end(); zitor++)
											{
												if (uitor->getzone() == zitor->getzoneid() && uitor->getactive())
												{
													if (zitor->getzonedesc() == "Toronto             ")
														cout << uitor->getlname() << endl;
												}
											}
										}
										return 0;
									}
									zoneid = temp2.substr(0, 6); //zonecost table 정보 받아오기
									zoneid_i = stoi(zoneid);
									zonedesc = temp2.substr(7, 20);
									newzonecost.putzoneid(zoneid_i);
									newzonecost.putzonedesc(zonedesc);
									vz.push_back(newzonecost);
								}
							}
						}
					}
					else //customer table 정보 받아오기
					{
						lname = temp.substr(42, 20);
						zone = temp.substr(135, 6);
						zone_i = stoi(zone);
						act = temp.substr(243, 6);
						act_i = stoi(act);
						newuser.putlname(lname);
						newuser.putzone(zone_i);
						if (act_i)
							newuser.isactive();
						else
							newuser.notactive();
						vu.push_back(newuser);
					}
				}
			}
		}
		return 0;
	}
	else if (!strcmp(argv[1], "q2"))
	{
		itemlist il;
		item newitem;
		int c = 0, p = 0;
		ifstream itemtable;
		ifstream producttable;
		string temp, bcode, uname, pro;
		int bcode_i;
		bool sameuser = 0;
		bool sameitem = 0;
		vector<item>::iterator itor;
		vector<string>::iterator itor2;
		itemtable.open(argv[2]);
		producttable.open(argv[3]);
		//itemtable.open("lineitem.txt");
		//producttable.open("products_a.txt");
		if (itemtable.is_open())
		{
			while (!itemtable.eof())
			{
				if (c == 0 || c == 1) //처음 두 줄 받아서 스킵
				{
					getline(itemtable, temp);
					c++;
				}
				else
				{
					getline(itemtable, temp);
					if (temp == "") //파일이 끝남, itemlist에서 count가 2 이상인 것 출력
					{
						itemtable.close();
						if (producttable.is_open())
						{
							while (!producttable.eof())
							{
								if (p == 0 || p == 1) //처음 두 줄 받아서 스킵
								{
									getline(producttable, temp);
									p++;
								}
								else
								{
									getline(producttable, temp);
									if (temp == "")
									{
										producttable.close();
										return 0;
									}
									bcode = temp.substr(0, 20);
									bcode_i = stoi(bcode);
									pro = temp.substr(32, 50);
									for (itor = il.list.begin(); itor != il.list.end(); itor++) //itemlist에서 count가 2 이상인지 확인
									{
										if (itor->getcount() >= 2)
										{
											if (itor->getbarcode() == bcode_i)
											{
												cout << bcode_i << "    " << pro << endl;
												break;
											}
										}
									}
								}
							}
						}
					}
					else
					{
						bcode = temp.substr(41, 20); //barcode
						bcode_i = stoi(bcode);
						uname = temp.substr(0, 20); //uname
						if (il.getcount() != 0)
						{
							for (itor = il.list.begin(); itor != il.list.end(); itor++) //itemlist에 해당 item이 이미 존재하는지 확인
							{
								if (itor->getbarcode() == bcode_i) //item이 이미 존재한다면?
								{
									sameitem = 1;
									for (itor2 = itor->userlist.begin(); itor2 != itor->userlist.end(); itor2++) //해당 item의 userlist를 검사하여 user가 겹치는지 검사
									{
										if (*itor2 == uname) //user가 겹친다면 스킵
										{
											sameuser = 1; //user 겹침 FLAG
											break;
										}
									}
									if (!sameuser)
									{
										itor->pluscount();
										itor->putuser(uname);
									}
									else
										sameuser = 0;
									break;
								}
							}
						}
						if (!sameitem)
						{
							newitem.putbar(bcode_i);
							newitem.pluscount();
							newitem.putuser(uname);
							il.putitem(newitem); //item을 만들어서 push back 해야함
							newitem.zerocount();
							newitem.vectorclear(); //newitem 변수 다시 초기화(다음에 사용)
						}
						else
							sameitem = 0;
					}
				}
			}
		}
		return 0;
	}
}

/*
customertable에서 zone, ACTIVE, LNAME받아옴. zone과 zonecosttable의
zoneid를 비교하여 일치하는 곳에 있는 zonedesc가 Toronto인지 확인
Toronto일 경우 ACTIVE이면 vector<string>에 넣어두었다가 한꺼번에 출력
*/