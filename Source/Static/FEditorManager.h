#pragma once
#include "Object/Actor/Actor.h"

class AGizmoHandle;
class AWorldText;

class FEditorManager : public TSingleton<FEditorManager>
{
public:
    
    inline AActor* GetSelectedActor() const {return SelectedActor;}
    
    void SelectActor(AActor* NewActor);

    inline ACamera* GetCamera() const {return Camera;}

    void SetCamera(ACamera* NewCamera);

    AGizmoHandle* GetGizmoHandle() const {return GizmoHandle;}

	AWorldText* GetWorldText() const { return WorldText; }
    
private:
    ACamera* Camera = nullptr;
    AActor* SelectedActor = nullptr;
    AGizmoHandle* GizmoHandle = nullptr;
	AWorldText* WorldText = nullptr;
};
