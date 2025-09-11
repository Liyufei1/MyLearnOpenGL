#pragma once
#include "Common/CommonFunLib.h"
#include "Common/CommonFunLib.hpp"
#include "Common/Config.h"
#include "Window/Window.h"
#include "Mesh/Mesh.h"
#include "Mesh/MeshManager.h"
#include "Texture/Texture2D.h"
#include "Camera/Camera.h"


#include "glfw/glfw3.h"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/vector_float3.hpp"
#include "glm/fwd.hpp"
#include "glm/glm.hpp"
#include <cmath>
#include <functional>
#include <memory>
#include <string>

#include "Test.h"

std::shared_ptr<StaticMesh> TestMesh0();
std::shared_ptr<StaticMesh> BoxMesh();


