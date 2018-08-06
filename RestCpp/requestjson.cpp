#include <iostream>
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <cpprest/json.h>

using namespace std;
using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency::streams;

pplx::task<void> RequestJSONValueAsync()
{
	// TODO: To successfully use this example, you must perform the request
	// against a server that provides JSON data.
	// This example fails because the returned Content-Type is text/html and not application/json.
	http_client client("http://localhost:3000/responseData");
	return client.request(methods::GET).then([](http_response response) -> pplx::task<json::value>
			{
			if(response.status_code() == status_codes::OK)
			{
			return response.extract_json();
			}

			// Handle error cases, for now return empty json value...
			return pplx::task_from_result(json::value());
			})
	.then([](pplx::task<json::value> previousTask)
			{
			try
			{
			const json::value& v = previousTask.get();
			cout << v.serialize() <<endl;
			// Perform actions here to process the JSON value...
			}
			catch (const http_exception& e)
			{
			// Print error.
			wostringstream ss;
			ss << e.what() << endl;
			wcout << ss.str();
			}
			});

	/* Output:
	   Content-Type must be application/json to extract (is: text/html)
	   */
}

int main()
{
	// This example uses the task::wait method to ensure that async operations complete before the app exits.
	// In most apps, you typically don�t wait for async operations to complete.

	cout << "Calling RequestJSONValueAsync..." << endl;
	RequestJSONValueAsync().wait();

	cout << "Calling IterateJSONValue..." << endl;
	for (auto i = ; i < count; ++i) {
		
	}
	return 0;
}
