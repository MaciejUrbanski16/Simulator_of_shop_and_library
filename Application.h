//
// Created by Admin on 04.01.2021.
//

#ifndef MACHINEOFSTATE_APPLICATION_H
#define MACHINEOFSTATE_APPLICATION_H

//singleton pattern
//this class storages configuration of simulator
class Application {

protected:
    Application() = default;
    static Application *app;
public:

    //to ensure only one instance of this class
    Application(Application &other) = delete;
    void operator=(const Application &other) = delete;

    static Application *getInstance();

    int mode;


};


#endif //MACHINEOFSTATE_APPLICATION_H
