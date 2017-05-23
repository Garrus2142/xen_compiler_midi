#include "ArgsParser.h"
#include <iostream>

using namespace std;

ArgsParser::ArgsParser(int argc, char **argv, const string &allowedOptions)
{
    parseArgs(argc, argv, allowedOptions);
}

void ArgsParser::parseArgs(int argc, char **argv, const string &allowedOptions)
{
    bool stopOptions(false);

    m_operands.clear();
    m_options.clear();
    m_error = false;

    for (int i = 1; i < argc; ++i)
    {
        string arg(argv[i]);

        if (stopOptions)
            m_operands.push_back(arg);
        else {
            if (arg == "--") {
                stopOptions = true;
            }
            else if (arg[0] != '-')
            {
                stopOptions = true;
                m_operands.push_back(arg);
            }
            else {
                // Options
                string substr(arg.substr(1));

                if (substr.find_first_not_of(allowedOptions) != string::npos)
                {
                    m_error = true;
                    return ;
                }

                for (size_t u = 0; u < substr.size(); ++u)
                {
                    if (m_options.find(substr[u]) == string::npos)
                        m_options += substr[u];
                }
            }
        }
    }
}

bool ArgsParser::hasError() const
{
    return (m_error);
}

bool ArgsParser::hasOption(char opt) const
{
    if (m_options.find(opt) != string::npos)
        return (true);
    return (false);
}

vector<string> ArgsParser::getOperands() const
{
    return (m_operands);
}
