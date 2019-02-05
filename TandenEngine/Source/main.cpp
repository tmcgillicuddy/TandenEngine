#include "./Engine/Engine.h"

int main() {
    TandenEngine::Engine * theEngine = new TandenEngine::Engine();

    theEngine->StartEngine();  // Initialize all systems and load resources

    theEngine->RunEngine();  // Run the update loop

    theEngine->StopEngine();  // Safely close out data
    return 0;
}
