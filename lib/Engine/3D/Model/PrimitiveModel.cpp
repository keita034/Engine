#include "PrimitiveModel.h"
#include"DefaultMaterial.h"

void PrimitiveModel::Draw(Transform* transform, Material* material)
{
	if (!material)
	{
		if (!modelMaterialData)
		{
			modelMaterialData = DefaultMaterial::GetDefaultMaterial()->DEFAULT_TEXTURE_MATERIAL.get();
		}
	}
	else
	{
		modelMaterialData = material;
	}

	ModelDraw(transform, modelMaterialData);
}

void PrimitiveModel::Initialize(ModelShape shape)
{
	ModelInitialize();

	switch (shape)
	{
	case ModelShape::Cube:
		maxIndex = cubeMaxIndex;
		maxVert = cubeMaxVert;

		//頂点バッファ・インデックス生成
		CreatVertexIndexBuffer();
		CubeCreate();
		break;

	case ModelShape::Sphere:
		maxIndex = sphereMaxIndex;
		maxVert = sphereMaxVert;

		//頂点バッファ・インデックス生成
		CreatVertexIndexBuffer();
		SphereCreate();
		break;

	case ModelShape::Capsule:
		break;

	case ModelShape::Cylinder:
		maxIndex = cylinderMaxIndex;
		maxVert = cylinderMaxVert;

		//頂点バッファ・インデックス生成
		CreatVertexIndexBuffer();
		CylinderCreate();
		break;

	case ModelShape::Cone:
		maxIndex = coneMaxIndex;
		maxVert = coneMaxVert;

		//頂点バッファ・インデックス生成
		CreatVertexIndexBuffer();
		ConeCreate();
		break;

	default:
		break;
	}
}

