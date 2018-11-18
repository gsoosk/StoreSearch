#ifndef TOOLS
#define TOOLS
#include <string>
#include <vector>
#define EMPTY_STRING ""
#define END_OF_FILES "END_OF_FILES"
#define FIFO_FILE_PATH "namedPipe/fifo"


class Tools
{
public:
    static std::string removeAllSpaces(std::string);
	static std::vector<std::string> splitByCharacter(std::string line, char character);
	static bool doesStringContainsChar(std::string line, char character);
};
#endif