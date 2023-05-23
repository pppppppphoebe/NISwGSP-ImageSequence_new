//
//  main.cpp
//  UglyMan_Stitching
//
//  Created by uglyman.nothinglo on 2015/8/15.
//  Copyright (c) 2015 nothinglo. All rights reserved.
//

#include <iostream>
#include "./Stitching/NISwGSP_Stitching.h"
#include "./Debugger/TimeCalculator.h"
#include <dirent.h>

using namespace std;


int main(int argc, const char * argv[]) {
    Eigen::initParallel(); /* remember to turn off "Hardware Multi-Threading */
    cout << "nThreads = " << Eigen::nbThreads() << endl;
    cout << "[#Images : " << argc - 1 << "]" << endl;

    TimeCalculator timer;

    for(int i = 1; i < argc; ++i) {
        cout << ", [Images : " << argv[i] << "]" << endl;
        MultiImages multi_images(argv[i], LINES_FILTER_WIDTH, LINES_FILTER_LENGTH);
        
        timer.start();
        /* 2D */
        NISwGSP_Stitching niswgsp(multi_images);

        /* 3D */
        niswgsp.setWeightToAlignmentTerm(1.0);
        niswgsp.setWeightToLocalSimilarityTerm(0.5);
        niswgsp.setWeightToGlobalSimilarityTerm(6, 20, GLOBAL_ROTATION_2D_METHOD);
        niswgsp.solve(BLEND_LINEAR);

        timer.end("[NISwGSP] " + multi_images.parameter.file_name);
  
    }
    return 0;
}
