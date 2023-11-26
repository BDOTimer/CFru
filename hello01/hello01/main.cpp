#include <iostream>
#include <string>

#define  l(v)  std::cout << #v << " = " << v << "\n";

struct  String : std::string
{       String(const char* s) : std::string(s) {}
        String(std::string s) : std::string(s) {}

    String operator[](size_t i)
    {
        const  size_t NPOS = (size_t)-1;
        static size_t  cnt = NPOS;

        if( cnt == NPOS)
        {   cnt =  i; return data() + i;
        }

        auto n = i - cnt;
           cnt = NPOS;
        return sub(n);
    }

    String sub(size_t n)
    {
        std::string s(n, ' ');

        for(size_t i = 0; i < n; ++i)
        {   s[i] = this->data()[i];
        }

        return s;
    }
};



int main()
{
    String s{"012345"};

    std::cout << s[1][3] << std::endl;
}
