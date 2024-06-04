#ifndef NORTHBOUNDINTERFACE_H
#define NORTHBOUNDINTERFACE_H

// #include "controller/controller.h"
#include "httplib.h"

class NorthboundInterface {
private:
    // Controller& controller;
    httplib::Server server;

    void setupRoutes() {
        // server.Post("/addSwitch", [&](const httplib::Request& req, httplib::Response& res) {
        //     std::string name = req.get_param_value("name");
        //     // Switch newSwitch(name);
        //     // controller.addSwitch(newSwitch);
        //     res.set_content("Switch added: " + name, "text/plain");
        // });
        server.Get("/hi", [](const httplib::Request &, httplib::Response &res) {
        res.set_content("Hello World!", "text/plain");
        });

        // server.Post("/removeSwitch", [&](const httplib::Request& req, httplib::Response& res) {
        //     std::string name = req.get_param_value("name");
        //     Switch oldSwitch(name);
        //     controller.removeSwitch(oldSwitch);
        //     res.set_content("Switch removed: " + name, "text/plain");
        // });

        // server.Post("/sendControlMessage", [&](const httplib::Request& req, httplib::Response& res) {
        //     std::string message = req.get_param_value("message");
        //     controller.sendControlMessage(message);
        //     res.set_content("Control message sent: " + message, "text/plain");
        // });

        // server.Post("/updateRoutingTable", [&](const httplib::Request& req, httplib::Response& res) {
        //     std::string updates = req.body;
        //     // Parse updates and update the routing table
        //     // For simplicity, assume the updates are in a specific format and parse them accordingly
        //     std::vector<RoutingTableEntry> parsedUpdates = parseUpdates(updates);
        //     controller.updateRoutingTable(parsedUpdates);
        //     res.set_content("Routing table updated", "text/plain");
        // });

        // server.Post("/simulateLinkFailure", [&](const httplib::Request& req, httplib::Response& res) {
        //     std::string failedLink = req.get_param_value("link");
        //     controller.handleLinkFailure(failedLink);
        //     res.set_content("Link failure simulated for: " + failedLink, "text/plain");
        // });
    }

    // std::vector<RoutingTableEntry> parseUpdates(const std::string& updates) {
    //     // Implement a simple parser for the updates
    //     // This is a placeholder implementation
    //     std::vector<RoutingTableEntry> entries;
    //     std::istringstream iss(updates);
    //     std::string line;
    //     while (std::getline(iss, line)) {
    //         std::istringstream lineStream(line);
    //         std::string destination, nextHop;
    //         int cost;
    //         lineStream >> destination >> nextHop >> cost;
    //         entries.push_back({destination, {nextHop}, cost});
    //     }
    //     return entries;
    // }

public:
    // NorthboundInterface(Controller& ctrl)
    NorthboundInterface()
    //  : controller(ctrl) 
     {
        setupRoutes();
    }

    void start(int port) {
        server.listen("0.0.0.0", port);
    }

    void stop() {
        server.stop();
    }
};

#endif // NORTHBOUNDINTERFACE_H
