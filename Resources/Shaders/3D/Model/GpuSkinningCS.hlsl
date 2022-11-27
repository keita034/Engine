// 頂点データ
static const int MAX_BONE = 32;

struct PosNormSkin
{
    float4 pos : POSITION; // 座標
    float3 normal : NORMAL; // 法線
    float2 uv : TEXCOORD; // uv座標
    float3 tangent :TANGENT; // 接空間
    float4 color :COLOR; // 頂点色
    uint4 boneIndex : BONEINDICES; // ボーンの番号
    float4 boneWeight : BONEWEIGHTS; // ボーンの重み

};

cbuffer SkinData : register(b0)
{
    matrix bones[MAX_BONE];
};

//出力データ構造体
struct OutputData
{
    float4 pos; // 座標
    float3 normal; // 法線
    float2 uv; // uv座標
    float3 tangent; // 接空間
    float4 color; // 頂点色
};

//入力データにアクセスするための変数
StructuredBuffer<PosNormSkin> input : register(t0);

//出力データにアクセスするための変数
RWStructuredBuffer<OutputData> output : register(u0);

//エントリーポイント
[numthreads(256, 1, 1)]
void main(uint3 DTid : SV_DispatchThreadID)
{

    // ゼロクリア
    OutputData outputData = (OutputData) 0;
    
    matrix m; // スキニング行列

    
    m = input[DTid.x].boneWeight.x * bones[input[DTid.x].boneIndex.x];
    m += input[DTid.x].boneWeight.y * bones[input[DTid.x].boneIndex.y];
    m += input[DTid.x].boneWeight.z * bones[input[DTid.x].boneIndex.z];
    m += input[DTid.x].boneWeight.w * bones[input[DTid.x].boneIndex.w];
    
    // ボーン0
    outputData.pos = mul(m, input[DTid.x].pos);
    outputData.normal = mul((float3x3) m, input[DTid.x].normal);

    outputData.uv = input[DTid.x].uv;
    outputData.tangent = input[DTid.x].tangent;
    outputData.color = input[DTid.x].color;
    output[DTid.x] = outputData;

}