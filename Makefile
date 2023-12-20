DIR_ROOT := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

BUILD_TYPE ?= Debug
#BUILD_TYPE ?= Release
#BUILD_GEN ?= "NMake Makefiles"
#BUILD_GEN ?= "Unix Makefiles"
BUILD_GEN ?= "Ninja"
BUILD_JOB ?= -j4
BUILD_DIR ?= _VOut/${BUILD_TYPE}
INSTALL_DIR ?= install/${BUILD_TYPE}

VCPKG_ROOT ?= ${APPS_HOME}/vcpkg
VCPKG_TRIPLET ?= x64-mingw-mix
VCPKG_XSCRIPT := 'clear;x-script,bash ${DIR_ROOT}/scripts/vcpkg_xscript.sh {url} {dst};x-block-origin'
DEPS_DIR ?= ${DIR_ROOT}/deps


.PHONY: all
all: alpha #omega

.PHONY: alpha
alpha: src
	@echo [run] egraphics/alpha...
	./${INSTALL_DIR}/alpha ${DIR_ROOT}/../assets

.PHONY: omega
omega: src
	@echo [run] egraphics/omega...
	./${INSTALL_DIR}/omega ${DIR_ROOT}/../assets

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Build src
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
.PHONY: src
src:
	@echo [src] Build egraphics...
	cmake -G ${BUILD_GEN} -Wno-dev \
		-DCMAKE_BUILD_TYPE=${BUILD_TYPE} \
		-DCMAKE_INSTALL_PREFIX=${INSTALL_DIR} \
		-DPROJECT_BUILD_DIR=${BUILD_DIR} \
		-DCMAKE_TOOLCHAIN_FILE=${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake \
		-DVCPKG_TARGET_TRIPLET=${VCPKG_TRIPLET} \
		-DVCPKG_OVERLAY_TRIPLETS=${DIR_ROOT}/cmake \
		-DVCPKG_INSTALLED_DIR=${DEPS_DIR} \
		-DVCPKG_MANIFEST_INSTALL=OFF \
		-S . -B ${BUILD_DIR}
	cmake --build ${BUILD_DIR} ${BUILD_JOB}
	cmake --install ${BUILD_DIR}

.PHONY: clean
clean:
	-rm -rf ${BUILD_DIR}

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

.PHONY: tags
tags:
	cmake -G ${BUILD_GEN} -Wno-dev \
		-DCMAKE_BUILD_TYPE=${BUILD_TYPE} \
		-DCMAKE_INSTALL_PREFIX=${BUILD_DIR}/${BUILD_TYPE} \
		-S . -B ${BUILD_DIR}
	cmake --build ${BUILD_DIR} ${BUILD_JOB} --target tags
