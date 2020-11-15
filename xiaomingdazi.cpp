#include <iostream>
#include <string>
#include "List.h"
int main() {
    std::string str;
    std::getline(std::cin,str);
    List<char> list;
    auto iter = list.end();
    bool insert_mode=true;
    for(auto i:str) {
        switch(i) {
            case '[': //home
                iter = list.begin();
                break;
            case ']': //end
                iter = list.end();
                break;
            case '{': //左
                iter--;
                break;
            case '}': //右
                iter++;
                break;
            case '-': //insert
                insert_mode = !insert_mode;
                if(insert_mode == 1)
                    iter++;
                break;
            case '=': //del
                list.erase(--iter);
                break;
            default:
                if(insert_mode) {
                    list.insert(iter, i);
                    iter++;
                }
                else {
                    *iter = i;
                }
                break;
        }
    }
    for(auto i=list.begin(); i!=list.end(); i++)
        std::cout << *i;
    std::cout << std::endl;

    return 0;
}