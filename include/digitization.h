#ifndef DIGITIZATION_H
#define DIGITIZATION_H

/*
* Copyright (c) 2021, Stefan Güttel, Xinye Chen
* Licensed under BSD 3-Clause License
* All rights reserved.
*

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>

#include "operatorLoader.h"
#include "globalFunc.h"


struct Model{
    int _scl = 1;
    double _len_Param[2] = {0.0, 0.0};
    double _inc_Param[2] = {0.0, 0.0};
    std::vector<std::string> _symbols;
    std::map<std::string, int> _hashmap;
    std::map<int, std::string> _inverse_hashmap;
    std::vector<std::vector<double> > _centers;
};


void 
cal_standard_value(std::vector<double>,  double &, double &);


std::vector<std::vector<double> > 
scale_pieces(std::vector<std::vector<double> >, Model &, int scl=1);

std::vector<int> 
aggregate(std::vector<std::vector<double> >, Model &, double alpha=0.5, std::string sorting="2-norm", bool verbose=true);

Model 
digitize(std::vector<std::vector<double> >, double alpha=0.5, std::string sorting="2-norm", int scl=1, bool verbose=true);


std::vector<std::vector<double> > 
inverse_digitize(Model& parameters);

#endif // DIGITIZATION_H
