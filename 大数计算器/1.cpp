#include<iostream>
#include<vector>
#include<string>
#include<cstdio>

using namespace std;

#define LIFE '('
#define RIGHT ')'
#define THEPOW '^'
#define JIECHENG '!'
#define MUL '*'
#define DIV '/'
#define ADD '+'
#define SUB '-'
#define FH '#'
#define FENGE 4
#define FENGECHENG 10000
class calculator
{
private:
	string import; //����
	string outport; //���
	vector<string> res_import; //ת���������

public:
	calculator();
	~calculator();
	//���� 
	bool PutIn();
	//������Ĺ�ʽת�����沨����ʽ�洢��vector
	bool Change();
	//�õ����
	void GetResult();
	//���
	void PutOut();

	//����
	string DoCalculator(const string &a, const string &b, const char &fuhao);

	//���ȼ��ж� �Ƿ����ǰ��
	bool IsLow(const char &a, const char &b);
	//���ȼ�����
	int FirstCode(const char &a);
	//�ַ����ֳ�������С������
	void DoCalBase(const string &a, const string &b, vector<int> &int_a_i, vector<int> &int_b_i, vector<int> &int_a_f, vector<int> &int_b_f);
	//�ַ������䲹0
	void DoToDuiqibuling(vector<int> &int_a_i, vector<int> &int_b_i, vector<int> &int_a_f, vector<int> &int_b_f);
	//�ַ���ȥ��.
	void DoToDel(int &n, const string &a, const string &b, vector<int> &int_a_i, vector<int> &int_b_i);
	void DoDelFront(string &a);//ȥ��ǰ���0
	void DoDelBack(string &a);//ȥ�������0
	//��
	string DoAdd(const string &a, const string &b);
	//��
	string DoSub(const string &a, const string &b);
	//��
	string DoMul(const string &a, const string &b);
	//��
	string DoDiv(const string &a, const string &b);
	//�η�
	string DoThepow(const string &a, const string &b);
	//�׳�
	string DoJiecheng(const string &a);
	//����
	string DoFushu(const string &a);
};

