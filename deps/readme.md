# Notes about dependencies

## GLFW
Removed the following content from the original GLFW source:
- glfw/docs
- glfw/examples
- glfw/tests

## GLAD
GLAD2 - OpenGL Core 4.3
Permalink:
    - https://gen.glad.sh/#generator=c&api=gl%3D4.3&profile=gl%3Dcore%2Cgles1%3Dcommon

### Fixing GLAD's clock skewed warning

The warning:
```bash
make[2]: Warning: File '../deps/glad/src/gl.c' has modification time 9985 s in the future
```
 The fix:
```bash
cd /path/to/file
touch tmp
cp file.xxx tmp
rm file.xxx
mv tmp file.xxx
```
