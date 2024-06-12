#ifndef NORTHBOUNDINTERFACE_H
#define NORTHBOUNDINTERFACE_H
#include <iostream>
#include <string>
#include "httplib.h"
#include "controller/controller.h"
#include <format>
#include <typeinfo>
#include <unordered_map>
#include <json.hpp>
using namespace std;
using json = nlohmann::json;


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
            svr.Post("/addSwitch/:id", [&](const httplib::Request& req, httplib::Response& res){
                string Id = req.path_params.at("id");
                Switch newSwitch(Id , true);
                controller.addSwitch(newSwitch);
                std::ostringstream message;
                message << "Added switch:" << Id;
                res.set_content(message.str(), "text/plain");
            });

            // End point to remove a switch from a controller
            svr.Post("/removeSwitch/:id", [&](const httplib::Request& req, httplib::Response& res){
                string Id = req.path_params.at("id");
                controller.removeSwitch(Id);
                std::ostringstream message;
                message << "Removed switch with Id: " << Id;
                res.set_content(message.str(), "text/plain");
            });

            // End point to send a control message to all the switches 
            svr.Post("/sendControlMessage", [&](const httplib::Request& req, httplib::Response& res){
                auto bdy = json::parse(req.body);                
                string message = bdy.at("message").get<string>();
                controller.sendControlMessage(message);
                res.set_content("Control Message Sent: " + message, "text/plain");
            });

            // End point to simulate link failure 
            svr.Post("/SimulateLinkFailure/:link", [&](const httplib::Request& req, httplib::Response& res){
                string failedLink = req.path_params.at("link");
                if(failedLink == ""){
                    res.status = 400;
                    res.set_content("Missing link paramete", "text/plain");
                    return;
                }
                controller.handleLinkFailure(failedLink);
                res.set_content("Link failure simulated for: " + failedLink, "text/plain");
            });

            svr.Post("/updateRoutingTable", [&](const httplib::Request& req, httplib::Response& res){
                string updates = req.body;
                if(updates.empty()){
                    res.status = 400;
                    res.set_content("Missing routing table updates in the request body", "text/plain");
                    return;   
                }
                vector<RoutingTableEntry> parsedUpdates = parseUpdates(updates);
            });
        }
        std::vector<RoutingTableEntry> parseUpdates(const std::string& updates) {
        std::vector<RoutingTableEntry> entries;
        std::istringstream iss(updates);
        std::string line;
        while (std::getline(iss, line)) {
            std::istringstream lineStream(line);
            std::string destination, nextHop;
            int cost;
            lineStream >> destination >> nextHop >> cost;
            entries.push_back({destination, {nextHop}, cost});
        }
        return entries;
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