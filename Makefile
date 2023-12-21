DIR_ROOT := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

BUILD_TYPE ?= Debug
#BUILD_TYPE ?= Release
BUILD_GEN ?= "Ninja"
#BUILD_GEN ?= "Unix Makefiles"
BUILD_JOB ?= -j4
DIR_BUILD ?= _VOut/${BUILD_TYPE}
DIR_INSTALL ?= install/${BUILD_TYPE}

VCPKG_ROOT ?= ${APPS_HOME}/vcpkg
VCPKG_TRIPLET ?= x64-mingw-mix
VCPKG_XSCRIPT := 'clear;x-script,bash ${DIR_ROOT}/scripts/vcpkg_xscript.sh {url} {dst};x-block-origin'
DEPS_DIR ?= ${DIR_ROOT}/deps


.PHONY: all
all: alpha #omega

.PHONY: alpha
alpha: src
	@echo [run] evktor/alpha...
	./${DIR_INSTALL}/alpha ${DIR_ROOT}/../assets

.PHONY: omega
omega: src
	@echo [run] evktor/omega...
	./${DIR_INSTALL}/omega ${DIR_ROOT}/../assets

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Build src
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
.PHONY: src
src: gen
	@echo [src] Build evktor...
	cmake -G ${BUILD_GEN} -Wno-dev \
		-DCMAKE_BUILD_TYPE=${BUILD_TYPE} \
		-DCMAKE_INSTALL_PREFIX=${DIR_INSTALL} \
		-DPROJECT_BUILD_DIR=${DIR_BUILD} \
		-DCMAKE_TOOLCHAIN_FILE=${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake \
		-DVCPKG_TARGET_TRIPLET=${VCPKG_TRIPLET} \
		-DVCPKG_OVERLAY_TRIPLETS=${DIR_ROOT}/cmake \
		-DVCPKG_INSTALLED_DIR=${DEPS_DIR} \
		-DVCPKG_MANIFEST_INSTALL=OFF \
		-S . -B ${DIR_BUILD}

.PHONY: gen
gen:
	@echo [src] Generate evktor...
	cmake -G ${BUILD_GEN} -Wno-dev \
		-DCMAKE_BUILD_TYPE=${BUILD_TYPE} \
		-DCMAKE_INSTALL_PREFIX=${DIR_INSTALL} \
		-DPROJECT_BUILD_DIR=${DIR_BUILD} \
		-DCMAKE_TOOLCHAIN_FILE=${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake \
		-DVCPKG_TARGET_TRIPLET=${VCPKG_TRIPLET} \
		-DVCPKG_OVERLAY_TRIPLETS=${DIR_ROOT}/cmake \
		-DVCPKG_INSTALLED_DIR=${DEPS_DIR} \
		-DVCPKG_MANIFEST_INSTALL=OFF \
		-S . -B ${DIR_BUILD}

.PHONY: tags
tags: gen
	cmake --build ${DIR_BUILD} ${BUILD_JOB} --target tags

.PHONY: clean
clean:
	-rm -rf ${DIR_BUILD}
	-rm -rf ${DIR_INSTALL}

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Build deps
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
.PHONY: deps
deps:
	@echo Prepare deps...
	vcpkg install --recurse --no-binarycaching \
		--triplet=${VCPKG_TRIPLET} \
		--overlay-triplets=${DIR_ROOT}/cmake \
		--x-install-root=${DEPS_DIR} \
		--x-asset-sources=${VCPKG_XSCRIPT}

.PHONY: deps-repos
deps-repos:
	# Modify vcpkg.json to install/remove
	@echo Prepare deps-repos...
	git clone --depth=1 https://github.com/zeux/volk.git ${DEPS_DIR}/repos/volk
	git clone --depth=1 https://github.com/KhronosGroup/Vulkan-ValidationLayers.git ${DEPS_DIR}/repos/Vulkan-ValidationLayers
