/*************************************************************************
 * Copyright (c) 2016-2019, NVIDIA CORPORATION. All rights reserved.
 * Modifications Copyright (c) 2019-2020 Advanced Micro Devices, Inc. All rights reserved.
 *
 * See LICENSE.txt for license information
 ************************************************************************/

#ifndef UTILS_H_
#define UTILS_H_

struct allGather1Data_t {
  struct ncclPeerInfo peerInfo;
  struct ncclComm* comm;
  int cudaCompCap;
};

// AllGather3 - begin
struct ncclGraphInfo {
  int pattern;
  int nChannels;
  int sameChannels;
  float speedIntra;
  float speedInter;
  int typeIntra;
  int typeInter;
};

struct allGather3Data_t{
  int collNetSupport;
  int nc;
  struct ncclGraphInfo tree;
  struct ncclGraphInfo ring;
  struct ncclGraphInfo collNet;
  struct ncclTopoRanks topoRanks;
};

void initCollNet();

ncclResult_t ncclTopoGetSystem(const char* xmlTopoFile, struct ncclTopoSystem** system);

ncclResult_t ncclTopoGetSystemFromXml(struct ncclXml* xml, struct ncclTopoSystem** topoSystem);

ncclResult_t bootstrapAllGather(struct ncclComm* comm, struct allGather1Data_t * allGather1Data);

ncclResult_t initTransportsRank_1(struct ncclComm* comm, struct allGather1Data_t *allGather1Data, struct allGather3Data_t *allGather3Data,
  struct ncclTopoGraph& treeGraph, struct ncclTopoGraph& ringGraph, struct ncclTopoGraph& collNetGraph);

ncclResult_t initTransportsRank_3(struct ncclComm* comm, struct allGather3Data_t *allGather3Data,
  struct ncclTopoGraph& treeGraph, struct ncclTopoGraph& ringGraph, struct ncclTopoGraph& collNetGraph);

#endif