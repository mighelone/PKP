//
//  runner.hpp
//  testing
//
//  Created by Michele Vascellari on 19.06.17.
//  Copyright © 2017 Michele Vascellari. All rights reserved.
//

#ifndef runner_hpp
#define runner_hpp

//#include <memory>
#include "model.hpp"
#include <iostream>

void printv(const dvector &y, const double t);

class Runner
{
protected:
    Model * model;
    
    //std::unique_ptr<Model> model;
public:
  //enum models {sfor, c2sm};
  Runner(int modelType, dvector parameters)
  {
    std::cout << "ctor Runner=" << modelType << std::endl;
    if (modelType == 0)
      {
	std::cout << "SFOR" << std::endl;
	model = new SFOR(parameters);
      }
    else if (modelType == 1)
      {
	std::cout << "C2SM" << std::endl;
	model = new C2SM(parameters);
      }
    else
      {
	throw 1;
      }

    // switch (modelType)
    //   {
    //   case(0):
    // 	  std::cout << "SFOR" << std::endl;
    // 	  model = new SFOR(parameters);
    // 	//model = std::make_unique<SFOR>(parameters);
    //   case(1):
    // 	  std::cout << "C2SM" << std::endl;
    // 	  model = new C2SM(parameters);
    // 	//model = std::make_unique<SFOR>(parameters);
    //   }
  }
  ~Runner()
  {//delete model;
    delete model;
  }
  void solve(dvector y0, double t0, double tEnd, double dt);
};

#endif /* runner_hpp */
