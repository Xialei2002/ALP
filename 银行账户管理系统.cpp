#include<iostream>
#include<string>
#include<fstream>
#include<cmath>
#include<stdio.h>
#include<algorithm>
#include<string.h>
#include<iomanip>
using namespace std;

struct Account
{
	string a_number;
	string a_name;
	string a_sex;
	int a_key;
	long long a_sum;
	int a_date;
	string a_state;
	Account* a_next;
};

/*
运算符重载，使用小于号<比较两字符串大小时采用该方法。
*/
bool operator<(string s1, string s2)
{
	int min_size = min(s1.size(), s2.size());
	for (int i = 0; i < min_size; i++)
	{
		if (s1[i] < s2[i])
		{
			return true;
		}
		else if (s1[i] > s2[i])
		{
			return false;
		}
		if (i == min_size - 1 and s1[i] == s2[i])
		{
			if (s1.size() < s2.size())
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
}

/*
日期比较，比较两个八位日期(yyyymmdd)时采用该方法。
*/
bool comp_date(int a, int b)//小的日期排在前
{
	if (a / 10000 < b / 10000)
	{
		return true;
	}
	else if (a / 10000 == b / 10000 and (a / 100 - a / 10000) < (b / 100 - b / 10000))
	{
		return true;
	}
	else if (a / 10000 == b / 10000 and (a / 100 - a / 10000) == (b / 100 - b / 10000) and (a - a / 100 - a / 10000) < (b - b / 100 - b / 10000))
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*
从文件导入账户信息到单链表。
变量定义；
如果银行内没有账户，则输出"该银行不存在账户。"；
如果有账户，则将各个账户的信息导入到单链表中，并返回头指针。
*/
Account* CreateAccount(ifstream& fcin)
{
	Account* Head = nullptr;
	Account* q = nullptr;
	if (fcin.peek() == -1)
	{
		cout << "该银行不存在账户。" << endl;
		return Head;
	}
	while (fcin.peek() != -1)
	{
		Account* p = new Account;
		fcin >> p->a_number >> p->a_name >> p->a_sex >> p->a_key >> p->a_sum >> p->a_date >> p->a_state;
		if (Head == nullptr)
		{
			Head = p;
			q = p;
			if (fcin.peek() == '\n')
			{
				fcin.get();
			}
			continue;
		}
		q->a_next = p;
		q = p;
		if (fcin.peek() == '\n')
		{
			fcin.get();
		}
	}
	if (q != nullptr)
	{
		q->a_next = nullptr;
	}
	return Head;
}

/*
展示所有账号。
如果头指针为空指针，则输出"该银行内不存在账号。"；
变量定义；
如果头指针不为空，则按链表输出所有的账号信息。
*/
void ShowAccount(Account*& Head)
{
	if (Head == nullptr)
	{
		cout << "该银行内不存在账号。" << endl;
		return;
	}
	Account* p = Head;
	while (p != nullptr)
	{
		cout << p->a_number << " " << p->a_name << " " << p->a_sex << " " << p->a_key << " " << p->a_sum << " " << p->a_date << " " << p->a_state << endl;
		p = p->a_next;
	}
}

/*
将账户信息导出到文件。
打开文件；
将链表内容依次输出到文件；
关闭文件。
*/
void InputAccount(Account* Head, char& bank)
{
	ofstream fcout;
	switch (bank)
	{
	case 'a':fcout.open("a.txt", ios::out); break;
	case 'b':fcout.open("b.txt", ios::out); break;
	case 'c':fcout.open("c.txt", ios::out); break;
	case 'd':fcout.open("d.txt", ios::out); break;
	case 'e':fcout.open("e.txt", ios::out); break;
	default:cout << "不存在此银行。" << endl; return;
	}
	Account* p = Head;
	while (p != nullptr)
	{
		if (p == Head)
		{
			fcout << p->a_number << " " << p->a_name << " " << p->a_sex << " " << p->a_key << " " << p->a_sum << " " << p->a_date << " " << p->a_state;
		}
		else
		{
			fcout << endl << p->a_number << " " << p->a_name << " " << p->a_sex << " " << p->a_key << " " << p->a_sum << " " << p->a_date << " " << p->a_state;
		}
		p = p->a_next;
	}
	cout << "bank " << bank << ":Input Successfully.";
	fcout.close();
}

/*
搜索账号。
变量定义；
如果头指针为空指针，或搜索不到对应账号，则返回空指针；
如果搜索到了对应账号，则返回该账号数据的地址。
*/
Account* SearchAccount(Account*& Head,string number)
{
	if (Head == nullptr)
	{
		return nullptr;
	}
	Account* p = Head;
	bool flag = false;
	while (p != nullptr)
	{
		if (p->a_number == number)
		{
			break;
		}
		p = p->a_next;
	}
	if (p == nullptr)
	{
		return nullptr;
	}
	else
	{
		return p;
	}
}

/*
开户。
变量定义；
如果输入的账号已存在，则打印"账户已存在。"；
如果不存在，则输入账户信息，将账户加到链表末尾，并将账户链表保存到文件。
*/
void AddAccount(Account*& Head,char& bank)
{
	cout << "请输入您的账号：";
	string num;
	cin >> num;
	Account* temp = SearchAccount(Head, num);
	if (temp != nullptr)
	{
		cout << "账户已存在。" << endl;
	}
	else
	{
		Account* p = new Account;
		p->a_number = num;
		cout << "请输入姓名、性别、密码、金额、开户日期、账户状态" << endl;
		cin >> p->a_name >> p->a_sex >> p->a_key >> p->a_sum >> p->a_date >> p->a_state;
		p->a_next = nullptr;
		if (Head == nullptr)
		{
			Head = p;
			cout << "开户成功。" << endl;
			return;
		}
		Account* temp0 = Head;
		while (temp0 != nullptr)
		{
			if (temp0->a_next == nullptr)
			{
				temp0->a_next = p;
				break;
			}
			temp0 = temp0->a_next;
		}
		InputAccount(Head, bank);
		cout << "开户成功。" << endl;
	}
}

/*
销户。
变量定义；
如果输入的账号不存在，则打印"账户不存在。"；
如果存在，则输入密码；
如果密码错误，则输出"密码错误！"；
若密码正确，则将账户从链表删除，并将账户链表保存到文件。
*/
void DeleteAccount(Account*& Head,char& bank)
{
	if (Head == nullptr)
	{
		cout << "该银行内不存在账号。" << endl;
		return;
	}
	cout << "请输入您的账号：";
	string num;
	cin >> num;
	Account* temp = SearchAccount(Head, num);
	if (temp == nullptr)
	{
		cout << "账户不存在。" << endl;
	}
	else
	{
		cout << "请输入密码：";
		int k;
		cin >> k;
		if (k != temp->a_key)
		{
			cout << "密码错误！" << endl;
			return;
		}
		else
		{
			Account* p = Head;
			while (p != nullptr)
			{
				if (p == temp)
				{
					break;
				}
				if (p->a_next == temp)
				{
					break;
				}
				p = p->a_next;
			}
			if (temp == Head)
			{
				Head = Head->a_next;
				temp->a_sum = 0;
				delete temp;
				InputAccount(Head, bank);
				cout << "销户成功" << endl;
			}
			else if (p != nullptr)
			{
				p->a_next = temp->a_next;
				temp->a_sum = 0;
				delete temp;
				InputAccount(Head, bank);
				cout << "销户成功" << endl;
			}
		}
	}
}

/*
按账号排序。
变量定义；
如果头指针为空指针或链表仅含一条数据，则返回；
如果含多条数据，按15位账号的大小对各个数据进行选择排序。
*/
void SortAccount_Number(Account*& Head)
{
	if (Head == nullptr)
	{
		cout << "该银行不存在账户。" << endl;
		return;
	}
	if (Head->a_next == nullptr)
	{
		return;
	}
	Account* p = Head;
	Account* min_ac = Head;
	Account* sorted = nullptr;
	Account* now_ac = Head;
	while (now_ac->a_next != nullptr)
	{
		while (p != nullptr)
		{
			if (p->a_number < min_ac->a_number)
			{
				min_ac = p;//min_ac指向待测数据中的最小值
			}
			p = p->a_next;
		}
		Account* min_last = Head;//指针min_last指向最小值数据的前一个数据
		if (Head == min_ac)
		{
			min_last = nullptr;//如果最小值就是头部，min_last为空指针
		}
		else
		{
			while (min_last->a_next != min_ac)
			{
				min_last = min_last->a_next;
			}
		}
		if (sorted == nullptr)//刚开始排序，未排第一个
		{
			if (now_ac != min_ac and now_ac->a_next != min_ac)//（头部与非下一个数据的某一个数据）两个不连在一起的位置交换
			{
				Account* temp = min_ac->a_next;
				min_ac->a_next = now_ac->a_next;
				if (min_last != nullptr)
				{
					min_last->a_next = now_ac;
				}
				now_ac->a_next = temp;
				Head = min_ac;
			}
			else if (now_ac->a_next == min_ac)//（头部与下一个数据）两个连在一起的数据交换
			{
				Account* temp = min_ac->a_next;
				min_ac->a_next = now_ac;
				now_ac->a_next = temp;
				Head = min_ac;
			}
		}
		else//排完第一个
		{
			Account* now_last = Head;//是否可以把now_last用sorted替代
			while (now_last->a_next != now_ac)
			{
				now_last = now_last->a_next;
			}
			if (now_ac != min_ac and now_ac->a_next != min_ac)//两个不连在一起的数据交换位置
			{
				Account* temp = min_ac->a_next;
				min_ac->a_next = now_ac->a_next;
				now_ac->a_next = temp;
				min_last->a_next = now_ac;
				now_last->a_next = min_ac;
			}
			else if (now_ac->a_next == min_ac)
			{
				Account* temp = min_ac->a_next;
				min_ac->a_next = now_ac;
				now_ac->a_next = temp;
				now_last->a_next = min_ac;
			}
		}
		sorted = min_ac;
		now_ac = min_ac->a_next;
		p = sorted->a_next;
		min_ac = min_ac->a_next;
	}
	cout << "已完成按账号排序。" << endl;
}

/*
按姓名排序。
变量定义；
如果头指针为空指针或链表仅含一条数据，则返回；
如果含多条数据，按姓名对各个数据进行选择排序。
*/
void SortAccount_Name(Account*& Head)
{
	if (Head == nullptr)
	{
		cout << "该银行不存在账户。" << endl;
		return;
	}
	if (Head->a_next == nullptr)
	{
		return;
	}
	Account* p0 = Head;
	while (p0 != nullptr)
	{
		for (int i = 0; i < p0->a_name.size(); i++)
		{
			if (p0->a_name[i] < 0)
			{
				cout << "暂不支持以汉字排序。" << endl;
				return;
			}
		}
		p0 = p0->a_next;
	}
	Account* p = Head;
	Account* min_ac = Head;
	Account* sorted = nullptr;
	Account* now_ac = Head;
	while (now_ac->a_next != nullptr)
	{
		while (p != nullptr)
		{
			if (p->a_name < min_ac->a_name)
			{
				min_ac = p;//min_ac指向待测数据中的最小值
			}
			p = p->a_next;
		}
		Account* min_last = Head;//指针min_last指向最小值数据的前一个数据
		if (Head == min_ac)
		{
			min_last = nullptr;//如果最小值就是头部，min_last为空指针
		}
		else
		{
			while (min_last->a_next != min_ac)
			{
				min_last = min_last->a_next;
			}
		}
		if (sorted == nullptr)//刚开始排序，未排第一个
		{
			if (now_ac != min_ac and now_ac->a_next != min_ac)//（头部与非下一个数据的某一个数据）两个不连在一起的位置交换//min_last!=now可行
			{
				Account* temp = min_ac->a_next;
				min_ac->a_next = now_ac->a_next;
				if (min_last != nullptr)
				{
					min_last->a_next = now_ac;
				}
				now_ac->a_next = temp;
				Head = min_ac;
			}
			else if (now_ac->a_next == min_ac)//（头部与下一个数据）两个连在一起的数据交换
			{
				Account* temp = min_ac->a_next;
				min_ac->a_next = now_ac;
				now_ac->a_next = temp;
				Head = min_ac;
			}
		}
		else//排完第一个
		{
			Account* now_last = Head;//是否可以把now_last用sorted替代
			while (now_last->a_next != now_ac)
			{
				now_last = now_last->a_next;
			}
			if (now_ac != min_ac and now_ac->a_next != min_ac)//两个不连在一起的数据交换位置
			{
				Account* temp = min_ac->a_next;
				min_ac->a_next = now_ac->a_next;
				now_ac->a_next = temp;
				min_last->a_next = now_ac;
				now_last->a_next = min_ac;
			}
			else if (now_ac->a_next == min_ac)
			{
				Account* temp = min_ac->a_next;
				min_ac->a_next = now_ac;
				now_ac->a_next = temp;
				now_last->a_next = min_ac;
			}
		}
		sorted = min_ac;
		now_ac = min_ac->a_next;
		p = sorted->a_next;
		min_ac = min_ac->a_next;
	}
	cout << "已完成按姓名排序。" << endl;
}

/*
按金额排序。
变量定义；
如果头指针为空指针或链表仅含一条数据，则返回；
如果含多条数据，按金额对各个数据进行选择排序。
*/
void SortAccount_Sum(Account*& Head)
{
	if (Head == nullptr)
	{
		cout << "该银行不存在账户。" << endl;
		return;
	}
	if (Head->a_next == nullptr)
	{
		return;
	}
	Account* p = Head;
	Account* min_ac = Head;
	Account* sorted = nullptr;
	Account* now_ac = Head;
	while (now_ac->a_next != nullptr)
	{
		while (p != nullptr)
		{
			if (p->a_sum < min_ac->a_sum)
			{
				min_ac = p;//min_ac指向待测数据中的最小值
			}
			p = p->a_next;
		}
		Account* min_last = Head;//指针min_last指向最小值数据的前一个数据
		if (Head == min_ac)
		{
			min_last = nullptr;//如果最小值就是头部，min_last为空指针
		}
		else
		{
			while (min_last->a_next != min_ac)
			{
				min_last = min_last->a_next;
			}
		}
		if (sorted == nullptr)//刚开始排序，未排第一个
		{
			if (now_ac != min_ac and now_ac->a_next != min_ac)//（头部与非下一个数据的某一个数据）两个不连在一起的位置交换//min_last!=now可行
			{
				Account* temp = min_ac->a_next;
				min_ac->a_next = now_ac->a_next;
				if (min_last != nullptr)
				{
					min_last->a_next = now_ac;
				}
				now_ac->a_next = temp;
				Head = min_ac;
			}
			else if (now_ac->a_next == min_ac)//（头部与下一个数据）两个连在一起的数据交换
			{
				Account* temp = min_ac->a_next;
				min_ac->a_next = now_ac;
				now_ac->a_next = temp;
				Head = min_ac;
			}
		}
		else//排完第一个
		{
			Account* now_last = Head;//是否可以把now_last用sorted替代
			while (now_last->a_next != now_ac)
			{
				now_last = now_last->a_next;
			}
			if (now_ac != min_ac and now_ac->a_next != min_ac)//两个不连在一起的数据交换位置
			{
				Account* temp = min_ac->a_next;
				min_ac->a_next = now_ac->a_next;
				now_ac->a_next = temp;
				min_last->a_next = now_ac;
				now_last->a_next = min_ac;
			}
			else if (now_ac->a_next == min_ac)
			{
				Account* temp = min_ac->a_next;
				min_ac->a_next = now_ac;
				now_ac->a_next = temp;
				now_last->a_next = min_ac;
			}
		}
		sorted = min_ac;
		now_ac = min_ac->a_next;
		p = sorted->a_next;
		min_ac = min_ac->a_next;
	}
	cout << "已完成按金额排序。" << endl;

}

/*
按开户日期排序。
变量定义；
如果头指针为空指针或链表仅含一条数据，则返回；
如果含多条数据，按日期先后对各个数据进行选择排序。
*/
void SortAccount_Date(Account*& Head)
{
	if (Head == nullptr)
	{
		cout << "该银行不存在账户。" << endl;
		return;
	}
	if (Head->a_next == nullptr)
	{
		return;
	}
	Account* p = Head;
	Account* min_ac = Head;
	Account* sorted = nullptr;
	Account* now_ac = Head;
	while (now_ac->a_next != nullptr)
	{
		while (p != nullptr)
		{
			if (comp_date(p->a_date, min_ac->a_date))
			{
				min_ac = p;//min_ac指向待测数据中的最小值
			}
			p = p->a_next;
		}
		Account* min_last = Head;//指针min_last指向最小值数据的前一个数据
		if (Head == min_ac)
		{
			min_last = nullptr;//如果最小值就是头部，min_last为空指针
		}
		else
		{
			while (min_last->a_next != min_ac)
			{
				min_last = min_last->a_next;
			}
		}
		if (sorted == nullptr)//刚开始排序，未排第一个
		{
			if (now_ac != min_ac and now_ac->a_next != min_ac)//（头部与非下一个数据的某一个数据）两个不连在一起的位置交换//min_last!=now可行
			{
				Account* temp = min_ac->a_next;
				min_ac->a_next = now_ac->a_next;
				if (min_last != nullptr)
				{
					min_last->a_next = now_ac;
				}
				now_ac->a_next = temp;
				Head = min_ac;
			}
			else if (now_ac->a_next == min_ac)//（头部与下一个数据）两个连在一起的数据交换
			{
				Account* temp = min_ac->a_next;
				min_ac->a_next = now_ac;
				now_ac->a_next = temp;
				Head = min_ac;
			}
		}
		else//排完第一个
		{
			Account* now_last = Head;//是否可以把now_last用sorted替代
			while (now_last->a_next != now_ac)
			{
				now_last = now_last->a_next;
			}
			if (now_ac != min_ac and now_ac->a_next != min_ac)//两个不连在一起的数据交换位置
			{
				Account* temp = min_ac->a_next;
				min_ac->a_next = now_ac->a_next;
				now_ac->a_next = temp;
				min_last->a_next = now_ac;
				now_last->a_next = min_ac;
			}
			else if (now_ac->a_next == min_ac)
			{
				Account* temp = min_ac->a_next;
				min_ac->a_next = now_ac;
				now_ac->a_next = temp;
				now_last->a_next = min_ac;
			}
		}
		sorted = min_ac;
		now_ac = min_ac->a_next;
		p = sorted->a_next;
		min_ac = min_ac->a_next;
	}
	cout << "已完成按开户日期排序。" << endl;
}

/*
展示搜索到的账号。
变量定义；
当头指针为空指针时，输出"该银行内不存在账户。"；
当搜索到的指针为空指针时，输出"账户不存在。"；
当搜索到账号时，输出账号信息。
*/
void ShowSearchAccount(Account*& Head)
{
	string tempstr;
	cout << "请输入查询的账号：" << endl;
	cin >> tempstr;
	if (Head == nullptr)
	{
		cout << "该银行内不存在账户。" << endl;
		return;
	}
	Account* temp = SearchAccount(Head, tempstr);
	if (temp == nullptr)
	{
		cout << "账户不存在。" << endl;
	}
	else
	{
		cout << "账号：" << temp->a_number << "\n姓名：" << temp->a_name << "\n性别：" << temp->a_sex << "\n余额：" << temp->a_sum << "\n开户日期：" << temp->a_date << endl;
	}
}

/*
修改密码。
定义变量；
当头指针为空指针时，输出"该银行不存在账户。"，返回；
当搜索到账户时，要求用户输入原密码；
若密码错误，输出"密码错误！"；
若密码正确，要求用户输入新密码，用新密码代替旧密码，并将账户信息更新至文件。
*/
void ChangeKey(Account*& Head,char& bank)
{
	Account* p = Head;
	if (Head == nullptr)
	{
		cout << "该银行不存在账户。" << endl;
		return;
	}
	cout << "请输入待修改密码的账号：";
	string num;
	cin >> num;
	Account* temp = SearchAccount(Head, num);
	if (temp == nullptr)
	{
		cout << "账户不存在。" << endl;
	}
	else
	{
		cout << "请输入原密码：";
		int c_key;
		cin >> c_key;
		if (c_key != temp->a_key)
		{
			cout << "密码错误！" << endl;
		}
		else
		{
			cout << "请输入新密码：";
			int new_key;
			cin >> new_key;
			temp->a_key = new_key;
			InputAccount(Head, bank);
			cout << "修改成功。" << endl;
		}
	}
}

/*
存款。
变量定义；
当头指针为空指针时，输出"该银行不存在账户。"，返回；
当搜索到账户时，要求用户输入密码；
若密码错误，输出"密码错误！"；
若密码正确，要求用户输入存款金额，将存款金额加到余额，并将账户信息更新至文件。
*/
void AddMoney(Account*& Head,char& bank)
{
	Account* p = Head;
	if (Head == nullptr)
	{
		cout << "该银行不存在账户。" << endl;
		return;
	}
	cout << "请输入存款账号：";
	string num;
	cin >> num;
	Account* temp = SearchAccount(Head, num);
	if (temp == nullptr)
	{
		cout << "账户不存在。" << endl;
	}
	else
	{
		cout << "请输入密码：";
		int c_key;
		cin >> c_key;
		if (c_key != temp->a_key)
		{
			cout << "密码错误！" << endl;
		}
		else
		{
			cout << "请输入存款金额：";
			long long money_add;
			cin >> money_add;
			temp->a_sum += money_add;
			InputAccount(Head, bank);
			cout << "存款成功。" << endl;
		}
	}
}

/*
取款
变量定义；
当头指针为空指针时，输出"该银行不存在账户。"，返回；
当搜索不到账户，输出"账户不存在。"，返回；
当搜索到账户时，要求用户输入密码；
若密码错误，输出"密码错误！"；
若密码正确，要求用户输入取款金额；
若取款金额大于余额，输出"余额不足。"；
若取款金额大于等于余额，将取款金额从余额减去，并将账户信息更新至文件。
*/
void GetMoney(Account*& Head,char& bank)
{
	cout << "请输入取款账号：";
	string num;
	cin >> num;
	Account* temp = SearchAccount(Head, num);
	if (temp == nullptr)
	{
		cout << "账户不存在。" << endl;
	}
	else
	{
		cout << "请输入密码：";
		int c_key;
		cin >> c_key;
		if (c_key != temp->a_key)
		{
			cout << "密码错误！" << endl;
		}
		else
		{
			cout << "请输入取款金额：";
			long long money_get;
			cin >> money_get;
			if (money_get > temp->a_sum)
			{
				cout << "余额不足。" << endl;
			}
			else
			{
				temp->a_sum -= money_get;
				InputAccount(Head, bank);
				cout << "取款成功。" << endl;
			}
		}
	}
}

/*
计算利息
当头指针为空指针时，输出"该银行不存在账户。"，返回；
当搜索不到账户，输出"账户不存在。"，返回；
当找到账户，要求输入存款到期日期；
若到期日期早于存款日期，输出"日期有误。"，返回；
若到期日期晚于存款日期或为存款日期当天，计算存款年数，根据活期或定期计算利息。
*/
void Interest(Account* Head)
{
	if (Head == nullptr)
	{
		cout << "该银行不存在账户。" << endl;
		return;
	}
	cout << "请输入您的账号：";
	string num;
	cin >> num;
	Account* result = SearchAccount(Head, num);
	if (result == nullptr)
	{
		cout << "未找到账户。" << endl;
		return;
	}
	if (result->a_state != "活期" and result->a_state != "定期")
	{
		cout << "无法识别存款类型" << endl;
		return;
	}
	cout << "请输入存款到期日期：";
	int date_arrive;
	cin >> date_arrive;
	if (date_arrive < result->a_date)
	{
		cout << "日期有误。" << endl;
		return;
	}
	int year0 = (date_arrive - result->a_date) / 10000;
	double year = year0;
	int left_res = result->a_date % 10000, left_arr = date_arrive % 10000;
	if (left_arr < left_res)
	{
		year -= 0.5;
	}
	else if (left_arr > left_res)
	{
		year += 0.5;
	}
	double s;
	if (result->a_state == "活期")
	{
		s = year * result->a_sum * 0.0035;
	}
	else
	{
		if (year <= 1)
		{
			s = year * result->a_sum * 0.0275;
		}
		else if (year <= 2)
		{
			s = result->a_sum * 0.0275 + (year - 1) * result->a_sum * 0.0335;
		}
		else if (year > 2)
		{
			s = result->a_sum * 0.0275 + result->a_sum * 0.0335 + (year - 2) * result->a_sum * 0.04;
		}
	}
	cout << fixed << setprecision(2) << "预计总利息为：" << s << "元" << endl;
}

/*
转账。
定义变量；
若收款方与转账方所在银行不存在账户，输出"当前/该银行不存在账户。"，返回；
若收款方所在银行与转账方所在银行相同，在当前链表内操作；
若收款方所在银行与转账方所在银行不同，打开收款方银行文件并导入至新链表；
要求输入转账方与收款方账户，若账户不正确，输出"您的/对方账户不存在。"，返回；
要求输入转账方密码，若密码错误，输出"密码错误！"，返回；
若账号均存在且密码正确，输入转账金额，若金额小于转账方余额，输出"余额不足。"；
若余额大于等于转账金额，从转账方余额减去转账金额，并向收款方余额加上转账金额，输出"转账成功。"，并将账户链表导入文件。
*/
void Transfer(Account*& Head,char& bank)
{
	if (Head == nullptr)
	{
		cout << "当前银行不存在账户。" << endl;
		return;
	}
	cout << "请输入对方账户的银行：";
	char bank_t;
	cin >> bank_t;
	if (bank_t == bank)
	{
		cout << "请输入对方账号：";
		string num_p;
		cin >> num_p;
		Account* q = SearchAccount(Head, num_p);
		if (q == nullptr)
		{
			cout << "对方账户不存在。" << endl;
			return;
		}
		else
		{
			Account* p = nullptr;
			cout << "请输入您的账号：";
			string num_q;
			cin >> num_q;
			p = SearchAccount(Head, num_q);
			if (p == nullptr)
			{
				cout << "您的账户不存在。" << endl;
				return;
			}
			else
			{
				cout << "请输入密码：";
				int key_q;
				cin >> key_q;
				if (key_q != p->a_key)
				{
					cout << "密码错误。" << endl;
					return;
				}
				else
				{
					cout << "请输入转账金额：";
					long long money_transfer_p;
					cin >> money_transfer_p;
					if (money_transfer_p > p->a_sum)
					{
						cout << "余额不足。" << endl;
					}
					else
					{
						p->a_sum -= money_transfer_p;
						q->a_sum += money_transfer_p;
						InputAccount(Head, bank);
						cout << "转账成功。" << endl;
					}
					return;
				}
			}
		}
	}
	ifstream fcin_t;
	ofstream fcout_t;
	switch (bank_t)
	{
	case 'a':fcin_t.open("a.txt", ios::in); break;
	case 'b':fcin_t.open("b.txt", ios::in); break;
	case 'c':fcin_t.open("c.txt", ios::in); break;
	case 'd':fcin_t.open("d.txt", ios::in); break;
	case 'e':fcin_t.open("e.txt", ios::in); break;
	default:cout << "不存在该银行。" << endl; return;
	}
	Account* Head_t = CreateAccount(fcin_t);
	if (Head_t == nullptr)
	{
		cout << "该银行内不存在账户。" << endl;
		return;
	}
	cout << "请输入对方账号：";
	string num_t;
	cin >> num_t;
	Account* q = SearchAccount(Head_t, num_t);
	if (q == nullptr)
	{
		cout << "对方账户不存在。" << endl;
		return;
	}
	else
	{
		Account* p = nullptr;
		cout << "请输入您的账号：";
		string num;
		cin >> num;
		p = SearchAccount(Head, num);
		if (p == nullptr)
		{
			cout << "您的账户不存在。" << endl;
			return;
		}
		else
		{
			cout << "请输入密码：";
			int key;
			cin >> key;
			if (key != p->a_key)
			{
				cout << "密码错误。" << endl;
				return;
			}
			else
			{
				cout << "请输入转账金额：";
				long long money_transfer;
				cin >> money_transfer;
				if (money_transfer > p->a_sum)
				{
					cout << "余额不足。" << endl;
				}
				else
				{
					p->a_sum -= money_transfer;
					q->a_sum += money_transfer;
					InputAccount(Head, bank);
					InputAccount(Head_t, bank_t);
					cout << "转账成功。" << endl;
				}
			}
		}
	}
}

/*
删除整个链表。
从堆区内依次删去各个账户数据，并将头指针赋值为空指针。
*/
void DeleteAll(Account*& Head)
{
	Account* p = Head;
	while (p != nullptr)
	{
		Account* temp = p->a_next;
		delete p;
		p = temp;
	}
	Head = nullptr;
}

/*
在控制台界面要求用户选择银行并输出各个功能模块的名称，要求用户选择功能，退卡或退出程序
*/
int main()
{
	ifstream fcin;
	cout << "请输入您的账户所在银行：";
	char bank;
	cin >> bank;
	switch (bank)
	{
	case 'a':fcin.open("a.txt", ios::in ); break;
	case 'b':fcin.open("b.txt", ios::in ); break;
	case 'c':fcin.open("c.txt", ios::in ); break;
	case 'd':fcin.open("d.txt", ios::in ); break;
	case 'e':fcin.open("e.txt", ios::in ); break;
	default:cout << "不存在该银行。" << endl; break;
	}
	Account* Head = CreateAccount(fcin);
	fcin.close();
	while (1)
	{
		cout << "-------------------------------------------------------" << endl;
		cout << "\n输入*展示所有账户；输入#退卡；输入p输出账户信息到文件\n1.查找账户；2.开户；3.销户\n4.修改密码；5.存款；6.取款\n7.转账；8.排序；9.计算利息\n输入0退出\n";
		char i;
		cin >> i;
		switch (i)
		{
		case '*':ShowAccount(Head); break;//展示账户信息
		case 'p':InputAccount(Head, bank); break;//将单链表导出到文件
		case '1':ShowSearchAccount(Head); break;//查找账户
		case '2':AddAccount(Head, bank); break;//开户
		case '3':DeleteAccount(Head, bank); break;//销户
		case '4':ChangeKey(Head, bank); break;//修改密码
		case '5':AddMoney(Head, bank); break;//存款
		case '6':GetMoney(Head, bank); break;//取款
		case '7':Transfer(Head, bank); break;//转账
		case '8': 
		{
			cout << "请选择排序依据（从小到大）：\n1.账号；2.姓名（非中文）；3.金额；4.开户日期" << endl;
			int j;
			cin >> j;
			switch (j)
			{
			case 1:SortAccount_Number(Head); break;
			case 2:SortAccount_Name(Head); break;
			case 3:SortAccount_Sum(Head); break;
			case 4:SortAccount_Date(Head); break;
			default:cout << "无法识别的字符。" << endl; break;
			}
			break;
		}
		case '9':Interest(Head); break;
		case '#':
		{
			DeleteAll(Head);
			cout << "退卡成功。" << endl;
			cout << "请输入您的账户所在银行：";
			cin >> bank;
			switch (bank)
			{
			case 'a':fcin.open("a.txt", ios::in); break;
			case 'b':fcin.open("b.txt", ios::in); break;
			case 'c':fcin.open("c.txt", ios::in); break;
			case 'd':fcin.open("d.txt", ios::in); break;
			case 'e':fcin.open("e.txt", ios::in); break;
			default:cout << "不存在该银行。" << endl; break;
			}
			Head = CreateAccount(fcin);
			fcin.close();
			break;
		}
		case '0':cout << "程序已退出。" << endl; return 0;//退出
		default:cout << "无法识别的字符，已默认退出。" << endl; return 0;//退出
		}
	}
	return 0;
}