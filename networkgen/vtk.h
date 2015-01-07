//
//  vtk.h
//  networkgen
//
//  Created by Lucas van Oosterhout on 02-12-14.
//  Copyright (c) 2014 Lucas van Oosterhout. All rights reserved.
//

#ifndef __networkgen__vtk__
#define __networkgen__vtk__

#include "PoreNetwork.h"

void writeVTK(const char* filename, PoreNetwork *P_net, char * pb_flags, const int precision = 0);

void writeVTK(const char* filename, PoreNetwork *P_net, const int precision = 0);

#endif /* defined(__networkgen__vtk__) */
