
#include "ImgHash.h"

#include <iostream>

int main()
{
    std::wstring a_1280x800;
    std::wstring a_960x600;
    std::wstring b_1280x800;

    HashHbitmap(L"a_1280x800.bmp", a_1280x800);
    HashHbitmap(L"a_960x600.bmp", a_960x600);
    HashHbitmap(L"b_1280x800.bmp", b_1280x800);

    std::wcout << L"a_1280x800 : " << a_1280x800 << std::endl;
    std::wcout << L"a_960x600  : " << a_960x600 << std::endl;
    std::wcout << L"b_1280x800 : " << b_1280x800 << std::endl;

    int32_t distance_a = HanmingDistance(a_1280x800, a_960x600);
    std::cout << "distance(a_1280x800, a_960x600)  : " 
        << ((distance_a < 5) ? "MATCH" : "!MATCH") 
        << distance_a
        << std::endl;
    int32_t distance_ab = HanmingDistance(a_1280x800, b_1280x800);
    std::cout << "distance(a_1280x800, b_1280x800) : "
        << ((distance_ab < 5) ? "MATCH" : "!MATCH")
        << distance_ab
        << std::endl;

    return 0;
}
