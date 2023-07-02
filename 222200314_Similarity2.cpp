#include "222200314_Similarity1.h"

using namespace filesystem;
using namespace std;

int main()
{
    cout << "Copyright (c) 2023-2023 ���ٰ�(222200314). All Rights Reserved." << endl << endl;

    printTime();
    cout << endl;
    //�ļ�·��
    vector<string> CodeFilesUrl;

    //��ʱ��������������ĳһ�ݴ�������д���Ƭ��
    //��һ��Ԫ�ش����ĳһ���ִ����Դ�룬�ڶ���Ԫ�ش����ĳһ���ִ���Ļ�������
    //tempCodePart[i]�����i��Ƭ�εĴ�����Ϣ
    vector<pair<string, string> > tempCodePart;

    //student[i]�����i��ѧ���Ĵ����ļ���Ϣ
    //student[i][j]�����i��ѧ���ĵ�j��Ƭ�εĴ�����Ϣ��δ�޸İ�ͻ���棩
    vector<vector<pair<string, string> > > student;

    //ѧ����������
    int studentNumber = 0;
    cout << "��ӭ����MEWWW�δ������ϵͳ!!!" << endl << endl;
    cout << "�������ļ��еĵ�ַ���ó����Զ���ָ��Ŀ¼�µ����д�����������ȶԲ���: " << endl;
    setGreen;
    //�ļ���·�����ܴ������ţ�����preFolderPathȥ����
    string preFolderPath, folderPath;
    cin >> preFolderPath;
    setWhite;
    cout << endl;
    if (preFolderPath[0] == '"')
    {
        folderPath = preFolderPath.substr(1, preFolderPath.length() - 2);
    }
    else
    {
        folderPath = preFolderPath;
    }
    //����ļ��в����ڣ���Ҫ���������룬ֱ����ȷΪֹ
    while (!filesystem::exists(folderPath))
    {
        setRed;
        cout << "��������ļ��в����ڣ����������룡" << endl << endl;
        setGreen;
        cin >> preFolderPath;
        if (preFolderPath[0] == '"')
        {
            int i = 1;
            while (preFolderPath[i] != '"')
            {
                folderPath[i - 1] = preFolderPath[i];
            }
        }
        else
        {
            folderPath = preFolderPath;
        }
    }
    setYellow;
    cout << "Ŀ���ļ��������ļ�����: " << endl;
    setWhite;

    //����c++11�ĵ�������������ǰ�ļ����µ����д����ļ������һ�ȡ�����ļ���url
    for (const auto &entry: filesystem::directory_iterator(folderPath))
    {
        if (filesystem::is_regular_file(entry))
        {
            CodeFilesUrl.push_back(entry.path().string());
            studentNumber++;
            cout << "�� " + numToString(studentNumber) + " ��ѧ��: " << CodeFilesUrl[studentNumber - 1]
                 << endl;
        }
    }

    //��õ�ǰ�����ļ������д���Ƭ�ε�ԭʼ��ʹ����
    for (int i = 0; i < studentNumber; i++)
    {
        tempCodePart = divideIntoPart(CodeFilesUrl[i]);
        student.push_back(tempCodePart);
    }

    setYellow;
    cout << endl << "�����ʽ������:" << endl;
    setGreen;
    for (int i = 1; i <= studentNumber; i++)
    {
        cout << '\t' << i;
    }
    for (int i = 0; i < studentNumber; i++)
    {
        cout << endl << i + 1 << '\t';
        for (int j = 0; j < studentNumber; j++)
        {
            if (i != j)
            {
                printf("%.2lf%%\t", compare(student[i], student[j], i, j));
            }
            else
            {
                cout << "100.00%" << '\t';
            }
        }
    }
    setWhite;
    for (int i = 0; i < studentNumber; i++)
    {
        for (int j = i + 1; j < studentNumber; j++)
        {
            if (i != j)
            {
                if (!samePart[i][j].empty())
                {
                    cout << endl;
                    int sizes = samePart[i][j].size();

                    //samePart�ĵ�����
                    //�����������ļ������˱Ƚϣ�it[i]��Ϊ���ݴ����i�����ƴ���������Ϣ��������������һ�������ƣ����о������ƶ�
                    auto &it = samePart[i][j];
                    setYellow;
                    cout << endl << "���� " + numToString(sizes) + " �����ƴ�" + "�ڵ� " +
                            numToString(i + 1) + " ��ѧ���Ĵ���͵� " +
                            numToString(j + 1) + " ��ѧ���Ĵ�����: " << endl;

                    //kΪ��������Ƭ����
                    for (int k = 0; k < sizes; k++)
                    {
                        if (sizes != 1)
                        {
                            setYellow;
                            cout << "�� " + numToString(k + 1) + " �����ƴ�:" << endl << endl;
                        }
                        cout << "�� " + numToString(i + 1) + " ��ѧ���Ĵ���Ƭ��:" << endl;
                        setWhite;
                        cout << student[i][it[k].a].first << "\n\n";
                        setYellow;
                        cout << "�� " + numToString(j + 1) + " ��ѧ���Ĵ���Ƭ��:" << endl;
                        setWhite;
                        cout << student[j][it[k].b].first << endl;
                        setGreen;
                        cout << endl << "���ǵ����ƶ�Ϊ " << fixed << setprecision(2) << it[k].similarity * 100.0 << "%"
                             << endl;
                        setYellow;
                        cout << "=================================================================" << endl;
                        setWhite;
                    }
                }
            }
        }
    }
    system("pause");
    return 0;
}
