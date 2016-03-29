#include <iostream>
#include <cstdlib>
#include <ctime>
 
using namespace std;
 
// class Of Arighm
class Ari
{
public:
    // ���캯��
    Ari();
    // ���캯��
    ~Ari();
    // ���ɺ���num���������ֵ�������ʽ���
    void CreateShu(int num);
    // ����������������������
    int Count();
    // ��������ɵı��ʽ
    void Display();
     
private:
    // �Ƚ�����������ȼ�
    bool OperIsHigher();
    // �õ��������Ȩֵ
    int GetPriOfOper(const char oper);
 
private:
    int iResult;
        // ���ʽ�Ľ��
    char oper;
        // ���ʽ�������
    Ari *lhs;
        // ���ʽ����ڵ�
    Ari *rhs;
        // ���ʽ���ҽڵ�
    bool isRoot;
        // �ñ��ʽ�Ƿ�Ϊ���յı��ʽ
    Ari *Parent;
        // ���ʽ�ĸ��ڵ�
    bool isLeft;
        // �Ƿ�Ϊ��ڵ�(Ϊ������Ǽ�������)
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
