#include"ModelSimple.hlsli"

VSOutput main(float4 pos : POSITION, float3 normal : NORMAL, float2 uv : TEXCOORD, float3 tangent : TANGENT, float4 color : COLOR)
{
    // 法線にワールド行列によるスケーリング・回転を適用
    float4 wnormal = normalize(mul(world, float4(normal, 0)));

    VSOutput output; // ピクセルシェーダーに渡す値
    output.svpos = mul(matWorld, mul(postureMat, pos));
    output.normal = wnormal.xyz;
    output.color = color;
    output.uv = uv;
    return output;
}