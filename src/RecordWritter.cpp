#include "RecordWritter.h"

RecordWritter::RecordWritter(std::shared_ptr<PageFileManager> pageFileManagerPointer)
        :pageFileManagerPointer(pageFileManagerPointer)
{
    this->lastPagePointer = (pageFileManagerPointer->sizeOfFile() / Page::PageSize) * Page::PageSize;

    if (0 == pageFileManagerPointer->sizeOfFile()%Page::PageSize) {
        this->lastPage = std::make_shared<Page>();
    }
    else {
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
