# ChaiScript Extras Http

Provides [ChaiScript](https://github.com/ChaiScript/ChaiScript) bindings to make HTTP requests with [http.h](https://github.com/mattiasgustavsson/libs/blob/master/docs/http.md).

## Usage

1. Include [`include/chaiscript/extras/http.hpp`](include/chaiscript/extras/curl.hpp)
2. Include the module source...
  ```
  #define HTTP_IMPLEMENTATION
  #include "../include/chaiscript/extras/http.hpp"
  ```
3. Add the module to the ChaiScript instance...
  ```
  auto httplib = chaiscript::extras::http::bootstrap();
  chai.add(httplib);
  ```

## Development

```
mkdir build
cd build
cmake ..
make
make test
```

## License

[MIT](LICENSE)
