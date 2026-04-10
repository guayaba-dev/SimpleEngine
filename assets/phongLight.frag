#version 330 core

uniform vec3 ambientColor;
uniform vec3 lightPos;
uniform vec3 lightColor;

in vec3 ndc;
in vec3 fragNormal;


void main(){
  vec3 targetVec = normalize(lightPos - ndc);
  vec3 diffuse = max(dot(targetVec, fragNormal), 0.01) * lightColor;
  gl_FragColor = vec4(diffuse * ambientColor, 1.0);
}
