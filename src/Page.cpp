#include "../include/Page.h"

Page::Page()
{
    this->buffer = new char[PageSize];
    this->pageHeader = new(buffer+(PageSize-sizeof(PageHeader))) PageHeader(0, MaxFreeSpace);
}

Page::Page(char* buffer)
{
    this->buffer = buffer;
    this->pageHeader = (PageHeader*)(buffer+(PageSize-sizeof(PageHeader)));
}

void Page::insertRecord(char* recordPointer, uint16_t recordLength)
{
    if (pageHeader->fsUpper-pageHeader->fsLower<recordLength) {
        throw std::bad_alloc();
    }
    memcpy(buffer+pageHeader->fsLower, recordPointer, recordLength);
    new(buffer+pageHeader->fsUpper) RecordPointer(pageHeader->fsLower, recordLength);

    pageHeader->fsLower += recordLength;
    pageHeader->fsUpper -= sizeof(RecordPointer);

}

char* Page::getBuffer() const
{
    return buffer;
}

Page::~Page()
{
    delete[] this->buffer;
}