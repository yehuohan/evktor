set shell := ['bash', '-uc']
set dotenv-load
set ignore-comments

dir_root := replace(justfile_directory(), '\', '/')
dir_home := replace(env('DOT_HOME'), '\', '/')

build_type := env('BUILD_TYPE', 'Debug')
# build_type := env('BUILD_TYPE', 'Release')
build_gen := env('BUILD_GEN', 'Ninja')
# build_gen := env('BUILD_GEN', '"Unix Makefiles"')
build_job := '-j4'
dir_build := dir_root / '_VOut' / build_type
dir_install := dir_root / 'install' / build_type

export VCPKG_ROOT := dir_home / 'vcpkg'
export VCPKG_TRIPLET := env('VCPKG_TRIPLET', 'x64-mingw-mix')
VCPKG_XSCRIPT := 'clear;x-script,bash {{dir_root}}/scripts/vcpkg_xscript.sh {url} {dst};x-block-origin'
DEPS_DIR := dir_root / 'deps'


all: evktor #omega

evktor: src
    @echo [run] evktor...
    {{dir_install}}/evktor {{dir_root}}/../assets {{dir_root}}/glsl

omega: src
    @echo [run] evktor/omega...
    {{dir_install}}/omega {{dir_root}}/../assets {{dir_root}}/glsl

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Build src
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
src: gen
    @echo [src] Build evktor...
    cmake --build {{dir_build}} {{build_job}}
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
    cmake --build {{dir_build}} {{build_job}} --target tags

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
    -git clone --depth=1 https://github.com/zeux/volk.git {{DEPS_DIR}}/repos/volk
    -git clone --depth=1 https://github.com/KhronosGroup/Vulkan-ValidationLayers.git {{DEPS_DIR}}/repos/Vulkan-ValidationLayers
    pip install glad2
    python -m glad \
        --api='gl:core=4.5' \
        --extensions='' \
        --reproducible \
        --out-path {{DEPS_DIR}}/repos/glad

deps-gen:
    @echo Prepare generated
    python {{dir_root}}/scripts/generate.py
