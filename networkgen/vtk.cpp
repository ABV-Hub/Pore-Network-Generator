//
//  vtk.cpp
//  networkgen
//
//  Created by Lucas van Oosterhout on 02-12-14.
//  Copyright (c) 2014 Lucas van Oosterhout. All rights reserved.
//

#include "vtk.h"
#include <iostream>
#include <iomanip>
#include <fstream>

/*
 * Write current network to vtk file,
 * Enhance the shit out of this, we want te select what to put in the files
 * Or even better put any and everything in the file!
 */
void writeVTK(const char* filename, PoreNetwork *P_net, char * pb_flags ){
    
    //int PNMax = P_net->ns->Ni*P_net->ns->Nj*P_net->ns->Nk;
    int PNMax = P_net->nrOfActivePBs;
    std::ofstream file;
    if( filename == nullptr){
        std::cerr << "Invalid filename specified! " << std::endl;
    }
    
    std::cout << "Opening File: " << filename << std::endl;
    file.open(filename, std::ios::trunc);
    if(!file){
        std::cerr<< "Error opening file [" << filename << ']' << std::endl;
        return;
    }
    
    file.setf(std::ios_base::scientific );
    
    /*
     * Write the header
     */
    file << "# vtk DataFile Version 3.0"     << std::endl;
    file << "pore-scale field varables"     << std::endl;
    file << "ASCII"                         << std::endl;
    file << "DATASET POLYDATA "             << std::endl;
    file << "POINTS "<<'\t' << PNMax <<'\t'<< "FLOAT"   << std::endl;
    
    
    /*
     * Write pb location data
     */
    for(int pn = 1; pn < (PNMax + 1); pn++){
        file << P_net->locationList[0][pn]<< '\t';
        file << P_net->locationList[1][pn]<< '\t';
        file << P_net->locationList[2][pn] << '\n';
        
    }
    
    /*
     * Write throat data
     */
    int i;
    for(i = 0; i < PNMax * 13; i ++){
        if (P_net->throatList[0][i] == 0)
            break;
    }
    
    int nrOfThroats = i;
    file << "LINES" << '\t'<< nrOfThroats << '\t'<< nrOfThroats * 3 <<std::endl;
    for(i = 0; i < PNMax * 13; i ++){
        if (P_net->throatList[0][i] != 0){
            file<< 2<< '\t' << P_net->throatList[0][i] - 1 << '\t' << P_net->throatList[1][i] - 1 << std::endl;
        // VTK is zero based zo a line from pb[1] to pb[10] -> p[0] - p[9]
        } else
            break;
    }
    
    file << "POINT_DATA" << ' '<<PNMax << '\n'<< "SCALARS size_pb float" << '\n';
    file << "LOOKUP_TABLE default" <<std::endl;
    // Pn Size
    for(int pn = 1; pn < PNMax + 1; pn++){
        file << (float)(int)pb_flags[pn] << '\n';
        //std::cout<< pn << '\t' << (float)(int)pb_flags[pn] << std::endl;
    }
    
    file.close();
    
}

void writeVTK(const char* filename, PoreNetwork *P_net){
    
   
    
    int PNMax = P_net->ns->Ni*P_net->ns->Nj*P_net->ns->Nk;
    
    std::ofstream file;
    if( filename == nullptr){
        std::cerr << "Invalid filename specified! " << std::endl;
    }
    
    std::cout << "Opening File: " << filename << std::endl;
    file.open(filename, std::ios::trunc);
    if(!file){
        std::cerr<< "Error opening file [" << filename << ']' << std::endl;
        return;
    }
    
    file.setf(std::ios_base::scientific );
    
    /*
     * Write the header
     */
    file << "# vtk DataFile Version 3.0"     << std::endl;
    file << "pore-scale field varables"     << std::endl;
    file << "ASCII"                         << std::endl;
    file << "DATASET POLYDATA "             << std::endl;
    file << "POINTS "<<'\t' << PNMax <<'\t'<< "FLOAT"   << std::endl;
    
    
    /*
     * Write pb location data
     */
    for(int pn = 1; pn < (PNMax + 1); pn++){
        file << P_net->locationList[0][pn]<< '\t';
        file << P_net->locationList[1][pn]<< '\t';
        file << P_net->locationList[2][pn] << '\n';
        
    }
    
    /*
     * Write throat data
     */
    int i;
    for(i = 0; i < PNMax * 13; i ++){
        if (P_net->throatList[0][i] == 0)
            break;
    }
    
    int nrOfThroats = i;
    file << "LINES" << '\t'<< nrOfThroats << '\t'<< nrOfThroats * 3 <<std::endl;
    for(i = 0; i < nrOfThroats; i ++){
        file<< 2<< '\t' << P_net->throatList[0][i] - 1 << '\t' << P_net->throatList[1][i] - 1 << std::endl;
        // VTK is zero based zo a line from pb[1] to pb[10] -> p[0] - p[9]
    }
    
    file << "POINT_DATA" << ' '<<PNMax << '\n'<< "SCALARS size_pb float" << '\n';
    file << "LOOKUP_TABLE default" <<std::endl;
    // Pn Size
    for(int pn = 1; pn < PNMax + 1; pn++){
        file << 1.0 << '\n';
    }
    
    file.close();
    
}