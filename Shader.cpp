#include "Shader.h"

#include "Logger.h"
#include <fstream>
#include <string>

using namespace std;

Shader::Shader() : vertexShader(0), fragmentShader(0), program(0), parameters()
{}

Shader::Shader(const Shader& shader) :
vertexShader(shader.vertexShader),
fragmentShader(shader.fragmentShader),
program(shader.program), parameters()
{
	cout << "### copy ###" << endl;
}

Shader::Shader(Shader&& shader) :
vertexShader(shader.vertexShader),
fragmentShader(shader.fragmentShader),
program(shader.program), parameters()
{
	cout << "### move ###" << endl;
}

Shader::Shader(const string& vsPath, const string& fsPath) :
	vertexShader(0), fragmentShader(0), program(0), parameters()
{

	createShaders(vsPath,  fsPath);	
	compileShaders(vsPath, fsPath);
	
	// check
	if (!glIsShader(this->vertexShader))
	{
		logger_error("The shader '" + vsPath
			      + "' haven't been created");
		return;
	}
	if (!glIsShader(this->fragmentShader))
	{
		logger_error("The shader '" + fsPath
			      + "' haven't been created");
		return;
	}

	
	createProgram(vsPath, fsPath);
	linkProgram(vsPath,   fsPath);
	
	// check
	if (!glIsProgram(this->program))
	{
		logger_error("The OpenGL program ['" + vsPath + "' + '"
			      + fsPath + "'] has not been created");
		return;
	}
	
	
	logger_info("OpenGL program created ['" + vsPath + "' + '" + fsPath
		     + "']");
	
	getBasicUniformsLocation();
}

void Shader::createShaders(const string& vsPath, const string& fsPath)
{
	// creation of the vertex and fragment shaders ID + verifications
	this->vertexShader = glCreateShader(GL_VERTEX_SHADER);
	if (!this->vertexShader || !glIsShader(this->vertexShader)) 
		logger_warn("Opengl was not able to create a vertex "
			     "shader ID with '" + vsPath + "'");

	this->fragmentShader  = glCreateShader(GL_FRAGMENT_SHADER);
	if (!this->fragmentShader || !glIsShader(this->fragmentShader))
		logger_warn("Opengl was not able to create a fragment "
			     "shader ID with '" + fsPath + "'");


	// load files
	char* src = loadFileASCII(vsPath);
	glShaderSource(this->vertexShader, 1, const_cast<const GLchar**>(&src), nullptr);
	free(src);
	
	src = loadFileASCII(fsPath);
	glShaderSource(this->fragmentShader, 1, const_cast<const GLchar**>(&src), nullptr);
	free(src);

}

char* Shader::loadFileASCII(const string& filePath)
{
	unsigned long length;
	ifstream file(filePath, ios::ate);
	
	if (!file.good())
		logger_error("Unable to open shader file '" + filePath + "'."
			      "The file may be empty or simply does not exist");
	
	// get file length
	length = (unsigned long) file.tellg();
	
	file.seekg(0, ios::beg);
	
	// transmit chars from the file to the string
	char* str = reinterpret_cast<char*>(malloc((length + 1) * sizeof(char)));
	if (str == nullptr)
		logger_warn("Unable to load string from file " + filePath);
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
	char* vCompileLog = nullptr;
	char* pCompileLog = nullptr;
	
	// compile vertex shader
	glCompileShader(this->vertexShader);
	
	// compilation check
	glGetShaderiv(this->vertexShader, GL_COMPILE_STATUS, &CompileStatus);

	if (CompileStatus != true) {
		glGetShaderiv(this->vertexShader,
					  GL_INFO_LOG_LENGTH,
					  &CompileLogSize);
		vCompileLog = reinterpret_cast<char*>(calloc(size_t(CompileLogSize + 1),
					     sizeof(char)));
		if (vCompileLog == nullptr)
			logger_warn("Unable to allocate the compilation log\
				     message string for " + vsPath);
		glGetShaderInfoLog(this->vertexShader, CompileLogSize,
				   &CompileLogSize, vCompileLog);
		logger_warn(string(vsPath + ": GLSL ") + vCompileLog);
	}
	
	// compile fragment shader
	glCompileShader(this->fragmentShader);

	// compilation check
	glGetShaderiv(this->fragmentShader, GL_COMPILE_STATUS, &CompileStatus);
	if (CompileStatus != true) {
		glGetShaderiv(this->fragmentShader,
					  GL_INFO_LOG_LENGTH,
					  &CompileLogSize);
		pCompileLog = reinterpret_cast<char*>(calloc(size_t(CompileLogSize + 1),
					     sizeof(char)));
		if (pCompileLog == nullptr)
			logger_warn("Unable to allocate the compilation log\
				     message string for " + fsPath);
		glGetShaderInfoLog(this->fragmentShader, CompileLogSize,
				   &CompileLogSize, pCompileLog);
		logger_warn(string(fsPath + ": GLSL ") + pCompileLog);
	}
	
	// clean up
	if(vCompileLog != nullptr)
		free(vCompileLog);
	if(pCompileLog != nullptr)
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
		logger_warn("Opengl was not able to create a program "
			     "shader ID with : "
			     + vsPath + " and " + fsPath);
}

void Shader::linkProgram(const string &vsPath, const string &fsPath)
{
	GLint linkingStatus = true;
	GLint linkingLogSize;
	char* linkingLog = nullptr;


	// link program
	glLinkProgram(this->program);
	
	// linking check
	glGetProgramiv(this->program, GL_LINK_STATUS, &linkingStatus);
	if (linkingStatus != true) {
		glGetProgramiv(this->program,
					  GL_INFO_LOG_LENGTH,
					  &linkingLogSize);
		linkingLog = reinterpret_cast<char*>(calloc(size_t(linkingLogSize + 1),
					    sizeof(char)));
		if (linkingLog == nullptr)
			logger_warn("Unable to allocate the linking log\
				     message string for the program with "
				     + vsPath + " and " + fsPath);
		glGetProgramInfoLog(this->program, linkingLogSize,
				    &linkingLogSize, linkingLog);
		logger_error(string(vsPath + ": GLSL ") + linkingLog);
	}
	
	//clean up
	if (linkingLog != nullptr)
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
