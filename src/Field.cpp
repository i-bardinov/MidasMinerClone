#include "Field.h"
#include "Const.h"
#include "Game.h"

Field::Field()
{
    
}

void Field::setTextures(const std::vector< std::shared_ptr<Texture> >& _gemTextures)
{
    this->gemTextures = _gemTextures;
}

void Field::setCollapseSounds(const std::vector< std::shared_ptr<Sound> >& soundsForGemCollapse)
{
    this->soundsCollapse = soundsForGemCollapse;
}

void Field::update(const double delta)
{
    for(Gem &gem : gems)
    {
        gem.update(delta);
    }
    
    if(gems.size() > 0)
    {
        // remove some score amount while not collapsing gems
        if(removeScore > 0.0f)
        {
            removeScore -= delta;
        } else {
            score -= SCORE_REMOVING;
            if(score < 0)
                score = 0;
            removeScore = SCORE_TIME_REMOVING_MS;
        }
    }
    
    if(gameTimer > 0)
    {
        gameTimer -= delta;
    }
    
    // check if we can swipe two gems
    if(swipedGemOne != -1 && swipedGemTwo != -1)
    {
        if(gems[swipedGemOne].getMovingType() == MovingType::None && gems[swipedGemTwo].getMovingType() == MovingType::None)
        {
            if(!tryToCollapseGem(swipedGemOne) && !tryToCollapseGem(swipedGemTwo))
            {
                onGemClick(swipedGemTwo);
                onGemClick(swipedGemOne);
            }
            swipedGemOne = -1;
            swipedGemTwo = -1;
        }
    }
    
    // moving gems when some was collapsed
    for(int i = gems.size() - 1; i >= 0; i--)
    {
        // check all collapsed gems
        if(gems[i].isCollapsed())
        {
            bool isFound = false;
            for(int j = i; j >= 0; j -= GEM_COLUMNS)
            {
                // check if we found gem that higher than collapsed => move it to collapsed gem position
                if(!gems[j].isCollapsed() && !gems[j].willCollapse() && gems[j].getMovingType() == MovingType::None)
                {
                    isFound = true;
                    gems[j].moveTo(gems[i].getPosition());
                    gems[i].setPosition(gems[j].getPosition());
                    std::swap(gems[i], gems[j]);
                    break;
                }
            }
            // if not found higher gem for moving => generate new gem higher collapsed and move it
            if(!isFound)
            {
                int count = 1;
                for(int j = i; j >= 0; j -= GEM_COLUMNS)
                {
                    EntityPosition pos = gems[j].getPosition();
                    EntityPosition moveToPos = pos;
                    pos.y -= (i / GEM_COLUMNS) * GEM_SIZE + GEM_SIZE * count;
                    gems[j] = Gem(getRandomGemTexture(), EntityAlign::Center);
                    gems[j].setPosition(pos);
                    gems[j].moveTo(moveToPos);
                }
            }
        }
    }
    
    // check if there exist gems that moving or going to collapse
    bool needCheck = true;
    for(const Gem &gem : gems)
    {
        if(gem.isCollapsed() || gem.willCollapse() || gem.getMovingType() != MovingType::None)
        {
            needCheck = false;
            break;
        }
    }
    
    // if there are no moving gems or collapsing => check if there are another gems that can be collapsed
    if(needCheck)
    {
        for(int i = gems.size() - 1; i >= 0; i--)
        {
            tryToCollapseGem(i);
        }
    }
}

void Field::render(SDL_Renderer* renderer) const
{
    for(const Gem &gem : gems)
    {
        gem.render(renderer);
    }
}

