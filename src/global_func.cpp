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

#include "globalFunc.h"
#include "operatorLoader.h"
#include <cmath>
#include <vector>
#include <numeric>
#include <cassert>
#include <string>
#include <iostream>
#include <algorithm>



// generate the recognized symbol
std::string 
generate_symbol(int value){
    int asciiv = int(value % 93 + 33);
    char ascii = char(asciiv);
    std::string ascii_s = std::string(1, ascii);
    int period = (int) (value / 93);
    if (period != 0){
        ascii_s = ascii_s.append(std::to_string(period));
    }
    return ascii_s;
}


// range
std::vector<double> 
arange(double series_len){
    std::vector<double> range(series_len);
    std::generate(range.begin(), range.end(), [n = 0] () mutable { return n++; });
    return range;
}

// range
std::vector<double> 
arange(int series_len){
    std::vector<double> range(series_len);
    std::generate(range.begin(), range.end(), [n = 0] () mutable { return n++; });
    return range;
}
    // std::vector<float> range = arange((float)10.0);
    // print_vector(range);



// 2-norm
template <typename T> double 
norm(const std::vector<T>& vec){
    std::vector<T> square_vec;
    square_vec.reserve(vec.size());
    std::transform(vec.begin(), vec.end(), vec.begin(), 
                   std::back_inserter(square_vec), std::multiplies<T>());
    double sum_of_v = std::accumulate(square_vec.begin(), square_vec.end(), 0.0);
    return sqrt(sum_of_v);
}

template double 
norm<int>(const std::vector<int>& vec);

template double 
norm<float>(const std::vector<float>& vec);

template double 
norm<double>(const std::vector<double>& vec);


// sort lexicographically
template <typename T>  std::vector<T> 
arg_lexisort(std::vector<std::vector<T> > array){
    std::vector<T> size_array;
    for (int i = 0; i < array.size(); i++){
        size_array.push_back( abs(array[i][0]) + abs(array[i][1]) );
    }
    double v_max = *std::max_element(size_array.begin(), size_array.end());
    for (int i = 0; i < array.size(); i++){
        size_array[i] = array[i][0] + array[i][1] / (v_max*10);
    }

    // cout << "size array:" << endl; 
    // print_vector(size_array);
    
    std::vector<T> indices(size_array.size()); 
    std::iota(indices.begin(), indices.end(), 0); 
    std::sort(indices.begin(), indices.end(), 
                [&size_array](int left, int right)-> bool {
                    return size_array[left] < size_array[right];
                    });
    return indices;
}


template std::vector<int> 
arg_lexisort<int>(std::vector<std::vector<int> > array);

template std::vector<float> 
arg_lexisort<float>(std::vector<std::vector<float> > array);

template std::vector<double> 
arg_lexisort<double>(std::vector<std::vector<double> > array);


// sort 2d vector
template <typename T> std::vector<T> 
argsort_norm(std::vector<std::vector<T> > array, std::string norm_t){
    std::vector<T> size_array;
    if (norm_t == "2-norm"){
        for (int i = 0; i < array.size(); i++){
            size_array.push_back(norm(array[i]));
        }
    }else{ // 1-norm
        for (int i = 0; i < array.size(); i++){
            size_array.push_back( abs(array[i][0]) + abs(array[i][1]) );
        }
    }

    //std::cout << "size array:" << std::endl; 
    //print_vector(size_array);
    
    std::vector<T> indices(size_array.size()); 
    std::iota(indices.begin(), indices.end(), 0); 
    std::sort(indices.begin(), indices.end(), 
                [&size_array](int left, int right)-> bool {
                    return size_array[left] < size_array[right];
                    });
    return indices;
}

template std::vector<int> 
argsort_norm<int>(std::vector<std::vector<int> > array, std::string norm_t);

template std::vector<float> 
argsort_norm<float>(std::vector<std::vector<float> > array, std::string norm_t);

template std::vector<double> 
argsort_norm<double>(std::vector<std::vector<double> > array, std::string norm_t);



std::vector<std::vector<double> > 
remove_col(std::vector<std::vector<double> > matrix, unsigned deletecol){
    for (unsigned i = 0; i < matrix.size(); ++i){
        if (matrix[i].size() > deletecol)
            matrix[i].erase(matrix[i].begin() + deletecol);
    }
    return matrix;
}


// slice
template <typename T> std::vector<T> 
vslice(std::vector<T> series, int start, int stop){
    typename std::vector<T>::const_iterator first = series.begin() + start;
    typename std::vector<T>::const_iterator last = series.begin() + stop;
    std::vector<T> subseries(first, last);
    return subseries;
}

template std::vector<int> 
vslice<int>(std::vector<int> series, int start, int stop);

template std::vector<float> 
vslice<float>(std::vector<float> series, int start, int stop);

template std::vector<double> 
vslice<double>(std::vector<double> series, int start, int stop);


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% print %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
template <typename T> void 
print_sort_matrix(std::string logs, std::vector<std::vector<T> > matrix, std::vector<T> indices){
    std::cout << logs << std::endl;
    for (int i = 0; i < indices.size(); i++){
        print_vector(logs, matrix[indices[i]]);
    }
}


template void 
print_sort_matrix<int>(std::string logs, std::vector<std::vector<int> > matrix, std::vector<int> indices);

template void 
print_sort_matrix<float>(std::string logs, std::vector<std::vector<float> > matrix, std::vector<float> indices);

template void 
print_sort_matrix<double>(std::string logs, std::vector<std::vector<double> > matrix, std::vector<double> indices);




template <typename T> void 
print_vector(std::string logs, std::vector<T> vec){
    std::cout << logs << std::endl;
    for (int i = 0; i < vec.size(); i++){
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;
}


template void
print_vector<int>(std::string logs, std::vector<int> vec);

template void
print_vector<float>(std::string logs, std::vector<float> vec);

template void
print_vector<double>(std::string logs, std::vector<double> vec);





template <typename T> void 
print_matrix(std::string logs, std::vector<std::vector<T> > matrix){
    std::cout << logs << std::endl;
    for (int i = 0; i < matrix.size(); i++){
        for (int j = 0; j < matrix[i].size(); j++){
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}


template void
print_matrix<int>(std::string logs, std::vector<std::vector<int> > matrix);

template void
print_matrix<float>(std::string logs, std::vector<std::vector<float> > matrix);

template void
print_matrix<double>(std::string logs, std::vector<std::vector<double> > matrix);




template <typename T> std::vector<std::vector<T> > 
quantize(std::vector<std::vector<T> > pieces){
    auto num = (int)pieces.size();
    double corr;
    if (num == 1){
        pieces[0][0] = round(pieces[0][0]);
    }else{
        for(int p=0 ; p<num-1; p++){
            corr = round(pieces[p][0]) - pieces[p][0];
            pieces[p][0] = round(pieces[p][0] + corr);
            pieces[p+1][0] = pieces[p+1][0] - corr;
            if (pieces[p][0] == 0){
                pieces[p][0] = 1;
                pieces[p+1][0] = pieces[p+1][0] - 1;
            }
        }
        pieces[num-1][0] = round(pieces[num-1][0]);
    }
    return pieces;
}


template std::vector<std::vector<int> > 
quantize(std::vector<std::vector<int> > pieces);

template std::vector<std::vector<float> > 
quantize(std::vector<std::vector<float> > pieces);

template std::vector<std::vector<double> > 
quantize(std::vector<std::vector<double> > pieces);

