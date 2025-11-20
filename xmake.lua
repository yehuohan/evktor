-- Addon: git clone https://github.com/LelouchHe/xmake-luals-addon ./deps/xmake-luals-addon

--[[
dir_xmake := dir_root / 'xmake'
export XMAKE_CONFIGDIR := dir_xmake / '.xmake'
export XMAKE_PKG_INSTALLDIR := dir_xmake / 'pkgs'
export XMAKE_PKG_CACHEDIR := dir_xmake / 'cache'

# x:
#     xmake g --proxy_pac={{dir_xmake}}/pac.lua
#     xmake f --buildir={{dir_root}}/_VOut/xmake
--]]


add_requires("vulkan-headers")

-- evktor
-- target("evktor", function()
--  set_kind("binary")
--  add_files("src/main/*.cpp")
-- end)
