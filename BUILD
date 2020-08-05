cc_binary(
    name = "game",
    srcs = [
        "CastleGame.cpp",
        "Audio.h",
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
        "-lGLU"
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
    "-lm",
    "-lGL", 
    "-lGLEW",
    "-lglut", 
    "-lGLU",
  ],
#   deps = [
#     "@glew//:glew",
#   ],
  visibility = ["//visibility:public"]
)