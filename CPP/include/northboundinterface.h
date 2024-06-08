#ifndef NORTHBOUNDINTERFACE_H
#define NORTHBOUNDINTERFACE_H

#include <iostream>
#include <string>
#include "httplib.h"
#include "controller/controller.h"
using namespace std;


class NorthBoundInterface{
    private:
        httplib::Server svr;
        Controller& controller;
        void setUpRoutes(){
            // Testing routes
            // svr.Get("/addSwitch", [&](const httplib::Request&  req, httplib::Response& res ){
            //     // string id = req.get_param_value("id");
            //     res.set_content("hello world", "text/plain");
            // });

            // End point to add switch to the controller 
            svr.Post("/addSwitch", [&](const httplib::Request& req, httplib::Response& res){
                string Id = req.get_param_value("id");
                Switch newSwitch(Id , true);
                controller.addSwitch(newSwitch);
                string message = "Switch added: " + Id;
                res.set_content(message, "text/plain");
            });
        }

        public:
            NorthBoundInterface(Controller& ctrl):controller(ctrl){
                // controller = ctrl;
                setUpRoutes();
            }

            void start(int port){
                svr.listen("0.0.0.0", port);
            }

            void stop(){
                svr.stop();
            }
};

#endif