#ifndef SHADERS_H_INCLUDED
#define SHADERS_H_INCLUDED

 const char * const vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aNorm;\n"
    "layout (location = 2) in vec2 aTexCoord;"
  //  "out vec3 outCol;\n"
    "out vec3 outNorm;\n"
    "out vec2 TexCoord;\n"
    "out vec3 FragPos;\n"
    "uniform mat4 model_matr;\n"
    "uniform mat4 view_matr;\n"
    "uniform mat4 proj_matr;\n"
    "void main()\n"
    "{\n"
       "gl_Position =proj_matr*view_matr*model_matr*vec4(aPos.x,aPos.y,aPos.z,1);\n"
      "outNorm=mat3(model_matr) * aNorm;"
       "FragPos = vec3(model_matr * vec4(aPos, 1.0));"
       "TexCoord = aTexCoord;\n"
    "}\0";

 const char * const fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "in vec3 outNorm;\n"
    "in vec2 TexCoord;\n"
    "in vec3 FragPos;\n"
    "uniform sampler2D ourTexture;\n"
    "uniform vec3 viewPos;\n"
    "uniform vec3 lightPos;\n"
    "uniform vec3 lightColor;\n"
    "void main()\n"
    "{\n"
        //fog
        "vec4  fog_colour = vec4(0.75, 0.75, 0.75, 1);"
         "float dist= distance(viewPos,FragPos);"
        " float FogMin = length(viewPos);"
        "  float FogMax = FogMin+3;"
        "float fog_factor= (FogMax - dist) / (FogMax - FogMin);"
        "fog_factor=clamp(fog_factor,0,1);"
        // light
        "vec3 norm = normalize(outNorm);\n"
        "vec3 lightDir = normalize(lightPos - FragPos);\n"
        "float diff = max(dot(norm, lightDir), 0.0);"  //diffuse
        "float specularStrength = 0.5;\n"
        "vec3 viewDir = normalize(viewPos - FragPos);"
        "vec3 reflectDir = reflect(-lightDir, norm);"
        "float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);"
        "vec3 specular = specularStrength * spec * lightColor;"
        "vec4 light_factor =vec4( ((diff+0.05) * lightColor)+ specular,1 );" // 0.05 is ambient lighting
        "FragColor =mix(fog_colour,light_factor*texture(ourTexture, TexCoord),fog_factor);"
        //"FragColor =light_factor* texture(ourTexture, TexCoord);"
    "}\n\0";

const char* cubeMapVS=
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;"
"out vec3 TexCoords;"
"out vec3 FragPos;"
"uniform mat4 projection;"
"uniform mat4 view;"
"void main()"
"{"
    "TexCoords = aPos;"
    "vec4 pos  = projection * view * vec4(aPos, 1.0);"
    "FragPos = aPos;"
    "gl_Position = vec4(pos.x,pos.y,pos.w,pos.w);"
"}";

const char* cubeMapFS=
"#version 330 core\n"
"out vec4 FragColor;"
"in vec3 TexCoords;"
"in vec3 FragPos;"
"uniform samplerCube skybox;"
"void main()\n"
"{"
     "vec4  fog_colour = vec4(0.75, 0.75, 0.75, 1);"
     "float dist =FragPos.z;"
     "float fog_factor =0.35;"
    //"    FragColor = texture(skybox, TexCoords);"
    "FragColor =mix(fog_colour,texture(skybox, TexCoords),fog_factor);"
"}";

#endif // SHADERS_H_INCLUDED
