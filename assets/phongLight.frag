#version 330 core

uniform vec3 ambientColor;
uniform vec3 lightPos;
uniform vec3 lightColor;

in vec3 ndc;
in vec3 fragNormal;

vec3 norm = normalize(fragNormal);
vec3 lightDir = normalize(lightPos - ndc);

void main(){
  float lightAmount = max(dot(lightDir, fragNormal), 0.0);
  vec3 result =  ambientColor * lightAmount;

  gl_FragColor = vec4(result, 1.0);
}
