template< typename AnimationType >
const int AnimationContainer< AnimationType >::INVALID_ANIMATION_ID( -1 );

template< typename AnimationType >
AnimationContainer< AnimationType >::AnimationContainer()
{

}

template< typename AnimationType >
AnimationContainer< AnimationType >::~AnimationContainer()
{
	clearAnimations();
}

template< typename AnimationType >
void AnimationContainer< AnimationType >::clearAnimations()
{
	for ( unsigned int i = 0; i < m_animations.size(); i++ )
	{
		delete m_animations[ i ];
	}
	m_animations.clear();
}

template< typename AnimationType >
void AnimationContainer< AnimationType >::addAnimation( AnimationType* animation )
{
	// Fail hard in debug mode, but continue running gracefully in release mode...
	assert( animation != NULL );
	if ( animation == NULL )
	{
		return;
	}

	int animationId = int( m_animations.size() );
	m_animations.push_back( animation );

	m_animationNameToIdDictionary[ animation->getName() ] = animationId;
}

template< typename AnimationType >
int AnimationContainer< AnimationType >::getAnimationId( const std::string& animationName ) const
{
	NameIndexDictionary::const_iterator cit = m_animationNameToIdDictionary.find( animationName );
	bool animationIdFound = ( cit != m_animationNameToIdDictionary.end() );

	if ( ! animationIdFound )
	{
		return INVALID_ANIMATION_ID;
	}

	int animationId = cit->second;

	return animationId;
}

template< typename AnimationType >
AnimationType* AnimationContainer< AnimationType >::getAnimation( const int animationId )
{
	if ( ! hasAnimation( animationId ) )
	{
		return NULL;
	}

	return m_animations[ animationId ];
}

template< typename AnimationType >
const AnimationType* AnimationContainer< AnimationType >::getAnimation( const int animationId ) const
{
	if ( ! hasAnimation( animationId ) )
	{
		return NULL;
	}

	return m_animations[ animationId ];
}

template< typename AnimationType >
bool AnimationContainer< AnimationType >::hasAnimation( const int animationId ) const
{
	return ( 0 <= animationId && animationId < getAnimationCount() );
}

template< typename AnimationType >
AnimationType* AnimationContainer< AnimationType >::getAnimation( const std::string& animationName )
{
	int animationId = getAnimationId( animationName );
	return getAnimation( animationId );
}

template< typename AnimationType >
const AnimationType* AnimationContainer< AnimationType >::getAnimation( const std::string& animationName ) const
{
	int animationId = getAnimationId( animationName );
	return getAnimation( animationId );
}

template< typename AnimationType >
bool AnimationContainer< AnimationType >::hasAnimation( const std::string& animationName ) const
{
	int animationId = getAnimationId( animationName );
	return hasAnimation( animationId );
}

template< typename AnimationType >
int AnimationContainer< AnimationType >::getAnimationCount() const
{
	return int( m_animations.size() );
}