void PrimitiveModel::CubeCreate()
{
	//定数バッファ生成(マテリアル)
	constBuffMaterial = std::make_unique<ConstantBuffer>();
	constBuffMaterial->Create(sizeof(ConstBuffDataMaterial));

	AliceMathF::Vector3 one = { 0.8f,0.8f,0.8f };
	modelMaterial.ambient = one;
	modelMaterial.diffuse = one;
	modelMaterial.specular = one;
	modelMaterial.alpha = modelMaterial.alpha;
	constBuffMaterial->Update(&modelMaterial);

	// 頂点データ
	//正面
	PosNormalUv tmp = { { -1.0f, -1.0f, -1.0f }, {}, { 0.0f, 1.0f } };//左上インデックス0
	vertices.push_back(tmp);
	tmp = { {-1.0f, 1.0f,-1.0f},{},{ 0.0f, 0.0f} };//左下インデックス1
	vertices.push_back(tmp);
	tmp = { { 1.0f,-1.0f,-1.0f},{},{ 1.0f, 1.0f} };//右上インデックス2
	vertices.push_back(tmp);
	tmp = { { 1.0f, 1.0f,-1.0f},{},{ 1.0f, 0.0f} };//右下インデックス3
	vertices.push_back(tmp);

	//右
	tmp = { { 1.0f,-1.0f,-1.0f},{},{ 0.0f, 1.0f} };//左上インデックス4
	vertices.push_back(tmp);
	tmp = { { 1.0f, 1.0f,-1.0f},{},{ 0.0f, 0.0f} };//左下インデックス5
	vertices.push_back(tmp);
	tmp = { { 1.0f,-1.0f, 1.0f},{},{ 1.0f, 1.0f} };//右上インデックス6
	vertices.push_back(tmp);
	tmp = { { 1.0f, 1.0f, 1.0f},{},{ 1.0f, 0.0f} };//右下インデックス7
	vertices.push_back(tmp);

	//左
	tmp = { {-1.0f,-1.0f, 1.0f},{},{ 0.0f, 1.0f} };//左上インデックス8
	vertices.push_back(tmp);
	tmp = { {-1.0f, 1.0f, 1.0f},{},{ 0.0f, 0.0f} };//左下インデックス9
	vertices.push_back(tmp);
	tmp = { {-1.0f,-1.0f,-1.0f},{},{ 1.0f, 1.0f} };//右上インデックス10
	vertices.push_back(tmp);
	tmp = { {-1.0f, 1.0f,-1.0f},{},{ 1.0f, 0.0f} };//右下インデックス11
	vertices.push_back(tmp);

	//裏
	tmp = { { 1.0f,-1.0f, 1.0f},{},{ 0.0f, 1.0f} };//左上インデックス12
	vertices.push_back(tmp);
	tmp = { { 1.0f, 1.0f, 1.0f},{},{ 0.0f, 0.0f} };//左下インデックス13
	vertices.push_back(tmp);
	tmp = { {-1.0f,-1.0f, 1.0f},{},{ 1.0f, 1.0f} };//右上インデックス14
	vertices.push_back(tmp);
	tmp = { {-1.0f, 1.0f, 1.0f},{},{ 1.0f, 0.0f} };//右下インデックス15
	vertices.push_back(tmp);

	//上
	tmp = { {-1.0f, 1.0f,-1.0f},{},{ 0.0f, 1.0f} };//左上インデックス16
	vertices.push_back(tmp);
	tmp = { {-1.0f, 1.0f, 1.0f},{},{ 0.0f, 0.0f} };//左下インデックス17
	vertices.push_back(tmp);
	tmp = { { 1.0f, 1.0f,-1.0f},{},{ 1.0f, 1.0f} };//右上インデックス18
	vertices.push_back(tmp);
	tmp = { { 1.0f, 1.0f, 1.0f},{},{ 1.0f, 0.0f} };//右下インデックス19
	vertices.push_back(tmp);

	//底
	tmp = { {-1.0f,-1.0f, 1.0f},{},{ 0.0f, 1.0f} };//左上インデックス20
	vertices.push_back(tmp);
	tmp = { {-1.0f,-1.0f,-1.0f},{},{ 0.0f, 0.0f} };//左下インデックス21
	vertices.push_back(tmp);
	tmp = { { 1.0f,-1.0f, 1.0f},{},{ 1.0f, 1.0f} };//右上インデックス22
	vertices.push_back(tmp);
	tmp = { { 1.0f,-1.0f,-1.0f},{},{ 1.0f, 0.0f} };//右下インデックス23
	vertices.push_back(tmp);

// インデックスデータ

	//正面
	indices.push_back(0), indices.push_back(1), indices.push_back(3);//0
	indices.push_back(3), indices.push_back(2), indices.push_back(0);//1

	//右
	indices.push_back(4), indices.push_back(5), indices.push_back(7);//2
	indices.push_back(7), indices.push_back(6), indices.push_back(4);//3

	//左
	indices.push_back(8), indices.push_back(9), indices.push_back(11);//4
	indices.push_back(11), indices.push_back(10), indices.push_back(8);//5

	//裏
	indices.push_back(12), indices.push_back(13), indices.push_back(15);//6
	indices.push_back(15), indices.push_back(14), indices.push_back(12);//7

	//上
	indices.push_back(16), indices.push_back(17), indices.push_back(19);//8
	indices.push_back(19), indices.push_back(18), indices.push_back(16);//9

	//底
	indices.push_back(20), indices.push_back(21), indices.push_back(23);//10
	indices.push_back(23), indices.push_back(22), indices.push_back(20);//11

	for (size_t i = 0; i < cubeMaxIndex / 3; i++)
	{
		//三角形1つごとに計算していく
		//三角形のインデックスを取り出して、一時的な変数に入れる
		uint32_t Index0 = indices[i * 3 + 0];
		uint32_t Index1 = indices[i * 3 + 1];
		uint32_t Index2 = indices[i * 3 + 2];
		//三角形を構成する頂点座標をベクトルに代入
		AliceMathF::Vector3 p0 = vertices[Index0].pos;
		AliceMathF::Vector3 p1 = vertices[Index1].pos;
		AliceMathF::Vector3 p2 = vertices[Index2].pos;
		//p0->p1ベクトル、p0->p2ベクトルを計算(ベクトルの減算)
		AliceMathF::Vector3 v1 = p1 - p0;
		AliceMathF::Vector3 v2 = p2 - p0;
		//外積は両方から垂直なベクトル
		AliceMathF::Vector3 normal = v1.Cross(v2);
		//正規化する
		normal.Normal();
		vertices[Index0].normal = normal;
		vertices[Index1].normal = normal;
		vertices[Index2].normal = normal;

	}
	//頂点バッファへのデータ転送
	vertexBuffer->Update(vertices.data());

	//インデックスバッファへのデータ転送
	indexBuffer->Update(indices.data());

	matWorld = AliceMathF::MakeIdentity();
}

