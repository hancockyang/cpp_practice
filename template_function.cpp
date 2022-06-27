#include<vector>
#include<iostream>
template<typename T1, typename T2, int N>
void printNumbers(std::vector<T1> t1, std::vector<T2> t2, T1 filter = T1(N)){
    for (int i = 0; i < t1.size(); ++i){
        if (t1[i] > filter)
            std::cout<<t1[i]<<" ";
    }
    std::cout<<"\n";
    for (int i = 0; i < t2.size(); ++i){
        std::cout<<t2[i]<<" ";
    }
    std::cout<<"\n";
}

template<typename T>
T Max(T a1, T a2){
    std::cout<<"called general template"<<std::endl;
    return (a1 > a2) ? a1 : a2;
}

template<> char Max(char a1, char a2){
    std::cout<<"called specification"<<std::endl;
    return (a1 > a2) ? a1 : a2;
}

int main(){
    std::vector<int> a = {0, 1, 2, 3, 4, 5, 6, 8};
    std::vector<float> b = {0, 1.0f, 2.1f, 3, 4.2f, 5.5f, 6, 8.0f};
    std::vector<char> c = {'a','4','b','2','6','c'};
    printNumbers<int, float, 2>(a, b);
    int a1 = 2, a2 = 1;
    int resI = Max(a1, a2);
    char c1 = '2', c2 = 'a';
    char resC = Max(c1, c2);
    return 0;
}