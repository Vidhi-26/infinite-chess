#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>

class Observer;

//Abstract Subject Declaration
class Subject {
  std::vector<Observer*> observers; //Keeps track of the observers for the subject
 public:
  void attach(Observer *o);
  void detach(Observer *o);
  void notifyObservers();
  virtual char getState(int row, int col) const = 0;
  virtual ~Subject() = default;
};

#endif
