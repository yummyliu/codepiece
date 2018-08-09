#include <strstream>

#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <cpprest/streams.h>

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

<<<<<<< HEAD
	return client_config;
}


int main(int argc, char *args[])
{
	if(argc != 2)
	{
		printf("Usage: BingRequest search_term output_file\n");
		return -1;
	}
	//	const string_t searchTerm = args[1];
	const string_t outputFileName = args[1];
	auto fileBuffer = std::make_shared<streambuf<uint8_t>>();

	// Open a stream to the file to write the HTTP response body into.
	file_buffer<uint8_t>::open(outputFileName, std::ios::out)
		.then([=](streambuf<uint8_t> outFile) -> pplx::task<http_response>
=======
	http_client client(url);
	client.request(methods::GET)
		.then([](http_response response) -> pplx::task<json::value>
>>>>>>> ca72155babb329750f442d0d50a028b8623b4237
				{
					if(response.status_code() == status_codes::OK)
				{
					return response.extract_json();
				}

<<<<<<< HEAD
				// Create an HTTP request.
				// Encode the URI query since it could contain special characters like spaces.
				http_client client(U("http://localhost:3000"));
				return client.request(methods::GET, uri_builder(U("/dbinfo")).to_string());
=======
					// Handle error cases, for now return empty json value...
					return pplx::task_from_result(json::value());
>>>>>>> ca72155babb329750f442d0d50a028b8623b4237
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
