#ifdef _WIN32
	#include <windows.h>
#endif

#include <GL/glew.h> // Needs to be imported before Resource.hpp as it includes gl.h
#include "resources.hpp"
#include <fstream>
#include "stb_image.c"
#include <iostream>

static const char *vertex_shaders[NUM_SHADERS]   = {"./data/shaders/ppl.vert", "./data/shaders/nmap.vert"};
static const char *fragment_shaders[NUM_SHADERS] = {"./data/shaders/ppl.frag", "./data/shaders/nmap.frag"};

static const char *texture_files[NUM_TEXTURES] = {
	"./data/wall.png", "./data/wall_normalmap.png",
	"./data/tiles.png", "./data/tiles_normalmap.png",
	"./data/acid.png", "./data/acid_normalmap.png",
	"./data/cake.png",
	"./data/blueportal.png", "./data/orangeportal.png",
	"./data/crosshair.png",
	"./data/balls.png",
	"./data/strings.png"
};

/**
 * Loads all textures from files.
 */
void Resources::loadTextures() {
	for(int i = 0; i < NUM_TEXTURES; i++) {
		textures[i] = createTexture(texture_files[i]);
	}
}

/**
 * Binds a texture.
 *
 * @param id TEXTURE_ID of the texture to bind
 */
void Resources::bindTexture(TEXTURE_ID id) {
	if(id == TID_WALL) {
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, textures[TID_WALL_NMAP]);
	} else if(id == TID_TILES) {
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, textures[TID_TILES_NMAP]);
	} else if(id == TID_ACID) {
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, textures[TID_ACID_NMAP]);
	}

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textures[id]);
}

/**
 * Compiles all GLSL shaders
 */
void Resources::compileShaders() {
	GLuint vert, frag; // Vertex and fragment shader handles
	for(int i = 0; i < NUM_SHADERS; i++) {
		// Create handles for program and shaders
		programs[i] = glCreateProgram();
		vert = glCreateShader(GL_VERTEX_SHADER);
		frag = glCreateShader(GL_FRAGMENT_SHADER);

		// Read shaders from files
		char *vs_source = readShader(vertex_shaders[i]);
		char *fs_source = readShader(fragment_shaders[i]);

		if (!vs_source || !fs_source) {
            std::cerr << "Failed to read shader files for program " << i << std::endl;
            continue;
        }

		// Loader shader sources
		glShaderSource(vert, 1, (const char**)&vs_source, NULL);
		glShaderSource(frag, 1, (const char**)&fs_source, NULL);

		// Compile shaders
		glCompileShader(vert);
		// printShaderLog(vert);
		printShaderLog(vert, vertex_shaders[i]);

		glCompileShader(frag);
		// printShaderLog(frag);
		printShaderLog(frag, fragment_shaders[i]);


		// Attach shaders to program
		glAttachShader(programs[i], vert);
		glAttachShader(programs[i], frag);
		
		// Link program
		glLinkProgram(programs[i]);
		// printProgramLog(programs[i]);
		printProgramLog(programs[i], vertex_shaders[i], fragment_shaders[i]);

		// Free memory from shader files
		delete[] vs_source;
		delete[] fs_source;
	}
}

/**
 * Prints the log output from a compiled shader if any.
 *
 * @param shader Handle of the shader
 */
void Resources::printShaderLog(GLuint shader, const char* shaderFile) {
    char buffer[512];
    memset(buffer, 0, sizeof(buffer));
    GLsizei length = 0;
    glGetShaderInfoLog(shader, sizeof(buffer), &length, buffer);
    if (length > 0) {
        std::cerr << "Error in shader (" << shaderFile << "):\n" << buffer << std::endl;
    }
}

/**
 * Prints the log output from a linked program.
 *
 * @param program Handle of the program
 */
void Resources::printProgramLog(GLuint program, const char* vertexShaderFile, const char* fragmentShaderFile) {
    char buffer[512];
    memset(buffer, 0, sizeof(buffer));
    GLsizei length = 0;
    glGetProgramInfoLog(program, sizeof(buffer), &length, buffer);
    if (length > 0) {
        std::cerr << "Error linking program (" << vertexShaderFile << " + " << fragmentShaderFile << "):\n" << buffer << std::endl;
    }
}

/**
 * Enables a shader program from the enumerator PROGRAM_ID.
 *
 * @param pid PROGRAM_ID for the program to enable
 */
void Resources::enableProgram(PROGRAM_ID pid) {
	glUseProgram(programs[pid]);

	// Set normal shader uniforms
	// Bind first texture unit to "texture" in fragment shader
	GLuint paramTex = glGetUniformLocation(programs[pid], "tex");
	glUniform1i(paramTex, 0);
	// Bind second texture unit to "nmap" in fragment shader
	GLuint paramNmap = glGetUniformLocation(programs[pid], "nmap");
	glUniform1i(paramNmap, 1);
}

/**
 * Disables the current program and falls back to fixed-function pipeline
 */
void Resources::disableProgram() {
	glUseProgram(0);
}

/**
 * Reads the entire contents of a shader into a char buffer.
 * Data must be freed after use.
 *
 * @param filename Path to the shader to read
 *
 * @return Pointer to array of chars containing shader
 */
char* Resources::readShader(const char *filename) {
    std::ifstream file(filename, std::ios::in | std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Failed to open shader file: " << filename << std::endl;
        return nullptr;
    }

    file.seekg(0, std::ios::end);
    int length = file.tellg();
    file.seekg(0, std::ios::beg);
    char* buffer = new char[length + 1];
    file.read(buffer, length);
    buffer[length] = '\0';
    file.close();

    return buffer;
}

