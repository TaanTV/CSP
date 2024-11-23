/// VS
float4x4 mWorldViewProjection;
float4x4 mWorld;

float4 vSunDir;
float4 vSunDiffuse;

float4 vEyePos;

struct LIGHT
{
    float4 vPos;
    float4 vColor;
    float4 vAttenuation;
};

// LIGHT
#define MAX_LIGHTS 16

unsigned int nLightsNum;

float4 vPointLightPos[MAX_LIGHTS];
float4 vPointLightDiffuse[MAX_LIGHTS];
float4 vPointLightAttenuation[MAX_LIGHTS];
//float4 vPointLightSpecular[MAX_LIGHTS];

float fMaterialAmbient;
float fMaterialDiffuse;
float fMaterialEmissive;
float fMaterialSpecular;
float fMaterialShininess;

struct VS_INPUT
{
    float4 vPos : POSITION;
    float3 vNormal : NORMAL0;
    float4 vDiffuse : COLOR0;
    float2 vTexCoord0 : TEXCOORD0;
    float2 vTexCoord1 : TEXCOORD1;
};

struct VS_OUTPUT
{
    float4 vPos : POSITION;
    float3 vNormal : NORMAL0;
    float4 vDiffuse : COLOR0;
    float2 vTexCoord0 : TEXCOORD0;
    float2 vTexCoord1 : TEXCOORD1;
    float3 vWorldPos : TEXCOORD3;
    float3 vView : TEXCOORD4;
};

VS_OUTPUT main(VS_INPUT In)
{
    VS_OUTPUT Out = (VS_OUTPUT) 0;
    Out.vTexCoord0 = In.vTexCoord0;
    Out.vTexCoord1 = In.vTexCoord1;
    Out.vDiffuse = In.vDiffuse;
	
    Out.vPos = mul(In.vPos, mWorldViewProjection);
    Out.vWorldPos = mul(In.vPos, mWorld).xyz;
    Out.vNormal = In.vNormal;
    Out.vView = vEyePos.xyz - Out.vWorldPos;

    return Out;
}

///PS
sampler tex1 : register(s0);
sampler tex2 : register(s1);

struct PS_OUTPUT
{
    float4 RGBColor : COLOR0; // Pixel color
};

PS_OUTPUT ps_red(VS_OUTPUT In)
{
    PS_OUTPUT Output;
    
    Output.RGBColor.ra = 1.0f;
    Output.RGBColor.gb = 0.0f;
     
    return Output;
}

PS_OUTPUT ps_0tex(VS_OUTPUT In)
{
    PS_OUTPUT Output;
    Output.RGBColor = In.vDiffuse;
    Output.RGBColor.a = 1.0f;
    return Output;
}

float3 doDirLight(float3 dir, float3 norm)
{
	// TODO: sun params (ambient, spec?)
	float4 ambient = normalize(vSunDiffuse) * 0.7f;
    float4 diffuseIntensitySun = ambient + max(dot(dir, norm), 0.0f) * vSunDiffuse;
    return diffuseIntensitySun.rgb;
	/*
    float3 n = normalize(tex2D(normalMap, IN.texCoord).rgb * 2.0f - 1.0f);
    float3 h = normalize(IN.halfVector);
    float3 l = normalize(IN.lightDir);
    
    float nDotL = saturate(dot(n, l));
    float nDotH = saturate(dot(n, h));
    float power = (nDotL == 0.0f) ? 0.0f : pow(nDotH, fMaterial.shininess);
    
    float4 color = (fMaterial.ambient * (globalAmbient + light.ambient)) +
                   (IN.diffuse * nDotL) + (IN.specular * power);

	return color * tex2D(colorMap, IN.texCoord);*/
}

float4 doLights(VS_OUTPUT In)
{
    float3 N = normalize(In.vNormal);
    float3 V = normalize(In.vView);
    float3 Lsun = normalize(-vSunDir.xyz);

    float4 result = float4(saturate(doDirLight(Lsun, N) + fMaterialAmbient), 1.0f);
	
    for (uint i = 0; i < nLightsNum; i++)
    {
        float3 light = vPointLightPos[i].xyz - In.vWorldPos;
        float3 L = normalize(light);
        float3 R = reflect(-L, N);

		// TODO: light params (ambient, spec)
        float lightDistance = length(light);
        float lightAttenuation = 1.0f / (vPointLightAttenuation[i].x + vPointLightAttenuation[i].y * lightDistance + vPointLightAttenuation[i].z * lightDistance * lightDistance);

        float4 diffuseIntensity = lightAttenuation * fMaterialDiffuse * max(dot(L, N), 0.0f) * vPointLightDiffuse[i];
		//float4 specularIntensity = lightAttenuation * max(pow(dot(R, V), 8.0f), 0.0f) * float4(0.8863f, 0.3451f, 0.1333f, 1.0f) * 0.25f;
        float4 specularIntensity = lightAttenuation * fMaterialSpecular * max(pow(abs(dot(R, V)), fMaterialShininess), 0.0f) * vPointLightDiffuse[i];
		   
        result += float4((specularIntensity + diffuseIntensity).rgb, 1.0f);
    }
	
    return float4(result.xyz, 1.0f);
}

