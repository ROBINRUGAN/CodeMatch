#include "222200314_Similarity1.h"

//C++关键字
set<string> keywords =
        {
                "int", "double", "float", "char", "short", "long", "using", "namespace", "bool", "auto", "typeof",
                "class",
                "static", "return",
                "goto", "struct", "cout", "cin", "scanf", "printf", "get", "put", "in", "out", "ios", "std", "pair",
                "string"
        };

//容器的关键字
set<string> container =
        {
                "set", "map", "vector", "unordered_set", "unordered_map"
        };

//存储两份代码相似部分的代码
vector<areaAttr> samePart[100][100];

string numToString(int number)
{
    char tempChar;
    string result;
    while (number)
    {
        tempChar = number % 10 + '0';
        number /= 10;
        result += tempChar;
    }
    reverse(result.begin(), result.end());
    return result;
}

string init(string code)
{
    //存放初始化后的的代码
    string modifyCode = "1 ";
    int row = 1;
    for (int i = 0; i < code.length(); i++)
    {
        //把一些连续的空格和制表符全部规范成单空格
        if (code[i] == ' ' || code[i] == '\t')
        {
            modifyCode += ' ';
            while (code[i + 1] == ' ' || code[i + 1] == '\t')
            {
                i++;
            }
        }
            //遇到换行就另起一行，并补上行号
        else if (code[i] == '\n')
        {
            row++;
            modifyCode += '\n' + numToString(row) + ' ';
        }
            //如果遇到了行注释，则直接跳过本行
        else if (code[i] == '/' && code[i + 1] == '/')
        {
            while (code[i + 1] != '\n')
            {
                i++;
            }
        }
            //如果遇到了块注释，则直接掠过这些部分
        else if (code[i] == '/' && code[i + 1] == '*')
        {
            while (!(code[i - 1] == '*' && code[i] == '/'))
            {
                i++;
                if (code[i] == '\n')
                {
                    row++;
                }
            }
        }
            //正常的代码直接加即可
        else
        {
            modifyCode += code[i];
        }
    }
    return modifyCode;
}

