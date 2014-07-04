#include "Shader.h"

#include "Logger.h"
#include <fstream>

Shader::Shader() : vertexShader(0), pixelShader(0), program(0)
{}

Shader::Shader(Shader&& shader) :
	vertexShader(shader.vertexShader), pixelShader(shader.pixelShader),
	program(shader.program)
{
	shader.vertexShader = 0;
	shader.pixelShader = 0;
	shader.program = 0;
}

Shader::Shader(const std::string& vShaderPath, const std::string& pShaderPath)
{
	createShaders(vShaderPath, pShaderPath);	
	compileShaders(vShaderPath, pShaderPath);
	
	// check
	if (!glIsShader(this->vertexShader) || !glIsShader(this->pixelShader))
		logger::error("The shaders haven't been created", _FL_);
	
	createProgram(vShaderPath, pShaderPath);
	linkProgram(vShaderPath, pShaderPath);
	
	// check
	if (!glIsProgram(this->program))
		logger::error("The shader program has not been created", _FL_);
		
	
	logger::info("Shader created.", _FL_);
}

Shader::Shader(const std::string& name)
{}

void Shader::createShaders(const std::string& vShaderPath,
		const std::string& pShaderPath)
{
	// creation of the vertex and pixel shaders ID + verifications
	this->vertexShader = glCreateShader(GL_VERTEX_SHADER);
	if (!this->vertexShader || !glIsShader(this->vertexShader)) 
		logger::warn("Opengl was not able to create a vertex shader ID with : "
					  + vShaderPath, _FL_);

	this->pixelShader  = glCreateShader(GL_FRAGMENT_SHADER);
	if (!this->pixelShader || !glIsShader(this->pixelShader))
		logger::warn("Opengl was not able to create a pixel shader ID with : "
					  + pShaderPath, _FL_);


	// creation of the shaders
	char* src;
	src = loadFileASCII(vShaderPath);
	glShaderSource(this->vertexShader, 1, (const char**) &src, NULL);	
	free(src);
	
	src = loadFileASCII(pShaderPath);
	glShaderSource(this->pixelShader, 1, (const char**) &src, NULL);
	free(src);

}

char* Shader::loadFileASCII(const std::string& filePath)
{
	int length;
	std::ifstream file(filePath);
	
	if (!file)
		logger::error("Unable to load " + filePath, _FL_);
	
	// get file length
	file.seekg(0, std::ios::end);
	length = (int) file.tellg();
	if (length == -1)
		logger::error("Unable to load the file size " + filePath, _FL_);
	file.seekg(0, std::ios::beg);
	if (length == 0)
		logger::warn("The file seens to be empty. " + filePath, _FL_);
	
	// transmit chars from the file to the string
	char* str = (char*)  malloc((length + 1) * sizeof(char));
	if (str == NULL)
		logger::warn("Unable to load string from file " + filePath, _FL_);
	file.read(str, length);

	// adding \0 at the of the string
	str[length] = '\0';
	
	// clean up
	file.close();
	
	return str;
}

void Shader::compileShaders(const std::string& vShaderPath,
		const std::string& pShaderPath)
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
		vCompileLog = (char*) calloc(CompileLogSize + 1, sizeof(char));
		if (vCompileLog == NULL)
			logger::warn("Unable to allocate the compilation log\
						 message string for " + vShaderPath, _FL_);
		glGetShaderInfoLog(this->vertexShader, CompileLogSize,
						   &CompileLogSize, vCompileLog);
		logger::warn(std::string(vShaderPath + ": GLSL ") + vCompileLog, _FL_);
	}
	
	// compile pixel shader
	glCompileShader(this->pixelShader);

	// compilation check
	glGetShaderiv(this->pixelShader, GL_COMPILE_STATUS, &CompileStatus);
	if (CompileStatus != true) {
		glGetShaderiv(this->pixelShader,
					  GL_INFO_LOG_LENGTH,
					  &CompileLogSize);
		pCompileLog = (char*) calloc(CompileLogSize + 1, sizeof(char));
		if (pCompileLog == NULL)
			logger::warn("Unable to allocate the compilation log\
						 message string for " + pShaderPath, _FL_);
		glGetShaderInfoLog(this->pixelShader, CompileLogSize,
						   &CompileLogSize, pCompileLog);
		logger::warn(std::string(pShaderPath + ": GLSL ") + pCompileLog, _FL_);
	}
	
	// clean up
	if(vCompileLog != NULL)
		free(vCompileLog);
	if(pCompileLog != NULL)
		free(pCompileLog);
}

void Shader::createProgram(const std::string &vShaderPath,
		const std::string &pShaderPath)
{
	// create program Id
	this->program = glCreateProgram();
	
	// attach the shaders to the program
	glAttachShader(this->program, this->vertexShader);
	glAttachShader(this->program, this->pixelShader);
	
	// check program ID
	if (!this->program || !glIsProgram(this->program)) 
		logger::warn("Opengl was not able to create a program shader ID with : "
					  + vShaderPath + " and " + pShaderPath, _FL_);
}

void Shader::linkProgram(const std::string &vShaderPath,
		const std::string &pShaderPath)
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
		linkingLog = (char*) calloc(linkingLogSize + 1, sizeof(char));
		if (linkingLog == NULL)
			logger::warn("Unable to allocate the linking log\
						 message string for the program with " + vShaderPath
						 + " and " + pShaderPath, _FL_);
		glGetProgramInfoLog(this->program, linkingLogSize,
							&linkingLogSize, linkingLog);
		logger::error(std::string(vShaderPath + ": GLSL ") + linkingLog, _FL_);
	}
	
	//clean up
	if (linkingLog != NULL)
		free(linkingLog);
}

void Shader::use()
{
	glUseProgram(this->program);
}

GLuint Shader::getShaderId() const
{
	return this->program;
}

GLuint Shader::getvShaderId() const
{
	return this->vertexShader;
}

GLuint Shader::getpShaderId() const
{
	return this->pixelShader;
}

bool Shader::operator<(const Shader &b) const
{
	return (this->vertexShader + this->pixelShader) <
		(b.vertexShader + b.pixelShader);
}
