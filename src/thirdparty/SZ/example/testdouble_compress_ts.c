/**
 *  @file testdouble_compress_ts.c
 *  @author Sheng Di
 *  @date May, 2018
 *  @brief This is an example of using compression interface
 *  (C) 2015 by Mathematics and Computer Science (MCS), Argonne National Laboratory.
 *      See COPYRIGHT in top-level directory.
 */


#include <stdio.h>
#include <stdlib.h>
#include "sz.h"
#include "rw.h"

struct timeval startTime;
struct timeval endTime;  /* Start and end times */
struct timeval costStart; /*only used for recording the cost*/
double totalCost = 0;


void cost_start()
{
	totalCost = 0;
        gettimeofday(&costStart, NULL);
}

void cost_end()
{
        double elapsed;
        struct timeval costEnd;
        gettimeofday(&costEnd, NULL);
        elapsed = ((costEnd.tv_sec*1000000+costEnd.tv_usec)-(costStart.tv_sec*1000000+costStart.tv_usec))/1000000.0;
        totalCost += elapsed;
}


int main(int argc, char * argv[])
{
    int i = 0;
    size_t r5=0,r4=0,r3=0,r2=0,r1=0;
    char oriDir[640], outputDir[640], outputFilePath[600];
    char *cfgFile;
    
    if(argc < 3)
    {
		printf("Test case: testdouble_compress_ts [config_file] [srcDir] [dimension sizes...]\n");
		printf("Example: testdouble_compress_ts sz.config /home/sdi/Data/Hurricane-ISA/consecutive-steps 500 500 100\n");
		exit(0);
    }
   
    cfgFile=argv[1];
    sprintf(oriDir, "%s", argv[2]);
    if(argc>=4)
		r1 = atoi(argv[3]); //8
    if(argc>=5)
		r2 = atoi(argv[4]); //8
    if(argc>=6)
		r3 = atoi(argv[5]); //128
    if(argc>=7)
        r4 = atoi(argv[6]);
    if(argc>=8)
        r5 = atoi(argv[7]);
   
    printf("cfgFile=%s\n", cfgFile); 
    int status = SZ_Init(cfgFile);
    if(status == SZ_NSCS)
		exit(0);
    sprintf(outputDir, "%s", oriDir);
   
    char oriFilePath[600];
    size_t nbEle;
    size_t dataLength = computeDataLength(r5,r4,r3,r2,r1);
    double *data = (double*)malloc(sizeof(double)*dataLength);
    SZ_registerVar("CLOUDf", SZ_FLOAT, data, REL, 0, 0.001, 0, r5, r4, r3, r2, r1);

    if(status != SZ_SCES)
    {
		printf("Error: data file %s cannot be read!\n", oriFilePath);
		exit(0);
    }
   
    size_t outSize; 
    unsigned char *bytes = NULL;
    for(i=1;i<20;i++)
	{
		printf("simulation time step %d\n", i);
		sprintf(oriFilePath, "%s/QCLOUDf%02d.bin.dat", oriDir, i);
		double *data_ = readDoubleData(oriFilePath, &nbEle, &status);
		memcpy(data, data_, nbEle*sizeof(double));
		cost_start();
		SZ_compress_ts(&bytes, &outSize);
		cost_end();
		printf("timecost=%f\n",totalCost); 
		sprintf(outputFilePath, "%s/QCLOUDf%02d.bin.dat.sz2", outputDir, i);
		printf("writing compressed data to %s\n", outputFilePath);
		writeByteData(bytes, outSize, outputFilePath, &status); 
		free(bytes);
		free(data_);
	}
    
    printf("done\n");
    free(data);
    SZ_Finalize();
    
    return 0;
}
