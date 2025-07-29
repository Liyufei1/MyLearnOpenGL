#pragma once
#include "Common/CommonFunLib.h"
#include "Common/CommonFunLib.hpp"
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>

template <typename ...Args>
void foo (Args ...args){
    (void) std::initializer_list<int>{(std::cout << args << ' ', 0)...};
}

template<typename ...Args> void foo1 (Args ...args){
    std::cout << sizeof...(args) << std::endl;
}

template <typename  T>
T sum(T a){
    return a;
}

template <typename  T1 ,typename ...Args>
auto sum(T1 a, Args ...args){
    return a + sum(args...);
}


template <typename ...Args>
auto sum1(Args ...args){
    return (... + args );
}

template <typename ...Args>
void mycout(Args ...args){
    (std::cout << ... << args) << std::endl;
}

void TestFun(){
	LOG(LOGTEMP,"TestFun::Begin !");

	// glm::mat4 AA{1.0f};
	// glm::vec3 Scale{1.0,2.0,2.0};
	// AA = glm::scale(AA, Scale);

	// lyf::QueryMaxAttribVetxCount();

    foo1(1.0f, 2.0f,1,"asdasd");

    // std::cout << sum(1,2,3,4,5,6,7,8,9,10) << std::endl;
    // std::cout << "sum1 :: " <<sum1(std::string("321"),"asd","123") << std::endl;
    // mycout(1,2,3,4,5,6,7,8,9,10);
	LOG(LOGTEMP,"TestFun::End !");	
}
