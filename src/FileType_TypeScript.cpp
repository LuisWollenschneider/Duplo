#include "FileType_TypeScript.h"
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

    bool StartsWithRequireCall(const std::string& line, std::string::size_type index) {
        return line.compare(index, 8, "require(") == 0 || line.compare(index, 9, "require (") == 0;
    }

    bool IsCommonJsRequire(const std::string& line) {
        if (StartsWithRequireCall(line, 0))
            return true;

        const char* declarations[] = { "const", "let", "var" };
        for (auto declaration : declarations) {
            if (!StartsWithKeyword(line, declaration))
                continue;

            const auto assignment = line.find('=');
            if (assignment == std::string::npos)
                return false;

            const auto right = line.find_first_not_of(" \t", assignment + 1);
            return right != std::string::npos && StartsWithRequireCall(line, right);
        }

        return false;
    }
}

FileType_TypeScript::FileType_TypeScript(bool ignorePrepStuff, unsigned minChars)
    : FileTypeBase(ignorePrepStuff, minChars) {
}

ILineFilterPtr FileType_TypeScript::CreateLineFilter() const {
    return std::make_shared<CstyleCommentsLineFilter>();
}

std::string FileType_TypeScript::GetCleanLine(const std::string& line) const {
    return CstyleUtils::RemoveSingleLineComments(line);
}

bool FileType_TypeScript::IsPreprocessorDirective(const std::string& line) const {
    size_t first = line.find_first_not_of(" \t\r\n");
    if (first == std::string::npos)
        return false;

    const auto directive = line.substr(first);
    return StartsWithKeyword(directive, "import")
        || StartsWithKeyword(directive, "export")
        || IsCommonJsRequire(directive);
}