string analyze(string originCode)
{
    //最终的处理完的代码
    string resultCode;

    //可能的关键字名，变量名，函数名等
    string name;

    //处理完多行代码和去除行号的代码
    string modifyCode;

    //用来保存圆括号或者花括号里的代码的，进行递归抽象化
    string areaTmp;

    //用来记录可能变量名的两个下标
    int right = 0, left = 0;

    //开始初步预处理
    for (int i = 0; i < originCode.length(); i++)
    {
        //在代码用反斜杠连接的时候，跳过空格和换行，把代码弄成一行
        if (originCode[i] == '\\')
        {
            //用来记录过渡行，最后更新有效下标
            int tempPos = i + 1;
            while (originCode[tempPos] == ' ')
            {
                tempPos++;
            }
            if (originCode[tempPos] == '\n')
            {
                i = tempPos + 1;
            }
        }
        //把每一行的行号去掉
        if (i == 0 || originCode[i - 1] == '\n')
        {
            while (isdigit(originCode[i]))
            {
                i++;
            }
            while (originCode[i] == ' ')
            {
                i++;
            }
        }
        //注入有效字符
        modifyCode += originCode[i];
    }

    //开始进行替换操作的核心代码
    while (right < modifyCode.length())
    {
        //可能遇到了关键字或变量名，进行进一步的判断
        if (isalpha(modifyCode[right]) || modifyCode[right] == '_')
        {
            //记录一下初始坐标
            left = right;

            //获取整个疑似变量名
            while (isalnum(modifyCode[right]) || modifyCode[right] == '_')
            {
                right++;
            }

            //将其分割出来
            name = modifyCode.substr(left, right - left);

            //如果这是一个关键字
            if (keywords.count(name))
            {
                resultCode += "k";
                name = "";
            }
                //如果这是一个容器类型字段
            else if (container.count(name))
            {
                resultCode += "c";
                name = "";
            }
        }

            //我们上面没有对变量名的情况进行处理，但是搜索到的变量名会存储在tmp中
            //因为变量会有一些四则运算和逻辑运算操作，所以遇到这些符号的话说明我们遇到了变量
            //赋值运算，说明我们遇到了变量名
        else if (modifyCode[right] == '=')
        {
            right++;
            //如果有东西，说明捕获到了变量名
            if (!name.empty())
            {
                resultCode += "v";
                name = "";
            }
            //去除掉连续空格和换行
            while (modifyCode[right + 1] == ' ' || modifyCode[right + 1] == '\n')
            {
                right++;
            }
            //如果能遇到第二个等号，说明这是个相等运算符，要补上==
            if (modifyCode[right] == '=')
            {
                resultCode += "==";
            }
                //否则就是普通的赋值运算符
            else
            {
                resultCode += "=";
            }
            //处理完之后往后走一步，进入新部分判断
            right++;
        }

            //接下来是加法的情况，和赋值的情况类似
        else if (modifyCode[right] == '+')
        {
            right++;
            if (!name.empty())
            {
                resultCode += "v";
                name = "";
            }
            while (modifyCode[right + 1] == ' ' || modifyCode[right + 1] == '\n')
            {
                right++;
            }
            //遇到了+=
            if (modifyCode[right] == '=')
            {
                resultCode += "+=";
            }
                //遇到了++
            else if (modifyCode[right] == '+')
            {
                resultCode += "++";
            }
                //其他情况就是只有一个+
            else
            {
                resultCode += '+';
            }
            right++;
        }

            //减号和加法类似
        else if (modifyCode[right] == '-')
        {
            right++;
            if (!name.empty())
            {
                resultCode += "v";
                name = "";
            }
            while (modifyCode[right + 1] == ' ' || modifyCode[right + 1] == '\n')
            {
                right++;
            }
            if (modifyCode[right] == '=')
            {
                resultCode += "-=";
            }
            else if (modifyCode[right] == '-')
            {
                resultCode += "--";
            }
            else
            {
                resultCode += '-';
            }
        }

            //乘号和加法类似
        else if (modifyCode[right] == '*')
        {
            right++;
            if (!name.empty())
            {
                resultCode += "v";
                name = "";
            }
            while (modifyCode[right + 1] == ' ' || modifyCode[right + 1] == '\n')
            {
                right++;
            }
            if (modifyCode[right] == '=')
            {
                resultCode += "*=";
            }
            else
            {
                resultCode += '*';
            }
            right++;
        }

            //除号和加法类似
        else if (modifyCode[right] == '/')
        {
            right++;
            if (!name.empty())
            {
                resultCode += "v";
                name = "";
            }
            while (modifyCode[right + 1] == ' ' || modifyCode[right + 1] == '\n')
            {
                right++;
            }
            if (modifyCode[right] == '=')
            {
                resultCode += "/=";
            }
            else
            {
                resultCode += '/';
            }
            right++;
        }

            //接下来处理for if等语句或者函数的情况
        else if (modifyCode[right] == '(')
        {
            //用来计算括号匹配数
            int count = 1;
            left = right + 1;

            //把括号匹配完
            while (count)
            {
                right++;
                if (modifyCode[right] == '(')
                {
                    count++;
                }
                else if (modifyCode[right] == ')')
                {
                    count--;
                }
            }
            //如果有东西，则替换成f()
            if (!name.empty())
            {
                resultCode += "f(";
                name = "";
            }
            //套娃一下
            areaTmp = analyze(modifyCode.substr(left, right - left));
            resultCode += areaTmp;
            resultCode += ')';
            right++;
        }

            //接下来处理数组的情况，说明也是个变量
        else if (modifyCode[right] == '[')
        {
            //用来计算括号匹配数
            int count = 1;
            left = right + 1;
            while (count)
            {
                right++;
                if (modifyCode[right] == '[')
                {
                    count++;
                }
                else if (modifyCode[right] == ']')
                {
                    count--;
                }
            }
            if (!name.empty())
            {
                resultCode += "v";
                name = "";
            }
            resultCode += "[";
            areaTmp = analyze(modifyCode.substr(left, right - left));
            resultCode += areaTmp;
            resultCode += ']';
            right++;
        }

            //接下来就是普通的函数体或者代码块语句的递归调用
        else if (modifyCode[right] == '{')
        {
            int count = 1;
            left = right + 1;
            while (count)
            {
                right++;
                if (modifyCode[right] == '{')
                {
                    count++;
                }
                else if (modifyCode[right] == '}')
                {
                    count--;
                }
            }
            resultCode += '{';
            areaTmp = analyze(modifyCode.substr(left, right - left));
            resultCode += areaTmp;
            resultCode += '}';
            right++;
        }

            //接下来是双引号的处理，将字符串抽象成s
        else if (modifyCode[right] == '"')
        {
            right++;
            while (modifyCode[right] != '"')
            {
                right++;
            }
            resultCode += "s";
            right++;
        }

            //接下来是单引号的处理，将字符抽象成s
        else if (modifyCode[right] == '\'')
        {
            right++;
            while (modifyCode[right] != '\'')
            {
                right++;
            }
            resultCode += "s";
            right++;
        }

            //遇到了逗号或者分号的话，进行判断
        else if (modifyCode[right] == ',' || modifyCode[right] == ';')
        {
            if (!name.empty())
            {
                if (keywords.count(name))
                {
                    resultCode += "k";
                }
                else if (container.count(name))
                {
                    resultCode += "c";
                }
                else
                {
                    resultCode += "v";
                }
                name = "";
            }
            resultCode += modifyCode[right], right++;
        }

            //数字抽象化，其中特殊考虑16进制的数字
        else if (isdigit(modifyCode[right]))
        {
            right++;
            if (modifyCode[right] == 'x')
            {
                right++;
                while (isxdigit(modifyCode[right]))
                {
                    right++;
                }
                resultCode += "n";
            }
            else
            {
                while (isdigit(modifyCode[right]) || modifyCode[right] == '.' || modifyCode[right] == 'e')
                {
                    right++;
                }
                resultCode += "n";
            }
        }

            //小于号判断，判断是输入运算符，还是比较运算符
        else if (modifyCode[right] == '<')
        {
            right++;
            if (!name.empty())
            {
                resultCode += "v", name = "";
            }
            if (modifyCode[right] == '=')
            {
                right++;
                resultCode += "<=";
            }
            else if (modifyCode[right] == '<')
            {
                right++;
                resultCode += "<<";
            }
            else if (container.count(name))
            {
                int t = 1;
                left = right;
                resultCode += "c<";
                while (t)
                {
                    if (modifyCode[right] == '<')
                    {
                        t++;
                    }
                    else if (modifyCode[right] == '>')
                    {
                        t--;
                    }
                    right++;
                }
                resultCode += '<';
                resultCode += analyze(modifyCode.substr(left, right - left));
                resultCode += '>';
            }
            else
            {
                resultCode += '<';
            }
        }

            //大于号判断，判断是输入运算符，还是比较运算符
        else if (modifyCode[right] == '>')
        {
            right++;
            if (!name.empty())
            {
                resultCode += "v", name = "";
            }
            if (modifyCode[right] == '=')
            {
                resultCode += ">=";
                right++;
            }
            else if (modifyCode[right] == '>')
            {
                right++, resultCode += ">>";
            }
            else
            {
                resultCode += ">";
            }
        }

            //其他处理
        else
        {
            left = right;

            //处理头文件
            if (modifyCode[right] == '#')
            {
                right++;
                resultCode += "#";
                while (isspace(modifyCode[right]))
                {
                    right++;
                }
                while (modifyCode[right] != '\n')
                {
                    right++;
                }
                resultCode += "h";
            }

                //三目运算符处理
            else if (modifyCode[right] == '?')
            {
                right++;
                if (!name.empty())
                {
                    resultCode += "v";
                }
                resultCode += "?";
                while (isspace(modifyCode[right]))
                {
                    right++;
                }
                left = right;
                while (modifyCode[right] != ':')
                {
                    right++;
                }
                resultCode += analyze(modifyCode.substr(left, right - left));
                left = right++;
                resultCode += ":";
                while (modifyCode[right] != ';')
                {
                    right++;
                }
                resultCode += analyze(modifyCode.substr(left, right - left));
                resultCode += ';';
            }

                //作用域运算符处理
            else if (modifyCode[right] == ':' && modifyCode[right + 1] == ':')
            {
                right += 2;
                resultCode += "::";
            }

                //其他的普通字符直接添加
            else
            {
                right++;
                resultCode += modifyCode[right - 1];
            }
        }

        //去除行末空格
        if (isspace(modifyCode[right]))
        {
            right++;
        }

        //如果我已经到文件末尾，但是还存在变量名，例如continue这种
        if (right == modifyCode.length())
        {
            if (!name.empty())
            {
                if (keywords.count(name))
                {
                    resultCode += "k";
                }
                else if (container.count(name))
                {
                    resultCode += "c";
                }
                else
                {
                    resultCode += "v";
                }
            }
        }
    }
    return resultCode;
}

