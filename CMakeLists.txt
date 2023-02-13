
cmake_minimum_required(VERSION 3.10)

project(liboctopus)

if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

set(LIBOCTOPUS_OCTOPUS_HEADERS
    "octopus/octopus.h"
    "octopus/general.h"
    "octopus/filter.h"
    "octopus/fill.h"
    "octopus/stroke.h"
    "octopus/effect.h"
    "octopus/shape.h"
    "octopus/text.h"
    "octopus/layer-change.h"
    "octopus/override.h"
    "octopus/layer.h"
)
set(LIBOCTOPUS_MANIFEST_HEADERS
    "octopus-manifest/octopus-manifest.h"
    "octopus-manifest/general.h"
    "octopus-manifest/status.h"
    "octopus-manifest/resource.h"
    "octopus-manifest/asset.h"
    "octopus-manifest/artifact.h"
    "octopus-manifest/library.h"
    "octopus-manifest/chunk.h"
    "octopus-manifest/component.h"
    "octopus-manifest/page.h"
)
set(LIBOCTOPUS_VALIDATOR_SOURCES
    "octopus/validator.h"
    "octopus/validator.cpp"
)
set(LIBOCTOPUS_JSON_SOURCES
    "octopus/parser.h"
    "octopus/parser.cpp"
    "octopus/serializer.h"
    "octopus/serializer.cpp"
)
set(LIBOCTOPUS_MANIFEST_JSON_SOURCES
    "octopus-manifest/parser.h"
    "octopus-manifest/parser.cpp"
    "octopus-manifest/serializer.h"
    "octopus-manifest/serializer.cpp"
)

add_library(liboctopus ${LIBOCTOPUS_OCTOPUS_HEADERS} ${LIBOCTOPUS_MANIFEST_HEADERS} ${LIBOCTOPUS_VALIDATOR_SOURCES} ${LIBOCTOPUS_JSON_SOURCES} ${LIBOCTOPUS_MANIFEST_JSON_SOURCES})

target_include_directories(liboctopus PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

source_group("Octopus structures" FILES ${LIBOCTOPUS_OCTOPUS_HEADERS})
source_group("Manifest structures" FILES ${LIBOCTOPUS_MANIFEST_HEADERS})
source_group("Octopus validator" FILES ${LIBOCTOPUS_VALIDATOR_SOURCES})
source_group("Octopus serialization" FILES ${LIBOCTOPUS_JSON_SOURCES})
source_group("Manifest serialization" FILES ${LIBOCTOPUS_MANIFEST_JSON_SOURCES})
