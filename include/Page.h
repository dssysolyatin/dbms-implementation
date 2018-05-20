//
// Created by Sysolyatin Dmitrey on 20/05/2018.
//

#ifndef DBMS_STUDY_IMPLEMENTATION_PAGE_H
#define DBMS_STUDY_IMPLEMENTATION_PAGE_H

#include <cstdint>
#include <cstring>
#include <new>

struct RecordPointer {
    uint16_t offset;
    uint16_t len;

    RecordPointer(unsigned int offset, unsigned int len)
            :offset(offset), len(len) {}
};

struct PageHeader {
    uint16_t fsLower; /* offset to start of free space */
    uint16_t fsUpper; /* offset to end of free space */
    RecordPointer rPointers[]; /* line pointer array */

    PageHeader(const PageHeader&) = delete; // non-copyable

    explicit PageHeader(uint16_t fsLower, uint16_t fsUpper)
            :fsLower(fsLower), fsUpper(fsUpper) {}
};

struct Page {
private:
    char* buffer;
    PageHeader* pageHeader;
public:
    const static uint16_t PageSize = 8192;
    constexpr static uint16_t MaxFreeSpace = PageSize-sizeof(PageHeader)-sizeof(RecordPointer);
public:
    Page(const Page&) = delete; // non-copyable

    explicit Page(void);
    explicit Page(char *);

    void insert(char* recordPointer, uint16_t recordLength);

    char* getBuffer() const;

    virtual ~Page();
};

#endif //DBMS_STUDY_IMPLEMENTATION_PAGE_H
