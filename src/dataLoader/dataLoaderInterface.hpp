#ifndef _DATA_LOADER_INTERFACE_H_
#define _DATA_LOADER_INTERFACE_H_

#include <string>
#include <mpi.h>
#include <sstream>

class DataLoaderInterface
{
  protected:
    std::string loader;
    std::string filename;
    size_t totalNumberOfElements;

    std::string dataType;
    std::string param;

    size_t numElements;
	size_t elemSize;
    //void *data;

    MPI_Comm comm;
    std::stringstream log;

  public:
    virtual void init(std::string _filename, MPI_Comm _comm) = 0;
    virtual int loadData(std::string paramName) = 0;
    virtual int close() = 0;

	size_t size() { return numElements; }
	size_t type() { return elemSize; }
    std::string getDataInfo();
    std::string getLog() { return log.str(); }

    void *data;
};


inline std::string DataLoaderInterface::getDataInfo()
{
    std::stringstream dataInfo;
    dataInfo << "\nLoader type: " << loader << std::endl;
    dataInfo << "Filename: " << filename << std::endl;
    dataInfo << "Total number of elements: " << totalNumberOfElements << std::endl;
    dataInfo << "Param: " << param << std::endl;
    dataInfo << "dataType: " << dataType << std::endl;
    dataInfo << "numElements: " << numElements << std::endl;

    return dataInfo.str();
}

#endif