vector<pair<string, string> > divideIntoPart(const string &filename)
{
    //代码的初始片段和修改后片段
    vector<pair<string, string> > areas;

    // originCode存的是代码源码，
    // modifyCode存的是预处理后的代码（加上行号、去除连续空格、去除注释）
    string originCode, modifyCode;

    // circleBracket是记录之前十分出现过圆括号，
    // bigBracket是记录是否出现过大括号，
    // 两个都有说明是函数，
    // 只有大括号没有圆括号说明是结构体
    bool circleBracket, bigBracket;

    //读取文件，并且存放在originCode
    ifstream file;
    file.open(filename, ios::in);
    if (!file)
    {
        cout << "无法读取文件: " + filename << endl;
        return areas;
    }
    originCode = "";
    while (!file.eof())
    {
        originCode += file.get();
    }

    // 清除多余空格和注释
    modifyCode = init(originCode);

    //代码字符下标指针
    int position = 0;

    //第二个是局部下标指针，用来在括号那边计算
    int temp = 0;

    //代码分块的起始下标
    int start = 0;

    //代码分块的终点下标
    int end = 0;

    //lineNum是当前行号
    int lineNum = 1;

    //sLineNum是起始处行号
    int sLineNum = 1;

    //进行代码的划分工作
    while (position < modifyCode.length())
    {
        //计算行数
        if (modifyCode[position - 1] == '\n')
        {
            lineNum++;
        }
        //有小括号又有大括号，说明这是一个函数
        if (bigBracket && circleBracket)
        {
            end = position - 1;

            //把空行和回车全部略过
            while (modifyCode[start] == ' ' || modifyCode[start] == '\n')
            {
                if (modifyCode[start] == '\n')
                {
                    sLineNum++;
                }
                start++;
            }

            //如果当前start位为数字，就说明start位就是行号开始，就不用加行号。如果start位不是数字，那拆分后第一行前面要加上行号
            //避免有种投机取巧的代码，把代码压在同一行
            if (isdigit(modifyCode[start]))
            {
                areas.emplace_back(modifyCode.substr(start, end - start + 1), "");
            }
            else
            {
                areas.emplace_back(numToString(sLineNum) + ' ' + modifyCode.substr(start, end - start + 1), "");
            }

            //更新新的起始行和起始坐标
            start = end + 1;
            sLineNum = lineNum;

            //清零
            bigBracket = false;
            circleBracket = false;
        }

            //没有小括号但是有大括号，说明是结构体或者类
        else if (!circleBracket && bigBracket)
        {
            //因为他们比普通函数多了个分号，所以继续把分号读掉
            while (modifyCode[position] != ';')
            {
                position++;
            }
            end = position;

            //去掉空格和换行
            while (modifyCode[start] == ' ' || modifyCode[start] == '\n')
            {
                if (modifyCode[start] == '\n')
                {
                    sLineNum++;
                }
                start++;
            }
            //如果当前start位为数字，就说明start位就是行号开始，就不用加行号。如果start位不是数字，那拆分后第一行前面要加上行号
            if (isdigit(modifyCode[start]))
            {
                areas.emplace_back(modifyCode.substr(start, end - start + 1), "");
            }
            else
            {
                areas.emplace_back(numToString(sLineNum) + ' ' + modifyCode.substr(start, end - start + 1), "");
            }
            start = end + 1;
            sLineNum = lineNum;
            bigBracket = 0;
        }

            //遇到了普通语句的分号，那么就及时更新end
        else if (modifyCode[position] == ';')
        {
            end = position;
        }

            //把圆括号的部分全部略掉，更新position和lineNum
        else if (modifyCode[position] == '(')
        {
            temp = position;
            int t = 1;
            while (t)
            {
                position++;
                if (modifyCode[position] == '(')
                {
                    t++;
                }
                else if (modifyCode[position] == ')')
                {
                    t--;
                }
                if (modifyCode[position - 1] == '\n')
                {
                    lineNum++;
                }
            }
            temp = position + 1;
            circleBracket = true;
        }

            //把大括号的部分全部略掉，更新position和lineNum
        else if (modifyCode[position] == '{')
        {
            //正常情况下start会被更新成end+1，所以如果中间有夹杂一些其他语句的话，我的end就会比start大
            //我们把这些语句全部塞到第一部分
            if (end > start)
            {
                if (areas.empty())
                {
                    areas.emplace_back(modifyCode.substr(start, end - start + 1), "");
                }
                else
                {
                    while (modifyCode[start] == ' ' || modifyCode[start] == '\n')
                    {
                        if (modifyCode[start] == '\n')
                        {
                            sLineNum++;
                        }
                        start++;
                    }
                    if (isdigit(modifyCode[start]))
                    {
                        areas[0].first += '\n' + modifyCode.substr(start, end - start + 1);
                    }
                    else
                    {
                        areas[0].first += '\n' + numToString(sLineNum) + ' ' +
                                modifyCode.substr(start, end - start + 1);
                    }
                }
            }
            temp = position;
            start = end + 1;

            //去除空格
            while (isspace(modifyCode[start]))
            {
                start++;
            }
            sLineNum = lineNum;

            //处理括号匹配
            int t = 1;
            while (t)
            {
                position++;
                if (modifyCode[position] == '{')
                {
                    t++;
                }
                else if (modifyCode[position] == '}')
                {
                    t--;
                }
                if (modifyCode[position - 1] == '\n')
                {
                    lineNum++;
                }
            }
            end = position;
            bigBracket = true;
        }

        //如果已经到了最后一位，就把剩下的部分算一个
        if (position == modifyCode.length() - 1)
        {
            //略掉空格和回车
            while (modifyCode[start] == ' ' || modifyCode[start] == '\n')
            {
                if (modifyCode[start] == '\n')
                {
                    sLineNum++;
                }
                start++;
            }

            //如果是大括号组成的，遇到末尾另起一行并且补充行号
            if (bigBracket)
            {
                if (isdigit(modifyCode[start]))
                {
                    areas.emplace_back(modifyCode.substr(start, position - start + 1), "");
                }
                else
                {
                    areas.emplace_back(numToString(sLineNum) + ' ' + modifyCode.substr(start, position - start + 1),
                                       "");
                }
            }

                //其他情况的代码块的话，全部塞到第一部分
            else
            {
                if (isdigit(modifyCode[start]))
                {
                    areas[0].first += '\n' + modifyCode.substr(start, position - start + 1);
                }
                else
                {
                    areas[0].first += '\n' + numToString(sLineNum) + ' ' +
                            modifyCode.substr(start, position - start + 1);
                }
            }
        }
        position++;
    }

    //调用analyze，将原来的代码加工后存到second里去
    for (auto &area: areas)
    {
        area.second = analyze(area.first);
    }
    return areas;
}

