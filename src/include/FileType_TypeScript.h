#ifndef _FILETYPE_TYPESCRIPT_H_
#define _FILETYPE_TYPESCRIPT_H_

#include "FileTypeBase.h"

struct FileType_TypeScript : public FileTypeBase {
    FileType_TypeScript(bool ignorePrepStuff, unsigned minChars);

    ILineFilterPtr CreateLineFilter() const override;

    std::string GetCleanLine(const std::string& line) const override;

    bool IsPreprocessorDirective(const std::string& line) const override;
};

#endif