calculator::calculator() :import(""), outport(""), res_import(NULL)
{

}
calculator::~calculator()
{

}
bool calculator::PutIn()
{
	import = "";
	getline(cin, import);
	if (import == "")
		return false;
	else
		return true;
}
bool calculator::Change()
{
	vector<string> temp; //������ʱ�洢�������ŵ�
	string temp_str = ""; //������ʱ�洢����

	for (int i = 0; i < import.size(); i++)
	{
		string temp_fh = "";
		//����
		if ((import[i] >= '0' && import[i] <= '9') || import[i] == '.')
		{
			temp_str.push_back(import[i]);
		}
		else if (import[i] == LIFE)
		{
			if (i > 0 && import[i - 1] != LIFE && import[i - 1] != THEPOW && import[i - 1] && JIECHENG && import[i - 1] != MUL && import[i - 1] != DIV && import[i - 1] != ADD && import[i - 1] != SUB && import[i - 1] != FH)
			{
				if (temp_str != "")
				{
					res_import.push_back(temp_str);
					temp_str = "";
				}
				temp.push_back("*");
			}
			temp_fh = import[i];
			temp.push_back(temp_fh);
		}
		else if (import[i] == RIGHT)
		{
			//����������ѹ��
			if (temp_str != "")
			{
				res_import.push_back(temp_str);
				temp_str = "";
			}
			//������������ķ���
			if (temp.size() > 0)
			{
				string fuhao = temp.at(temp.size() - 1);
				while (fuhao[0] != LIFE)
				{
					temp.pop_back();
					res_import.push_back(fuhao);
					if (temp.size() <= 0)
						break;
					fuhao = temp.at(temp.size() - 1);
				}

				//����������
				temp.pop_back();
			}
		}
		else if (import[i] == THEPOW || import[i] == JIECHENG || import[i] == MUL || import[i] == DIV || import[i] == ADD || import[i] == SUB || import[i] == FH)
		{
			//����������ѹ��
			if (temp_str != "")
			{
				res_import.push_back(temp_str);
				temp_str = "";
			}
			//����Ǹ��� �����⴦��
			if (import[i] == SUB)
			{
				if (i == 0 || import[i - 1] == LIFE || import[i - 1] == ADD || import[i - 1] == SUB || import[i - 1] == MUL || import[i - 1] == DIV || import[i - 1] == THEPOW || import[i - 1] == JIECHENG || import[i - 1] == FH)
				{
					//ѹ��#����������
					import[i] = FH;
				}
			}
			//�ж����ȼ� �����ǰ��ĵ� �򵯳�ǰ��һ��
			if (temp.size() > 0)
			{
				string fuhao = temp.at(temp.size() - 1); //ǰһ��
				while (IsLow(import[i], fuhao[0]))
				{
					temp.pop_back();
					if (fuhao[0] == SUB && res_import.at(res_import.size() - 1)[0] == SUB)
					{
						res_import.at(res_import.size() - 1)[0] = '+';
					}
					res_import.push_back(fuhao);
					if (temp.size() <= 0)
						break;
					fuhao = temp.at(temp.size() - 1);
				}
			}
			//ѹ���������
			temp_fh = import[i];
			temp.push_back(temp_fh);
		}
	}
	//����������ѹ�� �������һ���ַ������ֵ����
	if (temp_str != "")
	{
		res_import.push_back(temp_str);
		temp_str = "";
	}
	//������ȫ��ȡ��
	for (; temp.size() > 0;)
	{
		string fuhao = temp.at(temp.size() - 1);
		temp.pop_back();
		if (fuhao[0] == SUB && res_import.at(res_import.size() - 1)[0] == SUB)
		{
			res_import.at(res_import.size() - 1)[0] = '+';
		}
		res_import.push_back(fuhao);
		if (temp.size() <= 0)
			break;
		fuhao = temp.at(temp.size() - 1);
	}
	//ת���ɹ����
	if (res_import.size() > 0)
		return true;
	else
		return false;
}
void calculator::PutOut()
{
	cout << "������Ϊ��" << outport.c_str() << endl;
}
bool calculator::IsLow(const char &a, const char &b)
{
	if (FirstCode(a) < FirstCode(b))
		return true;
	else
		return false;
}
int calculator::FirstCode(const char &a)
{
	switch (a)
	{
	case LIFE:
	case RIGHT:
		return 0;
	case THEPOW:
		return 9;
	case JIECHENG:
		return 8;
	case MUL:
		return 5;
	case DIV:
		return 6;
	case ADD:
		return 2;
	case SUB:
		return 3;
	case FH:
		return 9;
	}
	return 0;
}
void calculator::GetResult()
{
	outport = "";
	vector<string> temp; //������ʱ�������õ�ջ
	string temp_str = "";//��ʱ�洢����
	for (int i = 0; i < res_import.size(); i++)
	{
		if (res_import[i][0] == JIECHENG || res_import[i][0] == FH)  //����ǽ׳˻��߷��� ��ֻ��ҪһԪ
		{
			if (temp.size() < 1)
				return;
			string res = DoCalculator(temp[temp.size() - 1], "", res_import[i][0]);
			if (res == "")
				return;
			temp.pop_back();	 //������һ������
			temp.push_back(res); //ѹ������Ľ��
		}
		else if (res_import[i].size() == 1 && (res_import[i][0] == THEPOW || res_import[i][0] == MUL || res_import[i][0] == DIV || res_import[i][0] == ADD || res_import[i][0] == SUB))
		{
			if (temp.size() < 2)
				return;
			string res = DoCalculator(temp[temp.size() - 2], temp[temp.size() - 1], res_import[i][0]);
			if (res == "")
				return;
			temp.pop_back();    //������һ������
			temp.pop_back();    //������һ������
			temp.push_back(res);//ѹ������Ľ��
		}
		else  //����
		{
			//ֱ��ѹ����ʱջ
			temp.push_back(res_import[i]);
		}
	}

	outport = temp[0];
	return;
}
string calculator::DoCalculator(const string &a, const string &b, const char &fuhao)
{
	string the_res = "";
	switch (fuhao)
	{
	case FH:
		the_res = DoFushu(a);
		break;
	case JIECHENG:
		the_res = DoJiecheng(a);
		break;
	case THEPOW:
		the_res = DoThepow(a, b);
		break;
	case MUL:
		the_res = DoMul(a, b);
		break;
	case DIV:
		the_res = DoDiv(a, b);
		break;
	case ADD:
		the_res = DoAdd(a, b);
		break;
	case SUB:
		the_res = DoSub(a, b);
		break;
	}
	return the_res;
}
void calculator::DoCalBase(const string &a, const string &b, vector<int> &int_a_i, vector<int> &int_b_i, vector<int> &int_a_f, vector<int> &int_b_f)
{
	string str_a_i = "";
	string str_b_i = "";
	string str_a_f = "";
	string str_b_f = "";

	int_a_i.clear();
	int_b_i.clear();
	int_a_f.clear();
	int_b_f.clear();

	//�����ֵ�������С�����ֱַ�ָ�
	bool is_i = true;
	for (int i = 0; i < a.size(); i++)
	{
		if (a[i] == '-')
			continue;
		if (a[i] == '.')
		{
			is_i = false;
			continue;
		}
		if (is_i)
		{
			str_a_i += a[i];
		}
		else
		{
			str_a_f += a[i];
		}
	}
	is_i = true;
	for (int i = 0; i < b.size(); i++)
	{
		if (b[i] == '-')
			continue;
		if (b[i] == '.')
		{
			is_i = false;
			continue;
		}
		if (is_i)
		{
			str_b_i += b[i];
		}
		else
		{
			str_b_f += b[i];
		}
	}

	//��С�����ֶ��� 
	DoDelBack(str_a_f);
	DoDelBack(str_b_f);
	int f_max = str_a_f.size() - str_b_f.size();
	if (f_max > 0)
	{
		for (int i = 0; i < f_max; i++)
		{
			str_b_f = str_b_f + "0";
		}
	}
	else if (f_max < 0)
	{
		f_max = -f_max;
		for (int i = 0; i < f_max; i++)
		{
			str_a_f = str_a_f + "0";
		}
	}
	int bunumber = str_a_f.size() % FENGE;
	if (bunumber > 0)
	{
		for (int i = 0; i < FENGE - bunumber; i++)
		{
			str_a_f = str_a_f + "0";
			str_b_f = str_b_f + "0";
		}
	}
	//ÿNλ�ָ�
	int number = str_a_i.size() / FENGE + 1; //���ٸ�Ԫ��
	int count = str_a_i.size() % FENGE;  //��һ��Ԫ���ж��ٸ��ַ�
	string str_temp = "";
	int now_count = 0;
	for (; now_count < count; now_count++)
	{
		str_temp = str_temp + str_a_i[now_count];
	}

	if (str_temp != "")
	{
		int_a_i.push_back(atoi(str_temp.c_str()));
		str_temp = "";
	}

	for (int j = 1; j < number; j++)
	{
		bool is_push = false;
		for (int i = 0; i < FENGE; i++, now_count++)
		{
			if (str_a_i[now_count] != '0')
				is_push = true;
			if (is_push)
				str_temp = str_temp + str_a_i[now_count];
		}
		if (str_temp == "")
			str_temp = "0";
		int_a_i.push_back(atoi(str_temp.c_str()));
		str_temp = "";
	}

	number = str_b_i.size() / FENGE + 1; //���ٸ�Ԫ��
	count = str_b_i.size() % FENGE;  //��һ��Ԫ���ж��ٸ��ַ�
	str_temp = "";
	now_count = 0;
	for (; now_count < count; now_count++)
	{
		str_temp = str_temp + str_b_i[now_count];
	}
	if (str_temp != "")
	{
		int_b_i.push_back(atoi(str_temp.c_str()));
		str_temp = "";
	}

	for (int j = 1; j < number; j++)
	{
		bool is_push = false;
		for (int i = 0; i < FENGE; i++, now_count++)
		{
			if (str_b_i[now_count] != '0')
				is_push = true;
			if (is_push)
				str_temp = str_temp + str_b_i[now_count];
		}
		if (str_temp == "")
			str_temp = "0";
		int_b_i.push_back(atoi(str_temp.c_str()));
		str_temp = "";
	}

	//f
	number = str_a_f.size() / FENGE + 1; //���ٸ�Ԫ��
	count = str_a_f.size() % FENGE;  //��һ��Ԫ���ж��ٸ��ַ�
	str_temp = "";
	now_count = 0;
	for (; now_count < count; now_count++)
	{
		str_temp = str_temp + str_a_f[now_count];
	}
	if (str_temp != "")
	{
		int_a_f.push_back(atoi(str_temp.c_str()));
		str_temp = "";
	}

	for (int j = 1; j < number; j++)
	{
		bool is_push = false;
		for (int i = 0; i < FENGE; i++, now_count++)
		{
			if (str_a_f[now_count] != '0')
				is_push = true;
			if (is_push)
				str_temp = str_temp + str_a_f[now_count];
		}
		if (str_temp == "")
			str_temp = "0";
		int_a_f.push_back(atoi(str_temp.c_str()));
		str_temp = "";
	}

	number = str_b_f.size() / FENGE + 1; //���ٸ�Ԫ��
	count = str_b_f.size() % FENGE;  //��һ��Ԫ���ж��ٸ��ַ�
	str_temp = "";
	now_count = 0;
	for (; now_count < count; now_count++)
	{
		str_temp = str_temp + str_b_f[now_count];
	}
	if (str_temp != "")
	{
		int_b_f.push_back(atoi(str_temp.c_str()));
		str_temp = "";
	}

	for (int j = 1; j < number; j++)
	{
		bool is_push = false;
		for (int i = 0; i < FENGE; i++, now_count++)
		{
			if (str_b_f[now_count] != '0')
				is_push = true;
			if (is_push)
				str_temp = str_temp + str_b_f[now_count];
		}
		if (str_temp == "")
			str_temp = "0";
		int_b_f.push_back(atoi(str_temp.c_str()));
		str_temp = "";
	}
}
//�ַ������䲹0
void calculator::DoToDuiqibuling(vector<int> &int_a_i, vector<int> &int_b_i, vector<int> &int_a_f, vector<int> &int_b_f)
{
	int i_max = int_a_i.size() - int_b_i.size();
	if (i_max > 0)
	{
		for (int i = 0; i < i_max; i++)
		{
			int_b_i.insert(int_b_i.begin(), 0);
		}
	}
	else if (i_max < 0)
	{
		i_max = -i_max;
		for (int i = 0; i < i_max; i++)
		{
			int_a_i.insert(int_a_i.begin(), 0);
		}
	}

	int f_max = int_a_f.size() - int_b_f.size();
	if (f_max > 0)
	{
		for (int i = 0; i < f_max; i++)
		{
			int_b_f.push_back(0);
		}
	}
	else if (f_max < 0)
	{
		f_max = -f_max;
		for (int i = 0; i < f_max; i++)
		{
			int_a_f.push_back(0);
		}
	}
}
//ȥ��С���� ��¼�Ժ�С����Ҫ�ڵ����ڼ���
void calculator::DoToDel(int &n, const string &a, const string &b, vector<int> &int_a_i, vector<int> &int_b_i)
{
	n = 0;
	string str_a_i = "";
	string str_b_i = "";

	int_a_i.clear();
	int_b_i.clear();

	bool is_dian = false;
	for (int i = 0; i < a.size(); i++)
	{
		if (a[i] == '.')
		{
			is_dian = true;
			continue;
		}
		if (is_dian)
			n++;

		str_a_i += a[i];
	}

	is_dian = false;
	for (int i = 0; i < b.size(); i++)
	{
		if (b[i] == '.')
		{
			is_dian = true;
			continue;
		}
		if (is_dian)
			n++;

		str_b_i += b[i];
	}
	DoDelFront(str_a_i);
	DoDelFront(str_b_i);
	//ÿNλ�ָ�
	int number = str_a_i.size() / FENGE + 1; //���ٸ�Ԫ��
	int count = str_a_i.size() % FENGE;  //��һ��Ԫ���ж��ٸ��ַ�
	string str_temp = "";
	int now_count = 0;
	for (; now_count < count; now_count++)
	{
		str_temp = str_temp + str_a_i[now_count];
	}

	if (str_temp != "")
	{
		int_a_i.push_back(atoi(str_temp.c_str()));
		str_temp = "";
	}

	for (int j = 1; j < number; j++)
	{
		bool is_push = false;
		for (int i = 0; i < FENGE; i++, now_count++)
		{
			if (str_a_i[now_count] != '0')
				is_push = true;
			if (is_push)
				str_temp = str_temp + str_a_i[now_count];
		}
		if (str_temp == "")
			str_temp = "0";
		int_a_i.push_back(atoi(str_temp.c_str()));
		str_temp = "";
	}

	number = str_b_i.size() / FENGE + 1; //���ٸ�Ԫ��
	count = str_b_i.size() % FENGE;  //��һ��Ԫ���ж��ٸ��ַ�
	str_temp = "";
	now_count = 0;
	for (; now_count < count; now_count++)
	{
		str_temp = str_temp + str_b_i[now_count];
	}

	if (str_temp != "")
	{
		int_b_i.push_back(atoi(str_temp.c_str()));
		str_temp = "";
	}

	for (int j = 1; j < number; j++)
	{
		bool is_push = false;
		for (int i = 0; i < FENGE; i++, now_count++)
		{
			if (str_b_i[now_count] != '0')
				is_push = true;
			if (is_push)
				str_temp = str_temp + str_b_i[now_count];
		}
		if (str_temp == "")
			str_temp = "0";
		int_b_i.push_back(atoi(str_temp.c_str()));
		str_temp = "";
	}
}
//ȥ��ǰ���0
void calculator::DoDelFront(string &a)
{
	if (a.size() <= 0)
		return;
	while (a[0] == '0')
	{
		a.erase(a.begin());

		if (a.size() <= 0)
			return;
	}
}
//ȥ�������0
void calculator::DoDelBack(string &a)
{
	if (a.size() <= 0)
		return;
	while (a[a.size() - 1] == '0')
	{
		a.erase(a.end() - 1);

		if (a.size() <= 0)
			return;
	}
}
//�ӷ�
string calculator::DoAdd(const string &a, const string &b)
{
	string f_str = "";
	string i_str = "";
	string is_fushu = "";

	vector<int> int_a_i; //a��������
	vector<int> int_a_f; //aС������
	vector<int> int_b_i; //b��������
	vector<int> int_b_f; //bС������

	string aa = a;
	string bb = b;
	if (a[0] == '-')
		aa.erase(aa.begin());
	if (b[0] == '-')
		bb.erase(bb.begin());

	if (a[0] == '-')
	{
		if (b[0] == '-')
		{
			is_fushu = "-";
		}
		else
		{
			return DoSub(bb, aa);
		}
	}
	else
	{
		if (b[0] == '-')
		{
			return DoSub(aa, bb);
		}
	}

	DoCalBase(aa, bb, int_a_i, int_b_i, int_a_f, int_b_f);
	DoToDuiqibuling(int_a_i, int_b_i, int_a_f, int_b_f);

	//ÿNλ�ֱ����
	int temp = 0; //��λ����
	for (int i = int_a_f.size() - 1; i >= 0; i--)
	{
		int res = int_a_f[i] + int_b_f[i] + temp;
		temp = int(res / FENGECHENG);

		char buffer[1024];
		sprintf_s(buffer, "%d\0", res % FENGECHENG);
		string str_temp(buffer);

		for (int x = str_temp.size(); x < FENGE; x++)
		{
			str_temp = "0" + str_temp;
		}

		f_str = str_temp + f_str;
	}

	for (int i = int_a_i.size() - 1; i >= 0; i--)
	{
		int res = int_a_i[i] + int_b_i[i] + temp;
		temp = int(res / FENGECHENG);

		char buffer[1024];
		sprintf_s(buffer, "%d\0", res % FENGECHENG);
		string str_temp(buffer);

		for (int x = str_temp.size(); x < FENGE; x++)
		{
			str_temp = "0" + str_temp;
		}

		i_str = str_temp + i_str;
	}
	if (temp > 0)
	{
		char buffer[1024];
		sprintf_s(buffer, "%d\0", temp % FENGECHENG);
		string str_temp(buffer);
		i_str = str_temp + i_str;

		temp = 0;
	}

	DoDelFront(i_str);
	DoDelBack(f_str);

	if (i_str == "")
		i_str = "0";
	if (f_str == "")
		f_str = "0";
	string res_str = "";
	if (f_str == "0")
		res_str = i_str;
	else
		res_str = i_str + "." + f_str;
	if (is_fushu == "-")
		res_str = is_fushu + res_str;
	return res_str;
}
//��
string calculator::DoSub(const string &a, const string &b)
{
	string is_fushu = "";
	string f_str = "";
	string i_str = "";

	string aa = a;
	string bb = b;
	if (a[0] == '-')
		aa.erase(aa.begin());
	if (b[0] == '-')
		bb.erase(bb.begin());

	vector<int> int_a_i; //a��������
	vector<int> int_a_f; //aС������
	vector<int> int_b_i; //b��������
	vector<int> int_b_f; //bС������

	if (a[0] == '-')
	{
		if (b[0] == '-')
		{
			return DoSub(bb, aa);
		}
		else
		{
			return DoAdd(aa, bb);
		}
	}
	else
	{
		if (b[0] == '-')
		{
			return DoAdd(aa, bb);
		}
	}

	DoCalBase(aa, bb, int_a_i, int_b_i, int_a_f, int_b_f);
	DoToDuiqibuling(int_a_i, int_b_i, int_a_f, int_b_f);

	if (is_fushu == "")
	{
		for (int i = int_a_i.size() - 1; i >= 0; i--)
		{
			if (int_a_i[i] < int_b_i[i])
			{
				is_fushu = "-";
				break;
			}
			else if (int_a_i[i] > int_b_i[i])
			{
				is_fushu = "+";
				break;
			}
		}
	}
	if (is_fushu == "")
	{
		for (int i = 0; i < int_a_f.size(); i++)
		{
			if (int_a_f[i] < int_b_f[i])
			{
				is_fushu = "-";
				break;
			}
			else if (int_a_f[i] > int_b_f[i])
			{
				is_fushu = "+";
				break;
			}
		}
	}

	int temp = 0;
	if (is_fushu == "+")
	{
		for (int i = int_a_f.size() - 1; i >= 0; i--)
		{
			int res = int_a_f[i] - temp - int_b_f[i];
			if (res < 0)
			{
				res = res + FENGECHENG;
				temp = 1;
			}
			else
			{
				temp = 0;
			}
			char buffer[1024];
			sprintf_s(buffer, "%d\0", res);
			string str_temp(buffer);

			for (int x = str_temp.size(); x < FENGE; x++)
			{
				str_temp = "0" + str_temp;
			}

			f_str = str_temp + f_str;
		}

		for (int i = int_a_i.size() - 1; i >= 0; i--)
		{
			int res = int_a_i[i] - temp - int_b_i[i];
			if (res < 0)
			{
				res = res + FENGECHENG;
				temp = 1;
			}
			else
			{
				temp = 0;
			}
			char buffer[1024];
			sprintf_s(buffer, "%d\0", res);
			string str_temp(buffer);

			for (int x = str_temp.size(); x < FENGE; x++)
			{
				str_temp = "0" + str_temp;
			}

			i_str = str_temp + i_str;
		}
	}
	else if (is_fushu == "-")
	{
		for (int i = int_a_f.size() - 1; i >= 0; i--)
		{
			int res = int_b_f[i] - temp - int_a_f[i];
			if (res < 0)
			{
				res = res + FENGECHENG;
				temp = 1;
			}
			else
			{
				temp = 0;
			}
			char buffer[1024];
			sprintf_s(buffer, "%d\0", res);
			string str_temp(buffer);

			for (int x = str_temp.size(); x < FENGE; x++)
			{
				str_temp = "0" + str_temp;
			}

			f_str = str_temp + f_str;
		}

		for (int i = int_a_i.size() - 1; i >= 0; i--)
		{
			int res = int_b_i[i] - temp - int_a_i[i];
			if (res < 0)
			{
				res = res + FENGECHENG;
				temp = 1;
			}
			else
			{
				temp = 0;
			}
			char buffer[1024];
			sprintf_s(buffer, "%d\0", res);
			string str_temp(buffer);

			for (int x = str_temp.size(); x < FENGE; x++)
			{
				str_temp = "0" + str_temp;
			}

			i_str = str_temp + i_str;
		}
	}
	else
	{
		i_str = "0";
		f_str = "0";
	}

	DoDelFront(i_str);
	DoDelBack(f_str);

	if (i_str == "")
		i_str = "0";
	if (f_str == "")
		f_str = "0";
	string res_str = "";
	if (f_str == "0")
		res_str = i_str;
	else
		res_str = i_str + "." + f_str;
	if (is_fushu == "-")
		res_str = is_fushu + res_str;
	return res_str;
}
//��
string calculator::DoMul(const string &a, const string &b)
{
	string f_str = "";
	string i_str = "";
	string is_fushu = "";

	string aa = a;
	string bb = b;
	if (a[0] == '-')
		aa.erase(aa.begin());
	if (b[0] == '-')
		bb.erase(bb.begin());

	if (a[0] == '-' && b[0] != '-')
		is_fushu = "-";
	if (b[0] == '-' && a[0] != '-')
		is_fushu = "-";

	vector<int> int_a_i; //a��������
	vector<int> int_b_i; //b��������

	int n = 0;
	DoToDel(n, aa, bb, int_a_i, int_b_i);

	for (int j = int_b_i.size() - 1; j >= 0; j--)
	{
		string res_temp = "";
		int temp = 0;
		for (int i = int_a_i.size() - 1; i >= 0; i--)
		{
			int res = int_a_i[i] * int_b_i[j] + temp;
			temp = int(res / FENGECHENG);

			char buffer[1024];
			sprintf_s(buffer, "%d\0", res % FENGECHENG);
			string str_temp(buffer);

			for (int x = str_temp.size(); x < FENGE; x++)
			{
				str_temp = "0" + str_temp;
			}

			res_temp = str_temp + res_temp;
		}
		if (temp > 0)
		{
			char buffer[1024];
			sprintf_s(buffer, "%d\0", temp % FENGECHENG);
			string str_temp(buffer);
			res_temp = str_temp + res_temp;

			temp = 0;
		}

		DoDelFront(res_temp);
		if (res_temp != "")
		{
			for (int k = 0; k < int_b_i.size() - 1 - j; k++)
			{
				string stemp = "";
				for (int x = 0; x < FENGE; x++)
					stemp = stemp + "0";
				res_temp = res_temp + stemp;
			}
			i_str = DoAdd(i_str, res_temp);
		}
	}
	int i_str_size = i_str.size();
	if (i_str_size <= n)
	{
		for (int i = i_str_size; i <= n; i++)
			i_str = "0" + i_str;
	}
	for (int i = 0; i < n; i++)
	{
		f_str = i_str[i_str.size() - 1] + f_str;
		i_str.erase(i_str.end() - 1);
	}

	DoDelFront(i_str);
	DoDelBack(f_str);

	if (i_str == "")
		i_str = "0";
	if (f_str == "")
		f_str = "0";
	string res_str = "";
	if (f_str == "0")
		res_str = i_str;
	else
		res_str = i_str + "." + f_str;

	if (is_fushu == "-")
		res_str = is_fushu + res_str;
	return res_str;
}
//��
string calculator::DoDiv(const string &a, const string &b)
{
	return "2";
}
//�η�
string calculator::DoThepow(const string &a, const string &b)
{
	string str = "";
	string aa = a;
	string bb = "";
	if (b[0] == '-')
		aa = DoDiv("1", aa);

	for (int i = 0; i < b.size(); i++)
	{
		if (b[i] == '.')
			break;
		if (b[i] >= '0' && b[i] <= '9')
			bb.push_back(b[i]);
	}
	if (bb == "")
		return str;

	int b_i = atoi(bb.c_str());

	for (int i = 0; i < b_i; i++)
	{
		if (str == "")
			str = "1";
		str = DoMul(str, aa);
	}

	return str;
}
//�׳�
string calculator::DoJiecheng(const string &aa)
{
	string a = aa;
	string is_fushu = "";
	if (a[0] == '-')
	{
		a.erase(a.begin());
		is_fushu = "-";
	}

	string i_str = "1";

	int int_temp = 1;
	int int_end = atoi(a.c_str());

	if (int_end == 0)
	{
		i_str = "";
		return i_str;
	}

	for (int i = 1; i < int_end;)
	{
		i++;
		char buffer[1024];
		sprintf_s(buffer, "%d\0", i);
		string str_temp(buffer);

		i_str = DoMul(i_str, str_temp);
	}
	i_str = is_fushu + i_str;
	return i_str;
}
//����
string calculator::DoFushu(const string &a)
{
	string str = "-";
	if (a[0] == '-')
	{
		str = a;
		str.erase(str.begin());
	}
	else
	{
		str = str + a;
	}
	return str;
}

int main()
{
	calculator cal;
	cout << "�����빫ʽ:" << endl;
	while (!cal.PutIn() || !cal.Change())
	{
		cout << "��������,����������" << endl;
	}

	cal.GetResult();
	cal.PutOut();

	system("pause");
	return 0;
}