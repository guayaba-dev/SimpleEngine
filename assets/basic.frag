#version 330 core

uniform sampler2D texture1;

in vec2 fTexCoords;

void main() {
  gl_FragColor = texture(texture1, fTexCoords);
}
