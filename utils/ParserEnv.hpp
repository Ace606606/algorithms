// ParserEnv.hpp
#include <string>
#include <utility>
#include <vector>

enum class ParserStatus { OK = 0, FILE_OPEN_ERROR = 1, INVALID_KEY = 2 };

class ParserEnv {
   public:
    explicit ParserEnv(const std::string& path_to_env);
    ~ParserEnv();
    ParserStatus read_env_file(char token = '=');
    std::vector<std::pair<std::string, std::string>> get_env_vars() const;
    std::string to_string_status(ParserStatus status) const;

   private:
    std::string path_to_env_;
    std::vector<std::pair<std::string, std::string>> env_vars_;
};