int minEditDistance(const string &firstText, const string &secondText)
{
    int m = firstText.length();
    int n = secondText.length();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    //预处理边界
    for (int i = 0; i <= m; ++i)
    {
        dp[i][0] = i * 2;
    }

    //预处理边界
    for (int j = 0; j <= n; ++j)
    {
        dp[0][j] = j * 1;
    }

    //计算最短编辑距离
    for (int i = 1; i <= m; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            if (firstText[i - 1] == secondText[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1];
            }
            else
            {
                int insertCost = dp[i][j - 1] + 1;
                int deleteCost = dp[i - 1][j] + 1;
                int replaceCost = dp[i - 1][j - 1] + 1;
                dp[i][j] = min(min(insertCost, deleteCost), replaceCost);
            }
        }
    }
    return dp[m][n];
}

double compare(const vector<pair<string, string>> &a, const vector<pair<string, string>> &b, int num1, int num2)
{
    double res = 0.0;
    int codeLength = 0;
    double score[10000];

    //a同学代码的相应片段的序号
    int aPartNumber;

    //b同学代码的相应片段的序号
    int bPartNumber;

    //a的代码片段们的总长
    for (int i = 0; i < a.size(); i++)
    {
        codeLength += a[i].second.length();
    }

    for (int i = 0; i < a.size(); i++)
    {
        //枚举片段，计算最高的相似度
        double maxScore = 0.0;

        //当前a的代码片段的简化代码长度
        int numA = a[i].second.length();

        //当前a的代码片段的简化版
        string codePartA = a[i].second;

        for (int j = 0; j < b.size(); j++)
        {
            //b的代码片段的简化代码长度
            int numB = b[j].second.length();

            //当前b的代码片段的简化版
            string codePartB = b[j].second;

            //计算最小编辑距离
            int distance = minEditDistance(codePartA, codePartB);

            //计算出得分
            score[j] = 1.0 - (double) distance / max(numA, numB);
            if (score[j] > maxScore)
            {
                maxScore = score[j];
                aPartNumber = i;
                bPartNumber = j;
            }
        }
        //我们以最大相似度的结果作为答案
        //然后加权平均，计算总相似度
        res += maxScore * (double) numA / (double) codeLength;

        //只保留相似度超过70%的代码片段
        if (maxScore > 0.7)
        {
            samePart[num1][num2].push_back({aPartNumber, bPartNumber, maxScore});
        }
    }

    //返回相似率
    return res * 100.0;
}

