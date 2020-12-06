//
//  guiParameter.hpp
//  redisSyncParameter
//
//  Created by TOMITAHAYATO on 2020/12/06.
//

#ifndef guiParameter_hpp
#define guiParameter_hpp

#include <stdio.h>

class guiParameter{
public:
    guiParameter() {}
    ~guiParameter() {}
    void setValue(float _value) { value = _value; }
    float getValue() { return value; }
    float *getValuePtr() { return &value; }
private:
    float value;
};

#endif /* guiParameter_hpp */
