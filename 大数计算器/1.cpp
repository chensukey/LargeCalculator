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
	string import; //输入
	string outport; //输出
	vector<string> res_import; //转换后的输入

public:
	calculator();
	~calculator();
	//输入 
	bool PutIn();
	//将输入的公式转换成逆波兰形式存储到vector
	bool Change();
	//得到结果
	void GetResult();
	//输出
	void PutOut();

	//计算
	string DoCalculator(const string &a, const string &b, const char &fuhao);

	//优先级判断 是否低于前面
	bool IsLow(const char &a, const char &b);
	//优先级计算
	int FirstCode(const char &a);
	//字符串分成整数和小数部分
	void DoCalBase(const string &a, const string &b, vector<int> &int_a_i, vector<int> &int_b_i, vector<int> &int_a_f, vector<int> &int_b_f);
	//字符串对其补0
	void DoToDuiqibuling(vector<int> &int_a_i, vector<int> &int_b_i, vector<int> &int_a_f, vector<int> &int_b_f);
	//字符串去掉.
	void DoToDel(int &n, const string &a, const string &b, vector<int> &int_a_i, vector<int> &int_b_i);
	void DoDelFront(string &a);//去掉前面的0
	void DoDelBack(string &a);//去掉后面的0
	//加
	string DoAdd(const string &a, const string &b);
	//减
	string DoSub(const string &a, const string &b);
	//乘
	string DoMul(const string &a, const string &b);
	//除
	string DoDiv(const string &a, const string &b);
	//次方
	string DoThepow(const string &a, const string &b);
	//阶乘
	string DoJiecheng(const string &a);
	//负号
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
	vector<string> temp; //用来临时存储操作符号的
	string temp_str = ""; //用来临时存储数字

	for (int i = 0; i < import.size(); i++)
	{
		string temp_fh = "";
		//数字
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
			//把整个数字压入
			if (temp_str != "")
			{
				res_import.push_back(temp_str);
				temp_str = "";
			}
			//弹出括号里面的符号
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

				//弹出左括号
				temp.pop_back();
			}
		}
		else if (import[i] == THEPOW || import[i] == JIECHENG || import[i] == MUL || import[i] == DIV || import[i] == ADD || import[i] == SUB || import[i] == FH)
		{
			//把整个数字压入
			if (temp_str != "")
			{
				res_import.push_back(temp_str);
				temp_str = "";
			}
			//如果是负数 则特殊处理
			if (import[i] == SUB)
			{
				if (i == 0 || import[i - 1] == LIFE || import[i - 1] == ADD || import[i - 1] == SUB || import[i - 1] == MUL || import[i - 1] == DIV || import[i - 1] == THEPOW || import[i - 1] == JIECHENG || import[i - 1] == FH)
				{
					//压入#代表负数符号
					import[i] = FH;
				}
			}
			//判断优先级 如果比前面的低 则弹出前面一个
			if (temp.size() > 0)
			{
				string fuhao = temp.at(temp.size() - 1); //前一个
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
			//压入这个符号
			temp_fh = import[i];
			temp.push_back(temp_fh);
		}
	}
	//把整个数字压入 用于最后一个字符是数字的情况
	if (temp_str != "")
	{
		res_import.push_back(temp_str);
		temp_str = "";
	}
	//将符号全部取出
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
	//转换成功与否
	if (res_import.size() > 0)
		return true;
	else
		return false;
}
void calculator::PutOut()
{
	cout << "计算结果为：" << outport.c_str() << endl;
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
	vector<string> temp; //用于临时计算结果用的栈
	string temp_str = "";//临时存储数字
	for (int i = 0; i < res_import.size(); i++)
	{
		if (res_import[i][0] == JIECHENG || res_import[i][0] == FH)  //如果是阶乘或者符号 则只需要一元
		{
			if (temp.size() < 1)
				return;
			string res = DoCalculator(temp[temp.size() - 1], "", res_import[i][0]);
			if (res == "")
				return;
			temp.pop_back();	 //弹出上一个数字
			temp.push_back(res); //压入计算后的结果
		}
		else if (res_import[i].size() == 1 && (res_import[i][0] == THEPOW || res_import[i][0] == MUL || res_import[i][0] == DIV || res_import[i][0] == ADD || res_import[i][0] == SUB))
		{
			if (temp.size() < 2)
				return;
			string res = DoCalculator(temp[temp.size() - 2], temp[temp.size() - 1], res_import[i][0]);
			if (res == "")
				return;
			temp.pop_back();    //弹出上一个数字
			temp.pop_back();    //弹出上一个数字
			temp.push_back(res);//压入计算后的结果
		}
		else  //数字
		{
			//直接压入临时栈
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

	//把数字的整数和小数部分分别分割
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

	//将小数部分对齐 
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
	//每N位分割
	int number = str_a_i.size() / FENGE + 1; //多少个元素
	int count = str_a_i.size() % FENGE;  //第一个元素有多少个字符
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

	number = str_b_i.size() / FENGE + 1; //多少个元素
	count = str_b_i.size() % FENGE;  //第一个元素有多少个字符
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
	number = str_a_f.size() / FENGE + 1; //多少个元素
	count = str_a_f.size() % FENGE;  //第一个元素有多少个字符
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

	number = str_b_f.size() / FENGE + 1; //多少个元素
	count = str_b_f.size() % FENGE;  //第一个元素有多少个字符
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
//字符串对其补0
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
//去掉小数点 记录以后小数点要在倒数第几个
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
	//每N位分割
	int number = str_a_i.size() / FENGE + 1; //多少个元素
	int count = str_a_i.size() % FENGE;  //第一个元素有多少个字符
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

	number = str_b_i.size() / FENGE + 1; //多少个元素
	count = str_b_i.size() % FENGE;  //第一个元素有多少个字符
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
//去掉前面的0
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
//去掉后面的0
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
//加法
string calculator::DoAdd(const string &a, const string &b)
{
	string f_str = "";
	string i_str = "";
	string is_fushu = "";

	vector<int> int_a_i; //a整数部分
	vector<int> int_a_f; //a小数部分
	vector<int> int_b_i; //b整数部分
	vector<int> int_b_f; //b小数部分

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

	//每N位分别相加
	int temp = 0; //进位的数
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
//减
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

	vector<int> int_a_i; //a整数部分
	vector<int> int_a_f; //a小数部分
	vector<int> int_b_i; //b整数部分
	vector<int> int_b_f; //b小数部分

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
//乘
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

	vector<int> int_a_i; //a整数部分
	vector<int> int_b_i; //b整数部分

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
//除
string calculator::DoDiv(const string &a, const string &b)
{
	return "2";
}
//次方
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
//阶乘
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
//负号
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
	cout << "请输入公式:" << endl;
	while (!cal.PutIn() || !cal.Change())
	{
		cout << "输入有误,请重新输入" << endl;
	}

	cal.GetResult();
	cal.PutOut();

	system("pause");
	return 0;
}