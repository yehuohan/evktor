// vim@code: slangc pbr.slang -target spirv -o pbr.slang.spv

struct PBRUniform {
    float4x4 model;
    float4x4 view_proj;
};

[[vk::binding(0, 0)]]
ConstantBuffer<PBRUniform> pbr_ubo;

[[vk::binding(1, 0)]]
Sampler2D base_color_texture;

[shader("vertex")]
float4 vertMain(
    // Vertex inputs
    in float3 position: POSITION, in float2 texcoord_0: TEXCOORD0, in float3 normal: NORMAL,
    // Vertex outputs
    out float3 out_position, out float2 out_texcoord, out float3 out_normal)
    : SV_Position {
    float4 model = mul(pbr_ubo.model, float4(position, 1.0));
    out_position = model.xyz;
    out_texcoord = texcoord_0;
    out_normal = mul(float3x3(pbr_ubo.model), normal);
    return mul(pbr_ubo.view_proj, model);
}

[shader("fragment")]
float4 fragMain(
    // Fragment inputs
    in float3 inp_position, in float2 inp_texcoord, in float3 inp_normal)
    : SV_Target0 {
    return base_color_texture.Sample(inp_texcoord);
}
