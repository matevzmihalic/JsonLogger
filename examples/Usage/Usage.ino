#include <json_builder.h>

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    ;  // wait for serial port to connect. Needed for native USB port only
  }

  char buf3[3], buf256[256], buf64[64], buf512[512];
  // key: value is a string
  // i|key: value is an integer
  // d|*key: value is a floating number with 1 to 17 significant digits; argument should be a double
  // b|key: value is a boolean
  // o|key: value is anything else (object, array, null)
  int json_len = json(buf256, "str_key1", "str1", "i|int_key1", 7, "d|3double_key1", 3.14159,
                      "b|boolean_key1", 1, "o|object_key1", "{}", "o|array_key1", "[]", "o|null_key1", "null");
  Serial.println(String(buf256) + " length: " + json_len);  // {"str_key1":"str1","int_key1":7,"double_key1":3.14,"boolean_key1":true,"object_key1":{},"array_key1":[],"null_key1":null}

  // return value: length of the json string
  json_len = json(buf3, "k", "v");  // need buffer size to be 10 to hold {"k":"v"}
  if (json_len != JSON_ERR_BUF_SIZE) {
    Serial.println("ERROR json_len is " + String(json_len));
  }
  Serial.println(String(buf3) + " length: " + json_len);

  // if an argument has no matching pair, is not a fragment or part of an array, it will be a value to empty key
  json(buf512, "value only");
  Serial.println(buf512);  // {"":"value only"}

  // "-{": build a fragment (starts with +|) that can be inserted into a json
  json(buf64, "-{", "str_key2", "str2", "i|int_key2", 8);
  Serial.println(buf64);  // +|"str_key2":"str2","int_key2":8

  // build a json with an object json and a fragment
  json(buf512, "o|obj", buf256, buf64);
  Serial.println(buf512);  // {"obj":{"str_key1":"str1","int_key1":7,"double_key1":3.14,"boolean_key1":true,"object_key1":{},"array_key1":[],"null_key1":null},"str_key2":"str2","int_key2":8}

  // "s[": a string array, the next argument is the number of items
  json(buf64, "s[", 2, "str3", "str4\"inquote\"");
  Serial.println(buf64);  // ["str3","str4\"inquote\""]

  // "i[": an integer array
  json(buf64, "i[", 3, 0, 10, 20);
  Serial.println(buf64);  // [0,10,20]

  // "d[*": a floating number array with 1 to 17 significant digits (a is 10, b is 11 ... h is 17); arguments should be doubles
  json(buf64, "d[7", 4, 0.0, 0.01, 4.44, 1.2345678901234567890);
  Serial.println(buf64);  // [0,0.01,4.44,1.234568]

  // "b[": a boolean array
  json(buf64, "b[", 2, 0, 1);
  Serial.println(buf64);  // [false,true]

  // "o[": an array of mixed values
  json(buf64, "o[", 7, "[]", "{}", "null", "40", "5.55", "false", "\"str5\"");
  Serial.println(buf64);  // [[],{},null,40,5.55,false,"str5"]
}

void loop() {
}
