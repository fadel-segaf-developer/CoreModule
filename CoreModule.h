#ifndef COREMODULE_H
#define COREMODULE_H

#include <iostream>
#include <memory>

class EntityObject; // Forward declaration

class CoreModule {
public:
    CoreModule(); // Constructor

    // Lifecycle functions
    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void FixedUpdate();
    virtual void OnDestroy();

    // Set the entity object this module is attached to
    void SetEntityObject(std::shared_ptr<EntityObject> entity);

    // Static property for fixed update time interval
    static void SetFixedUpdateTime(float time);
    static float GetFixedUpdateTime();

protected:
    std::weak_ptr<EntityObject> entityObject; // Reference to the entity object

private:
    bool started; // Tracks whether Start function has been called
    static float fixedTime; // Static member variable for fixed update time interval
};

#endif // COREMODULE_H
