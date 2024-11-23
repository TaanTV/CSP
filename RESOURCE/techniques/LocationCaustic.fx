
// 18.01.2023
// Mett: имитация каустики в локациях

technique LocationCaustic
{
	pass p0
	{
		Lighting = false;
		FogEnable = false;

		ZWriteEnable = false;
		AlphaTestEnable = false;
		AlphaBlendEnable = true;

		SrcBlend = destcolor;
		DestBlend = destalpha;

		ColorOp[0] = modulate2x;
		ColorOp[1] = modulate2x;
	}
}