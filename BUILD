cc_binary(
    name = "game",
    srcs = [
        "CastleGame.cpp",
        "Audio.h",
        "Audio.cpp",
        "CommonTypes.h",
        "GameData.h",
        "units/Archer.h",
        "units/Archer.cpp",
        "units/Castle.h",
        "units/Castle.cpp",
        "units/Peasant.h",
        "units/Peasant.cpp",
        "units/Tree.h",
        "units/Tree.cpp",
        "units/Swordsman.h",
        "units/Swordsman.cpp",
        "units/Unit.h",
    ],
    deps = [
        "@openal-soft//:al",
        "@openal-soft//examples:alhelpers",
        "@glut//freeglut/freeglut:glut",
        "@OpenFBX//:openFBX",
        ":OggVorbois",
        ":initShader"
    ],
    linkopts = [
        "-lGL",
    ],
    data = [
        "@music//file",
        "assets/box.fbx",
        "shaders/fragmentShader.glsl",
        "shaders/vertexShader.glsl"
    ],
    defines = [ 
        "DEBUG", 
        "GL_GLEXT_PROTOTYPES"
    ],
    visibility = ["//visibility:public"]
)

cc_library(
    name = "OggVorbois",
    hdrs = ["@OggVorbois//file"],
    deps = [
        "@openal-soft//:al",
    ],
    visibility = ["//visibility:public"],
    strip_include_prefix = "/external/OggVorbois/file",
    include_prefix = "OggVorbois",
    linkstatic = True,
)

cc_library(
  name = "initShader",
  hdrs = ["ShaderLoader.h"],
  linkopts = [
    "-lGL", 
  ],
  deps = [
    "@glew//:glew",
  ],
  visibility = ["//visibility:public"]
)