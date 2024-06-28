#ifndef MAINCHARACTER_H
#define MAINCHARACTER_H

#include "EntityObject.h"

class MainCharacter : public EntityObject {
public:
    // Factory function to create an instance of MainCharacter
    static std::shared_ptr<MainCharacter> Create();
    MainCharacter();

    void CustomFunction(); // Example of a unique function

    void Update() override;
};

#endif // MAINCHARACTER_H
