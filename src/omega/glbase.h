/*!
 * @file lngl.h
 * @brief LnGL base class
 */

#ifndef LNGL_BASE_H
#define LNGL_BASE_H

#include <glad/gl.h>
#include <xwin.h>
#include <glm/glm.hpp>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <iostream>
#include <cstdint>
#include <memory>
#include "camera.h"
#include "efmt.h"


class LnGL : public XWin {
public:
    LnGL(int width, int height);
    virtual ~LnGL() { }

    virtual void run() override;
    virtual void tick(float cur_time, float delta_time) = 0;
};

#endif /* end of include guard: LNGL_BASE_H */
