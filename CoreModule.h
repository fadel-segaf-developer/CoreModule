#ifndef COREMODULE_H
#define COREMODULE_H

#include <iostream>
#include <memory>
#include <vector>

using namespace std;

class GameObject; // Forward declaration

class CoreModule {
public:
    CoreModule(); // Constructor

    // Lifecycle functions
    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void FixedUpdate();
    virtual void OnDestroy();

    // Initialization function to call all lifecycle methods
    void Initialize();

    // Attach this module to a game object
    void AttachToGameObject(shared_ptr<GameObject> gameObject);

    // Get the game object this module is attached to
    std::shared_ptr<GameObject> GetGameObject() const;

protected:
    // Reference to the game object this module is attached to
    std::weak_ptr<GameObject> gameObject;

private:
    // Helper function to automatically call lifecycle functions
    void AutoCallLifecycleFunctions();

    // Tracks whether Start function has been called
    bool started;
};

#endif // COREMODULE_H
