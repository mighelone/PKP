//
//  runner.hpp
//  testing
//
//  Created by Michele Vascellari on 19.06.17.
//  Copyright © 2017 Michele Vascellari. All rights reserved.
//

#ifndef reactor_hpp
#define reactor_hpp

//#include <memory>
#include "model.hpp"
#include "SFOR.hpp"
#include "C2SM.hpp"
//#include "ModelFactory.hpp"
#include "ReactorFactory.hpp"
#include <iostream>
#include <string>

// include gtest for testing purpose
#include "gtest/gtest_prod.h"

namespace pkp {
    void printv(const dvector &y, const double t);

    struct push_back_state_and_time
    {
        std::vector< dvector >& m_states;
        std::vector< double >& m_times;

        push_back_state_and_time( std::vector< dvector > &states , std::vector< double > &times )
          : m_states( states ) , m_times( times ) {}

        void operator()( const dvector &x , double t )
        {
          m_states.push_back( x );
          m_times.push_back( t );
        }
    };

    /*
        Reactor runner class
    */
    class Reactor
    {
    protected:
        //Model * model;
        std::shared_ptr<Model> model;
        std::vector<double> times;
        std::vector<dvector> states;
        bool isoThermal;
        //
        //    calculate the derivatives
        //
        void dydt(const dvector &y, dvector &dydt, double t);
        void dTdt(const dvector &y, dvector &dydt, double t);

        FRIEND_TEST(ReactorTest2, dydt);
        //std::unique_ptr<Model> model;
    public:
        //enum models {sfor, c2sm};
        Reactor(const std::string& modelType, dvector parameters);
        // Reactor(models modelType)
        // {
        //     switch (modelType)
        //     {
        //     case sfor:
    	//            model = new SFOR(); break;
        //     case c2sm:
    	//            model = new C2SM(); break;
        //     }
        //     //throw 0;
        // }
        ~Reactor();
        void solve(double t, double T=1000, double dt=1e-4, bool verbose=false);
        void solve(std::vector<std::vector<double>> points, double dt=1e-4, bool verbose=false);
        dvector const getParameters(){return model->getParameters();}
        void setParameters(const dvector & parameters);
        std::vector<double> getTimes(){return times;}
        std::vector<dvector> getStates(){return states;}
        void dump(const std::string &csv, std::string sep = ",");
        void printParameters(){model->printParameters();}
    };
}//namespace pkp


#endif /* runner_hpp */