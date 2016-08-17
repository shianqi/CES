#include <string>
using namespace std;
class cCheckIdCard
{
public:
    cCheckIdCard(void);
    //���֤��֤
    bool CheckIDCard(const string& Id);
    
    //18λ���֤��֤
    bool CheckIDCard18(const string& Id);

    //15λ���֤��֤
    bool CheckIDCard15(const string& Id);

    //������֤
    bool   CheckDate(const string &Year,   const string &const Month,   const string &Day);
    
    //���һλУ��
    bool cCheckIdCard::VarifyCode(const string& Id);
    
    //ʵ�����֤��15λת18λ 
    string per15To18(const string& Id);

    //�������
    string getBirthday(const string& Id);

    virtual ~cCheckIdCard(void);

};
