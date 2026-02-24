//CODE 
//INTRO to manage threads in C++

#include <bits/stdc++.h>
#include <thread>
using namespace std;

void function_1 (){
    cout<<" FULL bt difficuklt it is ig "<<endl;
}


class functor {
    public:
    void operator()(string msg){///////(NO USE OF &)
        cout<<"FUNCTOR ???!!!!!!!! and message is "<<msg<<endl;
    }
};
int main(){
    thread t1 (function_1);
    t1.detach();//DOES NOT WAIT FOR Child thread to finsish ==> daemon thread means it can be running when we dontk know 
    //Once detached forever detached 
    if(t1.joinable()){}
    else{
    cout<<"YOU LOST him"<<endl;
    }


/*
Using try–catch with threads ensures exception safety and prevents program crashes. When a thread is created using std::thread, 
it must be either join()ed or detach()ed before the thread object is destroyed. If an exception occurs and you are not using a 
try–catch block, the control may exit the function before join() is called. In such a case, the thread remains joinable, and its
 destructor calls std::terminate(), causing the program to crash. By using a try–catch, you can call join() inside the catch block 
 before rethrowing the exception, ensuring the thread is cleaned up properly and the program remains stable. Without try–catch, any
unexpected exception can skip cleanup and lead to abrupt termination.
*/
    thread t (function_1);
try{
    for(int i =0;i<100;i++){
        cout<<"from main : "<<i<<endl;
    }
}
catch(...){
    t.join();
    throw;
}
t.join();










//UNABLE TO UNDERSTAND COMPLETETLY TRY AND CATCH 
    //In a thread all parameters are passed as a value only never refernece
 string s ="HIMANSHU ";
    thread t2 ((functor()),s);
    t2.join();

    cout<<endl;
    cout<<thread::hardware_concurrency()<<endl;
    return 0;
}