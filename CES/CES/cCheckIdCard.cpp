#include "StdAfx.h"
#include "cCheckIdCard.h"

cCheckIdCard::cCheckIdCard(void)
{
}

cCheckIdCard::~cCheckIdCard(void)
{
}
/// <summary>
/// ��֤���֤����
/// </summary>
/// <param name="Id">���֤����</param>
/// <returns>��֤�ɹ�ΪTrue������ΪFalse</returns>
bool cCheckIdCard::CheckIDCard(const string& Id)
{
    if (Id.length() == 18)
        {
            bool check = CheckIDCard18(Id);
            return check;
        }
        else if (Id.length()  == 15)
        {
            bool check = CheckIDCard15(Id);
            return check;
        }
        else
        {
            return false;
        }
}

bool cCheckIdCard::CheckIDCard18(const string& Id)
{
    string address[] ={ "11","22","35","44","53","12","23","36","45","54","13","31","37","46","61","14","32","41","50","62","15","33","42","51","63","21","34","43","52","64","65","71","81","82","91"};
    for( int i = 0; i<= 34; i++)
    {
        if (!(Id.substr(0,2) != address[i]))
            break;//ʡ����֤��ȷ
        else if (i == 34)
            return false;//ʡ����֤����
    }

    string birth = Id.substr(6, 8);
    if(!CheckDate(birth.substr(0,4), birth.substr(4,2), birth.substr(6,2)))
        return false;//������֤����
    if(!VarifyCode(Id))
        return false;//���һλУ�����
    return true;
}

bool cCheckIdCard::CheckIDCard15(const string& Id)
{
    string newID = per15To18(Id);

    if(!CheckIDCard18(newID))
        return false;
    return true;
}

string cCheckIdCard::getBirthday(const string& Id)
{
 if(!CheckIDCard(Id))
        return "";//������֤����
    else
    {
        string birth;
        if (Id.length() == 15)
        {
            string newID = per15To18(Id);
            birth = newID.substr(6, 8);
            return birth.insert(6,"-").insert(4,"-");
        }
        else
            return Id.substr(6,8).insert(6,"-").insert(4,"-");
    }
}

bool   cCheckIdCard::CheckDate(const string&   Year, const   string&   Month,   const string&   Day)
{
    int iYear  = atoi(Year.c_str());
    int  iMonth = atoi(Month.c_str());
    int iDay = atoi(Day.c_str());
    int   Days[12]={31,   28,   31,   30,   31,   30,   31,   31,   30,   31,   30,   31};
    if(iMonth<1   ||   iMonth>12)   return   false;  

    bool   b_IsLeapYear=false;  
    if(iYear%4==0)    
    {  
        b_IsLeapYear=true;  

        if(!(iYear%100==0   &&   iYear%400==0))   b_IsLeapYear=false;  
    }  

    if(b_IsLeapYear)   Days[1]=29;  
    else   Days[1]=28;  

    if(iDay<0   ||   iDay>Days[iMonth-1])   return   false;  

    return   true;  
}   

bool cCheckIdCard::VarifyCode( const string& Id)
{
    char perIDSrc[19];
    strcpy(perIDSrc,Id.c_str());
    int iS = 0;
    int const iW[]={7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2};
    char const  LastCode[]="10X98765432";

    for(int i=0;i<17;i++)
    {
        iS += (int)(perIDSrc[i]-'0') * iW[i];
    }

    int iY = iS%11;
    char   ch   =   LastCode[iY];  
    string   lastChar;  
    lastChar.insert(lastChar.begin(),   ch   );   
    
    if(lastChar != Id.substr(17,1))
        return false;
    return true;
} 

//ʵ�����֤��15λת18λ
string cCheckIdCard::per15To18(const string& Id)
{
    if(Id.length() != 15)
        return "";
    char perIDSrc[19];
    strcpy(perIDSrc,Id.c_str());
    int iS = 0;

    //��Ȩ���ӳ���
    int const iW[]={7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2};
    //У���볣��
    char const LastCode[]="10X98765432";
    //�����֤��
    char perIDNew[19];

    for( int i = 0; i < 6; i++ )
    {
        perIDNew[i] = perIDSrc[i];
    }

    //���ڵ�6λ����7λ�����ϡ�1������9����������
    perIDNew[6] = '1';
    perIDNew[7] = '9';

    for( int i = 8; i < 17; i++ )
    {
        perIDNew[i] = perIDSrc[i - 2];
    }

    //���м�Ȩ���
    for( int i=0; i<17; i++)
    {
        iS += (perIDNew[i]-'0') * iW[i];
        /**//*
        ����perIDNew[i]-'0'����һ�£�
            perIDNew[i]->ASCII�룬ȡ������ֵʵ����ʮ��������
            '0' ->ASCII�룬ͬ�ϣ�
            perIDNew[i]-'0' -> �õ������ʮ������ֵ��
            �����������Ϊʲô�����ת��������ȥ��C++PRIMER���Ǻǡ�
          */
    }
    
    //ȡģ���㣬�õ�ģֵ
    int iY = iS%11;
    //��LastCode��ȡ����ģΪ�����ŵ�ֵ���ӵ����֤�����һλ����Ϊ�����֤�š�
    perIDNew[17] = LastCode[iY];
    //���Ͻ�����
    perIDNew[18] = '\0';

    string tempstr = perIDNew;
    return tempstr;
} 
