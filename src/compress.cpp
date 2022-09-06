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

#include "compress.h"
#include "globalFunc.h"
#include "operatorLoader.h"

#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>


// Compression
std::vector<std::vector<double> > 
compress(std::vector<double>& series, double tol, int max_len, bool verbose){
    int start(0), end(1);
    int series_len = series.capacity();
    std::vector<std::vector<double> > pieces(0);
    std::vector<double> range(series_len), subrange, errors;
    std::generate(range.begin(), range.end(), [n = 0] () mutable { return n++; });
    std::vector<double> last_piece = {0.0, 0.0, 0.0};
    double eps = std::numeric_limits<double>::epsilon();
    double inc(0.0), err(0.0);

    while (end < series_len){
        inc = series[end] - series[start];
        subrange = vslice(range, 0, end-start+1);
        errors = series[start] + (inc / (end-start)) * subrange;
        errors = errors - vslice(series, start, end+1);
        err = norm(errors);

        if ((pow(err,2) <= tol*(end-start-1) + eps) && (end-start-1 < max_len)){
            last_piece[1] = inc; last_piece[2] = err;
            end = end + 1;
        }else{
            last_piece[0] = end-start-1;
            pieces.push_back(last_piece);
            start = end - 1;
        }
    }

    last_piece[0] = end - start - 1;
    pieces.push_back(last_piece);

    if (verbose){
        std::cout << "Compression: Reduced time series of length " << series.size() << " to " << pieces.size() << " segments" << std::endl;
    }

    return pieces;
}



template <typename T> std::vector<T> 
stable_range(T n){
    std::vector<T> inc_range;
    for(int i=0; i<n; i++){
        inc_range.push_back(i);
    }
    return inc_range;
}



template std::vector<int> stable_range<int>(int n);

template std::vector<float> stable_range<float>(float n);

template std::vector<double> stable_range<double>(double n);



std::vector<double> 
inverse_compress(std::vector<std::vector<double> >& pieces, double& start){
    std::vector<double> series = {start}, x, y, srange;
    
    double scale;
    for(int i=0; i < pieces.size(); i++){
        scale = pieces[i][1] / pieces[i][0];
        srange = stable_range(pieces[i][0] + 1.0); 
        x = scale * srange;
        y = series[series.size()-1] + x; //*(series.end()-1) + x;
        series.insert(series.end(), y.begin()+1, y.end()); 
    }
    return series;
}
