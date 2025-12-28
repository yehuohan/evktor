#version 450 core

// Fragment input
layout(location = 0) in vec2 inTexcoord;

// Fragment output
layout(location = 0) out vec4 outColor;

// GBuffer from base pass
struct GBuffer {
    sampler2D pos;
    sampler2D normal;
    sampler2D diffspec;
};
uniform GBuffer GBuf;

// Light info
struct Light {
    vec3 pos;
    vec3 color;
};
const int LightNum = 32;
uniform Light lights[LightNum];
uniform vec3 viewPos;


void main() {
    vec3 fragPos = texture(GBuf.pos, inTexcoord).rgb;
    vec3 normal = texture(GBuf.normal, inTexcoord).rgb;
    vec3 matDiffuse = texture(GBuf.diffspec, inTexcoord).rgb;
    float matSpecular = texture(GBuf.diffspec, inTexcoord).a;

    vec3 lighting  = matDiffuse * 0.1; // As ambient component
    vec3 viewDir  = normalize(viewPos - fragPos);
    for(int i = 0; i < LightNum; ++i) {
        // diffuse
        vec3 lightDir = normalize(lights[i].pos - fragPos);
        vec3 diffuse = max(dot(normal, lightDir), 0.0) * matDiffuse * lights[i].color;
        // specular
        vec3 halfwayDir = normalize(lightDir + viewDir);
        vec3 specular = pow(max(dot(normal, halfwayDir), 0.0), 16.0) * matSpecular * lights[i].color;
        // attenuation
        float dist = length(lights[i].pos - fragPos);
        float attenuation = 1.0 / (1.0 + 0.3 * dist + 0.2 * dist * dist);

        lighting += (diffuse + specular) * attenuation;
    }

    outColor = vec4(lighting, 1.0);
}
