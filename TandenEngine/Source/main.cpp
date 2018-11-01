#include <iostream>

#include "./Engine/Engine.h"

int main() {
    Engine * theEngine = new Engine();

    theEngine->StartEngine(); //Initialize all systems and load resources

    theEngine->RunEngine(); //Run the update loop

    theEngine->StopEngine(); //Safely close out data
	
	system("pause");
    return 0;
}