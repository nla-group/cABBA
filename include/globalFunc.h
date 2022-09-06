#ifndef GLOBALFUNC_H
#define GLOBALFUNC_H

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

#include <vector>
#include <string>

std::string 
generate_symbol(int value);

std::vector<double> 
arange(double series_len);

std::vector<double> 
arange(int series_len);

template <typename T> double 
norm(const std::vector<T>&);

template <typename T> std::vector<T> 
vslice(std::vector<T>, int, int);

template <typename T> std::vector<T> 
arg_lexisort(std::vector<std::vector<T> >);

template <typename T> std::vector<T> 
argsort_norm(std::vector<std::vector<T> >, std::string norm_t="2-norm");

std::vector<std::vector<double> > 
remove_col(std::vector<std::vector<double> > matrix, unsigned deletecol=2);

template <typename T> void 
print_sort_matrix(std::vector<std::vector<T> >, std::vector<T>);

template <typename T> void 
print_vector(std::string, std::vector<T>);

template <typename T> void 
print_matrix(std::string, std::vector<std::vector<T> >);

template <typename T> void 
print_sort_matrix(std::string, std::vector<std::vector<T> >, std::vector<T>);

template <typename T> std::vector<std::vector<T> > 
quantize(std::vector<std::vector<T> >);

#endif // GLOBALFUNC_H