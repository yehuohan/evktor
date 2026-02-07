#pragma once

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE // Use depth range 0 to 1
#ifdef GLM_FORCE_LEFT_HANDED
    #undef GLM_FORCE_LEFT_HANDED // Setup: GLM_CONFIG_CLIP_CONTROL = GLM_CLIP_CONTROL_RH_ZO
#endif
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/io.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/quaternion.hpp>

namespace glm {

/**
 * @brief Reversed-z infinite perspective
 *
 * - Perspective projection matrix with depth [0,1]:
 * ```
 *  LH: | sx,  0,          0,              0 |  RH: | sx,  0,          0,             0 |
 *      |  0, sy,          0,              0 |      |  0, sy,          0,             0 |
 *      |  0,  0, zf/(zf-zn), -zf*zn/(zf-zn) |      |  0,  0, zf/(zn-zf), zf*zn/(zn-zf) |
 *      |  0,  0,          1,              0 |      |  0,  0,         -1,             0 |
 * ```
 *
 * - Remap depth from [0,1] to [1,0] by applying transformation matrix:
 * ```
 *  M: | 1, 0,  0, 0 |
 *     | 0, 1,  0, 0 |
 *     | 0, 0, -1, 1 |
 *     | 0, 0,  0, 1 |
 * ```
 *
 * - Reversed-z perspective projection matrix:
 * ```
 *  M*LH: | sx,  0,           0,             0 |  M*RH: | sx,  0,          0,             0 |
 *        |  0, sy,           0,             0 |        |  0, sy,          0,             0 |
 *        |  0,  0, -zn/(zf-zn), zf*zn/(zf-zn) |        |  0,  0, zn/(zf-zn), zf*zn/(zf-zn) |
 *        |  0,  0,           1,             0 |        |  0,  0,         -1,             0 |
 * ```
 *
 * - With lim(zf -> +inf):
 * ```
 *  M*LH: | sx,  0, 0,  0 |  M*RH: | sx,  0,  0,  0 |
 *        |  0, sy, 0,  0 |        |  0, sy,  0,  0 |
 *        |  0,  0, 0, zn |        |  0,  0,  0, zn |
 *        |  0,  0, 1,  0 |        |  0,  0, -1,  0 |
 * ```
 */
template <typename T>
GLM_FUNC_QUALIFIER mat<4, 4, T, defaultp> reversedInfinitePerspectiveRH_ZO(T fovy, T aspect, T zNear) {
    T const f = static_cast<T>(1) / tan(fovy / static_cast<T>(2));

    mat<4, 4, T, defaultp> Result(static_cast<T>(0));
    Result[0][0] = f / aspect;
    Result[1][1] = f;
    Result[2][2] = static_cast<T>(0);
    Result[2][3] = static_cast<T>(-1);
    Result[3][2] = zNear;

    return Result;
}

/**
 * @brief Reversed-z perspective
 */
template <typename T>
GLM_FUNC_QUALIFIER mat<4, 4, T, defaultp> reversedPerspectiveRH_ZO(T fovy, T aspect, T zNear, T zFar) {
    T const f = static_cast<T>(1) / tan(fovy / static_cast<T>(2));
    T const fn = zFar - zNear;

    mat<4, 4, T, defaultp> Result(static_cast<T>(0));
    Result[0][0] = f / aspect;
    Result[1][1] = f;
    Result[2][2] = zFar / fn - static_cast<T>(1);
    Result[2][3] = static_cast<T>(-1);
    Result[3][2] = zFar * zNear / fn;

    return Result;
}

template <typename T>
GLM_FUNC_QUALIFIER mat<4, 4, T, defaultp> reversedInfinitePerspective(T fovy, T aspect, T zNear) {
#if GLM_CONFIG_CLIP_CONTROL == GLM_CLIP_CONTROL_RH_ZO
    return reversedInfinitePerspectiveRH_ZO(fovy, aspect, zNear);
#endif
}

template <typename T>
GLM_FUNC_QUALIFIER mat<4, 4, T, defaultp> reversedPerspective(T fovy, T aspect, T zNear, T zFar) {
#if GLM_CONFIG_CLIP_CONTROL == GLM_CLIP_CONTROL_RH_ZO
    return reversedPerspectiveRH_ZO(fovy, aspect, zNear, zFar);
#endif
}

} /* namespace glm */
