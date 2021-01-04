//
// Created by Admin on 04.01.2021.
//

#include "Application.h"

Application *Application::getInstance() {
    if(app == nullptr){
        app = new Application();
    }
    return app;
}
