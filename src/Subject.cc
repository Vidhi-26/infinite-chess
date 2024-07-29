#include "Subject.h"
#include "./Observers/Observer.h"

//Abstract Subject Implementation

//Adds the given obsever
void Subject::attach(Observer* o){
    observers.push_back(o);
}

//Removes the given obsever
void Subject::detach(Observer* o){

    //Iterate through the observers list and remove the observer
    for(int i = 0; i < observers.size(); i++){
        if(o == observers[i]){
            std::swap(observers[i], observers[observers.size() - 1]);
            observers.pop_back();
            break;
        }
    }
}

//Notifies all observers - calls each obsever's notify method
void Subject::notifyObservers(){
    for(auto o: observers){
        o->notify();
    }
}
