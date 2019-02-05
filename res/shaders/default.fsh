#version 450 core

uniform vec4 albedo;
uniform sampler2D image;
varying vec2 _uv;

void main(void) {
    gl_FragColor = albedo.rgba * texture(image, _uv).rgba;
}