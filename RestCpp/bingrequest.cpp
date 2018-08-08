#include <strstream>

#include <cpprest/http_client.h>
#include <cpprest/filestream.h>

using namespace utility;
using namespace web::http;
using namespace web;
using namespace web::http::client;
using namespace concurrency::streams;
using namespace std;

int main(int argc, char *argv[])
{
	if (argc != 2) {
		std::cout << "need key" << std::endl;
		return 0;
	}
	auto key = argv[1];
	auto url = "http://localhost:3000/dbs";

	http_client client(url);
	client.request(methods::GET)
		.then([](http_response response) -> pplx::task<json::value>
				{
					if(response.status_code() == status_codes::OK)
				{
					return response.extract_json();
				}

					// Handle error cases, for now return empty json value...
					return pplx::task_from_result(json::value());
				})
	.then([&key](pplx::task<json::value> previousTask){
			try
			{
				const json::value& v = previousTask.get();
				cout << v.as_object().at(key).serialize() <<endl;
			}
			catch (const http_exception& e)
			{
				// Print error.
				wostringstream ss;
				ss << e.what() << endl;
				wcout << ss.str();
			}
			}).wait();
	return 0;
}
