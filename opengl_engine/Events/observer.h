#pragma once
#include <functional>

#define Bind_0(FuncSignature)      std::bind(FuncSignature, this)
#define Bind_1(FuncSignature)      std::bind(FuncSignature, this, std::placeholders::_1)
#define Bind_2(FuncSignature)      std::bind(FuncSignature, this, std::placeholders::_1, std::placeholders::_2)
#define Bind_3(FuncSignature)      std::bind(FuncSignature, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)
#define Bind_4(FuncSignature)      std::bind(FuncSignature, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4)
#define Bind_5(FuncSignature)      std::bind(FuncSignature, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5)
#define Bind_6(FuncSignature)      std::bind(FuncSignature, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, std::placeholders::_6)
#define Bind_7(FuncSignature)      std::bind(FuncSignature, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, std::placeholders::_6, std::placeholders::_7)
#define Bind_8(FuncSignature)      std::bind(FuncSignature, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, std::placeholders::_6, std::placeholders::_7, std::placeholders::_8)
#define Bind_9(FuncSignature)      std::bind(FuncSignature, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, std::placeholders::_6, std::placeholders::_7, std::placeholders::_8, std::placeholders::_9)



class Observer
{
};