#include "222200314_Similarity1.h"

//C++�ؼ���
set<string> keywords =
        {
                "int", "double", "float", "char", "short", "long", "using", "namespace", "bool", "auto", "typeof",
                "class",
                "static", "return",
                "goto", "struct", "cout", "cin", "scanf", "printf", "get", "put", "in", "out", "ios", "std", "pair",
                "string"
        };

//�����Ĺؼ���
set<string> container =
        {
                "set", "map", "vector", "unordered_set", "unordered_map"
        };

//�洢���ݴ������Ʋ��ֵĴ���
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
    //��ų�ʼ����ĵĴ���
    string modifyCode = "1 ";
    int row = 1;
    for (int i = 0; i < code.length(); i++)
    {
        //��һЩ�����Ŀո���Ʊ��ȫ���淶�ɵ��ո�
        if (code[i] == ' ' || code[i] == '\t')
        {
            modifyCode += ' ';
            while (code[i + 1] == ' ' || code[i + 1] == '\t')
            {
                i++;
            }
        }
            //�������о�����һ�У��������к�
        else if (code[i] == '\n')
        {
            row++;
            modifyCode += '\n' + numToString(row) + ' ';
        }
            //�����������ע�ͣ���ֱ����������
        else if (code[i] == '/' && code[i + 1] == '/')
        {
            while (code[i + 1] != '\n')
            {
                i++;
            }
        }
            //��������˿�ע�ͣ���ֱ���ӹ���Щ����
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
            //�����Ĵ���ֱ�ӼӼ���
        else
        {
            modifyCode += code[i];
        }
    }
    return modifyCode;
}

