cc_binary(
    name = "castleGame",
    srcs = [
        "CastleGame.cpp",
        "SoundUtil.h"
    ],
    deps = [
        "@openal-soft//:al",
        "@openal-soft//examples:alhelpers",
        "@glut//freeglut/freeglut:glut",
        "@OpenFBX//:openFBX"
    ],
    linkopts = ["-lGL"],
    data = [
        "@music//file"
    ],
    visibility = ["//visibility:public"]
)