load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_file")

# Sound
http_archive(
    name = "openal-soft",
    urls = ["https://github.com/LaurieHarding-Russell/openal-soft/archive/0288c3ed3894f9d093537825bc2a03fc35a424ef.zip"],
    strip_prefix = "openal-soft-0288c3ed3894f9d093537825bc2a03fc35a424ef",
)

http_file(
    name = "music",
    urls = ["https://upload.wikimedia.org/wikipedia/commons/2/29/Richard_Wagner_-_Ride_of_the_Valkyries.ogg"]
)

#graphics
http_archive(
    name = "glut",
    urls = ["https://github.com/LaurieHarding-Russell/FreeGLUT/archive/fb1ce95712dc472aff5279e0e8e19d684549204e.zip"],
    strip_prefix = "FreeGLUT-fb1ce95712dc472aff5279e0e8e19d684549204e",
    sha256 = "6e9034e1f5dd94524cd96c951e8c928a0ea91649d87f8aeb87e25045fa66ba4b",
)


# Asset Loader
http_archive(
    name = "OpenFBX",
    urls = ["https://github.com/nem0/OpenFBX/archive/f94fcb1ab0ee618c3c9ca105836ed52102bbcd7c.zip"],
    strip_prefix = "OpenFBX-f94fcb1ab0ee618c3c9ca105836ed52102bbcd7c",
    build_file = "OpenFBX.BUILD",
    sha256 = "8502ddcabfdbfb9f7099a8f4cbb073ce851e25cf35322f7df716d814c741d09f"
)