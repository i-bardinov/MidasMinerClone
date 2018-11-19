#include "Gem.h"
#include <cstdlib>

Gem::Gem() : TextureEntity()
{
    
}

Gem::Gem(const std::shared_ptr<Sprite>& texture, EntityAlign align) : TextureEntity(texture, align)
{
    
}

void Gem::update(const double delta)
{
    // timer for make gem visible (for start)
    if(isChangeVisibilityStarted)
    {
        if(timerToChangeVisible > 0.0f)
        {
            timerToChangeVisible -= delta;
        } else {
            isChangeVisibilityStarted = false;
            _isVisible = !_isVisible;
        }
    }
    
    // timer to make gem collapse
    if(isCollapseStarted)
    {
        if(timeToCollapse > 0.0f)
        {
            timeToCollapse -= delta;
            setSizeMultiplier(timeToCollapse / GEM_COLLAPSE_TIME_MS);
        } else {
            isCollapseStarted = false;
            _isVisible = false;
            _isCollapsed = true;
        }
    }
    
    // moving gem horizontally
    if(movingType == MovingType::Horizontal)
    {
        double deltaMultiplier = 0.25f;
        if(moveToPosition.x < getPosition().x)
            deltaMultiplier *= -1;
        
        if(abs(moveToPosition.x - getPosition().x) > fabs(delta * deltaMultiplier))
        {
            EntityPosition newPos = getPosition();
            newPos.x += delta * deltaMultiplier;
            setPosition(newPos);
        } else {
            movingType = MovingType::None;
            setPosition(moveToPosition);
        }
    }
    
    // moving gem vertically
    if(movingType == MovingType::Vertical)
    {
        double deltaMultiplier = 0.25f;
        if(moveToPosition.y < getPosition().y)
            deltaMultiplier *= -1;
        
        if(abs(moveToPosition.y - getPosition().y) > fabs(delta * deltaMultiplier))
        {
            EntityPosition newPos = getPosition();
            newPos.y += delta * deltaMultiplier;
            setPosition(newPos);
        } else {
            movingType = MovingType::None;
            setPosition(moveToPosition);
        }
    }
}

void Gem::render(SDL_Renderer * renderer) const
{
    if(getPosition().y < FIELD_START_Y - GEM_SIZE / 2)
    {
        return;
    }
    
    if(_isVisible)
    {
        TextureEntity::render(renderer);
    }
}

bool Gem::isEqualTo(const Gem& anotherGem) const
{
    if(getTexture() == anotherGem.getTexture())
        return true;
    return false;
}

void Gem::swap(Gem& anotherGem)
{
    // if gem is moving we should get it future position
    
    if(getMovingType() == MovingType::None)
    {
        moveTo(anotherGem.getPosition());
    } else {
        moveTo(anotherGem.moveToPosition);
    }
    
    if(anotherGem.getMovingType() == MovingType::None)
    {
        anotherGem.moveTo(getPosition());
    } else {
        anotherGem.moveTo(moveToPosition);
    }
}

void Gem::collapse()
{
    isCollapseStarted = true;
}

void Gem::setSelected(const bool _isSelected)
{
    this->_isSelected = _isSelected;
    if(_isSelected)
        setSizeMultiplier(0.7f);
    else
        setSizeMultiplier(1.0f);
}

const bool Gem::isSelected() const
{
    return _isSelected;
}

void Gem::setVisible(const bool isVisible)
{
    this->_isVisible = isVisible;
}

void Gem::changeVisibility(double timeInMs)
{
    isChangeVisibilityStarted = true;
    timerToChangeVisible = timeInMs;
}

const bool Gem::isVisible() const
{
    return _isVisible;
}

const bool Gem::isCollapsed() const
{
    return _isCollapsed;
}

const bool Gem::willCollapse() const
{
    return isCollapseStarted;
}

void Gem::moveTo(const EntityPosition position)
{
    this->moveToPosition = position;
    // set moving type
    MovingType tempType = MovingType::Horizontal;
    if(moveToPosition.x == getPosition().x)
        tempType = MovingType::Vertical;
    
    this->movingType = tempType;
}

const MovingType Gem::getMovingType() const
{
    return movingType;
}
