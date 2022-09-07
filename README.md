# cabba: An efficient symbolic representation for time series 

[![License](https://img.shields.io/badge/License-BSD%203--Clause-greenyellow.svg)](https://opensource.org/licenses/BSD-3-Clause)

ABBA is an accurate symbolic time series representation method. The Python package and detailed description has been shown in [ABBA](https://github.com/nla-group/ABBA) and [fABBA](https://github.com/nla-group/fABBA).  ``cabba`` is undergoing project that contains implementation for ABBA (to be built) and fABBA. 

### Install
Install ``cabba`` simply by:
```sh
git clone https://github.com/nla-group/cabba.git
cd cabba
cmake . # or mkdir build -> cd build -> cmake ../
make 
cp *.a /usr/lib 
```

After that, we can include the ``cabba`` library with ``#include "ABBA.h"`` in include folder.

### API

The below shows the use of ``cabba`` to perform symbolic transform:

```c++
#include <iostream>
#include <vector>
#include <chrono> 
#include "gents.h" // generate random noise as time series
#include "ABBA.h" // include library

using namespace std;

int main(){
    size_t series_size = 10000; // time series length
    
    double tol(0.01), alpha(0.01); // parameter for ABBA
    vector<string> symbols;
    vector<double> r_fabba_series;

    string dist="uniform";
    vector<double> ts = generate_random_sequence(series_size, dist);
    
    ABBA fabba(tol, alpha, "lexi", 1, series_size, true); // define ABBA object
    symbols= fabba.fit_transform(ts); // transform time series into symbols
    r_fabba_series = fabba.inverse_transform(ts[0]); // reconstruct time series from symbols
    
    return 0;
 }
```



### Reference

[1] X. Chen and S. Güttel. An efficient aggregation method for the symbolic representation of temporal data. Published online in ACM Transactions on Knowledge Discovery from Data, 2022. 

[2] S. Elsworth and S. Güttel. ABBA: adaptive Brownian bridge-based symbolic aggregation of time series. Data Mining and Knowledge Discovery, 34: 1175-1200, 2020.



### License
All the content in this repository is licensed under the BSD-3 License.

Copyright © 2022 NLA group
