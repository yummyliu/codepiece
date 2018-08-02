#include <cpprest/http_client.h>
#include<cpprest/filestream.h>
#include <cpprest/uri.h>

using namespace concurrency::streams;
using namespace web::http::client;
using namespace web::http;

int main()
{
  // Open stream to file.
  file_stream<unsigned char>::open_istream("myfile.txt").then([](basic_istream<unsigned char> fileStream)
  {
    // Make HTTP request with the file stream as the body.
    http_client client("http://www.myhttpserver.com");
    client.request(methods::PUT, "myfile", fileStream).then([fileStream](http_response response)
    {
      fileStream.close();
      // Perform actions here to inspect the HTTP response…
      if(response.status_code() == status_codes::OK)
      {
      }
    });
  });

  return 0;
}
