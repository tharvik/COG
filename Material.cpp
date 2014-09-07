#include "Material.h"

#include <fstream>

#include "Logger.h"
#include "utilities.h"

using namespace std;

map<string, shared_ptr<Texture>> Material::texturesCont;

/**
 * Create a vs or a fs
 *
 * \param type GL_VERTEX_SHADER or GL_FRAGMENT_SHADER
 * \param sPath path to the shader file
 * 
 * \return the shader openGL ids
 */
GLuint createShaders(const GLenum type, const string& sPath);

/**
 * Compile a shader
 *
 * \param shader openGL id of the shader
 *
 * \return "" in case of success, the error string in case of failure
 */
string compileShader(const GLuint shader);

/**
 * Create a program and attach the given shaders
 *
 * \param vs vertex shader openGL id
 * \param fs vertex shader openGL id
 *
 * \return openGL id to the program
 */
GLuint createProgram(const GLuint vs, const GLuint fs);

/**
 * Link a program
 *
 * \param vs vertex shader openGL id
 * \param fs vertex shader openGL id
 *
 * \return true in case of success, false in case of failure
 */
string linkProgram(const GLuint program);

Material::Material(const string& mbfPath, const string& vsPath,
		   const string& fsPath)
: textures(), paramLoc(), samplerLoc(), program(0)
{
	loadShader(vsPath, fsPath);
	loadMaterial(mbfPath);
}

Material::Material(const Material&& material)
: textures(move(material.textures)), paramLoc(move(material.paramLoc)),
  samplerLoc(move(material.samplerLoc))
{}

Material::~Material()
{
	//!! still need to free textures
	glDeleteProgram(this->program);
}

void Material::loadShader(const string &vsPath, const string &fsPath)
{
	// create shaders
	GLuint vs = createShaders(GL_VERTEX_SHADER,   vsPath);
	GLuint fs = createShaders(GL_FRAGMENT_SHADER, fsPath);
	
	// compile shaders
	string log;
	log = compileShader(vs);
	if (log.size())
		logger_error("'" + vsPath + "' :\n" + log);
		
	log = compileShader(fs);
	if (log.size())
		logger_error("'" + fsPath + "' :\n" + log);

	// create program
	this->program = createProgram(vs, fs);
	
	log = linkProgram(this->program);
	if (log.size())
		logger_error("'" + vsPath + "' + '" + fsPath + "' : " + log);
	
	// check
	if (!glIsProgram(this->program))
	{
		logger_error("The OpenGL program ['" + vsPath + "' + '"
			      + fsPath + "'] has not been created");
	}
	
	
	logger_warn("OpenGL program created with ['" + vsPath + "' + '"
		    + fsPath + "']");
	getBasicUniformsLocation();
}

void Material::loadMaterial(const string& mtlPath)
{
	string localDir = mtlPath.substr(0, mtlPath.find_last_of("/") + 1);

	// open file
	ifstream file;
	file.open(mtlPath, std::ifstream::binary);
	if (!file.good())
	{
		logger_warn("Unable to open material binary file '" + mtlPath
			     + "'. The file may be empty or doesn't exist.");
		return;
	}
	
	// send parameters
	array<float, 11> param;
	file.read(reinterpret_cast<char*>(param.data()),
		  long(param.max_size() * sizeof(float)));
		  
	setUniformValue(param);

	// read textures
	string str;
	for (uint8_t i = 0; i < textures.size(); i++) {
		str = readString(file);
				
		if (str == "") {
			textures[i] = NULL;
		} else {
			string texturePath = localDir + str;
		
			// check if the texture already exists
			map<string, shared_ptr<Texture>>::iterator it;
			it = texturesCont.find(texturePath);
			
			// if doesn't exist create mesh
			if (it == texturesCont.end()) {
				textures[i] =
					shared_ptr<Texture>(
						new Texture(texturePath));
				texturesCont[texturePath] = textures[i];
			} else
				textures[i] = texturesCont[texturePath];
		}
	}
	
	// send texturesList to openGL program
	glUseProgram(this->program);
	
	array<GLint, 6> texturesList;
	array<string, 6> uniformsNames = {{"map_Ka", "map_Kd", "map_Ks",
					   "map_Ns", "map_d", "map_bump"}};
	
	for (uint8_t i = 0; i < textures.size(); i++) {
		if (textures[i]) {
			texturesList[i] = true;
			glUniform1i(glGetUniformLocation(this->program,
						      uniformsNames[i].c_str()),
						      i);
		} else {
			texturesList[i] = false;
		}
	}
		
	glUniform1iv(glGetUniformLocation(this->program, "activeTextures"), 6, texturesList.data());
	
	// end
	file.close();
}

