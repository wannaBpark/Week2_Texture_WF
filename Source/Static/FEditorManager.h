#pragma once
#include "Object/Actor/Actor.h"

class FEditorManager : public TSingleton<FEditorManager>
{
public:
    
    inline AActor* GetSelectedActor() const {return SelectedActor;}
    
    void SelectActor(AActor* NewActor);

    inline ACamera* GetCamera() const {return Camera;}

    void SetCamera(ACamera* NewCamera);
    
private:
    ACamera* Camera = nullptr;
    AActor* SelectedActor = nullptr;
    class AGizmoHandle* GizmoHandle = nullptr;
};
