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

template <class T> class guiParameter {
public:
  guiParameter() {}
  guiParameter(redisContext *_conn, std::string _key) {
    key = _key;
    conn = _conn;
    resp = (redisReply *)redisCommand(conn, "HGETALL %s", key.c_str());
    if (resp->element == NULL) {
      std::cout << "init value" << std::endl;
      value = T(0);
      dbsync();
      return;
    }
    unpackMessage(resp);
  }
  ~guiParameter() {}

  void setValue(T _value) { value = _value; }
  T getValue() { return value; }
  T *getValuePtr() { return &value; }

  bool dbsync() {
    msgpack::sbuffer buffer;
    msgpack::pack(buffer, value);
    resp =
        (redisReply *)redisCommand(conn, "HMSET %s size %d value %s",
                                   key.c_str(), buffer.size(), buffer.data());
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
  T value;
  redisContext *conn = NULL;
  redisReply *resp = NULL;
  void unpackMessage(redisReply *resp) {
    size_t data_size = std::atoi(resp->element[1]->str);
    char *pdata = resp->element[3]->str;
    msgpack::object_handle hd = msgpack::unpack(pdata, data_size);
    const msgpack::object &obj = hd.get();
    obj.convert(value);
  }
};

#endif /* guiParameter_hpp */
