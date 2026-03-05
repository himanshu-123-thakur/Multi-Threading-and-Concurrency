//CODE

//CLASSIC DEADLOCK 
//HOW TO AVOID DEADLOCK

//TO CREATE deadlock we reversed the order 
//to orevent we keep in order
//OR
//use lock(mu,mu2)
// lock_guard<mutex> namemutex(mu, adopt_lock)

#include <iostream>
#include <mutex>
#include <thread>
#include <fstream>   // Needed for std::ofstream (writing output to a file)

using namespace std;

class LogFile{
    mutex mu;
    mutex mu2;

    ofstream cout;

    public:
    LogFile(){
        cout.open("log.txt"); //THIS IS JUST FOR PRINTING THE OUTPUT IN A SEPERATE FILE ELSE NO NEED FOR THIS 
    }


    void shared_print(string id, int value){
        lock(mu,mu2);//to avoid mutex
        lock_guard<mutex>locker (mu,adopt_lock);//adopt_lock
        lock_guard<mutex>locker2(mu2,adopt_lock);

        this_thread::yield();              // <-- widen the race window
        cout<<"FROM "<<id <<" : "<<value<<endl; //IF DONT WANT SEPERATE FILE JUST WRITE COUT

    }

    void shared_print2(string id, int value){
        lock(mu,mu2);//to avoid mutex
        lock_guard<mutex>locker2 (mu2,adopt_lock);//adopt_lock
        lock_guard<mutex>locker(mu,adopt_lock);

    this_thread::yield();              // <-- widen the race window
        cout<<"FROM "<<id <<" : "<<value<<endl; //IF DONT WANT SEPERATE FILE JUST WRITE COUT

    }
};



void function_1(LogFile &log){
    for(int i=0;i>-100;i--){
        log.shared_print(string("from t1: "),i);
    }
}

int main(){

    LogFile log;
    thread t1(function_1, ref(log));
    for(int i =0;i<100;i++){
        log.shared_print2(string("from main: "),i);
    }
    t1.join();
    return 0;
}