/* comment */

#pragma once

#include <glm/glm.hpp>
#include <vcl/dllapi.h>

#include <ostream>

std::ostream& operator<<(std::ostream& rStrm, const glm::mat4& rMatrix);
std::ostream& operator<<(std::ostream& rStrm, const glm::vec4& rPos);
std::ostream& operator<<(std::ostream& rStrm, const glm::vec3& rPos);

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
