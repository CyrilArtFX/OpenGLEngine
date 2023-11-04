#version 330 core

struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	sampler2D emissive;
	float shininess;
};

struct Light
{
	vec3 position;
	vec3 direction;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float cutOff;
	float outerCutOff;
	
    float constant;
    float linear;
    float quadratic;
};

out vec4 FragColor;

in vec3 tFragPos;
in vec3 tNormal;
in vec2 tTexCoord;

uniform Material material;
uniform Light light;
uniform vec3 viewPos;

void main()
{
	//  ambient
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, tTexCoord));

	//  diffuse
	vec3 norm = normalize(tNormal);
	vec3 lightDir = normalize(light.position - tFragPos);
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, tTexCoord));

	//  specular
	vec3 viewDir = normalize(viewPos - tFragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
	vec3 specular = light.specular * spec * vec3(texture(material.specular, tTexCoord));

	//  emissive
	vec3 emissive = texture(material.emissive, tTexCoord).rgb;  
    
    //  spotlight (soft edges)
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = (light.cutOff - light.outerCutOff);
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    diffuse  *= intensity;
    specular *= intensity;
    
    //  attenuation
    float lightDist = length(light.position - tFragPos);
    float attenuation = 1.0 / (light.constant + light.linear * lightDist + light.quadratic * (lightDist * lightDist));    
    ambient *= attenuation; 
    diffuse *= attenuation;
    specular *= attenuation;   
        
	//  result
    vec3 result = ambient + diffuse + specular + emissive;
    FragColor = vec4(result, 1.0);
}