void Field::generateGems()
{
    gems.clear();
    // generate random field of gems
    int posX = 0;
    int posY = FIELD_START_Y - GEM_SIZE / 2;
    for(int i = 0; i < GEM_ROWS * GEM_COLUMNS; i++)
    {
        if(i % GEM_COLUMNS == 0)
        {
            posX = FIELD_START_X + GEM_SIZE / 2;
            posY += GEM_SIZE;
        }
        
        int random = rand() % gemTextures.size();
        std::shared_ptr<Texture> randomTexture = gemTextures[random];
        if(i % GEM_COLUMNS >= 2)
        {
            Gem prevGem1 = gems[i - 1];
            Gem prevGem2 = gems[i - 2];
            // check if there are three gems with same colour => regenerate third gem for another color
            if(prevGem1.getTexture() == randomTexture && prevGem2.getTexture() == randomTexture)
            {
                random = (random + 1) % gemTextures.size();
                randomTexture = gemTextures[random];
            }
        }
        if(i / GEM_COLUMNS >= 2)
        {
            Gem prevGem1 = gems[i - 1 * GEM_COLUMNS];
            Gem prevGem2 = gems[i - 2 * GEM_COLUMNS];
            // check if there are three gems with same colour => regenerate third gem for another color
            if(prevGem1.getTexture() == randomTexture && prevGem2.getTexture() == randomTexture)
            {
                random = (random + 1) % gemTextures.size();
                randomTexture = gemTextures[random];
            }
        }
        if(i % GEM_COLUMNS >= 2)
        {
            Gem prevGem1 = gems[i - 1];
            Gem prevGem2 = gems[i - 2];
            // check if there are three gems with same colour => regenerate third gem for another color
            if(prevGem1.getTexture() == randomTexture && prevGem2.getTexture() == randomTexture)
            {
                random = (random + 1) % gemTextures.size();
                randomTexture = gemTextures[random];
            }
        }
        
        Gem gem(randomTexture, EntityAlign::Center);
        EntityPosition pos;
        pos.x = posX;
        pos.y = posY;
        gem.setPosition(pos);
        gem.setVisible(false);
        // make gem appears in different time as an effect
        gem.changeVisibility(15 * (GEM_ROWS * GEM_COLUMNS - i));
        gems.push_back(gem);
        
        posX += GEM_SIZE;
    }
}

void Field::reset()
{
    gems.clear();
    selectedGemNumber = -1;
    swipedGemOne = -1;
    swipedGemTwo = -1;
    removeScore = 0.0f;
}

void Field::startTimer()
{
    gameTimer = GAME_TIMER;
}

const double Field::getTimer()
{
    return gameTimer;
}

void Field::onGemClick(const int gemPosition)
{
    // action on clicking on gem => we can make it selected or we can swipe two gems
    if(gemPosition < gems.size() && gemPosition >= 0)
    {
        if(selectedGemNumber == -1)
        {
            selectedGemNumber = gemPosition;
            gems[selectedGemNumber].setSelected(true);
        } else {
            if(gems[selectedGemNumber].isSelected())
            {
                gems[selectedGemNumber].setSelected(false);

                EntityPosition posSelected = gems[selectedGemNumber].getPosition();
                EntityPosition posSecond = gems[gemPosition].getPosition();
                if((posSelected.x == posSecond.x && abs(posSelected.y - posSecond.y) == GEM_SIZE)
                   || (posSelected.y == posSecond.y && abs(posSelected.x - posSecond.x) == GEM_SIZE))
                {
                    gems[selectedGemNumber].swap(gems[gemPosition]);
                    std::swap(gems[selectedGemNumber], gems[gemPosition]);
                    swipedGemOne = selectedGemNumber;
                    swipedGemTwo = gemPosition;
                }
                selectedGemNumber = -1;
            }
            else
            {
                selectedGemNumber = gemPosition;
                gems[selectedGemNumber].setSelected(true);
            }
        }
    }
}

const int Field::getScore() const
{
    return score;
}

void Field::setScore(const int _score)
{
    this->score = _score;
}

std::shared_ptr<Texture>& Field::getRandomGemTexture()
{
    int random = rand() % gemTextures.size();
    return gemTextures[random];
}

