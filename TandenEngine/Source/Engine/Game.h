//
// Created by Thomas on 1/22/2019.
//

#ifndef TANDENENGINE_GAME_H
#define TANDENENGINE_GAME_H

namespace TandenEngine {

    class Game {
    public:
        virtual void StartUpGame()=0;

        virtual void UpdateGame()=0;

        virtual void ShutDownGame()=0;
    };

}

#endif //TANDENENGINE_GAME_H
