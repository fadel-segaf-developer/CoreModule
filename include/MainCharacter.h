#ifndef MAINCHARACTER_H
#define MAINCHARACTER_H

#include "EntityObject.h"
#include <chrono>

class MainCharacter : public EntityObject {
public:
    // Factory function to create an instance of MainCharacter
    static std::shared_ptr<MainCharacter> Create(const std::string& name);

    MainCharacter() = default;

    void CustomFunction(); // Example of a unique function

    void Initialize() override;
    void Update() override;

    int x = 0;
    string nameObj = "";

};

#endif // MAINCHARACTER_H
