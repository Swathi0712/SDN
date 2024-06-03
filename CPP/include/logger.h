#ifndef LOGGER_H 
#define LOGGER_H 

#include <iostream>
#include <fstream>
#include <mutex>
#include <string>
using namespace std;

class Logger{
    private:
        ofstream logfile;
        mutex mtx;
        Logger(){
            logfile.open("network_log.txt", ios::out|ios::app);
            if(!logfile.is_open()){
                cout << "Failed to open log file" << endl;
            }
        }
        
    public:
        ~Logger(){
            if(logfile.is_open()){
                logfile.close();
            }
        }

        // Method to log messages
        void log(string message){
        std::lock_guard<std::mutex> lock(mtx);
            if(logfile.is_open()){
                logfile << message << endl;
            }
        }

        // Singleton instance
        static Logger& getInstance(){
            static Logger instance;
            return instance;
        }

        // Delete copy constructor and assignment operator
     Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
};

#endif