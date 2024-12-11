#ifndef CORELOGIC_H
#define CORELOGIC_H

#include <iostream>
#include <memory>
using namespace std;

class EntityObject; // Forward declaration

class CoreLogic {
public:
    CoreLogic(); // Constructor

    // Lifecycle functions
    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void FixedUpdate();
    virtual void OnDestroy();

    // Set the entity object this module is attached to
    void SetEntityObject(std::shared_ptr<EntityObject> entity);

   

protected:
    std::weak_ptr<EntityObject> entityObject; // Reference to the entity object

private:
    bool started; // Tracks whether Start function has been called
};

#endif // CoreLogic_H
