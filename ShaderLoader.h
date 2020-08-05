#include <string>
#include <X11/Xlib.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>
#include <GL/glcorearb.h>
#include <iostream>
#include <fstream>

int initShader(const char* vShaderFile, const char* fShaderFile);

void vertexShaderDebug(int compiled, int program, int fShaderProgram);
void fragementShaderDebug(int compiled, int program, int fShaderProgram);
void linkShaderDebug(int compiled, int program, int vShaderProgram);

std::string readInFile(const char* name);

int initShader(const char* vShaderFile, const char* fShaderFile){
	int program = glCreateProgram();
	std::string vertexS=readInFile(vShaderFile);
	std::string fragmentS=readInFile(fShaderFile);
	int vShaderProgram= glCreateShader(GL_VERTEX_SHADER);
	int fShaderProgram= glCreateShader(GL_FRAGMENT_SHADER);

	// Put code into program
	const char* temp1=vertexS.c_str();
	const char* temp2=fragmentS.c_str();
	glShaderSource(vShaderProgram,1,(const GLchar**)(&temp1), NULL);
	glShaderSource(fShaderProgram,1,(const GLchar**)(&temp2), NULL);

	// Compile code
	glCompileShader(vShaderProgram);
	glCompileShader(fShaderProgram);

	//* check for errors in compile
	int compiled;
	glGetShaderiv(vShaderProgram,GL_COMPILE_STATUS,&compiled);
	// Vertex shader is bad
	vertexShaderDebug(compiled, program, vShaderProgram);

	glGetShaderiv(fShaderProgram,GL_COMPILE_STATUS,&compiled);
	fragementShaderDebug(compiled, program, fShaderProgram);

	glAttachShader(program,vShaderProgram);
	glAttachShader(program,fShaderProgram);
	glLinkProgram(program);
	// Shaders will be deleted with program;
	glDeleteShader(vShaderProgram);
	glDeleteShader(fShaderProgram);

	glGetProgramiv( program, GL_LINK_STATUS, &compiled);

	linkShaderDebug(compiled, program, vShaderProgram);

	return program;
}


int initShader(std::string vShader, std::string fShader) {
	int program = glCreateProgram();
	int vShaderProgram= glCreateShader(GL_VERTEX_SHADER);
	int fShaderProgram= glCreateShader(GL_FRAGMENT_SHADER);

	// Put code into program
	const char* temp1=vShader.c_str();
	const char* temp2=fShader.c_str();
	glShaderSource(vShaderProgram,1,(const GLchar**)(&temp1), NULL);
	glShaderSource(fShaderProgram,1,(const GLchar**)(&temp2), NULL);

	// Compile code
	glCompileShader(vShaderProgram);
	glCompileShader(fShaderProgram);

	//* check for errors in compile
	int compiled;
	glGetShaderiv(vShaderProgram,GL_COMPILE_STATUS,&compiled);

	vertexShaderDebug(compiled, program, vShaderProgram);

	glGetShaderiv(fShaderProgram,GL_COMPILE_STATUS,&compiled);
	fragementShaderDebug(compiled, program, fShaderProgram);

	glAttachShader(program,vShaderProgram);
	glAttachShader(program,fShaderProgram);
	glLinkProgram(program);
	glGetProgramiv( program, GL_LINK_STATUS, &compiled);
	linkShaderDebug(compiled, program, vShaderProgram);

	return program;
}

int initShader(int vShaderProgram, std::string fShader){
	int program = glCreateProgram();
	int fShaderProgram= glCreateShader(GL_FRAGMENT_SHADER);

	// Put code into program
	const char* temp2=fShader.c_str();
	glShaderSource(fShaderProgram, 1, (const GLchar**)(&temp2), NULL);

	// Compile code
	glCompileShader(fShaderProgram);

	//* check for errors in compile
	int compiled;
	glGetShaderiv(vShaderProgram, GL_COMPILE_STATUS,&compiled);
	vertexShaderDebug(compiled, program, vShaderProgram);

	glGetShaderiv(fShaderProgram,GL_COMPILE_STATUS,&compiled);
	fragementShaderDebug(compiled, program, fShaderProgram);

	glAttachShader(program, vShaderProgram);
	glAttachShader(program, fShaderProgram);

	glLinkProgram(program);
	glGetProgramiv( program, GL_LINK_STATUS, &compiled);

	//*/
	return program;
}

int initVertexShader(const char* vShaderFile) {
	std::string vertexS=readInFile(vShaderFile);
	int vShaderProgram= glCreateShader(GL_VERTEX_SHADER);
	const char* temp1=vertexS.c_str();

	glShaderSource(vShaderProgram,1,(const GLchar**)(&temp1), NULL);
	glCompileShader(vShaderProgram);

	int compiled;
	glGetShaderiv(vShaderProgram, GL_COMPILE_STATUS, &compiled);

	return vShaderProgram;
}

// PRIVATE: **Need to read more into C++ conventions on this.

void vertexShaderDebug(int compiled, int program, int vShaderProgram) {
	#ifdef DEBUG
		if (compiled == GL_FALSE){
			std::cerr << "Vertex shader failed to compile\n";
			int logSize;
			glGetShaderiv(vShaderProgram,GL_INFO_LOG_LENGTH,&logSize);
			char* logMsg= new char[logSize];
			glGetShaderInfoLog(vShaderProgram,logSize,NULL, logMsg);
			std::cerr << logMsg;
			delete[] logMsg;
			exit(1);
		}
	#endif
}

void fragementShaderDebug(int compiled, int program, int fShaderProgram) {
	#ifdef DEBUG
		if (compiled == GL_FALSE){ // Fragment shader is bad
			std::cout << "Fragment shader failed to compile\n";
			int logSize;
			glGetShaderiv(fShaderProgram, GL_INFO_LOG_LENGTH, &logSize);
			char* logMsg= new char[logSize];
			glGetShaderInfoLog(fShaderProgram, logSize, NULL, logMsg);
			std::cerr << logMsg;
			delete[] logMsg;
			exit(1);
		}
	#endif
}

void linkShaderDebug(int compiled, int program, int vShaderProgram) {
	#ifdef DEBUG
		if(compiled == GL_FALSE) { // program failed to link vertex shader
			char* logProgram= new char[1024];
			glGetProgramInfoLog(program, 1024, NULL, logProgram);
			std::cerr << "Somethings messed up with the program!\n";
			std::cerr <<logProgram << "\n";
			std::cerr << "What we think the shader source file looks like \n";
			glGetShaderSource(vShaderProgram, 1024, NULL, logProgram);
			std::cerr << logProgram;
			delete[] logProgram;
			exit(1);
		}
	#endif
}


std::string readInFile(const char* name){
	std::ifstream file;
	std::string code="";
	file.open(name);
	while(file){
		std::string temp;
		getline(file,temp);
		code= code +temp+'\n';
	}
	code=code+'\0';
	return code;
}
