#version 330 core

uniform vec3 ambientColor;

void main(){
  gl_FragColor = vec4(ambientColor, 1.0);
}
