#include "RecordWritter.h"
#include <iostream>

RecordWritter::RecordWritter(std::shared_ptr<PageFileManager> pageFileManagerPointer)
        :pageFileManagerPointer(pageFileManagerPointer)
{

    bool isEmpty = (0 == pageFileManagerPointer->sizeOfFile());

    if (true == isEmpty) {
        this->lastPagePointer = 0;
        this->lastPage = std::make_shared<Page>();
    } else {
        this->lastPagePointer = ((pageFileManagerPointer->sizeOfFile() - 1) / Page::PageSize)*Page::PageSize;
        this->lastPage = std::shared_ptr<Page>(this->pageFileManagerPointer->read(this->lastPagePointer));
    }
}

void RecordWritter::write(char* data, uint16_t sizeOfData)
{
    try {
        this->lastPage->insert(data, sizeOfData);
        this->pageFileManagerPointer->write(*this->lastPage, this->lastPagePointer);
    }
    catch (std::bad_alloc e) {
        this->lastPage = std::make_shared<Page>();
        this->lastPagePointer += Page::PageSize;

        this->write(data, sizeOfData);
    }
}
