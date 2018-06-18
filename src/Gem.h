#ifndef GEM_H
#define GEM_H

#include "TextureEntity.h"
#include "Const.h"

enum class MovingType
{
    None = 0,
    Vertical = 1,
    Horizontal = 2
};

class Gem : public TextureEntity
{
public:
    Gem();
    Gem(const std::shared_ptr<Texture>& texture, EntityAlign align = EntityAlign::LeftUpper);
    
    virtual void update(const double delta) override;
    virtual void render(SDL_Renderer* renderer) const override;
    
    // we can check if gems are equals by their texture
    bool isEqualTo(const Gem& anotherGem) const;
    
    // change place of gems
    void swap(Gem& anotherGem);
    
    // destroy gem
    void collapse();
    
    void setSelected(const bool isSelected);
    const bool isSelected() const;
    
    const bool isCollapsed() const;
    const bool willCollapse() const;
    
    // visibility of gem
    void setVisible(const bool isVisible);
    void changeVisibility(const double timeInMs);
    const bool isVisible() const;
    
    // moving gem
    void moveTo(const EntityPosition position);
    const MovingType getMovingType() const;
    
private:
    bool _isSelected = false;
    bool _isVisible = true;
    bool _isCollapsed = false;

    double timerToChangeVisible = 0.0f;
    bool isChangeVisibilityStarted = false;
    
    double timeToCollapse = GEM_COLLAPSE_TIME_MS;
    bool isCollapseStarted = false;
    
    EntityPosition moveToPosition;
    MovingType movingType = MovingType::None;
};

#endif