PS_OUTPUT ps_1tex1uv(VS_OUTPUT In)
{
    In.vNormal = mul(normalize(In.vNormal), (float3x3) mWorld);
    PS_OUTPUT Output;
    Output.RGBColor = tex2D(tex1, In.vTexCoord0) * doLights(In);
    return Output;
}

PS_OUTPUT ps_2tex1uv(VS_OUTPUT In)
{
    In.vNormal = mul(normalize(In.vNormal), (float3x3) mWorld);
    PS_OUTPUT Output;
    Output.RGBColor = tex2D(tex1, In.vTexCoord0) * tex2D(tex2, In.vTexCoord0) * doLights(In);
    return Output;
}

PS_OUTPUT ps_2tex2uv(VS_OUTPUT In)
{
    In.vNormal = mul(normalize(In.vNormal), (float3x3) mWorld);
    PS_OUTPUT Output;
    Output.RGBColor = tex2D(tex1, In.vTexCoord0) * tex2D(tex2, In.vTexCoord1) * doLights(In);
    return Output;
}


technique s_0tex
{
    pass p0
    {
        VertexShader = compile vs_3_0 main();
        PixelShader = compile ps_3_0 ps_0tex();
    }
}

technique s_1tex1uv
{
    pass p0
    {
        VertexShader = compile vs_3_0 main();
        PixelShader = compile ps_3_0 ps_1tex1uv();
    }
}

technique s_2tex1uv
{
    pass p0
    {
        VertexShader = compile vs_3_0 main();
        PixelShader = compile ps_3_0 ps_2tex1uv();
    }
}

technique s_2tex2uv
{
    pass p0
    {
        VertexShader = compile vs_3_0 main();
        PixelShader = compile ps_3_0 ps_2tex2uv();
    }
}

float3x3 inverse3x3(float3x3 M)
{
    float det = dot(cross(M[0], M[1]), M[2]);
    float3x3 adjugate = float3x3(cross(M[1], M[2]),
                          cross(M[2], M[0]),
                          cross(M[0], M[1]));
    return adjugate / det;
}

float3x3 cotangent_frame(float3 N, float3 p, float2 uv)
{
    // get edge vectors of the pixel triangle
    float3 dp1 = ddx(p);
    float3 dp2 = ddy(p);
    float2 duv1 = ddx(uv);
    float2 duv2 = ddy(uv);
 
    // solve the linear system
    float3 dp2perp = cross(dp2, N);
    float3 dp1perp = cross(N, dp1);
    float3 T = dp2perp * duv1.x + dp1perp * duv2.x;
    float3 B = dp2perp * duv1.y + dp1perp * duv2.y;
 
    // construct a scale-invariant frame 
    float invmax = rsqrt(max(dot(T, T), dot(B, B)));
    return float3x3(T * invmax, B * invmax, N);
}

float3 perturb_normal(float3 N, float3 V, float2 texcoord)
{
    // assume N, the interpolated vertex normal and 
    // V, the view vector (vertex to eye)
    float3 map = tex2D(tex2, texcoord).xyz;
    map = map * 255./127. - 128./127.;
    
    float3x3 TBN = cotangent_frame(N, -V, texcoord);
    return normalize(mul(TBN, map));
}


PS_OUTPUT ps_1tex1uv_nm(VS_OUTPUT In)
{
    In.vNormal = perturb_normal(mul(normalize(In.vNormal), (float3x3) mWorld), In.vView, In.vTexCoord0);
    PS_OUTPUT Output;
    Output.RGBColor = tex2D(tex1, In.vTexCoord0) * doLights(In);
    return Output;
}

technique s_1tex1uv_nm
{
    pass p0
    {
        VertexShader = compile vs_3_0 main();
        PixelShader = compile ps_3_0 ps_1tex1uv_nm();
    }
}

technique EnvAmmoShader_test
{
    pass p0
    {
        VertexShader = compile vs_3_0 main();
        PixelShader = compile ps_3_0 ps_1tex1uv_nm();
		
        AlphaTestEnable = false;
        AlphaBlendEnable = false;
    }
}

