#ifndef _RESOURCES_MANAGER_H_
#define _RESOURCES_MANAGER_H_


#include <SFML/Graphics.hpp>
#include <string>


class ResourcesManager
{
public:
	ResourcesManager();
	~ResourcesManager();

    sf::Texture * getTexture(const std::string &path);
    sf::Texture * addTexture(const std::string &path);
    void removeTexture(const std::string &path);

    sf::Font * getFont(const std::string &path);
    sf::Font * addFont(const std::string &path);
    void removeFont(const std::string &path);

private:
    std::map<std::string, sf::Texture *> m_textures;
    std::map<std::string, sf::Font *> m_fonts;
};


#endif // _RESOURCES_MANAGER_H_

