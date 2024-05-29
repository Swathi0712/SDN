        
# function to log events to the network log
def logEvent(event):
    Logger.getInstance().log(event)

class Logger:
    __File = None
    _instance = None
    
    # Singleton instance
    def __new__(cls):
        if cls._instance is None:
            cls._instance = super(Logger, cls).__new__(cls)
        return cls._instance
           
    def __init__(self):
       self.__File = open("./py/src/networkLog.txt" , "a")
       if (self.__File).closed:
           print("Failed to open log file")
           
    def __del__(self):
        self.__File.close()
    
    # Method to log messages
    def log(self, message):
        if self.__File.closed == False:
            self.__File.write(f"{message}\n")
            
    def getInstance():
        return Logger()
    
# example
# logEvent("test event")
# logEvent("this is another test event")

    