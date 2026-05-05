#version 330 core

uniform vec3 ambientColor;
uniform vec3 lightPos;
uniform vec3 lightColor;

uniform vec3 viewPos;
float specularStrength = 0.5;

in vec3 ndc;
in vec3 fragNormal;

vec3 norm = normalize(fragNormal);
vec3 lightDir = normalize(lightPos - ndc);

void main(){

  vec3 viewDir = normalize(viewPos - ndc);
  vec3 reflectLight = reflect(-lightDir, fragNormal);

  float spec = pow(max(dot(viewDir, reflectLight), 0.0), 64);
  
  vec3 specular = lightColor * spec * specularStrength;
  vec3 diffuse = max(dot(lightDir, fragNormal), 0.1) * lightColor;

  vec3 result = (diffuse + specular) * ambientColor;

  gl_FragColor = vec4(result, 1.0);
}
