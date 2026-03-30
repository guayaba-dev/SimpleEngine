#pragma once

#include "../entities/components.h"
#include "../vendor/glm/glm.hpp"

namespace System {

glm::mat4 getModelMat(TransformComponent &transform);

}
