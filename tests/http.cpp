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
    var request = http_get("http://example.com/index.html")

    while (http_process(request) == "pending") {
      // TODO: Output the status?
    }

    print(to_string(request))
    var response = to_string(request)
    http_release(request)
  )"");

  std::string response = chai.eval<std::string>("response");
  CHECK(response.find("Example Domain") > 10);


}
