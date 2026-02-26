//CODE
#include <iostream>
#include <mutex>
#include <thread>
#include <fstream>   // Needed for std::ofstream (writing output to a file)

using namespace std;

// =======================================================
// LogFile class
// Purpose:
// This class represents a shared logging object.
// Multiple threads will use this same object to print.
// It contains:
//   1) A mutex (to prevent simultaneous access)
//   2) A file stream (to write output into a file)
// =======================================================

class LogFile{
    mutex mu;
    ofstream f;

    public:
    LogFile(){
        f.open("log.txt"); //THIS IS JUST FOR PRINTING THE OUTPUT IN A SEPERATE FILE ELSE NO NEED FOR THIS 
    }


    // ---------------------------------------------------
    // shared_print()
    // This function is called by multiple threads.
    // So it must be protected using a mutex.
    // ---------------------------------------------------

    void shared_print(string id, int value){

        // lock_guard automatically locks the mutex here.
        // When this function ends, it automatically unlocks.
        // This prevents two threads from printing at same time.

        lock_guard<mutex>locker (mu);
        f<<"FROM "<<id <<" : "<<value<<endl; //IF DONT WANT SEPERATE FILE JUST WRITE COUT

        // If you don't want file output:
        // replace f with cout and remove ofstream.
    }
};


// =======================================================
// function_1()
// This function will run inside a separate thread.
// It receives LogFile by REFERENCE.
// Reference is needed because:
//   - We want both threads to use SAME LogFile object.
//   - LogFile cannot be copied (mutex inside is non-copyable).
// =======================================================

void function_1(LogFile &log){
    for(int i=0;i>-100;i--){
        log.shared_print(string("from t1: "),i);
    }
}

int main(){

    LogFile log;

    // Create a new thread named t1.
    // It will start running function_1(log).
    // ref(log) is VERY IMPORTANT:
    // By default, thread tries to COPY arguments.
    // But LogFile cannot be copied (mutex inside).
    // So ref(log) tells thread:
    // "Use this object by reference. Do not copy it."
    thread t1(function_1, ref(log));
    for(int i =0;i<100;i++){
        log.shared_print(string("from main: "),i);
    }
    t1.join();
}