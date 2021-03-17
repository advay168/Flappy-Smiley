#version 330 core

precision mediump float;

out vec4 FragColor;

in vec2 texPos;

uniform sampler2D tex;

void main(){
	//FragColor = vec4(1.0,0.0,0.0,1.0);
	FragColor = texture(tex,texPos);
}