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

      int get(const std::string& url) {
        return 5;
        //return http_get(url.c_str(), NULL);
      }

      ModulePtr bootstrap(ModulePtr m = std::make_shared<Module>())
      {
        //m->add(chaiscript::user_type<http_t>(), "HttpRequest");
        //m->add(chaiscript::fun(&http_t::status_code), "status_code");
        m->add(chaiscript::fun(&get), "http_get");
        return m;
      }
    }
  }
}