void PrimitiveModel::ConeCreate()
{
	//定数バッファ生成(マテリアル)
	constBuffMaterial = std::make_unique<ConstantBuffer>();
	constBuffMaterial->Create(sizeof(ConstBuffDataMaterial));
	constBuffMaterial->Update(&modelMaterial);

	// 頂点データ
	constexpr UINT NumDiv = 32; // 分割数
	float RadianPerDivision = AliceMathF::AX_2PI / float(NumDiv); // 分割1単位の角度

	//分割点分割数より1つ多くしておいて1周回るようにする
	std::array<float, NumDiv + 1> pointsZ{};
	std::array<float, NumDiv + 1> pointsX{};
	std::array<float, NumDiv + 1> pointsU{};
	std::array<float, NumDiv + 1> pointsV{};

	//上側の計算
	//頂点座標の計算
	for (size_t i = 0; i < NumDiv; ++i)
	{
		float baseZ = cos(RadianPerDivision * static_cast<float>(i)) * 1.0f;
		float baseX = sin(RadianPerDivision * static_cast<float>(i)) * 1.0f;
		pointsZ[i] = baseZ * -1.0f;
		pointsX[i] = baseX;
	}

	//UV座標の計算
	for (size_t i = 0; i < NumDiv; ++i)
	{
		float baseU = cos(RadianPerDivision * static_cast<float>(i)) * 0.25f;
		float baseV = sin(RadianPerDivision * static_cast<float>(i)) * 0.25f;
		pointsU[i] = baseU + 0.25f;
		pointsV[i] = baseV + 0.5f;
	}

	//最後と最初は一緒
	(*pointsZ.rbegin()) = (*pointsZ.begin());
	(*pointsX.rbegin()) = (*pointsX.begin());
	(*pointsU.rbegin()) = (*pointsU.begin());
	(*pointsV.rbegin()) = (*pointsV.begin());

	PosNormalUv tmp{};
	//計算した値を代入
	for (size_t i = 0; i < static_cast<size_t>(NumDiv + 1.0f); i++)
	{
		tmp = { { pointsX[i],-1.0f,pointsZ[i] },{},{ pointsU[i],pointsV[i]} };
		vertices.push_back(tmp);
	}

	tmp = { { 0.0f,1.0f,0.0f },{},{ 0.25f,0.5f } };
	vertices.push_back(tmp);

	//下側の計算
	//UV座標の計算
	for (size_t i = 0; i < NumDiv; ++i)
	{
		float baseU = cos(RadianPerDivision * static_cast<float>(i)) * 0.25f;
		float baseV = sin(RadianPerDivision * static_cast<float>(i)) * 0.25f;
		pointsU[i] = baseU + 0.75f;
		pointsV[i] = baseV + 0.5f;
	}

	(*pointsU.rbegin()) = (*pointsU.begin());
	(*pointsV.rbegin()) = (*pointsV.begin());

	//計算した値を代入
	for (size_t i = 1; i < static_cast<size_t>(NumDiv + 1.0f); i++)
	{
		tmp = { { pointsX[i],-1.0f,pointsZ[i] },{},{ pointsU[i],pointsV[i]} };
		vertices.push_back(tmp);
	}

	tmp = { { 0.0f,-1.0f,0.0f },{},{ 0.75f,0.5 } };
	vertices.push_back(tmp);

	// インデックスデータ
	uint8_t count = 0;
	uint16_t indexData = 0;

	//インデックスデータの計算上側
	for (uint16_t i = 0; i < 96; i++)
	{
		if (count == 3)
		{
			count = 0;
		}

		switch (count)
		{
		case 0:
			indices.push_back(indexData);
			break;
		case 1:
			indices.push_back(33);
			break;
		case 2:
			indexData++;
			indices.push_back(indexData);
			break;
		}

		count++;
	}

	count = 0;
	indexData = 35;
	//インデックスデータの計側
	for (size_t i = 96; i < maxIndex; i++)
	{
		if (count == 3)
		{
			count = 0;
		}

		switch (count)
		{
		case 0:
			indices.push_back(indexData);
			break;
		case 1:
			indices.push_back(65);
			break;
		case 2:
			indices.push_back(indexData - static_cast<unsigned>(1));
			indexData++;
			break;
		}

		count++;
	}

	for (UINT i = 0; i < indices.size() / 3; i++)
	{
		//三角形1つごとに計算していく
		//三角形のインデックスを取り出して、一時的な変数に入れる
		uint32_t Index0 = indices[static_cast<size_t>(i * 3 + 0)];
		uint32_t Index1 = indices[static_cast<size_t>(i * 3 + 1)];
		uint32_t Index2 = indices[static_cast<size_t>(i * 3 + 2)];
		//三角形を構成する頂点座標をベクトルに代入
		AliceMathF::Vector3 p0 = vertices[Index0].pos;
		AliceMathF::Vector3 p1 = vertices[Index1].pos;
		AliceMathF::Vector3 p2 = vertices[Index2].pos;
		//p0->p1ベクトル、p0->p2ベクトルを計算(ベクトルの減算)
		AliceMathF::Vector3 v1 = p1 - p0;
		AliceMathF::Vector3 v2 = p2 - p0;
		//外積は両方から垂直なベクトル
		AliceMathF::Vector3 normal = v1.Cross(v2);
		//正規化する
		normal.Normal();
		vertices[Index0].normal = normal;
		vertices[Index1].normal = normal;
		vertices[Index2].normal = normal;
	}

	//頂点バッファへのデータ転送
	vertexBuffer->Update(vertices.data());

	//インデックスバッファへのデータ転送
	indexBuffer->Update(indices.data());

	//ワールド座標
	matWorld = AliceMathF::MakeIdentity();
}

