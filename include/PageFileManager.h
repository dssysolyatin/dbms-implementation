//
// Created by Sysolyatin Dmitrey on 20/05/2018.
//

#ifndef DBMS_STUDY_IMPLEMENTATION_PAGEFILEMANAGER_H
#define DBMS_STUDY_IMPLEMENTATION_PAGEFILEMANAGER_H

#include <fstream>
#include <string>

#include "Page.h"

typedef off_t PagePointer; // offset to start of file

class PageFileManager {
private:
    std::fstream fs;
public:
    PageFileManager(const PageFileManager&) = delete; // noncopyable

    explicit PageFileManager(const std::string& path);

    Page* read(const PagePointer& pagePointer);

    void write(const Page& page, const PagePointer& pagePointer);

};

#endif //DBMS_STUDY_IMPLEMENTATION_PAGEFILEMANAGER_H
