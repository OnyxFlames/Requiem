/*
	Animation class.
	This class is for any game object that can/will contain an animation, AKA sprites, tiles, models etc.
	The game object will either inherit the animation class or just have one as a data member and just references it internally.
	TODO: Move content from AnimatedSprite to Animation
*/

#pragma once
class Animation
{
public:
	Animation();
	~Animation();
};

