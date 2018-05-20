#include "../include/Page.h"

Page::Page()
{
    this->buffer = new char[PageSize];
    this->pageHeader = new(this->buffer) PageHeader(sizeof(PageHeader), Page::PageSize);
}

Page::Page(char* buffer)
{
    this->buffer = buffer;
    this->pageHeader = (PageHeader*)(buffer);
}

void Page::insert(char* recordPointer, uint16_t recordLength)
{
    if (pageHeader->fsUpper - pageHeader->fsLower < (recordLength + sizeof(RecordPointer))) {
        throw std::bad_alloc();
    }

    uint16_t off = pageHeader->fsUpper - recordLength;
    memcpy(buffer + off, recordPointer, recordLength);
    new(buffer+pageHeader->fsLower) RecordPointer(off, recordLength);

    pageHeader->fsLower += sizeof(RecordPointer);
    pageHeader->fsUpper -= recordLength;

}

char* Page::getBuffer() const
{
    return buffer;
}

Page::~Page()
{
    delete[] this->buffer;
}