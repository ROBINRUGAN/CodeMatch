#ifndef FOURTH_222200314_SIMILARITY1_H
#define FOURTH_222200314_SIMILARITY1_H
#define setRed SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12)
#define setGreen SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10)
#define setYellow SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14)
#define setWhite SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15)

#include <windows.h>
#include <bits/stdc++.h>
#include <filesystem>

using namespace std;

//代码相似度属性结构体
//一个单元代表两份代码的两个部分的相似情况
struct areaAttr
{
    //a为第一份代码的对应部分序号
    int a;

    //b为第二份代码的对应部分序号
    int b;

    //similarity代表两个部分的相似度
    double similarity;
};

//C++关键字
extern set<string> keywords;

//容器的关键字
extern set<string> container;

//存储两份代码相似部分的代码
extern vector<areaAttr> samePart[100][100];

//输出时间
void printTime();

//数字转字符串
string numToString(int number);

//初始化，去除注释和连续空格
string init(string code);

//代码进一步处理，抽象化变量名，函数，关键字，头文件
string analyze(string originCode);

// 预处理代码后将代码进行划分，分段
vector<pair<string, string> > divideIntoPart(const string &filename);

//最小编辑距离，采用dp算法
int minEditDistance(const string &firstText, const string &secondText);

//对于a或b而言，first是一个片段的代码，second这个片段代码的替换简化
//num1和num2是互相比较的两个的文件序号
double compare(const vector<pair<string, string> > &a, const vector<pair<string, string> > &b, int num1, int num2);


#endif //FOURTH_222200314_SIMILARITY1_H
