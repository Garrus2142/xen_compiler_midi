#include <vector>
#include <string>
#include "strUtils.h"

class ArgsParser
{
public:
    ArgsParser(int argc, char **argv, const std::string &allowedOptions = "");

    void parseArgs(int argc, char **argv, const std::string &allowedOptions = "");
    bool hasError() const;
    bool hasOption(char opt) const;
    std::vector<std::string> getOperands() const;

private:
    std::vector<std::string> m_operands;
    std::string m_options;
    bool m_error;

    bool isAlpha(std::string std);
};
