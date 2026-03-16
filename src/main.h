#pragma once
#include "Scene/Light/Light.h"
#include "Scene/Camera/Camera.h"
#include "Common/CommonFunLib.h"
#include "Common/CommonFunLib.hpp"
#include "Common/Config.h"
#include "Window/Window.h"
#include "Scene/Mesh/Mesh.h"
#include "Render/RenderService.h"
#include "Render/Texture/Texture2D.h"

#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/vector_float3.hpp"
#include "glm/fwd.hpp"
#include "glm/glm.hpp"
#include <cmath>
#include <cstddef>
#include <functional>
#include <memory>
#include <string>
#include <vector>


#include "Test.h"

class Light;

class Main
{
public:
    ~Main(){}
    static Main& GetInstance();

    void Update(){
        for(auto it :UpdateFunctions) it();
    }

    void AddUpdateFunction(std::function<void()> func){UpdateFunctions.push_back(func);}

    void LoadUsedResources();

    void InitMesh();

    void InitLight();


    //材质
    std::shared_ptr<Material> M_Phone = nullptr;
    std::shared_ptr<Material> M_Base = nullptr;
    std::shared_ptr<Material> M_back_pack = nullptr;

    //光照
    DirLight L_DirLight;
    PointLight PointLight1;
    PointLight PointLight2;

private:
    std::vector<std::function<void()>> UpdateFunctions;
    Main(){}

};

