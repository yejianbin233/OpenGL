#version 330 core
in  vec4 vertexColor;
out vec4 color;
uniform  vec4 uniColor;    // define uniform color

void main () {
  //color = vertexColor;     // set out color as vertex color
  //color = uniColor;        // set out color as unifrom color
  color = vertexColor + uniColor / 10;
}