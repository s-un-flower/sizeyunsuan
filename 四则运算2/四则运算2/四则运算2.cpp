#include <iostream>
#include <cstdlib>
#include <ctime>
 
using namespace std;
 
// class Of Arighm
class Ari
{
public:
    // 构造函数
    Ari();
    // 构造函数
    ~Ari();
    // 生成含有num个运算数字的随机表达式框架
    void CreateShu(int num);
    // 填入符合条件的随机的数字
    int Count();
    // 输出所生成的表达式
    void Display();
     
private:
    // 比较运算符的优先级
    bool OperIsHigher();
    // 得到运算符的权值
    int GetPriOfOper(const char oper);
 
private:
    int iResult;
        // 表达式的结果
    char oper;
        // 表达式的运算符
    Ari *lhs;
        // 表达式的左节点
    Ari *rhs;
        // 表达式的右节点
    bool isRoot;
        // 该表达式是否为最终的表达式
    Ari *Parent;
        // 表达式的父节点
    bool isLeft;
        // 是否为左节点(为了输出是加括号用)
};
Ari::Ari()
: iResult(0)
, oper('\0')
, lhs(NULL)
, rhs(NULL)
, Parent(NULL)
, isLeft(false)
{
     
}
 
Ari::~Ari()
{
    if(lhs != NULL)
    {
        delete lhs;
    }
 
    if (rhs != NULL)
    {
        delete rhs;
    }
}
 
void Ari::CreateShu(int numOfNode)
{
    if (1 == numOfNode)
    {
        return ;
    }
    else
    {
        int opfu = rand() % 4;
        if (0 == opfu)
        {
            oper = '+';
        }
        else if (1 == opfu)
        {
            oper = '-';
        }
        else if (2 == opfu)
        {
            oper = '*';
        }
        else
        {
            oper = '/';
        }
 
        lhs = new Ari();
        rhs = new Ari();
        lhs->Parent = this;
        lhs->isLeft = true;
        rhs->Parent = this;
        rhs->isLeft = false;
 
        int numOfNodeLeft = numOfNode - rand() % numOfNode;
        if (numOfNodeLeft == numOfNode)
        {
            numOfNodeLeft = 1;
        }
 
        lhs->CreateShu(numOfNodeLeft);
        rhs->CreateShu(numOfNode - numOfNodeLeft);
    }
}
 
 
int Ari::Count()
{
    if (lhs != NULL && rhs != NULL)
    {
        int lResult = 0;
        int rResult = 0;
 
        lResult = lhs->Count();
        rResult = rhs->Count();
 
        while (lResult >= 200 || lResult <= 0)
        {
            lResult = lhs->Count();
        }
 
        while (rResult >= 200 || rResult <= 0)
        {
            rResult = rhs->Count();
        }
 
        if ('+' == oper)
        {
            iResult = lResult + rResult;
        }
 
        else if ('-' == oper)
        {
            iResult = lResult - rResult;
            if (iResult < 0)
            {
                Ari*temp = lhs;
                lhs = rhs;
                lhs->isLeft = true;
                rhs = temp;
                rhs->isLeft = false;
                iResult = rResult - lResult;
            }
        }
 
        else if ('*' == oper)
        {
            int getNum = 0;
            iResult = lResult * rResult;
            while(iResult >= 100)
            {
                lResult = lhs->Count();
                rResult = rhs->Count();
                getNum++;
 
                if (getNum > 100)
                {
                    int mode = rand() % 2;
                    if (0 == mode)
                    {
                        oper = '+';
                        iResult = lResult + rResult;
                    }
                    else if (1 == mode)
                    {
                        oper = '-';
                        iResult = lResult - rResult;
                        if (iResult < 0)
                        {
                            Ari *temp = lhs;
                            lhs = rhs;
                            lhs->isLeft = true;
                            rhs = temp;
                            rhs->isLeft = false;
                            iResult = rResult - lResult;
                        }
                    }
 
                    return iResult;
                }
 
                iResult = lResult * rResult;
            }
        }
 
        else if ('/' == oper)
        {
            int getNum = 0;
            while (0 == lResult || 0 == rResult || lResult % rResult != 0)
            {
                lResult = lhs->Count();
                rResult = rhs->Count();
                getNum++;
                if(getNum > 2000)
                {
                    int mode = rand() % 2;
                    if (0 == mode)
                    {
                        oper = '+';
                        iResult = lResult + rResult;
                    }
                    else if (1 == mode)
                    {
                        oper = '-';
                        iResult = lResult - rResult;
                        if (iResult < 0)
                        {
                            Ari*temp = lhs;
                            lhs = rhs;
                            lhs->isLeft = true;
                            rhs = temp;
                            rhs->isLeft = false;
                            iResult = rResult - lResult;
                        }
                    }
 
                    return iResult;
                }
            }
 
            iResult = lResult / rResult;
        }
    }
    else
    {
        iResult = rand() % 200;
        while (iResult == 0)
        {
            iResult = rand() % 200;
        }
    }
 
    return iResult;
}
 
void Ari::Display()
{
    if(lhs != NULL && rhs != NULL)
    {
        if (!OperIsHigher())
        {
            cout << '(';
        }
        lhs->Display();
        cout << " " << oper << " ";
        rhs->Display();
        if (!OperIsHigher())
        {
            cout << ')';
        }
    }
    else
    {
        cout << iResult;
    }
}
 
bool Ari::OperIsHigher()
{
    if (NULL == Parent)
    {
        return true;
    }
    if (isLeft)
    {
        return GetPriOfOper(this->oper) >= GetPriOfOper(Parent->oper);
    }
    else
    {
        return GetPriOfOper(this->oper) > GetPriOfOper(Parent->oper);
    }
}
 
int Ari::GetPriOfOper(const char oper)
{
    if ('\0' == oper)
    {
        return 3;
    }
    else if ('/' == oper || '*' == oper)
    {
        return 2;
    }
    else if ('+' == oper || '-' == oper)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int main()
{
    Ari *pRoot = NULL;
 
    int numOfArighm = 0;
 
    int numOfNumber = 0;
 
    cout << "please input the number of arithmetic expressions:" << endl;
 
    cin >> numOfArighm;
 
    int iResult = 0;
    srand((int)time(0));
 
    for (int i = 0; i < numOfArighm; i++)
    {
        pRoot = new Ari();
        numOfNumber = rand() % 7 + 2;
        pRoot->CreateShu(numOfNumber);
        iResult = pRoot->Count();
        while (iResult >= 200 || iResult <= 0)
        {
            iResult = pRoot->Count();
        }
        pRoot->Display();
        cout << " = " << iResult;
        cout << endl;
        delete pRoot;
    }
    return 0;
}
