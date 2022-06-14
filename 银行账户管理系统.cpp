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
��������أ�ʹ��С�ں�<�Ƚ����ַ�����Сʱ���ø÷�����
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
���ڱȽϣ��Ƚ�������λ����(yyyymmdd)ʱ���ø÷�����
*/
bool comp_date(int a, int b)//С����������ǰ
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
���ļ������˻���Ϣ��������
�������壻
���������û���˻��������"�����в������˻���"��
������˻����򽫸����˻�����Ϣ���뵽�������У�������ͷָ�롣
*/
Account* CreateAccount(ifstream& fcin)
{
	Account* Head = nullptr;
	Account* q = nullptr;
	if (fcin.peek() == -1)
	{
		cout << "�����в������˻���" << endl;
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
չʾ�����˺š�
���ͷָ��Ϊ��ָ�룬�����"�������ڲ������˺š�"��
�������壻
���ͷָ�벻Ϊ�գ�������������е��˺���Ϣ��
*/
void ShowAccount(Account*& Head)
{
	if (Head == nullptr)
	{
		cout << "�������ڲ������˺š�" << endl;
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
���˻���Ϣ�������ļ���
���ļ���
��������������������ļ���
�ر��ļ���
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
	default:cout << "�����ڴ����С�" << endl; return;
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
�����˺š�
�������壻
���ͷָ��Ϊ��ָ�룬������������Ӧ�˺ţ��򷵻ؿ�ָ�룻
����������˶�Ӧ�˺ţ��򷵻ظ��˺����ݵĵ�ַ��
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
������
�������壻
���������˺��Ѵ��ڣ����ӡ"�˻��Ѵ��ڡ�"��
��������ڣ��������˻���Ϣ�����˻��ӵ�����ĩβ�������˻������浽�ļ���
*/
void AddAccount(Account*& Head,char& bank)
{
	cout << "�����������˺ţ�";
	string num;
	cin >> num;
	Account* temp = SearchAccount(Head, num);
	if (temp != nullptr)
	{
		cout << "�˻��Ѵ��ڡ�" << endl;
	}
	else
	{
		Account* p = new Account;
		p->a_number = num;
		cout << "�������������Ա����롢���������ڡ��˻�״̬" << endl;
		cin >> p->a_name >> p->a_sex >> p->a_key >> p->a_sum >> p->a_date >> p->a_state;
		p->a_next = nullptr;
		if (Head == nullptr)
		{
			Head = p;
			cout << "�����ɹ���" << endl;
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
		cout << "�����ɹ���" << endl;
	}
}

/*
������
�������壻
���������˺Ų����ڣ����ӡ"�˻������ڡ�"��
������ڣ����������룻
���������������"�������"��
��������ȷ�����˻�������ɾ���������˻������浽�ļ���
*/
void DeleteAccount(Account*& Head,char& bank)
{
	if (Head == nullptr)
	{
		cout << "�������ڲ������˺š�" << endl;
		return;
	}
	cout << "�����������˺ţ�";
	string num;
	cin >> num;
	Account* temp = SearchAccount(Head, num);
	if (temp == nullptr)
	{
		cout << "�˻������ڡ�" << endl;
	}
	else
	{
		cout << "���������룺";
		int k;
		cin >> k;
		if (k != temp->a_key)
		{
			cout << "�������" << endl;
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
				cout << "�����ɹ�" << endl;
			}
			else if (p != nullptr)
			{
				p->a_next = temp->a_next;
				temp->a_sum = 0;
				delete temp;
				InputAccount(Head, bank);
				cout << "�����ɹ�" << endl;
			}
		}
	}
}

/*
���˺�����
�������壻
���ͷָ��Ϊ��ָ����������һ�����ݣ��򷵻أ�
������������ݣ���15λ�˺ŵĴ�С�Ը������ݽ���ѡ������
*/
void SortAccount_Number(Account*& Head)
{
	if (Head == nullptr)
	{
		cout << "�����в������˻���" << endl;
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
				min_ac = p;//min_acָ����������е���Сֵ
			}
			p = p->a_next;
		}
		Account* min_last = Head;//ָ��min_lastָ����Сֵ���ݵ�ǰһ������
		if (Head == min_ac)
		{
			min_last = nullptr;//�����Сֵ����ͷ����min_lastΪ��ָ��
		}
		else
		{
			while (min_last->a_next != min_ac)
			{
				min_last = min_last->a_next;
			}
		}
		if (sorted == nullptr)//�տ�ʼ����δ�ŵ�һ��
		{
			if (now_ac != min_ac and now_ac->a_next != min_ac)//��ͷ�������һ�����ݵ�ĳһ�����ݣ�����������һ���λ�ý���
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
			else if (now_ac->a_next == min_ac)//��ͷ������һ�����ݣ���������һ������ݽ���
			{
				Account* temp = min_ac->a_next;
				min_ac->a_next = now_ac;
				now_ac->a_next = temp;
				Head = min_ac;
			}
		}
		else//�����һ��
		{
			Account* now_last = Head;//�Ƿ���԰�now_last��sorted���
			while (now_last->a_next != now_ac)
			{
				now_last = now_last->a_next;
			}
			if (now_ac != min_ac and now_ac->a_next != min_ac)//����������һ������ݽ���λ��
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
	cout << "����ɰ��˺�����" << endl;
}

/*
����������
�������壻
���ͷָ��Ϊ��ָ����������һ�����ݣ��򷵻أ�
������������ݣ��������Ը������ݽ���ѡ������
*/
void SortAccount_Name(Account*& Head)
{
	if (Head == nullptr)
	{
		cout << "�����в������˻���" << endl;
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
				cout << "�ݲ�֧���Ժ�������" << endl;
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
				min_ac = p;//min_acָ����������е���Сֵ
			}
			p = p->a_next;
		}
		Account* min_last = Head;//ָ��min_lastָ����Сֵ���ݵ�ǰһ������
		if (Head == min_ac)
		{
			min_last = nullptr;//�����Сֵ����ͷ����min_lastΪ��ָ��
		}
		else
		{
			while (min_last->a_next != min_ac)
			{
				min_last = min_last->a_next;
			}
		}
		if (sorted == nullptr)//�տ�ʼ����δ�ŵ�һ��
		{
			if (now_ac != min_ac and now_ac->a_next != min_ac)//��ͷ�������һ�����ݵ�ĳһ�����ݣ�����������һ���λ�ý���//min_last!=now����
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
			else if (now_ac->a_next == min_ac)//��ͷ������һ�����ݣ���������һ������ݽ���
			{
				Account* temp = min_ac->a_next;
				min_ac->a_next = now_ac;
				now_ac->a_next = temp;
				Head = min_ac;
			}
		}
		else//�����һ��
		{
			Account* now_last = Head;//�Ƿ���԰�now_last��sorted���
			while (now_last->a_next != now_ac)
			{
				now_last = now_last->a_next;
			}
			if (now_ac != min_ac and now_ac->a_next != min_ac)//����������һ������ݽ���λ��
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
	cout << "����ɰ���������" << endl;
}

/*
���������
�������壻
���ͷָ��Ϊ��ָ����������һ�����ݣ��򷵻أ�
������������ݣ������Ը������ݽ���ѡ������
*/
void SortAccount_Sum(Account*& Head)
{
	if (Head == nullptr)
	{
		cout << "�����в������˻���" << endl;
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
				min_ac = p;//min_acָ����������е���Сֵ
			}
			p = p->a_next;
		}
		Account* min_last = Head;//ָ��min_lastָ����Сֵ���ݵ�ǰһ������
		if (Head == min_ac)
		{
			min_last = nullptr;//�����Сֵ����ͷ����min_lastΪ��ָ��
		}
		else
		{
			while (min_last->a_next != min_ac)
			{
				min_last = min_last->a_next;
			}
		}
		if (sorted == nullptr)//�տ�ʼ����δ�ŵ�һ��
		{
			if (now_ac != min_ac and now_ac->a_next != min_ac)//��ͷ�������һ�����ݵ�ĳһ�����ݣ�����������һ���λ�ý���//min_last!=now����
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
			else if (now_ac->a_next == min_ac)//��ͷ������һ�����ݣ���������һ������ݽ���
			{
				Account* temp = min_ac->a_next;
				min_ac->a_next = now_ac;
				now_ac->a_next = temp;
				Head = min_ac;
			}
		}
		else//�����һ��
		{
			Account* now_last = Head;//�Ƿ���԰�now_last��sorted���
			while (now_last->a_next != now_ac)
			{
				now_last = now_last->a_next;
			}
			if (now_ac != min_ac and now_ac->a_next != min_ac)//����������һ������ݽ���λ��
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
	cout << "����ɰ��������" << endl;

}

/*
��������������
�������壻
���ͷָ��Ϊ��ָ����������һ�����ݣ��򷵻أ�
������������ݣ��������Ⱥ�Ը������ݽ���ѡ������
*/
void SortAccount_Date(Account*& Head)
{
	if (Head == nullptr)
	{
		cout << "�����в������˻���" << endl;
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
				min_ac = p;//min_acָ����������е���Сֵ
			}
			p = p->a_next;
		}
		Account* min_last = Head;//ָ��min_lastָ����Сֵ���ݵ�ǰһ������
		if (Head == min_ac)
		{
			min_last = nullptr;//�����Сֵ����ͷ����min_lastΪ��ָ��
		}
		else
		{
			while (min_last->a_next != min_ac)
			{
				min_last = min_last->a_next;
			}
		}
		if (sorted == nullptr)//�տ�ʼ����δ�ŵ�һ��
		{
			if (now_ac != min_ac and now_ac->a_next != min_ac)//��ͷ�������һ�����ݵ�ĳһ�����ݣ�����������һ���λ�ý���//min_last!=now����
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
			else if (now_ac->a_next == min_ac)//��ͷ������һ�����ݣ���������һ������ݽ���
			{
				Account* temp = min_ac->a_next;
				min_ac->a_next = now_ac;
				now_ac->a_next = temp;
				Head = min_ac;
			}
		}
		else//�����һ��
		{
			Account* now_last = Head;//�Ƿ���԰�now_last��sorted���
			while (now_last->a_next != now_ac)
			{
				now_last = now_last->a_next;
			}
			if (now_ac != min_ac and now_ac->a_next != min_ac)//����������һ������ݽ���λ��
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
	cout << "����ɰ�������������" << endl;
}

/*
չʾ���������˺š�
�������壻
��ͷָ��Ϊ��ָ��ʱ�����"�������ڲ������˻���"��
����������ָ��Ϊ��ָ��ʱ�����"�˻������ڡ�"��
���������˺�ʱ������˺���Ϣ��
*/
void ShowSearchAccount(Account*& Head)
{
	string tempstr;
	cout << "�������ѯ���˺ţ�" << endl;
	cin >> tempstr;
	if (Head == nullptr)
	{
		cout << "�������ڲ������˻���" << endl;
		return;
	}
	Account* temp = SearchAccount(Head, tempstr);
	if (temp == nullptr)
	{
		cout << "�˻������ڡ�" << endl;
	}
	else
	{
		cout << "�˺ţ�" << temp->a_number << "\n������" << temp->a_name << "\n�Ա�" << temp->a_sex << "\n��" << temp->a_sum << "\n�������ڣ�" << temp->a_date << endl;
	}
}

/*
�޸����롣
���������
��ͷָ��Ϊ��ָ��ʱ�����"�����в������˻���"�����أ�
���������˻�ʱ��Ҫ���û�����ԭ���룻
������������"�������"��
��������ȷ��Ҫ���û����������룬���������������룬�����˻���Ϣ�������ļ���
*/
void ChangeKey(Account*& Head,char& bank)
{
	Account* p = Head;
	if (Head == nullptr)
	{
		cout << "�����в������˻���" << endl;
		return;
	}
	cout << "��������޸�������˺ţ�";
	string num;
	cin >> num;
	Account* temp = SearchAccount(Head, num);
	if (temp == nullptr)
	{
		cout << "�˻������ڡ�" << endl;
	}
	else
	{
		cout << "������ԭ���룺";
		int c_key;
		cin >> c_key;
		if (c_key != temp->a_key)
		{
			cout << "�������" << endl;
		}
		else
		{
			cout << "�����������룺";
			int new_key;
			cin >> new_key;
			temp->a_key = new_key;
			InputAccount(Head, bank);
			cout << "�޸ĳɹ���" << endl;
		}
	}
}

/*
��
�������壻
��ͷָ��Ϊ��ָ��ʱ�����"�����в������˻���"�����أ�
���������˻�ʱ��Ҫ���û��������룻
������������"�������"��
��������ȷ��Ҫ���û���������������ӵ��������˻���Ϣ�������ļ���
*/
void AddMoney(Account*& Head,char& bank)
{
	Account* p = Head;
	if (Head == nullptr)
	{
		cout << "�����в������˻���" << endl;
		return;
	}
	cout << "���������˺ţ�";
	string num;
	cin >> num;
	Account* temp = SearchAccount(Head, num);
	if (temp == nullptr)
	{
		cout << "�˻������ڡ�" << endl;
	}
	else
	{
		cout << "���������룺";
		int c_key;
		cin >> c_key;
		if (c_key != temp->a_key)
		{
			cout << "�������" << endl;
		}
		else
		{
			cout << "���������";
			long long money_add;
			cin >> money_add;
			temp->a_sum += money_add;
			InputAccount(Head, bank);
			cout << "���ɹ���" << endl;
		}
	}
}

/*
ȡ��
�������壻
��ͷָ��Ϊ��ָ��ʱ�����"�����в������˻���"�����أ�
�����������˻������"�˻������ڡ�"�����أ�
���������˻�ʱ��Ҫ���û��������룻
������������"�������"��
��������ȷ��Ҫ���û�����ȡ���
��ȡ������������"���㡣"��
��ȡ������ڵ�������ȡ���������ȥ�������˻���Ϣ�������ļ���
*/
void GetMoney(Account*& Head,char& bank)
{
	cout << "������ȡ���˺ţ�";
	string num;
	cin >> num;
	Account* temp = SearchAccount(Head, num);
	if (temp == nullptr)
	{
		cout << "�˻������ڡ�" << endl;
	}
	else
	{
		cout << "���������룺";
		int c_key;
		cin >> c_key;
		if (c_key != temp->a_key)
		{
			cout << "�������" << endl;
		}
		else
		{
			cout << "������ȡ���";
			long long money_get;
			cin >> money_get;
			if (money_get > temp->a_sum)
			{
				cout << "���㡣" << endl;
			}
			else
			{
				temp->a_sum -= money_get;
				InputAccount(Head, bank);
				cout << "ȡ��ɹ���" << endl;
			}
		}
	}
}

/*
������Ϣ
��ͷָ��Ϊ��ָ��ʱ�����"�����в������˻���"�����أ�
�����������˻������"�˻������ڡ�"�����أ�
���ҵ��˻���Ҫ������������ڣ�
�������������ڴ�����ڣ����"��������"�����أ�
�������������ڴ�����ڻ�Ϊ������ڵ��죬���������������ݻ��ڻ��ڼ�����Ϣ��
*/
void Interest(Account* Head)
{
	if (Head == nullptr)
	{
		cout << "�����в������˻���" << endl;
		return;
	}
	cout << "�����������˺ţ�";
	string num;
	cin >> num;
	Account* result = SearchAccount(Head, num);
	if (result == nullptr)
	{
		cout << "δ�ҵ��˻���" << endl;
		return;
	}
	if (result->a_state != "����" and result->a_state != "����")
	{
		cout << "�޷�ʶ��������" << endl;
		return;
	}
	cout << "������������ڣ�";
	int date_arrive;
	cin >> date_arrive;
	if (date_arrive < result->a_date)
	{
		cout << "��������" << endl;
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
	if (result->a_state == "����")
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
	cout << fixed << setprecision(2) << "Ԥ������ϢΪ��" << s << "Ԫ" << endl;
}

/*
ת�ˡ�
���������
���տ��ת�˷��������в������˻������"��ǰ/�����в������˻���"�����أ�
���տ����������ת�˷�����������ͬ���ڵ�ǰ�����ڲ�����
���տ����������ת�˷��������в�ͬ�����տ�����ļ���������������
Ҫ������ת�˷����տ�˻������˻�����ȷ�����"����/�Է��˻������ڡ�"�����أ�
Ҫ������ת�˷����룬������������"�������"�����أ�
���˺ž�������������ȷ������ת�˽������С��ת�˷������"���㡣"��
�������ڵ���ת�˽���ת�˷�����ȥת�˽������տ������ת�˽����"ת�˳ɹ���"�������˻��������ļ���
*/
void Transfer(Account*& Head,char& bank)
{
	if (Head == nullptr)
	{
		cout << "��ǰ���в������˻���" << endl;
		return;
	}
	cout << "������Է��˻������У�";
	char bank_t;
	cin >> bank_t;
	if (bank_t == bank)
	{
		cout << "������Է��˺ţ�";
		string num_p;
		cin >> num_p;
		Account* q = SearchAccount(Head, num_p);
		if (q == nullptr)
		{
			cout << "�Է��˻������ڡ�" << endl;
			return;
		}
		else
		{
			Account* p = nullptr;
			cout << "�����������˺ţ�";
			string num_q;
			cin >> num_q;
			p = SearchAccount(Head, num_q);
			if (p == nullptr)
			{
				cout << "�����˻������ڡ�" << endl;
				return;
			}
			else
			{
				cout << "���������룺";
				int key_q;
				cin >> key_q;
				if (key_q != p->a_key)
				{
					cout << "�������" << endl;
					return;
				}
				else
				{
					cout << "������ת�˽�";
					long long money_transfer_p;
					cin >> money_transfer_p;
					if (money_transfer_p > p->a_sum)
					{
						cout << "���㡣" << endl;
					}
					else
					{
						p->a_sum -= money_transfer_p;
						q->a_sum += money_transfer_p;
						InputAccount(Head, bank);
						cout << "ת�˳ɹ���" << endl;
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
	default:cout << "�����ڸ����С�" << endl; return;
	}
	Account* Head_t = CreateAccount(fcin_t);
	if (Head_t == nullptr)
	{
		cout << "�������ڲ������˻���" << endl;
		return;
	}
	cout << "������Է��˺ţ�";
	string num_t;
	cin >> num_t;
	Account* q = SearchAccount(Head_t, num_t);
	if (q == nullptr)
	{
		cout << "�Է��˻������ڡ�" << endl;
		return;
	}
	else
	{
		Account* p = nullptr;
		cout << "�����������˺ţ�";
		string num;
		cin >> num;
		p = SearchAccount(Head, num);
		if (p == nullptr)
		{
			cout << "�����˻������ڡ�" << endl;
			return;
		}
		else
		{
			cout << "���������룺";
			int key;
			cin >> key;
			if (key != p->a_key)
			{
				cout << "�������" << endl;
				return;
			}
			else
			{
				cout << "������ת�˽�";
				long long money_transfer;
				cin >> money_transfer;
				if (money_transfer > p->a_sum)
				{
					cout << "���㡣" << endl;
				}
				else
				{
					p->a_sum -= money_transfer;
					q->a_sum += money_transfer;
					InputAccount(Head, bank);
					InputAccount(Head_t, bank_t);
					cout << "ת�˳ɹ���" << endl;
				}
			}
		}
	}
}

/*
ɾ����������
�Ӷ���������ɾȥ�����˻����ݣ�����ͷָ�븳ֵΪ��ָ�롣
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
�ڿ���̨����Ҫ���û�ѡ�����в������������ģ������ƣ�Ҫ���û�ѡ���ܣ��˿����˳�����
*/
int main()
{
	ifstream fcin;
	cout << "�����������˻��������У�";
	char bank;
	cin >> bank;
	switch (bank)
	{
	case 'a':fcin.open("a.txt", ios::in ); break;
	case 'b':fcin.open("b.txt", ios::in ); break;
	case 'c':fcin.open("c.txt", ios::in ); break;
	case 'd':fcin.open("d.txt", ios::in ); break;
	case 'e':fcin.open("e.txt", ios::in ); break;
	default:cout << "�����ڸ����С�" << endl; break;
	}
	Account* Head = CreateAccount(fcin);
	fcin.close();
	while (1)
	{
		cout << "-------------------------------------------------------" << endl;
		cout << "\n����*չʾ�����˻�������#�˿�������p����˻���Ϣ���ļ�\n1.�����˻���2.������3.����\n4.�޸����룻5.��6.ȡ��\n7.ת�ˣ�8.����9.������Ϣ\n����0�˳�\n";
		char i;
		cin >> i;
		switch (i)
		{
		case '*':ShowAccount(Head); break;//չʾ�˻���Ϣ
		case 'p':InputAccount(Head, bank); break;//�������������ļ�
		case '1':ShowSearchAccount(Head); break;//�����˻�
		case '2':AddAccount(Head, bank); break;//����
		case '3':DeleteAccount(Head, bank); break;//����
		case '4':ChangeKey(Head, bank); break;//�޸�����
		case '5':AddMoney(Head, bank); break;//���
		case '6':GetMoney(Head, bank); break;//ȡ��
		case '7':Transfer(Head, bank); break;//ת��
		case '8': 
		{
			cout << "��ѡ���������ݣ���С���󣩣�\n1.�˺ţ�2.�����������ģ���3.��4.��������" << endl;
			int j;
			cin >> j;
			switch (j)
			{
			case 1:SortAccount_Number(Head); break;
			case 2:SortAccount_Name(Head); break;
			case 3:SortAccount_Sum(Head); break;
			case 4:SortAccount_Date(Head); break;
			default:cout << "�޷�ʶ����ַ���" << endl; break;
			}
			break;
		}
		case '9':Interest(Head); break;
		case '#':
		{
			DeleteAll(Head);
			cout << "�˿��ɹ���" << endl;
			cout << "�����������˻��������У�";
			cin >> bank;
			switch (bank)
			{
			case 'a':fcin.open("a.txt", ios::in); break;
			case 'b':fcin.open("b.txt", ios::in); break;
			case 'c':fcin.open("c.txt", ios::in); break;
			case 'd':fcin.open("d.txt", ios::in); break;
			case 'e':fcin.open("e.txt", ios::in); break;
			default:cout << "�����ڸ����С�" << endl; break;
			}
			Head = CreateAccount(fcin);
			fcin.close();
			break;
		}
		case '0':cout << "�������˳���" << endl; return 0;//�˳�
		default:cout << "�޷�ʶ����ַ�����Ĭ���˳���" << endl; return 0;//�˳�
		}
	}
	return 0;
}