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
	vec3 bumpNormals = 2.0f * texture(normalSampler, vertexTextureCoordsOut).rgb -1.0f;
	bumpNormals = normalize(bumpNormals);
	
	vec3 lightDir = normalize(-directionLight.direction);
	float diffuseTerm = dot(bumpNormals, lightDir);
	vec3 halfWayVec = normalize(cameraDirectionOut + lightDir);
	float specularTerm = pow(dot(bumpNormals, halfWayVec), specularPower);
	
	
	
	vec4 diffuseTextureColour = texture(diffuseSampler, vertexTextureCoordsOut);
	vec4 specularTextureColour = texture(specularSampler, vertexTextureCoordsOut);
	
	vec4 diffuseColour = diffuseTextureColour*directionLight.diffuseColour*diffuseTerm;
	vec4 specularColour = specularTextureColour*directionLight.specularColour*specularTerm;
	
	FragColor = (ambientMaterialColour*directionLight.ambientColour) + diffuseColour + specularColour;
}