void PrimitiveModel::CylinderCreate()
{
	//定数バッファ生成(マテリアル)
	constBuffMaterial = std::make_unique<ConstantBuffer>();
	constBuffMaterial->Create(sizeof(ConstBuffDataMaterial));
	constBuffMaterial->Update(&modelMaterial);

	// 頂点データ
	constexpr UINT NumDiv = 32; // 分割数
	float RadianPerDivision = AliceMathF::AX_2PI / float(NumDiv); // 分割1単位の角度

	//分割点分割数より1つ多くしておいて1周回るようにする
	std::array<float, NumDiv + 1> pointsZ{};
	std::array<float, NumDiv + 1> pointsX{};
	std::array<float, NumDiv + 1> pointsU{};
	std::array<float, NumDiv + 1> pointsV{};

	//上側の計算
	//頂点座標の計算
	for (size_t i = 0; i < NumDiv; ++i)
	{
		float baseZ = cos(RadianPerDivision * static_cast<float>(i)) * 1.0f;
		float baseX = sin(RadianPerDivision * static_cast<float>(i)) * 1.0f;
		pointsZ[i] = baseZ * -1.0f;
		pointsX[i] = baseX;
		//UV座標の計算
		float baseU = cos(RadianPerDivision * static_cast<float>(i)) * 0.25f;
		float baseV = sin(RadianPerDivision * static_cast<float>(i)) * 0.25f;
		pointsU[i] = baseU + 0.75f;
		pointsV[i] = baseV + 0.75f;
	}

	//最後と最初は一緒
	(*pointsZ.rbegin()) = (*pointsZ.begin());
	(*pointsX.rbegin()) = (*pointsX.begin());
	(*pointsU.rbegin()) = (*pointsU.begin());
	(*pointsV.rbegin()) = (*pointsV.begin());

	PosNormalUv tmp;

	//計算した値を代入
	for (size_t i = 0; i < NumDiv; i++)
	{
		tmp = { { pointsX[i],1.0f,pointsZ[i] },{},{ pointsV[i],pointsU[i] } };
		vertices.push_back(tmp);
	}

	tmp = { { 0.0f,1.0f,0.0f },{},{ 0.75f,0.75f } };
	vertices.push_back(tmp);

	//下側の計算
	//UV座標の計算
	for (size_t i = 0; i < NumDiv; ++i)
	{
		float baseU = cos(RadianPerDivision * static_cast<float>(i)) * 0.25f;
		float baseV = sin(RadianPerDivision * static_cast<float>(i)) * 0.25f;
		pointsU[i] = baseU + 0.25f;
		pointsV[i] = baseV + 0.75f;
	}

	(*pointsU.rbegin()) = (*pointsU.begin());
	(*pointsV.rbegin()) = (*pointsV.begin());

	//計算した値を代入
	for (size_t i = 0; i < static_cast<size_t>(NumDiv); i++)
	{
		tmp = { { pointsX[i],-1.0f,pointsZ[i] },{},{ pointsU[i],pointsV[i] }, };
		vertices.push_back(tmp);
	}

	tmp = { { 0.0f,-1.0f,0.0f },{},{ 0.25f,0.75f } };
	vertices.push_back(tmp);

	//UV座標の計算
	for (size_t i = 0; i < static_cast<size_t>(NumDiv + 1); ++i)
	{
		pointsU[i] = static_cast<float>(i) * (1.0f / 31.0f);
		pointsV[i] = 0.5f;
	}
	(*pointsU.rbegin()) = 1.0f;

	//計算した値を代入
	for (size_t i = 0; i < static_cast<size_t>(NumDiv + 1); i++)
	{
		tmp = { { pointsX[i],-1.0f,pointsZ[i] },{},{ pointsU[i],pointsV[i] } };
		vertices.push_back(tmp);
	}

	//UV座標の計算
	for (size_t i = 0; i < static_cast<size_t>(NumDiv + 1); ++i)
	{
		pointsU[i] = static_cast<float>(i) * (1.0f / 31.0f);
		pointsV[i] = 0.0f;
	}

	(*pointsU.rbegin()) = 1.0f;

	//計算した値を代入
	for (size_t i = 0; i < static_cast<size_t>(NumDiv + 1); i++)
	{
		tmp = { { pointsX[i],1.0f,pointsZ[i] },{},{ pointsU[i],pointsV[i] } };
		vertices.push_back(tmp);
	}

	// インデックスデータ
	uint8_t count = 0;
	uint16_t indexData = 0;

	//インデックスデータの計算上側
	for (uint16_t i = 0; i < 93; i++)
	{
		if (count == 3)
		{
			count = 0;
		}

		if (i == 92)
		{
			indices.push_back(0);
			count++;
		}

		switch (count)
		{
		case 0:
			indices.push_back(indexData);
			break;
		case 1:
			indices.push_back(32);
			break;
		case 2:
			indexData++;
			indices.push_back(indexData);

			break;
		}

		count++;
	}

	count = 0;
	indexData = 34;
	//インデックスデータの計側
	for (size_t i = 0; i < 95; i++)
	{
		if (count == 3)
		{
			count = 0;
		}

		if (i == 93)
		{
			indices.push_back(33);
			count++;
		}

		switch (count)
		{
		case 0:
			indices.push_back(indexData);
			break;
		case 1:
			indices.push_back(65);
			break;
		case 2:
			indices.push_back(indexData - static_cast<unsigned>(1));
			indexData++;
			break;
		}
		count++;
	}

	count = 0;
	indexData = 66;
	//インデックスデータの計側
	for (size_t i = 0; i < 96; i++)
	{
		if (count == 3)
		{
			count = 0;
		}

		if (i == 95)
		{
			indices.push_back(98);
			count++;
		}

		switch (count)
		{
		case 0:
			indices.push_back(indexData);
			break;
		case 1:
			indices.push_back(indexData + static_cast<unsigned>(33));
			break;
		case 2:
			indices.push_back(indexData + static_cast<unsigned>(1));
			indexData += 1;
			break;
		}
		count++;

	}

	count = 0;
	indexData = 98;
	//インデックスデータの計側
	for (size_t i = 0; i < 99; i++)
	{
		if (count == 3)
		{
			count = 0;
		}

		if (i == 97)
		{
			indices.push_back(98);
			count++;
		}

		switch (count)
		{
		case 0:
			indices.push_back(indexData + static_cast<unsigned>(1));
			break;
		case 1:
			indices.push_back(indexData - static_cast<unsigned>(32));
			break;
		case 2:
			indices.push_back(indexData);
			indexData += 1;
			break;
		}
		count++;
	}

	for (UINT i = 0; i < indices.size() / 3; i++)
	{
		//三角形1つごとに計算していく
		//三角形のインデックスを取り出して、一時的な変数に入れる
		uint32_t Index0 = indices[static_cast<std::vector<uint32_t, std::allocator<uint32_t>>::size_type>(i) * 3 + 0];
		uint32_t Index1 = indices[static_cast<std::vector<uint32_t, std::allocator<uint32_t>>::size_type>(i) * 3 + 1];
		uint32_t Index2 = indices[static_cast<std::vector<uint32_t, std::allocator<uint32_t>>::size_type>(i) * 3 + 2];
		//三角形を構成する頂点座標をベクトルに代入
		AliceMathF::Vector3 p0 = vertices[Index0].pos;
		AliceMathF::Vector3 p1 = vertices[Index1].pos;
		AliceMathF::Vector3 p2 = vertices[Index2].pos;
		//p0->p1ベクトル、p0->p2ベクトルを計算(ベクトルの減算)
		AliceMathF::Vector3 v1 = p1 - p0;
		AliceMathF::Vector3 v2 = p2 - p0;
		//外積は両方から垂直なベクトル
		AliceMathF::Vector3 normal = v1.Cross(v2);
		//正規化する
		normal.Normal();
		vertices[Index0].normal = normal;
		vertices[Index1].normal = normal;
		vertices[Index2].normal = normal;

	}

	//頂点バッファへのデータ転送
	vertexBuffer->Update(vertices.data());

	//インデックスバッファへのデータ転送
	indexBuffer->Update(indices.data());

	matWorld = AliceMathF::MakeIdentity();
}

