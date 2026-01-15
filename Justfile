# vim@code{ efm = [[error: %f:%l:%c: %m,%.%#error: %f:%l: %m]], efm_fts = { 'cmake', 'cpp', 'glsl', 'shaderslang', 'rust', 'python' } }:
set shell := ['bash', '-uc']
set dotenv-load
set ignore-comments

dir_root := replace(justfile_directory(), '\', '/')

xplat := env('XPLAT', if os() == "windows" { 'mingw' } else { 'linux' })
xarch := env('XARCH', 'x86_64')
xmode := env('XBUILD', 'debug')
dir_xbuild := dir_root / '_VOut'
dir_xinstall := dir_root / 'install'

build_type := env('BUILD_TYPE', 'Debug') # 'Release'
build_gen := env('BUILD_GEN', 'Ninja')
dir_build := dir_root / '_VOut' / build_type
dir_install := dir_root / 'install' / build_type

export LD_LIBRARY_PATH := dir_install / 'lib'

export XMAKE_CONFIGDIR := dir_xbuild / 'xmake'
export XMAKE_MAIN_REPO := 'https://gitee.com/tboox/xmake-repo.git'

export VCPKG_FORCE_SYSTEM_BINARIES := '1' # Use custom installed pwsh, jinja, cmake
export VCPKG_ROOT := replace(env('DOT_APPS'), '\', '/') / 'vcpkg'
export VCPKG_TRIPLET := if os() == "windows" { 'x64-mingw-mix' } else { 'x64-linux-mix' }
VCPKG_XSCRIPT := '"clear;x-script,bash ' + dir_root + '/scripts/vcpkg_xscript.sh {url} {dst};x-block-origin"'
DEPS_DIR := dir_root / 'deps'


all: evktor

# 目前xmake使用相对路径build，会导致Neovim的QuickFix不能正确解析路径
x-all: x-evktor

x-evktor: x-src
    @echo [Run] evktor...
    {{dir_xinstall}}/bin/evktor {{dir_root}}/../assets {{dir_root}}/shaders

x-sigma: x-src
    @echo [Run] evktor/test/tst_main core
    VK_LAYER_PATH={{dir_xinstall}}/layer VK_INSTANCE_LAYERS=VK_LAYER_VKTOR_Sample {{dir_xinstall}}/bin/tst_main core_graphics

x-test case="": x-src
    @echo [Run] evktor/test
    {{dir_xinstall}}/bin/tst_main {{case}}

evktor: src
    @echo [Run] evktor...
    {{dir_install}}/evktor {{dir_root}}/../assets {{dir_root}}/shaders

omega: src
    @echo [Run] evktor/omega...
    {{dir_install}}/omega {{dir_root}}/../assets {{dir_root}}/shaders

sigma: src
    @echo [Run] evktor/test/tst_main core
    # Replace layers with VK_LAYER_PATH
    VK_LAYER_PATH={{dir_install}}/layer VK_INSTANCE_LAYERS=VK_LAYER_VKTOR_Sample {{dir_install}}/tst_main core_graphics
    # Append layers from VK_ADD_LAYER_PATH (why VK_ADD_LAYER_PATH not work?)
    # VK_ADD_LAYER_PATH={{dir_install}}/layer VK_INSTANCE_LAYERS=VK_LAYER_VKTOR_Sample {{dir_install}}/tst_main core_graphics

test case="": src
    @echo [Run] evktor/test
    {{dir_install}}/tst_main {{case}}

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Build src
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
x-src: x-gen
    @echo [src] Build evktor...
    xmake b -j4
    xmake i --installdir={{dir_xinstall}}

x-gen:
    @echo [src] Generate evktor...
    xmake g --proxy_pac={{dir_root}}/scripts/xmake_pac.lua
    xmake f -y \
        --plat={{xplat}} --arch={{xarch}} --mode={{xmode}} \
        --mingw=c:/apps/msys64/ucrt64 \
        --builddir={{dir_xbuild}}
    xmake project -k compile_commands

x-tags: x-gen
    xmake b tags

x-clean:
    -rm -rf {{dir_xbuild}}/.build_cache
    -rm -rf {{dir_xbuild}}/.gens
    -rm -rf {{dir_xbuild}}/objs
    -rm -rf {{dir_xbuild}}/deps
    -rm -rf {{dir_xbuild}}/xmake

src: gen
    @echo [src] Build evktor...
    cmake --build {{dir_build}} -j4
    cmake --install {{dir_build}}

gen:
    @echo [src] Generate evktor...
    cmake -G {{build_gen}} -Wno-dev \
        -DCMAKE_BUILD_TYPE={{build_type}} \
        -DCMAKE_INSTALL_PREFIX={{dir_install}} \
        -DPROJECT_BUILD_DIR={{dir_build}} \
        -DCMAKE_TOOLCHAIN_FILE={{VCPKG_ROOT}}/scripts/buildsystems/vcpkg.cmake \
        -DVCPKG_TARGET_TRIPLET={{VCPKG_TRIPLET}} \
        -DVCPKG_OVERLAY_TRIPLETS={{dir_root}}/cmake \
        -DVCPKG_INSTALLED_DIR={{DEPS_DIR}} \
        -DVCPKG_MANIFEST_INSTALL=OFF \
        -S . -B {{dir_build}}

tags: gen
    cmake --build {{dir_build}} --target tags

clean:
    -rm -rf {{dir_build}}
    -rm -rf {{dir_install}}

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Build deps
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
deps:
    # Modify vcpkg.json to install/remove
    @echo Prepare deps...
    vcpkg install --recurse --no-binarycaching \
        --triplet={{VCPKG_TRIPLET}} \
        --overlay-triplets={{dir_root}}/cmake \
        --x-install-root={{DEPS_DIR}} \
        --x-asset-sources={{VCPKG_XSCRIPT}}

deps-repos:
    @echo Prepare deps-repos...
    -git clone --depth=1 https://github.com/LelouchHe/xmake-luals-addon.git {{DEPS_DIR}}/repos/xmake-luals-addon
    -git clone --depth=1 -b vulkan-sdk-1.4.321 https://github.com/zeux/volk.git {{DEPS_DIR}}/repos/volk
    -git clone --depth=1 -b vulkan-sdk-1.4.321 https://github.com/KhronosGroup/Vulkan-Headers.git {{DEPS_DIR}}/repos/Vulkan-Headers
    -git clone --depth=1 -b vulkan-sdk-1.4.321 https://github.com/KhronosGroup/Vulkan-ValidationLayers.git {{DEPS_DIR}}/repos/Vulkan-ValidationLayers
    pip install glad2
    python -m glad \
        --api='gl:core=4.5' \
        --extensions='' \
        --reproducible \
        --out-path {{DEPS_DIR}}/repos/glad

deps-gen:
    @echo Prepare generated
    python {{dir_root}}/scripts/generate.py
