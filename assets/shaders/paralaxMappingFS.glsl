#version 410

out vec4 FragColor;

in vec3 vertexNormalOut;
in vec3 cameraDirectionOut;
in vec2 vertexTextureCoordsOut;
in mat3	tangentMatrix;


uniform vec4 ambientMaterialColour;
uniform vec4 diffuseMaterialColour;
uniform vec4 specularMaterialColour;
uniform float specularPower;

uniform float bias = 0.03f;
uniform float scale = 0.015f;

uniform sampler2D heightMap;

uniform sampler2D diffuseSampler;
uniform sampler2D specularSampler;
uniform sampler2D normalSampler;


struct DirectionalLight
{
	 vec4 ambientColour;
	 vec4 diffuseColour;
	 vec4 specularColour;
	 
	 vec3 direction;


};

uniform DirectionalLight directionLight;


void main()
{
	float height = texture(heightMap, vertexTextureCoordsOut).r;
	vec2 correctTexCoords = scale*vertexTextureCoordsOut*height;
	correctTexCoords = correctTexCoords - bias;
	
	vec3 bumpNormals = 2.0f * texture(normalSampler, correctTexCoords).rgb -1.0f;
	bumpNormals = normalize(bumpNormals);
	
	vec3 lightDir = normalize(-directionLight.direction);
	float diffuseTerm = dot(bumpNormals,lightDir);
	vec3 halfWayVec = normalize(cameraDirectionOut + lightDir);
	float specularTerm = pow(dot(bumpNormals, halfWayVec), specularPower);
	
	
	
	vec4 diffuseTextureColour = texture(diffuseSampler, correctTexCoords);
	vec4 specularTextureColour = texture(specularSampler, correctTexCoords);
	
	vec4 diffuseColour = diffuseTextureColour*directionLight.diffuseColour*diffuseTerm;
	vec4 specularColour = specularTextureColour*directionLight.specularColour*specularTerm;
	
	FragColor = (ambientMaterialColour*directionLight.ambientColour) + diffuseColour + specularColour;
}
