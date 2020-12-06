//
//  guiParameter.hpp
//  redisSyncParameter
//
//  Created by TOMITAHAYATO on 2020/12/06.
//

#ifndef guiParameter_hpp
#define guiParameter_hpp

#include "hiredis.h"
#include <iostream>
#include <stdio.h>
#include <string>

class guiParameter {
public:
  guiParameter() {}
  guiParameter(redisContext *_conn, std::string _key) {
    key = _key;
    conn = _conn;
    resp = (redisReply *)redisCommand(conn, "GET %s", key.c_str());
    if (NULL == resp) {
      return false;
    }
    if (REDIS_REPLY_ERROR == resp->type) {
      return false;
    }
    if (resp->str == NULL) {
      std::cout << "init value" << std::endl;
      dbsync();
    }
    value = std::atof(resp->str);
  }
  ~guiParameter() {}
  void setValue(float _value) { value = _value; }
  float getValue() { return value; }
  float *getValuePtr() { return &value; }
  bool dbsync() {
    resp = (redisReply *)redisCommand(conn, "SET %s %f", key.c_str(), value);
    if (NULL == resp) {
      std::cout << "failed to set value." << std::endl;
      return false;
    }
    if (REDIS_REPLY_ERROR == resp->type) {
      return false;
    }
  }

private:
  std::string key;
  float value = 0;
  redisContext *conn = NULL;
  redisReply *resp = NULL;
};

#endif /* guiParameter_hpp */