void Material::getBasicUniformsLocation()
{
	array<string, 5> paramNames = {{"Ka", "Kd", "Ks", "Ns", "d"}};
	array<string, 6> samplerNames = {{"map_Ka", "map_Kd", "map_Ks", 
					  "map_Ns", "map_d", "map_bump"}};

	for (uint8_t i = 0; i < paramLoc.size(); i++) {
		paramLoc[i] = glGetUniformLocation(this->program,
						   paramNames[i].c_str());
	}
	
	for (uint8_t i = 0; i < samplerLoc.size(); i++) {
		samplerLoc[i] = glGetUniformLocation(this->program,
						     samplerNames[i].c_str());
	}
}

void Material::setUniformValue(array<float, 11> values) const
{
	glUseProgram(this->program);
	glUniform3f(this->paramLoc[0], values[0], values[1], values[2]);
	glUniform3f(this->paramLoc[1], values[3], values[4], values[5]);
	glUniform3f(this->paramLoc[2], values[6], values[7], values[8]);
	glUniform1f(this->paramLoc[3], values[9]);
	glUniform1f(this->paramLoc[4], values[10]);
}

void Material::use() const
{
	// use openGL program
	glUseProgram(this->program);
	
	// bind textures
	for (uint8_t i = 0; i < textures.size(); i++) {
		if (textures[i]) {
			glActiveTexture(GL_TEXTURE0 + i);
			this->textures[i]->bindTexture();
		}
	}
}

void Material::print() const
{
	cout << "\tKa = ("
	     << this->paramLoc[Material::Ka+0]
	     << this->paramLoc[Material::Ka+1]
	     << this->paramLoc[Material::Ka+2]
	     << ")" << endl
	     << "\tKd = ("
	     << this->paramLoc[Material::Kd+0]
	     << this->paramLoc[Material::Kd+1]
	     << this->paramLoc[Material::Kd+2]
	     << ")" << endl
	     << "\tKs = ("
	     << this->paramLoc[Material::Ks+0]
	     << this->paramLoc[Material::Ks+1]
	     << this->paramLoc[Material::Ks+2]
	     << ")" << endl
	     << "\tNs = " << this->paramLoc[Material::Ns+0] << endl
	     << "\td = "  << this->paramLoc[Material::d+0]  << endl;
}

GLuint createShaders(const GLenum type, const string& sPath)
{
	// create shader + check
	GLuint shader = glCreateShader(type);
	if (!shader || !glIsShader(shader)) 
		logger_warn("Opengl was not able to create a vertex "
			     "shader for '" + sPath + "'");

	// load file
	char* src = loadFileASCII(sPath);
	if (src == NULL) {
		logger_error("Unable to load shader source in '" + sPath + "'");
		return 0;
	}
	glShaderSource(shader, 1, const_cast<const GLchar**>(&src), nullptr);
	free(src);
	
	return shader;
}

string compileShader(const GLuint shader)
{
	GLint compileStatus = true;
	GLint compileLogSize;
	char* compileLog = nullptr;
	
	// compile vertex shader
	glCompileShader(shader);
	
	// compilation check
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);

	if (compileStatus != true) {
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &compileLogSize);
		compileLog = reinterpret_cast<char*>(
				calloc(size_t(compileLogSize + 1),
				sizeof(char)));
		if (compileLog == nullptr) {
			logger_warn("Unable to allocate the compilation log");
			return "*Unable to allocate log*";
		}
		glGetShaderInfoLog(shader, compileLogSize,
				   &compileLogSize, compileLog);
		string log(compileLog);
		if(compileLog != nullptr)
			free(compileLog);

		return log;
	}
		
	// clean up
	if(compileLog != nullptr)
		free(compileLog);

	return "";
}

GLuint createProgram(const GLuint vs, const GLuint fs)
{
	// create program Id
	GLuint program = glCreateProgram();
	
	// attach the shaders to the program
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	
	return program;
}

string linkProgram(const GLuint program)
{
	GLint linkingStatus = true;
	GLint linkingLogSize;
	char* linkingLog = nullptr;

	// link program
	glLinkProgram(program);
	
	// linking check
	glGetProgramiv(program, GL_LINK_STATUS, &linkingStatus);
	if (linkingStatus != true) {
		glGetProgramiv(program,
			       GL_INFO_LOG_LENGTH,
			       &linkingLogSize);
		linkingLog = reinterpret_cast<char*>(malloc(
						size_t(linkingLogSize + 1)
						* sizeof(char)));
		if (linkingLog == nullptr) {
			logger_warn("Unable to allocate the linking log\
				     message string for the program with");
			return "Linking error.";
		}
		
		glGetProgramInfoLog(program, linkingLogSize,
				    &linkingLogSize, linkingLog);
		string log(linkingLog);
		free(linkingLog);
		return log;
	}
	
	//clean up
	if (linkingLog != nullptr)
		free(linkingLog);
		
	return "";
}
