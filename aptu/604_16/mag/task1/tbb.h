//
// Automatically generated by Flow Graph Analyzer: C++ Code Generator Plugin version Alpha 5.15230
//

#pragma once
#define TBB_PREVIEW_GRAPH_NODES 1

#include <fstream>
#include <iomanip>
#include <mutex>
#include "tbb/flow_graph.h"
#include "tbb/atomic.h"
#include "tbb/tick_count.h"
#include "image.h"


using namespace std;
using namespace tbb;
using namespace tbb::flow;

static void spin_for( double weight ) {
    tick_count t1, t0 = tick_count::now();
    const double weight_multiple = 10e-6;
    const double end_time = weight_multiple * weight;
    do {
        t1 = tick_count::now();
    } while ( (t1-t0).seconds() < end_time );
}

class image_input_node_body {
    int n;
public:
    image_input_node_body(int n): n(n){}

    bool operator()( image &output ) {
        //
        // ADD USER BODY HERE
        //
        static int i = 0;
        if ( i++ < n ) {
            output = image();
            return true;
        }
        return false;
    }
};

class max_node_body {
public:
    vector<point> operator()( const image & input ) {
        //
        // ADD USER BODY HERE
        //
        return input.max_points();
    }
};

class min_node_body {
public:
    vector<point> operator()( const image & input ) {
        //
        // ADD USER BODY HERE
        //
        return input.min_points();
    }
};

class exact_node_body {
    char value;
public:
    exact_node_body(char v): value(v){};

    vector<point> operator()( const image & input ) {
        //
        // ADD USER BODY HERE
        //
        return input.exact_points(value);
    }
};

class highlight_node_body {
public:
    image operator()( const tbb::flow::tuple<image,vector<point>,vector<point>,vector<point>> & input ) {
        //
        // ADD USER BODY HERE
        //
        image img(get<0>(input));
        auto points1 = get<1>(input);
        auto points2 = get<2>(input);
        auto points3 = get<3>(input);
        for(size_t i = 0; i < points1.size(); i++){
            img.highlight_point(points1[i]);
        }
        for(size_t i = 0; i < points2.size(); i++){
            img.highlight_point(points2[i]);
        }
        for(size_t i = 0; i < points3.size(); i++){
            img.highlight_point(points3[i]);
        }
        return img;
    }
};

class average_brightness_node_body {
    string filename;
    ofstream& log;
    static mutex tlock;
public:

    average_brightness_node_body(string& filename, ofstream& log): filename(filename), log(log){};
    int operator()( const image & input ) {
        //
        // ADD USER BODY HERE
        //
        if(!filename.empty()){
            tlock.lock();
            log  << setprecision(5) << fixed << input.average() << endl;
            tlock.unlock();
        }
        return 0;
    }
};


class inverse_image_node_body {
public:
    int operator()( const image & input ) {
        //
        // ADD USER BODY HERE
        //
        image other(input);
        other.invert();
        return 0;
    }
};

class counter_node_body {
public:
    continue_msg operator()( const tbb::flow::tuple<int,int> & /*input*/ ) {
        //
        // ADD USER BODY HERE
        //
        return continue_msg();
    }
};
