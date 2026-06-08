#include "FileType_Swift.h"
#include "CstyleCommentsFilter.h"
#include "Utils.h"

#include <cctype>
#include <cstring>

namespace {
    bool StartsWithKeyword(const std::string& line, const char* keyword) {
        const auto length = std::strlen(keyword);
        if (line.compare(0, length, keyword) != 0)
            return false;

        if (line.size() == length)
            return true;

        const auto next = static_cast<unsigned char>(line[length]);
        return std::isspace(next) || line[length] == '{' || line[length] == '*';
    }
}

FileType_Swift::FileType_Swift(bool ignorePrepStuff, unsigned minChars)
    : FileTypeBase(ignorePrepStuff, minChars) {
}

ILineFilterPtr FileType_Swift::CreateLineFilter() const {
    return std::make_shared<CstyleCommentsLineFilter>();
}

std::string FileType_Swift::GetCleanLine(const std::string& line) const {
    return CstyleUtils::RemoveSingleLineComments(line);
}

bool FileType_Swift::IsPreprocessorDirective(const std::string& line) const {
    size_t first = line.find_first_not_of(" \t\r\n");
    if (first == std::string::npos)
        return false;

    // Swift compiler control statements (#if, #available, #selector, ...)
    if (line[first] == '#')
        return true;

    return StartsWithKeyword(line.substr(first), "import");
}
