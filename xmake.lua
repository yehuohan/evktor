set_xmakever("2.9.1")

-- Deps
add_requires("vulkan-headers")
-- add_requires("glslang >=13.1.1")
add_requires("vulkan-memory-allocator >=3.0.1")
add_requires("glfw >=3.3.9")
add_requires("glm >=1.0.1")
add_requires("stb >=2023.12.15")
add_requires("imgui >=1.90", {
	configs = {
		glfw = true,
		glfw_opengl3 = true,
		glfw_vulkan = true,
	},
})
add_requires("tinygltf >=2.8.17")
add_requires("freetype >=2.12.1")
add_requires("assimp >=5.3.1")
add_requires("fmt >=10.1.1")

-- target("test", function()
--  set_kind("binary")
--  add_files("tst_xmake.cpp")
-- end)
