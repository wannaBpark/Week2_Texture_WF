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

    inline ACamera* GetCamera() const {return Camera;}

    void SetCamera(ACamera* NewCamera);
    
private:
    ACamera* Camera = nullptr;
    AActor* SelectedActor = nullptr;
    class AGizmoHandle* GizmoHandle = nullptr;
};
