//
// Created by Sysolyatin Dmitrey on 20/05/2018.
//

#ifndef DBMS_STUDY_IMPLEMENTATION_RECORDWRITTER_H
#define DBMS_STUDY_IMPLEMENTATION_RECORDWRITTER_H

#include <memory>

#include "Page.h"
#include "PageFileManager.h"

class RecordWritter {
private:
    std::shared_ptr<PageFileManager> pageFileManagerPointer;
    std::shared_ptr<Page> lastPage;
    PagePointer lastPagePointer;
public:
    RecordWritter(const RecordWritter&) = delete; // noncopyable

    explicit RecordWritter(std::shared_ptr<PageFileManager> pageFileManagerPointer);

    void write(char * data, uint16_t sizeOfData);
};

#endif //DBMS_STUDY_IMPLEMENTATION_RECORDWRITTER_H
