// vim@code: slangc pbr.slang -target spirv -o pbr.spv
// vim@code: slangc pbr.slang -profile glsl_450 -target glsl -o pbr.glsl -entry vertMain
// vim@code: slangc pbr.slang -profile glsl_450 -target glsl -o pbr.glsl -entry fragMain

struct VertInps {
    float3 position : POSITION;
    float2 texcoord : TEXCOORD0;
    float3 normal : NORMAL;
};

struct VertOuts {
    float3 sv_position : SV_Position;
    float2 texcoord;
    float3 normal;
};

struct FragOuts {
    float4 sv_albedo : SV_Target0;
    float2 sv_normal : SV_Target1;
};

[shader("vertex")]
VertOuts vertMain(VertInps inps) {
    VertOuts outs;
    outs.sv_position = inps.position;
    outs.texcoord = inps.texcoord;
    outs.normal = inps.normal;
    return outs;
}

[shader("fragment")]
FragOuts fragMain(VertOuts inps) {
    FragOuts outs;
    outs.sv_albedo = float4(0.0, 0.0, 0.0, 0.0);
    return outs;
}

// [shader("vertex")]
// void vertMain(
//     // Vertex inputs
//     in float3 position : POSITION,
//     in float2 texcoord : TEXCOORD0,
//     in float3 normal : NORMAL,
//     // Vertex outputs
//     out float3 sv_position : SV_Position,
//     out float2 out_texcoord,
//     out float3 out_normal
// ) {
//     sv_position = position;
//     out_texcoord = texcoord;
//     out_normal = normal;
// }
