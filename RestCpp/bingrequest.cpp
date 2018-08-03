/***
 * Copyright (C) Microsoft. All rights reserved.
 * Licensed under the MIT license. See LICENSE.txt file in the project root for full license information.
 *
 * =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
 *
 * bingrequest.cpp - Simple cmd line application that makes an HTTP GET request to bing searching and outputting
 *       the resulting HTML response body into a file.
 *
 * =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
 ****/

#include <cpprest/http_client.h>
#include <cpprest/filestream.h>

using namespace utility;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency::streams;

/*	Can pass proxy information via environment variable http_proxy.
Example:
Linux:   export http_proxy=http://192.1.8.1:8080
*/
web::http::client::http_client_config client_config_for_proxy()
{
	web::http::client::http_client_config client_config;
	if(const char* env_http_proxy = std::getenv("http_proxy")) {
		std::string env_http_proxy_string(env_http_proxy);
		if (env_http_proxy_string == U("auto"))
			client_config.set_proxy(web::web_proxy::use_auto_discovery);
		else
			client_config.set_proxy(web::web_proxy(env_http_proxy_string));
	}

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
				{
				*fileBuffer = outFile;

				// Create an HTTP request.
				// Encode the URI query since it could contain special characters like spaces.
				http_client client(U("http://localhost:3000"));
				return client.request(methods::GET, uri_builder(U("/responseData")).to_string());
				})
	// Write the response body into the file buffer.
	.then([=](http_response response) -> pplx::task<size_t>
			{
			printf("Response status code %u returned.\n", response.status_code());
			return response.body().read_to_end(*fileBuffer);
			})
	// Close the file buffer.
	.then([=](size_t)
			{
			return fileBuffer->close();
			})
	// Wait for the entire response body to be written into the file.
	.wait();

	return 0;
}
