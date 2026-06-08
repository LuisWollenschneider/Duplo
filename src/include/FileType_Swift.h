#ifndef _FILETYPE_Swift_H_
#define _FILETYPE_Swift_H_

#include "FileTypeBase.h"

struct FileType_Swift : public FileTypeBase {
    FileType_Swift(bool ignorePrepStuff, unsigned minChars);

    ILineFilterPtr CreateLineFilter() const override;

    std::string GetCleanLine(const std::string& line) const override;

    bool IsPreprocessorDirective(const std::string& line) const override;
};

#endif
