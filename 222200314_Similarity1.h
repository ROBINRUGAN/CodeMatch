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

//�������ƶ����Խṹ��
//һ����Ԫ�������ݴ�����������ֵ��������
struct areaAttr
{
    //aΪ��һ�ݴ���Ķ�Ӧ�������
    int a;

    //bΪ�ڶ��ݴ���Ķ�Ӧ�������
    int b;

    //similarity�����������ֵ����ƶ�
    double similarity;
};

//C++�ؼ���
extern set<string> keywords;

//�����Ĺؼ���
extern set<string> container;

//�洢���ݴ������Ʋ��ֵĴ���
extern vector<areaAttr> samePart[100][100];

//���ʱ��
void printTime();

//����ת�ַ���
string numToString(int number);

//��ʼ����ȥ��ע�ͺ������ո�
string init(string code);

//�����һ���������󻯱��������������ؼ��֣�ͷ�ļ�
string analyze(string originCode);

// Ԥ�������󽫴�����л��֣��ֶ�
vector<pair<string, string> > divideIntoPart(const string &filename);

//��С�༭���룬����dp�㷨
int minEditDistance(const string &firstText, const string &secondText);

//����a��b���ԣ�first��һ��Ƭ�εĴ��룬second���Ƭ�δ�����滻��
//num1��num2�ǻ���Ƚϵ��������ļ����
double compare(const vector<pair<string, string> > &a, const vector<pair<string, string> > &b, int num1, int num2);


#endif //FOURTH_222200314_SIMILARITY1_H