const int Field::getGemPosByMouseCoordinates(const int x, const int y) const
{
    // return gem position by mouse coordinates
    // return -1 if we out of field
    if(x > FIELD_START_X + GEM_COLUMNS * GEM_SIZE || y > FIELD_START_Y + GEM_ROWS * GEM_SIZE)
        return -1;
    if(x < FIELD_START_X || y < FIELD_START_Y)
        return -1;
    
    // return -1 if we gems are moving
    for(const Gem &gem : gems)
    {
        if(gem.isCollapsed() || gem.willCollapse() || gem.getMovingType() != MovingType::None)
        {
            return -1;
        }
    }
    
    int currMousePosX = x - FIELD_START_X;
    int currMousePosY = y - FIELD_START_Y;
    int pos = 0;
    
    while(currMousePosY > GEM_SIZE)
    {
        currMousePosY -= GEM_SIZE;
        pos += GEM_COLUMNS;
    }
    while(currMousePosX > GEM_SIZE)
    {
        currMousePosX -= GEM_SIZE;
        pos += 1;
    }
    
    if(pos >= gems.size())
        return -1;
    
    // moving gem is not possible to detect in out game (we shouldn't select them or swipe)
    if(gems[pos].getMovingType() != MovingType::None || !gems[pos].isVisible())
        return -1;
        
    return pos;
}

const bool Field::tryToCollapseGem(const int gemPosition)
{
    std::vector<int> columns = getCollapseColumnForPosition(gemPosition);
    std::vector<int> rows = getCollapseRowForPosition(gemPosition);
    int columnsCount = columns.size();
    int rowsCount = rows.size();
    
    if(columnsCount < 3 && rowsCount < 3)
    {
        return false;
    } else {
        if(soundsCollapse.size() > 0)
        {
            int random = rand() % soundsCollapse.size();
            soundsCollapse[random]->play();
            gameTimer += ADDITIONAL_TIMER;
        }
    }
    
    int addScore = 0;
    if(columnsCount >= 3)
    {
        addScore += columnsCount;
        for(const int i : columns)
        {
            gems[i].collapse();
        }
    }
    
    if(rowsCount >= 3)
    {
        addScore += rowsCount;
        for(const int i : rows)
        {
            gems[i].collapse();
        }
    }
    
    score += addScore * SCORE_PER_GEM;
    removeScore = SCORE_TIME_REMOVING_MS;
    
    return true;
}

std::vector<int> Field::getCollapseColumnForPosition(const int gemPosition) const
{
    std::vector<int> positions;
    positions.push_back(gemPosition);
    for(int i = gemPosition + GEM_COLUMNS; i < gems.size(); i += GEM_COLUMNS)
    {
        if(gems[i].isEqualTo(gems[gemPosition]) && gems[i].getMovingType() == MovingType::None && !gems[i].willCollapse() & !gems[i].isCollapsed())
            positions.push_back(i);
        else
            break;
    }
    for(int i = gemPosition - GEM_COLUMNS; i >= 0; i -= GEM_COLUMNS)
    {
        if(gems[i].isEqualTo(gems[gemPosition]) && gems[i].getMovingType() == MovingType::None && !gems[i].willCollapse() & !gems[i].isCollapsed())
            positions.push_back(i);
        else
            break;
    }
    
    return positions;
}

std::vector<int> Field::getCollapseRowForPosition(const int gemPosition) const
{
    std::vector<int> positions;
    positions.push_back(gemPosition);
    int rowNumber = 1 + (gemPosition / GEM_COLUMNS);
    for(int i = gemPosition + 1; i < rowNumber * GEM_COLUMNS; i += 1)
    {
        if(gems[i].isEqualTo(gems[gemPosition]) && gems[i].getMovingType() == MovingType::None && !gems[i].willCollapse() & !gems[i].isCollapsed())
            positions.push_back(i);
        else
            break;
    }
    for(int i = gemPosition - 1; i >= (rowNumber - 1) * GEM_COLUMNS; i -= 1)
    {
        if(gems[i].isEqualTo(gems[gemPosition]) && gems[i].getMovingType() == MovingType::None && !gems[i].willCollapse() & !gems[i].isCollapsed())
            positions.push_back(i);
        else
            break;
    }
    
    return positions;
}
