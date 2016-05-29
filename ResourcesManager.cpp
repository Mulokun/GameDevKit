#include "ResourcesManager.h"

#include "Log.h"

// CONSTRUCTOR / DESTRUCTOR

ResourcesManager::ResourcesManager()
{

}

ResourcesManager::~ResourcesManager()
{
	for( std::map<std::string, sf::Texture *>::iterator it = m_textures.begin(); it != m_textures.end(); it++ )
	{
		delete ( *it ).second;
	}
}

// ***

// TEXTURES :

sf::Texture * ResourcesManager::getTexture( const std::string &path )
{
	std::map<std::string, sf::Texture *>::iterator it = m_textures.find( path );
	if( it == m_textures.end() )
	{
		return addTexture( path );
	}
	return ( *it ).second;
}

sf::Texture * ResourcesManager::addTexture( const std::string &path )
{
	std::map<std::string, sf::Texture *>::iterator it = m_textures.find( path );
	if( it != m_textures.end() )
	{
		delete ( *it ).second;
	}
	sf::Texture * texture = new sf::Texture();
	if( !texture->loadFromFile( path ) )
	{
		log( LOG_ERROR ) << "Can't load texture : " << path << std::endl;
	}
	m_textures[path] = texture;
	return texture;
}

void ResourcesManager::removeTexture( const std::string &path )
{
	std::map<std::string, sf::Texture *>::iterator it = m_textures.find( path );
	if( it != m_textures.end() )
	{
		delete ( *it ).second;
	}
	else
	{
		log( LOG_WARNING ) << "Remove texture : \"" << path << "\" impossible." << std::endl;
	}
}


// FONTS :

sf::Font * ResourcesManager::getFont( const std::string &path )
{
	std::map<std::string, sf::Font *>::iterator it = m_fonts.find( path );
	if( it == m_fonts.end() )
	{
		return addFont( path );
	}
	return ( *it ).second;
}

sf::Font * ResourcesManager::addFont( const std::string &path )
{
	std::map<std::string, sf::Font *>::iterator it = m_fonts.find( path );
	if( it != m_fonts.end() )
	{
		delete ( *it ).second;
	}
	sf::Font * font = new sf::Font();
	if( !font->loadFromFile( path ) )
	{
		log( LOG_ERROR ) << "Can't load font : " << path << std::endl;
	}
	m_fonts[path] = font;
	return font;
}

void ResourcesManager::removeFont( const std::string &path )
{
	std::map<std::string, sf::Font *>::iterator it = m_fonts.find( path );
	if( it != m_fonts.end() )
	{
		delete ( *it ).second;
	}
	else
	{
		log( LOG_WARNING ) << "Remove font : \"" << path << "\" impossible." << std::endl;
	}
}