string analyze(string originCode)
{
    //���յĴ�����Ĵ���
    string resultCode;

    //���ܵĹؼ�����������������������
    string name;

    //��������д����ȥ���кŵĴ���
    string modifyCode;

    //��������Բ���Ż��߻�������Ĵ���ģ����еݹ����
    string areaTmp;

    //������¼���ܱ������������±�
    int right = 0, left = 0;

    //��ʼ����Ԥ����
    for (int i = 0; i < originCode.length(); i++)
    {
        //�ڴ����÷�б�����ӵ�ʱ�������ո�ͻ��У��Ѵ���Ū��һ��
        if (originCode[i] == '\\')
        {
            //������¼�����У���������Ч�±�
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
        //��ÿһ�е��к�ȥ��
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
        //ע����Ч�ַ�
        modifyCode += originCode[i];
    }

    //��ʼ�����滻�����ĺ��Ĵ���
    while (right < modifyCode.length())
    {
        //���������˹ؼ��ֻ�����������н�һ�����ж�
        if (isalpha(modifyCode[right]) || modifyCode[right] == '_')
        {
            //��¼һ�³�ʼ����
            left = right;

            //��ȡ�������Ʊ�����
            while (isalnum(modifyCode[right]) || modifyCode[right] == '_')
            {
                right++;
            }

            //����ָ����
            name = modifyCode.substr(left, right - left);

            //�������һ���ؼ���
            if (keywords.count(name))
            {
                resultCode += "k";
                name = "";
            }
                //�������һ�����������ֶ�
            else if (container.count(name))
            {
                resultCode += "c";
                name = "";
            }
        }

            //��������û�жԱ�������������д��������������ı�������洢��tmp��
            //��Ϊ��������һЩ����������߼��������������������Щ���ŵĻ�˵�����������˱���
            //��ֵ���㣬˵�����������˱�����
        else if (modifyCode[right] == '=')
        {
            right++;
            //����ж�����˵�������˱�����
            if (!name.empty())
            {
                resultCode += "v";
                name = "";
            }
            //ȥ���������ո�ͻ���
            while (modifyCode[right + 1] == ' ' || modifyCode[right + 1] == '\n')
            {
                right++;
            }
            //����������ڶ����Ⱥţ�˵�����Ǹ�����������Ҫ����==
            if (modifyCode[right] == '=')
            {
                resultCode += "==";
            }
                //���������ͨ�ĸ�ֵ�����
            else
            {
                resultCode += "=";
            }
            //������֮��������һ���������²����ж�
            right++;
        }

            //�������Ǽӷ���������͸�ֵ���������
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
            //������+=
            if (modifyCode[right] == '=')
            {
                resultCode += "+=";
            }
                //������++
            else if (modifyCode[right] == '+')
            {
                resultCode += "++";
            }
                //�����������ֻ��һ��+
            else
            {
                resultCode += '+';
            }
            right++;
        }

            //���źͼӷ�����
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

            //�˺źͼӷ�����
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

            //���źͼӷ�����
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

            //����������for if�������ߺ��������
        else if (modifyCode[right] == '(')
        {
            //������������ƥ����
            int count = 1;
            left = right + 1;

            //������ƥ����
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
            //����ж��������滻��f()
            if (!name.empty())
            {
                resultCode += "f(";
                name = "";
            }
            //����һ��
            areaTmp = analyze(modifyCode.substr(left, right - left));
            resultCode += areaTmp;
            resultCode += ')';
            right++;
        }

            //��������������������˵��Ҳ�Ǹ�����
        else if (modifyCode[right] == '[')
        {
            //������������ƥ����
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

            //������������ͨ�ĺ�������ߴ�������ĵݹ����
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

            //��������˫���ŵĴ������ַ��������s
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

            //�������ǵ����ŵĴ������ַ������s
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

            //�����˶��Ż��߷ֺŵĻ��������ж�
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

            //���ֳ��󻯣��������⿼��16���Ƶ�����
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

            //С�ں��жϣ��ж�����������������ǱȽ������
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

            //���ں��жϣ��ж�����������������ǱȽ������
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

            //��������
        else
        {
            left = right;

            //����ͷ�ļ�
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

                //��Ŀ���������
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

                //���������������
            else if (modifyCode[right] == ':' && modifyCode[right + 1] == ':')
            {
                right += 2;
                resultCode += "::";
            }

                //��������ͨ�ַ�ֱ�����
            else
            {
                right++;
                resultCode += modifyCode[right - 1];
            }
        }

        //ȥ����ĩ�ո�
        if (isspace(modifyCode[right]))
        {
            right++;
        }

        //������Ѿ����ļ�ĩβ�����ǻ����ڱ�����������continue����
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
    //����ĳ�ʼƬ�κ��޸ĺ�Ƭ��
    vector<pair<string, string> > areas;

    // originCode����Ǵ���Դ�룬
    // modifyCode�����Ԥ�����Ĵ��루�����кš�ȥ�������ո�ȥ��ע�ͣ�
    string originCode, modifyCode;

    // circleBracket�Ǽ�¼֮ǰʮ�ֳ��ֹ�Բ���ţ�
    // bigBracket�Ǽ�¼�Ƿ���ֹ������ţ�
    // ��������˵���Ǻ�����
    // ֻ�д�����û��Բ����˵���ǽṹ��
    bool circleBracket, bigBracket;

    //��ȡ�ļ������Ҵ����originCode
    ifstream file;
    file.open(filename, ios::in);
    if (!file)
    {
        cout << "�޷���ȡ�ļ�: " + filename << endl;
        return areas;
    }
    originCode = "";
    while (!file.eof())
    {
        originCode += file.get();
    }

    // �������ո��ע��
    modifyCode = init(originCode);

    //�����ַ��±�ָ��
    int position = 0;

    //�ڶ����Ǿֲ��±�ָ�룬�����������Ǳ߼���
    int temp = 0;

    //����ֿ����ʼ�±�
    int start = 0;

    //����ֿ���յ��±�
    int end = 0;

    //lineNum�ǵ�ǰ�к�
    int lineNum = 1;

    //sLineNum����ʼ���к�
    int sLineNum = 1;

    //���д���Ļ��ֹ���
    while (position < modifyCode.length())
    {
        //��������
        if (modifyCode[position - 1] == '\n')
        {
            lineNum++;
        }
        //��С�������д����ţ�˵������һ������
        if (bigBracket && circleBracket)
        {
            end = position - 1;

            //�ѿ��кͻس�ȫ���Թ�
            while (modifyCode[start] == ' ' || modifyCode[start] == '\n')
            {
                if (modifyCode[start] == '\n')
                {
                    sLineNum++;
                }
                start++;
            }

            //�����ǰstartλΪ���֣���˵��startλ�����кſ�ʼ���Ͳ��ü��кš����startλ�������֣��ǲ�ֺ��һ��ǰ��Ҫ�����к�
            //��������Ͷ��ȡ�ɵĴ��룬�Ѵ���ѹ��ͬһ��
            if (isdigit(modifyCode[start]))
            {
                areas.emplace_back(modifyCode.substr(start, end - start + 1), "");
            }
            else
            {
                areas.emplace_back(numToString(sLineNum) + ' ' + modifyCode.substr(start, end - start + 1), "");
            }

            //�����µ���ʼ�к���ʼ����
            start = end + 1;
            sLineNum = lineNum;

            //����
            bigBracket = false;
            circleBracket = false;
        }

            //û��С���ŵ����д����ţ�˵���ǽṹ�������
        else if (!circleBracket && bigBracket)
        {
            //��Ϊ���Ǳ���ͨ�������˸��ֺţ����Լ����ѷֺŶ���
            while (modifyCode[position] != ';')
            {
                position++;
            }
            end = position;

            //ȥ���ո�ͻ���
            while (modifyCode[start] == ' ' || modifyCode[start] == '\n')
            {
                if (modifyCode[start] == '\n')
                {
                    sLineNum++;
                }
                start++;
            }
            //�����ǰstartλΪ���֣���˵��startλ�����кſ�ʼ���Ͳ��ü��кš����startλ�������֣��ǲ�ֺ��һ��ǰ��Ҫ�����к�
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

            //��������ͨ���ķֺţ���ô�ͼ�ʱ����end
        else if (modifyCode[position] == ';')
        {
            end = position;
        }

            //��Բ���ŵĲ���ȫ���Ե�������position��lineNum
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

            //�Ѵ����ŵĲ���ȫ���Ե�������position��lineNum
        else if (modifyCode[position] == '{')
        {
            //���������start�ᱻ���³�end+1����������м��м���һЩ�������Ļ����ҵ�end�ͻ��start��
            //���ǰ���Щ���ȫ��������һ����
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

            //ȥ���ո�
            while (isspace(modifyCode[start]))
            {
                start++;
            }
            sLineNum = lineNum;

            //��������ƥ��
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

        //����Ѿ��������һλ���Ͱ�ʣ�µĲ�����һ��
        if (position == modifyCode.length() - 1)
        {
            //�Ե��ո�ͻس�
            while (modifyCode[start] == ' ' || modifyCode[start] == '\n')
            {
                if (modifyCode[start] == '\n')
                {
                    sLineNum++;
                }
                start++;
            }

            //����Ǵ�������ɵģ�����ĩβ����һ�в��Ҳ����к�
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

                //��������Ĵ����Ļ���ȫ��������һ����
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

    //����analyze����ԭ���Ĵ���ӹ���浽second��ȥ
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

    //Ԥ����߽�
    for (int i = 0; i <= m; ++i)
    {
        dp[i][0] = i * 2;
    }

    //Ԥ����߽�
    for (int j = 0; j <= n; ++j)
    {
        dp[0][j] = j * 1;
    }

    //������̱༭����
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

    //aͬѧ�������ӦƬ�ε����
    int aPartNumber;

    //bͬѧ�������ӦƬ�ε����
    int bPartNumber;

    //a�Ĵ���Ƭ���ǵ��ܳ�
    for (int i = 0; i < a.size(); i++)
    {
        codeLength += a[i].second.length();
    }

    for (int i = 0; i < a.size(); i++)
    {
        //ö��Ƭ�Σ�������ߵ����ƶ�
        double maxScore = 0.0;

        //��ǰa�Ĵ���Ƭ�εļ򻯴��볤��
        int numA = a[i].second.length();

        //��ǰa�Ĵ���Ƭ�εļ򻯰�
        string codePartA = a[i].second;

        for (int j = 0; j < b.size(); j++)
        {
            //b�Ĵ���Ƭ�εļ򻯴��볤��
            int numB = b[j].second.length();

            //��ǰb�Ĵ���Ƭ�εļ򻯰�
            string codePartB = b[j].second;

            //������С�༭����
            int distance = minEditDistance(codePartA, codePartB);

            //������÷�
            score[j] = 1.0 - (double) distance / max(numA, numB);
            if (score[j] > maxScore)
            {
                maxScore = score[j];
                aPartNumber = i;
                bPartNumber = j;
            }
        }
        //������������ƶȵĽ����Ϊ��
        //Ȼ���Ȩƽ�������������ƶ�
        res += maxScore * (double) numA / (double) codeLength;

        //ֻ�������ƶȳ���70%�Ĵ���Ƭ��
        if (maxScore > 0.7)
        {
            samePart[num1][num2].push_back({aPartNumber, bPartNumber, maxScore});
        }
    }

    //����������
    return res * 100.0;
}

//���ʱ��
void printTime()
{
    //ʱ��ָ��
    time_t timePointer;

    //ʱ��ṹ��ָ��
    struct tm *p;

    //��ʽ��ƴװ֮���ʱ���ַ���
    char timeString[100];

    //���ڴ洢���ֵĽṹ���飬�������������ת��������
    char whichDay[20];
    time(&timePointer);

    //��ȡ����ʱ��
    p = localtime(&timePointer);

    //����Ӧ��������ת��������
    switch (p->tm_wday)
    {
        case 0:
            strcpy(whichDay, "��");
            break;
        case 1:
            strcpy(whichDay, "һ");
            break;
        case 2:
            strcpy(whichDay, "��");
            break;
        case 3:
            strcpy(whichDay, "��");
            break;
        case 4:
            strcpy(whichDay, "��");
            break;
        case 5:
            strcpy(whichDay, "��");
            break;
        case 6:
            strcpy(whichDay, "��");
            break;
    }

    //��ʽ��ƴ���ַ������洢��timeString��
    sprintf(timeString, "%d��%02d��%02d�� %02d:%02d:%02d ����%s", 1900 + p->tm_year, 1 + p->tm_mon, p->tm_mday,
            p->tm_hour,
            p->tm_min, p->tm_sec, whichDay);

    //��ӡʱ��
    printf("��ǰ������ʱ��Ϊ: %s\n", timeString);
}
