
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


* 
* fABBA -- an accelerated ABBA based on adaptive polygonal chain approximation of time series
*
*  Parameters
*  ----------    
*     tol - default=0.1
*         Control tolerence for compression.
*     
*     alpha -  default=0.5
*         Control tolerence for digitization.        
*     
*     sorting - default='2-norm', {'lexi', '1-norm', '2-norm'}
*         by which the sorting pieces prior to aggregation.
* 
*     scl - default=1
*         Scale for length, default as 1, refers to 2d-digitization, otherwise implement 1d-digitization.
*     
*     verbose - default=1
*         Verbosity mode, control logs print, default as 1; print logs.
*     
*     max_len - default=1
*         The max length for each segment, optional choice for compression.
*     
*     string_form - boolean, default=true
*         Whether to return with string form
*
*  Methods:
*  ----------
*     std::string ABBA::fit_transform(std::vector<T>&)
*          Transform time series into symbols.
*
*     std::vector<T> ABBA::inverse_transform(std::string& symbols, T& start)
*          Reconstruct the symbols back into time series.
*
*  Attributes
*  ---------- 
*  parameters - Model, store the parameters of fABBA
*/


#ifndef ABBA_H
#define ABBA_H

#include <vector>
#include <string>
#include "digitization.h"

class ABBA_MODEL {
    protected:
        double tol; double alpha;
        std::string sorting;
        int scl; int maxlen; bool verbose; 
        Model parameters;

    public:
        ABBA_MODEL(double _tol=0.5, double _alpha=0.5, std::string _sorting="lexi",
                    int _scl=1, int _maxlen=std::numeric_limits<int>::max(), bool _verbose=true);
                    
        std::vector<std::string> fit_transform(std::vector<double>&);
        std::vector<double> inverse_transform(double&);
        void print_parameters();
        ~ABBA_MODEL(){};
};


#endif // ABBA_H