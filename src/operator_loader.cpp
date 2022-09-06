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

#include <functional>
#include "operatorLoader.h"
#include <vector>
#include <cassert>
#include <algorithm>

// scalar + vector 
template <typename T> std::vector<T> 
operator+(const T scalar, std::vector<T> vec) {
    transform(vec.begin(), vec.end(), vec.begin(),
        bind2nd(std::plus<T>(), scalar));     
    return vec;
}


template std::vector<int>
operator+<int>(const int scalar, std::vector<int> vec);

template std::vector<float>
operator+<float>(const float scalar, std::vector<float> vec);

template std::vector<double>
operator+<double>(const double scalar, std::vector<double> vec);

// vector - vector
template <typename T> std::vector<T> 
operator-(const std::vector<T>& vec1, const std::vector<T>& vec2) {
    assert(vec1.size() == vec2.size());
    std::vector<T> vec;
    vec.reserve(vec1.size());
    std::transform(vec1.begin(), vec1.end(), vec2.begin(),
                std::back_inserter(vec), std::minus<T>());
    return vec;
}

template std::vector<int>
operator-<int>(const std::vector<int>& vec1, const std::vector<int>& vec2);

template std::vector<float>
operator-<float>(const std::vector<float>& vec1, const std::vector<float>& vec2);

template std::vector<double>
operator-<double>(const std::vector<double>& vec1, const std::vector<double>& vec2);


// scalar * vector  
template <typename T> std::vector<T> 
operator*(const T scalar, std::vector<T>& vec) {
    transform(vec.begin(), vec.end(), vec.begin(),
        bind2nd(std::multiplies<T>(), scalar));     
    return vec;
}

template std::vector<int>
operator*<int>(const int scalar, std::vector<int>& vec);

template std::vector<float>
operator*<float>(const float scalar, std::vector<float>& vec);

template std::vector<double>
operator*<double>(const double scalar, std::vector<double>& vec);



// vector + vector
template <typename T> std::vector<T> 
operator+(const std::vector<T>& vec1, const std::vector<T>& vec2) {
    assert(vec1.size() == vec2.size());
    std::vector<T> vec;
    vec.reserve(vec1.size());
    std::transform(vec1.begin(), vec1.end(),
                    vec2.begin(), std::back_inserter(vec),
                    std::plus<T>());
    return vec;
}


template std::vector<int>
operator+<int>(const std::vector<int>& vec1, const std::vector<int>& vec2);

template std::vector<float>
operator+<float>(const std::vector<float>& vec1, const std::vector<float>& vec2);

template std::vector<double>
operator+<double>(const std::vector<double>& vec1, const std::vector<double>& vec2);


