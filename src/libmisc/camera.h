/*!
 * @file camera.h
 * @brief 摄像机
 *
 */
#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


/*!
 * @brief 摄像机接口
 */
class ICamera {
public:
    glm::vec3   eye;            /**< 摄像机位置 */
    glm::vec3   center;         /**< 摄像机看向的目标位置 */
    glm::vec3   up;             /**< 摄像机的正上方向量 */
    float       speed;          /**< 摄像机移动速度 */
    float       zoom;           /**< 摄像机镜头视角，表现为投影矩阵的fov */
    float       sensitivity;    /**< 鼠标移动灵敏度 */

    enum Type {
        Arcball,
        FirstPerson,
    };
    Type        type;           /**< 摄摄机类型 */

    /*!
     * @brief 摄像机移动方向
     *
     */
    enum Movement {
        Reset = 0,
        Forward,
        Backward,
        Leftward,
        Rightward,
        Upward,
        Downward,
    };

    ICamera(glm::vec3 _eye, glm::vec3 _center)
        : eye(_eye)
        , center(_center)
        , speed(1.0f)
        , zoom(45.0f)
        , sensitivity(1.0f)
    { }

    /*!
     * @brief 摄像机的视图变换矩阵
     *
     * 用lookAt矩阵乘以1个坐标向量，则可将坐标变换到摄像机的坐标空间（摄像机空间）中。
     *
     */
    inline glm::mat4 getView() {
        return glm::lookAt(eye, center, up);
    };

    /*!
     * @brief 返回透视投影矩阵
     *
     */
    inline glm::mat4 getProj(unsigned int wid, unsigned int hei, float znear=0.1f, float zfar=100.0f) {
        return glm::perspective(glm::radians(zoom), (float)wid / hei, znear, zfar);
    };

    virtual void update() { };

    /*!
     * @brief 移动摄像机
     *
     * @param delta_time 当前帧与上一帧的时间差
     */
    virtual void processCameraMove(Movement dir, float delta_time) { };

    /*!
     * @brief 鼠标移动
     *
     * @param pa,pb 移动起止坐标（使用归一化坐标）
     */
    virtual void processMouseMove(const glm::vec2& pa, const glm::vec2& pb) { };

    /*!
     * @brief 滚轮缩放
     *
     * @param yofs 滚轮偏移
     */
    virtual void processMouseScroll(float yofs) {
        this->zoom = glm::clamp(this->zoom - yofs, 1.0f, 45.0f);
    };
};

/*!
 * @brief Arcball相机
 *
 */
class CameraArcball final : public ICamera {
public:
    glm::vec3 right; /**< 摄像机的正右方向 */

    CameraArcball(glm::vec3 _eye = glm::vec3(0.0f, 0.0f, 1.0f))
        : ICamera(_eye, glm::vec3(0.0f, 0.0f, 0.0f))
    {
        this->speed = 5.5f;
        this->sensitivity = 3.0f;
        this->up = glm::vec3(0.0f, 1.0f, 0.0f);
        this->update();
        this->type = ICamera::Type::Arcball;
    }

    virtual inline void update() {
        this->right = glm::cross(up, glm::normalize(eye - center));
    }

    virtual void processCameraMove(Movement dir, float delta_time);

    virtual void processMouseMove(const glm::vec2& pa, const glm::vec2& pb);

private:
    /*!
     * @brief 根据屏幕坐标计算arcball上的三维坐标
     *
     * @param p 归一化的屏幕坐标
     */
    glm::vec3 arcball_coordinate(const glm::vec2& p);
};

/*!
 * @brief 第一视角相机
 *
 */
class CameraFirstPerson final : public ICamera {
public:
    const glm::vec3 world_up = glm::vec3(0.0f, 1.0f, 0.0f); /**< 世界坐标的正上方向 */
    glm::vec3   right;          /**< 摄像机的正右方向 */
    float       pitch;          /**< 府仰角（向上或向下看） */
    float       yaw;            /**< 偏航角（向左或向右看） */

    CameraFirstPerson(glm::vec3 _eye = glm::vec3(0.0f, 0.0f, 0.0f))
        : ICamera(_eye, glm::vec3(0.0f, 0.0f, -1.0f))
    {
        this->speed = 5.5f;
        this->sensitivity = 50.0f;
        this->pitch = 0.0f;
        this->yaw = -90.0f;
        this->update();
        this->type = ICamera::Type::FirstPerson;
    };

    virtual void update();

    virtual void processCameraMove(Movement dir, float delta_time);

    virtual void processMouseMove(const glm::vec2& pa, const glm::vec2& pb);
};
