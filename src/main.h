#pragma once
#include "Camera/Camera.h"
#include "Common/CommonFunLib.h"
#include "Common/CommonFunLib.hpp"
#include "Common/Config.h"
#include "Window/Window.h"
#include "Mesh/Mesh.h"
#include "Mesh/MeshManager.h"
#include "Texture/Texture2D.h"

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

    

    //贴图
    std::shared_ptr<Texture2D> T_WoodBox = nullptr;
    std::shared_ptr<Texture2D> T_SmallFace = nullptr;

    //着色器程序
    std::shared_ptr<ShaderProgram> PhoneShaderPrograme = nullptr;
    std::shared_ptr<ShaderProgram> BaseShaderPrograme = nullptr;

    //材质
    std::shared_ptr<Material> M_Phone = nullptr;
    std::shared_ptr<Material> M_Base = nullptr;

    //光照
    Light PointLight1;
    std::shared_ptr<StaticMesh> SM_PointLight1   = nullptr;

private:
    std::vector<std::function<void()>> UpdateFunctions;
    Main(){}

};

