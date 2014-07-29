#include "Shader.h"

#include "Logger.h"
#include <fstream>
#include <string>

using namespace std;

Shader::Shader() : vertexShader(0), fragmentShader(0), program(0)
{}

Shader::Shader(const Shader& shader) :
vertexShader(shader.vertexShader),
fragmentShader(shader.fragmentShader),
program(shader.program)
{
	cout << "### copy ###" << endl;
}

Shader::Shader(Shader&& shader) :
vertexShader(shader.vertexShader),
fragmentShader(shader.fragmentShader),
program(shader.program)
{
	cout << "### move ###" << endl;
}

Shader::Shader(const string& vsPath, const string& fsPath)
{

	createShaders(vsPath,  fsPath);	
	compileShaders(vsPath, fsPath);
	
	// check
	if (!glIsShader(this->vertexShader))
	{
		logger::error("The shader '" + vsPath
			      + "' haven't been created", _FL_);
		return;
	}
	if (!glIsShader(this->fragmentShader))
	{
		logger::error("The shader '" + fsPath
			      + "' haven't been created", _FL_);
		return;
	}

	
	createProgram(vsPath, fsPath);
	linkProgram(vsPath,   fsPath);
	
	// check
	if (!glIsProgram(this->program))
	{
		logger::error("The OpenGL program ['" + vsPath + "' + '"
			      + fsPath + "'] has not been created", _FL_);
		return;
	}
	
	
	logger::info("OpenGL program created ['" + vsPath + "' + '" + fsPath
		     + "']", _FL_);
	
	getBasicUniformsLocation();
}

void Shader::createShaders(const string& vsPath, const string& fsPath)
{
	// creation of the vertex and fragment shaders ID + verifications
	this->vertexShader = glCreateShader(GL_VERTEX_SHADER);
	if (!this->vertexShader || !glIsShader(this->vertexShader)) 
		logger::warn("Opengl was not able to create a vertex "
			     "shader ID with '" + vsPath + "'", _FL_);

	this->fragmentShader  = glCreateShader(GL_FRAGMENT_SHADER);
	if (!this->fragmentShader || !glIsShader(this->fragmentShader))
		logger::warn("Opengl was not able to create a fragment "
			     "shader ID with '" + fsPath + "'", _FL_);


	// load files
	char* src;
	src = loadFileASCII(vsPath);
	glShaderSource(this->vertexShader, 1, (const char**) &src, NULL);	
	free(src);
	
	src = loadFileASCII(fsPath);
	glShaderSource(this->fragmentShader, 1, (const char**) &src, NULL);
	free(src);

}

char* Shader::loadFileASCII(const string& filePath)
{
	unsigned long length;
	ifstream file(filePath, ios::ate);
	
	if (!file.good())
		logger::error("Unable to open shader file '" + filePath + "'."
			      "The file may be empty or simply does not exist",
			      _FL_);
	
	// get file length
	length = (unsigned long) file.tellg();
	
	file.seekg(0, ios::beg);
	
	// transmit chars from the file to the string
	char* str = (char*)  malloc((length + 1) * sizeof(char));
	if (str == NULL)
		logger::warn("Unable to load string from file " + filePath,
			     _FL_);
	file.read(str, (long) length);

	// adding \0 at the of the string
	str[length] = '\0';
	
	// clean up
	file.close();
		
	return str;
}

