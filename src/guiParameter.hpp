//
//  guiParameter.hpp
//  redisSyncParameter
//
//  Created by TOMITAHAYATO on 2020/12/06.
//

#ifndef guiParameter_hpp
#define guiParameter_hpp

#include "hiredis.h"
#include "msgpack.hpp"
#include <iostream>
#include <stdio.h>
#include <string>

class guiParameter {
public:
  guiParameter() {}
  guiParameter(redisContext *_conn, std::string _key) {
    key = _key;
    conn = _conn;

    resp = (redisReply *)redisCommand(conn, "HGET %s size", key.c_str());
    if (resp->str == NULL) {
      std::cout << "init value" << std::endl;
      dbsync();
      resp = (redisReply *)redisCommand(conn, "HGET %s size", key.c_str());
    }
    size_t data_size = std::atoi(resp->str);

    resp = (redisReply *)redisCommand(conn, "HGET %s value", key.c_str());
    if (resp->str == NULL) {
      std::cout << "init value" << std::endl;
      dbsync();
      resp = (redisReply *)redisCommand(conn, "HGET %s size", key.c_str());
    }
    char *pdata = resp->str;

    msgpack::object_handle hd = msgpack::unpack(pdata, data_size);
    const msgpack::object &obj = hd.get();
    obj.convert(value);
  }

  ~guiParameter() {}
  void setValue(float _value) { value = _value; }
  float getValue() { return value; }
  float *getValuePtr() { return &value; }
  bool dbsync() {
    msgpack::sbuffer buffer;
    msgpack::pack(buffer, value);
    resp = (redisReply *)redisCommand(conn, "HSET %s size %d", key.c_str(),
                                      buffer.size());
    resp = (redisReply *)redisCommand(conn, "HSET %s value %s", key.c_str(),
                                      buffer.data());
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
