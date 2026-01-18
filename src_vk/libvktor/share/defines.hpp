#pragma once

// libvktor/share
#define VKT_SHARE_PRINT2FILE

// libvktor/vktor/core
/** Print verbose information */
#define VKT_CORE_VERBOSE true
/**
 * @brief Select Vulkan api version
 *
 * - VK_API_VERSION_1_1:
 *      * VK_KHR_get_physical_device_properties2 was promoted, which is better for VMA
 * - VK_API_VERSION_1_2:
 *      * VK_KHR_buffer_device_address was promoted, which is better for VMA
 * - VK_API_VERSION_1_3:
 *      * VK_KHR_dynamic_rendering was promoted
 */
#define VKT_CORE_VK_API_VERSION VK_API_VERSION_1_3
#define VKT_CORE_QUEUE_PRIORITY 1.0f
#define VKT_CORE_MAX_SETS       16
