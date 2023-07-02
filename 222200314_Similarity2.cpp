#include "222200314_Similarity1.h"

using namespace filesystem;
using namespace std;

int main()
{
    cout << "Copyright (c) 2023-2023 吴荣榜(222200314). All Rights Reserved." << endl << endl;

    printTime();
    cout << endl;
    //文件路径
    vector<string> CodeFilesUrl;

    //临时变量，用来接收某一份代码的所有代码片段
    //第一个元素存的是某一部分代码的源码，第二个元素存的是某一部分代码的化简版代码
    //tempCodePart[i]代表第i个片段的代码信息
    vector<pair<string, string> > tempCodePart;

    //student[i]代表第i个学生的代码文件信息
    //student[i][j]代表第i个学生的第j个片段的代码信息（未修改版和化简版）
    vector<vector<pair<string, string> > > student;

    //学生代码数量
    int studentNumber = 0;
    cout << "欢迎来到MEWWWの代码查重系统!!!" << endl << endl;
    cout << "请输入文件夹的地址，该程序将自动对指定目录下的所有代码进行两两比对查重: " << endl;
    setGreen;
    //文件夹路径可能带有引号，利用preFolderPath去过渡
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
    //如果文件夹不存在，则要求重新输入，直到正确为止
    while (!filesystem::exists(folderPath))
    {
        setRed;
        cout << "你输入的文件夹不存在，请重新输入！" << endl << endl;
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
    cout << "目标文件夹下有文件如下: " << endl;
    setWhite;

    //采用c++11的迭代器来遍历当前文件夹下的所有代码文件，并且获取所有文件的url
    for (const auto &entry: filesystem::directory_iterator(folderPath))
    {
        if (filesystem::is_regular_file(entry))
        {
            CodeFilesUrl.push_back(entry.path().string());
            studentNumber++;
            cout << "第 " + numToString(studentNumber) + " 个学生: " << CodeFilesUrl[studentNumber - 1]
                 << endl;
        }
    }

    //获得当前代码文件的所有代码片段的原始版和处理版
    for (int i = 0; i < studentNumber; i++)
    {
        tempCodePart = divideIntoPart(CodeFilesUrl[i]);
        student.push_back(tempCodePart);
    }

    setYellow;
    cout << endl << "查重率结果矩阵:" << endl;
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

                    //samePart的迭代器
                    //现在有两份文件经过了比较，it[i]即为两份代码第i处相似处的完整信息，包括到底是哪一部分相似，还有就是相似度
                    auto &it = samePart[i][j];
                    setYellow;
                    cout << endl << "存在 " + numToString(sizes) + " 个相似处" + "于第 " +
                            numToString(i + 1) + " 个学生的代码和第 " +
                            numToString(j + 1) + " 个学生的代码中: " << endl;

                    //k为遍历代码片段数
                    for (int k = 0; k < sizes; k++)
                    {
                        if (sizes != 1)
                        {
                            setYellow;
                            cout << "第 " + numToString(k + 1) + " 个相似处:" << endl << endl;
                        }
                        cout << "第 " + numToString(i + 1) + " 个学生的代码片段:" << endl;
                        setWhite;
                        cout << student[i][it[k].a].first << "\n\n";
                        setYellow;
                        cout << "第 " + numToString(j + 1) + " 个学生的代码片段:" << endl;
                        setWhite;
                        cout << student[j][it[k].b].first << endl;
                        setGreen;
                        cout << endl << "他们的相似度为 " << fixed << setprecision(2) << it[k].similarity * 100.0 << "%"
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
