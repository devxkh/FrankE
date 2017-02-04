@insertpiece( SetCrossPlatformSettings )

out gl_PerVertex
{
	vec4 gl_Position;
};

layout(std140) uniform;

@insertpiece( Common_Matrix_DeclUnpackMatrix4x4 )

in vec4 vertex;

@property( hlms_skeleton )
in uvec4 blendIndices;
in vec4 blendWeights;@end

@property( hlms_colour )in vec4 colour;@end

@foreach( hlms_uv_count, n )
in vec@value( hlms_uv_count@n ) uv@n;@end

in uint drawId;

@insertpiece( custom_vs_attributes )

@property( !hlms_shadowcaster || !hlms_shadow_uses_depth_texture )
out block
{
@insertpiece( VStoPS_block )
} outVs;
@end

// START UNIFORM DECLARATION
@insertpiece( PassDecl )
@insertpiece( InstanceDecl )
layout(binding = 0) uniform samplerBuffer worldMatBuf;
@property( texture_matrix )layout(binding = 1) uniform samplerBuffer animationMatrixBuf;@end
@insertpiece( custom_vs_uniformDeclaration )
// END UNIFORM DECLARATION

@property( hlms_skeleton )@piece( SkeletonTransform )
	uint _idx = (blendIndices[0] << 1u) + blendIndices[0]; //blendIndices[0] * 3u; a 32-bit int multiply is 4 cycles on GCN! (and mul24 is not exposed to GLSL...)
        uint matStart = instance.worldMaterialIdx[drawId].x >> 9u;
	vec4 worldMat[3];
        worldMat[0] = texelFetch( worldMatBuf, int(matStart + _idx + 0u) );
        worldMat[1] = texelFetch( worldMatBuf, int(matStart + _idx + 1u) );
        worldMat[2] = texelFetch( worldMatBuf, int(matStart + _idx + 2u) );
    vec4 worldPos;
    worldPos.x = dot( worldMat[0], vertex );
    worldPos.y = dot( worldMat[1], vertex );
    worldPos.z = dot( worldMat[2], vertex );
    worldPos.xyz *= blendWeights[0];

	@psub( NeedsMoreThan1BonePerVertex, hlms_bones_per_vertex, 1 )
	@property( NeedsMoreThan1BonePerVertex )vec4 tmp;
	tmp.w = 1.0;@end //!NeedsMoreThan1BonePerVertex
	@foreach( hlms_bones_per_vertex, n, 1 )
	_idx = (blendIndices[@n] << 1u) + blendIndices[@n]; //blendIndices[@n] * 3; a 32-bit int multiply is 4 cycles on GCN! (and mul24 is not exposed to GLSL...)
        worldMat[0] = texelFetch( worldMatBuf, int(matStart + _idx + 0u) );
        worldMat[1] = texelFetch( worldMatBuf, int(matStart + _idx + 1u) );
        worldMat[2] = texelFetch( worldMatBuf, int(matStart + _idx + 2u) );
	tmp.x = dot( worldMat[0], vertex );
	tmp.y = dot( worldMat[1], vertex );
	tmp.z = dot( worldMat[2], vertex );
	worldPos.xyz += (tmp * blendWeights[@n]).xyz;
	
	@end

	worldPos.w = 1.0;
@end @end //SkeletonTransform // !hlms_skeleton


@property( !hlms_identity_world )
	@piece( worldViewProj )worldViewProj@end
@end @property( hlms_identity_world )
	@property( !hlms_identity_viewproj_dynamic )
		@piece( worldViewProj )pass.viewProj[@value(hlms_identity_viewproj)]@end
	@end @property( hlms_identity_viewproj_dynamic )
		@piece( worldViewProj )pass.viewProj[instance.materialIdx[drawId].z]@end
	@end
@end

void main()
{
	@insertpiece( custom_vs_preExecution )
	@property( !hlms_identity_world )
		mat4 worldViewProj;
		worldViewProj = UNPACK_MAT4( worldMatBuf, drawId );
	@end

@property( !hlms_dual_paraboloid_mapping )
	gl_Position = vertex * @insertpiece( worldViewProj );
@end

@property( hlms_dual_paraboloid_mapping )
	//Dual Paraboloid Mapping
	gl_Position.w	= 1.0f;
	gl_Position.xyz	= (vertex * @insertpiece( worldViewProj )).xyz;
	float L = length( gl_Position.xyz );
	gl_Position.z	+= 1.0f;
	gl_Position.xy	/= gl_Position.z;
	gl_Position.z	= (L - NearPlane) / (FarPlane - NearPlane);
@end

@property( !hlms_shadowcaster )
@property( hlms_colour )	outVs.colour = colour;@end

@property( texture_matrix )	mat4 textureMatrix;@end

@foreach( out_uv_count, n )
	@property( out_uv@n_texture_matrix )
		textureMatrix = UNPACK_MAT4( animationMatrixBuf, (instance.materialIdx[drawId].x << 4u) + @value( out_uv@n_tex_unit )u );
		outVs.uv@value( out_uv@n_out_uv ).@insertpiece( out_uv@n_swizzle ) = (vec4( uv@value( out_uv@n_source_uv ).xy, 0, 1 ) * textureMatrix).xy;
	@end @property( !out_uv@n_texture_matrix )
		outVs.uv@value( out_uv@n_out_uv ).@insertpiece( out_uv@n_swizzle ) = uv@value( out_uv@n_source_uv ).xy;
	@end @end

	outVs.drawId = drawId;

@end @property( hlms_shadowcaster )
	float shadowConstantBias = uintBitsToFloat( instance.materialIdx[drawId].y );

	@property( !hlms_shadow_uses_depth_texture )
		//Linear depth
		outVs.depth	= (gl_Position.z - pass.depthRange.x + shadowConstantBias * pass.depthRange.y) * pass.depthRange.y;
		outVs.depth = (outVs.depth * 0.5) + 0.5;
	@end

	//We can't make the depth buffer linear without Z out in the fragment shader;
	//however we can use a cheap approximation ("pseudo linear depth")
	//see http://www.yosoygames.com.ar/wp/2014/01/linear-depth-buffer-my-ass/
	gl_Position.z = (gl_Position.z - pass.depthRange.x + shadowConstantBias * pass.depthRange.y) * pass.depthRange.y * gl_Position.w;
@end
	@insertpiece( custom_vs_posExecution )
}
