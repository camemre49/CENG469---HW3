#ifndef BASE_H
#define BASE_H

// OpenGL libraries
#define USE_MATH_DEFINES
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include <map>
#include <ft2build.h>
#include FT_FREETYPE_H


extern bool shouldDisplay;
extern bool shouldDisplayTexts;
extern float attractorMass;
extern glm::vec2 originPosition;

enum ClickMode {
    ATTRACTOR,
    ORIGIN
};
extern ClickMode currentClickMode;

#endif //BASE_H
