
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

#include "digitization.h"
#include "operatorLoader.h"
#include "globalFunc.h"

#include <map>
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <numeric>



std::vector<int> 
aggregate(std::vector<std::vector<double> > pieces, Model &parameters, double alpha, std::string sorting, bool verbose){
    auto num = (double) pieces.size();
    std::vector<double> indices = arange(num);
    // std::cout << "pieces" << std::endl;
    // print_matrix(pieces);
    if (sorting == "lexi"){
        indices = arg_lexisort(pieces);
    }else if (sorting == "2-norm"){
        indices = argsort_norm(pieces, sorting);
    }else if (sorting == "1-norm"){
        indices = argsort_norm(pieces, sorting);
    }

    int lab = 0;
    std::size_t starting_point;
    std::vector<int> labels;
    labels.insert(labels.end(), num, -1);
    std::vector<std::vector<double> > splist(0); // storing starting point information
    double center_norm, distance; 
    std::vector<double> clustc, center;
    std::string symbol;
    std::vector<std::vector<double> > cpieces_stack(0), centers(0);
    double len_m(0.0), inc_m(0.0);
    for (std::size_t i=0; i<num; i++){
        starting_point = indices[i];
        
        if (labels[starting_point] >= 0){
            continue;
        }else{
            cpieces_stack.clear();
            clustc = pieces[starting_point]; // starting point as temporary center
            cpieces_stack.push_back(clustc);

            labels[starting_point] = lab;
            std::vector<double> insert_sp = {(double)starting_point, (double)lab, clustc[0], clustc[1]};
            splist.push_back(insert_sp);

            if(sorting == "2-norm"){
                center_norm = norm(clustc);
            }else if (sorting == "1-norm"){
                center_norm = clustc[0] + abs(clustc[1]);
            }
        }

        for (auto &j: vslice(indices, i, indices.size())){
            if (labels[j] >= 0) continue;
            // early stopping
            if (sorting == "lexi"){
                if ((pieces[j][0] - pieces[starting_point][0]) > alpha) break;
            }else if (sorting == "2-norm"){
                if (norm(pieces[j]) - center_norm > alpha) break;
            }else if (sorting == "1-norm"){
                if (0.707101 * (pieces[j][0] + abs(pieces[j][1]) - center_norm) > alpha) break;
            }

            distance = norm(clustc - pieces[j]);
            if (distance <= alpha){
                labels[j] = lab;
                cpieces_stack.push_back(pieces[j]);
            }
        }

        symbol = generate_symbol(33 + lab);// ASCII convert *static_cast<unsigned char>
        parameters._hashmap[symbol] = lab; 
        parameters._inverse_hashmap[lab] = symbol; 

        // calculate centers
        for (std::size_t c = 0; c < cpieces_stack.size(); c++){
            len_m = len_m + cpieces_stack[c][0];
            inc_m = inc_m + cpieces_stack[c][1];
        }

        len_m = len_m / cpieces_stack.size();
        inc_m = inc_m / cpieces_stack.size();

        len_m =  parameters._len_Param[1] * len_m + parameters._len_Param[0];
        inc_m =  parameters._inc_Param[1] * inc_m + parameters._inc_Param[0];
        
        center = {len_m, inc_m}; 
        centers.push_back(center);

        len_m = 0.0; inc_m = 0.0;
        lab = lab + 1; 
    }

    if (verbose == true){
        std::cout << "Digitization: Reduced pieces of length " << pieces.size() << " to " << lab << " symbols" << std::endl;
    }
    parameters._centers = centers;
    return labels;
}



Model 
digitize(std::vector<std::vector<double> > pieces, double alpha, std::string sorting, int scl, bool verbose){
    Model parameters;
    pieces = remove_col(pieces,2);
    std::vector<std::vector<double> > spieces = scale_pieces(pieces, parameters, scl);
    std::vector<int> labels = aggregate(spieces, parameters, alpha, sorting, verbose);
    //double label_max = *std::max_element(labels.begin(), labels.end());
    std::vector<std::string> symbols;
    for (int &label : labels){
        symbols.push_back(parameters._inverse_hashmap[label]);
    } 
    parameters._symbols = symbols;
    return parameters;
}




std::vector<std::vector<double> > 
scale_pieces(std::vector<std::vector<double> > pieces, Model &parameters, int scl){
    /*
        Scale the pieces, speed up the aggregation, and reduce the influence of length over increment.
    */
    int num = pieces.size();
    std::vector<double> lens(num); 
    std::vector<double> incs(num); 
    for (std::size_t i=0; i < num; i++){
        lens[i] = pieces[i][0];
        incs[i] = pieces[i][1];
    }
    double len_m(0.0), inc_m(0.0), len_std(0.0), inc_std(0.0);
    cal_standard_value(lens, len_m, len_std);
    cal_standard_value(incs, inc_m, inc_std);

    if (len_std != 0){
        for (std::size_t i=0; i < num; i++){
            pieces[i][0] = pieces[i][0] * scl  / len_std;
            pieces[i][1] = pieces[i][1] / inc_std;
        }
        // parameters._len_Param[0] = len_m;
        parameters._len_Param[1] = len_std;
        // parameters._inc_Param[0] = inc_m;
        parameters._inc_Param[1] = inc_std;

    }else{
        for (std::size_t i=0; i < num; i++){
            pieces[i][0] = pieces[i][0] * scl;
            pieces[i][1] = pieces[i][1] / inc_std;
        }
        // parameters._len_Param[0] = len_m;
        parameters._len_Param[1] = 1;
        // parameters._inc_Param[0] = inc_m;
        parameters._inc_Param[1] = inc_std;
    }

    return pieces;
}



void 
cal_standard_value(std::vector<double> vec, double &mean, double &standard_deviation){
    double sum = std::accumulate(vec.begin(), vec.end(), 0.0);
    mean = sum / vec.size();
    std::vector<double> diff(vec.size());
    std::transform(vec.begin(), vec.end(), diff.begin(), std::bind2nd(std::minus<double>(), mean));
    double square_sum = std::inner_product(diff.begin(), diff.end(), diff.begin(), 0.0);
    standard_deviation = std::sqrt(square_sum / vec.size());
}



std::vector<std::vector<double> > 
inverse_digitize(Model& parameters){
    std::vector<std::vector<double> > pieces(0);
    for (auto & symbol : parameters._symbols){
        pieces.push_back(parameters._centers[parameters._hashmap[symbol]]); //std::string(1, symbol)
    }
    return pieces;
}
