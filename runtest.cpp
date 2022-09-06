#include <iostream>
#include <vector>
#include <chrono>
#include "gents.h"
#include "csvReader.h"
#include "ABBA.h"
//#include "dynamicTimeWarping.h"
using namespace std;

int main(){
    size_t series_size = 10000; // set 1000 if measured by DTW
    chrono::steady_clock time_point;
    double tol(0.01), alpha(0.01);
    vector<string> symbols;
    vector<double> r_fabba_series, errors, errors_dtw, runtimes;
    vector<pair<string, vector<double>>> benchmarks={}; // record the performance outcome
    pair<string, vector<double>> test; 


    string dist="uniform";
    vector<double> ts = generate_random_sequence(series_size, dist);
    cout << "\n*****************************test 1" << endl; 
    // print_vector(ts);
    auto start = time_point.now();
    ABBA_MODEL fabba1(tol, alpha, "lexi", 1, series_size, true);
    symbols= fabba1.fit_transform(ts);
    r_fabba_series = fabba1.inverse_transform(ts[0]);
    auto end = time_point.now();
    auto runtime = static_cast<chrono::duration<double>>(end - start);
    
    //cout << symbols << endl;
    double error = norm(ts - r_fabba_series);
    //double dtw =  DTW(ts, r_fabba_series, dist_euclidean, 1);
    errors.push_back(error);
    //errors_dtw.push_back(dtw);

    runtimes.push_back(runtime.count());
    cout << "runtime: " << runtime.count()<<" seconds" << endl;
    //cout << "error:" << error << endl; 
    test = {"test 1", ts};
    benchmarks.push_back(test); 
    test = {"reconst test 1", r_fabba_series};
    benchmarks.push_back(test); 


    ts = generate_random_sequence(series_size, "normal");
    cout << "\n*****************************test 2" << endl; 
    // print_vector(ts);
    start = time_point.now();
    ABBA_MODEL fabba2(tol, alpha, "lexi", 1, series_size, true);
    symbols= fabba2.fit_transform(ts);
    r_fabba_series = fabba2.inverse_transform(ts[0]);
    end = time_point.now();

    // cout << symbols << endl;
    runtime = static_cast<chrono::duration<double>>(end - start);
    error = norm(ts - r_fabba_series);
    //dtw =  DTW(ts, r_fabba_series, dist_euclidean, 1);
    errors.push_back(error);
    //errors_dtw.push_back(dtw);

    runtimes.push_back(runtime.count());
    cout << "runtime: " << runtime.count()<<" seconds" << endl;
    //cout << "error:" << error << endl; 
    test = {"test 2", ts};
    benchmarks.push_back(test); 
    test = {"reconst test 2", r_fabba_series};
    benchmarks.push_back(test); 


    vector<pair<string, vector<double>>> performance = {{"runtime", runtimes}, {"2-norm", errors}}; //, {"DTW", errors_dtw}}; 
    data_to_csv(performance, "performance.csv", true);
    data_to_csv(benchmarks, "benchmark_test.csv", true);
    return  0;
}
