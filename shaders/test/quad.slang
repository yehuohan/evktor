struct Args {
    int scaler;
};

// clang-format off
[[vk::binding(0, 0)]] Texture2D<float4> inp_img;
[[vk::binding(1, 0)]] RWTexture2D<float4> out_img;

[[vk::push_constant]] ConstantBuffer<Args> args;

[[vk::constant_id(0)]] const int alpha = 1;
// clang-format on

[shader("compute")]
[numthreads(8, 8, 1)]
void main(uint3 tid: SV_DispatchThreadID) {
    int2 pos = int2(tid.xy);
    float3 color = inp_img.Load(int3(pos, 0)).rgb;
    out_img[pos] = float4(color * args.scaler, alpha);
}
