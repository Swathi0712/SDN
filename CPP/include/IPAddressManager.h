#ifndef IPADDRESSMANAGER_H
#define IPADDRESSMANAGER_H

#include <string>
#include <set>
#include <sstream>

class IPAddressManager {
private:
    std::set<std::string> allocatedIPs;
    std::string baseIP;
    int currentIP;

    std::string intToIP(int ip) {
        std::stringstream ss;
        ss << ((ip >> 24) & 0xFF) << "."
           << ((ip >> 16) & 0xFF) << "."
           << ((ip >> 8) & 0xFF) << "."
           << (ip & 0xFF);
        return ss.str();
    }

    int ipToInt(const std::string& ip) {
        int a, b, c, d;
        char dot;
        std::stringstream ss(ip);
        ss >> a >> dot >> b >> dot >> c >> dot >> d;
        return (a << 24) + (b << 16) + (c << 8) + d;
    }

public:
    IPAddressManager(const std::string& base) : baseIP(base), currentIP(ipToInt(base)) {}

    std::string allocateIP() {
        while (allocatedIPs.find(intToIP(currentIP)) != allocatedIPs.end()) {
            currentIP++;
        }
        std::string newIP = intToIP(currentIP);
        allocatedIPs.insert(newIP);
        return newIP;
    }

    void releaseIP(const std::string& ip) {
        allocatedIPs.erase(ip);
    }
};

// IPADDRESSMANAGER_H
#endif 