void Shader::compileShaders(const string& vsPath, const string& fsPath)
{
	GLint CompileStatus = true;
	GLint CompileLogSize;
	char* vCompileLog = NULL;
	char* pCompileLog = NULL;
	
	// compile vertex shader
	glCompileShader(this->vertexShader);
	
	// compilation check
	glGetShaderiv(this->vertexShader, GL_COMPILE_STATUS, &CompileStatus);

	if (CompileStatus != true) {
		glGetShaderiv(this->vertexShader,
					  GL_INFO_LOG_LENGTH,
					  &CompileLogSize);
		vCompileLog = (char*) calloc((size_t) CompileLogSize + 1,
					     sizeof(char));
		if (vCompileLog == NULL)
			logger::warn("Unable to allocate the compilation log\
				     message string for " + vsPath, _FL_);
		glGetShaderInfoLog(this->vertexShader, CompileLogSize,
				   &CompileLogSize, vCompileLog);
		logger::warn(string(vsPath + ": GLSL ") + vCompileLog, _FL_);
	}
	
	// compile fragment shader
	glCompileShader(this->fragmentShader);

	// compilation check
	glGetShaderiv(this->fragmentShader, GL_COMPILE_STATUS, &CompileStatus);
	if (CompileStatus != true) {
		glGetShaderiv(this->fragmentShader,
					  GL_INFO_LOG_LENGTH,
					  &CompileLogSize);
		pCompileLog = (char*) calloc((size_t) CompileLogSize + 1,
					     sizeof(char));
		if (pCompileLog == NULL)
			logger::warn("Unable to allocate the compilation log\
				     message string for " + fsPath, _FL_);
		glGetShaderInfoLog(this->fragmentShader, CompileLogSize,
				   &CompileLogSize, pCompileLog);
		logger::warn(string(fsPath + ": GLSL ") + pCompileLog, _FL_);
	}
	
	// clean up
	if(vCompileLog != NULL)
		free(vCompileLog);
	if(pCompileLog != NULL)
		free(pCompileLog);
}

void Shader::createProgram(const string &vsPath, const string &fsPath)
{
	// create program Id
	this->program = glCreateProgram();
	
	// attach the shaders to the program
	glAttachShader(this->program, this->vertexShader);
	glAttachShader(this->program, this->fragmentShader);
	
	// check program ID
	if (!this->program || !glIsProgram(this->program)) 
		logger::warn("Opengl was not able to create a program "
			     "shader ID with : "
			     + vsPath + " and " + fsPath, _FL_);
}

void Shader::linkProgram(const string &vsPath, const string &fsPath)
{
	GLint linkingStatus = true;
	GLint linkingLogSize;
	char* linkingLog = NULL;


	// link program
	glLinkProgram(this->program);
	
	// linking check
	glGetProgramiv(this->program, GL_LINK_STATUS, &linkingStatus);
	if (linkingStatus != true) {
		glGetProgramiv(this->program,
					  GL_INFO_LOG_LENGTH,
					  &linkingLogSize);
		linkingLog = (char*) calloc((size_t) linkingLogSize + 1,
					    sizeof(char));
		if (linkingLog == NULL)
			logger::warn("Unable to allocate the linking log\
				     message string for the program with "
				     + vsPath + " and " + fsPath, _FL_);
		glGetProgramInfoLog(this->program, linkingLogSize,
				    &linkingLogSize, linkingLog);
		logger::error(string(vsPath + ": GLSL ") + linkingLog, _FL_);
	}
	
	//clean up
	if (linkingLog != NULL)
		free(linkingLog);
}

void Shader::getBasicUniformsLocation()
{
	array<string, 5> names = {{"Ka", "Kd", "Ks", "Ns", "d"}};

	for (unsigned char i = 0; i < 5; i++) {
		parameters[i] = glGetUniformLocation(this->program,
							 names[i].c_str());
	}
}

void Shader::use() const
{
	glUseProgram(this->program);
}

bool Shader::operator<(const Shader &b) const
{
	return ((this->vertexShader << sizeof(GLint) / 2) + this->fragmentShader) <
	((b.vertexShader << sizeof(GLint) / 2) + b.fragmentShader);
}

void Shader::setUniformValue(Shader::uniforms uniform, float value)
{
	glUniform1f(this->parameters[uniform-6], value);
}

void Shader::setUniformValue(Shader::uniforms uniform,
		     float v1, float v2, float v3)
{
	glUniform3f(this->parameters[uniform/3], v1, v2, v3);
}

void Shader::setUniformValue(std::array<float, 11> values)
{
	glUseProgram(this->program);
	glUniform3f(this->parameters[0], values[0], values[1], values[2]);
	glUniform3f(this->parameters[1], values[3], values[4], values[5]);
	glUniform3f(this->parameters[2], values[6], values[7], values[8]);
	glUniform1f(this->parameters[3], values[9]);
	glUniform1f(this->parameters[4], values[10]);
}
