#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>
#include "observer.h"

template <typename InfoType, typename StateType> class Observer;

template <typename InfoType, typename StateType> class Subject {

    StateType state;
    std::vector<Observer<InfoType, StateType>*> observers;

  protected:

    Subject( StateType state );
    void setState( StateType newState );

  public:

    void attach( Observer<InfoType, StateType> *observer );  
    void notifyObservers();
    StateType getState() const;

};


template <typename InfoType, typename StateType>
Subject<InfoType, StateType>::Subject( StateType state ) :

        state{ state } {}


        template <typename InfoType, typename StateType>
        void Subject<InfoType, StateType>::attach(
                        Observer<InfoType, StateType> *observer) {

                  observers.emplace_back(observer);

        }


template <typename InfoType, typename StateType>
void Subject<InfoType, StateType>::notifyObservers() {

          for (auto &ob : observers) ob->notify(*this);

}


template <typename InfoType, typename StateType>
void Subject<InfoType, StateType>::setState(StateType newS) {

        state = newS;

}


template <typename InfoType, typename StateType>
StateType Subject<InfoType, StateType>::getState() const {

        return state;

}


#endif
