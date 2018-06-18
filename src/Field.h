#ifndef FIELD_H
#define FIELD_H

#include <vector>

#include "Gem.h"
#include "Sound.h"

class Field
{
public:
    Field();
    
    // set textures for gems
    void setTextures(const std::vector< std::shared_ptr<Texture> >& gemTextures);
    // vector of sounds for collapsing gem
    void setCollapseSounds(const std::vector< std::shared_ptr<Sound> >& soundsForGemCollapse);
    
    // generate new field of gems
    void generateGems();
    
    void update(const double delta);
    void render(SDL_Renderer * renderer) const;
    
    // reset parameters of field
    void reset();
    
    // called when clicking on gem
    void onGemClick(const int gemPosition);
    
    // score setter and getter
    const int getScore() const;
    void setScore(const int score);
    
    // return random texture for field generation
    std::shared_ptr<Texture> getRandomGemTexture();
    // get gem by click in field
    const int getGemPosByMouseCoordinates(const int x, const int y) const;
    
private:
    const bool tryToCollapseGem(const int gemPosition);
    std::vector<int> getCollapseColumnForPosition(const int gemPosition) const;
    std::vector<int> getCollapseRowForPosition(const int gemPosition) const;
    
    std::vector< std::shared_ptr<Texture> > gemTextures;
    std::vector< std::shared_ptr<Sound> > soundsCollapse;
    std::vector<Gem> gems;
    
    int selectedGemNumber = -1;
    int swipedGemOne = -1;
    int swipedGemTwo = -1;
    
    int score;
    double removeScore = 0.0f;
};

#endif
