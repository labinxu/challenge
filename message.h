#include <cstring>


#include <unistd.h>


#include <iostream>


enum class message_type {ENTER_ORDER,CANCEL_ORDER, TRADE_ORDER};


class message_base{


public:


  enum {type_length = 4};


  enum {header_length = 4};


};


enum class message_t {type_len=4, header_len=4};


template<class T>


class message: public message_base


{


public:


  enum {max_body_length = sizeof(T)};


  enum {data_length = header_length+type_length+max_body_length};


　


  message(const message<T> &&msg){


　


    memcpy(_data, msg.data(), sizeof(_data));


  }


　


  T* get_value(){


    return (T*)(_data+header_length+type_length);


  }


  char *body(){


    return _data + header_length+type_length;


  }


  message(const T&& o, message_type t) {


    memcpy(_data+header_length+type_length, (char*)(&o), sizeof(T));


    encode_header();


    encode_type(t);


  }

  void encode_header(){


    char header[header_length+1] = {0};


    sprintf(header, "%4lu", type_length+max_body_length);


    memcpy(_data , header, header_length);


  }


  void encode_type(message_type t){


    memcpy(_data+header_length, (char*)&t, type_length);


  }


  message_type msg_type() const{


    char tp[type_length]={0};


    memcpy(tp, _data+header_length, type_length);


    return *(message_type*)tp;


  }


　


  bool decode_header(){


    char header[header_length+1] = {0};


    strncat(header, _data, header_length);


    _body_length = atoi(header);


    if (body_length > max_body_length){


      return false;


    }


    return true;


  }


  size_t body_length() const {


    return _body_length;


  }


  const char* data()const{


    return _data;


  }


　


private:


  char _data[header_length+type_length+max_body_length];


  size_t _body_length;


};


　


template<class T>


message<T>* make_message(const char *data){


  return (message<T>*)data;


}
