#include "../include/PageFileManager.h"

PageFileManager::PageFileManager(const std::string& path)
{
    fs.rdbuf()->pubsetbuf(0, 0);
    fs.open(path, std::fstream::in | std::fstream::out | std::fstream::trunc);
}

Page * PageFileManager::read(const PagePointer& pagePointer)
{
    fs.seekg(pagePointer, std::ios::beg);
    char * buffer = new char[Page::PageSize];

    fs.read(buffer, Page::PageSize);

    return new Page(buffer);
}

void PageFileManager::write(const Page& page, const PagePointer& pagePointer)
{
    fs.seekg(pagePointer, std::ios::beg);

    fs.write(page.getBuffer(), Page::PageSize);
}