void PrimitiveModel::SphereCreate()
{
	//定数バッファ生成(マテリアル)
	constBuffMaterial = std::make_unique<ConstantBuffer>();
	constBuffMaterial->Create(sizeof(ConstBuffDataMaterial));


	AliceMathF::Vector3 one = { 0.8f,0.8f,0.8f };
	modelMaterial.ambient = one;
	modelMaterial.diffuse = one;
	modelMaterial.specular = one;
	modelMaterial.alpha = modelMaterial.alpha;

	constBuffMaterial->Update(&modelMaterial);

	// 頂点データ
	float u = 0.0f;
	float v = 0.0f;

	PosNormalUv tmp = { {0, 0, 0},{1,1,1},{0,0} };

	vertices.push_back(tmp);

	size_t dividedInVertical = 16;
	size_t dividedInHorizontal = 32;
	float radius = 1;
	float Deg2Rad = (AliceMathF::AX_PI * 2.0f) / 360.0f;


	for (size_t p = 1; p < dividedInVertical; p++)
	{
		tmp.pos.y = std::cos(Deg2Rad * static_cast<float>(p) * 180.0f / static_cast<float>(dividedInVertical)) * radius;
		float t = std::sin(Deg2Rad * static_cast<float>(p) * 180.0f / static_cast<float>(dividedInVertical)) * radius;

		v += 1.0f / 16.0f;
		u = -1.0f / 32.0f;

		for (size_t q = 0; q < dividedInHorizontal + 1; q++)
		{
			u += 1.0f / 32.0f;
			tmp.uv = { u,v };
			tmp.pos.x = std::cos(Deg2Rad * static_cast<float>(q) * 360.0f / static_cast<float>(dividedInHorizontal)) * t;
			tmp.pos.z = std::sin(Deg2Rad * static_cast<float>(q) * 360.0f / static_cast<float>(dividedInHorizontal)) * t;
			vertices.push_back(tmp);
		}
	}

	u = 0.0f;
	v = 0.0f;
	for (size_t i = 0; i < dividedInHorizontal; i++)
	{
		u += 1.0f / 31.0f;
		tmp.uv = { u,v };
		tmp.pos = AliceMathF::Vector3(0, radius, 0);
		vertices.push_back(tmp);
	}

	u = 0.0f;
	v = 1.0f;
	for (size_t i = 0; i < dividedInHorizontal; i++)
	{
		u += 1.0f / 31.0f;
		tmp.uv = { u,v };
		tmp.pos = AliceMathF::Vector3(0, -radius, 0);
		vertices.push_back(tmp);
	}

#pragma endregion

#pragma region 頂点順序を格納

	uint16_t apexIndex = 496;

	for (size_t i = 0; i < dividedInHorizontal; i++)
	{
		if (i == dividedInHorizontal - 1)
		{
			indices.push_back(static_cast<uint16_t>(apexIndex));
			indices.push_back(static_cast<uint16_t>(i + 2));
			indices.push_back(static_cast<uint16_t>(i + 1));
			break;
		}

		indices.push_back(static_cast<uint16_t>(apexIndex++));
		indices.push_back(static_cast<uint16_t>(i + 2));
		indices.push_back(static_cast<uint16_t>(i + 1));
	}

	for (size_t p = 0; p < dividedInVertical - 1; p++)
	{
		auto firstIndexInLayer = p * dividedInHorizontal + 1;

		for (size_t q = 0; q < dividedInHorizontal; q++)
		{
			if (q == dividedInHorizontal - 1)
			{
				indices.push_back(static_cast<uint16_t>(firstIndexInLayer + q));
				indices.push_back(static_cast<uint16_t>(firstIndexInLayer));
				indices.push_back(static_cast<uint16_t>(firstIndexInLayer + dividedInHorizontal));

				indices.push_back(static_cast<uint16_t>(firstIndexInLayer + q));
				indices.push_back(static_cast<uint16_t>(firstIndexInLayer + dividedInHorizontal));
				indices.push_back(static_cast<uint16_t>(firstIndexInLayer + q + dividedInHorizontal));

				break;
			}

			indices.push_back(static_cast<uint16_t>(firstIndexInLayer + q));
			indices.push_back(static_cast<uint16_t>(firstIndexInLayer + q + 1));
			indices.push_back(static_cast<uint16_t>(firstIndexInLayer + q + 1 + dividedInHorizontal));

			indices.push_back(static_cast<uint16_t>(firstIndexInLayer + q));
			indices.push_back(static_cast<uint16_t>(firstIndexInLayer + q + dividedInHorizontal + 1));
			indices.push_back(static_cast<uint16_t>(firstIndexInLayer + q + dividedInHorizontal));
		}
	}

	apexIndex = 528;
	for (size_t i = 0; i < dividedInHorizontal; i++)
	{
		if (i == dividedInHorizontal - 1)
		{
			indices.push_back(static_cast<uint16_t>(apexIndex));
			indices.push_back(static_cast<uint16_t>(static_cast<size_t>(496) - 1 - dividedInHorizontal + i));
			indices.push_back(static_cast<uint16_t>(496 - dividedInHorizontal + i));
			break;
		}
		indices.push_back(static_cast<uint16_t>(apexIndex++));
		indices.push_back(static_cast<uint16_t>(static_cast<size_t>(496) - 1 - dividedInHorizontal + i));
		indices.push_back(static_cast<uint16_t>(496 - dividedInHorizontal + i));
	}

#pragma endregion



	for (UINT i = 0; i < indices.size() / 3; i++)
	{
		//三角形1つごとに計算していく
		//三角形のインデックスを取り出して、一時的な変数に入れる
		uint32_t Index0 = indices[static_cast<std::vector<uint32_t, std::allocator<uint32_t>>::size_type>(i) * 3 + 0];
		uint32_t Index1 = indices[static_cast<std::vector<uint32_t, std::allocator<uint32_t>>::size_type>(i) * 3 + 1];
		uint32_t Index2 = indices[static_cast<std::vector<uint32_t, std::allocator<uint32_t>>::size_type>(i) * 3 + 2];
		//三角形を構成する頂点座標をベクトルに代入
		AliceMathF::Vector3 p0 = vertices[Index0].pos;
		AliceMathF::Vector3 p1 = vertices[Index1].pos;
		AliceMathF::Vector3 p2 = vertices[Index2].pos;
		//p0->p1ベクトル、p0->p2ベクトルを計算(ベクトルの減算)
		AliceMathF::Vector3 v1 = p1 - p0;
		AliceMathF::Vector3 v2 = p2 - p0;
		//外積は両方から垂直なベクトル
		AliceMathF::Vector3 normal = v1.Cross(v2);
		//正規化する
		normal.Normal();
		vertices[Index0].normal = normal;
		vertices[Index1].normal = normal;
		vertices[Index2].normal = normal;

	}

	//頂点バッファへのデータ転送
	vertexBuffer->Update(vertices.data());

	//インデックスバッファへのデータ転送
	indexBuffer->Update(indices.data());

	matWorld = AliceMathF::MakeIdentity();
}

void PrimitiveModel::Create(bool smoothing)
{
	static_cast<void>(smoothing);
}

void PrimitiveModel::Create(const char* filePath, bool smoothing)
{
	static_cast<void>(filePath);
	static_cast<void>(smoothing);

}

void PrimitiveModel::Initialize(const char* filePath, bool smoothing)
{
	static_cast<void>(filePath);
	static_cast<void>(smoothing);
}
