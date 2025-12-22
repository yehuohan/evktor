--- Globals
set_xmakever("3.0.0")
set_languages("c++20")
set_objectdir("$(builddir)/objs")
set_dependir("$(builddir)/deps")

--- Requires
add_requires("vulkan-headers vulkan-sdk-1.4.321.0", { verify = false })
-- volk使用vulkan-sdk-1.4.321.0时会crash
-- add_requires("volk vulkan-sdk-1.4.321.0", { verify = false, configs = { header_only = true } })
add_requires("volk 1.4.309+0", { configs = { header_only = true } })
add_requires("glslang vulkan-sdk-1.4.321.0", {
	verify = false,
	configs = { default_resource_limits = true },
})
-- add_requires("slang")
add_requires("vulkan-memory-allocator 3.3.0")
add_requires("glfw 3.3.9")
add_requires("glm 1.0.1")
add_requires("stb 2025.03.14")
add_requires("imgui 1.90", { configs = { glfw = true, vulkan = true } })
add_requires("tinygltf 2.8.22")
add_requires("fmt 10.1.1")

local src_dir = "$(scriptdir)/src/"

--- Target: libvkt_devel
target("vkt_devel", function()
	set_kind("static")
	add_files(src_dir .. "libvkt_devel/**.cpp")
	add_includedirs(src_dir .. "libvkt_devel", { public = true })
	add_packages("glfw", "glm", "stb", "imgui", { public = true })
	add_packages("vktor")
	add_deps("vktor")
end)

--- Target: libvkt_scene
target("vkt_scene", function()
	set_kind("static")
	add_files(src_dir .. "libvkt_scene/**.cpp")
	add_includedirs(src_dir .. "libvkt_scene", { public = true })
	add_packages("glm", "stb", "tinygltf", { public = true })
	add_packages("vktor")
	add_deps("vktor")
end)

--- Target: vktor
target("vktor", function()
	set_kind("static")
	add_files(src_dir .. "libvktor/**.cpp")
	add_includedirs(src_dir .. "libvktor", { public = true })
	add_packages("vulkan-headers", "volk", "glslang", "vulkan-memory-allocator", "fmt", { public = true })

	add_defines("VK_NO_PROTOTYPES", { public = true })
	add_defines("VMA_STATIC_VULKAN_FUNCTIONS=0", { public = true })
	add_defines("VMA_DYNAMIC_VULKAN_FUNCTIONS=0", { public = true })
	if is_plat("windows") or is_plat("mingw") then
		add_defines("VK_USE_PLATFORM_WIN32_KHR", { public = true })
	elseif is_plat("linux") then
		add_defines("VK_USE_PLATFORM_XLIB_KHR", { public = true })
	elseif is_plat("android") then
		add_defines("VK_USE_PLATFORM_ANDROID_KHR", { public = true })
	elseif is_plat("macosx") then
		add_defines("VK_USE_PLATFORM_MACOS_MVK", { public = true })
	end
end)

--- Target: evktor
target("evktor", function()
	set_kind("binary")
	add_files(src_dir .. "main/**.cpp")
	add_includedirs(src_dir .. "main")
	add_packages("vkt_devel", "vkt_scene", "vktor")
	add_deps("vkt_devel", "vkt_scene", "vktor")
end)

--- Target: vkt_layer
target("vkt_layer", function()
	set_kind("static")
	add_files(src_dir .. "libvkt_layer/**.cpp")
	add_includedirs(src_dir .. "libvkt_layer", { public = true })
	add_packages("vktor", { public = true })
	add_deps("vktor", { public = true })

	if is_plat("windows") then
		add_defines("VKTLYR_API=__declspec(dllexport)", { public = true })
	else
		add_cxflags("-fvisibility=hidden", { public = true })
		add_defines('VKTLYR_API=__attribute__((visibility("default")))', { public = true })
	end
end)

--- Target: sigma
target("sigma", function()
	set_kind("shared")
	add_files(src_dir .. "sigma/**.cpp")
	add_packages("vkt_layer")
	add_deps("vkt_layer")

	set_prefixname("")
	set_basename("VK_LAYER_VKTOR_Sample")
	set_prefixdir("layer", { bindir = "", libdir = "" })
	add_installfiles(src_dir .. "sigma/VK_LAYER_VKTOR_Sample.json")
end)

--- Target: tst_main
target("tst_main", function()
	set_kind("binary")
	add_files("$(scriptdir)/test/*.cpp")
	add_includedirs("$(scriptdir)/test")
	add_packages("vkt_devel", "vkt_scene", "vktor")
	add_deps("vkt_devel", "vkt_scene", "vktor")

	on_prepare(function(tar)
		local case_exts = ""
		local case_maps = "static const Map<String, FnCaseVoid> cases{\n"
		for _, case in ipairs(os.files("$(scriptdir)/test/case_*.cpp")) do
			local name = path.basename(case)
			case_exts = case_exts .. ("extern void %s();\n"):format(name)
			case_maps = case_maps .. ('\t{"%s", %s},\n'):format(name, name)
		end
		case_maps = case_maps .. "};\n"

		local gen_dir = tar:autogendir()
		os.mkdir(gen_dir)
		io.writefile(gen_dir .. "/tst_generated.hpp", case_exts .. case_maps)
		tar:add("includedirs", gen_dir)
	end)
end)

--- Target: tags
target("tags", function()
	set_kind("phony")
	set_default(false)
	on_build(function()
		os.exec("ctags -R $(scriptdir)/src")
	end)
end)
