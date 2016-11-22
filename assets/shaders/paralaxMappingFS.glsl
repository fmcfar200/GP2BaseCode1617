#version 410

out vec4 FragColor;

in vec3 vertexNormalOut;
in vec3 cameraDirectionOut;
in vec2 vertexTextureCoordsOut;
in mat3	tangentMatrix;


uniform vec4 ambientMaterialColour=vec4(0.5f,0.0f,0.0f,1.0f);
uniform vec4 diffuseMaterialColour=vec4(0.8f,0.0f,0.0f,1.0f);
uniform vec4 specularMaterialColour=vec4(1.0f,1.0f,1.0f,1.0f);
uniform float specularPower=25.0f;

uniform float bias = 0.03f;
uniform float scale = 0.015f;

uniform sampler2D heightMap;

uniform sampler2D diffuseSampler;
uniform sampler2D specularSampler;
uniform sampler2D normalSampler;


struct DirectionalLight
{
	 vec4 ambientColour=vec4(1.0f,1.0f,1.0f,1.0f);
	 vec4 diffuseColour=vec4(1.0f,1.0f,1.0f,1.0f);
	 vec4 specularColour=vec4(1.0f,1.0f,1.0f,1.0f);
	 
	 vec3 direction=vec3(0.0f,0.0f,1.0f);


}

uniform DirectionalLight directionLight;


void main()
{
	float height = texture(heightMap, vertexTextureCoordsOut).r;
	vec2 correctTexCoords = scale*vertexTextureCoordsOut*height;
	correctTexCoords = correctTexCoords - bias;
	
	vec3 bumpNormals = 2.0f * texture(normalSampler, correctTexCoords).rgb -1.0f;
	bumpNormals = normalize(bumpNormals);
	
	directionLight.direction=normalize(-directionLight.direction);
	float diffuseTerm = dot(bumpNormals, directionLight.direction);
	vec3 halfWayVec = normalize(cameraDirectionOut + directionLight.direction);
	float specularTerm = pow(dot(bumpNormals, halfWayVec), specularPower);
	
	
	
	vec4 diffuseTextureColour = texture(diffuseSampler, correctTexCoords);
	vec4 specularTextureColour = texture(specularSampler, correctTexCoords);
	
	vec4 diffuseColour = diffuseTextureColour*directionLight.diffuseColour*diffuseTerm;
	vec4 specularColour = specularTextureColour*directionLight.specularColour*specularTerm;
	
	FragColor = (ambientMaterialColour*directionLight.ambientColour) + diffuseColour + specularColour;
}
