#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace vktdev {

/**
 * @brief Camera interface
 */
class ICamera {
public:
    enum Type {
        Arcball,
        FirstPerson,
    };

    /** 摄像机移动方向 */
    enum Movement {
        Reset = 0,
        Forward,
        Backward,
        Leftward,
        Rightward,
        Upward,
        Downward,
    };

    Type type;
    glm::vec3 eye{};         /**< 摄像机位置 */
    glm::vec3 center{};      /**< 摄像机看向的目标位置 */
    glm::vec3 up{};          /**< 摄像机的正上方向量 */
    float speed = 1.0f;      /**< 摄像机移动速度 */
    float zoom = 45.0f;      /**< 摄像机镜头视角，表现为投影矩阵的fov */
    float sensitivity = 1.0; /**< 鼠标移动灵敏度 */

public:
    ICamera(glm::vec3 eye, glm::vec3 center) : eye(eye), center(center) {}

    /**
     * @brief 摄像机的视图变换矩阵
     *
     * 用lookAt矩阵乘以1个坐标向量，则可将坐标变换到摄像机的坐标空间（摄像机空间）中。
     */
    inline glm::mat4 getView() const {
        return glm::lookAt(eye, center, up);
    };

    /**
     * @brief 返回透视投影矩阵
     */
    inline glm::mat4 getProj(unsigned int wid, unsigned int hei, float znear = 0.1f, float zfar = 100.0f) const {
        return glm::perspective(glm::radians(zoom), (float)wid / hei, znear, zfar);
    };

    virtual void update() {};

    /**
     * @brief 移动摄像机
     *
     * @param delta_time 当前帧与上一帧的时间差
     */
    virtual void processCameraMove(Movement dir, float delta_time) {};

    /**
     * @brief 鼠标移动
     *
     * @param pa,pb 移动起止坐标（使用归一化坐标）
     */
    virtual void processMouseMove(const glm::vec2& pa, const glm::vec2& pb) {};

    /**
     * @brief 滚轮缩放
     *
     * @param yofs 滚轮偏移
     */
    virtual void processMouseScroll(float yofs) {
        zoom = glm::clamp(zoom - yofs, 1.0f, 45.0f);
    };
};

/**
 * @brief Arcball camera
 */
class CameraArcball final : public ICamera {
public:
    glm::vec3 right{}; /**< 摄像机的正右方向 */

private:
    /**
     * @brief 根据屏幕坐标计算arcball上的三维坐标
     *
     * @param p 归一化的屏幕坐标
     */
    glm::vec3 arcball_coordinate(const glm::vec2& p) const;

public:
    CameraArcball(glm::vec3 eye = glm::vec3(0.0f, 0.0f, 1.0f)) : ICamera(eye, glm::vec3(0.0f, 0.0f, 0.0f)) {
        type = ICamera::Type::Arcball;
        up = glm::vec3(0.0f, 1.0f, 0.0f);
        speed = 5.5f;
        sensitivity = 3.0f;
        update();
    }

    virtual inline void update() override {
        right = glm::cross(up, glm::normalize(eye - center));
    }
    virtual void processCameraMove(Movement dir, float delta_time) override;
    virtual void processMouseMove(const glm::vec2& pa, const glm::vec2& pb) override;
};

/**
 * @brief First person camera
 */
class CameraFirstPerson final : public ICamera {
public:
    const glm::vec3 world_up{0.0f, 1.0f, 0.0f}; /**< 世界坐标的正上方向 */
    glm::vec3 right;                            /**< 摄像机的正右方向 */
    float pitch = 0.0f;                         /**< 府仰角（向上或向下看）*/
    float yaw = -90.0f;                         /**< 偏航角（向左或向右看）*/

public:
    CameraFirstPerson(glm::vec3 eye = glm::vec3(0.0f, 0.0f, 0.0f)) : ICamera(eye, glm::vec3(0.0f, 0.0f, -1.0f)) {
        type = ICamera::Type::FirstPerson;
        speed = 5.5f;
        sensitivity = 50.0f;
        update();
    };

    virtual void update() override;
    virtual void processCameraMove(Movement dir, float delta_time) override;
    virtual void processMouseMove(const glm::vec2& pa, const glm::vec2& pb) override;
};

} // namespace vktdev
