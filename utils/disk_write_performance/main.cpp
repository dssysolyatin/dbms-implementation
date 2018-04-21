#include <fstream>
#include <string>
#include <iostream>
#include <chrono>

using namespace std;

class DiskPerformanceChecker {
private:
    fstream fs;
    size_t blockSize;
    size_t writeSize;
public:

    DiskPerformanceChecker(string path, size_t blockSize, size_t writeSize): blockSize(blockSize), writeSize(writeSize) {
        fs.rdbuf()->pubsetbuf(0, 0);
        fs.open(path, fstream::in | fstream::out | fstream::trunc);
    }

    long long int write() {
        fs.seekg(0, ios::beg);

        auto start = chrono::high_resolution_clock::now();
        char * buffer = new char[this->blockSize];
        size_t cycle = (this->writeSize + (this->blockSize - 1)) / this->blockSize;

        for (size_t i = 0; i < cycle; i ++) {
            fs.write(buffer, this->blockSize);
        }

        return chrono::duration_cast<chrono::microseconds>(chrono::high_resolution_clock::now() - start).count();
    }

    long long int read() {
        fs.seekg(0, ios::beg);

        auto start = chrono::high_resolution_clock::now();
        char * buffer = new char[this->blockSize];
        size_t cycle = (this->writeSize + (this->blockSize - 1)) / this->blockSize;

        for (size_t i = 0; i < cycle; i ++) {
            fs.read(buffer, this->blockSize);
        }

        return chrono::duration_cast<chrono::microseconds>(chrono::high_resolution_clock::now() - start).count();
    }

    virtual ~DiskPerformanceChecker()
    {
        fs.close();
    }

};

int main(int argc, char * argv[]) {

    if (argc < 4) {
        cout << "Usage: " << argv[0] << " <filename> <blocksize in bytes> <writesize in bytes>" << std::endl;
        cout << "Output: <write_time_in_microseconds> <read_time_in_microseconds>";

        return 0;
    }

    DiskPerformanceChecker opt(argv[1], (size_t) atoi(argv[2]), (size_t) atoi(argv[3]));

    std::cout << opt.write() << " " << opt.read() << std::endl;

    return 0;
}



