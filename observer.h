#ifndef OBSERVER_H_
#define OBSERVER_H_

template <typename InfoType, typename StateType> class Subject;

template <typename InfoType, typename StateType> class Observer {

    virtual void doNotify( Subject<InfoType, StateType> &whoFrom ) = 0;

  public:

    void notify( Subject<InfoType, StateType> &whoFrom );
    virtual ~Observer() = default;

};


template <typename InfoType, typename StateType>
void Observer<InfoType, StateType>::notify( 
        Subject<InfoType, StateType> &whoFrom ) {

    doNotify( whoFrom );

}
    

#endif
