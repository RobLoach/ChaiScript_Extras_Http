#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
//#include <sstream>
#include "catch.hpp"

#include <chaiscript/chaiscript.hpp>
#include <chaiscript/chaiscript_stdlib.hpp>

#include <iostream>

/**
 * Load the HTTP library.
 */
#define HTTP_IMPLEMENTATION
#include "../include/chaiscript/extras/http.hpp"

#include <iostream>

TEST_CASE( "HTTP functions work", "[http]" ) {
  // Build the library.
  auto httplib = chaiscript::extras::http::bootstrap();
  
	std::cout << "Start" << std::endl;
  chaiscript::ChaiScript chai;

	std::cout << "httplib" << std::endl;

	std::cout << "httplib" << std::endl;
  // Add the library to the ChaiScript instance.
  chai.add(httplib);

	std::cout << "http_get" << std::endl;
  // get()
  CHECK(chai.eval<int>("http_get()") == 5);
	std::cout << "End" << std::endl;
}

