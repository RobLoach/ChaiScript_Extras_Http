#include <string>

#include <chaiscript/chaiscript.hpp>

#ifdef __cplusplus
extern "C" {
#endif
#include "http.h"
#ifdef __cplusplus
}
#endif

namespace chaiscript {
  namespace extras {
    namespace http {

      http_t* get(const std::string& url) {
        return http_get(url.c_str(), NULL);
      }

      std::string process(http_t* http) {
        http_status_t status = http_process(http);
        if (status == HTTP_STATUS_PENDING) {
          return "pending";
        }
        if (status == HTTP_STATUS_COMPLETED) {
          return "completed";
        }
        if (status == HTTP_STATUS_FAILED) {
            return "failed";
        }
        return "unknown";
      }

      ModulePtr bootstrap(ModulePtr m = std::make_shared<Module>())
      {
        // HttpRequest
        m->add(user_type<http_t>(), "HttpRequest");
        m->add(fun(&http_t::status_code), "status_code");
        m->add(fun(&http_t::response_size), "response_size");

        // http_get()
        m->add(fun(&chaiscript::extras::http::get), "http_get");

        // http_release()
        m->add(fun(&http_release), "http_release");

        // http_process()
        m->add(fun(&chaiscript::extras::http::process), "http_process");

        // to_string()
        m->add(type_conversion<http_t*, const std::string &>(
              [](http_t* httpRequest) { 
                void* data = httpRequest->response_data;
                const char* stringData = static_cast<const char*>(data);
                return std::string(stringData);
              }
            ));
        return m;
      }
    }
  }
}
