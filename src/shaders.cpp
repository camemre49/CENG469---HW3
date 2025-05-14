#include "../headers/shaders.h"

#include <fstream>
#include <iostream>
#include <string>

#include "../headers/base.h"
#include "../headers/particle.h"
using namespace std;

GLuint particleProgram, computeProgram;

bool ReadDataFromFile(
	const string& fileName, ///< [in]  Name of the shader file
	string& data)     ///< [out] The contents of the file
{
	fstream myfile;

	// Open the input
	myfile.open(fileName.c_str(), std::ios::in);

	if (myfile.is_open())
	{
		string curLine;

		while (getline(myfile, curLine))
		{
			data += curLine;
			if (!myfile.eof())
			{
				data += "\n";
			}
		}

		myfile.close();
	}
	else
	{
		return false;
	}

	return true;
}

GLuint createVS(const char* shaderName)
{
	const string vsFolderName = "vs";
    string shaderSource;

    string filename(vsFolderName + "/" +shaderName);
    if (!ReadDataFromFile(filename, shaderSource))
    {
        cout << "Cannot find file name: " + filename << endl;
        exit(-1);
    }

    GLint length = shaderSource.length();
    const GLchar* shader = (const GLchar*)shaderSource.c_str();

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &shader, &length);
    glCompileShader(vs);

    char output[1024] = { 0 };
    glGetShaderInfoLog(vs, 1024, &length, output);
    printf("VS compile log: %s\n", output);

    return vs;
}

GLuint createFS(const char* shaderName)
{
	const string vsFolderName = "fs";
	string shaderSource;

	string filename(vsFolderName + "/" +shaderName);
    if (!ReadDataFromFile(filename, shaderSource))
    {
        cout << "Cannot find file name: " + filename << endl;
        exit(-1);
    }

    GLint length = shaderSource.length();
    const GLchar* shader = (const GLchar*)shaderSource.c_str();

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &shader, &length);
    glCompileShader(fs);

    char output[1024] = { 0 };
    glGetShaderInfoLog(fs, 1024, &length, output);
    printf("FS compile log: %s\n", output);

    return fs;
}

GLuint createCS(const char* shaderName)
{
	const string csFolderName = "cs";
	string shaderSource;

	string filename(csFolderName + "/" +shaderName);
	if (!ReadDataFromFile(filename, shaderSource))
	{
		cout << "Cannot find file name: " + filename << endl;
		exit(-1);
	}

	GLint length = shaderSource.length();
	const GLchar* shader = (const GLchar*)shaderSource.c_str();

	GLuint cs = glCreateShader(GL_COMPUTE_SHADER);
	glShaderSource(cs, 1, &shader, &length);
	glCompileShader(cs);

	char output[1024] = { 0 };
	glGetShaderInfoLog(cs, 1024, &length, output);
	printf("CS compile log: %s\n", output);

	return cs;
}

void initShaders()
{
	// Create programs
	particleProgram = glCreateProgram();
	computeProgram = glCreateProgram();

	// Load shaders
	GLuint vs = createVS("vert.glsl");      // Vertex Shader
	GLuint fs = createFS("frag.glsl");      // Fragment Shader
	GLuint cs = createCS("particle.glsl");   // Compute Shader

	// Attach vertex and fragment shaders to the particle program
	glAttachShader(particleProgram, vs);
	glAttachShader(particleProgram, fs);

	// Attach compute shader to its own program
	glAttachShader(computeProgram, cs);

	// Link particle program (for rendering)
	glLinkProgram(particleProgram);
	GLint status;
	glGetProgramiv(particleProgram, GL_LINK_STATUS, &status);
	if (status != GL_TRUE)
	{
		cout << "Particle Program link failed" << endl;
		exit(-1);
	}

	// Link compute shader program
	glLinkProgram(computeProgram);
	glGetProgramiv(computeProgram, GL_LINK_STATUS, &status);
	if (status != GL_TRUE)
	{
		cout << "Compute Program link failed" << endl;
		exit(-1);
	}


	glUseProgram(computeProgram);
	glm::vec3 attractorPoints[] = {
		{  0.4f,  0.4f,  400.0f },  // top right
		{ -0.4f,  0.4f,  400.0f },  // top left
		{ 0.0f, -0.4f,  800.0f },  // bottom middle
		{  -0.0f, -0.4f,  800.0f },  // bottom middle
	};
	glUniform3fv(glGetUniformLocation(computeProgram, "attractors"), currentNumOfAttractors, glm::value_ptr(attractorPoints[0]));
}