/**
 * Loads a texture from disk and return a handle to it.
 *
 * @param filename Path to a texture image
 *
 * @return Handle of the created OpenGL texture
 */
GLuint Resources::createTexture(const char *filename) {
	GLuint handle;
	glGenTextures(1, &handle);
	glBindTexture(GL_TEXTURE_2D, handle);

	// Read bitmap data
	int w, h, n;
	unsigned char *data = stbi_load(filename, &w, &h, &n, 0);


	if (!data) {
        std::cerr << "Failed to load texture: " << filename << std::endl;
        return 0;
    }


	// Create texture with mip maps
	if(n == 3)
		gluBuild2DMipmaps(GL_TEXTURE_2D, n, w, h, GL_RGB, GL_UNSIGNED_BYTE, data);
	else if(n == 4)
		gluBuild2DMipmaps(GL_TEXTURE_2D, n, w, h, GL_RGBA, GL_UNSIGNED_BYTE, data);

	stbi_image_free(data);

	// Repeat texture in s- and t-axis
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Print any errors
	GLenum error = glGetError();
	while(error != GL_NO_ERROR) {
		printf("Error: %d\n", error);
		error = glGetError();
	}

	return handle;
}

/**
 * Draws a display list model
 *
 * @param mid MODEL_ID of the model to draw
 */
void Resources::drawModel(MODEL_ID mid) {
	glCallList(models[mid]);
}

/**
 * Compiles all display lists and populates the models array
 */
void Resources::compileModels() {
	GLuint lists = glGenLists(NUM_MODELS);
	for(int i = 0; i < NUM_MODELS; i++) {
		models[i] = lists+i;
	}

	// Compile portal stencil model
	glNewList(models[MID_PORTAL_STENCIL], GL_COMPILE);
		glBegin(GL_TRIANGLE_FAN);
			glVertex3f( 0.00f, 0.00f, 0.001f);

			glVertex3f( 0.00f, 1.25f, 0.001f);
			glVertex3f(-0.29f, 1.15f, 0.001f);
			glVertex3f(-0.53f, 0.88f, 0.001f);
			glVertex3f(-0.69f, 0.48f, 0.001f);

			glVertex3f(-0.75f, 0.00f, 0.001f);
			glVertex3f(-0.69f,-0.48f, 0.001f);
			glVertex3f(-0.53f,-0.88f, 0.001f);
			glVertex3f(-0.29f,-1.15f, 0.001f);

			glVertex3f( 0.00f,-1.25f, 0.001f);
			glVertex3f( 0.29f,-1.15f, 0.001f);
			glVertex3f( 0.53f,-0.88f, 0.001f);
			glVertex3f( 0.69f,-0.48f, 0.001f);

			glVertex3f( 0.75f, 0.00f, 0.001f);
			glVertex3f( 0.69f, 0.48f, 0.001f);
			glVertex3f( 0.53f, 0.88f, 0.001f);
			glVertex3f( 0.29f, 1.15f, 0.001f);

			glVertex3f( 0.00f, 1.25f, 0.001f);
		glEnd();
	glEndList();

	// Compile portal outline
	glNewList(models[MID_PORTAL_OUTLINE], GL_COMPILE);
		glBegin(GL_QUADS);
			glNormal3f(0,0,1);
			glTexCoord2f(0.207, 0); glVertex3f(-0.84, 1.35, 0.002);
			glTexCoord2f(0.207, 1); glVertex3f(-0.84,-1.35, 0.002);
			glTexCoord2f(0.793, 1); glVertex3f( 0.84,-1.35, 0.002);
			glTexCoord2f(0.793, 0); glVertex3f( 0.84, 1.35, 0.002);
		glEnd();
	glEndList();

	// Compile cake model
	glNewList(models[MID_CAKE], GL_COMPILE);
		glBegin(GL_QUADS);
			// Front side
			glTexCoord2f(0.000f, 0.00f); glVertex3f(-0.2f,  0.3f, 0.00f);
			glTexCoord2f(0.000f, 0.25f); glVertex3f(-0.2f,  0.0f, 0.00f);
			glTexCoord2f(0.375f, 0.25f); glVertex3f( 0.2f,  0.0f, 0.16f);
			glTexCoord2f(0.375f, 0.00f); glVertex3f( 0.2f,  0.3f, 0.16f);
			// Back side
			glTexCoord2f(0.375f, 0.00f); glVertex3f( 0.2f,  0.3f,-0.16f);
			glTexCoord2f(0.375f, 0.25f); glVertex3f( 0.2f,  0.0f,-0.16f);
			glTexCoord2f(0.000f, 0.25f); glVertex3f(-0.2f,  0.0f, 0.00f);
			glTexCoord2f(0.000f, 0.00f); glVertex3f(-0.2f,  0.3f, 0.00f);
			// Outer/right side
			glTexCoord2f(0.000f, 0.250f); glVertex3f( 0.2f,  0.3f, 0.16f);
			glTexCoord2f(0.000f, 0.375f); glVertex3f( 0.2f,  0.0f, 0.16f);
			glTexCoord2f(0.125f, 0.375f); glVertex3f( 0.2f,  0.0f,-0.16f);
			glTexCoord2f(0.125f, 0.250f); glVertex3f( 0.2f,  0.3f,-0.16f);
		glEnd();
		glBegin(GL_TRIANGLES);
			// Top side
			glTexCoord2f(0.00f, 0.375f); glVertex3f(-0.2f,  0.3f, 0.00f);
			glTexCoord2f(0.25f, 0.500f); glVertex3f( 0.2f,  0.3f, 0.16f);
			glTexCoord2f(0.25f, 0.250f); glVertex3f( 0.2f,  0.3f,-0.16f);
		glEnd();
	glEndList();
}
