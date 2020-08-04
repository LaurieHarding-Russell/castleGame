cc_binary(
    name = "game",
    srcs = [
        "CastleGame.cpp",
        "Audio.h",
        "ShaderLoader.h"
    ],
    deps = [
        "@openal-soft//:al",
        "@openal-soft//examples:alhelpers",
        "@glut//freeglut/freeglut:glut",
        "@OpenFBX//:openFBX",
        ":OggVorbois",
    ],
    linkopts = [
        "-lGL",
    ],
    data = [
        "@music//file",
        "assets/box.fbx",
        "@glew//:glew",
        "shaders/fragmentShader.glsl",
        "shaders/vertexShader.glsl"
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

