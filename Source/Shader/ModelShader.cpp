#include "Shader/ModelShader.h"

ModelShader::ModelShader()
{
	shader = "Model";
}

ModelShader::~ModelShader()
{
}

void ModelShader::loadProjectionMatrix(Matrix4f matrix)
{
	loadMatrix4f(projectionMatrix, matrix);
}

void ModelShader::loadTransformationMatrix(Matrix4f matrix)
{
	loadMatrix4f(transformationMatrix, matrix);
}

void ModelShader::loadCamera(Matrix4f matrix)
{
	loadMatrix4f(viewMatrix, matrix);
}

void ModelShader::loadAllUniformLocations()
{
	projectionMatrix = getUniformLocation("projectionMatrix");
	transformationMatrix = getUniformLocation("transformationMatrix");
	viewMatrix = getUniformLocation("viewMatrix");
	cameraPosition = getUniformLocation("cameraPosition");
	farPlane = getUniformLocation("farPlane");
	diffuseColor = getUniformLocation("diffuseColor");
}
void ModelShader::loadCamera(float x, float y, float z, float farPlane)
{
	loadVec3f(cameraPosition, x, y, z);
	loadFloat(this->farPlane, farPlane);
}

void ModelShader::loadDiffuseColor(float r, float g, float b, float a)
{
	loadVec4f(diffuseColor, r, g, b, a);
}
