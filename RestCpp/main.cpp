#include <cpprest/json.h>
using namespace web;

int main()
{
  // Create a JSON object.
  json::value obj;
  obj["key1"] = json::value::boolean(false);
  obj["key2"] = json::value::number(44);
  obj["key3"] = json::value::number(43.6);
  obj["key4"] = json::value::string(("str"));

  // Loop over each element in the object.
  for(auto iter = obj.cbegin(); iter != obj.cend(); ++iter)
  {
    // Make sure to get the value as const reference otherwise you will end up copying
    // the whole JSON value recursively which can be expensive if it is a nested object.
    const json::value &str = iter->first;
    const json::value &v = iter->second;

    // Perform actions here to process each string and value in the JSON object…
    wprintf("String:%s", str.as_string());
    wprintf("Value:%s", v.to_string());
  }
  return 0;
}
