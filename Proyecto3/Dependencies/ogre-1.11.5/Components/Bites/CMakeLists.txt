#-------------------------------------------------------------------
# This file is part of the CMake build system for OGRE
#     (Object-oriented Graphics Rendering Engine)
# For the latest info, see http://www.ogre3d.org/
#
# The contents of this file are placed in the public domain. Feel
# free to make use of it in any way you like.
#-------------------------------------------------------------------

############################################################
# Paging optional component
############################################################

if(ANDROID)
    include_directories(${ANDROID_NDK}/sources/android/native_app_glue)
endif()

if(EMSCRIPTEN)
    add_definitions(-s USE_SDL=2)
endif()

if (OGRE_STATIC)
  include_directories(${PROJECT_SOURCE_DIR}/RenderSystems/Direct3D9/include ${DirectX9_INCLUDE_DIR})
  include_directories(${PROJECT_SOURCE_DIR}/RenderSystems/Direct3D11/include)

  # Link to all enabled plugins
  if (OGRE_BUILD_PLUGIN_OCTREE)
    set(DEPENDENCIES ${DEPENDENCIES} Plugin_OctreeSceneManager)
  endif ()
  if (OGRE_BUILD_PLUGIN_BSP)
    set(DEPENDENCIES ${DEPENDENCIES} Plugin_BSPSceneManager)
  endif ()
  if (OGRE_BUILD_PLUGIN_CG)
    set(DEPENDENCIES ${DEPENDENCIES} Plugin_CgProgramManager)
  endif ()
  if (OGRE_BUILD_PLUGIN_PFX)
    set(DEPENDENCIES ${DEPENDENCIES} Plugin_ParticleFX)
  endif ()
  if (OGRE_BUILD_PLUGIN_PCZ)
    set(DEPENDENCIES ${DEPENDENCIES} Plugin_PCZSceneManager)
  endif ()
  if (OGRE_BUILD_PLUGIN_STBI)
    set(DEPENDENCIES ${DEPENDENCIES} Codec_STBI)
  endif ()
  if (OGRE_BUILD_PLUGIN_FREEIMAGE)
    set(DEPENDENCIES ${DEPENDENCIES} Codec_FreeImage)
  endif ()
  if (OGRE_BUILD_RENDERSYSTEM_D3D9)
    set(DEPENDENCIES ${DEPENDENCIES} RenderSystem_Direct3D9)
  endif ()
  if (OGRE_BUILD_RENDERSYSTEM_D3D11)
    set(DEPENDENCIES ${DEPENDENCIES} RenderSystem_Direct3D11)
  endif ()
  if (OGRE_BUILD_RENDERSYSTEM_GL)
    set(DEPENDENCIES ${DEPENDENCIES} RenderSystem_GL)
  endif ()
  if (OGRE_BUILD_RENDERSYSTEM_GL3PLUS)
    set(DEPENDENCIES ${DEPENDENCIES} RenderSystem_GL3Plus)
  endif ()
  if (OGRE_BUILD_RENDERSYSTEM_GLES2)
    set(DEPENDENCIES ${DEPENDENCIES} RenderSystem_GLES2)
  endif ()
endif ()

# define header and source files for the library
file(GLOB HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")
list(APPEND HEADER_FILES
  ${PROJECT_BINARY_DIR}/include/OgreBitesPrerequisites.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/OgreBites.i)
set(SOURCES 
  "${CMAKE_CURRENT_SOURCE_DIR}/src/OgreAdvancedRenderControls.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/OgreApplicationContext.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/OgreBitesConfigDialog.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/OgreCameraMan.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/OgreSGTechniqueResolverListener.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/OgreStaticPluginLoader.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/OgreTrays.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/OgreWindowEventUtilities.cpp")

if(ANDROID OR EMSCRIPTEN OR APPLE_IOS OR WINDOWS_STORE OR WINDOWS_PHONE)
  # no config dialog available
elseif(WIN32)
  include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src")
  list(APPEND SOURCES 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/OgreWIN32ConfigDialog.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/resource.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/misc/OgreWin32Resources.rc")
  # Need to include resource files so that icons are linked
  set(RESOURCE_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/resource.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/misc/OgreWin32Resources.rc"
  )
  source_group(Resources FILES ${RESOURCE_FILES})
elseif(APPLE)
  list(APPEND SOURCES 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/OgreOSXConfigDialog.mm"
    "${CMAKE_CURRENT_SOURCE_DIR}/misc/ogrelogo.png")
  set_source_files_properties("${CMAKE_CURRENT_SOURCE_DIR}/src/OgreOSXConfigDialog.mm"
    PROPERTIES COMPILE_FLAGS "-Wno-deprecated-declarations"
  )
  set(RESOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/misc/ogrelogo.png")
  source_group(Resources FILES ${RESOURCE_FILES})
  set(DEPENDENCIES ${DEPENDENCIES} "-framework Cocoa")
elseif(UNIX)
  list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/OgreGLXConfigDialog.cpp")
  list(APPEND DEPENDENCIES ${X11_X11_LIB} ${X11_Xt_LIB} ${XAW_LIBRARY})
  install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/misc/GLX_backdrop.png" DESTINATION "share/OGRE/")
endif()

# setup target
add_library(OgreBites ${OGRE_COMP_LIB_TYPE} ${HEADER_FILES} ${SOURCES})
set_target_properties(OgreBites PROPERTIES VERSION ${OGRE_SOVERSION} SOVERSION ${OGRE_SOVERSION})
target_link_libraries(OgreBites PUBLIC OgreMain OgreOverlay PRIVATE ${DEPENDENCIES})
if (OGRE_BUILD_COMPONENT_RTSHADERSYSTEM)
  target_link_libraries(OgreBites PUBLIC OgreRTShaderSystem)
endif ()
target_include_directories(OgreBites PUBLIC 
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
  $<INSTALL_INTERFACE:include/OGRE/Bites>)

if(OGRE_STATIC AND APPLE AND OGRE_BUILD_PLUGIN_CG)
  # workaround so the Cg framework is found in the above condition
  target_include_directories(OgreBites PUBLIC ${Cg_INCLUDE_DIRS})
endif()

if(SDL2_FOUND)
  target_include_directories(OgreBites PRIVATE ${SDL2_INCLUDE_DIR})
  target_link_libraries(OgreBites PRIVATE ${SDL2_LIBRARY})
endif()

generate_export_header(OgreBites 
    EXPORT_MACRO_NAME _OgreBitesExport
    EXPORT_FILE_NAME ${PROJECT_BINARY_DIR}/include/OgreBitesPrerequisites.h)

# install 
ogre_config_framework(OgreBites)
ogre_config_component(OgreBites)

install(FILES ${HEADER_FILES}
  DESTINATION include/OGRE/Bites
)
