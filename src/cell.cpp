#include <cell.h>
#include <random>



bool Cell::HasNonVisitedNeighbours() const{
    for(int i = 0; i < 4; i++){
        if(walls[i] == true){
            return true;
        }
    }

    return false;
}

void Cell::UpdateNextCellVisitedNeighbours(globals::DIRECTION dir){
    switch (dir)
    {
    case globals::UP:
        visited_neighbours.push_back(globals::DOWN);
        break;
    
    case globals::RIGHT:
        visited_neighbours.push_back(globals::LEFT);
        break;

    case globals::DOWN:
        visited_neighbours.push_back(globals::UP);
        break;

    case globals::LEFT:
        visited_neighbours.push_back(globals::RIGHT);
        break;

    default:
        break;
    }
}

bool Cell::IsDirectionVisited(globals::DIRECTION dir) const{
    for(int i = 0; i < visited_neighbours.size(); i++){
        if(visited_neighbours[i] == dir) return true;
    }
    return false;
}

bool Cell::HasAvailableConnections() const{
    for(int i = 0; i < 4; i++){
        if(walls[i] == false && !IsDirectionVisited(static_cast<globals::DIRECTION>(i))){
            return true;
        }
    }
    return false;
}


std::vector<std::pair<int,int>> Cell::GetCellEdges() const{
    std::vector<std::pair<int,int>> cell_edges(4);

    cell_edges[0] = std::make_pair(x*globals::CELL_SIZE, y*globals::CELL_SIZE); // top left
    cell_edges[1] = std::make_pair((x+1)*globals::CELL_SIZE, y*globals::CELL_SIZE); // top right
    cell_edges[2] = std::make_pair((x+1)*globals::CELL_SIZE, (y+1)*globals::CELL_SIZE); // bottom right
    cell_edges[3] = std::make_pair(x*globals::CELL_SIZE, (y+1)*globals::CELL_SIZE); // bottom left

    return cell_edges;
}