#include <iostream>

using namespace std;

class FooString
{
    int charsize;
    char* buf;
public:
    FooString(char* tbuf)
    {
        charsize = strlen(tbuf)+1;
        buf = new char[charsize];
        for (int i = 0; i < charsize; i++)   
        {
            buf[i] = tbuf[i];
        }
    }
    ~FooString()
    {

    }
    void show() {
        cout << buf<<endl;
    }
    bool compare(FooString str)
    {
        if (str.charsize != charsize)
        {
            return false;
        }
        else for (int i = 0; i < charsize; i++)
        {
            if (buf[i] != str.buf[i])
            {
                return false;
            }
        }
        return true;
    }
    
};

int test1()
{
    char str1[] = "Hello";
    char str2[] = "Hello";
    char str3[] = "Helloo";
    FooString a(str1);
    FooString b(str2);
    FooString c(str3);
    if ((a.compare(b) == 1) && (a.compare(c) == 0))
    {
        return 0;
    }
    return -1;
}

void successTest(int nameTest())
    {
        if (nameTest() == 0)
        {
            cout << "test is OK" << endl;
        }
        else
        {
            cout << "test is Fail" << endl;
        }
    }

int main()
{
    char str1[] = "Hello";
    FooString a(str1);
    a.show();
    successTest(test1);
    return 0;
}