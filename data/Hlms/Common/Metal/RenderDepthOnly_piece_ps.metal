
@property( !hlms_render_depth_only )
	@piece( output_type )PS_OUTPUT@end
@end @property( hlms_render_depth_only )
	@piece( output_type )void@end
@end

@property( hlms_render_depth_only && !alpha_test && !hlms_shadows_esm )
	@set( hlms_disable_stage, 1 )
@end

@piece( DeclOutputType )
	struct PS_OUTPUT
	{
		@property( !hlms_shadowcaster )
			float4 colour0	[[ color(0) ]];
		@end @property( hlms_shadowcaster )
			@property( !hlms_render_depth_only )
				float colour0	[[ color(0) ]];
			@end
			@property( hlms_render_depth_only )
				float colour0	[[ depth(any) ]];
			@end
		@end
	};
@end
