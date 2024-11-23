#define	POS		r0
#define	NORMAL		r1
#define	TEMP		r2

#define VS_LDL		r8
#define VS_LKa		r9
#define VS_LTMP		r10
#define VS_LDIFRESULT	r11

#define GC_CONSTANT	0
#define	GC_MTX_WVP	1
#define	GC_MTX_WORLD	5
#define GC_LIGHT0	9

#define SHADER \
asm { \
vs_1_1 \
dcl_position v0 \
dcl_normal v1 \
dcl_color v2 \
dcl_texcoord v3 \
dcl_texcoord1 v4 \
m4x4	POS, v0, c[GC_MTX_WORLD] \
m3x3	NORMAL, v1, c[GC_MTX_WORLD] \
m4x4	oPos, v0, c[GC_MTX_WVP] \
mov	oT0, v3 \
mov	oT1, v4 \
dp3 VS_LTMP.xyz, c[GC_LIGHT0], NORMAL \
max VS_LTMP.xyz, VS_LTMP.xyz, c[GC_CONSTANT].xxx \
mad VS_LTMP.xyz, VS_LTMP, -c[GC_LIGHT0+1].www, VS_LTMP \
add VS_LTMP.xyz, VS_LTMP.xyz, c[GC_LIGHT0+1].www \
mul VS_LDIFRESULT.xyz, VS_LTMP, c[GC_LIGHT0+1].xyz \
sub VS_LDL.xyz, c[GC_LIGHT0+2], POS \
dp3 VS_LTMP.w, VS_LDL, VS_LDL \
rsq VS_LTMP.x, VS_LTMP.w \
mul VS_LTMP.w, VS_LTMP.w, VS_LTMP.x \
mad VS_LKa.w, c[GC_LIGHT0+4].z, VS_LTMP.w, c[GC_LIGHT0+4].y \
mad VS_LKa.w, VS_LKa.w, VS_LTMP.w, c[GC_LIGHT0+4].x \
rcp VS_LKa.w, VS_LKa.w \
mul VS_LDL.xyz, VS_LDL, VS_LTMP.x \
dp3 VS_LTMP.xyz, VS_LDL, NORMAL \
max VS_LTMP.xyz, VS_LTMP.xyz, c[GC_LIGHT0+3].w \
mul VS_LKa.xyz, VS_LKa.www, c[GC_LIGHT0+3].xyz \
mad VS_LDIFRESULT.xyz, VS_LTMP, VS_LKa, VS_LDIFRESULT.xyz \
sub VS_LDL.xyz, c[GC_LIGHT0+5], POS \
dp3 VS_LTMP.w, VS_LDL, VS_LDL \
rsq VS_LTMP.x, VS_LTMP.w \
mul VS_LTMP.w, VS_LTMP.w, VS_LTMP.x \
mad VS_LKa.w, c[GC_LIGHT0+7].z, VS_LTMP.w, c[GC_LIGHT0+7].y \
mad VS_LKa.w, VS_LKa.w, VS_LTMP.w, c[GC_LIGHT0+7].x \
rcp VS_LKa.w, VS_LKa.w \
mul VS_LDL.xyz, VS_LDL, VS_LTMP.x \
dp3 VS_LTMP.xyz, VS_LDL, NORMAL \
max VS_LTMP.xyz, VS_LTMP.xyz, c[GC_LIGHT0+6].w \
mul VS_LKa.xyz, VS_LKa.www, c[GC_LIGHT0+6].xyz \
mad VS_LDIFRESULT.xyz, VS_LTMP, VS_LKa, VS_LDIFRESULT.xyz \
sub VS_LDL.xyz, c[GC_LIGHT0+8], POS \
dp3 VS_LTMP.w, VS_LDL, VS_LDL \
rsq VS_LTMP.x, VS_LTMP.w \
mul VS_LTMP.w, VS_LTMP.w, VS_LTMP.x \
mad VS_LKa.w, c[GC_LIGHT0+10].z, VS_LTMP.w, c[GC_LIGHT0+10].y \
mad VS_LKa.w, VS_LKa.w, VS_LTMP.w, c[GC_LIGHT0+10].x \
rcp VS_LKa.w, VS_LKa.w \
mul VS_LDL.xyz, VS_LDL, VS_LTMP.x \
dp3 VS_LTMP.xyz, VS_LDL, NORMAL \
max VS_LTMP.xyz, VS_LTMP.xyz, c[GC_LIGHT0+9].w \
mul VS_LKa.xyz, VS_LKa.www, c[GC_LIGHT0+9].xyz \
mad VS_LDIFRESULT.xyz, VS_LTMP, VS_LKa, VS_LDIFRESULT.xyz \
sub VS_LDL.xyz, c[GC_LIGHT0+11], POS \
dp3 VS_LTMP.w, VS_LDL, VS_LDL \
rsq VS_LTMP.x, VS_LTMP.w \
mul VS_LTMP.w, VS_LTMP.w, VS_LTMP.x \
mad VS_LKa.w, c[GC_LIGHT0+13].z, VS_LTMP.w, c[GC_LIGHT0+13].y \
mad VS_LKa.w, VS_LKa.w, VS_LTMP.w, c[GC_LIGHT0+13].x \
rcp VS_LKa.w, VS_LKa.w \
mul VS_LDL.xyz, VS_LDL, VS_LTMP.x \
dp3 VS_LTMP.xyz, VS_LDL, NORMAL \
max VS_LTMP.xyz, VS_LTMP.xyz, c[GC_LIGHT0+12].w \
mul VS_LKa.xyz, VS_LKa.www, c[GC_LIGHT0+12].xyz \
mad VS_LDIFRESULT.xyz, VS_LTMP, VS_LKa, VS_LDIFRESULT.xyz \
sub VS_LDL.xyz, c[GC_LIGHT0+14], POS \
dp3 VS_LTMP.w, VS_LDL, VS_LDL \
rsq VS_LTMP.x, VS_LTMP.w \
mul VS_LTMP.w, VS_LTMP.w, VS_LTMP.x \
mad VS_LKa.w, c[GC_LIGHT0+16].z, VS_LTMP.w, c[GC_LIGHT0+16].y \
mad VS_LKa.w, VS_LKa.w, VS_LTMP.w, c[GC_LIGHT0+16].x \
rcp VS_LKa.w, VS_LKa.w \
mul VS_LDL.xyz, VS_LDL, VS_LTMP.x \
dp3 VS_LTMP.xyz, VS_LDL, NORMAL \
max VS_LTMP.xyz, VS_LTMP.xyz, c[GC_LIGHT0+15].w \
mul VS_LKa.xyz, VS_LKa.www, c[GC_LIGHT0+15].xyz \
mad VS_LDIFRESULT.xyz, VS_LTMP, VS_LKa, VS_LDIFRESULT.xyz \
sub VS_LDL.xyz, c[GC_LIGHT0+17], POS \
dp3 VS_LTMP.w, VS_LDL, VS_LDL \
rsq VS_LTMP.x, VS_LTMP.w \
mul VS_LTMP.w, VS_LTMP.w, VS_LTMP.x \
mad VS_LKa.w, c[GC_LIGHT0+19].z, VS_LTMP.w, c[GC_LIGHT0+19].y \
mad VS_LKa.w, VS_LKa.w, VS_LTMP.w, c[GC_LIGHT0+19].x \
rcp VS_LKa.w, VS_LKa.w \
mul VS_LDL.xyz, VS_LDL, VS_LTMP.x \
dp3 VS_LTMP.xyz, VS_LDL, NORMAL \
max VS_LTMP.xyz, VS_LTMP.xyz, c[GC_LIGHT0+18].w \
mul VS_LKa.xyz, VS_LKa.www, c[GC_LIGHT0+18].xyz \
mad VS_LDIFRESULT.xyz, VS_LTMP, VS_LKa, VS_LDIFRESULT.xyz \
sub VS_LDL.xyz, c[GC_LIGHT0+20], POS \
dp3 VS_LTMP.w, VS_LDL, VS_LDL \
rsq VS_LTMP.x, VS_LTMP.w \
mul VS_LTMP.w, VS_LTMP.w, VS_LTMP.x \
mad VS_LKa.w, c[GC_LIGHT0+22].z, VS_LTMP.w, c[GC_LIGHT0+22].y \
mad VS_LKa.w, VS_LKa.w, VS_LTMP.w, c[GC_LIGHT0+22].x \
rcp VS_LKa.w, VS_LKa.w \
mul VS_LDL.xyz, VS_LDL, VS_LTMP.x \
dp3 VS_LTMP.xyz, VS_LDL, NORMAL \
max VS_LTMP.xyz, VS_LTMP.xyz, c[GC_LIGHT0+21].w \
mul VS_LKa.xyz, VS_LKa.www, c[GC_LIGHT0+21].xyz \
mad VS_LDIFRESULT.xyz, VS_LTMP, VS_LKa, VS_LDIFRESULT.xyz \
sub VS_LDL.xyz, c[GC_LIGHT0+23], POS \
dp3 VS_LTMP.w, VS_LDL, VS_LDL \
rsq VS_LTMP.x, VS_LTMP.w \
mul VS_LTMP.w, VS_LTMP.w, VS_LTMP.x \
mad VS_LKa.w, c[GC_LIGHT0+25].z, VS_LTMP.w, c[GC_LIGHT0+25].y \
mad VS_LKa.w, VS_LKa.w, VS_LTMP.w, c[GC_LIGHT0+25].x \
rcp VS_LKa.w, VS_LKa.w \
mul VS_LDL.xyz, VS_LDL, VS_LTMP.x \
dp3 VS_LTMP.xyz, VS_LDL, NORMAL \
max VS_LTMP.xyz, VS_LTMP.xyz, c[GC_LIGHT0+24].w \
mul VS_LKa.xyz, VS_LKa.www, c[GC_LIGHT0+24].xyz \
mad VS_LDIFRESULT.xyz, VS_LTMP, VS_LKa, VS_LDIFRESULT.xyz \
sub VS_LDL.xyz, c[GC_LIGHT0+26], POS \
dp3 VS_LTMP.w, VS_LDL, VS_LDL \
rsq VS_LTMP.x, VS_LTMP.w \
mul VS_LTMP.w, VS_LTMP.w, VS_LTMP.x \
mad VS_LKa.w, c[GC_LIGHT0+28].z, VS_LTMP.w, c[GC_LIGHT0+28].y \
mad VS_LKa.w, VS_LKa.w, VS_LTMP.w, c[GC_LIGHT0+28].x \
rcp VS_LKa.w, VS_LKa.w \
mul VS_LDL.xyz, VS_LDL, VS_LTMP.x \
dp3 VS_LTMP.xyz, VS_LDL, NORMAL \
max VS_LTMP.xyz, VS_LTMP.xyz, c[GC_LIGHT0+27].w \
mul VS_LKa.xyz, VS_LKa.www, c[GC_LIGHT0+27].xyz \
mad VS_LDIFRESULT.xyz, VS_LTMP, VS_LKa, VS_LDIFRESULT.xyz \
mul oD0.xyz, VS_LDIFRESULT.xyz, v2 \
mov oD0.w, v2 \
}