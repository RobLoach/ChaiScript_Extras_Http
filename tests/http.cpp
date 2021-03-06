#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
//#include <sstream>
#include "catch.hpp"

#include <chaiscript/chaiscript.hpp>

/**
 * Load the HTTP library.
 */
#define HTTP_IMPLEMENTATION
#include "../include/chaiscript/extras/http.hpp"

TEST_CASE( "HTTP functions work", "[http]" ) {
  // Build the library.
  auto httplib = chaiscript::extras::http::bootstrap();

  // Create the ChaiScript environment.
  chaiscript::ChaiScript chai;

  // Add the library to the ChaiScript instance.
  chai.add(httplib);

  // Run all the tests.
  chai.eval(R""(
    var request = Http("http://example.com/index.html")

    while (request.process() == "pending") {
      print("Please Wait...")
    }

    if (request.getStatus() == "failed") {
      print("Failed: " + request.getReasonPhrase())
    }

    global response = request.getResponseString()
    print(response)
  )"");

  std::string response = chai.eval<std::string>("response");
  CHECK(response.find("Example Domain") > 10);
}
