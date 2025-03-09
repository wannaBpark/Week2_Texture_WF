#pragma once
#include "Object/Actor/Actor.h"

class FEditorManager : public TSingleton<FEditorManager>
{
public:
    // TODO: Destroy가 구현되면 구현해야됨.
    
    // on Delete
    // if (SelectedActor == Delete Target)
    //      SelectedActor = nullptr;
    //      Gizmos.SelectedActor = nullptr;
    
    inline AActor* GetSelectedActor() const {return SelectedActor;}
    
    void SelectActor(AActor* NewActor);

private:
    AActor* SelectedActor = nullptr;
    // Gizmos* Gizmos = nullptr;
};
