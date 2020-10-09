
//#include "libhello.h"

#include <iostream>
#include <cstdlib>

#include "version.h"
#include "libhellostatic/hello_static.h"
#include "libhelloshared/hello_shared.h"

using namespace std;

int version(){
    return PROJECT_VERSION_PATCH;
}

int main(int, char**){

    cout<<"build "<<version()<<endl; 
    cout<<"Hello, world"<<endl;
    cout<<"Library static version "<<hello_static::version()<<endl;
    cout<<"Library shared version "<<hello_shared::version()<<endl;

    return EXIT_SUCCESS;
}