//输出时间
void printTime()
{
    //时间指针
    time_t timePointer;

    //时间结构体指针
    struct tm *p;

    //格式化拼装之后的时间字符串
    char timeString[100];

    //用于存储汉字的结构数组，将当天的星期数转换成中文
    char whichDay[20];
    time(&timePointer);

    //获取本机时间
    p = localtime(&timePointer);

    //将对应的星期数转化成中文
    switch (p->tm_wday)
    {
        case 0:
            strcpy(whichDay, "日");
            break;
        case 1:
            strcpy(whichDay, "一");
            break;
        case 2:
            strcpy(whichDay, "二");
            break;
        case 3:
            strcpy(whichDay, "三");
            break;
        case 4:
            strcpy(whichDay, "四");
            break;
        case 5:
            strcpy(whichDay, "五");
            break;
        case 6:
            strcpy(whichDay, "六");
            break;
    }

    //格式化拼接字符串，存储在timeString中
    sprintf(timeString, "%d年%02d月%02d日 %02d:%02d:%02d 星期%s", 1900 + p->tm_year, 1 + p->tm_mon, p->tm_mday,
            p->tm_hour,
            p->tm_min, p->tm_sec, whichDay);

    //打印时间
    printf("当前日期与时间为: %s\n", timeString);
}
