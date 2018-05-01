#include <string>
#include <memory>

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

			class Http {
				public:
				Http(const std::string& url);
				int getStatusCode();
				~Http();
				std::string process();
				std::string getStatus();
				std::string getContentType();
				std::string getReasonPhrase();
				std::string getResponseString();
				int getResponseSize();
				void* getResponse();

				private:
				http_t* m_request;
			};

			#ifdef HTTP_IMPLEMENTATION
				Http::Http(const std::string& url) {
					m_request = http_get(url.c_str(), NULL);
				}
				int Http::getStatusCode() {
					return m_request->status_code;
				}
				Http::~Http() {
					http_release(m_request);
					m_request = NULL;
				}
				std::string Http::process() {
					http_status_t status = http_process(m_request);
					switch (status) {
						case HTTP_STATUS_PENDING:
							return "pending";
						case HTTP_STATUS_COMPLETED:
							return "completed";
						case HTTP_STATUS_FAILED:
							return "failed";
					}
					return "unknown";
				}

				std::string Http::getStatus() {
					switch (m_request->status) {
						case HTTP_STATUS_PENDING:
							return "pending";
						case HTTP_STATUS_COMPLETED:
							return "completed";
						case HTTP_STATUS_FAILED:
							return "failed";
					}
					return "unknown";
				}
				std::string Http::getContentType(){
					return std::string(m_request->content_type);
				}
				std::string Http::getReasonPhrase(){
					return std::string(m_request->reason_phrase);
				}
				std::string Http::getResponseString() {
	                const char* stringData = static_cast<const char*>(m_request->response_data);
	                return std::string(stringData);
				}
				int Http::getResponseSize() {
					return m_request->response_size;
				}
			#endif

			ModulePtr bootstrap(ModulePtr m = std::make_shared<Module>()) {
				m->add(user_type<Http>(), "Http");
				m->add(constructor<Http(const std::string&)>(), "Http");
				m->add(fun(&Http::getStatusCode), "getStatusCode");
				m->add(fun(&Http::process), "process");
				m->add(fun(&Http::getContentType), "getContentType");
				m->add(fun(&Http::getStatus), "getStatus");
				m->add(fun(&Http::getReasonPhrase), "getReasonPhrase");
				m->add(fun(&Http::getResponseSize), "getResponseSize");
				m->add(fun(&Http::getResponseString), "getResponseString");
				return m;
			}
		}
	}
}
