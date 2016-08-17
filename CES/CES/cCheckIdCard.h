#include <string>
using namespace std;
class cCheckIdCard
{
public:
    cCheckIdCard(void);
    //身份证验证
    bool CheckIDCard(const string& Id);
    
    //18位身份证验证
    bool CheckIDCard18(const string& Id);

    //15位身份证验证
    bool CheckIDCard15(const string& Id);

    //生日验证
    bool   CheckDate(const string &Year,   const string &const Month,   const string &Day);
    
    //最后一位校验
    bool cCheckIdCard::VarifyCode(const string& Id);
    
    //实现身份证的15位转18位 
    string per15To18(const string& Id);

    //获得生日
    string getBirthday(const string& Id);

    virtual ~cCheckIdCard(void);

};
