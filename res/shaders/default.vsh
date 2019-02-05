#version 450 core
layout(location = 0) in highp vec2 position;

uniform mat4 camera;
uniform mat4 transform;
varying vec2 _uv;

void main(void) {

    vec2 vertex = position * 0.001953125;
    gl_Position = transform * vec4(vertex.xy, 0, 1.0);

    _uv = vertex.xy;
}
